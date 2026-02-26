#include "arduino.h"
#include "DateTime.h"

int tests, fails;

void testDayName(DateTime::Day day, String dayName) {

  Serial.println("  test dayName()");
  
  tests++;
  String name = String();
  Serial.print(dayName);
  Serial.print(" =? ");
  DateTime::dayName(day, name);
  Serial.print(name);
  if (name != dayName) {
    fails++;
    Serial.print(" FAIL");
  }
  Serial.println();
}

void testDayNameShort(DateTime::Day day, String dayName) {

  Serial.println("  test dayNameShort()");
  
  tests++;
  String name = String();
  Serial.print(dayName);
  Serial.print(" =? ");
  DateTime::dayNameShort(day, name);
  Serial.print(name);
  if (name != dayName) {
    fails++;
    Serial.print(" FAIL");
  }
  Serial.println();
}

void testDateTime() {
  
  Serial.println("    Testing ...");
  testDayName(DateTime::Day::Error, "Error");       // 1st enum
  testDayName(DateTime::Day::Sunday, "Sunday");     // 1st useful enum
  testDayName(DateTime::Day::Saturday, "Saturday"); // last enum
  testDayNameShort(DateTime::Day::Error, "Err");    // 1st enum
  testDayNameShort(DateTime::Day::Sunday, "Sun");   // 1st useful enum
  testDayNameShort(DateTime::Day::Saturday, "Sat"); // last enum

  // DateTime::dayNameShort(DateTime::Day::Sunday, name);
  // Serial.println(name);
  // DateTime::monthName(DateTime::Month::January, name);
  // Serial.println(name);
  // DateTime::monthNameShort(DateTime::Month::January, name);
  // Serial.println(name);

  Serial.println();
  Serial.print(tests);
  Serial.print(" test completed. ");
  Serial.print(fails);
  Serial.print(" failures. ");
  Serial.print((tests - fails)/(float) tests * 100);
  Serial.println("% pass rate.");
  if (fails) Serial.println("\nFAIL!");
}