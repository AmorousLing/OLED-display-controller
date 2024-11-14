#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>
#include "WiFi.h"
#include <time.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include "OLED.h"
#include "TIM.h"
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

const int led = 2;                       

void setup()
{
  SerialConfig config = SerialConfig::SERIAL_8N1;
  Serial.begin(115200);
  
  //设置引脚5为rxd  2为txd
  Serial.println("");
  OLED_Init();                                    //OLED初始化 
  pinMode(led, OUTPUT);               //设置LED引脚为输出模式
  digitalWrite(led, 1);               //初始LED为高电平（熄灭），板载LED为低电平点亮
  connectWifi();                         //先连接到指定路由器
  //syncTime();  // X.509 validation requires synchronization time
  initMQTT();                         //初始化MQTT客户端
  gotoMQTT();                         //连接到指定MQTT服务器，并订阅指定主题
  pinMode(12, OUTPUT); 
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
}

void loop()
{
  mqtt_run();
  httpRequest(reqRes);
  GetTime();
  OLED_Display();
  Page_change();
  delay(50);
}

