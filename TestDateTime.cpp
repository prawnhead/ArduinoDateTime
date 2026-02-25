#include "arduino.h"
#include "DateTime.h"

void testDateTime() {
  
  String name = String();
  DateTime::dayName(DateTime::Day::Sunday, name);
  Serial.println(name);
  DateTime::dayNameShort(DateTime::Day::Sunday, name);
  Serial.println(name);
  DateTime::monthName(DateTime::Month::January, name);
  Serial.println(name);
  DateTime::monthNameShort(DateTime::Month::January, name);
  Serial.println(name);

}