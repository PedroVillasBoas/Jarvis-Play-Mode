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
  0b01110,  // Make a Sword pointed up!
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
///////////////// END OF LCD PART DECLARATION /////////////////

// Defining the variables
// Buttons
int numberButtons = 6;   // Total number of buttons
int startPin = 22;       // Start of buttons pin number
int buttons[6];          // List with all buttons
boolean buttonsBool[6];  // Bool to check button state
// Buzzer
const int miniSom = 28;  // Buzzer Pin number
// Game varibles
int pressNumber = 0;            // Total number of times that the player will have to press in game
int gameState = 1;              // Varible that defines the state of where the game is
int countDown;                  // Countdown number
bool canStartGame = false;      // Says when the 4D7SDisplay can display the players numbers
bool canGetNumberPress = true;  // Check to let the code know when the Players varibles can get the total number of presses
// Player Varibles
char playerOne;             // Set the byte number from the tens to show on the 4D7SDisplay from player one
char playerOneUnit;         // Set the byte number from the unit to show on the 4D7SDisplay from player one
char playerTwo;             // Set the byte number from the tens to show on the 4D7SDisplay from player two
char playerTwoUnit;         // Set the byte number from the unit to show on the 4D7SDisplay from player two
int checkPlayerOne;         // Checks to get the tens of the total number of presses from player one
int checkPlayerOneUnit;     // Checks to get the unit of the total number of presses from player one
int checkPlayerTwo;         // Checks to get the tens of the total number of presses from player two
int checkPlayerTwoUnit;     // Checks to get the unit of the total number of presses from player two
int playerOnePress;         // The remaining number of presses from player one
int playerTwoPress;         // The remaining number of presses from player two
bool playerOneWon = false;  // Check to see if player one won
bool playerTwoWon = false;  // Check to see if player two won
// State varibles
bool countDownState = true;  // Count Down Clear
bool state = true;           // First Screen Clear
bool state1 = true;          // Second Screen Clear
bool state2 = true;          // First gameState add to only add once
bool state3 = true;          // Third and final Screen Clear
bool hasPrinted = false;     // To be sure that it'll only print once
// Millis varibles (Avoid using Delay() function)
unsigned long previousMillis = 0;  // Get the time when the last button was pressed
unsigned long currentMillis;       // Get the total amount of time that has passed since the program started
const long interval = 100;         // Interval from the last time the button was pressed (I found 100 to be the best for me)
// Initializing a controller object to 4D7SDisplay
SevSeg sevseg;

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
  // Setting varibles of 4D7SDisplay
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);
  // Initializing LCD Display
  lcd.init();
  // Turns backlight on and clears the screen
  lcd.backlight();
  lcd.clear();
  // Initializing special characters
  lcd.createChar(5, heart);
  lcd.createChar(6, swordDown);
  lcd.createChar(7, swordUp);

  GameMenu();
}

void loop() {
  currentMillis = millis();
  GameManager();
  ButtonPressing();
  DisplayPlayersPresses();
}

void ButtonPressing() {
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    for (int i = 0; i < numberButtons; i++) {
      if (!buttonsBool[i]) {
        if (digitalRead(buttons[i]) == LOW) {
          if (i == 0) {  // Adds +1 to the total number of times to be pressed --> Green Button
            buttonsBool[i] = true;
            pressNumber++;
            lcd.clear();
            lcd.print(pressNumber);
          } else if (i == 1) {  // Adds +10 to the total number of times to be pressed --> Yellow Button
            buttonsBool[i] = true;
            pressNumber += 10;
            lcd.clear();
            lcd.print(pressNumber);
          } else if (i == 2) {  // Erase the total number of times to be pressed and clears the screen --> Red Button
            buttonsBool[i] = true;
            lcd.clear();
            pressNumber = 0;
          } else if (i == 3) {  // Confirm and goes to next game screen --> Blue Button
            buttonsBool[i] == true;
            gameState++;
          } else if (i == 4) {  // Player 1 button --> Arcade button Blue
            buttonsBool[i] = true;
            playerOnePress--;
          } else if (i == 5) {  // Player 2 button --> Arcade button Red
            buttonsBool[i] = true;
            playerTwoPress--;
          }
        } else {
          if (digitalRead(buttons[i]) == HIGH) {
            buttonsBool[i] = false;
          }
        }
      }
    }
  }
}

