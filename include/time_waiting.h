#ifndef GUARD_TIME_WAITING_H
#define GUARD_TIME_WAITING_H

#include "constants/time_waiting.h"
#include "rtc.h"

void WaitTillMorning(void);
void WaitTillDay(void);
void WaitTillEvening(void);
void WaitTillNight(void);
void QOLMenu_CalculateTime(void);
enum TimeOfDay AccurateTimeOfDay(void);

#endif // GUARD_TIME_WAITING_H
