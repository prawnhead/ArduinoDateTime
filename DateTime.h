#ifndef DateTime_h
#define DateTime_h

#include "Arduino.h"
#include <avr/pgmspace.h>

const char monthNames[] PROGMEM = "Error\0January\0February\0March\0April\0May\0June\0July\0August\0September\0October\0November\0December";
const byte monthNameIndex[] = {0, 6, 14, 23, 29, 35, 39, 44, 49, 56, 66, 74, 83};
const char monthNamesShort[] PROGMEM = "Err\0Jan\0Feb\0Mar\0Apr\0May\0Jun\0Jul\0Aug\0Sep\0Oct\0Nov\0Dec";
const char weekdayNames[] PROGMEM = "Error\0Sunday\0Monday\0Tuesday\0Wednesday\0Thursday\0Friday\0Saturday";
const byte weekdayNameIndex[] = {0, 6, 13, 20, 28, 38, 47, 54};
const char weekdayNamesShort[] PROGMEM = "Err\0Sun\0Mon\0Tue\0Wed\0Thu\0Fri\0Sat";
class DateTime
{
  private:
    int _year, _month, _day, _hour, _minute, _second, _millisecond;
    int parse(char number);
    int parse(char* number, int characters);

  public:
    enum Period { Year, Month, Day, Hour, Minute, Second, Millisecond };
    enum DayOfWeek { Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday };

    DateTime();
    DateTime(char* date, char* time);
    DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond);

    int year() const;
    int month() const;
    int day() const;
    int hour() const;
    int minute() const;
    int second() const;
    int millisecond() const;
    
    int hourTens() const;
    int hourUnits() const;
    int minuteTens() const;
    int minuteUnits() const;

    void add(int interval, Period period);
    void print() const;
    int daysInMonth();
    unsigned long totalMilliseconds() const;
    DateTime::DayOfWeek dayOfWeek() const;
    DateTime toLocal();
    boolean isLeapYear() const;
    boolean isApproximatelyEqualTo(const DateTime &other) const;
    
    boolean isEarlierThan(const DateTime &other) const;
    boolean isEqualTo(const DateTime &other) const;
    
    static void getDaylightSavingsDates(DateTime forDate, DateTime &utcStartDate, DateTime &utcEndDate);

    boolean operator == (const DateTime &other) const;
    boolean operator < (const DateTime &other) const;
    boolean operator <= (const DateTime &other) const;
    boolean operator > (const DateTime &other) const;
    boolean operator >= (const DateTime &other) const;
    
    String& toString();
    String& monthToString();
    String& monthToShortString();
    String& dayOfWeekToString();
    String& dayOfWeekToShortString();
};

#endif
