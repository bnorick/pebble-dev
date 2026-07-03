# Preferences

Source: https://developer.repebble.com/docs/c/User_Interface/Preferences/index.html

Values recommended by the system

## Function Documentation

[uint32\_t](/docs/c/Standard_C/#uint32_t) preferred\_result\_display\_duration(void)

Get the recommended amount of milliseconds a result window should be visible before it should automatically close.

##### Note

It is the application developer's responsibility to automatically close a result window.

#### Returns

The recommended result window timeout duration in milliseconds

[PreferredContentSize](/docs/c/User_Interface/Preferences/#PreferredContentSize) preferred\_content\_size(void)

Returns the user's preferred content size representing the scale of all the app's UI components should use for display.

#### Returns

The user's [PreferredContentSize](/docs/c/User_Interface/Preferences/#PreferredContentSize) setting.

bool quiet\_time\_is\_active(void)

Users can toggle Quiet Time manually or on schedule. Watchfaces and apps should respect this choice and avoid disturbing actions such as vibration if quiet time is active.

#### Returns

True, if Quiet Time is currently active.

## Enum Documentation

enum PreferredContentSize

[PreferredContentSize](/docs/c/User_Interface/Preferences/#PreferredContentSize) represents the display scale of all the app's UI components. The enum contains all sizes that all platforms as a whole are capable of displaying, but each individual platform may not be able to display all sizes.

As of version 4.1, platforms other than Emery cannot display extra large and Emery itself cannot display small.

#### Enumerators
PreferredContentSizeSmallPreferredContentSizeMediumPreferredContentSizeLargePreferredContentSizeExtraLargeNumPreferredContentSizes
