#ifndef DateTime_h
#define DateTime_h

#include "Arduino.h"

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
    void printDayOfWeek() const;
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
};

#endif
