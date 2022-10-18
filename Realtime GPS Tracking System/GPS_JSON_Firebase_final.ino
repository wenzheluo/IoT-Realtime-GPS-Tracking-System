/**************************************************************************
 This is the final Project
 From Chen Chen(G01164294) & Wenzhe Luo(G01213418)
 **************************************************************************/
#include "modTinyGPSpp.h"
#include <stdio.h>
#include "myiot33_library.h"
#include <Arduino_JSON.h>
#include <Arduino.h>
#include <WiFiNINA.h>
#include <SPI.h>
#include <SD.h>
#include "WiFi_Default.h"
#include "Firebase_default.h"

File myFile;

unsigned long currMillis, prevMillis;
unsigned long wifiEpoch = 0;
int ii=0;

char lcdBuffer[80];
char etBuffer[80];
String strJsonBuffer;
String oledline[9];
const int oledLib = 1;

String output2Cloud ="";


int filect = 0;

TinyGPSPlus gps;
JSONVar myGPS;

void setup() {

  Serial.begin(9600); delay(500);
  Serial1.begin(9600); delay(500);
  //set up for OLED
  iot33StartOLED(oledLib);
  oledline[1] = "ECE508 GPS Tracker";
  int jj; for (jj=2; jj<=8; jj++){ oledline[jj]=""; }
  displayTextOLED(oledline, oledLib);

  //Wifi Set up
    //WifiSetup();
     
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, WIFI_SSID, WIFI_PASSWORD);
  Firebase.reconnectWiFi(true);

  //set up for SD card reader
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


Serial.print("Initializing SD card...");

if (!SD.begin(10)) {
Serial.println("initialization failed!");
while (1);
}
Serial.println("initialization done.");

//open the file. note that only one file can be open at a time,
//so you have to close this one before opening another.
myFile = SD.open("data.txt", FILE_WRITE);

//if the file opened okay, write to it:
if (myFile) {
Serial.print("Writing to data.txt...");
myFile.println("data collection");
//close the file:
myFile.close();
Serial.println("done.");
} else {
//if the file didn't open, print an error:
Serial.println("error opening test.txt");
}

//re-open the file for reading:
myFile = SD.open("data.txt");
if (myFile) {
Serial.println("data.txt:");

//read from the file until there's nothing else in it:
while (myFile.available()) {
Serial.write(myFile.read());
}
//close the file:
myFile.close();
} else {
//if the file didn't open, print an error:
Serial.println("error opening test.txt");
  

}
  
}

void loop() {

  currMillis = millis();

  if (currMillis - prevMillis >= 1000) {
    prevMillis = currMillis;
    
    smartDelay(250);    
    updateOledDisplay();
    strJsonBuffer = createJSON();
    output2Cloud =strJsonBuffer;
    //Serial.println(strJsonBuffer);


    //Write to SD card
    myFile = SD.open("data.txt", FILE_WRITE);
    if (myFile) {
      Serial.print("Writing to data.txt...");
      myFile.println("GPS Data Collection");
      myFile.println("------------------------------");
      myFile.println(strJsonBuffer);
      myFile.println("..............................");
      // close the file:
      myFile.close();
      Serial.println("done.");
    } else {
    // if the file didn't open, print an error:
      Serial.println("error opening data.txt");
    }
    sendToFirebase();
    
  }

}

void updateOledDisplay() {
  sprintf(lcdBuffer, "%04d-%02d-%02d %02d:%02d:%02d", gps.date.year(), gps.date.month(), gps.date.day(), 
                                                      gps.time.hour(), gps.time.minute(), gps.time.second());
  oledline[2] = String(lcdBuffer);

  double latRnd = (double) random(0, 1000)/1000;
  double lonRnd = (double) random(0, 1000)/1000;
  oledline[4] = String(gps.location.lat(),5) + ", " + String(gps.location.lng(),5);
  oledline[5] = "Alt(ft): " + String(gps.altitude.feet(), 1);
  oledline[6] = "Sat: " + String(gps.satellites.value()) + ", HDOP:" + String((float)gps.hdop.value()/100, 2);
  oledline[7] = "Speed(kmph): " + String(gps.speed.kmph(),2);
  convDDHHMMSS(currMillis/1000, lcdBuffer);
  oledline[8] = "Uptime: " + String(lcdBuffer);
  displayTextOLED(oledline, oledLib);  
}

String createJSON() {
  String strJSON = "";

  //myGPS["nameCollection"] = "myGPSdata";
  sprintf(lcdBuffer, "%04d-%02d-%02d %02d:%02d:%02d", gps.date.year(), gps.date.month(), gps.date.day(), 
                                                      gps.time.hour(), gps.time.minute(), gps.time.second());
  myGPS["epoch"] = String(lcdBuffer);

  //double latRnd = (double) random(0, 1000)/1000;
  //double lngRnd = (double) random(0, 1000)/1000;
  myGPS["gps"]["locvalid"] = gps.location.isValid();
  myGPS["gps"]["loc"]["lat"] = String(gps.location.lat(),5);
  myGPS["gps"]["loc"]["lon"] = String(gps.location.lng(),5);

  myGPS["gps"]["alt"] = gps.altitude.isValid();
  myGPS["gps"]["alt_ft"] = String(gps.altitude.feet(),1);

  myGPS["gps"]["speedvalid"] = gps.speed.isValid();
  myGPS["gps"]["speedkmph"] = String(gps.speed.kmph(),2);

  myGPS["gps"]["hdopvalid"] = gps.hdop.isValid();
  myGPS["gps"]["hdop"] = String((float)gps.hdop.value()/100,2);

  myGPS["gps"]["satvalid"] = gps.satellites.isValid();
  myGPS["gps"]["sat"] = gps.satellites.value();
    
  convDDHHMMSS(currMillis/1000, lcdBuffer);
  myGPS["uptime"] = lcdBuffer;

  return JSON.stringify(myGPS);
}


// This custom version of delay() ensures that the gps object is being "fed".
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (Serial1.available())
      gps.encode(Serial1.read());
  } while (millis() - start < ms);
}


//set up firebase
void sendToFirebase(){
        if (Firebase.setJSON(firebaseData, "/IoT33/Received", output2Cloud)){
            Serial.println("PASSED");
            Serial.println("PATH: " + firebaseData.dataPath());
            Serial.print("PUSH NAME: ");
            //Serial.println(firebaseData.pushName());
            Serial.println("------------------------------------");
            Serial.println();
          }
          else{
            Serial.println("FAILED");
            Serial.println("REASON: " + firebaseData.errorReason());
            Serial.println("------------------------------------");
            Serial.println();
          }  
}
