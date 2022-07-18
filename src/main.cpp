#include <Arduino.h>
#include "HID-Project.h"

const uint8_t STATUS_LED = 10;
const uint8_t NUM_BUTTONS = 4;
const uint8_t BUTTON_PINS [NUM_BUTTONS] = {6, 7, 8, 9};
const uint8_t BUTTON_0 = 0;
const uint8_t BUTTON_1 = 1;
const uint8_t BUTTON_2 = 2;
const uint8_t BUTTON_3 = 3;
uint8_t buttons_state = B00000000;  
uint8_t buttons_previous_state = B00000000;
unsigned long debounce_start_time [NUM_BUTTONS] = {0};
const unsigned int debounce_delay = 50; // milliseconds.


unsigned long input_interval = 50; //ms 
unsigned long previous_millis = 0;


void button_poll() {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    // Set the old button state data to the previous state before  we poll the buttons and
    // get the current state.
    buttons_previous_state = buttons_state; 

    // If the button's state is read differently than it was previously, start the debounce timer.
    if (digitalRead(BUTTON_PINS [i]) != (buttons_previous_state & (1 << i))) {
      debounce_start_time[i] = millis();
    }

    // Debounce for this button is probably done now, so it should be okay to save it's state.
    if (millis() - debounce_start_time[i] > debounce_delay) {
      /*if (digitalRead(BUTTON_PINS[i]) == LOW)
      {
        buttons_state |= 1 << i;
      }
      else
      {
        buttons_state &= ~(1 << i);
      }*/

      // If the previous state is still different, flip that button's bit.
      if (digitalRead(BUTTON_PINS[i]) != (buttons_previous_state & (1 << i)))
      {
        buttons_state ^= (1 << i);
      }
    }
  }
}

bool button_pressed (uint8_t button_number) {
  uint8_t mask = 1 << button_number;
  if ((buttons_state & mask == mask) && (buttons_previous_state & mask == 0)) {
    return true;
  }
  else {
    return false;
  }
}

// can be used if you want repeated function calling. Like, holding a key to print it several times.
bool button_held (uint8_t button_number) {
  uint8_t mask = 1 << button_number;
  if ((buttons_state & mask == mask) && (buttons_previous_state & mask == mask))
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool button_released(uint8_t button_number)
{
  uint8_t mask = 1 << button_number;
  if ((buttons_state & mask == 0) && (buttons_previous_state & mask == mask))
  {
    return true;
  }
  else
  {
    return false;
  }
}

void setup() {
  // put your setup code here, to run once:
  delay(1500);
  pinMode(STATUS_LED, OUTPUT);

  for (int i = 0; i < NUM_BUTTONS; i++) {
    pinMode(BUTTON_PINS[i], INPUT);
  }

  digitalWrite(STATUS_LED, HIGH);
  delay(300);
  digitalWrite(STATUS_LED, LOW);
  delay(300);
  digitalWrite(STATUS_LED, HIGH);
  delay(300);
  digitalWrite(STATUS_LED, LOW);
  delay(300);
  digitalWrite(STATUS_LED, HIGH);
  Keyboard.begin();
}

// doesn't deal with debounce yet.
void loop() {
  button_poll();

  unsigned long time = millis();
  if (time - previous_millis >= input_interval) {
    previous_millis = time;
    if (digitalRead(BUTTON_1) == LOW) {
      Keyboard.press(HID_KEYBOARD_LEFT_CONTROL);
      Keyboard.press('z');
      Keyboard.release(HID_KEYBOARD_LEFT_CONTROL);
      Keyboard.release('z');
    }

    if (digitalRead(BUTTON_2) == LOW) {
      Keyboard.press(HID_KEYBOARD_LEFT_CONTROL);
      Keyboard.press('x');
      Keyboard.release(HID_KEYBOARD_LEFT_CONTROL);
      Keyboard.release('x');
    }

    if (digitalRead(BUTTON_3) == LOW)
    {
      Keyboard.press(HID_KEYBOARD_LEFT_CONTROL);
      Keyboard.press('c');
      Keyboard.release(HID_KEYBOARD_LEFT_CONTROL);
      Keyboard.release('c');
    }

    if (digitalRead(BUTTON_4) == LOW)
    {
      Keyboard.press(HID_KEYBOARD_LEFT_CONTROL);
      Keyboard.press('v');
      Keyboard.release(HID_KEYBOARD_LEFT_CONTROL);
      Keyboard.release('v');
    }
  }
}