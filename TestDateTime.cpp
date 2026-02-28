#include "arduino.h"
#include "DateTime.h"

int tests, fails;
String True = "True";
String False = "False";

void testIsLeapYear(int year, bool expected) {

  Serial.print("    test isLeapYear(");
  Serial.print(year);
  Serial.println(")");

  tests++;
  bool leapYear = DateTime::isLeapYear(year);

  if (expected != leapYear) {
    fails++;
    Serial.print("FAIL! Expected: ");
    Serial.print((expected) ? True : False);
    Serial.print(", returned: ");
    Serial.println((leapYear) ? True : False);
  }
}

void testDayName(DateTime::Day day, String expectedDayName, bool shortName) {

  Serial.print("    test dayName");
  (shortName) ? Serial.print("Short("): Serial.print("(");
  Serial.print((int)day);
  Serial.println(")");
  
  tests++;
  String name = String();
  (shortName) ? DateTime::dayNameShort(day, name) : DateTime::dayName(day, name);
  if (name != expectedDayName) {
    fails++;
    Serial.print("FAIL! Expected: ");
    Serial.print(expectedDayName);
    Serial.print(", returned: ");
    Serial.println(name);
  }
}

void testMonthName(DateTime::Month month, String expectedMonthName, bool shortName) {

  Serial.print("    test monthName");
  (shortName) ? Serial.print("Short("): Serial.print("(");
  Serial.print(expectedMonthName);
  Serial.println(")");
  
  tests++;
  String name = String();
  (shortName) ? DateTime::monthNameShort(month, name) : DateTime::monthName(month, name);
  if (name != expectedMonthName) {
    fails++;
    Serial.print("FAIL! Expected: ");
    Serial.print(expectedMonthName);
    Serial.print(", returned ");
    Serial.println(name);
  }
}

void testDateTime() {
  
  Serial.println("    Testing ...");
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
  testMonthName(DateTime::Month::December, "Dec", true);         // last enum

  testIsLeapYear(2000, true);
  testIsLeapYear(2024, true);
  testIsLeapYear(1900, false);
  testIsLeapYear(2023, false);
  testIsLeapYear(2100, false);

  Serial.println();
  Serial.print(tests);
  Serial.print(" test completed. ");
  Serial.print(fails);
  Serial.print(" failures. ");
  Serial.print((tests - fails)/(float) tests * 100);
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