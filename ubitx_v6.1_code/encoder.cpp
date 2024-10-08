#include <Arduino.h>
#include <stdint.h>
#include "ubitx.h"//Pin definitions

//Normal encoder state
uint8_t prev_enc = 0;
int16_t enc_count = 0;

#define DECAY_RATE 10
#define MAX_SLAM 40
#define FAST_THRESH 30
#define FAST_STEP 20

//Momentum encoder state
int go_fast;
static const uint16_t CALLBACK_PERIOD_MS = 200;
static const uint8_t MOMENTUM_MULTIPLIER = 1;

uint8_t enc_state (void)
{
  return (digitalRead(ENC_A)?1:0 + digitalRead(ENC_B)?2:0);
}

/*
 * SmittyHalibut's encoder handling, using interrupts. Should be quicker, smoother handling.
 * The Interrupt Service Routine for Pin Change Interrupts on A0-A5.
 */
ISR (PCINT1_vect)
{
  uint8_t cur_enc = enc_state();
  if (prev_enc == cur_enc) {
    //Serial.println("unnecessary ISR");
    return;
  }
  //Serial.print(prev_enc);
  //Serial.println(cur_enc);
  
  //these transitions point to the enccoder being rotated anti-clockwise
  if ((prev_enc == 0 && cur_enc == 2) || 
      (prev_enc == 2 && cur_enc == 3) || 
      (prev_enc == 3 && cur_enc == 1) || 
      (prev_enc == 1 && cur_enc == 0))
  {
    if (go_fast >= FAST_THRESH)
      enc_count -= FAST_STEP;
    else
      enc_count -= 1;
    if (go_fast != MAX_SLAM)
      ++go_fast;
  }
  //these transitions point to the enccoder being rotated clockwise
  else if ((prev_enc == 0 && cur_enc == 1) || 
      (prev_enc == 1 && cur_enc == 3) || 
      (prev_enc == 3 && cur_enc == 2) || 
      (prev_enc == 2 && cur_enc == 0))
  {
    if (go_fast >= FAST_THRESH)
      enc_count += FAST_STEP;
    else
      enc_count += 1;
    if (go_fast != MAX_SLAM)
      ++go_fast;
  }
  else {
    // A change to two states, we can't tell whether it was forward or backward, so we skip it.
    //Serial.println("skip");
  }
  prev_enc = cur_enc; // Record state for next pulse interpretation
}

/*
 * Setup the encoder interrupts and global variables.
 */
void pci_setup(byte pin) {
  *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
  PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
  PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
}

void enc_setup(void)
{
  enc_count = 0;
  // This is already done in setup() ?
  //pinMode(ENC_A, INPUT);
  //pinMode(ENC_B, INPUT);
  prev_enc = enc_state();

  // Setup Pin Change Interrupts for the encoder inputs
  pci_setup(ENC_A);
  pci_setup(ENC_B);

  //Set up timer interrupt for momentum
  TCCR1A = 0;//"normal" mode
  TCCR1B = 3;//clock divider of 64
  TCNT1  = 0;//start counting at 0
  OCR1A  = F_CPU * CALLBACK_PERIOD_MS / 1000 / 64;//set target number
  TIMSK1 |= (1 << OCIE1A);//enable interrupt
}

ISR(TIMER1_COMPA_vect)
{
  if (go_fast > DECAY_RATE)
    go_fast -= DECAY_RATE;
  else
    go_fast = 0;
}

// Number of ticks knob was moved since last time this was called
// ...this way we don't miss any
// We divide enc_count by 2 to ignore the half-ticks, when knob is between detents

int8_t prev_mod_count;

int enc_read(void)
{
  int8_t mod_count = enc_count / 2;
  int8_t rtn = mod_count - prev_mod_count;
  prev_mod_count = mod_count;
  return rtn;
}
