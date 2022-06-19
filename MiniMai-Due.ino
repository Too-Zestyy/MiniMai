#include <stdint.h>
#include <Bounce2.h>
#include <LCD.h>
#include <SPI.h>
#include <XPT2046.h>
#include <Touch.h>
#include <MiniMai-Due.h>
#include <Keyboard.h>

#define GREY  		   0x8430
#define RED          0xF800

int state = 0;
int lastState = -1;
bool inputting = false;
uint8_t buf[8] = { 0 }; //Keyboard report buffer

int buttonStates[] = {0, 0, 0, 0, 0, 0, 0, 0};
char buttonKeys[] = {'x', 'c', 'z', 'd', 'a', 'e', 'q', 'w'};

const int xPin = 22;
const int cPin = 26;
const int zPin = 30;
const int dPin = 34;
const int aPin = 38;
const int ePin = 42;
const int qPin = 46;
const int wPin = 50;

Bounce xButton = Bounce();
Bounce cButton = Bounce();
// Bounce zButton = Bounce();
// Bounce dButton = Bounce();
// Bounce aButton = Bounce();
// Bounce eButton = Bounce();
// Bounce qButton = Bounce();
// Bounce wButton = Bounce();

// Bounce buttons[] = {xButton, cButton};

void setup()
{   

    // pinMode(xPin, INPUT_PULLUP);
    // pinMode(cPin, INPUT_PULLUP);

    // xButton.attach(xPin, INPUT_PULLUP);
    // xButton.interval(15);
    // cButton.attach(cPin, INPUT_PULLUP);
    // cButton.interval(15);

     __SD_CS_DISABLE();
   
    SPI.setDataMode(SPI_MODE3);
    SPI.setBitOrder(MSBFIRST);
    SPI.setClockDivider(SPI_CLOCK_DIV4);
    
    SPI.begin();

    Tft.lcd_init();                                      // init TFT library
    Tp.tp_init();
    Tp.tp_adjust();
    // Tft.lcd_clear_screen(GREY);
    // Tft.lcd_draw_line(0, 0, 239, 319, WHITE);
    Menu.SetTFT(Tft);
    Menu.DrawMaiZones();
    // Tft.lcd_draw_line(int(Menu.zoneMap[121][100]), 0, 239, 319, WHITE);
    
    // Tft.lcd_display_string(45, 50, (const uint8_t *)Menu.zoneMap[121][100], FONT_1608, WHITE);
    SerialUSB.begin(9600);
    // Serial.print('b');
    // Keyboard.begin();  
}


void loop()
{
  // if (SerialUSB.available()>0) {
  //   Tft.lcd_clear_screen(RED);
  //   SerialUSB.print('b');
  // }
  Tp.tp_scan(0);
  if (Tp.s_tTouch.hwXpos != 65535) {
    SerialUSB.println(int(Menu.getCoordVal(Tp.s_tTouch.hwXpos, Tp.s_tTouch.hwYpos)));
    // SerialUSB.print(Tp.s_tTouch.hwXpos);
    // SerialUSB.print(',');
    // SerialUSB.println(Tp.s_tTouch.hwYpos);
  //   // if (Menu.getCoordVal(Tp.s_tTouch.hwXpos, Tp.s_tTouch.hwYpos) == 0x0) {
  //   //   Tft.lcd_clear_screen(GREEN);
  //   // }
  //   // Tft.lcd_clear_screen(BLUE);

  }

  // for (int button = 0; button < 1; button++) { // TODO: Change to 8 when all buttons are wired
  //   buttons[button].update();
  //   if (buttons[button].fell()) { // Using pullup so output of buttons is 1 when buttons aren't pressed
  //       Keyboard.press(buttonKeys[button]);
  //   }
  //   else if (buttons[button].rose()) {
  //       Keyboard.release(buttonKeys[button]);
  //   }
  // }


    // if (digitalRead(xPin) == LOW) {Keyboard.press('x'); }
    // else {Keyboard.release('x');}
    // if (digitalRead(cPin) == LOW) {Keyboard.press('c'); }
    // else {Keyboard.release('c');}

}

    /* Scan 0 points (NOTE: These corners are correct when the USB port is facing *upwards*)
     TL: 0-3, 0-5
     TR: 236, 11
     BL: 0-2, 301-311
     BR: 232, 302-310
     Scan 0 seems to give coords for screen pixels, while Scan 1 gives a raw value?
    */
    
    /* if no touch is found at request, coords are returned as 65535 - 65535*/  
    // Serial.println((const uint8_t *)Tp.s_tTouch.hwXpos);
    // Tft.lcd_display_string(30, 152, (const uint8_t *)Tp.s_tTouch.hwXpos, FONT_1608, BLUE);
    // Tft.lcd_display_string(30, 250, (const uint8_t *)Tp.s_tTouch.hwYpos, FONT_1608, BLUE);
    // Tp.tp_draw_board();    
    // Tft.lcd_display_string(30, 152, (const uint8_t *)"2.8' TFT Touch Shield", FONT_1608, RED);
    // Serial.println();
  // }



/*********************************************************************************************************
  END FILE
*********************************************************************************************************/







