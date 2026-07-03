# WatchInfo

Source: https://developer.repebble.com/docs/c/Foundation/WatchInfo/index.html

Provides information about the watch itself.

This API provides access to information such as the watch model, watch color and watch firmware version.

## Function Documentation

[WatchInfoModel](/docs/c/Foundation/WatchInfo/#WatchInfoModel) watch\_info\_get\_model(void)

Provides the model of the watch.

#### Returns

`WatchInfoModel` representing the model of the watch.

[WatchInfoVersion](/docs/c/Foundation/WatchInfo/#WatchInfoVersion) watch\_info\_get\_firmware\_version(void)

Provides the version of the firmware running on the watch.

#### Returns

`WatchInfoVersion` representing the version of the firmware running on the watch.

[WatchInfoColor](/docs/c/Foundation/WatchInfo/#WatchInfoColor) watch\_info\_get\_color(void)

## Data Structure Documentation

struct WatchInfoVersion

Data structure containing the version of the firmware running on the watch. The version of the firmware has the form X.[X.[X]]. If a version number is not present it will be 0. For example: the version numbers of 2.4.1 are 2, 4, and 1. The version numbers of 2.4 are 2, 4, and 0.

#### Data Fields
uint8\_t major

Major version number.

uint8\_t minor

Minor version number.

uint8\_t patch

Patch version number.

## Enum Documentation

enum WatchInfoModel

The different watch models.

#### Enumerators
WATCH\_INFO\_MODEL\_UNKNOWN

Unknown model.

WATCH\_INFO\_MODEL\_PEBBLE\_ORIGINAL

Original Pebble.

WATCH\_INFO\_MODEL\_PEBBLE\_STEEL

Pebble Steel.

WATCH\_INFO\_MODEL\_PEBBLE\_TIME

Pebble Time.

WATCH\_INFO\_MODEL\_PEBBLE\_TIME\_STEEL

Pebble Time Steel.

WATCH\_INFO\_MODEL\_PEBBLE\_TIME\_ROUND\_14

Pebble Time Round, 14mm lug size.

WATCH\_INFO\_MODEL\_PEBBLE\_TIME\_ROUND\_20

Pebble Time Round, 20mm lug size.

WATCH\_INFO\_MODEL\_PEBBLE\_2\_HR

Pebble 2 HR.

WATCH\_INFO\_MODEL\_PEBBLE\_2\_SE

Pebble 2 SE.

WATCH\_INFO\_MODEL\_PEBBLE\_TIME\_2

Pebble Time 2.

WATCH\_INFO\_MODEL\_COREDEVICES\_P2D

CoreDevices P2D (Pebble 2 Duo)

WATCH\_INFO\_MODEL\_COREDEVICES\_PT2

CoreDevices PT2 (Pebble Time 2)

WATCH\_INFO\_MODEL\_COREDEVICES\_PR2

CoreDevices PR2 (Pebble Round 2)

WATCH\_INFO\_MODEL\_\_MAX

enum WatchInfoColor

The different watch colors.

#### Enumerators
WATCH\_INFO\_COLOR\_UNKNOWN

Unknown color.

WATCH\_INFO\_COLOR\_BLACK

Black.

WATCH\_INFO\_COLOR\_WHITE

White.

WATCH\_INFO\_COLOR\_RED

Red.

WATCH\_INFO\_COLOR\_ORANGE

Orange.

WATCH\_INFO\_COLOR\_GRAY

Gray.

WATCH\_INFO\_COLOR\_STAINLESS\_STEEL

Stainless Steel.

WATCH\_INFO\_COLOR\_MATTE\_BLACK

Matte Black.

WATCH\_INFO\_COLOR\_BLUE

Blue.

WATCH\_INFO\_COLOR\_GREEN

Green.

WATCH\_INFO\_COLOR\_PINK

Pink.

WATCH\_INFO\_COLOR\_TIME\_WHITE

Time White.

WATCH\_INFO\_COLOR\_TIME\_BLACK

Time Black.

WATCH\_INFO\_COLOR\_TIME\_RED

Time Red.

WATCH\_INFO\_COLOR\_TIME\_STEEL\_SILVER

Time Steel Silver.

WATCH\_INFO\_COLOR\_TIME\_STEEL\_BLACK

Time Steel Black.

WATCH\_INFO\_COLOR\_TIME\_STEEL\_GOLD

Time Steel Gold.

WATCH\_INFO\_COLOR\_TIME\_ROUND\_SILVER\_14

Time Round 14mm lug size, Silver.

WATCH\_INFO\_COLOR\_TIME\_ROUND\_BLACK\_14

Time Round 14mm lug size, Black.

WATCH\_INFO\_COLOR\_TIME\_ROUND\_SILVER\_20

Time Round 20mm lug size, Silver.

WATCH\_INFO\_COLOR\_TIME\_ROUND\_BLACK\_20

Time Round 20mm lug size, Black.

WATCH\_INFO\_COLOR\_TIME\_ROUND\_ROSE\_GOLD\_14

Time Round 14mm lug size, Rose Gold.

WATCH\_INFO\_COLOR\_PEBBLE\_2\_HR\_BLACK

Pebble 2 HR, Black / Charcoal.

WATCH\_INFO\_COLOR\_PEBBLE\_2\_HR\_LIME

Pebble 2 HR, Charcoal / Sorbet Green.

WATCH\_INFO\_COLOR\_PEBBLE\_2\_HR\_FLAME

Pebble 2 HR, Charcoal / Red.

WATCH\_INFO\_COLOR\_PEBBLE\_2\_HR\_WHITE

Pebble 2 HR, White / Gray.

WATCH\_INFO\_COLOR\_PEBBLE\_2\_HR\_AQUA

Pebble 2 HR, White / Turquoise.

WATCH\_INFO\_COLOR\_PEBBLE\_2\_SE\_BLACK

Pebble 2 SE, Black / Charcoal.

WATCH\_INFO\_COLOR\_PEBBLE\_2\_SE\_WHITE

Pebble 2 SE, White / Gray.

WATCH\_INFO\_COLOR\_PEBBLE\_TIME\_2\_BLACK

Pebble Time 2, Black.

WATCH\_INFO\_COLOR\_PEBBLE\_TIME\_2\_SILVER

Pebble Time 2, Silver.

WATCH\_INFO\_COLOR\_PEBBLE\_TIME\_2\_GOLD

Pebble Time 2, Gold.

WATCH\_INFO\_COLOR\_COREDEVICES\_P2D\_BLACK

CoreDevices P2D, Black.

WATCH\_INFO\_COLOR\_COREDEVICES\_P2D\_WHITE

CoreDevices P2D, White.

WATCH\_INFO\_COLOR\_COREDEVICES\_PT2\_BLACK\_GREY

CoreDevices PT2, Black/Grey.

WATCH\_INFO\_COLOR\_COREDEVICES\_PT2\_BLACK\_RED

CoreDevices PT2, Black/Red.

WATCH\_INFO\_COLOR\_COREDEVICES\_PT2\_SILVER\_BLUE

CoreDevices PT2, Silver/Blue.

WATCH\_INFO\_COLOR\_COREDEVICES\_PT2\_SILVER\_GREY

CoreDevices PT2, Silver/Grey.

WATCH\_INFO\_COLOR\_COREDEVICES\_PR2\_BLACK\_20

CoreDevices PR2, Black (20mm)

WATCH\_INFO\_COLOR\_COREDEVICES\_PR2\_SILVER\_20

CoreDevices PR2, Silver (20mm)

WATCH\_INFO\_COLOR\_COREDEVICES\_PR2\_GOLD\_14

CoreDevices PR2, Gold (14mm)

WATCH\_INFO\_COLOR\_COREDEVICES\_PR2\_SILVER\_14

CoreDevices PR2, Silver (14mm)

WATCH\_INFO\_COLOR\_\_MAX
