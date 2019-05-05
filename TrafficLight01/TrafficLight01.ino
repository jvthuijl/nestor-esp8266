#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include "index.h"

const int LDR = A0;
const int BUTTON = 4;
const int RED = 15;
const int GREEN = 12;
const int BLUE = 13;

const int WAITTIME = 1000; // 1 second
const int ON = 100;
const int OFF = 0;

int counter = 0;
int ledColor = RED;

IPAddress apIP(192, 168, 1, 1);
DNSServer dnsServer;
ESP8266WebServer httpServer(80); //Server on port 80

void setup() {
  // setup global configuration
  Serial.begin(9600);
  blueLed(ON);
  delay(100);
  Serial.println("Starting the Traffic Light..."); 
  pinMode(LDR, INPUT);
  pinMode(BUTTON, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  // setup WIFI AP
  WiFi.mode(WIFI_AP_STA); // Both hotspot and client are enabled
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("Traffic-Light", "traffic123"); // Start AP. Removing the password will disable security
  Serial.println("WIFI Accesspoint started");

  // setup DNS
  dnsServer.start(53, "*", apIP);
  Serial.println("DNS started");

  // setup HTTP Server
  httpServer.on("/", handleRequest);
  httpServer.on("/rood", handleRood);
  httpServer.on("/groen", handleGroen);
  httpServer.onNotFound(handleNotFound);
  httpServer.begin(); // Start server
  Serial.println("HTTP server started");  

  // setup HTTP Client (station)
  WiFi.begin("SSID", "..............."); // Connect to WiFi
  while (WiFi.status() != WL_CONNECTED) {
     delay(2000);
     Serial.println("Waiting for WIFI to connect...");
  }  
  Serial.println("WIFI is connected.");
  Serial.println(WiFi.SSID());
  Serial.println("Local IP: " + WiFi.localIP().toString());

  blueLed(OFF);
}

void loop() {
  dnsServer.processNextRequest();
  httpServer.handleClient(); // Handle client requests

  // Blink Led
  setLed(ledColor);
  delay(500);
  setLed(OFF);
  delay(500);
  
  // increment counter and call web if counter > threshold
  counter++;
  if (counter >= 20) {
    ledColor = (GetColorFromWeb() == "rood") ? RED : GREEN;
    counter = 0;
  }
}

// Helper-functions are below

void setLed(int color)
{
  if (color == RED) {
    redLed(ON);
  } else if (color == GREEN) {
    greenLed(ON);
  } else {
    redLed(OFF);
    greenLed(OFF);
  }
}

void redLed(int value) 
{
  analogWrite(RED, value);
}

void greenLed(int value) 
{
  analogWrite(GREEN, value);
}

void blueLed(int value) 
{
  analogWrite(BLUE, value);
}

void handleRequest() 
{
  String html = MAIN_page;
  httpServer.send(200, "text/html", html);
}

void handleRood() 
{
  ledColor = RED;
  httpServer.send(200, "text/plain", "rood");
}

void handleGroen() 
{
  ledColor = GREEN;
  httpServer.send(200, "text/plain", "groen");
}

void handleNotFound()
{
  httpServer.sendHeader("Location", "/", true); //Redirect to the root page  
  httpServer.send(302, "text/plain", "");
}

String GetColorFromWeb() 
{
  String color = "rood";
  if (WiFi.status() == WL_CONNECTED) { 
    HTTPClient httpClient; 
    httpClient.begin("http://server.fritz.box/service/TrafficColor"); 
    int httpCode = httpClient.GET(); //Send the request
    Serial.printf("Responsecode webrequest: %d\n", httpCode);
    if (httpCode == HTTP_CODE_OK) { // Check the returning code
      color = httpClient.getString(); // Get the request response payload
    }
    httpClient.end(); // Close connection
  } else {
    Serial.println("No WIFI connection");   
  }
  return color;
}
