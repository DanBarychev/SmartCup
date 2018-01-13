#include <LiquidCrystal.h>

#Another comment for sample commit, remove later

const int sensorPin = A0;
int setTemp = 20;

int switchState1 = 0;
int switchState2 = 0;
int switchState3 = 0;

boolean settingsButton = false;
boolean menuScreen = false;

LiquidCrystal lcd (12, 11, 5, 4, 3, 2);

void setup() {
  pinMode(7, INPUT);
  
  pinMode(8, INPUT);
  
  pinMode(9, INPUT);
  
  Serial.begin(9600);

  lcd.begin(16, 2);
  
  lcd.print("Welcome to");
 
  lcd.setCursor(0, 1);
 
  lcd.print("SmartCup!");
  
  delay(2000);
}

void loop() {
  
  if (!settingsButton)
  {
    
  lcd.clear();
  
  switchState1 = digitalRead(7);
  switchState2 = digitalRead(8);
  switchState3 = digitalRead(9);

  int sensorVal = analogRead(sensorPin);
  Serial.print(" Sensor Value: ");
  Serial.print(sensorVal);

  float voltage = (sensorVal/1024.0) * 5.0;

  Serial.print(", Volts: ");
  Serial.print(voltage);

  float temperature = (voltage - .5) * 100;

  Serial.print(", degrees C: ");
  Serial.print(temperature);
  
  if (temperature < setTemp - 2)
  {
    lcd.print("Cup is Too Cold! ");
  }
  
  if(temperature <= setTemp + 2 && temperature >= setTemp - 2)
  {
    lcd.print("Cup Just Right");
  }
  
  if (temperature > setTemp + 2)
  {
    lcd.print("Cup is Too Hot! ");
  }
  
  lcd.setCursor(0, 1);
  lcd.print(temperature);
  lcd.print(" Degrees C");
  }
  
  if (switchState3 == HIGH && !settingsButton) //Settings Menu
  {    
    lcd.clear();
    
    settingsButton = true;
    
    menuScreen = false;
  }
  
  if (settingsButton)
  {
    delay(200);
    
    switchState3 = digitalRead(9);
    
    if (switchState3 == HIGH)
    {
      settingsButton = false;
    }
    
    if(!menuScreen)
    {
    lcd.print("Set Temperature: ");
      
    lcd.setCursor(0, 1);
      
    lcd.print(setTemp);
      
    lcd.print(" Degrees C          ");
    
    menuScreen=true;
    }
    
   delay(100);
    
   switchState1 = digitalRead(7);
 
   if(switchState1 == HIGH)
   {
     setTemp++;
     
     menuScreen = false;
   } 
   
   delay(100);
    
   switchState2 = digitalRead(8);
 
   if(switchState2 == HIGH)
   {
     setTemp--;
     
     menuScreen = false;
   }
 }
  delay(200);
} 
