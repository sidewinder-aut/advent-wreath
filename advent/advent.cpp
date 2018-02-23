// ---------------------------- IMPORT OF LIBRARIES ----------------------------------
// Wire Library for I2C protocol
#include "Wire.h"

// Real Time Clock Library
#include "RTClib.h"


// ---------------------------- DEFINITION OF SENSOR TYPE AND PIN LAYOUT -------------
// RTC Module
RTC_DS1307 RTC;

// Digital IO 4-6 for first advent (marked in green)
int ledPin_A1_1 = 4;
int ledPin_A1_2 = 5;
int ledPin_A1_3 = 6;

// Digital IO 7-9 for second advent (not marked)
int ledPin_A2_1 = 7;
int ledPin_A2_2 = 8;
int ledPin_A2_3 = 9;

// Digital IO 10-11 for third advent (marked in pink)
int ledPin_A3_1 = 10;
int ledPin_A3_2 = 11;
int ledPin_A3_3 = 12;

// Digital IO 1-3 for first advent (marked in orange)
int ledPin_A4_1 = 1;
int ledPin_A4_2 = 2;
int ledPin_A4_3 = 3;


// ---------------------------- VOID SETUP -------------------------------------------
void setup(void) {

//--- Set baud rate
  Serial.begin(9600);

//--- RTC Module SETUP
// Initialization of I2C
  Wire.begin();
  RTC.begin();
  RTC.adjust(DateTime(__DATE__, __TIME__));
  Serial.println("RTC Initialization completed");

//--- Check RTC run
  //if (! RTC.isrunning()) {
  //  RTC.adjust(DateTime(__DATE__, __TIME__));                                         // Set current date and time if RTC is not running
  //  Serial.println("RTC run has been started and current time has been set");
  //}
  //else Serial.println("RTC already running");

//--- LED Pin Setup
  pinMode(ledPin_A1_1, OUTPUT);
  pinMode(ledPin_A1_2, OUTPUT);
  pinMode(ledPin_A1_3, OUTPUT);

  pinMode(ledPin_A2_1, OUTPUT);
  pinMode(ledPin_A2_2, OUTPUT);
  pinMode(ledPin_A2_3, OUTPUT);

  pinMode(ledPin_A3_1, OUTPUT);
  pinMode(ledPin_A3_2, OUTPUT);
  pinMode(ledPin_A3_3, OUTPUT);

  pinMode(ledPin_A4_1, OUTPUT);
  pinMode(ledPin_A4_2, OUTPUT);
  pinMode(ledPin_A4_3, OUTPUT);
}


// ---------------------------- MAIN PROGRAM -----------------------------------------
void loop(){

  // set advent number to zero every time for the daily shutoff
  int advent_number = 0;
  boolean is_daytime = false;

  // get current time
  DateTime now=RTC.now();
  //show_time_and_date(now);                                                            // show current time and date

  // get advent number
  advent_number = get_advent(now);
  advent_number = 4;
  // Serial.println(advent_number);

  // get daytime
  is_daytime = get_daytime(now);

  // light leds accordingly
  if(is_daytime == true){
    light_leds(advent_number);
  }
  else{
    shut_off_leds();
  }
//  switch_on_leds();
    shut_off_leds();

  // wait a specified amount of time until the advent is checked again
  delay(5000);
}


// ---------------------------- EXTENDED OUTPUT FOR THE RTC MODULE ---------------------------
void show_time_and_date(DateTime datetime){

//  Day/Month/Year
  Serial.print(datetime.day(),DEC);
  Serial.print("/");
  Serial.print(datetime.month(),DEC);
  Serial.print("/");
  Serial.print(datetime.year(),DEC);
  Serial.print(" --- ");

//  Hour:Minute:Second
  if(datetime.hour()<10)Serial.print(0);
  Serial.print(datetime.hour(),DEC);
  Serial.print(":");
  if(datetime.minute()<10)Serial.print(0);
  Serial.print(datetime.minute(),DEC);
  Serial.print(":");
  if(datetime.second()<10)Serial.print(0);
  Serial.println(datetime.second(),DEC);
}

