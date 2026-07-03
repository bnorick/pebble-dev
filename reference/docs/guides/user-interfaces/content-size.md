# Content Size

Source: https://developer.repebble.com/guides/user-interfaces/content-size/

**Notice**  

The ContentSize API is currently only available in SDK 4.2-BETA.

The [ContentSize](/docs/c/preview/User_Interface/Preferences/#preferred_content_size)API, added in SDK 4.2, allows developers to dynamically adapt their watchface and watchapp design based upon the system `Text Size`preference (_Settings \> Notifications \> Text Size_).

While this allows developers to create highly accessible designs, it also serves to provide a mechanism for creating designs which are less focused upon screen size, and more focused upon content size.

![ContentSize](/assets/images/guides/content-size/anim.gif)

The `Text Size` setting displays the following options on all platforms:

- Small
- Medium
- Large

Whereas, the[ContentSize](/docs/c/preview/User_Interface/Preferences/#preferred_content_size)API will return different content sizes based on the `Text Size` setting, varying by platform. The list of content sizes is:

- Small
- Medium
- Large
- Extra Large

An example of the varying content sizes:

- `Text Size`: `small` on `Basalt` is `ContentSize`: `small`
- `Text Size`: `small` on `Emery` is `ContentSize`: `medium`

The following table describes the relationship between `Text Size`, `Platform`and `ContentSize`:

| Platform | Text Size: Small | Text Size: Medium | Text Size: Large |
| --- | --- | --- | --- |
| Aplite, Basalt, Chalk, Diorite, Flint | ContentSize: Small | ContentSize: Medium | ContentSize: Large |
| Emery | ContentSize: Medium | ContentSize: Large | ContentSize: Extra Large |

> _At present the Text Size setting only affects notifications and some system UI components, but other system UI components will be updated to support ContentSize in future versions._

We highly recommend that developers begin to build and update their applications with consideration for[ContentSize](/docs/c/preview/User_Interface/Preferences/#preferred_content_size) to provide the best experience to users.

## Detecting ContentSize

In order to detect the current[ContentSize](/docs/c/preview/User_Interface/Preferences/#preferred_content_size) developers can use the[`preferred_content_size()`](/docs/c/User_Interface/Preferences/#preferred_content_size "preferred\_content\_size") function.

The [ContentSize](/docs/c/preview/User_Interface/Preferences/#preferred_content_size)will never change during runtime, so it's perfectly acceptable to check this once during `init()`.

```
static PreferredContentSize s\_content\_size;void init() {s\_content\_size = preferred\_content\_size();// ...}
```

## Adapting Layouts

There are a number of different approaches to adapting the screen layout based upon content size. You could change font sizes, show or hide design elements, or even present an entirely different UI.

In the following example, we will change font sizes based on the[ContentSize](/docs/c/preview/User_Interface/Preferences/#preferred_content_size)

```
static TextLayer \*s\_text\_layer;static PreferredContentSize s\_content\_size;void init() {s\_content\_size = preferred\_content\_size();// ...switch (s\_content\_size) {case PreferredContentSizeMedium:// Use a medium fonttext\_layer\_set\_font(s\_text\_layer, fonts\_get\_system\_font(FONT\_KEY\_GOTHIC\_18\_BOLD));break;case PreferredContentSizeLarge:case PreferredContentSizeExtraLarge:// Use a large fonttext\_layer\_set\_font(s\_text\_layer, fonts\_get\_system\_font(FONT\_KEY\_GOTHIC\_28\_BOLD));break;default:// Use a small fonttext\_layer\_set\_font(s\_text\_layer, fonts\_get\_system\_font(FONT\_KEY\_GOTHIC\_14\_BOLD));break;}// ...}
```

## Additional Considerations

When developing an application which dynamically adjusts based on the[ContentSize](/docs/c/preview/User_Interface/Preferences/#preferred_content_size)setting, try to avoid using fixed widths and heights. Calculate coordinates and dimensions based upon the size of the root layer,[`UnobstructedArea`](/docs/c/User_Interface/UnobstructedArea/ "UnobstructedArea") and[ContentSize](/docs/c/preview/User_Interface/Preferences/#preferred_content_size)
