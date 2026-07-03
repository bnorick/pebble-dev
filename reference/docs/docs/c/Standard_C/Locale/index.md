# Locale

Source: https://developer.repebble.com/docs/c/Standard_C/Locale/index.html

Standard locale functions.

## Function Documentation

char \* setlocale(int category, char \* locale)

Set the app's locale for a category of routines.

`setlocale` can be used to:

- set the app's locale to a specific locale: `setlocale(LC_ALL, "en_CA")`

- set the app's locale to the system locale: `setlocale(LC_ALL, "")`

- get the app's curent locale: `setlocale(LC_ALL, NULL)`

##### Note

Currently, we only support two categories: LC\_ALL and LC\_TIME

#### Parameters
 category

The category of routines for which to set the locale

 locale

The ISO formatted locale to use, or "" for the system locale

#### Returns

the locale after the change is applied, NULL on failure (e.g. unsuported category)
