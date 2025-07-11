#include "time_waiting.h"
#include "fake_rtc.h"
#include "rtc.h"
#include "overworld.h"
#include "main.h"

void WaitTillMorning()
{
    if(GetTimeOfDay() == TIME_MORNING)
        return; // Already morning, no need to wait
    FakeRtc_ForwardTimeTo(MORNING_HOUR_MID, 0, 0);
    SetMainCallback2(CB2_LoadMap);
}
void WaitTillDay()
{
    if(GetTimeOfDay() == TIME_DAY)
        return; // Already day, no need to wait
    FakeRtc_ForwardTimeTo(DAY_HOUR_MID, 0, 0);
    SetMainCallback2(CB2_LoadMap);
}
void WaitTillEvening()
{
    if(GetTimeOfDay() == TIME_EVENING)
        return; // Already evening, no need to wait
    FakeRtc_ForwardTimeTo(EVENING_HOUR_MID, 0, 0);
    SetMainCallback2(CB2_LoadMap);
}
void WaitTillNight()
{
    if(GetTimeOfDay() == TIME_NIGHT)
        return; // Already night, no need to wait
    FakeRtc_ForwardTimeTo(NIGHT_HOUR_MID, 0, 0);
    SetMainCallback2(CB2_LoadMap);
}