#include "core_esp8266_features.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <time.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <string.h>
#include "Wifi.h"
#include "OLED.h"
const char* ssid="Hello_world";
const char* password="010723dyn";

int value = 0;
int count;
extern uint8_t page;
extern uint8_t color;
const char* host="api.seniverse.com";    //心知天气接口API
const int httpPort=80;                   //端口号

String reqUserKey="SwwGBp7hLsksTdurI";   //用户私钥
String reqLocation="Changsha";            //查询地点
String reqUnit="c";                      //温度单位为摄氏度
String reqRes = "/v3/weather/daily.json?key=" + reqUserKey +
                  + "&location=" + reqLocation + 
                  "&language=en&unit=" +reqUnit+"&start=0"+"&days=3";   //API的HTTP调用

char LineString1[40];

unsigned int wifitick=0;

String results_0_daily_date_0;
String results_0_daily_date_1;
String results_0_daily_date_2;
int results_0_daily_highT_0;
int results_0_daily_highT_1;
int results_0_daily_highT_2;
int results_0_daily_humidity_0;
int results_0_daily_humidity_1;
int results_0_daily_humidity_2;
String results_0_daily_weather_0;
String results_0_daily_weather_1;
String results_0_daily_weather_2;
String results_0_location_name;

const char* mqtt_server = "broker.emqx.io";          
const int mqttPort = 1883;                            //MQTT服务器端口
/*****************用户信息项 (全部为自定义项)*****************/
const char* ESP8266_ID = "espmqttdyn";                 //自定义ID
const char* ESP8266_user = "dyn";                   //用户名
const char* ESP8266_password = "dyn";              //密码
const char* ESP8266_pub = "esppub";                 //发送主题（对方的订阅主题）
const char* ESP8266_sub = "espxl";                 //订阅主题（对方的发送主题）
// // NTP Server settings
// const char *ntp_server = "pool.ntp.org";     // Default NTP server
// // const char* ntp_server = "cn.pool.ntp.org"; // Recommended NTP server for users in China
// const long gmt_offset_sec = 0;            // GMT offset in seconds (adjust for your time zone)
// const int daylight_offset_sec = 0;        // Daylight saving time offset in seconds

//BearSSL::WiFiClientSecure espClient;

WiFiClient espClient;
PubSubClient client(espClient);                      //定义客户端对象
String data = "";
// static const char ca_cert[]
// PROGMEM = R"EOF(
// -----BEGIN CERTIFICATE-----
// MIIDrzCCApegAwIBAgIQCDvgVpBCRrGhdWrJWZHHSjANBgkqhkiG9w0BAQUFADBh
// MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3
// d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD
// QTAeFw0wNjExMTAwMDAwMDBaFw0zMTExMTAwMDAwMDBaMGExCzAJBgNVBAYTAlVT
// MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxGTAXBgNVBAsTEHd3dy5kaWdpY2VydC5j
// b20xIDAeBgNVBAMTF0RpZ2lDZXJ0IEdsb2JhbCBSb290IENBMIIBIjANBgkqhkiG
// 9w0BAQEFAAOCAQ8AMIIBCgKCAQEA4jvhEXLeqKTTo1eqUKKPC3eQyaKl7hLOllsB
// CSDMAZOnTjC3U/dDxGkAV53ijSLdhwZAAIEJzs4bg7/fzTtxRuLWZscFs3YnFo97
// nh6Vfe63SKMI2tavegw5BmV/Sl0fvBf4q77uKNd0f3p4mVmFaG5cIzJLv07A6Fpt
// 43C/dxC//AH2hdmoRBBYMql1GNXRor5H4idq9Joz+EkIYIvUX7Q6hL+hqkpMfT7P
// T19sdl6gSzeRntwi5m3OFBqOasv+zbMUZBfHWymeMr/y7vrTC0LUq7dBMtoM1O/4
// gdW7jVg/tRvoSSiicNoxBN33shbyTApOB6jtSj1etX+jkMOvJwIDAQABo2MwYTAO
// BgNVHQ8BAf8EBAMCAYYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUA95QNVbR
// TLtm8KPiGxvDl7I90VUwHwYDVR0jBBgwFoAUA95QNVbRTLtm8KPiGxvDl7I90VUw
// DQYJKoZIhvcNAQEFBQADggEBAMucN6pIExIK+t1EnE9SsPTfrgT1eXkIoyQY/Esr
// hMAtudXH/vTBH1jLuG2cenTnmCmrEbXjcKChzUyImZOMkXDiqw8cvpOp/2PV5Adg
// 06O/nVsJ8dWO41P0jmP6P6fbtGbfYmbW0W5BjfIttep3Sp+dWOIrWcBAI+0tKIJF
// PnlUkiaY4IBIqDfv8NZ5YBberOgOzW6sRBc4L0na4UU+Krk2U886UAb3LujEV0ls
// YSEY1QSteDwsOoBrp+uvFRTp2InBuThs4pFsiv9kuXclVzDAGySj4dzp30d8tbQk
// CAUw7C29C79Fv1C5qfPrmAESrciIxpg0X40KPMbp1ZWVbd4=
// -----END CERTIFICATE-----
// )EOF";

void connectWifi()
{
  WiFi.begin(ssid, password);
  Serial.print("连接WiFi中");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi连接成功");
}

