# Constants

Source: https://developer.repebble.com/docs/pebblekit-android/com/getpebble/android/kit/Constants/

[java.lang.Object](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Object.html "class or interface in java.lang")
com.getpebble.android.kit.Constants

* * *

public final class Constantsextends [Object](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Object.html "class or interface in java.lang")

Constant values used by PebbleKit-enabled android applications.

- 
## Nested Class Summary

Nested Classes

Modifier and Type

Class

Description

`static enum `

`Constants.PebbleAppType`

The Enum PebbleAppType.

`static enum `

`Constants.PebbleDataType`

The Enum PebbleDataType.

- 
## Field Summary

Fields

Modifier and Type

Field

Description

`static final String`

`APP_UUID`

The bundle-key used to store a message's UUID.

`static final String`

`CUST_APP_TYPE`

The bundle-key used to store the type of application being customized in a CUSTOMIZE intent.

`static final String`

`CUST_ICON`

The bundle-key used to store the custom icon provided in a CUSTOMIZE intent.

`static final String`

`CUST_NAME`

The bundle-key used to store the custom name provided in a CUSTOMIZE intent.

`static final String`

`DATA_LOG_TAG`

A bundle-key used to store the tag for the corresponding data log.

`static final String`

`DATA_LOG_TIMESTAMP`

The bundle-key used to store the timestamp of when a data log was first created.

`static final String`

`DATA_LOG_UUID`

A bundle-key used to store the UUID that uniquely identifies a data log.

`static final int`

`GOLF_BACK_KEY`

The Constant GOLF\_BACK\_KEY.

`static final int`

`GOLF_CMD_KEY`

The Constant GOLF\_CMD\_KEY.

`static final int`

`GOLF_CMD_NEXT`

Command sent by the golf-application to display the previous hole.

`static final int`

`GOLF_CMD_PREV`

Command sent by the golf-application to display the next hole.

`static final int`

`GOLF_FRONT_KEY`

The Constant GOLF\_FRONT\_KEY.

`static final int`

`GOLF_HOLE_KEY`

The Constant GOLF\_HOLE\_KEY.

`static final int`

`GOLF_MID_KEY`

The Constant GOLF\_MID\_KEY.

`static final int`

`GOLF_PAR_KEY`

The Constant GOLF\_PAR\_KEY.

`static final UUID`

`GOLF_UUID`

The UUID corresponding to Pebble's built-in "Golf" application.

`static final String`

`INTENT_APP_ACK`

Intent broadcast to pebble.apk to indicate that a message was received from the watch.

`static final String`

`INTENT_APP_CUSTOMIZE`

Intent broadcast to pebble.apk responsible for customizing the name and icon of the 'stock' Sports and Golf applications included in the watch's firmware.

`static final String`

`INTENT_APP_NACK`

Intent broadcast to pebble.apk to indicate that a message was unsuccessfully received from the watch.

`static final String`

`INTENT_APP_RECEIVE`

Intent broadcast from pebble.apk containing one-or-more key-value pairs sent from the watch to the phone.

`static final String`

`INTENT_APP_RECEIVE_ACK`

Intent broadcast from pebble.apk indicating that a sent message was successfully received by a watch app.

`static final String`

`INTENT_APP_RECEIVE_NACK`

Intent broadcast from pebble.apk indicating that a sent message was not received by a watch app.

`static final String`

`INTENT_APP_SEND`

Intent broadcast to pebble.apk containing one-or-more key-value pairs to be sent to the watch from the phone.

`static final String`

`INTENT_APP_START`

Intent broadcast to pebble.apk responsible for launching a watch-app on the connected watch.

`static final String`

`INTENT_APP_STOP`

Intent broadcast to pebble.apk responsible for closing a running watch-app on the connected watch.

`static final String`

`INTENT_DL_ACK_DATA`

Intent broadcast to pebble.apk implicitly when a unit of data from a data log is received.

`static final String`

`INTENT_DL_FINISH_SESSION`

Intent broadcast from pebble.apk indicating the session has finished.

`static final String`

`INTENT_DL_RECEIVE_DATA`

Intent broadcast from pebble.apk containing a unit of data from a data log.

`static final String`

`INTENT_DL_REQUEST_DATA`

