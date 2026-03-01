#include "arduino.h"
#include "DateTime.h"

int tests, fails;
String True = "True";
String False = "False";

// Test DST callback function
// std::function<DateTime(int, bool)>
DateTime aedst(int year, bool forward) {
  if (forward) {
    return DateTime(2001, 1, 1, 1, 1, 1, 1);
  } else {
    return DateTime(2002, 2, 2, 2, 2, 2, 2);
  }
}

void reset() {
  tests = 0;
  fails = 0;
}

void testToMonth(int month, DateTime::Month expectedMonth) {

  String expectedMonthName = String();
  DateTime::monthName(expectedMonth, expectedMonthName);
  Serial.print("      test toMonth(");
  Serial.print(expectedMonthName);
  Serial.println(")");

  tests++;
  DateTime::Month actualMonth = DateTime::toMonth(month);

  if (actualMonth != expectedMonth) {
    fails++;
    String actualMonthName = String();
    DateTime::monthName(actualMonth, actualMonthName);
    Serial.print("FAIL! Expected: ");
    Serial.print(expectedMonthName);
    Serial.print(", returned: ");
    Serial.println(actualMonthName);
  }
}

void testIsLeapYear(int year, bool expectedLeapYear) {

  Serial.print("      test isLeapYear(");
  Serial.print(year);
  Serial.println(")");

  tests++;
  bool actualLeapYear = DateTime::isLeapYear(year);

  if (expectedLeapYear != actualLeapYear) {
    fails++;
    Serial.print("FAIL! Expected: ");
    Serial.print((expectedLeapYear) ? True : False);
    Serial.print(", returned: ");
    Serial.println((actualLeapYear) ? True : False);
  }
}

void testDayName(DateTime::Day day, String expectedDayName, bool shortName) {

  Serial.print("      test dayName");
  (shortName) ? Serial.print("Short(") : Serial.print("(");
  Serial.print((int)day);
  Serial.println(")");

  tests++;
  String actualDayName = String();
  (shortName) ? DateTime::dayNameShort(day, actualDayName) : DateTime::dayName(day, actualDayName);
  if (actualDayName != expectedDayName) {
    fails++;
    Serial.print("FAIL! Expected: ");
    Serial.print(expectedDayName);
    Serial.print(", returned: ");
    Serial.println(actualDayName);
  }
}

void testMonthName(DateTime::Month month, String expectedMonthName, bool shortName) {

  Serial.print("      test monthName");
  (shortName) ? Serial.print("Short(") : Serial.print("(");
  Serial.print(expectedMonthName);
  Serial.println(")");

  tests++;
  String actualMonthName = String();
  (shortName) ? DateTime::monthNameShort(month, actualMonthName) : DateTime::monthName(month, actualMonthName);
  if (actualMonthName != expectedMonthName) {
    fails++;
    Serial.print("FAIL! Expected: ");
    Serial.print(expectedMonthName);
    Serial.print(", returned ");
    Serial.println(actualMonthName);
  }
}

void testDaysInMonth(DateTime::Month month, int year, int expectedDays) {

  String monthName = String();
  DateTime::monthName(month, monthName);
  Serial.print("      test daysInMonth(");
  Serial.print(monthName);
  Serial.print(", ");
  Serial.print(year);
  Serial.println(")");

  tests++;
  int actualDays = DateTime::daysInMonth(month, year);
  if (actualDays != expectedDays) {
    fails++;
    Serial.print("FAIL! Expected: ");
    Serial.print(expectedDays);
    Serial.print(", returned ");
    Serial.println(actualDays);
  }
}

void testDateTime() {

  Serial.println("Verify all tests can fail ...");
  testDayName(DateTime::Day::Error, "None", false);
  testDayName(DateTime::Day::Error, "Non", true);
  testMonthName(DateTime::Month::Error, "None", false);
  testMonthName(DateTime::Month::Error, "Non", true);
  testIsLeapYear(2000, false);
  testToMonth(1, DateTime::Month::February);
  testDaysInMonth(DateTime::Month::February, 2000, 31);

  Serial.println();
  Serial.print(tests);
  Serial.print(" test completed. ");
  Serial.print(fails);
  Serial.print(" failures. ");
  Serial.print((tests - fails) / (float)tests * 100);
  Serial.println("% pass rate.\n");
  reset();

  Serial.println("TESTING ...");
  testDayName(DateTime::Day::Error, "Error", false);            // 1st enum
  testDayName(DateTime::Day::Sunday, "Sunday", false);          // 1st useful enum
  testDayName(DateTime::Day::Saturday, "Saturday", false);      // last enum
  testDayName(DateTime::Day::Error, "Err", true);               // 1st enum
  testDayName(DateTime::Day::Sunday, "Sun", true);              // 1st useful enum
  testDayName(DateTime::Day::Saturday, "Sat", true);            // last enum
  testMonthName(DateTime::Month::Error, "Error", false);        // 1st enum
  testMonthName(DateTime::Month::January, "January", false);    // 1st useful enum
  testMonthName(DateTime::Month::December, "December", false);  // last enum
  testMonthName(DateTime::Month::Error, "Err", true);           // 1st enum
  testMonthName(DateTime::Month::January, "Jan", true);         // 1st useful enum
  testMonthName(DateTime::Month::December, "Dec", true);        // last enum

  testIsLeapYear(2000, true);
  testIsLeapYear(2024, true);
  testIsLeapYear(1900, false);
  testIsLeapYear(2023, false);
  testIsLeapYear(2100, false);

  testToMonth(1, DateTime::Month::January);
  testToMonth(12, DateTime::Month::December);
  testToMonth(13, DateTime::Month::January);
  testToMonth(24, DateTime::Month::December);
  testToMonth(0, DateTime::Month::December);
  testToMonth(-1, DateTime::Month::November);
  testToMonth(-12, DateTime::Month::December);

  testDaysInMonth(DateTime::Month::January, 2000, 31);
  testDaysInMonth(DateTime::Month::July, 2000, 31);
  testDaysInMonth(DateTime::Month::December, 2000, 31);
  testDaysInMonth(DateTime::Month::April, 2000, 30);
  testDaysInMonth(DateTime::Month::June, 2000, 30);
  testDaysInMonth(DateTime::Month::November, 2000, 30);
  testDaysInMonth(DateTime::Month::February, 2000, 29);
  testDaysInMonth(DateTime::Month::February, 2001, 28);

  Serial.println();
  Serial.print(tests);
  Serial.print(" test completed. ");
  Serial.print(fails);
  Serial.print(" failures. ");
  Serial.print((tests - fails) / (float)tests * 100);
  Serial.println("% pass rate.");

  if (fails) Serial.println("\nFAIL!");
}

/*

Q. What are some years I should use to test my leapYear() algorithm?

A. (Claude)
Here are the key test cases for a leap year algorithm:

**Definitely leap years:**
- **2000** – divisible by 400 (the "special" case many algorithms get wrong)
- **2024** – divisible by 4, not by 100 (common case)

**Definitely NOT leap years:**
- **1900** – divisible by 100 but *not* 400 (the most commonly failed edge case)
- **2023** – not divisible by 4 at all (basic case)
- **2100** – future century year, not divisible by 400

**The core rules to cover:**
1. Divisible by 4 → leap year ✓
2. Divisible by 100 → *not* a leap year ✗ (overrides rule 1)
3. Divisible by 400 → leap year ✓ (overrides rule 2)

The classic bug is treating **1900** as a leap year or **2000** as not one — so those two are your most important edge cases.
*/