// void syncTime() 
// {
//     configTime(gmt_offset_sec, daylight_offset_sec, ntp_server);
//     Serial.print("Waiting for NTP time sync: ");
//     while (time(nullptr) < 8 * 3600 * 2) {
//         delay(1000);
//         Serial.print(".");
//     }
//     Serial.println("Time synchronized");
//     struct tm timeinfo;
//     if (getLocalTime(&timeinfo)) {
//         Serial.print("Current time: ");
//         Serial.println(asctime(&timeinfo));
//     } else {
//         Serial.println("Failed to obtain local time");
//     }
// }
void callback(char* topic, byte* payload, unsigned int length)//数据回调函数，监听数据接收
{
  if((char)topic[3] == 'x')
  {
    for (int i = 0; i < length; i++)
    {
      // data += (char)payload[i]; 
      if((char)payload[i-2] == 'p' && (char)payload[i-1] == 'g')
      {
        page = (uint8_t)payload[i]-48;
      }
      if((char)payload[i-2] == 'c' && (char)payload[i-1] == 'l')
      {
        color = (uint8_t)payload[i]-48;
      }
    }
  }
  if((char)topic[3] == 'm')
  {
    data = "";
    for (int i = 0; i < length; i++)
    {
      data += (char)payload[i]; 
    }
  }
}
void initMQTT()//初始化MQTT设置
{
  //指定客户端要连接的MQTT服务器IP和端口
  client.setServer(mqtt_server, mqttPort);
  //绑定数据回调函数
  client.setCallback(callback);
}

void gotoMQTT()//连接MQTT服务器
{
  //BearSSL::X509List serverTrustedCA(ca_cert);
  //espClient.setTrustAnchors(&serverTrustedCA);
  //用while循环执行到连接MQTT成功
  while (!client.connected()) {
    Serial.println("连接MQTT服务器中");
    //连接MQTT服务器，提交ID，用户名，密码
    bool is=client.connect(ESP8266_ID, ESP8266_user, ESP8266_password);
    if (is) {
      Serial.println("连接MQTT服务器成功");
    } else {
      Serial.print("失败原因 ");
     Serial.print(client.state());
      delay(2000);
    }
  }
  client.subscribe(ESP8266_sub, 1);//添加订阅
  client.subscribe("espmsg", 1);//添加订阅
}
void mqtt_run()
{
  if (!client.connected()) {
        gotoMQTT();
    }
  client.loop();//持续运行MQTT运行函数，完成接收数据和定时发送心跳包
}
//对JOSN数据解析
void parseInfo(WiFiClient client){
  //开辟存储空间
  const size_t capacity = JSON_ARRAY_SIZE(1) +JSON_ARRAY_SIZE(3)+ JSON_OBJECT_SIZE(1)+
                          JSON_OBJECT_SIZE(3)+JSON_OBJECT_SIZE(6) + 3*JSON_OBJECT_SIZE(14)  + 700; 
  DynamicJsonDocument doc(capacity);
  deserializeJson(doc, client);
  
  JsonObject results_0 = doc["results"][0];                          //result为数组第一行
  JsonObject results_0_location = results_0["location"];
  JsonArray results_0_daily = results_0["daily"];                    //对返回的数组进行索引
  JsonObject results_0_daily_0=results_0_daily[0];
  JsonObject results_0_daily_1=results_0_daily[1];
  JsonObject results_0_daily_2=results_0_daily[2];
  
  results_0_location_name = results_0_location["name"].as<String>();     //地点 
  results_0_daily_date_0 = results_0_daily_0["date"].as<String>();       //日期
  results_0_daily_date_1 = results_0_daily_1["date"].as<String>();       //日期
  results_0_daily_date_2 = results_0_daily_2["date"].as<String>();       //日期
  results_0_daily_highT_0 = results_0_daily_0["high"].as<int>();         //今天最高温度
  results_0_daily_highT_1 = results_0_daily_1["high"].as<int>();         //明天最高温度
  results_0_daily_highT_2 = results_0_daily_2["high"].as<int>();         //后天最高温度
  results_0_daily_humidity_0=results_0_daily_0["humidity"].as<int>();    //今天湿度
  results_0_daily_humidity_1=results_0_daily_1["humidity"].as<int>();    //明天湿度
  results_0_daily_humidity_2=results_0_daily_2["humidity"].as<int>();    //后天湿度
  results_0_daily_weather_0 = results_0_daily_0["text_day"].as<String>();//今天天气
  results_0_daily_weather_1 = results_0_daily_1["text_day"].as<String>();//明天天气
  results_0_daily_weather_2 = results_0_daily_2["text_day"].as<String>();//后天天气 
}

void httpRequest(String reqRes){
  if(millis()-wifitick<10000) return;
  wifitick=millis();                               //实现定时调用（10s）

  WiFiClient client;
  // 建立http请求信息
  String httpRequest = String("GET ") + reqRes + " HTTP/1.1\r\n" + 
                              "Host: " + host + "\r\n" + 
                              "Connection: close\r\n\r\n";

  if (client.connect(host, 80)){          // 尝试连接服务器
    Serial.println(" Success!");
    client.print(httpRequest);    // 向服务器发送http请求信息
    String status_response = client.readStringUntil('\n');    // 获取并显示服务器响应状态行
    if (client.find("\r\n\r\n")) {            // 使用find跳过HTTP响应头
      Serial.println("Found Header End. Start Parsing.");
    }
    parseInfo(client);           // 自己编写JSON函数解析心知天气响应信息
  } 
  else {
    Serial.println(" connection failed!");
  }  
  client.stop();          //断开客户端与服务器连接工作
}