#include <IRremote.h>
#include "Keyboard.h"
#include <AbsMouse.h>


IRrecv irrecv(10);                // Receive on pin 10
decode_results results;

void setup()
{
  Serial.begin(9600); 
  Keyboard.begin();
  AbsMouse.init(5760, 1080);      // work mode
//AbsMouse.init(1920, 1080);      // debug
  irrecv.enableIRIn();            // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {  // IR detected
    switch (results.value)  {
      case 0xE0E036C9:                // A pressed - Answer Chat
        AbsMouse.move(2710, 136);     // Move to accept coordinates (3 monitors)
        //AbsMouse.move(0, 0);        // debug mode, top left corner
        AbsMouse.press(MOUSE_LEFT);   // press left click
        AbsMouse.release(MOUSE_LEFT); // release left click
        delay(3000);                  // wait for session to load
        Keyboard.write('/');          // open hot-key menu
        Keyboard.write('g');          // highlight greeting
        Keyboard.write(KEY_RETURN);   // select greeting
        break;
    case 0xE0E028D7:              // B Pressed - Auto-fill chat session info
        Keyboard.write(KEY_TAB);
        Keyboard.write(KEY_TAB);
        Keyboard.write(KEY_TAB);
        Keyboard.write(KEY_DOWN_ARROW);
        Keyboard.write(KEY_DOWN_ARROW);
        Keyboard.write(KEY_DOWN_ARROW); // chat
        Keyboard.write(KEY_TAB);
  
        Keyboard.write(KEY_TAB);
        break;
    case 0xE0E0A857:              // C Pressed
        break;
    case 0xE0E06897:              // D Pressed
        break;
    }
    irrecv.resume();              // Continue receiving
    
  }
}
