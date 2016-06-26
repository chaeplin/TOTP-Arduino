// GetCode.ino
//
// Basic example for the TOTP lib for esp8266
//


#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <time.h>
#include "sha1.h"
#include "TOTP.h"

#include "/usr/local/src/ap_setting.h"

// http://www.lucadentella.it/en/totp-libreria-per-arduino/
// http://www.lucadentella.it/OTP/
// https://gauth.apps.gbraad.nl
// The shared secret is MyLegoDoor
uint8_t hmacKey[] = {0x74, 0x65, 0x73, 0x74, 0x74, 0x65, 0x73, 0x74, 0x31, 0x32};

TOTP totp = TOTP(hmacKey, 10);
char code[7];


void setup() 
{
  Serial.begin(115200);
  Serial.println();

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(100);
  }
  configTime(0, 0, "pool.ntp.org", "time.nist.gov");
}

void loop() 
{
  time_t now = time(nullptr);
  //Serial.println(now);
  //Serial.println(ctime(&now));
  if ( now != 0 ) 
  {
    char* newCode = totp.getCode(now);
    if (strcmp(code, newCode) != 0) 
    {
      strcpy(code, newCode);
      Serial.println(code);
    }
  }
}
