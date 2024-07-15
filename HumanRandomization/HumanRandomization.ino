//This code uses human input to generate a random seed by measuring the time it takes to press a button in milliseconds. It also uses one analog input to read the 4x4 keypad.  I've included the wiring diagram.

// 30 Days Lost in Space
// Human input for randomization
// Matt Jackson

// https://www.youtube.com/watch?v=G14tREsVqz0
// https://www.factoryforward.com/use-matrix-keypad-single-arduino-pin/
// https://fritzing.org/projects/4x4-membrane-keypad-analog-in
#include <OnewireKeypad.h>
#include <Wire.h>
#include <TonePitch.h>
#define buzzer 10
const int redPin = 12;   //  color output pins
const int yellowPin = 8;
const int greenPin = 7;
const int bluePin = 4;
char key = NULL;
char KEYS[] = {
'1', '2', '3', 'A',
'4', '5', '6', 'B',
'7', '8', '9', 'C',
'*', '0', '#', 'D'
};
int voltage = 0;
byte KState;
OnewireKeypad <Print, 16> KP2(Serial, KEYS, 4, 4, A0, 220, 1000, 100000 );
int tones[] = { NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5};
int LED[] = {redPin, yellowPin, greenPin, bluePin};
char getKey() {
while (1) {
KState = KP2.Key_State();
if (KState == PRESSED) {
voltage = analogRead(A0);
//Serial << "Voltage: " << voltage << "\n";
if ((voltage >= 730 ) && (voltage <= 735)) {
return KEYS[0];
} else if ((voltage >= 785) && (voltage <= 790)) {
return KEYS[1];
} else if ((voltage >= 850) && (voltage <= 855)) {
return KEYS[2];
// keypad button S3 has to be pressed hard to register
} else if ((voltage >= 930) && (voltage <= 935)) {
return KEYS[3];
}else if ((voltage >= 720) && (voltage <= 725)) {
return KEYS[4];
}else if ((voltage >= 775) && (voltage <= 780)) {
return KEYS[5];
}else if ((voltage >= 835) && (voltage <= 840)) {
return KEYS[6];
}else if ((voltage >= 910) && (voltage <= 915)) {
return KEYS[7];
}else if ((voltage >= 705) && (voltage <= 710)) {
return KEYS[8];
}else if ((voltage >= 760) && (voltage <= 765)) {
return KEYS[9];
}else if ((voltage >= 820) && (voltage <= 825)) {
return KEYS[10];
}else if ((voltage >= 895) && (voltage <= 900)) {
return KEYS[11];
}else if ((voltage >= 695) && (voltage <= 700)) {
return KEYS[12];
}else if ((voltage >= 750) && (voltage <= 755)) {
return KEYS[13];
}else if ((voltage >= 805) && (voltage <= 810)) {
return KEYS[14];
}else if ((voltage >= 875) && (voltage <= 880)) {
return KEYS[15];
} else {
return NULL;
}
}
}
}
void randomize(){
// Human randomization
Serial << "Press any key to get random seed...";
key = NULL;
int then = millis();
while (!key) {
key = getKey();
}
int now = millis();
int seed = now - then;
key = '0';
Serial << "Random seed = " << seed << "\n";
randomSeed(seed);
}
void flash(int pin){
digitalWrite(pin, HIGH);
delay(500);
digitalWrite(pin, LOW);
delay(500);
//randomize();
}
void playRandTones(int note){
tone(buzzer, tones[note], 500);  //  play the tone for a half second
delay(500);
noTone(buzzer);
}
void setup() {
key = '0';
Serial.begin(9600);
Wire.begin();
pinMode (redPin, OUTPUT);
pinMode (yellowPin, OUTPUT);
pinMode (greenPin, OUTPUT);
pinMode (bluePin, OUTPUT);
KP2.SetKeypadVoltage(5.0);
randomize();
}
void loop(){
//flash(redPin);
//flash(yellowPin);
//flash(greenPin);
//flash(bluePin);
//Serial << getKey() << "\n";
flash(LED[random(4)]);
//playRandTones(random(8));
}