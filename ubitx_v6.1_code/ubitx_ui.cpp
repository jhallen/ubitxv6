#include <Arduino.h>
#include <EEPROM.h>
#include "morse.h"
#include "ubitx.h"
#include "nano_gui.h"

// Main screen layout..

// Command box, between VFOs and main buttons
#define COMMAND_TEXT_X 0
#define COMMAND_TEXT_Y 48
#define COMMAND_TEXT_WIDTH 280 // "TX" indicator is to the right of this box
#define COMMAND_TEXT_HEIGHT 28

#define TX_TEXT_X 280
#define TX_TEXT_Y 48
#define TX_TEXT_WIDTH 37
#define TX_TEXT_HEIGHT 28

// Status line, at bottom of screen
#define STATUS_TEXT_X 0
#define STATUS_TEXT_Y 201
#define STATUS_TEXT_WIDTH 200 // Version string is to right of this
#define STATUS_TEXT_HEIGHT 39

#define VERSION_TEXT_X 260
#define VERSION_TEXT_Y 201
#define VERSION_TEXT_WIDTH 60
#define VERSION_TEXT_HEIGHT 39

/**
 * The user interface of the ubitx consists of the encoder, the push-button on top of it
 * and the 16x2 LCD display.
 * The upper line of the display is constantly used to display frequency and status
 * of the radio. Occasionally, it is used to provide a two-line information that is 
 * quickly cleared up.
 */

#define BUTTON_SELECTED 1

struct Button {
  int x, y, w, h;
  char *text;
  char *morse;
};

#define MAX_BUTTONS 17
const struct Button btn_set[MAX_BUTTONS] PROGMEM = { 
//const struct Button  btn_set [] = {
  {0, 10, 159, 36,  "VFOA", "A"},
  {160, 10, 159, 36, "VFOB", "B"},
  
  {0, 80, 60, 36,  "RIT", "R"},
  {64, 80, 60, 36, "USB", "U"},
  {128, 80, 60, 36, "LSB", "L"},
  {192, 80, 60, 36, "CW", "M"},
  {256, 80, 60, 36, "SPL", "S"},

  {0, 120, 60, 36, "80", "8"},
  {64, 120, 60, 36, "40", "4"},
  {128, 120, 60, 36, "30", "3"},
  {192, 120, 60, 36, "20", "2"},
  {256, 120, 60, 36, "17", "7"},

  {0, 160, 60, 36, "15", "5"},
  {64, 160, 60, 36, "10", "1"},
  {128, 160, 60, 36, "WPM", "W"},
  {192, 160, 60, 36, "TON", "T"},
  {256, 160, 60, 36, "FRQ", "F"},
};

#define MAX_KEYS 17
const struct Button keypad[MAX_KEYS] PROGMEM = {   
  {0, 80, 60, 36,  "1", "1"},
  {64, 80, 60, 36, "2", "2"},
  {128, 80, 60, 36, "3", "3"},
  {192, 80, 60, 36,  "", ""},
  {256, 80, 60, 36,  "OK", "K"},

  {0, 120, 60, 36,  "4", "4"},
  {64, 120, 60, 36,  "5", "5"},
  {128, 120, 60, 36,  "6", "6"},
  {192, 120, 60, 36,  "0", "0"},
  {256, 120, 60, 36,  "<-", "B"},

  {0, 160, 60, 36,  "7", "7"},
  {64, 160, 60, 36, "8", "8"},
  {128, 160, 60, 36, "9", "9"},
  {192, 160, 60, 36,  "", ""},
  {256, 160, 60, 36,  "Can", "C"},
};

boolean getButton(char *text, struct Button *b){
  for (int i = 0; i < MAX_BUTTONS; i++){
    memcpy_P(b, btn_set + i, sizeof(struct Button));
    if (!strcmp(text, b->text)){
      return true;
    }
  }
  return false;
}


/*
 * This formats the frequency given in f 
 */
