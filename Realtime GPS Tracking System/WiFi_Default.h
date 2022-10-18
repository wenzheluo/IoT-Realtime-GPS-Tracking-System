#include <WiFiNINA.h>
#define SECRET_SSID "AndyC-Guest"//wifi name
#define SECRET_PASS "Nijiushijinbulai"//wifi password
int keyIndex = 0;
int status = WL_IDLE_STATUS;
char server[] = "";
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
WiFiClient client;
//char lcdBuffer[80];
//String oledline[9];
//String location= "torino,IT";
String location= "fairfax,US";
char rssi[4], ip[20], MAC_Address[24], WiFi_Time[24], eqoch[20], savedata[20];
uint32_t ptr=0 ;
String readString, readString1;
String servRes = "";
String serverEpoch = "";
