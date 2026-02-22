This class is under active development and is not ready for release.

A clock is a very reasonable project for an Arduino fan to make. The current date and time can be easily sourced (Internet NTP, GPS, etc.) and libraries exists to do that. If your time zone doesn't use Daylight Savings Time it's easy to adjust the time by a fix number of hours and the local time can be displayed.

The arduino_time (https://github.com/michaelmargolis/arduino_time) library is brilliant for synchronising the current time and providing many useful functions for it. But in adjusting for daylight savings in the current year, I need to calculate the dates and times on which the clock moves forward/backward and use those to determine if daylight savings applies now. Where arduino_time provides a single time variable, it does not make it possible to instantiate more than one. Thus I want a DateTime class such that multiple instances can exist and be compared.

prawnhead@gmail.com