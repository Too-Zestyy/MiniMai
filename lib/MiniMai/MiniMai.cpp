#include <lcd.h>

//Basic Colors as given by TFT
#define WHITE          0xFFFF
#define BLACK          0x0000	  
#define BLUE           0x001F  
#define BRED           0XF81F
#define GRED 		   0xFFE0
#define GBLUE		   0x07FF
#define RED            0xF800
#define MAGENTA        0xF81F
#define GREEN          0x07E0
#define CYAN           0x7FFF
#define YELLOW         0xFFE0
#define BROWN 		   0xBC40 
#define BRRED 		   0xFC07 
#define GREY  		   0x8430
#define BUTTON_D_GREY  0x3186
#define BUTTON_M_GREY  0x5ACB
#define BUTTON_L_GREY  0x738E

#include <MiniMai.h>

MaiButton::MaiButton(uint16_t x, uint16_t y, uint16_t width, uint16_t height, TFT Tft) {
    Tft.lcd_draw_line(x, y+1, x+width-1, y+1, BUTTON_D_GREY);
    Tft.lcd_draw_line(x, y, x+width-1, y, BUTTON_D_GREY);
    Tft.lcd_draw_line(x, y+2, x, y+height-1, BUTTON_D_GREY);
    Tft.lcd_draw_line(x+1, y+2, x+1, y+height-1, BUTTON_D_GREY);
    Tft.lcd_draw_line(x+2, y+height-2, x+width-1, y+height-2, BUTTON_D_GREY);
    Tft.lcd_draw_line(x+2, y+height-1, x+width-1, y+height-1, BUTTON_D_GREY);
    Tft.lcd_draw_line(x+width-2, y+height-2, x+width-2, y+2, BUTTON_D_GREY);
    Tft.lcd_draw_line(x+width-1, y+height-2, x+width-1, y+2, BUTTON_D_GREY);

    Tft.lcd_fill_rect(x+2, y+2, width-4, height/2-(height/10), BUTTON_M_GREY);
    Tft.lcd_fill_rect(x+2, y+(height/2)-2, width-4, height/2, BUTTON_L_GREY);
    x1 = x; x2 = x+width; y1 = y; y2 = y+height;
}

MaiButton::MaiButton() {
    x1 = x2 = y1 = y2 = 0;
}

bool MaiButton::isPressed(int touchX, int touchY) {
    // Serial.println(touchX - x1);
    // Serial.println(touchY - y1);
    if ((touchX >= this -> x1 and touchX <= this -> x2) and (touchY >= this -> y1 and touchX <= this -> y2)) {
        return true;
    }

    else {
        return false;
    }
}

MaiMenu::MaiMenu() {
    this -> menu = -1;
}

void MaiMenu::SetTFT(TFT Tft) {
    this -> cur_Tft = Tft;
}

int MaiMenu::add(int a, int b) {
    return a+b;
}

int MaiMenu::buttonCheck(int touchX, int touchY) {
    for (int i = 0; i < 8; i++) {
        if (this -> buttons[i].isPressed(touchX, touchY)) {
            // Serial.print("Button pressed: ");
            // Serial.println(i);
            return i;
            break;
        }
        else {
            continue;
        }

    return -1;
        // Serial.println(buttons[i].x2 - buttons[i].x1);
    }
}

// Arrays to store coords for button starting positions in the 9-button keypad
// int mainxcoords[3] = {15, 88, 161};
// int mainycoords[3] = {260, 209, 158};
// int mainxcoords[8] = {45, 131, 20, 156, 20, 156, 45, 131};
int mainxcoords[8] = {45, 131, 45, 131, 45, 131, 45, 131};
// int mainycoords[8] = {260, 260, 199, 199, 138, 138, 77, 77};
int mainycoords[8] = {273, 273, 222, 222, 171, 171, 120, 120};


void MaiMenu::BuildMainMenu(void) {
    // this -> buttons = new MaiButton buttons[9];
    this -> menu = MAIN_MENU;
    this -> cur_Tft.lcd_clear_screen(GREY);

    
    for (int i; i < 8; i++) {
        this -> buttons[i] = this -> BuildButton(mainxcoords[i], mainycoords[i]); // %, / operator order builds buttons in horizontal lines, while /, % builds vertically
        // Serial.println(buttons[i].x2 - buttons[i].x1);
    }

}

MaiButton MaiMenu::BuildButton(uint16_t x, uint16_t y, uint16_t width, uint16_t height) {
    // this -> cur_Tft.lcd_fill_rect(x, y, width, height, BUTTON_D_GREY);
    // Button border
    return MaiButton(x, y, width, height, this -> cur_Tft);
    
}

MaiButton MaiMenu::BuildButton(uint16_t x, uint16_t y) {
    return MaiMenu::BuildButton(x, y, 64, 40);
}

MaiMenu Menu = MaiMenu();
