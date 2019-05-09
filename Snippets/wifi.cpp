// Required headers
#include <ESP8266WiFi.h> // If you want to connect to WiFi
#include <WiFiClientSecure.h> // If you want to do HTTPS requests
#include <ESP8266HTTPClient.h> // If you want to do HTTP requests

extern "C" {
#include "wpa2_enterprise.h" // If you want to connect to enterprise networks such as Eduroam
}

// Required variables
static const char* username = "username"; // Username wifi
unsigned char identity[] = "username"; // Username for enterprise networks
static const char* password = "password";
static const char* ssid = "eduroam"; // WiFi name (SSID) to connect to
char* host = "example.com"; // Host you wish to connect to
char* url = "api/example"; // URL you wish to connect to
const char* fingerprint = "C1:0D:53:49:D2:3E:E5:2B:A2:61:D5:9E:6F:99:0D:3D:FD:8B:B2:B3"; // Required for HTTPS requests

// Setup function
void setup() {

    wifi_set_opmode(STATION_MODE); // Required to act as client

    // Basic WiFI
    // loginBasicWiFI();


    // WiFi with username
    // loginEnterpriseWiFi();
  
    while (WiFi.status() != WL_CONNECTED) { // See if connected
        redBlinkLight(); // If you want to receive feedback that you are trying to connect
    }

    giveFeedbackConnected(); // If you want to show you are connected
  
    wifi_station_clear_cert_key();
    wifi_station_clear_username();
  
}

void loop() {
    doHTTPSRequest();
}

void loginBasicWiFI() {
    WiFi.begin(ssid, password);
}

void loginEnterpriseWiFi() {
    struct station_config wifi_config;
    memset(&wifi_config, 0, sizeof(wifi_config));
    strcpy((char*)wifi_config.ssid, ssid);
    wifi_station_set_config(&wifi_config);
    wifi_station_clear_cert_key();
    wifi_station_set_username(identity, sizeof(identity));
    wifi_station_clear_enterprise_ca_cert();
    wifi_station_set_wpa2_enterprise_auth(1);
    wifi_station_set_enterprise_identity((uint8*)username, strlen(username));
    wifi_station_set_enterprise_username((uint8*)username, strlen(username));
    wifi_station_set_enterprise_password((uint8*)password, strlen(password));
    wifi_station_connect();
}

void doHTTPSRequest() {

    char newHost[248];
    const int httpPort = 443;

    strcpy( newHost, url );

    WiFiClientSecure  client;

    client.setFingerprint(fingerprint); // Fingerprint must match SSL fingerprint certificate of host / domain
    
    if (!client.connect(host, httpPort)) {
        Serial.println(client.getWriteError());
        Serial.println("connection failed");
        return;
    }

    while(client.available()){ // Get and print response to console
        String line = client.readStringUntil('\r'); 
        Serial.print(line);
    }

    return;

}

void redBlinkLight() { // If you want to receive feedback that you are trying to connect
    Serial.print(".");
    analogWrite(RED, ON);
    delay(250);
    analogWrite(RED, OFF);
    delay(250);
}

void giveFeedbackConnected() { // If you want to show you are connected
    analogWrite(GREEN, ON); 
    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());ø
}