void formatFreq(long f, char *buff) {
  // tks Jack Purdum W8TEE
  // replaced fsprint commmands by str commands for code size reduction

  memset(buff, 0, 10);
  memset(b, 0, sizeof(b));

  ultoa(f, b, DEC);

  //one mhz digit if less than 10 M, two digits if more
  if (f < 1000000l){
    buff[0] = ' ';
    buff[1] = ' ';
    strncat(buff, b, 3);    
    strcat(buff, ".");
    strncat(buff, &b[3], 2);
  }
  else if (f < 10000000l){
    buff[0] = ' ';
    strncat(buff, b, 4);    
    strcat(buff, ".");
    strncat(buff, &b[4], 2);
  }
  else {
    strncat(buff, b, 5);
    strcat(buff, ".");
    strncat(buff, &b[5], 2);    
  }
}

void drawCommandbar(char *text){
  displayText(text, COMMAND_TEXT_X, COMMAND_TEXT_Y, COMMAND_TEXT_WIDTH, COMMAND_TEXT_HEIGHT, DISPLAY_WHITE, DISPLAY_NAVY, DISPLAY_NAVY, LEFT);
}

void clearCommandbar()
{
  displayFillrect(COMMAND_TEXT_X, COMMAND_TEXT_Y, COMMAND_TEXT_WIDTH, COMMAND_TEXT_HEIGHT, DISPLAY_NAVY);
}

/** A generic control to read variable values
*/
int getValueByKnob(int minimum, int maximum, int step_size,  int initial, char* prefix, char *postfix)
{
    int knob = 0;
    int knob_value;

    while (btnDown())
      active_delay(100);

    active_delay(200);
    knob_value = initial;
     
    strcpy(b, prefix);
    itoa(knob_value, c, 10);
    strcat(b, c);
    strcat(b, postfix);
    drawCommandbar(b);

    while(!btnDown() && digitalRead(PTT) == HIGH){

      knob = enc_read();
      if (knob != 0){
        if (knob_value > minimum && knob < 0)
          knob_value -= step_size;
        if (knob_value < maximum && knob > 0)
          knob_value += step_size;
          
        strcpy(b, prefix);
        itoa(knob_value, c, 10);
        strcat(b, c);
        strcat(b, postfix);
        drawCommandbar(b);
      }
      checkCAT();
    }
   clearCommandbar();
   return knob_value;
}

void printCarrierFreq(unsigned long freq){

  memset(c, 0, sizeof(c));
  memset(b, 0, sizeof(b));

  ultoa(freq, b, DEC);
  
  strncat(c, b, 2);
  strcat(c, ".");
  strncat(c, &b[2], 3);
  strcat(c, ".");
  strncat(c, &b[5], 1);
  displayText(c, 110, 100, 100, 30, DISPLAY_CYAN, DISPLAY_NAVY, DISPLAY_NAVY, CENTERED);
}

void displayDialog(char *title, char *instructions){
  displayClear(DISPLAY_NAVY);
  displayRect(10,10,300,220, DISPLAY_WHITE);
  displayHline(20,45,280,DISPLAY_WHITE);
  displayRect(12,12,296,216, DISPLAY_WHITE);
  displayRawText(title, 20, 20, DISPLAY_CYAN, DISPLAY_NAVY);
  displayRawText(instructions, 20, 200, DISPLAY_CYAN, DISPLAY_NAVY);
}


// Buffers holding current contents of VFOs on screen
// This is used to minimize the amount of data we transfer to the screen.

#define VFO_SIZE 12

char vfoADisplay[VFO_SIZE];
char vfoBDisplay[VFO_SIZE];

