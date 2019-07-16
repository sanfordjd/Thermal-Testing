//Joe Sanford
//02JUL02019
//Intellibot

//LIDAR_Thermal_Test_CASE-3-3
/*This sketch helps to automate a thermal test of several
 * Hokuyo LIDAR. This sketch controls a relay that powers
 * LIDAR that are being tested for humidity tolerance in a
 * thermal chamber.
 * Test Plan currently Described Here:
 * https://docs.google.com/document/d/1PATsmtoUqLHud8jTLVV8WVLAqHYfIKmVEvpr6jq2F7g/edit#heading=h.gjdgxs
 * We use an Arduino MEGA 2560 to command a
 * JQC-3FF-S-Z 5V Relay. We assume Normally Open, ie, the LIDAR are ON to start
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

int pinOut1 = 30; //this pin writes digital HIGH to energize the relay that 
                  //powers some of the LIDARs under test.  We assume 
                  //Normally Open, ie, the LIDAR are ON to start

int pinOut2 = 32; //this pin writes digital HIGH to energize the relay that 
                  //powers some of the LIDARs under testWe assume 
                  //Normally Open, ie, the LIDAR are ON to start

int buttonPush = 0; //counting the number of times the Start Button has been pushed
                    //should be either zero or 1  

const char firstlineText[17] = "LIDAR Thermal   ";
const char secondlineText[17] = "Test: CASE3.3   ";

char iStrg[1];

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
  lcd.print("Test CASE 3.3   ");  
  
  pinMode (pinOut1, OUTPUT);
  pinMode (pinOut2, OUTPUT);
  //digitalWrite(pinOut1, LOW); //opening the RELAY so that the LIDAR are OFF
  //digitalWrite(pinOut2, LOW); //opening the RELAY so that the LIDAR are OFF
  
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

      //loop here, 4 times
      for(int i = 1; i < 5; i++)
      {
        digitalWrite(pinOut1, LOW); //opening the RELAY so that the LIDAR are OFF
        digitalWrite(pinOut2, LOW);
        lcd.setCursor(0, 0);
        lcd.print("LIDAR OFF       ");
        lcd.setCursor(0, 1);
        sprintf(iStrg, "%d", i);
        lcd.print(iStrg);
        lcd.print(" : LOW        ");
        Serial.print(iStrg);
        Serial.print(" LIDAR LOW\n");
        delay(3000000); //delay 50 minutes ... LIDAR off

        digitalWrite(pinOut1, HIGH); //Closing the RELAY so that the LIDAR are ON
        digitalWrite(pinOut2, HIGH);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("LIDAR ON        ");
        lcd.setCursor(0, 1);
        sprintf(iStrg, "%d", i);
        lcd.print(iStrg);
        lcd.print(" : HIGH        ");
        sprintf(iStrg, "%d", i);
        Serial.print(iStrg);
        Serial.print(" LIDAR HIGH\n");
        delay(3600000); //delay 60minutes ... LIDAR HIGH
        
      } //end for(i = 0; i <= 4, i++) 
      
      digitalWrite(pinOut1, LOW); //opening the RELAY so that the LIDAR are OFF
      digitalWrite(pinOut2, LOW);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("LIDAR OFF       ");
      lcd.setCursor(0, 1);
      lcd.print("Stop Test       ");
      Serial.print("LIDAR OFF\n");
      Serial.print("Stop Test\n");
      
    } //if (buttons & ... 
        
} // void loop()