Intent broadcast to pebble.apk to request data logs for a particular app.

`static final String`

`INTENT_PEBBLE_CONNECTED`

Intent broadcast by pebble.apk when a new connection to a Pebble is established.

`static final String`

`INTENT_PEBBLE_DISCONNECTED`

Intent broadcast by pebble.apk when the connection to a Pebble is closed or lost.

`static final int`

`KIT_STATE_COLUMN_APPMSG_SUPPORT`

&nbsp;

`static final int`

`KIT_STATE_COLUMN_CONNECTED`

&nbsp;

`static final int`

`KIT_STATE_COLUMN_DATALOGGING_SUPPORT`

&nbsp;

`static final int`

`KIT_STATE_COLUMN_VERSION_MAJOR`

&nbsp;

`static final int`

`KIT_STATE_COLUMN_VERSION_MINOR`

&nbsp;

`static final int`

`KIT_STATE_COLUMN_VERSION_POINT`

&nbsp;

`static final int`

`KIT_STATE_COLUMN_VERSION_TAG`

&nbsp;

`static final String`

`MSG_DATA`

The bundle-key used to store a message's JSON payload send-to or received-from the watch.

`static final String`

`PBL_DATA_ID`

A bundle-key used to store the ID of a unit of data in a data log.

`static final String`

`PBL_DATA_OBJECT`

A bundle-key used to store the value of the data unit.

`static final String`

`PBL_DATA_TYPE`

A bundle-key used to store the data type of the data unit.

`static final int`

`SPORTS_CUSTOM_LABEL_KEY`

The PebbleDictionary key corresponding to the custom label field sent to the Sports watch-app.

`static final int`

`SPORTS_CUSTOM_VALUE_KEY`

The PebbleDictionary key corresponding to the custom value sent to the Sports watch-app.

`static final int`

`SPORTS_DATA_KEY`

The PebbleDictionary key corresponding to the 'data' field sent to the Sports watch-app.

`static final int`

`SPORTS_DATA_PACE`

PebbleDictionary value corresponding to 'pace' data.

`static final int`

`SPORTS_DATA_SPEED`

PebbleDictionary value corresponding to 'speed' data.

`static final int`

`SPORTS_DISTANCE_KEY`

The PebbleDictionary key corresponding to the 'distance' field sent to the Sports watch-app.

`static final int`

`SPORTS_HR_BPM_KEY`

The PebbleDictionary key corresponding to the 'heart rate' field sent to the Sports watch-app.

`static final int`

`SPORTS_LABEL_KEY`

The PebbleDictionary key corresponding to the 'label' field sent to the Sports watch-app.

`static final int`

`SPORTS_STATE_END`

The Constant SPORTS\_STATE\_END.

`static final int`

`SPORTS_STATE_INIT`

The Constant SPORTS\_STATE\_INIT.

`static final int`

`SPORTS_STATE_KEY`

The PebbleDictionary key corresponding to the 'state' field sent to the Sports watch-app.

`static final int`

`SPORTS_STATE_PAUSED`

The Constant SPORTS\_STATE\_PAUSED.

`static final int`

`SPORTS_STATE_RUNNING`

The Constant SPORTS\_STATE\_RUNNING.

`static final int`

`SPORTS_TIME_KEY`

The PebbleDictionary key corresponding to the 'time' field sent to the Sports watch-app.

`static final int`

`SPORTS_UNITS_IMPERIAL`

PebbleDictionary value corresponding to 'imperial' units.

`static final int`

`SPORTS_UNITS_KEY`

The PebbleDictionary key corresponding to the 'units' field sent to the Sports watch-app.

`static final int`

`SPORTS_UNITS_METRIC`

PebbleDictionary value corresponding to 'metric' units.

`static final UUID`

`SPORTS_UUID`

The UUID corresponding to Pebble's built-in "Sports" application.

`static final String`

`TRANSACTION_ID`

The bundle-key used to store a message's transaction id.

- 
## Method Summary

### Methods inherited from class&nbsp;java.lang.[Object](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Object.html "class or interface in java.lang")
`clone, equals, finalize, getClass, hashCode, notify, notifyAll, toString, wait, wait, wait`

- 
## Field Details

  - 
### INTENT\_PEBBLE\_CONNECTED

