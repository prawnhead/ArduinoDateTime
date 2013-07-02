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

  Serial.println("Test interval rollovers");
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

  Serial.println("Test month rollovers");           // Also tests cascades millis -> seconds -> minutes ...

  test = DateTime(2000, 1, 31, 23, 59, 59, 999);    // January -> February
  test.add(1, DateTime::Millisecond);               // rollover
  testDateTime(test, 2000, 2, 1, 0, 0, 0, 0);
  test.add(-1, DateTime::Millisecond);              // rollback
  testDateTime(test, 2000, 1, 31, 23, 59, 59, 999);

  test = DateTime(2000, 2, 29, 23, 59, 59, 999);    // February -> March (leap year)
  test.add(1, DateTime::Millisecond);               // rollover
  testDateTime(test, 2000, 3, 1, 0, 0, 0, 0);
  test.add(-1, DateTime::Millisecond);              // rollback
  testDateTime(test, 2000, 2, 29, 23, 59, 59, 999);

  test = DateTime(2001, 2, 28, 23, 59, 59, 999);    // February -> March (non leap year)
  test.add(1, DateTime::Millisecond);               // rollover
  testDateTime(test, 2001, 3, 1, 0, 0, 0, 0);
  test.add(-1, DateTime::Millisecond);              // rollback
  testDateTime(test, 2001, 2, 28, 23, 59, 59, 999);

  test = DateTime(2000, 3, 31, 23, 59, 59, 999);    // March -> April
  test.add(1, DateTime::Millisecond);               // rollover
  testDateTime(test, 2000, 4, 1, 0, 0, 0, 0);
  test.add(-1, DateTime::Millisecond);              // rollback
  testDateTime(test, 2000, 3, 31, 23, 59, 59, 999);

  test = DateTime(2000, 4, 30, 23, 59, 59, 999);    // April -> May
  test.add(1, DateTime::Millisecond);               // rollover
  testDateTime(test, 2000, 5, 1, 0, 0, 0, 0);
  test.add(-1, DateTime::Millisecond);              // rollback
  testDateTime(test, 2000, 4, 30, 23, 59, 59, 999);

  test = DateTime(2000, 5, 31, 23, 59, 59, 999);    // May -> June
  test.add(1, DateTime::Millisecond);               // rollover
  testDateTime(test, 2000, 6, 1, 0, 0, 0, 0);
  test.add(-1, DateTime::Millisecond);              // rollback
  testDateTime(test, 2000, 5, 31, 23, 59, 59, 999);

  test = DateTime(2000, 6, 30, 23, 59, 59, 999);    // June -> July
  test.add(1, DateTime::Millisecond);               // rollover
  testDateTime(test, 2000, 7, 1, 0, 0, 0, 0);
  test.add(-1, DateTime::Millisecond);              // rollback
  testDateTime(test, 2000, 6, 30, 23, 59, 59, 999);

  test = DateTime(2000, 7, 31, 23, 59, 59, 999);    // July -> August
  test.add(1, DateTime::Millisecond);               // rollover
  testDateTime(test, 2000, 8, 1, 0, 0, 0, 0);
  test.add(-1, DateTime::Millisecond);              // rollback
  testDateTime(test, 2000, 7, 31, 23, 59, 59, 999);

  test = DateTime(2000, 8, 31, 23, 59, 59, 999);    // August -> September
  test.add(1, DateTime::Millisecond);               // rollover
  testDateTime(test, 2000, 9, 1, 0, 0, 0, 0);
  test.add(-1, DateTime::Millisecond);              // rollback
  testDateTime(test, 2000, 8, 31, 23, 59, 59, 999);

  test = DateTime(2000, 9, 30, 23, 59, 59, 999);    // September -> October
  test.add(1, DateTime::Millisecond);               // rollover
  testDateTime(test, 2000, 10, 1, 0, 0, 0, 0);
  test.add(-1, DateTime::Millisecond);              // rollback
  testDateTime(test, 2000, 9, 30, 23, 59, 59, 999);

  test = DateTime(2000, 10, 31, 23, 59, 59, 999);    // October -> November
  test.add(1, DateTime::Millisecond);               // rollover
  testDateTime(test, 2000, 11, 1, 0, 0, 0, 0);
  test.add(-1, DateTime::Millisecond);              // rollback
  testDateTime(test, 2000, 10, 31, 23, 59, 59, 999);

  test = DateTime(2000, 11, 30, 23, 59, 59, 999);    // November -> December
  test.add(1, DateTime::Millisecond);               // rollover
  testDateTime(test, 2000, 12, 1, 0, 0, 0, 0);
  test.add(-1, DateTime::Millisecond);              // rollback
  testDateTime(test, 2000, 11, 30, 23, 59, 59, 999);

  test = DateTime(2000, 12, 31, 23, 59, 59, 999);    // December -> January
  test.add(1, DateTime::Millisecond);               // rollover
  testDateTime(test, 2001, 1, 1, 0, 0, 0, 0);
  test.add(-1, DateTime::Millisecond);              // rollback
  testDateTime(test, 2000, 12, 31, 23, 59, 59, 999);

  Serial.println("Test leap years");
  
  test = DateTime(1999, 2, 28, 23, 59, 59, 999);    // Not a leap year
  test.add(1, DateTime::Millisecond);               // rollover
  testDateTime(test, 1999, 3, 1, 0, 0, 0, 0);
  test.add(-1, DateTime::Millisecond);              // rollback
  testDateTime(test, 1999, 2, 28, 23, 59, 59, 999);

  test = DateTime(1996, 2, 28, 23, 59, 59, 999);    // Leap year divisible by 4
  test.add(1, DateTime::Millisecond);               // rollover 28 -> 29
  testDateTime(test, 1996, 2, 29, 0, 0, 0, 0);
  test = DateTime(1996, 2, 29, 23, 59, 59, 999);
  test.add(1, DateTime::Millisecond);               // rollover 29 -> 1
  testDateTime(test, 1996, 3, 1, 0, 0, 0, 0);
  test.add(-1, DateTime::Millisecond);               // rollback 1 -> 29
  testDateTime(test, 1996, 2, 29, 23, 59, 59, 999);

  test = DateTime(1900, 2, 28, 23, 59, 59, 999);    // Not a leap year divisible by 100
  test.add(1, DateTime::Millisecond);               // rollover
  testDateTime(test, 1900, 3, 1, 0, 0, 0, 0);
  test.add(-1, DateTime::Millisecond);              // rollback
  testDateTime(test, 1900, 2, 28, 23, 59, 59, 999);

  test = DateTime(2000, 2, 28, 23, 59, 59, 999);    // Leap year divisible by 400
  test.add(1, DateTime::Millisecond);               // rollover 28 -> 29
  testDateTime(test, 2000, 2, 29, 0, 0, 0, 0);
  test = DateTime(2000, 2, 29, 23, 59, 59, 999);
  test.add(1, DateTime::Millisecond);               // rollover 29 -> 1
  testDateTime(test, 2000, 3, 1, 0, 0, 0, 0);
  test.add(-1, DateTime::Millisecond);               // rollback 1 -> 29
  testDateTime(test, 2000, 2, 29, 23, 59, 59, 999);

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
