#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include "OLED.h"
#include "tubiao.h"
#include "hanzi.h"
#include <string.h>
#include <U8g2lib.h>
String weather;
String temperature;
String humidity;
extern String data;
uint8_t page = 0;
uint8_t color = 0;
unsigned int pagetick=0;
uint8_t t = 0;
uint8_t h = 0;
char LineString[100];
// 定义 OLED屏幕的分辨率
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE); //速度慢
void OLED_Init()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);      // 设置OLED的I2C地址
  display.clearDisplay();                         // 清空屏幕
  display.setTextSize(1);                         // 设置字体大小
  display.setTextColor(SSD1306_WHITE);            // 设置字体颜色
  // display.display();                              // 使更改的显示生效
  u8g2.begin();
  u8g2.enableUTF8Print();  // enable UTF8 support for the Arduino print() function
}

void Weather_Judge(String Weather)
{
  sprintf(LineString,"%s",Weather);
  if(strcmp(LineString,"Overcast")==0)
  {
    display.drawBitmap(0,16, yin, 48, 48,1);
    display.drawBitmap(88,16, yin_zn, 16, 16,1);
  }
  else if(strcmp(LineString,"Cloudy")==0)
  {
    display.drawBitmap(0,16, duoyun, 48, 48,1);
    display.drawBitmap(88,16, duo_zn, 16, 16,1);
    display.drawBitmap(104,16, yun_zn, 16, 16,1);
  }
  else if(strcmp(LineString,"Sunny")==0)
  {
    display.drawBitmap(0,16, qing, 48, 48,1);
    display.drawBitmap(88,16, qing_zn, 16, 16,1);
  }
  else if(strcmp(LineString,"Light rain")==0)
  {
    display.drawBitmap(0,16, light_rain, 48, 48,1);
    display.drawBitmap(88,16, xiao_zn, 16, 16,1);
    display.drawBitmap(104,16, yu_zn, 16, 16,1);
  }
  else if(strcmp(LineString,"Moderate rain")==0)
  {
    display.drawBitmap(0,16, middle_rain, 48, 48,1);
    display.drawBitmap(88,16, zhong_zn, 16, 16,1);
    display.drawBitmap(104,16, yu_zn, 16, 16,1);
  }
  else if(strcmp(LineString,"Heavy rain")==0)
  {
    display.drawBitmap(0,16, heavy_rain, 48, 48,1);
    display.drawBitmap(88,16, da_zn, 16, 16,1);
    display.drawBitmap(104,16, yu_zn, 16, 16,1);
  }
  else if(strcmp(LineString,"Thundershower")==0)              //Thundershower写入LineString会乱码，未解决
  {
    display.drawBitmap(0,16, thunder_rain, 48, 48,1);
    display.drawBitmap(88,16, bao_zn, 16, 16,1);
    display.drawBitmap(104,16, yu_zn, 16, 16,1);
  }
  else if(strcmp(LineString,"Light snow")==0)
  {
    display.drawBitmap(0,16, light_snow, 48, 48,1);
    display.drawBitmap(88,16, xiao_zn, 16, 16,1);
    display.drawBitmap(104,16, xue_zn, 16, 16,1);
  }
  else if(strcmp(LineString,"Moderate snow")==0)
  {
    display.drawBitmap(0,16, middle_snow, 48, 48,1);
    display.drawBitmap(88,16, zhong_zn, 16, 16,1);
    display.drawBitmap(104,16, xue_zn, 16, 16,1);
  }
  else if(strcmp(LineString,"Heavy snow")==0)
  {
    display.drawBitmap(0,16, heavy_snow, 48, 48,1);
    display.drawBitmap(88,16, da_zn, 16, 16,1);
    display.drawBitmap(104,16, xue_zn, 16, 16,1);
  }
  else if(strcmp(LineString,"Foggy")==0)
  {
    display.drawBitmap(0,16, Foggy, 48, 48,1);
    display.drawBitmap(88,16, wu_zn, 16, 16,1);
  }
  else if(strcmp(LineString,"Haze")==0)
  {
    display.drawBitmap(0,16, Haze, 48, 48,1);
    display.drawBitmap(88,16, mai_zn, 16, 16,1);
  }
  else if(strcmp(LineString,"Dust")==0)
  {
    display.drawBitmap(0,16, Dust, 48, 48,1);
    display.drawBitmap(88,16, yang_zn, 16, 16,1);
    display.drawBitmap(104,16, chen_zn, 16, 16,1);
  }
  else if(strcmp(LineString,"Duststorm")==0)
  {
    display.drawBitmap(0,16, Duststorm, 48, 48,1);
    display.drawBitmap(88,16, sha_zn, 16, 16,1);
    display.drawBitmap(104,16, chen_zn, 16, 16,1);
  }
}
//天气温度和湿度使用
void Number_Handle(int number,int offset,int offset1)
{
  static unsigned char high,low;
  high=number/10;
  low=number%10;
  switch(high)
  {
    case 0:display.drawBitmap(88+offset1,16+offset, ling_zn, 8, 16,1);break;
    case 1:display.drawBitmap(88+offset1,16+offset, yi_zn, 8, 16,1);break;
    case 2:display.drawBitmap(88+offset1,16+offset, er_zn, 8, 16,1);break;
    case 3:display.drawBitmap(88+offset1,16+offset, san_zn, 8, 16,1);break;
    case 4:display.drawBitmap(88+offset1,16+offset, si_zn, 8, 16,1);break;
    case 5:display.drawBitmap(88+offset1,16+offset, wu1_zn, 8, 16,1);break;
    case 6:display.drawBitmap(88+offset1,16+offset, liu_zn, 8, 16,1);break;
    case 7:display.drawBitmap(88+offset1,16+offset, qi1_zn, 8, 16,1);break;
    case 8:display.drawBitmap(88+offset1,16+offset, ba_zn, 8, 16,1);break;
    case 9:display.drawBitmap(88+offset1,16+offset, jiu_zn, 8, 16,1);break;
  }
  switch(low)
  {
    case 0:display.drawBitmap(96+offset1,16+offset, ling_zn, 8, 16,1);break;
    case 1:display.drawBitmap(96+offset1,16+offset, yi_zn, 8, 16,1);break;
    case 2:display.drawBitmap(96+offset1,16+offset, er_zn, 8, 16,1);break;
    case 3:display.drawBitmap(96+offset1,16+offset, san_zn, 8, 16,1);break;
    case 4:display.drawBitmap(96+offset1,16+offset, si_zn, 8, 16,1);break;
    case 5:display.drawBitmap(96+offset1,16+offset, wu1_zn, 8, 16,1);break;
    case 6:display.drawBitmap(96+offset1,16+offset, liu_zn, 8, 16,1);break;
    case 7:display.drawBitmap(96+offset1,16+offset, qi1_zn, 8, 16,1);break;
    case 8:display.drawBitmap(96+offset1,16+offset, ba_zn, 8, 16,1);break;
    case 9:display.drawBitmap(96+offset1,16+offset, jiu_zn, 8, 16,1);break;
  }
}
//室内温度和湿度使用
void Number_Handle_1(int number,int offset,int offset1)
{
  static unsigned char high,low;
  high=number/10;
  low=number%10;
  switch(high)
  {
    case 0:display.drawBitmap(64+offset1,24+offset, ling_zn_1, 16, 32,1);break;
    case 1:display.drawBitmap(64+offset1,24+offset, yi_zn_1, 16, 32,1);break;
    case 2:display.drawBitmap(64+offset1,24+offset, er_zn_1, 16, 32,1);break;
    case 3:display.drawBitmap(64+offset1,24+offset, san_zn_1, 16, 32,1);break;
    case 4:display.drawBitmap(64+offset1,24+offset, si_zn_1, 16, 32,1);break;
    case 5:display.drawBitmap(64+offset1,24+offset, wu1_zn_1, 16, 32,1);break;
    case 6:display.drawBitmap(64+offset1,24+offset, liu_zn_1, 16, 32,1);break;
    case 7:display.drawBitmap(64+offset1,24+offset, qi1_zn_1, 16, 32,1);break;
    case 8:display.drawBitmap(64+offset1,24+offset, ba_zn_1, 16, 32,1);break;
    case 9:display.drawBitmap(64+offset1,24+offset, jiu_zn_1, 16, 32,1);break;
  }
  switch(low)
  {
    case 0:display.drawBitmap(80+offset1,24+offset, ling_zn_1, 16, 32,1);break;
    case 1:display.drawBitmap(80+offset1,24+offset, yi_zn_1, 16, 32,1);break;
    case 2:display.drawBitmap(80+offset1,24+offset, er_zn_1, 16, 32,1);break;
    case 3:display.drawBitmap(80+offset1,24+offset, san_zn_1, 16, 32,1);break;
    case 4:display.drawBitmap(80+offset1,24+offset, si_zn_1, 16, 32,1);break;
    case 5:display.drawBitmap(80+offset1,24+offset, wu1_zn_1, 16, 32,1);break;
    case 6:display.drawBitmap(80+offset1,24+offset, liu_zn_1, 16, 32,1);break;
    case 7:display.drawBitmap(80+offset1,24+offset, qi1_zn_1, 16, 32,1);break;
    case 8:display.drawBitmap(80+offset1,24+offset, ba_zn_1, 16, 32,1);break;
    case 9:display.drawBitmap(80+offset1,24+offset, jiu_zn_1, 16, 32,1);break;
  }
}

