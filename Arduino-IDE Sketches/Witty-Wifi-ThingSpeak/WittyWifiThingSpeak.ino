#include <ESP8266WiFi.h>

const int LDR = A0;
const int BUTTON = 4;
const int RED = 15;
const int GREEN = 12;
const int BLUE = 13;
const int ON = 25;
const int OFF = 0;

int counter = 0;  

// WIFI
const char* ssid     = "iPhone van Gerard";
const char* password = "pipodeclown";
const char* server   = "api.thingspeak.com";
String apiKey        = "EH3I4BJGZS2AZRC7";
String path          = "/update?key=" + apiKey + "&field1=";

void setup() 
{
    Serial.begin(9600);
 
    pinMode(LDR, INPUT);
    pinMode(BUTTON, INPUT);
    pinMode(RED, OUTPUT);
    pinMode(GREEN, OUTPUT);
    pinMode(BLUE, OUTPUT);

    initWifi();
}
 
void loop()
{
  greenLed(ON);
  delay(1000);
  greenLed(OFF);
  delay(1000);
  
  counter++;
  if (counter == 10)
  {
    int ldrValue = analogRead(LDR); 
    sendApiRequest(path + ldrValue);
    counter = 0;
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

// Establish WiFi connection
void initWifi() 
{
  redLed(ON);
  
  Serial.print("Connecting to: "); 
  Serial.print(ssid);
  WiFi.mode(WIFI_STA); // force WiFi to station mode
  WiFi.begin(ssid, password);  

  int timeout = 20 * 4; // 20 seconds
  while (WiFi.status() != WL_CONNECTED  && (timeout-- > 0)) 
  {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");

  if (WiFi.status() != WL_CONNECTED) 
  {
     Serial.println("Failed to connect!");
  }
  else
  {
    redLed(OFF);
    greenLed(ON);
  }

  Serial.print("WiFi connected in: "); 
  Serial.print(millis());
  Serial.print(", IP address: "); 
  Serial.println(WiFi.localIP());
}

void sendApiRequest(String path)
{
  WiFiClient client;

  blueLed(ON);
  
  int retries = 5;
  while (!!!client.connect(server, 80) && (retries-- > 0)) 
  {
    Serial.print(".");
  }
  Serial.println();
  
  if (client.connected()) 
  {
    client.print(String("GET ") 
      + path
      + " HTTP/1.1\r\n" 
      + "Host: " + server 
      + "\r\n" 
      + "Connection: close\r\n\r\n");
    
    int timeout = 5 * 10; // 5 seconds             
    while (!!!client.available() && (timeout-- > 0))
    {
      delay(100);
    }

    while (client.available())
    {
      Serial.write(client.read());
    }    
  } 
  else 
  {
    Serial.println("Failed to connect!");
  }

  blueLed(OFF);

}
