/*
 *  
 *    http://server_ip/messagetodisplay
 *  http://hostname.local/messagetodisplay
 *  
 *  Still a work in progress, this will display the message on a TFT LCD
 *  screen based on the ILI9341 chipset.
 *  
 *  Sometimes hostname doesn't show up on the network quickly,
 *  pinging the IP address seems to help.
 *  
 *  (C) LeRoy Miller, 2017
 *  updated Jun 8, 2017
 */

#include <WiFi.h>
#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`
#include <ESPmDNS.h>

const char* host = "wifidisplay";
const char* ssid = "Motel6";
const char* password = "";

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);
SSD1306  display(0x3c, 5, 4);

void setup() {
  Serial.begin(9600);
  delay(10);
// Initialising the UI will init the display too.
  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  //WiFi.hostname(host);
  WiFi.begin(ssid, password);
  MDNS.begin(host);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
  
  display.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
  //display.setFont(ArialMT_Plain_10);
  display.drawString(DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2, "Ready:\n" + WiFi.localIP().toString());
  display.display();
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  client.println("ESP32 Wifi Display v2.0.0");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  req.replace("%20", " ");
  req.remove(0,5);
  req.remove(req.length()-9, 9);
  Serial.println(req);
  if (req == "favicon.ico") {return;}
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawStringMaxWidth(0, 0, 120, req);
  display.display();
  client.println(req);
  client.flush();
  
  
  Serial.println("Client disonnected");
delay(100);
  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}

