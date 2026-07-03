# Converting SVG to PDC

Source: https://developer.repebble.com/guides/app-resources/converting-svg-to-pdc/

[Pebble Draw Commands](/docs/c/Graphics/Draw_Commands/ "Draw Commands") (PDC) are a powerful method of creating vector images and icons that can be transformed and manipulated at runtime. These can be used as a low-cost alternative to APNGs or bitmap sequences. Currently the only simple way to create PDC files is to use the[`svg2pdc.py`](https://github.com/pebble-examples/cards-example/blob/master/tools/svg2pdc.py)tool. However, as noted in[_Vector Animations_](/tutorials/advanced/vector-animations.md#creating-compatible-files)there are a some limitations to the nature of the input SVG file:

> The `svg2pdc` tool currently supports SVG files that use **only** the following elements: `g`, `layer`, `path`, `rect`, `polyline`, `polygon`,`line`, `circle`.

Fortunately, steps can be taken when creating SVG files in popular graphics packages to avoid these limitations and ensure the output file is compatible with `svg2pdc.py`. In this guide, we will be creating compatible PDC files using an example SVG - this[pencil icon](https://upload.wikimedia.org/wikipedia/commons/a/ac/Black_pencil.svg).

![pencil icon](/assets/images/guides/pebble-apps/resources/pencil.svg)

## Using Inkscape

- First, open the SVG in [Inkscape](https://inkscape.org/en/):

![inkscape-open](/assets/images/guides/pebble-apps/resources/inkscape-open.png)

- Resize the viewport with _File_, _Document Properties_,_Page_, _Resize Page to Drawing_:

![inkscape-resize-page](/assets/images/guides/pebble-apps/resources/inkscape-resize-page.png)

- Select the layer, then resize the image to fit Pebble (50 x 50 pixels in this example) with _Object_, _Transform_:

![inkscape-resize-pebble](/assets/images/guides/pebble-apps/resources/inkscape-resize-pebble.png)

- Now that the image has been resized, shrink the viewport again with _File_,_Document Properties_, _Page_, _Resize Page to Drawing_:

- Remove groupings with _Edit_, _Select All_, then _Object_, _Ungroup_ until no groups remain:

![inkscape-ungroup](/assets/images/guides/pebble-apps/resources/inkscape-ungroup.png)

- Disable relative move in _Object_, _Transform_. Hit _Apply_:

![inkscape-relative](/assets/images/guides/pebble-apps/resources/inkscape-relative.png)

- Finally, save the image as a 'Plain SVG':

![inkscape-plain](/assets/images/guides/pebble-apps/resources/inkscape-plain.png)

## Using Illustrator

- First, open the SVG in Illustrator:

![illustrator-open](/assets/images/guides/pebble-apps/resources/illustrator-open.png)

- Resize the image to fit Pebble (50 x 50 pixels in this example) by entering in the desired values in the 'W' and 'H' fields of the _Transform_ panel:

![illustrator-resize](/assets/images/guides/pebble-apps/resources/illustrator-resize.png)

- Ungroup all items with _Select_, _All_, followed by _Object_, _Ungroup_ until no groups remain:

![illustrator-ungroup](/assets/images/guides/pebble-apps/resources/illustrator-ungroup.png)

- Shrink the image bounds with _Object_, _Artboards_, _Fit to Selected Art_:

![illustrator-fit](/assets/images/guides/pebble-apps/resources/illustrator-fit.png)

- Save the SVG using _File_, _Save As_ with the _SVG Tiny 1.1_ profile and 1 decimal places:

![illustrator-settings](/assets/images/guides/pebble-apps/resources/illustrator-settings.png)

## Using the PDC Files

Once the compatible SVG files have been created, it's time to use `svg2pdc.py`to convert into PDC resources, which will contain all the vector information needed to draw the image in the correct Pebble binary format. The command is shown below, with the Inkscape output SVG used as an example:

```
$ python svg2pdc.py pencil-inkscape.svg# Use python 2.x!
```

> If a coordinate value's precision value isn't supported, a warning will be printed and the nearest compatible value will be used instead:
> 
> ```
> Invalid point: (9.4, 44.5). Closest supported coordinate: (9.5, 44.5)
> ```

To use the PDC file in a Pebble project, read[_Drawing a PDC Image_](/tutorials/advanced/vector-animations.md#drawing-a-pdc-image). The result should look near-identical on Pebble:

![svg-output](/assets/images/guides/pebble-apps/resources/svg-output.png)

## Example Output

For reference, compatible output files are listed below:

- Inkscape: [SVG](/assets/other/pdc/pencil-inkscape.svg) | [PDC](/assets/other/pdc/pencil-inkscape.pdc)

- Illustrator: [SVG](/assets/other/pdc/pencil-illustrator.svg) | [PDC](/assets/other/pdc/pencil-illustrator.pdc)
