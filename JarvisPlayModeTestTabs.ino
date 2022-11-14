// Libraries
#include <Wire.h>               // 16,2 LCD Screen
#include <LiquidCrystal_I2C.h>  // 16,2 LCD Screen
#include <SevSeg.h>             // 4 Digit 7 Segment Display (4D7SDisplay)
///////////////// BEGIN OF MUSIC PART DECLARATION /////////////////
// Define each note to a frequence in hertz
#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978
#define REST 0

// change this to make the song slower or faster
int tempo = 108;  // 108 is standard.

// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody[] = {

  NOTE_E4,
  2,
  NOTE_G4,
  4,
  NOTE_D4,
  2,
  NOTE_C4,
  8,
  NOTE_D4,
  8,
  NOTE_E4,
  2,
  NOTE_G4,
  4,
  NOTE_D4,
  -2,
  NOTE_E4,
  2,
  NOTE_G4,
  4,
  NOTE_D5,
  2,
  NOTE_C5,
  4,
  NOTE_G4,
  2,
  NOTE_F4,
  8,
  NOTE_E4,
  8,
  NOTE_D4,
  -2,
  NOTE_E4,
  2,
  NOTE_G4,
  4,
  NOTE_D4,
  2,
  NOTE_C4,
  8,
  NOTE_D4,
  8,
  NOTE_E4,
  2,
  NOTE_G4,
  4,
  NOTE_D4,
  -2,
  NOTE_E4,
  2,
  NOTE_G4,
  4,

  NOTE_D5,
  2,
  NOTE_C5,
  4,
  NOTE_G4,
  2,
  NOTE_F4,
  8,
  NOTE_E4,
  8,
  NOTE_F4,
  8,
  NOTE_E4,
  8,
  NOTE_C4,
  2,
  NOTE_F4,
  2,
  NOTE_E4,
  8,
  NOTE_D4,
  8,
  NOTE_E4,
  8,
  NOTE_D4,
  8,
  NOTE_A3,
  2,
  NOTE_G4,
  2,
  NOTE_F4,
  8,
  NOTE_E4,
  8,
  NOTE_F4,
  8,
  NOTE_E4,
  8,
  NOTE_C4,
  4,
  NOTE_F4,
  4,
  NOTE_C5,
  -2,

};

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;
///////////////// END OF MUSIC PART DECLARATION /////////////////

///////////////// BEGIN OF LEDs PART DECLARATION /////////////////
byte numDigits = 4;
byte digitPins[] = { 2, 3, 4, 5 };
byte segmentPins[] = { 6, 7, 8, 9, 10, 11, 12, 13 };
bool resistorsOnSegments = 0;
///////////////// END OF LEDs PART DECLARATION /////////////////

///////////////// BEGIN OF LCD PART DECLARATION /////////////////
// Set LCD address to 0x3F for 16 chars and 2 display lines
// 
LiquidCrystal_I2C lcd(0x3F, 16, 2);
// Declaration of special characters that will be used on the LCD
byte swordDown[8] = {
  0b00100,
  0b00100,
  0b11111,
  0b01110,  // Make a Sword pointed down!
  0b01110,
  0b01110,
  0b01110,
  0b00100
};
byte swordUp[8] = {
  0b00100,
  0b01110,
  0b01110,
  0b01110, // Make a Sword pointed up!
  0b01110,
  0b11111,
  0b00100,
  0b00100
};
byte heart[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,  // Make a Heart!
  0b01110,
  0b00100,
  0b00000,
  0b00000
};
///////////////// FIM DA DECLARACAO DA PARTE DO LCD /////////////////

// Defining the variables
// Buttons
int numberButtons = 6;   // Total number of buttons
int startPin = 22;       // Start of buttons pin number
int buttons[6];          // List with all buttons
boolean buttonsBool[6];  // Bool to check button state
// Buzzer
const int miniSom = 28;  // miniSom Pin number
// Game varibles
int pressNumber = 0;  // Total number of times that the player will have to press in game
int gameState = 1; // Varible that defines the state of where the game is