public static final&nbsp;[String](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/String.html "class or interface in java.lang")&nbsp;INTENT\_PEBBLE\_CONNECTED

Intent broadcast by pebble.apk when a new connection to a Pebble is established.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.INTENT_PEBBLE_CONNECTED)
  - 
### INTENT\_PEBBLE\_DISCONNECTED

public static final&nbsp;[String](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/String.html "class or interface in java.lang")&nbsp;INTENT\_PEBBLE\_DISCONNECTED

Intent broadcast by pebble.apk when the connection to a Pebble is closed or lost.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.INTENT_PEBBLE_DISCONNECTED)
  - 
### INTENT\_APP\_ACK

public static final&nbsp;[String](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/String.html "class or interface in java.lang")&nbsp;INTENT\_APP\_ACK

Intent broadcast to pebble.apk to indicate that a message was received from the watch. To avoid protocol timeouts on the watch, applications _must_ ACK or NACK all received messages.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.INTENT_APP_ACK)
  - 
### INTENT\_APP\_NACK

public static final&nbsp;[String](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/String.html "class or interface in java.lang")&nbsp;INTENT\_APP\_NACK

Intent broadcast to pebble.apk to indicate that a message was unsuccessfully received from the watch.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.INTENT_APP_NACK)
  - 
### INTENT\_APP\_RECEIVE

public static final&nbsp;[String](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/String.html "class or interface in java.lang")&nbsp;INTENT\_APP\_RECEIVE

Intent broadcast from pebble.apk containing one-or-more key-value pairs sent from the watch to the phone.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.INTENT_APP_RECEIVE)
  - 
### INTENT\_APP\_RECEIVE\_ACK

public static final&nbsp;[String](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/String.html "class or interface in java.lang")&nbsp;INTENT\_APP\_RECEIVE\_ACK

Intent broadcast from pebble.apk indicating that a sent message was successfully received by a watch app.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.INTENT_APP_RECEIVE_ACK)
  - 
### INTENT\_APP\_RECEIVE\_NACK

public static final&nbsp;[String](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/String.html "class or interface in java.lang")&nbsp;INTENT\_APP\_RECEIVE\_NACK

Intent broadcast from pebble.apk indicating that a sent message was not received by a watch app.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.INTENT_APP_RECEIVE_NACK)
  - 
### INTENT\_APP\_SEND

public static final&nbsp;[String](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/String.html "class or interface in java.lang")&nbsp;INTENT\_APP\_SEND

Intent broadcast to pebble.apk containing one-or-more key-value pairs to be sent to the watch from the phone.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.INTENT_APP_SEND)
  - 
### INTENT\_APP\_START

public static final&nbsp;[String](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/String.html "class or interface in java.lang")&nbsp;INTENT\_APP\_START

Intent broadcast to pebble.apk responsible for launching a watch-app on the connected watch. This intent is idempotent.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.INTENT_APP_START)
  - 
### INTENT\_APP\_STOP

public static final&nbsp;[String](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/String.html "class or interface in java.lang")&nbsp;INTENT\_APP\_STOP

Intent broadcast to pebble.apk responsible for closing a running watch-app on the connected watch. This intent is idempotent.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.INTENT_APP_STOP)
  - 
### INTENT\_APP\_CUSTOMIZE

public static final&nbsp;[String](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/String.html "class or interface in java.lang")&nbsp;INTENT\_APP\_CUSTOMIZE

Intent broadcast to pebble.apk responsible for customizing the name and icon of the 'stock' Sports and Golf applications included in the watch's firmware.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.INTENT_APP_CUSTOMIZE)
  - 
### INTENT\_DL\_RECEIVE\_DATA

public static final&nbsp;[String](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/String.html "class or interface in java.lang")&nbsp;INTENT\_DL\_RECEIVE\_DATA

Intent broadcast from pebble.apk containing a unit of data from a data log.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.INTENT_DL_RECEIVE_DATA)
  - 
### INTENT\_DL\_ACK\_DATA

public static final&nbsp;[String](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/String.html "class or interface in java.lang")&nbsp;INTENT\_DL\_ACK\_DATA

Intent broadcast to pebble.apk implicitly when a unit of data from a data log is received.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.INTENT_DL_ACK_DATA)
  - 