void displayVFO(int vfo, int force_redraw){
  int x, y;
  int displayColor, displayBorder;
  Button b;
  char *display = vfoBDisplay;

  if (vfo == VFO_A)
    display = vfoADisplay;
  else
    display = vfoBDisplay;

  if (force_redraw)
    memset(display, 0, VFO_SIZE);

  if (vfo == VFO_A){
    getButton("VFOA", &b);
    if (splitOn){
      if (vfoActive == VFO_A)
        strcpy(c, "R:");
      else 
        strcpy(c, "T:");
    }
    else  
      strcpy(c, "A:");
    if (vfoActive == VFO_A){
      formatFreq(frequency, c+2);
      displayColor = DISPLAY_WHITE; // Active VFO
      displayBorder = DISPLAY_DARKGREY; // Not focused
    }else{
      formatFreq(vfoA, c+2);
      displayColor = DISPLAY_GREEN; // Not active VFO
      displayBorder = DISPLAY_DARKGREY; // Not focused
    }
  }

  if (vfo == VFO_B){
    getButton("VFOB", &b);

    if (splitOn){
      if (vfoActive == VFO_B)
        strcpy(c, "R:");
      else 
        strcpy(c, "T:");
    }
    else  
      strcpy(c, "B:");
    if (vfoActive == VFO_B){
      formatFreq(frequency, c+2);
      displayColor = DISPLAY_WHITE; // Active VFO
      displayBorder = DISPLAY_DARKGREY; // Not focused
    } else {
      displayColor = DISPLAY_GREEN; // Not active VFO
      displayBorder = DISPLAY_DARKGREY; // Not focused
      formatFreq(vfoB, c+2);
    }
  }

  if (display[0] == 0){
    displayFillrect(b.x, b.y, b.w, b.h, DISPLAY_BLACK);
    displayRect(b.x, b.y, b.w , b.h, displayBorder);
  }
  x = b.x + 6;
  y = b.y + 3;

  for (int i = 0; c[i]; i++){
    char digit = c[i];
    if (digit != display[i]){
      
      displayFillrect(x, y, 15, b.h-6, DISPLAY_BLACK);
      //checkCAT();
     
      displayChar(x, y + TEXT_LINE_HEIGHT + 3, digit, displayColor, DISPLAY_BLACK);
      checkCAT();
    }
    if (digit == ':' || digit == '.')
      x += 7;
    else
      x += 16;
  }
  
  strcpy(display, c);
}

void btnDraw(struct Button *b){
  if (!strcmp(b->text, "VFOA")){
    displayVFO(VFO_A, 1);
  }
  else if(!strcmp(b->text, "VFOB")){
    displayVFO(VFO_B, 1);
  }
  else if ((!strcmp(b->text, "RIT") && ritOn == 1) || 
      (!strcmp(b->text, "USB") && isUSB == 1) || 
      (!strcmp(b->text, "LSB") && isUSB == 0) || 
      (!strcmp(b->text, "SPL") && splitOn == 1))
    displayText(b->text, b->x, b->y, b->w, b->h, DISPLAY_BLACK, DISPLAY_ORANGE, DISPLAY_DARKGREY, CENTERED);
  else if (!strcmp(b->text, "CW") && cwMode == 1)
      displayText(b->text, b->x, b->y, b->w, b->h, DISPLAY_BLACK, DISPLAY_ORANGE, DISPLAY_DARKGREY, CENTERED);
  else
    displayText(b->text, b->x, b->y, b->w, b->h, DISPLAY_GREEN, DISPLAY_BLACK, DISPLAY_DARKGREY, CENTERED);
}


void displayRIT(){
  displayFillrect(0,COMMAND_TEXT_Y,320,COMMAND_TEXT_HEIGHT, DISPLAY_NAVY);
  if (ritOn){
    strcpy(c, "TX:");
    formatFreq(ritTxFrequency, c+3);
    if (vfoActive == VFO_A)
      displayText(c, 0, COMMAND_TEXT_Y,159, COMMAND_TEXT_HEIGHT, DISPLAY_WHITE, DISPLAY_NAVY, DISPLAY_NAVY, CENTERED);
    else
      displayText(c, 160, COMMAND_TEXT_Y,159, COMMAND_TEXT_HEIGHT, DISPLAY_WHITE, DISPLAY_NAVY, DISPLAY_NAVY, CENTERED);
  }
  else {
    if (vfoActive == VFO_A)
      displayText("", 0, COMMAND_TEXT_Y,159, COMMAND_TEXT_HEIGHT, DISPLAY_WHITE, DISPLAY_NAVY, DISPLAY_NAVY, CENTERED);
    else
      displayText("", 160, COMMAND_TEXT_Y,159, COMMAND_TEXT_HEIGHT, DISPLAY_WHITE, DISPLAY_NAVY, DISPLAY_NAVY, CENTERED);
  }
}

