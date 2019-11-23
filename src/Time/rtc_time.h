#ifndef v2x_rtc_time_h
#define v2x_rtc_time_h

#include "globals.h"

#include <src/vendor/RTC/stm32f1_rtc.h>

#define ALARM_ACTIVE_CYCLE 30

#define FLAGS_REGISTER  1

#define HIJRI_MODE_BIT  1
#define HOUR_12_BIT     2
#define ALARM_ENTRY_BIT 3

#define HIJRI_MODE_FLAG  (1 << HIJRI_MODE_BIT)
#define HOUR_12_FLAG     (1 << HOUR_12_BIT)
#define ALARM_ENTRY_FLAG (1 << ALARM_ENTRY_BIT)

#define IS_HIJRI_MODE(x)      ((x.getBackupRegister(FLAGS_REGISTER) & HIJRI_MODE_FLAG)  == HIJRI_MODE_FLAG)
#define IS_HOUR_12(x)         ((x.getBackupRegister(FLAGS_REGISTER) & HOUR_12_FLAG)     == HOUR_12_FLAG)
#define IS_ALARM_ENTRY(x)     ((x.getBackupRegister(FLAGS_REGISTER) & ALARM_ENTRY_FLAG) == ALARM_ENTRY_FLAG)

namespace V2X_RTC
{
  void print3Digits(uint16_t n);
  void print2Digits(uint8_t n);
  void printTime(bool ms);
  void printTime();
  void printDate();

  //TASK CORE FUNCTIONS
  void main(void* p);
  void setup();
  void loop();
}

#endif