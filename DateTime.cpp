#include "DateTime.h"
#include "Arduino.h"

DateTime origin();

DateTime::DateTime() {
  _year = 2000;
  _month = 1;
  _day = 1;
  _hour = 0;
  _minute = 0;
  _second = 0;
  _millisecond = 0;
}

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond) {
  _year = year;
  _month = month;
  _day = day;
  _hour = hour;
  _minute = minute;
  _second = second;
  _millisecond = millisecond;
}

DateTime::DateTime(char* date, char* time) {
  _year = 2000 + parse(date + 4, 2);
  _month = parse(date + 2, 2);
  _day = parse(date, 2);
  _hour = parse(time, 2);
  _minute = parse(time + 2, 2);
  _second = parse(time + 4, 2);
  _millisecond = parse(time + 7, 3);
}

int DateTime::year() const {
  return _year;
}

int DateTime::month() const {
  return _month;
}

int DateTime::day() const {
  return _day;
}

int DateTime::hour() const {
  return _hour;
}

int DateTime::minute() const {
  return _minute;
}

int DateTime::second() const {
  return _second;
}

int DateTime::millisecond() const {
  return _millisecond;
}

int DateTime::hourTens() const {
  return _hour/10;
}

int DateTime::hourUnits() const {
  return _hour%10;
}

int DateTime::minuteTens() const {
  return _minute/10;
}

int DateTime::minuteUnits() const {
  return _minute%10;
}

void DateTime::print() const {
  Serial.print(year());
  Serial.print('-');
  if (month() < 10) Serial.print('0');
  Serial.print(month());
  Serial.print('-');
  if (day() < 10) Serial.print('0');
  Serial.print(day());
  Serial.print(' ');
  if (hour() < 10) Serial.print('0');
  Serial.print(hour());
  Serial.print(':');
  if (minute() < 10) Serial.print('0');
  Serial.print(minute());
  Serial.print(':');
  if (second() < 10) Serial.print('0');
  Serial.print(second());
  Serial.print('.');
  if (millisecond() < 100) Serial.print('0');
  if (millisecond() < 10) Serial.print('0');
  Serial.print(millisecond());
  Serial.print(' ');
  printDayOfWeek();
}

void DateTime::add(int interval, Period period) {
  // Should accept a positive or negative interval for any period.
  if (period == Millisecond) {
    int magnitude = this->millisecond() + interval;
    interval = magnitude / 1000;
    _millisecond = magnitude % 1000;
    if (this->millisecond() < 0) {
      _millisecond += 1000;
      interval -= 1;
    }
    if (interval != 0) period = Second;
  }
  if (period == Second) {
    int magnitude = this->second() + interval;
    interval = magnitude / 60;
    _second = magnitude % 60;
    if (this->second() < 0) {
      _second += 60;
      interval -= 1;
    }
    if (interval != 0) period = Minute;
  }
  if (period == Minute) {
    int magnitude = this->minute() + interval;
    interval = magnitude / 60;
    _minute = magnitude % 60;
    if (this->minute() < 0) {
      _minute += 60;
      interval -= 1;
    }
    if (interval != 0) period = Hour;
  }
  if (period == Hour) {
    int magnitude = this->hour() + interval;
    interval = magnitude / 24;
    _hour = magnitude % 24;
    if (this->hour() < 0) {
      _hour += 24;
      interval -= 1;
    }
    if (interval != 0) period = Day;
  }
  if (period == Day) {
    while(interval) {
      int magnitude = this->day() + interval;
      int daysInMonth = this->daysInMonth();
      if (magnitude > daysInMonth) {
        _day = 1;
        add(1, DateTime::Month);
        interval = magnitude - daysInMonth - 1;
      } else if (magnitude < 1) {
        int tempDay = day();
        _day = 1;
        add(-1, DateTime::Month);
        _day = this->daysInMonth();
        interval = interval + tempDay;
      } else {
        _day += interval;
        interval = 0;
      }
    }
  }
  if (period == Month) {
    int magnitude = this->month() + interval;  // 1 -1 = 0
    interval = magnitude / 12;
    _month = magnitude % 12;
    if (!_month) {
      _month = 12;
      interval -= 1;
    }
    if (interval != 0) period = Year;
  }
  if (period == Year) _year += interval;
}

int DateTime::daysInMonth() {
  // http://en.wikipedia.org/wiki/Month
  switch (month()) {
    case 1:
      return 31;
      break;
    case 2:
      return isLeapYear() ? 29 : 28;
      break;
    case 3:
      return 31;
      break;
    case 4:
      return 30;
      break;
    case 5:
      return 31;
      break;
    case 6:
      return 30;
      break;
    case 7:
      return 31;
      break;
    case 8:
      return 31;
      break;
    case 9:
      return 30;
      break;
    case 10:
      return 31;
      break;
    case 11:
      return 30;
      break;
    case 12:
      return 31;
      break;
  }
}

int DateTime::parse(char* number, int characters) {
  int result = 0;
  int index = characters;
  for (int index = 0; index < characters; index++) {
    result *= 10;
    result += parse(*(number + index));
  }
  return result;
}

int DateTime::parse(char number) {
  return number - 48;
}

boolean DateTime::isEarlierThan(const DateTime &other) const {
  if (this->year() < other.year()) return true;
  if (this->year() > other.year()) return false;
  if (this->month() < other.month()) return true;
  if (this->month() > other.month()) return false;
  if (this->day() < other.day()) return true;
  if (this->day() > other.day()) return false;
  if (this->hour() < other.hour()) return true;
  if (this->hour() > other.hour()) return false;
  if (this->minute() < other.minute()) return true;
  if (this->minute() > other.minute()) return false;
  if (this->second() < other.second()) return true;
  if (this->second() > other.second()) return false;
  if (this->millisecond() < other.millisecond()) return true;
  if (this->millisecond() > other.millisecond()) return false;
  return false;
}

