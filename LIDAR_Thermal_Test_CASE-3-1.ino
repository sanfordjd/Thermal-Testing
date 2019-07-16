//Joe Sanford
//02JUL02019
//Intellibot

//LIDAR_Thermal_Test_CASE-3-1
/*This sketch helps to automate a thermal test of several
 * Hokuyo LIDAR. This sketch controls a relay that powers
 * LIDAR that are being tested for humidity tolerance in a
 * thermal chamber.
 * Test Plan currently Described Here:
 * https://docs.google.com/document/d/1PATsmtoUqLHud8jTLVV8WVLAqHYfIKmVEvpr6jq2F7g/edit#heading=h.gjdgxs
 * We use an Arduino MEGA 2560 to command a
 * DQ542MA 2H Microstep driver. This driver is acting as a power
 * relay ... since we don't have a 5V relay in stock at the moment.
 * 
 * July 2019 V 1.0: Initial Version
 * 
 */

 #include <SoftwareSerial.h>   //Software Serial Port
//#include <LiquidCrystal.h>
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// These #defines make it easy to set the backlight color
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

int pwrPin = 26;  //this pin writes digital HIGH to energize the relay that 
                  //powers the LIDARs under test

int enablePin = 32; //stepper motor enabled and disabled in singleStep()

int buttonPush = 0; //counting the number of times the Start Button has been pushed
                    //should be either zero or 1  

const char firstlineText[17] = "LIDAR Thermal   ";
const char secondlineText[17] = "Test: CASE3.1   ";

void setup() 
{

  Serial.begin(9600);

  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(firstlineText);
  Serial.print(firstlineText);
  lcd.setCursor(0,1);
  lcd.print(secondlineText);
  Serial.print(secondlineText);
  int time = millis();
  lcd.print("Hello, world!");
  time = millis() - time;
  Serial.print("Took "); Serial.print(time); Serial.println(" ms");
  lcd.setBacklight(WHITE);

  delay(6000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Push Left Button");
  //Serial.print("Push Left Button");
  lcd.setCursor(0,1);
  lcd.print("To Start ...    ");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("To Start ...    ");
  lcd.setCursor(0, 1);
  lcd.print("Test CASE 3.1   ");  
  
  pinMode (pwrPin, OUTPUT);
  pinMode (enablePin, OUTPUT);
  digitalWrite(pwrPin, LOW);
  digitalWrite(enablePin, LOW);
  
  delay(1000);
  } //void setup()

void loop() 
{
  //lcd.clear();
  uint8_t buttons = lcd.readButtons(); //setting up button read
    
    lcd.setCursor(0,0);
    if (buttons & BUTTON_LEFT) 
    {
      //Serial.print("left button pushed\n");
      lcd.print("START ");
      Serial.print("START \n");
      buttonPush++;
      lcd.setBacklight(GREEN);
      lcd.setBacklight(WHITE); //reset LCD back to white
      lcd.clear();
      
      //digitalWrite(pwrPin, LOW); //power is off to LIDAR
      digitalWrite(enablePin, HIGH);
      digitalWrite(pwrPin, HIGH); //remove ... only for debug
      //digitalWrite(pwrPin, LOW); //remove ... only for debug
      lcd.setCursor(0, 0);
      lcd.print("LIDAR OFF       ");
      lcd.setCursor(0, 1);
      lcd.print("1st Low         ");
      delay(1200000); //first 20 minutes off
      digitalWrite(pwrPin, HIGH); //turning on
      
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("LIDAR ON        ");
      lcd.setCursor(0, 1);
      lcd.print("1st HIGH        ");
      delay(2100000); //delay 35minutes ... first HIGH
      digitalWrite(pwrPin, LOW); //power is off to LIDAR
      
      lcd.setCursor(0, 0);
      lcd.print("LIDAR OFF       ");
      lcd.setCursor(0, 1);
      lcd.print("2nd Low         ");
      delay(4200000); // 70 minutes off
      digitalWrite(pwrPin, HIGH); //turning on
      
      lcd.setCursor(0, 0);
      lcd.print("LIDAR ON        ");
      lcd.setCursor(0, 1);
      lcd.print("2nd HIGH        ");
      delay(2100000); //delay 35minutes ... second HIGH
      digitalWrite(pwrPin, LOW); //power is off to LIDAR
      
      lcd.setCursor(0, 0);
      lcd.print("LIDAR OFF       ");
      lcd.setCursor(0, 1);
      lcd.print("3rd Low         ");
      delay(4200000); // 70 minutes off
      
      lcd.setCursor(0, 0);
      lcd.print("LIDAR ON        ");
      lcd.setCursor(0, 1);
      lcd.print("3rd HIGH        ");
      delay(2100000); //delay 35minutes ... third HIGH
      digitalWrite(pwrPin, LOW); //power is off to LIDAR
      
      lcd.setCursor(0, 0);
      lcd.print("LIDAR OFF       ");
      lcd.setCursor(0, 1);
      lcd.print("4th Low         ");
      delay(4200000); // 70 minutes off
      
      lcd.setCursor(0, 0);
      lcd.print("LIDAR ON        ");
      lcd.setCursor(0, 1);
      lcd.print("4th HIGH        ");
      delay(2100000); //delay 35minutes ... third HIGH
      
      digitalWrite(pwrPin, LOW); //power is off to LIDAR
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("LIDAR OFF       ");
      lcd.print("Stop Test       ");
      
    } //if (buttons & ... 
        
} // void loop()
