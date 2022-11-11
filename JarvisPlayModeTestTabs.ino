// Libraries
#include <Wire.h>               // Nao lembro
#include <LiquidCrystal_I2C.h>  // Tela 16,2
#include <SevSeg.h>             // 4 Digit 7 Segment Display (4D7SDisplay)
///////////////// INICIO DA DECLARACAO DA PARTE DE MUSICA /////////////////
// Define cada nota para um frequencia em hertz
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
///////////////// FIM DA DECLARACAO DA PARTE DE MUSICA /////////////////

///////////////// INICIO DA DECLARACAO DA PARTE DO LEDs /////////////////
byte numDigits = 4;
byte digitPins[] = { 2, 3, 4, 5 };
byte segmentPins[] = { 6, 7, 8, 9, 10, 11, 12, 13 };
bool resistorsOnSegments = 0;
///////////////// FIM DA DECLARACAO DA PARTE DO LEDs /////////////////

///////////////// INICIO DA DECLARACAO DA PARTE DO LCD /////////////////
// Seta o adress da LCD para 0x3F para 16 chars e 2 linhas do display
LiquidCrystal_I2C lcd(0x3F, 16, 2);
// Declaracao dos characteres especiais que vao ser usados na LCD
byte swordDown[8] = {
  0b00100,
  0b00100,
  0b11111,
  0b01110,   // Faz o character de uma espada!
  0b01110,
  0b01110,
  0b01110,
  0b00100
};
byte swordUp[8] = {
  0b00100,
  0b01110,
  0b01110,
  0b01110,
  0b01110,
  0b11111,
  0b00100,
  0b00100
};
byte heart[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,   // Faz o character de um coracao!
  0b01110,
  0b00100,
  0b00000,
  0b00000
};
///////////////// FIM DA DECLARACAO DA PARTE DO LCD /////////////////

// Definindo as variaveis
  // Botoes
int numberButtons = 6;   // Numero total de botoes
int startPin = 22;       // Onde comeca a porta dos botoes
int buttons[6];          // Lista com todos os botoes
boolean buttonsBool[6];  // Bool pra checar o estado do botao
  // Buzzer
const int miniSom = 28;  // Pin do MiniSom
  // Jogo
int pressNumber = 0;  // Numero total de vezes que vao ser apertadas no jogo
int gameBegin = 0; // Variavel de vericacao para saber quando mudar para a tela de Setup (So faz algo quando estiver em 1)
int inGame = 0; // Variavel de vericacao para saber quando mudar para a tela de Jogo (So faz algo quando estiver em 2)

void setup() {
  Serial.begin(9600);
  // Inicilizando todos os botoes em seus respectivos pins
  for (int i = 0; i < numberButtons; i++)
    buttons[i] = i + startPin;
  // Setando todos os botoes para o estado de falso
  for (int i = 0; i < numberButtons; i++)
    buttonsBool[i] = false;
  // Setando todos os botoes para o estado de input pullup
  for (int i = 0; i < numberButtons; i++)
    pinMode(buttons[i], INPUT_PULLUP);
  // Setando o buzzer para o estado de output
  pinMode(miniSom, OUTPUT);
  //Inicializando um objeto controller do 4D7SDisplay
  SevSeg sevseg;
  // Setando as variaveis do 4D7SDisplay
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);
  // inicializando o lcd
  lcd.init();
  // Liga a luz de fundo e limpa a tela com o clear
  lcd.backlight();
  lcd.clear();
  // Inicializando os characteres especiais
  lcd.createChar(1, heart);
  lcd.createChar(2, swordDown);
  lcd.createChar(3, swordUp);

  //Music();
  GameMenu();
}

void loop() {
  ButtonPressing();
  GameManager();

}

void ButtonPressing() {
  for (int i = 0; i < numberButtons; i++) {
    if (!buttonsBool[i]) {
      if (digitalRead(buttons[i]) == LOW) {
        if (i == 0) { // Adicionador +1
          pressNumber++;
          lcd.clear();
          lcd.print(pressNumber);
          buttonsBool[i] = true;
        } else if (i == 1) { // Adicionador +10
          pressNumber += 10;
          lcd.clear();
          lcd.print(pressNumber);
          buttonsBool[i] = true;
        } else if (i == 2) { // Botao Green para ?? coisas
          lcd.clear();
          pressNumber = 0;
        } else if (i == 3) { // Botao Blue para confirmar
          gameBegin++;
          inGame++;
          buttonsBool[i] = true;
        } else if (i == 4) {
          lcd.clear();
          lcd.print("Player 1 funcionando!");
          buttonsBool[i] = true;
        } else if (i == 5) {
          lcd.clear();
          lcd.print("Player 2 funcionando!");
          buttonsBool[i] = true;
        }
      }
    } else {
      if (digitalRead(buttons[i]) == HIGH) {
        buttonsBool[i] = false;
      }
    }
  }
  delay(15);
}

void GameMenu(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Jarvis Play Mode");
  lcd.setCursor(0,1);
  lcd.write(3);
  lcd.setCursor(1,1);
  lcd.write(2);
  lcd.setCursor(2,1);
  lcd.write(3);
  lcd.setCursor(3,1);
  lcd.print("Press Blue");
  lcd.write(3);
  lcd.write(2);
  lcd.write(3);
}
void GameSetup(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("How many points?");
  lcd.setCursor(0, 1);
  lcd.print("G = +1 / Y = +10");
}
void GameManager(){
  if(gameBegin == 0 || inGame == 2){
    buttonsBool[0] = true;
    buttonsBool[1] = true;
    buttonsBool[2] = true;
    buttonsBool[4] = true;
    buttonsBool[5] = true;
  }
  if(gameBegin == 1){
    GameSetup();
  } else if(gameBegin > 1 && inGame == 2){
    Music();
  }
}