void setup() {
  Serial.begin(9600);
  // Initializing all buttons in their respectives pins
  for (int i = 0; i < numberButtons; i++)
    buttons[i] = i + startPin;
  // Setting all buttons to "false" state
  for (int i = 0; i < numberButtons; i++)
    buttonsBool[i] = false;
  // Setting all buttons to "input_pullup" state
  for (int i = 0; i < numberButtons; i++)
    pinMode(buttons[i], INPUT_PULLUP);
  // Setting buzzer to "output" state
  pinMode(miniSom, OUTPUT);
  // Initializing a controller object to 4D7SDisplay
  SevSeg sevseg;
  // Setting varibles of 4D7SDisplay 
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);
  // Initializing LCD Display
  lcd.init();
  // Turns backlight on and clears the screen
  lcd.backlight();
  lcd.clear();
  // Initializing special characters
  lcd.createChar(10, heart);
  lcd.createChar(20, swordDown);
  lcd.createChar(30, swordUp);

  GameMenu();
}

void loop() {
  GameManager();
  ButtonPressing();
}

void ButtonPressing() {
  for (int i = 0; i < numberButtons; i++) {
    if (!buttonsBool[i]) {
      if (digitalRead(buttons[i]) == LOW) {
        if (i == 0) {  // Adds +1 to the total number of times to be pressed --> Green Button
          pressNumber++;
          lcd.clear();
          lcd.print(pressNumber);
          buttonsBool[i] = true;
        } else if (i == 1) {  // Adds +10 to the total number of times to be pressed --> Yellow Button
          pressNumber += 10;
          lcd.clear();
          lcd.print(pressNumber);
          buttonsBool[i] = true;
        } else if (i == 2) {  // Erase the total number of times to be pressed and clears the screen --> Red Button
          lcd.clear();
          pressNumber = 0;
        } else if (i == 3) {  // Confirm and goes to next game screen --> Blue Button
          gameState += 1;
          buttonsBool[i] == true;
        } else if (i == 4) {  // Player 1 button --> Arcade button Blue
          lcd.clear();
          lcd.print("Player 1 funcionando!");
          buttonsBool[i] = true;
        } else if (i == 5) {  // Player 2 button --> Arcade button Red
          lcd.clear();
          lcd.print("Player 2 funcionando!");
          buttonsBool[i] = true;
        }
      } else {
        if (digitalRead(buttons[i]) == HIGH) {
          buttonsBool[i] = false;
        }
      }
    }
  }
  delay(15);
}
void GameMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Jarvis Play Mode");
  lcd.setCursor(0, 1);
  lcd.write(30);
  lcd.setCursor(1, 1);
  lcd.write(20);
  lcd.setCursor(2, 1);
  lcd.write(30);
  lcd.setCursor(3, 1);
  lcd.print("Press Blue");
  lcd.write(30);
  lcd.write(20);
  lcd.write(30);
}
void GameSetup() {
  lcd.clear();
  lcd.print("How many points?");
}
void GameStart() {
  lcd.clear();
  lcd.print("Did something...");
}
void GameManager() {
  switch (gameState){
    case 1: // Menu Screen
      StopAllButtons();
      break;
    case 2: // Setup Screen
      GameSetup();
      break;
    case 3:
      StopButtons();
      GameStart();
      break;
  }
}
void StopAllButtons(){ // Stops all buttons, exept the confirm (Blue button)
    buttonsBool[0] = true;
    buttonsBool[1] = true;
    buttonsBool[2] = true;
    buttonsBool[4] = true;
    buttonsBool[5] = true;
}
void StopButtons(){ // Stops all buttons, exept players (Arcades) and confirm (Blue) until game ends
    buttonsBool[0] = true;
    buttonsBool[1] = true;
    buttonsBool[2] = true;
    //buttonsBool[3] = true; // Only come back when the game ends
}
