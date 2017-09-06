# WIFI Display Badge

Display messages on a TFT or OLED screen, using a ESP8266 or ESP32.  

v1.0, 1.1 - Use a 3.3v ILI9341 TFT Color screen, they setup a website. When a "message" is attached to the URL it is displayed on the TFT screen.
There is no formating of the screen.   
v1.0 - Gives no feedback that it worked on, it the website - It looks like it failed with a "This page isn't working" message.  
v1.1 Give limited feeback to the website - displaying the version of arduino software, and the message you just send.  

v2.0 - Uses a ESP32 board that has a on board OLED. This version displays the IP address of the ESP32. There is limited on screen formating.   

v1.0, 1.1, 2.0 setup a website and hostname - the "message" is appended to the end of the IP address or Hostname.local IE:   
http://IP/messagetodisplay   
http://hostname.local/messagetodisplay  
  
Sometimes it takes a while for the hostname to show up on the network, using the IP address appears to be a better option.  
In these sketches the hostname is wifidisplay and should be changed if you are going to use more than one device on your network.  

The ESP32 should be easy to convert to a ESP8266 if needed.  

v1.3 MQTT - The MQTT version uses a MQTT broker to pass messages to your display. You don't need to know your IP, and you don't need to open any ports.  
This version subscribes to the topic "display1", there is limited formating for the display.   
The biggest limitation is if the message is larger than the display it will get "cut" off.  
There are two version of the sketch, one for the ESP8266 devices, and one for the ESP32 devices.   
Both sketches create a unique device name for the MQTT broker (It uses part of the MAC address of the device to do this) So far this has worked without duplication.   
I am limited to about 30 devices thou, so it's still possiable that it doesn't create a totally unique name.  
The broker is "test.mosquitto.org", and no security is being used.  So don't pass anything sensitive.  
For the ESP8266 version, I've commented out lines for using the D1 Mini with it's small OLED screen,  The ESP8266 boards w/on board OLEDs and the NodeMCU with external OLED.  
just uncomment the line for the device you are using, and comment the others.  IF you are using a D1 mini, also change the ```#define D1mini 0``` statement to ```#define D1mini 1```   
This will make some minor adjustments for the screen size.   The ESP32 version is almost the same sketch with some minor changes need for the ESP32.   

None of the versions gaurantee the message will be displayed, v1 - v2 have a better chance of it working without question since the webserver is running on the device.  
There is no qaurantee for the MQTT versions.  

## Libraries Needed
You need either the ESP8266 or ESP32 boards loaded in the board manager (or both if you have both)  

Depending on version:  
MQTT version:  
PubSubClient.h https://github.com/knolleary/pubsubclient  
SSD1306.h   https://github.com/squix78/esp8266-oled-ssd1306  

v1.0, 1.1:  
Adafruit_GFX.h  
Adafruit_ILI9341.h  
I beleive these can be found in the library manager of the IDE.  

v2.0:  
SSD1306.h  see above.  

Other Libraries are included with the respective board managers.  

## Video

https://youtu.be/fMKPxThoW1I  

## Usage

see above, general knowledge of MQTT is helpful.  

## Contributing

1. Fork it!
2. Create your feature branch: `git checkout -b my-new-feature`
3. Commit your changes: `git commit -am 'Add some feature'`
4. Push to the branch: `git push origin my-new-feature`
5. Submit a pull request

## Support Me

If you find this or any of my projects useful or enjoyable please support me.
Anything I do get goes to buy more parts and make more/better projects.  
https://www.patreon.com/kd8bxp  
https://ko-fi.com/lfmiller

## Other Projects

https://www.youtube.com/channel/UCP6Vh4hfyJF288MTaRAF36w
https://kd8bxp.blogspot.com/


## Credits

Copyright (c) 2017 LeRoy Miller

## License

This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses>
