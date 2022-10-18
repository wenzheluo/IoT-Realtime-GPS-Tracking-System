#include <time.h>
#include "myiot33_library.h"
#include <WiFiNINA.h>
#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define I2C_ADDRESS 0x3C
SSD1306AsciiWire oled;
Adafruit_SSD1306 myOled(128, 64, &Wire, -1);


int addTwoInts(int a, int b)
{
  return a + b;
};

void iot33StartOLED(int oledLibrary)
{
   if (oledLibrary == 1){
     iot33StartOLED_Adafruit();
   } else {
     iot33StartOLED_Ascii();
   }
}

void displayTextOLED(String oledline[9], int oledLibrary)
{
  if (oledLibrary == 1){
    displayTextOLED_Adafruit(oledline);
  } else {
    displayTextOLED_Ascii(oledline);
  }
}

void iot33StartOLED_Ascii(void){
  Wire.begin(); //Arduino Nano 33 ioT
  oled.begin(&Adafruit128x64, I2C_ADDRESS, -1);
  oled.setFont(Adafruit5x7);
}

void displayTextOLED_Ascii(String oledline[9]) {
  oled.clear();
  oled.set1X();
  for (int jj = 1; jj <= 8; jj++) {  
     oled.println(oledline[jj]);
  }
}

void iot33StartOLED_Adafruit(void)
{
  Wire.begin();
  if(!myOled.begin(SSD1306_SWITCHCAPVCC, I2C_ADDRESS)) { 
    Serial.println("SSD1306 allocation failed");
  }
}

void displayTextOLED_Adafruit(String oledline[9])
{
  int jj;
  
  myOled.clearDisplay();
  myOled.setTextSize(1);
  myOled.setTextColor(SSD1306_WHITE);
  myOled.setCursor(0, 0);

  Serial.println("===================");
  for (jj=1; jj<=8; jj++) { 
    myOled.println(oledline[jj]);
    Serial.println(oledline[jj]);
    }
  Serial.println("===================");
  
  myOled.display(); 
}

void convHHMMSS(unsigned long currSeconds, char *uptimeHHMMSS) 
{
  int hh, mm, ss;

  hh = (currSeconds/3600);
  mm = (currSeconds -(3600*hh))/60;
  ss = (currSeconds -(3600*hh)-(mm*60));
  sprintf(uptimeHHMMSS, "Time: %02d:%02d:%02d", hh, mm, ss);

};

 
void convDDHHMMSS(unsigned long currSeconds, char *uptimeDDHHMMSS) 
{
  int dd, hh, mm, ss;

  ss = currSeconds; //258320.0 2 23:45:20
  dd = (ss/86400);
  hh = (ss-(86400*dd))/3600; 
  mm = (ss-(86400*dd)-(3600*hh))/60;
  ss = (ss-(86400*dd)-(3600*hh)-(60*mm));

  sprintf(uptimeDDHHMMSS, "%d %02d:%02d:%02d", dd, hh ,mm, ss);
};

void convCurrentTimeET(unsigned long currSeconds, char *currentTimeET) 
{
    time_t rawtime = currSeconds - 18000+3600;
    struct tm  ts;
    char buf[70];

    ts = *localtime(&rawtime);

    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &ts);
    sprintf(currentTimeET, buf);

};

void getWiFiRSSI(char *wifiRSSI) 
{
    sprintf(wifiRSSI, "%lddBm %d.%d.%d.%d", WiFi.RSSI(), WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3]);
};

void getMacWifiShield(char *macWifiShield) 
{
    byte mac[6];

    WiFi.macAddress(mac);
    sprintf(macWifiShield, "%02X:%02X:%02X:%02X:%02X:%02X", mac[5], mac[4], mac[3], mac[2], mac[1], mac[0]);
};

void getMacRouter(char *macRouter) 
{
    byte mac[6];

    WiFi.BSSID(mac);
    sprintf(macRouter, "%02X:%02X:%02X:%02X:%02X:%02X", mac[5], mac[4], mac[3], mac[2], mac[1], mac[0]);
};

void getMacWifiShieldMacRouterSS(char *macCombined) 
{
    byte macWifiShield[6];
    byte macRouter[6];
    long currMillis;

    currMillis = millis();
    WiFi.macAddress(macWifiShield);
    WiFi.BSSID(macRouter);
    
    sprintf(macCombined, "%02X:%02X:%02X:%02X:%02X:%02d", macWifiShield[0], macRouter[4], macWifiShield[1], macRouter[2], macWifiShield[2], (currMillis/1000) % 60);
};

void scanWiFi(char *Rssi, char *WiFi_MAC_Address,char *WiFi_Time,char *WiFi_LocalIP) {// print the SSID of the network you're attached to:
byte mac[6];
int rssi;
//Serial.print("SSID: ");
//Serial.println(WiFi.SSID());
IPAddress ip = WiFi.localIP();
sprintf(WiFi_LocalIP, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
//Serial.print("IP Address: ");
//Serial.println(WiFi_LocalIP);// print your WiFi shield's IP address:
rssi = WiFi.RSSI();
//Serial.print(" signal strength (RSSI):");// print the received signal strength:
sprintf(Rssi,"%d",rssi);
//Serial.print(Rssi);
//Serial.println(" dBm");
WiFi.macAddress(mac);
//Serial.print(" macAddress: ");
sprintf(WiFi_MAC_Address,"MAC %02X:%02X:%02X:%02X:%02X:%02X", mac[5], mac[4], mac[3], mac[2], mac[1], mac[0]);
//Serial.println(WiFi_MAC_Address);
//Serial.print(" WiFi_Time: ");
convCurrentTimeET(WiFi.getTime(), WiFi_Time);
//Serial.println(WiFi_Time);
//Serial.println("");
}
