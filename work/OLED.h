#ifndef __OLED_H
#define __OLED_H



void OLED_Init();
void OLED_Display();
void OLED_Display1();
void Page_change();


extern int results_0_daily_highT_0;
extern int results_0_daily_highT_1;
extern int results_0_daily_highT_2;

extern int results_0_daily_humidity_0;
extern int results_0_daily_humidity_1;
extern int results_0_daily_humidity_2;

extern String results_0_daily_weather_0;
extern String results_0_daily_weather_1;
extern String results_0_daily_weather_2;
extern String results_0_location_name;

extern String Year;
extern String Month;
extern String Day;
extern String Hour;
extern String Minute;

extern String results_0_daily_date_0;
extern String results_0_daily_date_1;
extern String results_0_daily_date_2;
#endif