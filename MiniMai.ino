#include <stdint.h>
#include <LCD.h>
#include <SPI.h>
#include <XPT2046.h>
#include <Touch.h>
#include <MiniMai.h>
#include <Keyboard.h>
// #include <Joystick.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_ILI9341.h>
// #include <XPT2046_Touchscreen.h>

// #include <XPT2046_Touchscreen.h>
#define __AVR_ATmega32U4__
// Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
//   8, 0,                  // Button Count, Hat Switch Count
//   true, true, false,     // X and Y, but no Z Axis
//   false, false, false,   // No Rx, Ry, or Rz
//   false, false,          // No rudder or throttle
//   false, false, false);  // No accelerator, brake, or steering
int state = 0;
int lastState = -1;
bool inputting = false;

void setup()
{ 
   __SD_CS_DISABLE();
   
    SPI.setDataMode(SPI_MODE3);
    SPI.setBitOrder(MSBFIRST);
    SPI.setClockDivider(SPI_CLOCK_DIV4);
    
    SPI.begin();

    // Joystick.setXAxisRange(-127, 127);
    // Joystick.setYAxisRange(-127, 127);
    // Joystick.setZAxisRange(-127, 127);
    // Joystick.setRxAxisRange(0, 360);
    // Joystick.setRyAxisRange(360, 0);
    // Joystick.setRzAxisRange(0, 720);
    // Joystick.setThrottleRange(0, 255);
    // Joystick.setRudderRange(255, 0);
    
    // Joystick.begin();

    
    // SPI.beginTransaction(SPISettings(SPI_CLOCK_DIV4, MSBFIRST, SPI_MODE3));

    Tft.lcd_init();                                      // init TFT library
    // Tft.lcd_display_string(60, 120, (const uint8_t *)"Hello, world !", FONT_1608, RED);
    Tp.tp_init();
    Tp.tp_adjust();
    Menu.SetTFT(Tft);
    Menu.BuildMainMenu();
    Tft.lcd_display_string(45, 50, (const uint8_t *)"Welcome to MiniMai!", FONT_1608, WHITE);
    Keyboard.begin();  
}


void loop()
{
    //   if (ts.touched()) {
    // TS_Point p = ts.getPoint();
    // // Serial.print("Pressure = ");
    // // Serial.print(p.z);
    Tp.tp_scan(0);   
    // Serial.print(", x = ");
    // Serial.print(Tp.s_tTouch.hwXpos);
    // Serial.print(", y = ");
    // Serial.print(Tp.s_tTouch.hwYpos);  
    // Serial.print("\n"); 
    // TL: ~1870, ~1910
    // TR: ~150-180, ~1950    

    if (Tp.s_tTouch.hwXpos != 65535) { //Tp.s_tTouch.hwXpos != 65535
      // NOTE: Y-axis parses +ve as down and -ve as up
      // Y0, B1, A2, X3, LB4, RB5
      // Right stick is x and y rotation, with axes dealt in the same way as left stick
      // D-pad counts as hat buttons
      
        switch (Menu.menu) {
          case MAIN_MENU:

            state = Menu.buttonCheck(Tp.s_tTouch.hwXpos, Tp.s_tTouch.hwYpos);
            // Serial.println(state); 
            // Serial.println(Menu.buttons[6].isPressed(Tp.s_tTouch.hwXpos, Tp.s_tTouch.hwYpos));         
            

              lastState = state;
              switch (state) {
                case (0):
                    Keyboard.press('x');  
                  break;                
                case (1):
                    Keyboard.press('c');    
                  break;                
                case (2): 
                    Keyboard.press('z');
                  break;                      
                case (3):
                    Keyboard.press('d');                     
                  break;
                case (4):
                    Keyboard.press('a');                                  
                  break;
                case (5):
                    Keyboard.press('e');    
                  break;
                case (6):
                    Keyboard.press('q');                   
                  break;
                case (7):
                    Keyboard.press('w');
                  break;
                               
              }
        }

    }  
            // }

                     

            // if () {
            //   Tft.lcd_clear_screen(GREEN);
            //   Menu.BuildMainMenu();              
            // }
            // else {
            //   Tft.lcd_clear_screen(RED);
            //   Menu.BuildMainMenu();
            // }                                    


    else {
      state = -1; 
      Keyboard.releaseAll();
    }  
      // delay(50);          
        // Serial.println("coords of touch");
        // Serial.println(Tp.s_tTouch.hwXpos); // scanning is required to get the point of touch
        // Serial.println(Tp.s_tTouch.hwYpos); 
        // Serial.println("---------");        
        // Serial.println(Menu.add(5, 11));
        // Tft.lcd_clear_screen(0x3186); // 0xF0
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






