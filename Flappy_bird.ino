/*
 * Goal: To design a "flappy bird" style game. It implements the push buttton
 *       to move the character around the road blocks.
 * 
 * Steps:
 * 1. Build road blocks
 * 2. Design flappy bird character
 * 3. Implement 2 buttons to move "flappy bird" up and down
 * 
 */

// To make display easier to program
#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

byte bigBlock[8] = {
0b01110,
0b01110,
0b01110,
0b01110,
0b01110,
0b01110,
0b01110,
0b01110 };

byte littleBlockLower0[8] = { // position 0
0b00000,
0b00000,
0b00000,
0b00000,
0b01110,
0b01110,
0b01110,
0b01110 };

byte littleBlockLower1[8] = { // position 1
0b01110,
0b01110,
0b01110,
0b01110 ,
0b00000,
0b00000,
0b00000,
0b00000 };

byte littleBlockUpper[8] = {
0b00000,
0b00000,
0b00000,
0b00000,
0b01110,
0b01110,
0b01110,
0b01110 };

byte flappy[8] = {
0b01110,
0b11111,
0b01110, 
0b00000,
0b00000,
0b00000,
0b00000,
0b00000 };

const int horizontalButton = 8; // digital input connected to button motion 'RIGHT'
const int verticalButton = 9; // digital input connected to button motion 'UP' 'DOWN'
const int greenLED = 10; // green light go

// Button states
const int pressed = 1;
const int notpressed = 0;
int lastHorizontalState = 0;
int lastVerticalState = 0;

// flappy starting position
int col = 15;
int row = 1;

void setup() {
  lcd.begin(16, 2);
  
  // Road blocks
  lcd.createChar(0, bigBlock);
  lcd.createChar(1, littleBlockLower1);
  lcd.createChar(2, littleBlockLower0);  
  lcd.createChar(3, littleBlockUpper);

  // flappy bird character
  lcd.createChar(4, flappy);

  // define pins 
  pinMode(horizontalButton, INPUT);
  pinMode(verticalButton, INPUT);
  pinMode(greenLED, OUTPUT);
  Serial.begin(1200);

} // end setup()

void loop() {
  
  // build maze
  lcd.setCursor(15,0);
  lcd.write(byte(1));

  //lcd.setCursor(14,0);
  //lcd.write(byte(1));

  lcd.setCursor(13,1);
  lcd.write(byte(3));

  //lcd.setCursor(12,0);
  //lcd.write(byte(2));

  lcd.setCursor(12,1);
  lcd.write(byte(0));

  //lcd.setCursor(11,1);
  //lcd.write(byte(3));

  lcd.setCursor(10,0);
  lcd.write(byte(0));

  //lcd.setCursor(10,1);
  //lcd.write(byte(3));

  lcd.setCursor(8,1);
  lcd.write(byte(0));

  //lcd.setCursor(7,0);
  //lcd.write(byte(1));

  lcd.setCursor(7,1);
  lcd.write(byte(0));

  lcd.setCursor(5,0);
  lcd.write(byte(1));

  //lcd.setCursor(5,1);
  //lcd.write(byte(3));

  lcd.setCursor(4,0);
  lcd.write(byte(0));

  //lcd.setCursor(3,0);
  //lcd.write(byte(1));

  //lcd.setCursor(3,1);
  //lcd.write(byte(3));

  lcd.setCursor(2,0);
  lcd.write(byte(0));
  
  //lcd.setCursor(1,0);
  //lcd.write(byte(2));

  lcd.setCursor(0,1);
  lcd.write(byte(3));

  lcd.setCursor(0,0);
  lcd.print(char(219));

  lcd.setCursor(col, row);
  lcd.write(byte(4));
  
  // Has the button been pressed
  int horizontalState = digitalRead(horizontalButton);
  Serial.println(horizontalState);
  delay(20); // any faster my computer restarts

  int verticalState = digitalRead(verticalButton);
  Serial.println(verticalState);
  delay(20);

  // horizontal button function
  if (horizontalState != lastHorizontalState) {
    if (horizontalState == pressed) {
      col = col - pressed; } 
    else if (horizontalState == notpressed) {
      col = col - notpressed; }
  }
  lastHorizontalState = horizontalState; // update column position for next loop
  
  // vertical button function
  if (verticalState != lastVerticalState) {
    if (verticalState == pressed && row == 1) {
      row = row - pressed; }    
    else if (verticalState == pressed && row == 0) {
      row = row + pressed; }
    else if (verticalState == notpressed) {
      row = row; }
   }
   lastVerticalState = verticalState; // update vertical position for next loop

  // move flappy
  lcd.clear();
  lcd.setCursor(col, row);
  lcd.write(byte(4));

  if (col == 0 && row == 0) {
    digitalWrite(greenLED, HIGH);
   }
  else {
    digitalWrite(greenLED, LOW);
   }
}
