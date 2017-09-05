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

#include <ESP8266WiFi.h>
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <ESP8266mDNS.h>

// For the Adafruit shield, these are the default.
#define TFT_DC 2
#define TFT_CS 5

const char* host = "wifidisplay";
const char* ssid = "Motel6";
const char* password = "";

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

void setup() {
  Serial.begin(115200);
  delay(10);

  tft.begin();
    tft.fillScreen(ILI9341_BLACK);
    
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.hostname(host);
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
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  client.println("Wifi Display v1.0.1");
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
  
  if (req == "favicon.ico") { Serial.print("N/A"); } else {
    tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(0,0);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_WHITE);
  tft.println(req); }
  client.println(req);
  client.flush();
  
  
  Serial.println("Client disonnected");
delay(100);
  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}

