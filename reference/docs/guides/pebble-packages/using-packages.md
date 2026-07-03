# Using Pebble Packages

Source: https://developer.repebble.com/guides/pebble-packages/using-packages/

## Getting started

Using pebble packages is easy:

1. Find a package. We will have a searchable listing soon, but for now you can [browse the pebble-package keyword on npm](https://www.npmjs.com/browse/keyword/pebble-package).
2. Run `pebble package install pebble-somelib` to install pebble-somelib.
3. Use the package.

It is possible to use _some_ standard npm packages. However, packages that depend on being run in node, or in a real web browser, are likely to fail. If you install an npm package, you can use it in the usual manner, as described below.

### C code

Packages should document their specific usage. However, in general, for C packages you can include their headers and call them like so:

```
#include \<pebble-somelib/somelib.h\>int main() {somelib\_do\_the\_thing();}
```

All of the package's include files will be in a folder named after the package. Packages may have any structure inside that folder, so you are advised to read their documentation.

**Notice**  

**Tip** : If you want to use an[`Event Service`](/docs/c/Foundation/Event_Service/ "Event Service"), you should use the[pebble-events](https://www.npmjs.com/package/pebble-events) package to avoid conflicting with handlers registered by packages.

### JavaScript code

JavaScript packages are used via the `require` function. In most cases you can just `require` the package by name:

```
var somelib = require('pebble-somelib');somelib.doTheThing();
```

### Resources

If the package you are using has included image resources, you can reference them directly using their `RESOURCE_ID_*` identifiers.

```
static GBitmap \*s\_image\_01;s\_image\_01 = gbitmap\_create\_with\_resource(RESOURCE\_ID\_MEDIA\_PACKAGE\_IMAGE\_01\_TINY);
```

### Published Media

If the package you are using has defined `publishedMedia` resources, you can either reference the resources using their resource identifier (as above), or you can create an alias within the `package.json`. The `name` you specify in your own project can be used to reference that `publishedMedia` item for AppGlances and Timeline pins, eg. `PUBLISHED_ID_<name>`

For example, if the package exposes the following `publishedMedia`:

```
"resources": {//..."publishedMedia": [{"name": "MEDIA\_PACKAGE\_IMAGE\_01","glance": "MEDIA\_PACKAGE\_IMAGE\_01\_TINY","timeline": {"tiny": "MEDIA\_PACKAGE\_IMAGE\_01\_TINY","small": "MEDIA\_PACKAGE\_IMAGE\_01\_SMALL","large": "MEDIA\_PACKAGE\_IMAGE\_01\_LARGE"}}]}
```

You could define the following `name` and `alias` with a unique `id` in your`package.json`:

```
"resources": {//..."publishedMedia": [{"name": "SHARED\_IMAGE\_01","id": 1,"alias": "MEDIA\_PACKAGE\_IMAGE\_01"}]}
```

You can then proceed to use that `name`, prefixed with `PUBLISHED_ID_`, within your code:

```
const AppGlanceSlice entry = (AppGlanceSlice) {.layout = {.icon = PUBLISHED\_ID\_SHARED\_IMAGE\_01,.subtitle\_template\_string = "message"}};
```
