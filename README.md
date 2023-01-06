[![WiFi Clock LED Matrix](http://img.youtube.com/vi/qhvd6wGgwzA/0.jpg)](http://www.youtube.com/watch?v=qhvd6wGgwzA "WiFi Clock LED Matrix")

# WiFi Clock LED Matrix
LED Matrix clock that updates via WiFi

## Parts
| Qty | Product                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      | Description             |
| --- |------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|-------------------------|
|1 | [DEVKIT v3](https://www.aliexpress.com/item/4000502101618.html?spm=a2g0o.productlist.main.5.3198f68fA7sb7l&algo_pvid=c776aa69-0f96-465c-8a3a-5ed33ba152b4&algo_exp_id=c776aa69-0f96-465c-8a3a-5ed33ba152b4-2&pdp_ext_f=%7B%22sku_id%22%3A%2210000002402566500%22%7D&pdp_npi=2%40dis%21ILS%2113.54%2113.54%21%21%21%21%21%40214527c616727687280498709d0741%2110000002402566500%21sea&curPageLogUid=hq0vy3dw9STm)                                                                                                                                                              | Main board              |
|1 | [LED Matrix](https://www.aliexpress.com/item/4001010808015.html?spm=a2g0o.productlist.main.1.1612wt8dwt8dhe&algo_pvid=db754b11-196a-4ed8-b792-d3399b41c24f&algo_exp_id=db754b11-196a-4ed8-b792-d3399b41c24f-0&pdp_ext_f=%7B%22sku_id%22%3A%2212000031539433947%22%7D&pdp_npi=2%40dis%21ILS%2115.61%2112.8%21%21%21%21%21%402100ba4716730341185718755d075c%2112000031539433947%21sea&curPageLogUid=rWpg1VNb9M6x) | WS2812B LED Matrix 32x8 |

## Notes
[Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library) must be installed.

[Adafruit NeoMatrix](https://github.com/adafruit/Adafruit_NeoMatrix) must be installed.

[Adafruit NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel) must be installed.

[Adafruit BusIO](https://github.com/adafruit/Adafruit_BusIO) must be installed.

In the file Config.h you must set:
```
//Your WiFi SSID and Password
#define STASSID "YourSSID"
#define STAPSK  "YourPassword"
```
```
//Your Time Zone
#define MYTZ YourTimeZone
```
[See all time zones here](https://github.com/esp8266/Arduino/blob/master/cores/esp8266/TZ.h)

Set desired **upload_port** in the file **platformio.ini** file.

## Connection Diagram
![Connection Diagram](Images/Connection%20Diagram.png)