// Fast tune is now a mode..

int8_t fast_tune;

void enable_fast_tune()
{
  if (!ritOn) // No fast tune for RIT..
  {
    fast_tune = 1;
    displayText("Fast tune", 40, COMMAND_TEXT_Y, 240, COMMAND_TEXT_HEIGHT, DISPLAY_CYAN, DISPLAY_NAVY, DISPLAY_NAVY, CENTERED);
  }
}

void cancel_fast_tune()
{
  if (fast_tune)
  {
    fast_tune = 0;
    clearCommandbar();
  }
}

void enterFreq(){
  //force the display to refresh everything
  //display all the buttons
  int f;
  
  for (int i = 0; i < MAX_KEYS; i++){
    struct Button b;
    memcpy_P(&b, keypad + i, sizeof(struct Button));
    btnDraw(&b);
  }

  int cursor_pos = 0;
  memset(c, 0, sizeof(c));
  f = frequency / 1000l;

  while(1){

    checkCAT();
    if(!readTouch())
      continue;
      
    scaleTouch(&ts_point);

    int total = sizeof(btn_set)/sizeof(struct Button);
    for (int i = 0; i < MAX_KEYS; i++){
      struct Button b;
      memcpy_P(&b, keypad + i, sizeof(struct Button));

      int x2 = b.x + b.w;
      int y2 = b.y + b.h;
  
      if (b.x < ts_point.x && ts_point.x < x2 && 
        b.y < ts_point.y && ts_point.y < y2){
          if (!strcmp(b.text, "OK")){
            long f = atol(c);
            if(30000 >= f && f > 100){
              modify_frequency(f * 1000l, 1, 1);
            }
            guiUpdate();
            return;
          }
          else if (!strcmp(b.text, "<-")){
            c[cursor_pos] = 0;
            if (cursor_pos > 0)
              cursor_pos--;      
            c[cursor_pos] = 0;
          }
          else if (!strcmp(b.text, "Can")){
            guiUpdate();
            return;
          }
          else if('0' <= b.text[0] && b.text[0] <= '9'){
            c[cursor_pos++] = b.text[0];
            c[cursor_pos] = 0;
          }
        }
    } // end of the button scanning loop
    strcpy(b, c);
    strcat(b, " KHz");
    displayText(b, COMMAND_TEXT_X, COMMAND_TEXT_Y, COMMAND_TEXT_WIDTH, COMMAND_TEXT_HEIGHT, DISPLAY_WHITE, DISPLAY_NAVY, DISPLAY_NAVY, CENTERED);
    delay(300);
    while(readTouch())
      checkCAT();
  } // end of event loop : while(1)
  
}

void drawCWStatus(){
  strcpy(b, " cw:");
  int wpm = 1200/cwSpeed;    
  itoa(wpm,c, 10);
  strcat(b, c);
  strcat(b, "wpm, ");
  itoa(sideTone, c, 10);
  strcat(b, c);
  strcat(b, "hz");
  displayText(b, STATUS_TEXT_X, STATUS_TEXT_Y, STATUS_TEXT_WIDTH, STATUS_TEXT_HEIGHT, DISPLAY_CYAN, DISPLAY_NAVY, DISPLAY_NAVY, LEFT);

  displayText(version_string, 260, 201, 60, 39, DISPLAY_LIGHTGREY, DISPLAY_NAVY, DISPLAY_NAVY, CENTERED);
 
}


void drawTx(){
  if (inTx)
    displayText("TX", TX_TEXT_X, TX_TEXT_Y, TX_TEXT_WIDTH, TX_TEXT_HEIGHT, DISPLAY_BLACK, DISPLAY_ORANGE, DISPLAY_BLUE, CENTERED);
  else
    displayFillrect(TX_TEXT_X, TX_TEXT_Y, TX_TEXT_WIDTH, TX_TEXT_HEIGHT, DISPLAY_NAVY);
}

