#include <Wire.h>
#include "Adafruit_MPR121.h"

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

Adafruit_MPR121 cap = Adafruit_MPR121();

uint16_t lasttouched = 0;
uint16_t currtouched = 0;


int midiNotes[12] = {60, 62, 64, 65, 67, 69, 71, 72, 74, 76, 77, 79}; //Array of MIDI Notes

int buttonScale = 31; //Button to change scale


int buttonScale = 31;

void setup() {
  Serial.begin(9600);

  while (!Serial) {
    delay(10); 
  }
    
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");
}

void loop() {
  currtouched = cap.touched();
  
  for (uint8_t i=0; i<12; i++) {
    if ((currtouched & _BV(i)) and !(lasttouched & _BV(i))) {
      usbMIDI.sendNoteOn(midiNotes[i], 127, 1); 
    }

    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i))) {
      usbMIDI.sendNoteOff(midiNotes[i], 0, 1);
    }
  }

  lasttouched = currtouched;
  
  delay(10); 
}