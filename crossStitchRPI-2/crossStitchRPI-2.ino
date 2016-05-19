//adapted from Adafruit code by akleindolph  - - - extrasleepy.com  - - - April 2016
//For use with Adafruit Fona and Processing or openFrameworks
//need to use OLD FONA LIBRARY!!! 1.0
int inByte = 0;

#include <SoftwareSerial.h>
#include "Adafruit_FONA.h"

#define FONA_RX 2
#define FONA_TX 3
#define FONA_RST 4

// this is a large buffer for replies
char replybuffer[255];

SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
Adafruit_FONA fona = Adafruit_FONA(FONA_RST);

void setup() {
  Serial.begin(9600);
  fonaSS.begin(4800);

  // See if the FONA is responding
  if (! fona.begin(fonaSS)) {
    Serial.println(F("Couldn't find FONA"));
    while (1);
  }

  // Print SIM card IMEI number.
  char imei[15] = {     // MUST use a 16 character buffer for IMEI!
    0
  };
  uint8_t imeiLen = fona.getIMEI(imei);
}

void loop() {
  int8_t smsnum = fona.getNumSMS();     // read the number of SMS's!

  if (smsnum < 0) {
    Serial.println(F("Could not read # SMS"));
  }

  if (smsnum > 29) {
    for (int i = 0; i < 31; i++) {
      fona.deleteSMS(i);
      delay(50);
    }
    Serial.print("[");   
    Serial.print(" ");   
    Serial.println ("Clearing Memory");
    delay(5000);
    Serial.println ("Text Again!");
    delay(5000);
  }

  uint8_t smsn = smsnum;

  // Retrieve SMS value.
  uint16_t smslen;
  if (! fona.readSMS(smsn, replybuffer, 250, &smslen)) { // pass in buffer and max len!
    Serial.println("Failed!");
  }
  
  String text = replybuffer;
  Serial.print("[");   
  Serial.print(" ");   
  Serial.println(text);   
  delay (1000);
  Serial.print("[");   
  Serial.print(" ");  
  delay (1000);
}