void OLED_Display()
{
  // if(millis()-pagetick<5000) return;  //每5s切换一次界面
  // pagetick=millis();
  //Serial.println(color);
  if(page==0)
  {
    display.clearDisplay();
    display.setCursor(88,0);
    sprintf(LineString,"%s:%s",Hour,Minute);               //时间
    display.print(LineString);
    sprintf(LineString,"%s",results_0_daily_date_0);        //日期
    display.setCursor(0,0);
    display.print(LineString);
    Number_Handle(results_0_daily_highT_0,16,0);
    Number_Handle(results_0_daily_humidity_0,32,0);
    Weather_Judge(results_0_daily_weather_0);
    display.drawBitmap(48,16, tian_zn, 16, 16,1);          //天气
    display.drawBitmap(64,16, qi_zn, 16, 16,1);
    display.drawBitmap(80,16, maohao, 8, 16,1);
    display.drawBitmap(48,32, wen_zn, 16, 16,1);           //温度
    display.drawBitmap(64,32, du_zn, 16, 16,1);
    display.drawBitmap(80,32, maohao, 8, 16,1);
    display.drawBitmap(104,32, du_flag, 8, 16,1);
    display.drawBitmap(112,32, C_zn, 8, 16,1);
    display.drawBitmap(48,48, shi_zn, 16, 16,1);           //湿度
    display.drawBitmap(64,48, du_zn, 16, 16,1);
    display.drawBitmap(80,48, maohao, 8, 16,1);
    display.drawBitmap(104,48, baifenhao, 8, 16,1);
    display.display();
  }
  else if(page==1)//天气
  {
    display.clearDisplay();
    Weather_Judge(results_0_daily_weather_0);
    display.display();
  }
  else if(page==2)//温度
  {
    display.clearDisplay();
    display.drawBitmap(0,16, temper, 48, 48,1);
    Number_Handle_1(results_0_daily_highT_0,0,0);
    display.drawBitmap(96,24, du_1, 16, 32,1);
    display.display();
  }
  else if(page==3)//湿度
  {
    display.clearDisplay();
    display.drawBitmap(0,16, humidi, 48, 48,1);
    Number_Handle_1(results_0_daily_humidity_0,0,0);
    display.drawBitmap(96,24, baifenhao_1, 16, 32,1);
    display.display();
  }
  else if(page==4)//信息
  {
    u8g2.setFont(u8g2_font_wqy12_t_gb2312); 
    u8g2.setFontDirection(0);
    u8g2.firstPage();
    do {
      u8g2.setCursor(30, 14);
      u8g2.print("备忘录"); 
      u8g2.setCursor(0, 28);
      u8g2.print(data); 
   } while ( u8g2.nextPage() );
    //delay(5000);
  }
}

void Page_change()
{
  switch(color)
  {
    case 0:
     {
      digitalWrite(12, 0); 
      delay(1);
      digitalWrite(13, 0);  
      delay(1);    
      digitalWrite(14, 0);  
      delay(1);
      break;
    }
    case 1:   
    {      
      digitalWrite(12, 0);  
      delay(1);     
      digitalWrite(13, 0);   
      delay(1);   
      digitalWrite(14, 1);   
      delay(1);
      break; 
    }    
    case 2:   
    {      
      digitalWrite(12, 0);   
      delay(1);    
      digitalWrite(13, 1);      
      delay(1);
      digitalWrite(14, 0);  
      delay(1);
      break;  
    }
    case 3:
    {
      digitalWrite(12, 1); 
      delay(1);
      digitalWrite(13, 0);
      delay(1);
      digitalWrite(14, 0);
      delay(1);
      break;
    }
    default:
    break;
  }
}