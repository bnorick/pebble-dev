#!/usr/bin/env python3

from pathlib import Path
import re
import sys


REPO_ROOT = Path(__file__).resolve().parent.parent
C_HEADER_PATH = REPO_ROOT / "src" / "c" / "thymer.h"
PKJS_PATH = REPO_ROOT / "src" / "pkjs" / "pebble-js-app.js"


def read_text(file_path: Path) -> str:
  return file_path.read_text(encoding="utf-8")


def extract_max_timers(pattern: str, text: str, source: Path) -> int:
  match = re.search(pattern, text, re.MULTILINE)
  if not match:
    raise ValueError(f"could not find MAX_TIMERS in {source.relative_to(REPO_ROOT)}")
  return int(match.group(1))


def main() -> int:
  c_max = extract_max_timers(
    r"^#define\s+MAX_TIMERS\s+(\d+)\s*$",
    read_text(C_HEADER_PATH),
    C_HEADER_PATH,
  )
  pkjs_max = extract_max_timers(
    r"^const\s+MAX_TIMERS\s*=\s*(\d+);\s*$",
    read_text(PKJS_PATH),
    PKJS_PATH,
  )

  if c_max != pkjs_max:
    print("MAX_TIMERS is out of sync:", file=sys.stderr)
    print(f"- src/c/thymer.h: {c_max}", file=sys.stderr)
    print(f"- src/pkjs/pebble-js-app.js: {pkjs_max}", file=sys.stderr)
    print("", file=sys.stderr)
    print("Update both constants together before committing.", file=sys.stderr)
    return 1

  print(f"MAX_TIMERS is in sync at {c_max}")
  return 0


if __name__ == "__main__":
  raise SystemExit(main())
