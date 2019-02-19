#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "secrets.h"

#define BAUD_RATE 9600

template <class T>
inline Print &operator<<(Print &obj, T arg)
{
  obj.print(arg);
  return obj;
}

void setup()
{
  // Set the baud rate.
  Serial.begin(BAUD_RATE);

  // Initialize connection to WiFi access point.
  WiFi.begin(ssid, pass);
  Serial << "\nConnecting to WiFi ...";
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial << ".";
    delay(500);
  }
  Serial << "\nConnected to WiFi! (IP Address: " << WiFi.localIP().toString() << ")\n";
}

void loop()
{
  HTTPClient static http;
  // Fetch data from API.
  http.begin("http://numbersapi.com/random");
  http.setTimeout(5 * 1000);
  int const statusCode = http.GET();
  if (statusCode != HTTP_CODE_OK)
  {
    Serial << "Error: could not fetch data from API (" << http.errorToString(statusCode) << ").\n";
  }
  else
  {
    String const payload = http.getString();
    Serial << payload << '\n';
  }
  http.end();
  delay(5 * 1000);
}