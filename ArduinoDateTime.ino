#include "DateTime.h"
#include <String.h>

String& junk() {
  static String *message;
  String* temp = message;
  message = new String("Hello World");
  delete(temp);
  return *message;
}

void setup() {
  Serial.begin(115200);
  Serial.println("setup()");
}

void loop() {
  //junk('a');
  String &stuff = junk();
  Serial.println(stuff);
  Serial.println((int)&stuff);
  delay(1000);
}