void GameManager() {
  switch (gameState) {
    case 1:  // Menu Screen
      StopAllButtons();
      break;
    case 2:  // Setup Screen
      GameSetup();
      break;
    case 3:  // In Game
      GameStart();
      break;
    case 4:  // End Screen
      if (playerOneWon) {
        PlayerOneEndScreen();  // Displays the Player One End Screen
      } else if (playerTwoWon) {
        PlayerTwoEndScreen();  // Displays the Player Two End Screen
      }
  }
}

void GameMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Jarvis Play Mode");
  lcd.setCursor(0, 1);
  lcd.write(7);
  lcd.setCursor(1, 1);
  lcd.write(6);
  lcd.setCursor(2, 1);
  lcd.write(7);
  lcd.setCursor(3, 1);
  lcd.print("Press Blue");
  lcd.write(7);
  lcd.write(6);
  lcd.write(7);
}

void GameSetup() {
  PlayAllSetupButtons();  // Set the state of setup buttons back to false (functional)
  ClearScreenOnce();      // Clear the screen one time
  lcd.setCursor(0, 0);    // Set cursor to the start of LCD
  lcd.print("How many points?");
  lcd.setCursor(0, 1);     // Set cursor to the start of second roll of LCD
  lcd.print(pressNumber);  // Print the pressNumber varible (number of times to be pressed in game)
}

void GameStart() {
  CountDown();
  StopButtons();
  ClearScreenOnceAgain();
  canStartGame = true;  // Set the 4D7SDisplay to display the remaining number of presses for player one
  if (hasPrinted == false) {
    lcd.setCursor(0, 0);
    lcd.write(7);
    lcd.setCursor(1, 0);
    lcd.write(6);
    lcd.setCursor(2, 0);
    lcd.write(7);
    lcd.setCursor(3, 0);
    lcd.write(6);
    lcd.setCursor(4, 0);
    lcd.write(7);
    lcd.setCursor(5, 0);
    lcd.print("BATTLE");
    lcd.setCursor(11, 0);
    lcd.write(7);
    lcd.setCursor(12, 0);
    lcd.write(6);
    lcd.setCursor(13, 0);
    lcd.write(7);
    lcd.setCursor(14, 0);
    lcd.write(6);
    lcd.setCursor(15, 0);
    lcd.write(7);
    hasPrinted = true;
  }
}

void StopAllButtons() {  // Stops all buttons, exept the confirm (Blue button)
  buttonsBool[0] = true;
  buttonsBool[1] = true;
  buttonsBool[2] = true;
  buttonsBool[4] = true;
  buttonsBool[5] = true;
}

void StopButtons() {  // Stops setup buttons and turn on Arcade Buttons
  buttonsBool[1] = true;
  buttonsBool[2] = true;
  buttonsBool[4] = false;
  buttonsBool[5] = false;
}

void PlayAllSetupButtons() {  // Turn on all setup buttons
  buttonsBool[0] = false;
  buttonsBool[1] = false;
  buttonsBool[2] = false;
}

void ClearScreenOnce() {  // Clear the screen
  if (state) {
    lcd.clear();
    state = false;
  }
}

void ClearScreenOnceAgain() {  // Clear the screen
  if (state1) {
    lcd.clear();
    state1 = false;
  }
}

void ClearScreenOnceAgainAgain() {  // Clear the screen
  if (state3) {
    lcd.clear();
    state3 = false;
  }
}

void AddOneToGameStateOnce() {
  if (state2) {
    gameState++;
    state2 = false;
  }
}

void CountDown() {  // CountDown from 3
  if (countDownState) {
    for (countDown = 3; countDown > 0; countDown--) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(countDown);
      delay(1000);
    }
    countDownState = false;  // Stops de CountDown
  }
}