### INTENT\_DL\_REQUEST\_DATA

public static final&nbsp;[String](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/String.html "class or interface in java.lang")&nbsp;INTENT\_DL\_REQUEST\_DATA

Intent broadcast to pebble.apk to request data logs for a particular app.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.INTENT_DL_REQUEST_DATA)
  - 
### INTENT\_DL\_FINISH\_SESSION

public static final&nbsp;[String](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/String.html "class or interface in java.lang")&nbsp;INTENT\_DL\_FINISH\_SESSION

Intent broadcast from pebble.apk indicating the session has finished.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.INTENT_DL_FINISH_SESSION)
  - 
### SPORTS\_UUID

public static final&nbsp;[UUID](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/UUID.html "class or interface in java.util")&nbsp;SPORTS\_UUID

The UUID corresponding to Pebble's built-in "Sports" application.
  - 
### GOLF\_UUID

public static final&nbsp;[UUID](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/UUID.html "class or interface in java.util")&nbsp;GOLF\_UUID

The UUID corresponding to Pebble's built-in "Golf" application.
  - 
### TRANSACTION\_ID

public static final&nbsp;[String](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/String.html "class or interface in java.lang")&nbsp;TRANSACTION\_ID

The bundle-key used to store a message's transaction id.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.TRANSACTION_ID)
  - 
### APP\_UUID

public static final&nbsp;[String](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/String.html "class or interface in java.lang")&nbsp;APP\_UUID

The bundle-key used to store a message's UUID.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.APP_UUID)
  - 
### MSG\_DATA

public static final&nbsp;[String](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/String.html "class or interface in java.lang")&nbsp;MSG\_DATA

The bundle-key used to store a message's JSON payload send-to or received-from the watch.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.MSG_DATA)
  - 
### CUST\_APP\_TYPE

public static final&nbsp;[String](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/String.html "class or interface in java.lang")&nbsp;CUST\_APP\_TYPE

The bundle-key used to store the type of application being customized in a CUSTOMIZE intent.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.CUST_APP_TYPE)
  - 
### CUST\_NAME

public static final&nbsp;[String](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/String.html "class or interface in java.lang")&nbsp;CUST\_NAME

The bundle-key used to store the custom name provided in a CUSTOMIZE intent.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.CUST_NAME)
  - 
### CUST\_ICON

public static final&nbsp;[String](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/String.html "class or interface in java.lang")&nbsp;CUST\_ICON

The bundle-key used to store the custom icon provided in a CUSTOMIZE intent.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.CUST_ICON)
  - 
### DATA\_LOG\_TIMESTAMP

public static final&nbsp;[String](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/String.html "class or interface in java.lang")&nbsp;DATA\_LOG\_TIMESTAMP

The bundle-key used to store the timestamp of when a data log was first created.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.DATA_LOG_TIMESTAMP)
  - 
### DATA\_LOG\_UUID

public static final&nbsp;[String](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/String.html "class or interface in java.lang")&nbsp;DATA\_LOG\_UUID

A bundle-key used to store the UUID that uniquely identifies a data log.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.DATA_LOG_UUID)
  - 
### DATA\_LOG\_TAG

public static final&nbsp;[String](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/String.html "class or interface in java.lang")&nbsp;DATA\_LOG\_TAG

A bundle-key used to store the tag for the corresponding data log.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.DATA_LOG_TAG)
  - 
### PBL\_DATA\_ID

public static final&nbsp;[String](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/String.html "class or interface in java.lang")&nbsp;PBL\_DATA\_ID

A bundle-key used to store the ID of a unit of data in a data log.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.PBL_DATA_ID)
  - 
### PBL\_DATA\_TYPE

public static final&nbsp;[String](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/String.html "class or interface in java.lang")&nbsp;PBL\_DATA\_TYPE

A bundle-key used to store the data type of the data unit.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.PBL_DATA_TYPE)
  - 
### PBL\_DATA\_OBJECT

public static final&nbsp;[String](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/String.html "class or interface in java.lang")&nbsp;PBL\_DATA\_OBJECT

A bundle-key used to store the value of the data unit.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.PBL_DATA_OBJECT)
  - 
### SPORTS\_TIME\_KEY

public static final&nbsp;int&nbsp;SPORTS\_TIME\_KEY

