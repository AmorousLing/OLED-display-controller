#include "core_esp8266_features.h"
#include "WiFiClient.h"
#include "TIM.h"
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <string.h>

unsigned int timtick=0;

String Year;
String Month;
String Day;
String Hour;
String Minute;
String payload;

const String url="http://quan.suning.com/getSysTime.do";
void GetTime()
{
  if(millis()-timtick<5000) return;
  timtick=millis();

  WiFiClient tcpClient;
  HTTPClient http;
  http.begin(tcpClient,url);
  http.addHeader("Content-Type","text/plain");
  http.POST("Message from ESP8266");
  payload=http.getString();
  http.end();
  TimeHandle();
}

void TimeHandle()
{
  Year=payload.substring(13,17);
  Month=payload.substring(18,20);
  Day=payload.substring(21,23);
  Hour=payload.substring(24,26);
  Minute=payload.substring(27,29);
}