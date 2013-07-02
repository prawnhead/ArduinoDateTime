#include "DateTime.h"

int tests = 0;
int fails = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("setup()");
  DateTime test = DateTime(0, 1, 1, 1, 1, 1, 0);
  testDateTime(test, 0, 1, 1, 1, 1, 1, 0);
  printTestResults();
}

void loop() {
  delay(1000);
}

void testDateTime(DateTime test, byte year, byte month, byte day, byte hour, byte minute, byte second, int millisecond) {
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

boolean compare(byte expected, byte actual, String description) {
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
  Serial.print((tests - fails)/tests * 100);
  Serial.println("% pass rate.");
  if (fails) Serial.println("\nFAIL!");
}