void drawStatusbar(){
  drawCWStatus();
  displayText(version_string, VERSION_TEXT_X, VERSION_TEXT_Y, VERSION_TEXT_WIDTH, VERSION_TEXT_HEIGHT, DISPLAY_LIGHTGREY, DISPLAY_NAVY, DISPLAY_NAVY, CENTERED);
}

void guiUpdate(){

/*
  if (doingCAT)
    return;
*/
  // use the current frequency as the VFO frequency for the active VFO
  displayClear(DISPLAY_NAVY);
  checkCAT();

  //force the display to refresh everything
  //display all the buttons
  for (int i = 0; i < MAX_BUTTONS; i++){
    struct Button b;
    memcpy_P(&b, btn_set + i, sizeof(struct Button));
    btnDraw(&b);
    checkCAT();
  }
  drawStatusbar();
  checkCAT();  
  displayRIT();
  checkCAT();
}



// this builds up the top line of the display with frequency and mode
void updateDisplay() {
   displayVFO(vfoActive, 0);
   updateUSB();
}

int enc_prev_state = 3;

/**
 * The A7 And A6 are purely analog lines on the Arduino Nano
 * These need to be pulled up externally using two 10 K resistors
 * 
 * There are excellent pages on the Internet about how these encoders work
 * and how they should be used. We have elected to use the simplest way
 * to use these encoders without the complexity of interrupts etc to 
 * keep it understandable.
 * 
 * The enc_state returns a two-bit number such that each bit reflects the current
 * value of each of the two phases of the encoder
 * 
 * The enc_read returns the number of net pulses counted over 50 msecs. 
 * If the puluses are -ve, they were anti-clockwise, if they are +ve, the
 * were in the clockwise directions. Higher the pulses, greater the speed
 * at which the enccoder was spun
 */
/*
byte enc_state (void) {
    //Serial.print(digitalRead(ENC_A)); Serial.print(":");Serial.println(digitalRead(ENC_B));
    return (digitalRead(ENC_A) == 1 ? 1 : 0) + (digitalRead(ENC_B) == 1 ? 2: 0);
}

int enc_read(void) {
  int result = 0; 
  byte newState;
  int enc_speed = 0;
  
  long stop_by = millis() + 200;
  
  while (millis() < stop_by) { // check if the previous state was stable
    newState = enc_state(); // Get current state  
    
//    if (newState != enc_prev_state)
//      active_delay(20);
    
    if (enc_state() != newState || newState == enc_prev_state)
      continue; 
    //these transitions point to the encoder being rotated anti-clockwise
    if ((enc_prev_state == 0 && newState == 2) || 
      (enc_prev_state == 2 && newState == 3) || 
      (enc_prev_state == 3 && newState == 1) || 
      (enc_prev_state == 1 && newState == 0)){
        result--;
      }
    //these transitions point o the enccoder being rotated clockwise
    if ((enc_prev_state == 0 && newState == 1) || 
      (enc_prev_state == 1 && newState == 3) || 
      (enc_prev_state == 3 && newState == 2) || 
      (enc_prev_state == 2 && newState == 0)){
        result++;
      }
    enc_prev_state = newState; // Record state for next pulse interpretation
    enc_speed++;
    active_delay(1);
  }
  //if (result)
  //  Serial.println(result);
  return(result);
}
*/

void ritToggle(struct Button *b){
  if (ritOn == 0){
    ritEnable(frequency);
  }
  else
    ritDisable();
  btnDraw(b);
  displayRIT();
}

void splitToggle(struct Button *b){

  if (splitOn)
    splitOn = 0;
  else
    splitOn = 1;

  btnDraw(b);

  //disable rit as well
  ritDisable();
  
  struct Button b2;
  getButton("RIT", &b2);
  btnDraw(&b2);
  
  displayRIT();
  displayVFO(VFO_A, 1);
  displayVFO(VFO_B, 1);
}

