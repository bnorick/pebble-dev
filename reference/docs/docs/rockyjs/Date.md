# Date

Source: https://developer.repebble.com/docs/rockyjs/Date/

Creates a JavaScript Date instance that represents a single moment in time. Date objects are based on a time value that is the number of milliseconds since 1 January, 1970 UTC.

`var d = new Date();`

We fully implement standard JavaScript `Date` functions, such as: `getDay()`, `getHours()` etc.

For full `Date` documentation see: [https://developer.mozilla.org/en/docs/Web/JavaScript/Reference/Global\_Objects/Date](https://developer.mozilla.org/en/docs/Web/JavaScript/Reference/Global_Objects/Date)

### 

Locale Date Methods

The locale date methods ([toLocaleString](#toLocaleString), [toLocaleTimeString](#toLocaleTimeString) and [toLocaleDateString](#toLocaleDateString)) are currently limited in their initial implementation.

Available **options** :

**hour12**

Use 12-hour time (as opposed to 24-hour time). Possible values are `true` and `false`; the default is locale dependent (Pebble setting).

**weekday**

The representation of the weekday. Possible values are "narrow", "short", "long".

**year**

The representation of the year. Possible values are "numeric", "2-digit".

**month**

The representation of the month. Possible values are "numeric", "2-digit", "narrow", "short", "long".

**day**

The representation of the day. Possible values are "numeric", "2-digit".

**hour**

The representation of the hour. Possible values are "numeric", "2-digit".

**minute**

The representation of the minute. Possible values are "numeric", "2-digit".

**second**

The representation of the second. Possible values are "numeric", "2-digit".

Please note that locale based date and time functions have the following limitations at this time:

- You cannot manually specify a locale, it's automatically based upon the current device settings. Locale is optional, or you can specify `undefined`.

- Only a single date/time value can be requested in each method call. Do NOT request multiple options. e.g. `{hour: 'numeric', minute: '2-digit'}`

### Methods

 Date.toLocaleString(locale, options) 

This method returns a string with a language sensitive representation of this date object.

`d.toLocaleString();`

#### Parameters
String locale

(Optional) The name of the locale.

Object options

(Optional) Only a single option is currently supported.

 Date.toLocaleTimeString(locale, options) 

This method returns a string with a language sensitive representationof the date portion of this date object.

`d.toLocaleTimeString(undefined, {hour: 'numeric'});`

#### Parameters
String locale

(Optional) The name of the locale.

Object options

(Optional) Only a single option is currently supported.

 Date.toLocaleDateString(locale, options) 

This method returns a string with a language sensitive representationof the time portion of this date object.

`d.toLocaleDateString(undefined, {weekday: 'long'});`

#### Parameters
String locale

(Optional) The name of the locale.

Object options

(Optional) Only a single option is currently supported.
