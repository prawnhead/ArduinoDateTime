#include "DateTime.h"

int tests = 0;
int fails = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("setup()");
  Serial.println("Test create any DateTime");
  DateTime test = DateTime(2000, 1, 1, 1, 1, 1, 1);
  testDateTime(test, 2000, 1, 1, 1, 1, 1, 1);
  Serial.println("Test add every interval");
  test.add(1, DateTime::Millisecond);
  testDateTime(test, 2000, 1, 1, 1, 1, 1, 2);
  test.add(1, DateTime::Second);
  testDateTime(test, 2000, 1, 1, 1, 1, 2, 2);
  test.add(1, DateTime::Minute);
  testDateTime(test, 2000, 1, 1, 1, 2, 2, 2);
  test.add(1, DateTime::Hour);
  testDateTime(test, 2000, 1, 1, 2, 2, 2, 2);
  test.add(1, DateTime::Day);
  testDateTime(test, 2000, 1, 2, 2, 2, 2, 2);
  test.add(1, DateTime::Month);
  testDateTime(test, 2000, 2, 2, 2, 2, 2, 2);
  test.add(1, DateTime::Year);
  testDateTime(test, 2001, 2, 2, 2, 2, 2, 2);
  Serial.println("Test rollovers");
  test = DateTime(2000, 1, 1, 0, 0, 0, 999);        // millisecond -> seconds
  test.add(1, DateTime::Millisecond);               // rollover
  testDateTime(test, 2000, 1, 1, 0, 0, 1, 0);
  test.add(-1, DateTime::Millisecond);              // rollback
  testDateTime(test, 2000, 1, 1, 0, 0, 0, 999);

  test = DateTime(2000, 1, 1, 0, 0, 59, 0);         // seconds -> minutes
  test.add(1, DateTime::Second);                    // rollover
  testDateTime(test, 2000, 1, 1, 0, 1, 0, 0);
  test.add(-1, DateTime::Second);                   // rollback
  testDateTime(test, 2000, 1, 1, 0, 0, 59, 0);

  test = DateTime(2000, 1, 1, 0, 59, 0, 0);         // minutes -> hours
  test.add(1, DateTime::Minute);                    // rollover
  testDateTime(test, 2000, 1, 1, 1, 0, 0, 0);
  test.add(-1, DateTime::Minute);                   // rollback
  testDateTime(test, 2000, 1, 1, 0, 59, 0, 0);

  test = DateTime(2000, 1, 1, 23, 0, 0, 0);         // hours -> days
  test.add(1, DateTime::Hour);                      // rollover
  testDateTime(test, 2000, 1, 2, 0, 0, 0, 0);
  test.add(-1, DateTime::Hour);                     // rollback
  testDateTime(test, 2000, 1, 1, 23, 0, 0, 0);

  test = DateTime(2000, 1, 31, 0, 0, 0, 0);         // days -> months
  test.add(1, DateTime::Day);                       // rollover
  testDateTime(test, 2000, 2, 1, 0, 0, 0, 0);
  test.add(-1, DateTime::Day);                      // rollback
  testDateTime(test, 2000, 1, 31, 0, 0, 0, 0);

  test = DateTime(2000, 12, 1, 0, 0, 0, 0);        // months -> years
  test.add(1, DateTime::Month);                     // rollover
  testDateTime(test, 2001, 1, 1, 0, 0, 0, 0);
  test.add(-1, DateTime::Month);                    // rollback
  testDateTime(test, 2000, 12, 1, 0, 0, 0, 0);

  printTestResults();
}

void loop() {
  delay(1000);
}

void testDateTime(DateTime test, int year, int month, int day, int hour, int minute, int second, int millisecond) {
  boolean fail = false;
  if (!compare(year, test.year(), "Year")) fail = true;
  if (!compare(month, test.month(), "Month")) fail = true;
  if (!compare(day, test.day(), "Day")) fail = true;
  if (!compare(hour, test.hour(), "Hour")) fail = true;
  if (!compare(minute, test.minute(), "Minute")) fail = true;
  if (!compare(second, test.second(), "Second")) fail = true;
  if (!compare(millisecond, test.millisecond(), "Millisecond")) fail = true;
  if (fail) fails++;
  tests++;
  Serial.println(test.toString());
}

boolean compare(int expected, int actual, String description) {
  if (expected == actual) return true;
  Serial.print("Compare failed on ");
  Serial.print(description);
  Serial.print(". Expected: ");
  Serial.print(expected);
  Serial.print(". Actual: ");
  Serial.println(actual);
  return false;
}

void printTestResults() {
  Serial.print(tests);
  Serial.print(" test completed. ");
  Serial.print(fails);
  Serial.print(" failures. ");
  Serial.print((tests - fails)/(float) tests * 100);
  Serial.println("% pass rate.");
  if (fails) Serial.println("\nFAIL!");
}