void vfoReset(){
  Button b;
  if (vfoActive = VFO_A)
    vfoB = vfoA;
  else
    vfoA = vfoB;

  if (splitOn){
    getButton("SPL", &b);
    splitToggle(&b);
  }

  if (ritOn){
    getButton("RIT", &b);
    ritToggle(&b);
  }
  
  displayVFO(VFO_A, 1);
  displayVFO(VFO_B, 1);

  saveVFOs();
}

void cwToggle(struct Button *b){
  if (cwMode == 0){
    cwMode = 1;
  }
  else
    cwMode = 0;

  setFrequency(frequency);
  btnDraw(b);
}

char usb_needs_update;

void setUSB(char wantUSB)
{
  if ((wantUSB && !isUSB) || (!wantUSB && isUSB))
  {
    isUSB = wantUSB;
    usb_needs_update = 1;
  }
}

void updateUSB()
{
  if (usb_needs_update)
  {
    usb_needs_update = 0;
    struct Button e;
    getButton("USB", &e);
    btnDraw(&e);
    getButton("LSB", &e);
    btnDraw(&e);
  }
}

void sidebandToggle(struct Button *b){
  int wantUSB;
  if (!strcmp(b->text, "LSB"))
    wantUSB = 0;
  else
    wantUSB = 1;
  setUSB(wantUSB);
  updateUSB();

  setFrequency(frequency); // USB/LSB change should have immediate effect
  saveVFOs();
}


void redrawVFOs(){

    struct Button b;
    ritDisable();
    getButton("RIT", &b);
    btnDraw(&b);
    displayRIT();
    displayVFO(VFO_A, 1);
    displayVFO(VFO_B, 1);

    //draw the lsb/usb buttons, the sidebands might have changed
    updateUSB();
}


void switchBand(long bandfreq){
  long offset;

//  Serial.println(frequency);
//  Serial.println(bandfreq);
  if (3500000l <= frequency && frequency <= 4000000l)
    offset = frequency - 3500000l;
  else if (24800000l <= frequency && frequency <= 25000000l)
    offset = frequency - 24800000l;
  else 
    offset = frequency % 1000000l; 

//  Serial.println(offset);

  modify_frequency(bandfreq + offset, 1, 1);
}

int setCwSpeed(){
    int knob = 0;
    int wpm;

    wpm = 1200/cwSpeed;
     
    wpm = getValueByKnob(1, 100, 1,  wpm, "CW: ", " WPM");
  
    cwSpeed = 1200/wpm;

    EEPROM.put(CW_SPEED, cwSpeed);
    active_delay(500);
    drawStatusbar();      
//    printLine2("");
//    updateDisplay();
}

void setCwTone(){
  int knob = 0;
  int prev_sideTone;
     
  tone(CW_TONE, sideTone);

  // Initial display
  tone(CW_TONE, sideTone);
  itoa(sideTone, c, 10);
  strcpy(b, "CW Tone: ");
  strcat(b, c);
  strcat(b, " Hz");
  drawCommandbar(b);

  //disable all clock 1 and clock 2 
  while (digitalRead(PTT) == HIGH && !btnDown())
  {
    knob = enc_read();

    if (knob > 0 && sideTone < 2000)
      sideTone += 10;
    else if (knob < 0 && sideTone > 100 )
      sideTone -= 10;
    else
      continue; //don't update the frequency or the display
        
    tone(CW_TONE, sideTone);
    itoa(sideTone, c, 10);
    strcpy(b, "CW Tone: ");
    strcat(b, c);
    strcat(b, " Hz");
    drawCommandbar(b);
    //printLine2(b);

    checkCAT();
    active_delay(20);
  }
  noTone(CW_TONE);
  //save the setting
  EEPROM.put(CW_SIDETONE, sideTone);

  clearCommandbar();
  drawStatusbar();
//  printLine2("");  
//  updateDisplay();  
}

