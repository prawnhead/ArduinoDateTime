#ifndef DateTime_h
#define DateTime_h

#include "Arduino.h"
// #include <avr/pgmspace.h>

/*  TODO: Need to implement callback functions for dstStart() and dstEnd()
 */


/* TODO: Edit
 * Notes:
 * Each DateTime object can store ONLY ONE associated string. When now.monthToString() is called,
 * the object now maintains a String containing the name of the current month. When dayOfWeekToString()
 * is called, the same String object is reused and the string containing the month is deleted and now
 * holds the name of the day of the week.
 */

const char monthNames[] = "Error\0January\0February\0March\0April\0May\0June\0July\0August\0September\0October\0November\0December";
const int monthNameIndex[] = { 0, 6, 14, 23, 29, 35, 39, 44, 49, 56, 66, 74, 83 };
const char dayNames[] = "Error\0Sunday\0Monday\0Tuesday\0Wednesday\0Thursday\0Friday\0Saturday";
const byte dayNameIndex[] = { 0, 6, 13, 20, 28, 38, 47, 54 };

class DateTime {

  // Alias for function prototype that returns DateTime for (int year, bool Forward)
  // This is a callback so DateTime can ask for daylight savings DateTimes.
  using dstCallbackFunction = std::function<DateTime(int, bool)>;

private:
  int _year, _month, _day, _hour, _minute, _second, _millisecond;
  dstCallbackFunction dstDate;
  unsigned long lastMillis;

  // int parse(char number);
  // int parse(char* number, int characters);

  // String& getProgMemString(const char *progMemString, byte index);

public:
  // C++11 Scoped Enums
  enum class Period { Year,
                      Month,
                      Day,
                      Hour,
                      Minute,
                      Second,
                      Millisecond };
  enum class Day { Error,
                   Sunday,
                   Monday,
                   Tuesday,
                   Wednesday,
                   Thursday,
                   Friday,
                   Saturday };
  enum class Month { Error,
                     January,
                     February,
                     March,
                     April,
                     May,
                     June,
                     July,
                     August,
                     September,
                     October,
                     November,
                     December };
  enum class TimeSource { Compiler,
                          NMEA,
                          NTP,
                          Epoch };
  enum class DST { forward,
                   backward };

  DateTime();
  // DateTime(char* date, char* time, DateTime::TimeSource source);
  DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond);

  int year() const;
  int month() const;
  int day() const;
  int hour() const;
  int minute() const;
  int second() const;
  int millisecond() const;

  static void dayName(int dayOfWeek, String &name);
  static void dayName(Day day, String &name);
  static void dayNameShort(Day day, String &name);
  static void monthName(int dayOfMonth, String &name);
  static void monthName(Month month, String &name);
  static void monthNameShort(Month month, String &name);
  static Month toMonth(int month);
  static bool isLeapYear(int year);
  static int daysInMonth(Month month, int year);

  /* The logic to calculate dates and times for daylight savings time varies by country/state/province/region and is beyond the scope of this class. We'll achieve that functionality by allowing the user to write their own functions and register these as callback functions. It is intended they will only need to be called if the year changes. On each setting of the year, DateTime will compare the current to previous year and, when different, call both DST functions. eg:
  DateTime dstForward(int year);
  DateTime dstBackward(int year);
  TODO: Complete assignment and operation testing
  */
  static void setDstCallbackFunction(DST dstType, dstCallbackFunction func);

  /* DateTime can be used like a clock. Each time tick() is called, the datetime will be incremented by the number of elapsed milliseconds since the last call. As long as tick() is called periodically (at least every 49 days) the internal time will not slip. Note: Before tick() is called, the clock is out of date.
   */
  void tick();

  // int hourTens() const;
  // int hourUnits() const;
  // int minuteTens() const;
  // int minuteUnits() const;

  // void add(int interval, Period period);
  // byte monthFromString(char* string);
  // unsigned long totalMilliseconds() const;
  // DateTime::DayOfWeek dayOfWeek() const;
  // DateTime toLocal();
  // boolean isLeapYear() const;
  // boolean isApproximatelyEqualTo(const DateTime &other) const;

  // boolean isEarlierThan(const DateTime &other) const;
  // boolean isEqualTo(const DateTime &other) const;

  // static void getDaylightSavingsDates(DateTime forDate, DateTime &utcStartDate, DateTime &utcEndDate);

  // boolean operator == (const DateTime &other) const;
  // boolean operator < (const DateTime &other) const;
  // boolean operator <= (const DateTime &other) const;
  // boolean operator > (const DateTime &other) const;
  // boolean operator >= (const DateTime &other) const;

  // String& toString();
  // String& monthToString();
  // String& monthToString(int month);
  // String& monthToShortString();
  // String& monthToShortString(int month);
  // String& dayOfWeekToString();
  // String& dayOfWeekToString(DayOfWeek day);
  // String& dayOfWeekToShortString();
  // String& dayOfWeekToShortString(DayOfWeek day);
};

#endif
