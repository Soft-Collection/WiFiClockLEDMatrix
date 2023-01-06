#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "ClockLEDMatrixDisplay.h"
#include "RTC.h"
#include "Config.h"
#include "Period.h"

RTC rtc;
ClockLEDMatrixDisplay clmd;
Period period100_1(NULL, 100, true);
Period period100_2(NULL, 100, true);

static void on_period100_1(void* instance);
static void on_period100_2(void* instance);

void setup() 
{
  Serial.begin(115200);
  rtc.Init();
  clmd.Init();
  period100_1.AddOnPeriodExpiredHandler(on_period100_1);
  period100_2.AddOnPeriodExpiredHandler(on_period100_2);
}
void loop() 
{
   int8_t hour;
   int8_t minute;
   int8_t second;
   rtc.GetTime(hour, minute, second);
   uint32_t TC = millis();
   clmd.Check();
   bool isUpdated = rtc.GetIsUpdated();
   if (!isUpdated)
   {
      period100_1.Check(TC); //Points only.
   }
   else
   {
      period100_2.Check(TC); //Time and points.
   }
}
void on_period100_1(void* instance)
{
   clmd.DisplayNotUpdated();
}
void on_period100_2(void* instance)
{
   int8_t hour;
   int8_t minute;
   int8_t second;
   int8_t day;
   int8_t month;
   int8_t year;
   rtc.GetTime(hour, minute, second);
   rtc.GetDate(day, month, year);
   clmd.DisplayTime(hour, minute, day, month, millis() % 1000 > 500);
}
