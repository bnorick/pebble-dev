#!/usr/bin/env python3

import argparse
import json
import queue
import threading
import time
import uuid

from libpebble2.communication import PebbleConnection
from libpebble2.communication.transports.websocket import WebsocketTransport
from libpebble2.exceptions import TimeoutError
from libpebble2.services.appmessage import AppMessageService, ByteArray, CString, Int32, Uint32
from pebble_tool.sdk.emulator import get_emulator_info


def parse_args():
    parser = argparse.ArgumentParser(description="Send one or more AppMessages to a running Pebble emulator.")
    parser.add_argument("--platform", default="emery", help="Target emulator platform")
    parser.add_argument("--app-uuid", required=True, help="Target app UUID")
    parser.add_argument("--messages-file", required=True, help="JSON file containing a list of messages")
    parser.add_argument("--ack-timeout", type=float, default=10.0, help="Seconds to wait for each ACK")
    parser.add_argument("--message-delay-ms", type=int, default=0, help="Delay between messages")
    parser.add_argument("--verbose", action="store_true", help="Print progress for each message")
    return parser.parse_args()


def typed_dictionary(message):
    dictionary = {}

    for key, value in message.get("uint", {}).items():
      dictionary[int(key)] = Uint32(int(value))
    for key, value in message.get("int", {}).items():
      dictionary[int(key)] = Int32(int(value))
    for key, value in message.get("string", {}).items():
      dictionary[int(key)] = CString(str(value))
    for key, value in message.get("bytes", {}).items():
      dictionary[int(key)] = ByteArray(bytes.fromhex(str(value)))

    return dictionary


def open_connection(platform):
    emulator_info = get_emulator_info(platform)
    if not emulator_info or "pypkjs" not in emulator_info or "port" not in emulator_info["pypkjs"]:
        raise RuntimeError(f"No running emulator info found for platform {platform}")

    port = emulator_info["pypkjs"]["port"]
    transport = WebsocketTransport(f"ws://localhost:{port}/")
    transport.connect()
    connection = PebbleConnection(transport)
    thread = threading.Thread(target=connection.run_sync, daemon=True, name="PebbleConnection")
    thread.start()
    return connection


def wait_for_result(ack_queue, expected_tid, timeout):
    deadline = time.time() + timeout
    while True:
        remaining = deadline - time.time()
        if remaining <= 0:
            raise TimeoutError()

        try:
            kind, tid = ack_queue.get(timeout=remaining)
            if tid != expected_tid:
                continue
            if kind == "ack":
                return
            if kind == "nack":
                raise RuntimeError(f"Received NACK for transaction {expected_tid}")
        except queue.Empty:
            continue


def main():
    args = parse_args()
    app_uuid = uuid.UUID(args.app_uuid)
    with open(args.messages_file, "r", encoding="utf-8") as handle:
        messages = json.load(handle)

    connection = open_connection(args.platform)
    service = AppMessageService(connection)
    ack_queue = queue.Queue()

    ack_handle = service.register_handler("ack", lambda tid, _uuid: ack_queue.put(("ack", tid)))
    nack_handle = service.register_handler("nack", lambda tid, _uuid: ack_queue.put(("nack", tid)))

    try:
        for index, message in enumerate(messages, start=1):
            if args.verbose:
                print(f"send_app_messages: sending {index}/{len(messages)}")
            tid = service.send_message(app_uuid, typed_dictionary(message))
            wait_for_result(ack_queue, tid, args.ack_timeout)
            if args.verbose:
                print(f"send_app_messages: ack {index}/{len(messages)} tid={tid}")
            if args.message_delay_ms > 0 and index < len(messages):
                time.sleep(args.message_delay_ms / 1000.0)
    finally:
        service.unregister_handler(ack_handle)
        service.unregister_handler(nack_handle)
        service.shutdown()


if __name__ == "__main__":
    main()