void DisplayPlayersPresses() {
  if (canStartGame) {         // Check to see if the 4D7SDisplay can display the remaining number of presses
    if (canGetNumberPress) {  // To be sure it won't get the number every loop
      playerOnePress = pressNumber;
      playerTwoPress = pressNumber;
      canGetNumberPress = false;  // Set it to false so it doesn't get the number of presses again
    }
  }
  if (playerOnePress != 0 || playerTwoPress != 0) {  // Check to see if there's any presses remaining
    if (playerOnePress / 10 > 0) {                   // Get the tens number if there's one
      checkPlayerOne = playerOnePress / 10;
      if (checkPlayerOne == 1) {  // All ifs and else ifs sets the playerOne char varible to a bit code to show at the display
        playerOne = (0b00000110);
        sevseg.setSegmentsDigit(0, playerOne);  // Display the number on the first digit of the display, in this case the number 1 on digit 1
      } else if (checkPlayerOne == 2) {
        playerOne = (0b01011011);
        sevseg.setSegmentsDigit(0, playerOne);
      } else if (checkPlayerOne == 3) {
        playerOne = (0b01001111);
        sevseg.setSegmentsDigit(0, playerOne);
      } else if (checkPlayerOne == 4) {
        playerOne = (0b01100110);
        sevseg.setSegmentsDigit(0, playerOne);
      } else if (checkPlayerOne == 5) {
        playerOne = (0b01101101);
        sevseg.setSegmentsDigit(0, playerOne);
      } else if (checkPlayerOne == 6) {
        playerOne = (0b01111101);
        sevseg.setSegmentsDigit(0, playerOne);
      } else if (checkPlayerOne == 7) {
        playerOne = (0b00000111);
        sevseg.setSegmentsDigit(0, playerOne);
      } else if (checkPlayerOne == 8) {
        playerOne = (0b01111111);
        sevseg.setSegmentsDigit(0, playerOne);
      } else if (checkPlayerOne == 9) {
        playerOne = (0b01101111);
        sevseg.setSegmentsDigit(0, playerOne);
      }
    } else {  // If the number divided by 10 is less than 0, it doesn't have a tens anymore, so it should display 0
      playerOne = (0b00111111);
      sevseg.setSegmentsDigit(0, playerOne);
    }
    if (playerOnePress % 10 >= 0) {              // Gets the unid number of the total number of presses
      checkPlayerOneUnit = playerOnePress % 10;  // Set the unid number
      if (checkPlayerOneUnit == 0) {             // All ifs and else ifs sets the playerOneUnit char varible to a bit code to show at the display
        playerOneUnit = (0b00111111);
        sevseg.setSegmentsDigit(1, playerOneUnit);  // Display the number on the second digit of the display, in this case the number 0 on digit 2
      } else if (checkPlayerOneUnit == 1) {
        playerOneUnit = (0b00000110);
        sevseg.setSegmentsDigit(1, playerOneUnit);
      } else if (checkPlayerOneUnit == 2) {
        playerOneUnit = (0b01011011);
        sevseg.setSegmentsDigit(1, playerOneUnit);
      } else if (checkPlayerOneUnit == 3) {
        playerOneUnit = (0b01001111);
        sevseg.setSegmentsDigit(1, playerOneUnit);
      } else if (checkPlayerOneUnit == 4) {
        playerOneUnit = (0b01100110);
        sevseg.setSegmentsDigit(1, playerOneUnit);
      } else if (checkPlayerOneUnit == 5) {
        playerOneUnit = (0b01101101);
        sevseg.setSegmentsDigit(1, playerOneUnit);
      } else if (checkPlayerOneUnit == 6) {
        playerOneUnit = (0b01111101);
        sevseg.setSegmentsDigit(1, playerOneUnit);
      } else if (checkPlayerOneUnit == 7) {
        playerOneUnit = (0b00000111);
        sevseg.setSegmentsDigit(1, playerOneUnit);
      } else if (checkPlayerOneUnit == 8) {
        playerOneUnit = (0b01111111);
        sevseg.setSegmentsDigit(1, playerOneUnit);
      } else if (checkPlayerOneUnit == 9) {
        playerOneUnit = (0b01101111);
        sevseg.setSegmentsDigit(1, playerOneUnit);
      }
    }
    if (playerTwoPress / 10 > 0) {  // Get the tens number if there's one
      checkPlayerTwo = playerTwoPress / 10;
      if (checkPlayerTwo == 1) {  // All ifs and else ifs sets the playerTwo char varible to a bit code to show at the display
        playerTwo = (0b00000110);
        sevseg.setSegmentsDigit(2, playerTwo);  // Display the number on the first digit of the display, in this case the number 1 on digit 3
      } else if (checkPlayerTwo == 2) {
        playerTwo = (0b01011011);
        sevseg.setSegmentsDigit(2, playerTwo);
      } else if (checkPlayerTwo == 3) {
        playerTwo = (0b01001111);
        sevseg.setSegmentsDigit(2, playerTwo);
      } else if (checkPlayerTwo == 4) {
        playerTwo = (0b01100110);
        sevseg.setSegmentsDigit(2, playerTwo);
      } else if (checkPlayerTwo == 5) {
        playerTwo = (0b01101101);
        sevseg.setSegmentsDigit(2, playerTwo);
      } else if (checkPlayerTwo == 6) {
        playerTwo = (0b01111101);
        sevseg.setSegmentsDigit(2, playerTwo);
      } else if (checkPlayerTwo == 7) {
        playerTwo = (0b00000111);
        sevseg.setSegmentsDigit(2, playerTwo);
      } else if (checkPlayerTwo == 8) {
        playerTwo = (0b01111111);
        sevseg.setSegmentsDigit(2, playerTwo);
      } else if (checkPlayerTwo == 9) {
        playerTwo = (0b01101111);
        sevseg.setSegmentsDigit(2, playerTwo);
      }
    } else {  // If the number divided by 10 is less than 0, it doesn't have a tens anymore, so it should display 0
      playerTwo = (0b00111111);
      sevseg.setSegmentsDigit(2, playerTwo);
    }
    if (playerTwoPress % 10 >= 0) {              // Gets the unid number of the total number of presses
      checkPlayerTwoUnit = playerTwoPress % 10;  // Set the unid number
      if (checkPlayerTwoUnit == 0) {             // All ifs and else ifs sets the playerTwoUnit char varible to a bit code to show at the display
        playerTwoUnit = (0b00111111);
        sevseg.setSegmentsDigit(3, playerTwoUnit);  // Display the number on the second digit of the display, in this case the number 0 on digit 4
      } else if (checkPlayerTwoUnit == 1) {
        playerTwoUnit = (0b00000110);
        sevseg.setSegmentsDigit(3, playerTwoUnit);
      } else if (checkPlayerTwoUnit == 2) {
        playerTwoUnit = (0b01011011);
        sevseg.setSegmentsDigit(3, playerTwoUnit);
      } else if (checkPlayerTwoUnit == 3) {
        playerTwoUnit = (0b01001111);
        sevseg.setSegmentsDigit(3, playerTwoUnit);
      } else if (checkPlayerTwoUnit == 4) {
        playerTwoUnit = (0b01100110);
        sevseg.setSegmentsDigit(3, playerTwoUnit);
      } else if (checkPlayerTwoUnit == 5) {
        playerTwoUnit = (0b01101101);
        sevseg.setSegmentsDigit(3, playerTwoUnit);
      } else if (checkPlayerTwoUnit == 6) {
        playerTwoUnit = (0b01111101);
        sevseg.setSegmentsDigit(3, playerTwoUnit);
      } else if (checkPlayerTwoUnit == 7) {
        playerTwoUnit = (0b00000111);
        sevseg.setSegmentsDigit(3, playerTwoUnit);
      } else if (checkPlayerTwoUnit == 8) {
        playerTwoUnit = (0b01111111);
        sevseg.setSegmentsDigit(3, playerTwoUnit);
      } else if (checkPlayerTwoUnit == 9) {
        playerTwoUnit = (0b01101111);
        sevseg.setSegmentsDigit(3, playerTwoUnit);
      }
    }
    if (playerOnePress == 0) {
      StopAllButtons();
      playerOneWon = true;
      AddOneToGameStateOnce();
    } else if (playerTwoPress == 0) {
      StopAllButtons();
      playerTwoWon = true;
      AddOneToGameStateOnce();
    }
    sevseg.refreshDisplay();  // refresh the display
  }
}

