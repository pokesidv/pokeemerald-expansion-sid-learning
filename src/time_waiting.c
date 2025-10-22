#include "time_waiting.h"
#include "fake_rtc.h"
#include "rtc.h"
#include "overworld.h"
#include "main.h"
#include "string_util.h"
#include "event_data.h"

void WaitTillMorning()
{
    if(AccurateTimeOfDay() == TIME_MORNING)
        return; // Already morning, no need to wait
    FakeRtc_ForwardTimeTo(MORNING_HOUR_MID, 0, 0);
    SetMainCallback2(CB2_LoadMap);
}
void WaitTillDay()
{
    if(AccurateTimeOfDay() == TIME_DAY)
        return; // Already day, no need to wait
    FakeRtc_ForwardTimeTo(DAY_HOUR_MID, 0, 0);
    SetMainCallback2(CB2_LoadMap);
}
void WaitTillEvening()
{
    if(AccurateTimeOfDay() == TIME_EVENING)
        return; // Already evening, no need to wait
    FakeRtc_ForwardTimeTo(EVENING_HOUR_MID, 0, 0);
    SetMainCallback2(CB2_LoadMap);
}
void WaitTillNight()
{
    if(AccurateTimeOfDay() == TIME_NIGHT)
        return; // Already night, no need to wait
    FakeRtc_ForwardTimeTo(NIGHT_HOUR_MID, 0, 0);
    SetMainCallback2(CB2_LoadMap);
}

static const u8 *const gTimeOfDayStringsTable[TIMES_OF_DAY_COUNT] = {
    COMPOUND_STRING("Morning"),
    COMPOUND_STRING("Day"),
    COMPOUND_STRING("Evening"),
    COMPOUND_STRING("Night"),
};

void QOLMenu_CalculateTime()
{
    
    s8 hours;
    s8 minutes;
    
    if (OW_USE_FAKE_RTC)
    {
        struct SiiRtcInfo *rtc = FakeRtc_GetCurrentTime();
        hours = rtc->hour;
        minutes = rtc->minute;
    }
    else
    {
        RtcCalcLocalTime();
        hours = gLocalTime.hours;
        minutes = gLocalTime.minutes;
    }
    ConvertIntToDecimalStringN(gStringVar2, hours, STR_CONV_MODE_LEFT_ALIGN, 3);
    ConvertIntToDecimalStringN(gStringVar3, minutes, STR_CONV_MODE_LEADING_ZEROS, 2);

    enum TimeOfDay timeOfDay;
    if(IsBetweenHours(hours, MORNING_HOUR_BEGIN, MORNING_HOUR_END))
    {
        timeOfDay = TIME_MORNING;
    }
    else if(IsBetweenHours(hours, DAY_HOUR_BEGIN, DAY_HOUR_END))
    {
        timeOfDay = TIME_DAY;
    }
    else if(IsBetweenHours(hours, EVENING_HOUR_BEGIN, EVENING_HOUR_END))
    {
        timeOfDay = TIME_EVENING;
    }
    else
    {
        timeOfDay = TIME_NIGHT;

    }
    StringExpandPlaceholders(gStringVar1, gTimeOfDayStringsTable[timeOfDay]);
    gSpecialVar_0x8000 = timeOfDay;
}

enum TimeOfDay AccurateTimeOfDay()
{
    
    s8 hours;
    
    if (OW_USE_FAKE_RTC)
    {
        struct SiiRtcInfo *rtc = FakeRtc_GetCurrentTime();
        hours = rtc->hour;
    }
    else
    {
        RtcCalcLocalTime();
        hours = gLocalTime.hours;
    }

    if(IsBetweenHours(hours, MORNING_HOUR_BEGIN, MORNING_HOUR_END))
    {
        return TIME_MORNING;
    }
    else if(IsBetweenHours(hours, DAY_HOUR_BEGIN, DAY_HOUR_END))
    {
        return TIME_DAY;
    }
    else if(IsBetweenHours(hours, EVENING_HOUR_BEGIN, EVENING_HOUR_END))
    {
        return TIME_EVENING;
    }
    else
    {
        return TIME_NIGHT;

    }
}