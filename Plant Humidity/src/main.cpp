#include "main.h"

void printSSID()
{
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
}
void printSignalStrength()
{
  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);
}
void setup()
{
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
}
void loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED)
    {
      // Connect to WPA/WPA2 network:
      WiFi.begin(ssid, pass);
      Serial.print('.');
      delay(5000);
    }
    Serial.println("\nConnected.");
  }

  int value = analogRead(A0);
  Serial.println("Value = " + value);
  printSSID();
  printSignalStrength();

  int x = ThingSpeak.writeField(703220, 1, value, "355PMDGV834I40BT");
  if (x == 200)
  {
    Serial.println("Channel update successful.");
  }
  else
  {
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }

  // timeout 20 sec
  delay(20000);
}