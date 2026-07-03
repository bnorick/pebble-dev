# App Resources

Source: https://developer.repebble.com/guides/app-resources/

The Pebble SDK allows apps to include extra files as app resources. These files can include images, animated images, vector images, custom fonts, and raw data files. These resources are stored in flash memory and loaded when required by the SDK. Apps that use a large number of resources should consider only keeping in memory those that are immediately required.

**Notice**  

The maximum number of resources an app can include is **256**. In addition, the maximum size of all resources bundled into a built app is **128 kB** on the Aplite platform, and **256 kB** on the Basalt and Chalk platforms. These limits include resources used by included Pebble Packages.

App resources are included in a project by being listed in the `media` property of `package.json`, and are converted into suitable firmware-compatible formats at build time. Examples of this are shown in each type of resource's respective guide.

## Contents

- [**Animated Images**](/guides/app-resources/animated-images.md) - How to add animated image resources to a project in the APNG format, and display them in your app.

- [**App Assets**](/guides/app-resources/app-assets.md) - A collection of assets for use as resources in Pebble apps.

- [**Converting SVG to PDC**](/guides/app-resources/converting-svg-to-pdc.md) - How to create compatible SVG files using Inkscape and Illustrator.

- [**Fonts**](/guides/app-resources/fonts.md) - How to use built-in system fonts, or add your own font resources to a project.

- [**Images**](/guides/app-resources/images.md) - How to add image resources to a project and display them in your app.

- [**Pebble Draw Command File Format**](/guides/app-resources/pdc-format.md) - The binary file format description for Pebble Draw Command Frames, Images and Sequences.

- [**Platform-specific Resources**](/guides/app-resources/platform-specific.md) - How to include different resources for different platforms, as well as how to include a resource only on a particular platform.

- [**Raw Data Files**](/guides/app-resources/raw-data-files.md) - How to add raw data resources to a project and read them in your app.

- [**System Fonts**](/guides/app-resources/system-fonts.md) - A complete list of all the system fonts available for use in Pebble projects.
