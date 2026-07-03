# Effect Layer

Source: https://developer.repebble.com/community/libraries/effect-layer/

EffectLayer is a visual effect layer for Pebble Smartwatch. User places the layer over screen at set coordinates and special effects are applied to that area of the screen. Effects work both on Aplite/Classic Pebble and Basalt/Pebble time unless specified (e.g. Blur works only on Basalt)

To use the library place the source files in your SRC directory and add #include "effect\_layer.h" to your source. EffectLayer library is implemented in efficient pay-to-play way so only effects that you actually use get compiled into your binary.

Currently supported effects:

- Invert
- Invert b/w only
- Invert brightness, preserve hue
- Vertical Mirror
- Horizontal Mirror
- Rotate 90 degrees (counter- or clock-wise)
- Blur
- Zoom
- Lens
- Mask
- FPS
- Shadow
- Outline
- effect\_colorize
- effect\_colorswap

![Inverter](http://i.imgur.com/6t9r3qa.gif "Inverter") ![Bitmap Mask](http://i.imgur.com/JspSsx1.gif "Bitmap Mask") ![Text Mask](http://i.imgur.com/EdKu49w.png "Text Mask")