boolean DateTime::isEqualTo(const DateTime &other) const {
  return (this->year() == other.year() &&
          this->month() == other.month() &&
          this->day() == other.day() &&
          this->hour() == other.hour() &&
          this->minute() == other.minute() &&
          this->second() == other.second() &&
          this->millisecond() == other.millisecond());
}

boolean DateTime::operator == (const DateTime &other) const {
  return this->isEqualTo(other);
}

boolean DateTime::operator < (const DateTime &other) const {
  return this->isEarlierThan(other);
}

boolean DateTime::operator <= (const DateTime &other) const {
  return this->isEarlierThan(other) || this->isEqualTo(other);
}

boolean DateTime::operator > (const DateTime &other) const {
  return other.isEarlierThan(*this);
}

boolean DateTime::operator >= (const DateTime &other) const {
  return other.isEarlierThan(*this) || other.isEqualTo(*this);
}

DateTime DateTime::toLocal() {
  DateTime local(*this);
  DateTime dstStart;
  DateTime dstEnd;
  DateTime::getDaylightSavingsDates(*this, dstStart, dstEnd);
  if (this->isEarlierThan(dstStart) && (dstEnd.isEarlierThan(*this) || (dstEnd.isEqualTo(*this))))
    local.add(10, DateTime::Hour);
  else
    local.add(11, DateTime::Hour);
  return local;
}

boolean DateTime::isLeapYear() const {
  //http://en.wikipedia.org/wiki/Leap_year
  int year = this->year();
  return (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));
}

void DateTime::getDaylightSavingsDates(DateTime forDate, DateTime &utcStartDate, DateTime &utcEndDate) {
  //http://www.nsw.gov.au/daylight-saving
  int year = forDate.year();
  utcStartDate = DateTime(year, 10, 1, 16, 0, 0, 0);
  utcEndDate = DateTime(year, 4, 1, 16, 0, 0, 0);
  if (utcStartDate.dayOfWeek() == 0)
    utcStartDate.add(-1, DateTime::Day);
  else
    utcStartDate.add(6 - utcStartDate.dayOfWeek(), DateTime::Day);
  if (utcEndDate.dayOfWeek() == 0)
    utcEndDate.add(-1, DateTime::Day);
  else
    utcEndDate.add(6 - utcEndDate.dayOfWeek(), DateTime::Day);
}

DateTime::DayOfWeek DateTime::dayOfWeek() const {
  //http://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week
  // Calculating only for the 2000-2099 century
  int century = 6;
  int monthFactors[12] = { 0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5 };
  int monthFactorsLeap[12] = { 6, 2, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5 };
  int twoDigitYear = this->year()%100;
  int yearOverFour = twoDigitYear/4;
  int month = this->isLeapYear() ? monthFactorsLeap[this->month() - 1] : monthFactors[this->month() - 1];
  int sum = century + twoDigitYear + yearOverFour + month + this->day();
  return (DateTime::DayOfWeek)(sum % 7);
}

boolean DateTime::isApproximatelyEqualTo(const DateTime &other) const {
  // The goal is to judge if two DateTimes are close, within seconds.
  // If one date were one millisecond to midnight before new year's eve,
  // and the other date were the stroke of midnight, you still couldn't
  // even use years to tell how close two DateTimes are.
  DateTime alpha;
  DateTime alphaOne;
  DateTime omega;
  if (this->isEarlierThan(other)) {
    alpha = (*this);
    omega = other;
  } else {
    alpha = other;
    omega = (*this);
  }
  alphaOne = alpha;
  alphaOne.add(1, DateTime::Day);
  if (((alpha.year() != omega.year())
    || (alpha.month() != omega.month())
    || (alpha.day() != omega.day())) // not same day
    && ((alphaOne.year() != omega.year())
    || (alphaOne.month() != omega.month())
    || (alphaOne.day() != omega.day()))) // not consecutive days
    return false;
    if ((omega.totalMilliseconds() - alpha.totalMilliseconds()) > 2000) return false;
    return true;
}

unsigned long DateTime::totalMilliseconds() const {
  unsigned long result = 0;
  result += millisecond();
  result += second() * 1000UL;
  result += minute() * 60UL * 1000;
  result += hour() * 60UL * 60 * 1000;
  return result;
}

void DateTime::printDayOfWeek() const {
  switch (this->dayOfWeek())
  {
    case DateTime::Sunday:
      Serial.print("Sunday");
      break;
    case DateTime::Monday:
      Serial.print("Monday");
      break;
    case DateTime::Tuesday:
      Serial.print("Tuesday");
      break;
    case DateTime::Wednesday:
      Serial.print("Wednesday");
      break;
    case DateTime::Thursday:
      Serial.print("Thursday");
      break;
    case DateTime::Friday:
      Serial.print("Friday");
      break;
    case DateTime::Saturday:
      Serial.print("Saturday");
      break;
  }
}

String& DateTime::toString() {
  //http://arduino.cc/en/Reference/StringObject
  static String* output;
  if (output) delete(output);
  output = new String();
  if (_day < 10) *output += '0';
  *output += _day;
  *output += '/';
  if (_month < 10) *output += '0';
  *output += _month;
  *output += '/';
  *output += _year;
  *output += ' ';
  if (_hour < 10) *output += '0';
  *output += _hour;
  *output += ':';
  if (_minute < 10) *output += '0';
  *output += _minute;
  *output += ':';
  if (_second < 10) *output += '0';
  *output += _second;
  *output += '.';
  if (_millisecond < 100) *output += '0';
  if (_millisecond < 10) *output += '0';
  *output += _millisecond;
  return *output;
}
