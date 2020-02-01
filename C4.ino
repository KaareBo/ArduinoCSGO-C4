#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Keypad.h>
//Liquid Crystal IC2, change to your settings
LiquidCrystal_I2C lcd(0x27,16,2);



char* password = "7355608";
//Password

int mins = 00;
int sec = 45;
int milisecs = 000;
//Time in minutes, seconds and milliseconds
bool armed = true;
bool detonated = false;

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
//The keypad is connected from left to right, digitalpin 10 to 4

byte rowPins[ROWS] = {9, 4, 5, 7}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 10, 6};    //connect to the column pinouts of the keypad
int position = 0;
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
position = 0;
lcd.init();
lcd.backlight();
lcd.setCursor(0, 0);

}

void loop() {
  // put your main code here, to run repeatedly:
//Get the pressed key and store it as a char key
char key = keypad.getKey();
//Do nothing if nothing is pressed
if(key != NO_KEY){
 
}
//If you press the wrong button, start again
if(key != NO_KEY){
  if(key != password[position]){
    position = 0;
  }
}
//If you press the correct button you advance
if (key == password[position]){
  position = position + 1; 
}
if(position == 7) //Numbers in the password
{
//What to do if the position is correct
  Serial.println("Riktig");
  //To prevent the code from running again
  position = position + 1;
  armed = true;
}

if(armed == false){
//If the bomb is off, do this
//This is just for show, it shows stars and numbers like in counter strike
if(position == 0){
  Serial.println("*******");
  lcd.clear();
  lcd.print("*******");
}
if(position == 1){
  Serial.println("******7");
  lcd.clear();
  lcd.print("******7");
}
if(position == 2){
  Serial.println("*****73");
  lcd.clear();
  lcd.print("*****73");
}
if(position == 3){
  Serial.println("****735");
  lcd.clear();
  lcd.print("****735");
}
if(position == 4){
  Serial.println("***7355");
  lcd.clear();
  lcd.print("***7355");
}
if(position == 5){
  Serial.println("**73556");
  lcd.clear();
  lcd.print("**73556");
}
if(position == 6){
  Serial.println("*735560");
  lcd.clear();
  lcd.print("*735560");
}
if(position == 7){
  Serial.println("7355608");
  lcd.clear();
  lcd.print("7355608");
}
}





//Countdown starts when the bomb is armed
if(sec == 0 && milisecs == 00 && mins != 0){
  mins = mins - 1;
  sec = 60;
}
if(milisecs == 0 && sec != 0){
  sec = sec - 1;
  milisecs = 100;
}
if(armed == true){
  milisecs = milisecs - 1;
  delay(1);
}
//If the bomb is armed
//Here 
  if(armed == true){
//If there's under a minute left,
  if(mins == 0){
  Serial.print("00");
  Serial.print(":");
  Serial.print(sec);
  Serial.print(":");
  Serial.println(milisecs);

  //Write the time left to the LCD screen
  
  lcd.clear();
  String Separator = ":";
  String Print = mins + Separator + sec + Separator + milisecs;
  lcd.print(Print);
  }
  //If there's more than a minute left, display time as well
  else if(mins > 0){
  Serial.print(mins);
  Serial.print(":");
  Serial.print(sec);
  Serial.print(":");
  Serial.println(milisecs);
  
  lcd.clear();
  String Separator = ":";
  String Print = mins + Separator + sec + Separator + milisecs;
  lcd.print(Print);
  }
}
//When the countdown is completed
if(mins == 0 && sec == 0 && milisecs == 0){
  Detonate();
  armed = false;
  }
}

//This is what it does when it detonates
void Detonate(){
  Serial.println("Bang");
  detonated = false;
  lcd.clear();
  lcd.print("Bang!");
}