void doCommand(struct Button *b)
{
  // These should toggle fast tune, or cancel it if we are switching VFOs
  if (!strcmp(b->text, "VFOA")) {
    if (vfoActive == VFO_A)
    {
      if (fast_tune)
        cancel_fast_tune();
      else
        enable_fast_tune();
    }
    else
    {
      cancel_fast_tune();
      switchVFO(VFO_A);
    }
    return;
  }
  else if (!strcmp(b->text, "VFOB")) {
    if (vfoActive == VFO_B)
    {
      if (fast_tune)
        cancel_fast_tune();
      else
        enable_fast_tune();
    }
    else
    {
      cancel_fast_tune();
      switchVFO(VFO_B);
    }
    return;
  }

  // All of the rest always cancel fast_tune
  cancel_fast_tune();

  if (!strcmp(b->text, "RIT"))
    ritToggle(b);
  else if (!strcmp(b->text, "LSB"))
    sidebandToggle(b);
  else if (!strcmp(b->text, "USB"))
    sidebandToggle(b);
  else if (!strcmp(b->text, "CW"))
    cwToggle(b);
  else if (!strcmp(b->text, "SPL"))
    splitToggle(b);
  else if (!strcmp(b->text, "A=B"))
    vfoReset();
  else if (!strcmp(b->text, "80"))
    switchBand(3500000l);
  else if (!strcmp(b->text, "40"))
    switchBand(7000000l);
  else if (!strcmp(b->text, "30"))
    switchBand(10000000l);
  else if (!strcmp(b->text, "20"))
    switchBand(14000000l);
  else if (!strcmp(b->text, "17"))
    switchBand(18000000l);
  else if (!strcmp(b->text, "15"))
    switchBand(21000000l);
  else if (!strcmp(b->text, "13"))
    switchBand(24800000l);
  else if (!strcmp(b->text, "10"))
    switchBand(28000000l);  
  else if (!strcmp(b->text, "FRQ"))
    enterFreq();
  else if (!strcmp(b->text, "WPM"))
    setCwSpeed();
  else if (!strcmp(b->text, "TON"))
    setCwTone();
}

void  checkTouch(){

  if (!readTouch())
    return;

  while(readTouch())
    checkCAT();
  scaleTouch(&ts_point);
 
  /* //debug code
  Serial.print(ts_point.x); Serial.print(' ');Serial.println(ts_point.y);
  */
  int total = sizeof(btn_set)/sizeof(struct Button);
  for (int i = 0; i < MAX_BUTTONS; i++){
    struct Button b;
    memcpy_P(&b, btn_set + i, sizeof(struct Button));

    int x2 = b.x + b.w;
    int y2 = b.y + b.h;

    if (b.x < ts_point.x && ts_point.x < x2 && 
      b.y < ts_point.y && ts_point.y < y2)
          doCommand(&b);
  }
}

//returns true if the button is pressed
int btnDown(){
  if (digitalRead(FBUTTON) == HIGH)
    return 0;
  else
    return 1;
}

// Wait for button to be released
void wait_released()
{
  //wait for the button to be raised up
  while(btnDown())
    active_delay(50);
  active_delay(50);  //debounce
}

void drawFocus(int ibtn, int color){
  struct Button b;

  memcpy_P(&b, btn_set + ibtn, sizeof(struct Button));
  displayRect(b.x, b.y, b.w, b.h, color);
}

void doCommands(){
  int select=0, prevButton=0;

  // Button has been released before this is called

  // Initial focus
  drawFocus(select, DISPLAY_WHITE);

  for (;;) {
    //check if the knob's button was pressed
    if (btnDown()) {
      struct Button b;
      memcpy_P(&b, btn_set + select, sizeof(struct Button));

      wait_released(); // Button released before doCommand

      doCommand(&b);

      //unfocus the buttons
      drawFocus(select, DISPLAY_DARKGREY);

      wait_released(); // Button released before we return
        
      return;
    }

    int i = enc_read();
    
    if (i == 0){
      active_delay(50);
      continue;
    }
    
    if (i > 0){
      if (select + i < MAX_BUTTONS)
        select += i;
    }
    if (i < 0 && select + i >= 0)
      select += i;      //caught ya, i is already -ve here, so you add it
    
    if (prevButton == select)
      continue;

     //we are on a new button
     drawFocus(prevButton, DISPLAY_DARKGREY);
     drawFocus(select, DISPLAY_WHITE);
     prevButton = select;
  }
}

