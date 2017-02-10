#include <LiquidCrystal.h>
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 2);


// pins for Multiport
int focus = 13;
int shutter = 12;

//Variable for number of shots to take. Add the number of shots in setup
int shots;

void go(){
  //set focus pin into output mode
   pinMode(focus, OUTPUT);
  
  //set shutter pin to output mode
   pinMode(shutter, OUTPUT);
  
  //wait 20 milliseconds
    delay(20);

  //Activate the camera focus
    digitalWrite(focus, HIGH);
  
  //wait 50 milliseconds
    delay(500);

  //Activate the camera shutter
    digitalWrite(shutter, HIGH);

  //Wait 50 milliseconds
    delay(50);

  //Set the focus pin back to input mode. This stops the camera from taking extra pictures through noise in the circuits
    pinMode(focus, INPUT);

  //Set the shutter pin back to input mode. This stops the camera from taking extra pictures through noise in the circuits
    pinMode(shutter, INPUT);

  //Wait 1 second
    delay(1000);  

  //Send stepper motor forward 1 step
    myMotor->step(1,FORWARD,DOUBLE);

  //reduce the number of shots Remaining
    --shots;

  //Display shots remaining
  lcd.setCursor(0,0);
  lcd.print("Shots remaining:");
  lcd.setCursor(0,1);
  lcd.print (shots);
  delay(1000);
  lcd.clear();
}

void setup() {
  
  // set up Serial library at 9600 bps
    Serial.begin(9600);

  //Set up number of Shots to take
  shots=1300;
    
  // set up the LCD's number of columns and rows: 
    lcd.begin(16, 2);
    
  //assert all pins, just to make sure...
    pinMode(focus, INPUT);
    pinMode(shutter, INPUT);
    
  // Initialize the motor shield with the default frequency 1.6KHz
    AFMS.begin();
    
  // initialise LCD lib full-screen  
    lcd.begin(16, 2);               
  // set cursor position
    lcd.setCursor(0,0); 
  //Welcome Screen
    lcd.print("Welcome to");
  //Move cursor to second row
    lcd.setCursor(0,1);
  lcd.print("Slidey V 0.1");
  delay(1000);
  lcd.clear();            
}

void loop() {
  // put your main code here, to run repeatedly:
  if (shots > 0)go();
}