// ---------------------------- GET THE ADVENT FROM THE CURRENT DATE -------------------------
int get_advent(DateTime datetime){
  int advent_number;
  advent_number = 0;

  // Check, if it is actually december
  if(datetime.month() == 12){

    //check for first advent
    if(datetime.day() >= 3){
      advent_number = 1;
    }

    // check for second advent
    if(datetime.day() >= 10){
      advent_number = 2;
    }

    // check for third advent
    if(datetime.day() >= 17){
      advent_number = 3;
    }

    // check for fourth advent
    if(datetime.day() >= 24){
      advent_number = 4;
    }
  }
  return advent_number;
}

// ---------------------------- LIGHT THE LEDS ACCORDING TO ----------------------------------
void light_leds(int advent_number){

  // Check if it is December
  if(advent_number > 0){
    // check for first advent and light first advent leds
    if(advent_number >= 1){
        digitalWrite(ledPin_A1_1, HIGH);
        digitalWrite(ledPin_A1_2, HIGH);
        digitalWrite(ledPin_A1_3, HIGH);
    }

    // check for second advent and light second advent leds
    if(advent_number >= 2){
        digitalWrite(ledPin_A2_1, HIGH);
        digitalWrite(ledPin_A2_2, HIGH);
        digitalWrite(ledPin_A2_3, HIGH);
    }

    // check for third advent and light third advent leds
    if(advent_number >= 3){
        digitalWrite(ledPin_A3_1, HIGH);
        digitalWrite(ledPin_A3_2, HIGH);
        digitalWrite(ledPin_A3_3, HIGH);
    }

    // check for fourth advent and light fourth advent leds
    if(advent_number >= 4){
        digitalWrite(ledPin_A4_1, HIGH);
        digitalWrite(ledPin_A4_2, HIGH);
        digitalWrite(ledPin_A4_3, HIGH);
    }
  }

  // shut off all leds if is not December
  else{
        shut_off_leds();
  }
}

// ---------------------------- CHECK FOR DAYTIME  -------------------------------------------
boolean get_daytime(DateTime datetime){
  boolean is_daytime;
  is_daytime = false;

  // Check if it is after 06:00 and before 20:00
  if((datetime.hour() > 6) && (datetime.hour() < 23)){
    is_daytime = true;
  }
  else{
    is_daytime = false;
  }
  return is_daytime;
}

// --------------------------- SHUT OFF ALL LEDS ---------------------------------------------
void shut_off_leds(){
    digitalWrite(ledPin_A1_1, LOW);
    digitalWrite(ledPin_A1_2, LOW);
    digitalWrite(ledPin_A1_3, LOW);
    digitalWrite(ledPin_A2_1, LOW);
    digitalWrite(ledPin_A2_2, LOW);
    digitalWrite(ledPin_A2_3, LOW);
    digitalWrite(ledPin_A3_1, LOW);
    digitalWrite(ledPin_A3_2, LOW);
    digitalWrite(ledPin_A3_3, LOW);
    digitalWrite(ledPin_A4_1, LOW);
    digitalWrite(ledPin_A4_2, LOW);
    digitalWrite(ledPin_A4_3, LOW);
}

// ---------------------------SWITCH ON ALL LEDS ---------------------------------------------
void switch_on_leds(){
    digitalWrite(ledPin_A1_1, HIGH);
    digitalWrite(ledPin_A1_2, HIGH);
    digitalWrite(ledPin_A1_3, HIGH);
    digitalWrite(ledPin_A2_1, HIGH);
    digitalWrite(ledPin_A2_2, HIGH);
    digitalWrite(ledPin_A2_3, HIGH);
    digitalWrite(ledPin_A3_1, HIGH);
    digitalWrite(ledPin_A3_2, HIGH);
    digitalWrite(ledPin_A3_3, HIGH);
    digitalWrite(ledPin_A4_1, HIGH);
    digitalWrite(ledPin_A4_2, HIGH);
    digitalWrite(ledPin_A4_3, HIGH);
}
