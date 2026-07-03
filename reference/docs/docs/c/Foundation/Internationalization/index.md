# Internationalization

Source: https://developer.repebble.com/docs/c/Foundation/Internationalization/index.html

Internationalization & Localization APIs

## Function Documentation

const char \* i18n\_get\_system\_locale(void)

Get the ISO locale name for the language currently set on the watch.

##### Note

It is possible for the locale to change while your app is running. And thus, two calls to i18n\_get\_system\_locale may return different values.

#### Returns

A string containing the ISO locale name (e.g. "fr", "en\_US", ...)