The PebbleDictionary key corresponding to the 'time' field sent to the Sports watch-app.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.SPORTS_TIME_KEY)
  - 
### SPORTS\_DISTANCE\_KEY

public static final&nbsp;int&nbsp;SPORTS\_DISTANCE\_KEY

The PebbleDictionary key corresponding to the 'distance' field sent to the Sports watch-app.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.SPORTS_DISTANCE_KEY)
  - 
### SPORTS\_DATA\_KEY

public static final&nbsp;int&nbsp;SPORTS\_DATA\_KEY

The PebbleDictionary key corresponding to the 'data' field sent to the Sports watch-app. The data field is paired with the label specified by SPORTS\_LABEL\_KEY and can be used to display speed or pace data.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.SPORTS_DATA_KEY)
  - 
### SPORTS\_UNITS\_KEY

public static final&nbsp;int&nbsp;SPORTS\_UNITS\_KEY

The PebbleDictionary key corresponding to the 'units' field sent to the Sports watch-app.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.SPORTS_UNITS_KEY)
  - 
### SPORTS\_STATE\_KEY

public static final&nbsp;int&nbsp;SPORTS\_STATE\_KEY

The PebbleDictionary key corresponding to the 'state' field sent to the Sports watch-app. Both the watch and phone-app may modify this field. The phone-application is responsible for performing any required state transitions to stay in sync with the watch-app's state.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.SPORTS_STATE_KEY)
  - 
### SPORTS\_LABEL\_KEY

public static final&nbsp;int&nbsp;SPORTS\_LABEL\_KEY

The PebbleDictionary key corresponding to the 'label' field sent to the Sports watch-app. The label field controls the label above the 'data' field.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.SPORTS_LABEL_KEY)
  - 
### SPORTS\_HR\_BPM\_KEY

public static final&nbsp;int&nbsp;SPORTS\_HR\_BPM\_KEY

The PebbleDictionary key corresponding to the 'heart rate' field sent to the Sports watch-app. The heart rate field controls the data displayed in the scrollable field containing heart rate bpm.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.SPORTS_HR_BPM_KEY)
  - 
### SPORTS\_CUSTOM\_LABEL\_KEY

public static final&nbsp;int&nbsp;SPORTS\_CUSTOM\_LABEL\_KEY

The PebbleDictionary key corresponding to the custom label field sent to the Sports watch-app. This label field controls the label above the custom value field.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.SPORTS_CUSTOM_LABEL_KEY)
  - 
### SPORTS\_CUSTOM\_VALUE\_KEY

public static final&nbsp;int&nbsp;SPORTS\_CUSTOM\_VALUE\_KEY

The PebbleDictionary key corresponding to the custom value sent to the Sports watch-app. The custom value field controls the data displayed in the scrollable field containing custom data.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.SPORTS_CUSTOM_VALUE_KEY)
  - 
### SPORTS\_UNITS\_IMPERIAL

public static final&nbsp;int&nbsp;SPORTS\_UNITS\_IMPERIAL

PebbleDictionary value corresponding to 'imperial' units.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.SPORTS_UNITS_IMPERIAL)
  - 
### SPORTS\_UNITS\_METRIC

public static final&nbsp;int&nbsp;SPORTS\_UNITS\_METRIC

PebbleDictionary value corresponding to 'metric' units.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.SPORTS_UNITS_METRIC)
  - 
### SPORTS\_DATA\_SPEED

public static final&nbsp;int&nbsp;SPORTS\_DATA\_SPEED

PebbleDictionary value corresponding to 'speed' data.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.SPORTS_DATA_SPEED)
  - 
### SPORTS\_DATA\_PACE

public static final&nbsp;int&nbsp;SPORTS\_DATA\_PACE

PebbleDictionary value corresponding to 'pace' data.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.SPORTS_DATA_PACE)
  - 
### SPORTS\_STATE\_INIT

public static final&nbsp;int&nbsp;SPORTS\_STATE\_INIT

The Constant SPORTS\_STATE\_INIT.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.SPORTS_STATE_INIT)
  - 
### SPORTS\_STATE\_RUNNING

public static final&nbsp;int&nbsp;SPORTS\_STATE\_RUNNING

