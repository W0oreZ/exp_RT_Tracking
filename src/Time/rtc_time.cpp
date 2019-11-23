#include "rtc_time.h"

//STATE VARIABLES
const char * weekdayName[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
const char * monthName[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

char     buffer[12];
char     comType       = '-';
uint32_t epochTime;

DateVar date;
TimeVar time;

STM32F1_RTC rtc;

void V2X_RTC::setup()
{
  Serial.println("RTC SETUP");
  rtc.begin();
}

void V2X_RTC::loop()
{
  epochTime = rtc.getTime();
  rtc.epochToTime(epochTime, time);
  rtc.epochToDate(epochTime, date);
  printDate();
  Serial.print(" ");
  printTime(true);
  Serial.println();
  vTaskDelay(500/portTICK_PERIOD_MS);
}

void V2X_RTC::main(void* p){
  Serial.println("RTC TASK Started !");
  V2X_RTC::setup();

  for(;;)
  {
    V2X_RTC::loop();

    vTaskDelay(1);
  }
}

void V2X_RTC::printDate() {
  Serial.print(weekdayName[date.weekday]);
  Serial.print(", ");
  Serial.print(date.day);
  Serial.print(" ");
  Serial.print(monthName[date.month - 1]);
  Serial.print(" ");
  Serial.print(date.year);
}

void V2X_RTC::printTime() {
  printTime(false);
}

void V2X_RTC::printTime(bool ms) {
  unsigned short int h = time.hours;

  print2Digits(h);
  Serial.print(":");
  print2Digits(time.minutes);
  Serial.print(":");
  print2Digits(time.seconds);
  if (ms) {
    Serial.print(".");
    print3Digits(rtc.getMilliseconds());
  }
}

void V2X_RTC::print2Digits(uint8_t n) {
  if (n < 10)
    Serial.print(0);
  Serial.print(n);
}

void V2X_RTC::print3Digits(uint16_t n) {
  if (n < 100) {
    Serial.print(0);
    print2Digits(n);
  }
  else
    Serial.print(n);
}