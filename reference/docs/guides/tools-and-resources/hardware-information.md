# Hardware Information

Source: https://developer.repebble.com/guides/tools-and-resources/hardware-information/

The Pebble watch family comprises of multiple generations of hardware, each with unique sets of features and capabilities. Developers wishing to reach the maximum number of users will want to account for these differences when developing their apps.

The table below details the differences between hardware platforms:

| Company | Pebble Technology Corporation | Core Devices |
| --- | --- | --- |
| Model | Classic,  
Steel | Time,  
Time Steel | Time Round | Pebble 2 | Pebble 2 Duo | Pebble Time 2\* | Pebble Round 2 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| Platform | Aplite | Basalt | Chalk | Diorite | Flint | Emery | Gabbro |
| SOC | [STMicro STM32F205RE](https://www.st.com/en/microcontrollers-microprocessors/stm32f205re.html) | [STMicro STM32F411](https://www.st.com/en/microcontrollers-microprocessors/stm32f411.html) | [Nordic nRF52840](https://www.nordicsemi.com/Products/nRF52840) | [SiFli SF32LB52J](https://www.sifli.com/en/node/31) |
| CPU | Cortex-M3  
64 MHz | Cortex-M4  
100 MHz | Cortex-M4  
64 MHz | [Star-MC1](https://www.armchina.com/mountain?infoId=160&name=%22%E6%98%9F%E8%BE%B0%22%20STAR-MC1&CategoryStr=%22%E6%98%9F%E8%BE%B0%22&pStatus=)  
(Cortex-M33-like)  
240 MHz |
| Max Resource Size | 96k | 256k |
| Max App Size (code + heap) | 24k | 64k | 128k |
| Display Shape | Rectangle | Round | Rectangle | Round |
| Display Size | 1.26" | 1.25" | 1" | 1.26" | 1.5" | 1.3" |
| Display Resolution | 144 x 168 | 180 x 180 | 144 x 168 | 200 x 228 | 260 x 260 |
| Display PPI | 175 | 182 | 175 | 202 | 200 |
| Display Colors | 2  
_(B/W)_ | 64  
_(Color)_ | 2  
_(B/W)_ | 64  
_(Color)_ |
| Touch Screen | No | Yes |
| Backlight | White LED | Multicolor  
RGB LED | White LED |
| Heart Rate Monitor | No | No  
_(possible with smartstrap)_ | Yes  
_(except SE model)_ | No | Yes | No |
| Microphone | No | Yes | Yes  
_(with 2nd Mic for ENC\*1)_ |
| Speaker | No | Yes | No |
| Sensors | Accelerometer, Compass | Accelerometer | 6-axis IMU, Compass, Barometer | 6-axis IMU, Compass | 3-axis IMU, Compass |
| Buttons | 4 |
| Vibration | ERM (eccentric rotating mass) | LRA (linear resonant actuator) |
| Case Material | Polycarbonate _(P, PT)_  
Stainless Steel 316 _(PS, PTS)_ | Stainless Steel 316 | Polycarbonate | Stainless Steel 316 |
| Lens Material | Polycarbonate | Gorilla Glass  
_(curved)_ | Gorilla Glass  
_(flat)_ | Hardened Glass  
_(flat)_ | Hardened Glass  
_(curved)_ |
| Charging Port | Power only | Smart accessory port | Smart accessory port  
_(data only)_ | Power only |
| Battery Life\*4 | ~7 days | ~7 days (Pebble Time), ~10 days (Pebble Time Steel) | ~2 days | ~7 days | ~30 days | ~14 days |
| Water Resistance\*3 | 5 ATM\*2  
_(50 m)_ | 3 ATM\*2  
_(30 m)_ | None  
_(Splash Resistant)_ | 3 ATM\*2  
_(30 m)_ | 20 m  
 | TBD  
_(target IPX8)_ | TBD  
_(target 30m)_ |
| Model | Classic,  
Steel | Time,  
Time Steel | Time Round | Pebble 2 | Pebble 2 Duo | Pebble Time 2\* | Pebble Round 2 |
| --- | --- | --- | --- | --- | --- | --- | --- |

\*1 ENC = Environmental Noise Cancellation

\*2 Please note regarding water resistance:

- 3 ATM → Safe for hand-washing, rain, splashes, and brief immersion, but not for swimming/diving.
- 5 ATM → Safe for swimming in shallow water, showering, and snorkeling, but not for diving.
  

\*3Rated waterproofing is applicable to new, sealed hardware. Age or repairs may compromise water resistance.

\*4Rated battery life is applicable to new hardware in typical usage conditions. Heavy use or use of power intensive apps and watchfaces may lead to a lower battery life. Battery life will reduce as the watch ages. Aftermarket replacement batteries may have a lower capacity.

See[_Available Defines and Macros_](/guides/best-practices/building-for-every-pebble.md#available-defines-and-macros)for a complete list of compile-time defines available.