The Constant SPORTS\_STATE\_RUNNING.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.SPORTS_STATE_RUNNING)
  - 
### SPORTS\_STATE\_PAUSED

public static final&nbsp;int&nbsp;SPORTS\_STATE\_PAUSED

The Constant SPORTS\_STATE\_PAUSED.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.SPORTS_STATE_PAUSED)
  - 
### SPORTS\_STATE\_END

public static final&nbsp;int&nbsp;SPORTS\_STATE\_END

The Constant SPORTS\_STATE\_END.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.SPORTS_STATE_END)
  - 
### GOLF\_FRONT\_KEY

public static final&nbsp;int&nbsp;GOLF\_FRONT\_KEY

The Constant GOLF\_FRONT\_KEY.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.GOLF_FRONT_KEY)
  - 
### GOLF\_MID\_KEY

public static final&nbsp;int&nbsp;GOLF\_MID\_KEY

The Constant GOLF\_MID\_KEY.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.GOLF_MID_KEY)
  - 
### GOLF\_BACK\_KEY

public static final&nbsp;int&nbsp;GOLF\_BACK\_KEY

The Constant GOLF\_BACK\_KEY.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.GOLF_BACK_KEY)
  - 
### GOLF\_HOLE\_KEY

public static final&nbsp;int&nbsp;GOLF\_HOLE\_KEY

The Constant GOLF\_HOLE\_KEY.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.GOLF_HOLE_KEY)
  - 
### GOLF\_PAR\_KEY

public static final&nbsp;int&nbsp;GOLF\_PAR\_KEY

The Constant GOLF\_PAR\_KEY.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.GOLF_PAR_KEY)
  - 
### GOLF\_CMD\_KEY

public static final&nbsp;int&nbsp;GOLF\_CMD\_KEY

The Constant GOLF\_CMD\_KEY.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.GOLF_CMD_KEY)
  - 
### GOLF\_CMD\_PREV

public static final&nbsp;int&nbsp;GOLF\_CMD\_PREV

Command sent by the golf-application to display the next hole.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.GOLF_CMD_PREV)
  - 
### GOLF\_CMD\_NEXT

public static final&nbsp;int&nbsp;GOLF\_CMD\_NEXT

Command sent by the golf-application to display the previous hole.
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.GOLF_CMD_NEXT)
  - 
### KIT\_STATE\_COLUMN\_CONNECTED

public static final&nbsp;int&nbsp;KIT\_STATE\_COLUMN\_CONNECTED
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.KIT_STATE_COLUMN_CONNECTED)
  - 
### KIT\_STATE\_COLUMN\_APPMSG\_SUPPORT

public static final&nbsp;int&nbsp;KIT\_STATE\_COLUMN\_APPMSG\_SUPPORT
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.KIT_STATE_COLUMN_APPMSG_SUPPORT)
  - 
### KIT\_STATE\_COLUMN\_DATALOGGING\_SUPPORT

public static final&nbsp;int&nbsp;KIT\_STATE\_COLUMN\_DATALOGGING\_SUPPORT
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.KIT_STATE_COLUMN_DATALOGGING_SUPPORT)
  - 
### KIT\_STATE\_COLUMN\_VERSION\_MAJOR

public static final&nbsp;int&nbsp;KIT\_STATE\_COLUMN\_VERSION\_MAJOR
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.KIT_STATE_COLUMN_VERSION_MAJOR)
  - 
### KIT\_STATE\_COLUMN\_VERSION\_MINOR

public static final&nbsp;int&nbsp;KIT\_STATE\_COLUMN\_VERSION\_MINOR
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.KIT_STATE_COLUMN_VERSION_MINOR)
  - 
### KIT\_STATE\_COLUMN\_VERSION\_POINT

public static final&nbsp;int&nbsp;KIT\_STATE\_COLUMN\_VERSION\_POINT
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.KIT_STATE_COLUMN_VERSION_POINT)
  - 
### KIT\_STATE\_COLUMN\_VERSION\_TAG

public static final&nbsp;int&nbsp;KIT\_STATE\_COLUMN\_VERSION\_TAG
See Also:
    - [Constant Field Values](/docs/pebblekit-android/constant-values/#com.getpebble.android.kit.Constants.KIT_STATE_COLUMN_VERSION_TAG)
