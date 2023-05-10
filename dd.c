#include <Adafruit_SSD1306.h>
#include <splash.h>
#include <Wire.h>
#include "RTClib.h"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday",
                             "Thursday", "Friday", "Saturday"};
int rele = 6;
#define OLED_RESET 4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire,OLED_RESET);

String Hours[] = {
"7:02 am",
"8:00 am",
"8:50 am",
"9:40 am",
"10:00 am",
"10:50 am",
"11:40 am",
"12:20 pm",
"1:00 pm",
"1:50 pm",
"2:40 pm"
};

void setup() {
pinMode(rele, OUTPUT);
digitalWrite(rele, HIGH);

  Serial.begin(9600);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // Following line sets the RTC to the date & time this sketch was compiled
        rtc.adjust(DateTime(F(_DATE), F(TIME_)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  if (! display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds
  display.clearDisplay();
  display.display();
  delay(2000);
}

void text(String date) {
  display.clearDisplay();
  display.setTextSize(2); // Draw 2X-scale text
  display.invertDisplay(true);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  display.println(date);
  display.display(); // Show initial text
  delay(100);

}

void loop() {
  DateTime now = rtc.now();
  int weekDay = now.day();
  int hourDay = now.hour();
  int minuteDay = now.minute();
  int secondDay = now.second();
  // Button state on, not weekend, not woking hours
  String timeNowString = "" + String(hourDay) + "" + String(minuteDay);
  int caseSwitch = timeNowString.toInt();
  Serial.println(caseSwitch);
  text(" Son las   " + String(hourDay) + ": " + String(minuteDay) + " "+ String(secondDay));
   Serial.println (weekDay);
   Serial.println (hourDay);
  if (  (hourDay > 6 && hourDay < 15 )) {
   Serial.println ("hey entro");
    switch (caseSwitch) {
      case 702:
        ring();
        break;
      case 705:
        ring();
        break;
      case 820:
        ring();
        break;
      case 821:
        ring();
        break;
      case 100:
        ring();
        break;
      case 1050:
        ring();
        break;
      case 1140:
        ring();
        break;
      case 1220:
        ring();
        break;
      case 130:
        ring();
        break;
      case 1350:
        ring();
        break;
      case 1440:
        Serial.println("Bye!!, end the day.");
        ring();
        break;
      default:
        Serial.println("Time between hours doorbell off");
        printTime();
        digitalWrite(rele, HIGH);
        break;
    }
  }
  else {
    Serial.println("In weekend or not working hours and doorbell off");
    digitalWrite(rele,  HIGH);
    printTime();
  }
}

void ring() {
  printTime();
  Serial.println("doorbell on");
  digitalWrite(rele, LOW);
  waitRing();
  digitalWrite(rele, HIGH);
  Serial.println("doorbell off");
  waitMinute();

}

void printTime() {
  DateTime now = rtc.now();
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  delay(1000);
}

void waitMinute() {
  DateTime now = rtc.now();
  int minuteDay = now.minute();
  Serial.println("Wait minute after ring!");
  while ( minuteDay == now.minute()) {
    delay(1000);
    now = rtc.now();
  }
}

void waitRing() {
  Serial.println("Wait 6 seg while ring!");
  delay(6000);
} //Hace que el programa tarde 6 segundos para hacer la ejecucion