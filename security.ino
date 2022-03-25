/* Arduino Security System with the Keypad and LCD 
 * Creator Mert KILIC - Mert Arduino Tutorial and Project
 * Please subscribe for support
 * Thanks
 */

#include <LiquidCrystal.h> //include LCD library (standard library)
#include <Keypad.h> //include keypad library - first you must install library (library link in the video description)


/*const int RED_PIN = 10;
const int GREEN_PIN = 11;
const int BLUE_PIN = 12;*/

const int trigPin   = 10; // Arduino pin connected to Ultrasonic Sensor's TRIG pin
const int echoPin   = 11; // Arduino pin connected to Ultrasonic Sensor's ECHO pin
const int buzzer = 1; // Arduino pin connected to Piezo Buzzer's pin
const int DISTANCE_THRESHOLD = 20; // centimeters

// variables will change:
int duration, distance;

char* password ="1234"; //create a password
int pozisyon = 0; //keypad position

const byte rows = 4; //number of the keypad's rows and columns
const byte cols = 4;

char keyMap [rows] [cols] = { //define the cymbols on the buttons of the keypad

  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins [rows] = {9, 8, 7, 6}; //pins of the keypad
byte colPins [cols] = {5, 4, 3, 2};

Keypad myKeypad = Keypad( makeKeymap(keyMap), rowPins, colPins, rows, cols); // holding the keys

LiquidCrystal lcd (A0, A1, A2, A3, A4, A5); // pins of the LCD. (RS, E, D4, D5, D6, D7)

void setup(){

 
  pinMode(trigPin, OUTPUT);   // set arduino pin to output mode
  pinMode(echoPin, INPUT);    // set arduino pin to input mode
  pinMode(buzzer, OUTPUT); // set arduino pin to output mode

  lcd.begin(16, 2); //Initialize the 16x2 LCD
  lcd.clear();  //Clear any old data displayed on the LCD
  lcd.setCursor(0, 0);
  lcd.print("   Welcome AI");
  lcd.setCursor(0, 1);
  lcd.print("   We are ready");
  //setLocked (true); //state of the password
   tone(buzzer, 700, 100);
   delay(1000);
  
}

void loop(){
  
// generate 10-microsecond pulse to TRIG pin
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // measure duration of pulse from ECHO pin
  duration = pulseIn(echoPin, HIGH);
  
  // calculate the distance
  distance = 0.017 * duration;
  
  char whichKey = myKeypad.getKey(); //define which key is pressed with getKey

if(distance < DISTANCE_THRESHOLD){
    // setLocked (true);
    tone(buzzer, 1000); // Send 1KHz sound signal 
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" Enter Password");
    lcd.setCursor(0, 1);
    lcd.print(" Please");

 if(whichKey == '*' || whichKey == '#' || whichKey == 'A' ||       //define invalid keys
  whichKey == 'B' || whichKey == 'C' || whichKey == 'D'  ||  
  whichKey == '5' || whichKey == '6'  ||  
  whichKey == '7' || whichKey == '8' || whichKey == '9'  ||  
  whichKey == '0'){

    pozisyon=0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Invalid Password!");
    delay(1000);
    lcd.clear();
  }
  
   if(whichKey == password [pozisyon]){
    pozisyon ++;
    }

 if(pozisyon == 4){   // count of the password
   // setLocked (false);
   noTone(buzzer);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("*** Verified ***");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Blossom Arduino");
    lcd.setCursor(0, 1);
    lcd.print("AI Project");
    delay(7000);
    lcd.clear();
  }
  delay(100);
 
  } // end of distance is less than
  else
  {
    // do nothing
  } // end of if distance is greater than

} // end of void
   