void PlayerOneEndScreen() {  // End Screen for Player One
  ClearScreenOnceAgainAgain();
  lcd.setCursor(0, 0);
  lcd.write(5);
  lcd.setCursor(1, 0);
  lcd.write(5);
  lcd.setCursor(2, 0);
  lcd.write(5);
  lcd.setCursor(3, 0);
  lcd.print("Player One");
  lcd.setCursor(13, 0);
  lcd.write(5);
  lcd.setCursor(14, 0);
  lcd.write(5);
  lcd.setCursor(15, 0);
  lcd.write(5);
  lcd.setCursor(6, 1);
  lcd.print("WON!");
  Music();
}

void PlayerTwoEndScreen() {  // End Screen for Player Two
  ClearScreenOnceAgainAgain();
  lcd.setCursor(0, 0);
  lcd.write(5);
  lcd.setCursor(1, 0);
  lcd.write(5);
  lcd.setCursor(2, 0);
  lcd.write(5);
  lcd.setCursor(3, 0);
  lcd.print("Player Two");
  lcd.setCursor(13, 0);
  lcd.write(5);
  lcd.setCursor(14, 0);
  lcd.write(5);
  lcd.setCursor(15, 0);
  lcd.write(5);
  lcd.setCursor(6, 1);
  lcd.print("WON!");
  Music();
}
