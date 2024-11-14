#ifndef __WIFI_H
#define __WIFI_H

void parseInfo(WiFiClient client);
void connectWifi();
void httpRequest(String reqRes);
void syncTime();
void initMQTT();
void gotoMQTT();
void mqtt_run();
extern String reqRes;
extern String Year;
extern String Month;
extern String Day;
extern String Hour;
extern String Minute;

extern float h;
extern float t;






#endif