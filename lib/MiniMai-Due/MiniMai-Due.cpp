#include <lcd.h>

#include <MiniMai-Due.h>

// Ensuring zone character codes are consistent across lib
#include <charset.cpp>

// #include "zonesraw.pgm"

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
// simplify checking for bounds
#define BETWEEN(value, min, max) (value < max && value > min)
// const byte ZoneA1 = 0x2;



// int centreZone[8][2] = {{120, 91}, {140, 100}, {149, 120}, {140, 140}, {120, 149}, {100, 140}, {91, 120}, {100, 100}};
// int aZones[8][4][2] = {
//     {{171, 171}, {239, 239}, {120, 239}, {120, 192}},
//     {{192, 120}, {239, 120}, {239, 239}, {171, 171}},
//     {{239, 0}, {239, 120}, {192, 120}, {171, 70}},
//     {{120, 0}, {239, 0}, {171, 70}, {120, 48}},
//     {{0, 0}, {120, 0}, {120, 48}, {70, 70}},
//     {{48, 120}, {0, 120}, {0, 0}, {70, 70}},
//     {{70, 171}, {0, 239}, {0, 120}, {48, 120}},
//     {{120, 192}, {120, 239}, {0, 239}, {70, 171}}
// };
// int bZones[8][4][2] = {
//     {{140, 140}, {171, 171}, {120, 192}, {120, 149}},
//     {{149, 120}, {192, 120}, {171, 171}, {140, 140}},
//     {{171, 70}, {192, 120}, {149, 120}, {140, 100}},
//     {{120, 48}, {171, 70}, {140, 100}, {120, 91}},
//     {{70, 70}, {120, 48}, {120, 91}, {100, 100}},
//     {{48, 120}, {91, 120}, {100, 100}, {70, 70}},
//     {{100, 140}, {91, 120}, {48, 120}, {70, 171}}, 
//     {{120, 149}, {120, 192}, {70, 171}, {100, 140}}
// };

int centreZone[8][2] = {{120, 91}, {140, 99}, {148, 120}, {140, 140}, {120, 148}, {99, 140}, {91, 120}, {99, 99}};
int aZones[8][4][2] = {
    {{170, 170}, {239, 239}, {120, 239}, {120, 192}},
    {{192, 120}, {239, 120}, {239, 239}, {170, 170}},
    {{239, 0}, {239, 120}, {192, 120}, {170, 69}},
    {{120, 0}, {239, 0}, {170, 69}, {120, 48}},
    {{0, 0}, {120, 0}, {120, 48}, {69, 69}},
    {{48, 120}, {0, 120}, {0, 0}, {69, 69}},
    {{69, 170}, {0, 239}, {0, 120}, {48, 120}},
    {{120, 192}, {120, 239}, {0, 239}, {69, 170}}
};
int bZones[8][4][2] = {
    {{140, 140}, {170, 170}, {120, 192}, {120, 148}},
    {{148, 120}, {192, 120}, {170, 170}, {140, 140}},
    {{170, 69}, {192, 120}, {148, 120}, {140, 99}},
    {{120, 48}, {170, 69}, {140, 99}, {120, 91}},
    {{69, 69}, {120, 48}, {120, 91}, {99, 99}},
    {{48, 120}, {91, 120}, {99, 99}, {69, 69}},
    {{99, 140}, {91, 120}, {48, 120}, {69, 170}}, 
    {{120, 148}, {120, 192}, {69, 170}, {99, 140}}
};

int mainxcoords[8] = {45, 131, 45, 131, 45, 131, 45, 131};
// int mainycoords[8] = {260, 260, 199, 199, 138, 138, 77, 77};
int mainycoords[8] = {273, 273, 222, 222, 171, 171, 120, 120};


// Struct for the bounding boxes of shapes for simpler testing of if a coord is far away from a zone


coordBounds returnBounds(int x1, int y1, int x2, int y2) {
    coordBounds boundset;
    boundset.bounds[0][0] = x1;
    boundset.bounds[0][1] = y1;
    boundset.bounds[1][0] = x2;
    boundset.bounds[1][1] = y2;
    return boundset;
}

// MaiPoly:MaiPoly(uint16_t c1, uint16_t c2, uint16_t c3, uint16_t c4, TFT Tft) {

// }

// MaiButton::MaiButton(int x, int y, int width, int height, TFT Tft) {
//     Tft.lcd_draw_line(x, y+1, x+width-1, y+1, BUTTON_D_GREY);
//     Tft.lcd_draw_line(x, y, x+width-1, y, BUTTON_D_GREY);
//     Tft.lcd_draw_line(x, y+2, x, y+height-1, BUTTON_D_GREY);
//     Tft.lcd_draw_line(x+1, y+2, x+1, y+height-1, BUTTON_D_GREY);
//     Tft.lcd_draw_line(x+2, y+height-2, x+width-1, y+height-2, BUTTON_D_GREY);
//     Tft.lcd_draw_line(x+2, y+height-1, x+width-1, y+height-1, BUTTON_D_GREY);
//     Tft.lcd_draw_line(x+width-2, y+height-2, x+width-2, y+2, BUTTON_D_GREY);
//     Tft.lcd_draw_line(x+width-1, y+height-2, x+width-1, y+2, BUTTON_D_GREY);

//     Tft.lcd_fill_rect(x+2, y+2, width-4, height/2-(height/10), BUTTON_M_GREY);
//     Tft.lcd_fill_rect(x+2, y+(height/2)-2, width-4, height/2, BUTTON_L_GREY);
//     x1 = x; x2 = x+width; y1 = y; y2 = y+height;
// }

// MaiButton::MaiButton() {
//     x1 = x2 = y1 = y2 = 0;
// }

// bool MaiButton::isPressed(int touchX, int touchY) {
//     // Serial.println(touchX - x1);
//     // Serial.println(touchY - y1);
//     if ((touchX >= this -> x1 and touchX <= this -> x2) and (touchY >= this -> y1 and touchX <= this -> y2)) {
//         return true;
//     }

//     else {
//         return false;
//     }
// }

MaiMenu::MaiMenu() {
    this -> menu = -1;
}

void MaiMenu::SetTFT(TFT Tft) {
    this -> cur_Tft = Tft;
}

// void MaiMenu::setCentreCoords(int centre[8][2]) {
//     this -> centreZone = centre;
// }

// void MaiMenu::setaZones(int aZoneCoords[8][4][2]) {
//     this -> aZones = aZoneCoords;
// }

// void MaiMenu::setbZones(int bZoneCoords[8][4][2]) {
//     this -> bZones = bZoneCoords;
// }

// drawLine and fill are meant to be replaceable in case of different hardware being used.
// As long as these functions are rewritten in those cases to take the arguments in the same way, no rewriting of the library should be needed.

void MaiMenu::drawLine(int x1, int y1, int x2, int y2, int colour) {
    this -> cur_Tft.lcd_draw_line(x1, y1, x2, y2, colour);
}

void MaiMenu::fill(int colour) {
    this -> cur_Tft.lcd_clear_screen(colour);
}

void MaiMenu::drawShape(int points[][2], int numPoints, int colour) {
    int lastIndex = numPoints-1;
    for (int point = 0; point < lastIndex; point++) {
        this -> drawLine(points[point][0], points[point][1], points[point+1][0], points[point+1][1], colour);
    };

    this -> drawLine(points[0][0], points[0][1], points[lastIndex][0], points[lastIndex][1], colour);
}

void MaiMenu::drawQuad(int points[][2], int colour) {
    return this -> drawShape(points, 4, colour);
}

void MaiMenu::drawQuads(int zones[][4][2], int numQuads, int colour) {
    for (int quad = 0; quad < numQuads; quad++) {
        this -> drawQuad(zones[quad], colour);
    }
    // this -> drawQuad(zones[0], WHITE);
}

coordBounds MaiMenu::getBounds(int polyPoints[][2]) {
    int minX = 32767; int minY = 32767;
    int maxX = 0; int maxY = 0;
    for (int coord = 0; coord < sizeof(polyPoints)/sizeof(polyPoints[0]); coord++) {
        if (polyPoints[coord][0] < minX) {minX = polyPoints[coord][0];} else if (polyPoints[coord][0] > maxX) {maxX = polyPoints[coord][0];}
        if (polyPoints[coord][1] < minY) {minY = polyPoints[coord][1];} else if (polyPoints[coord][1] > maxY) {maxY = polyPoints[coord][1];}
    }
    return returnBounds(minX, minY, maxX, maxY);
}

char MaiMenu::getCoordVal(int x, int y) {
    return this -> zoneMap[y][x];
}

bool MaiMenu::inPoly(int x, int y, int polyPoints[][2], int pointNum) {
    // int index = 0;
    bool inside = false;

    coordBounds polyBounds = getBounds(polyPoints);

    if (BETWEEN(x, polyBounds.bounds[0][0], polyBounds.bounds[1][0]) && BETWEEN(y, polyBounds.bounds[0][1], polyBounds.bounds[1][1])) {
        inside = true;
    }

    return inside;

}

int MaiMenu::getZoneTouch(int xTouch, int yTouch) {

    if (this->inPoly(xTouch, yTouch, this->centreZone, 8)) {return 0;}
    for (int zone = 0; zone < 8; zone++) {
        if (this->inPoly(xTouch, yTouch, this->aZones[zone], 4)) {return 0;}
    }
    // int testlist[4][2] = {{0, 0}, {320, 0}, {320, 320}, {0, 320}}; 
    // if (this->inPoly(xTouch, yTouch, testlist, 4)) {return 0;}

    // for (int centrePoint = 0; centrePoint < 8; centrePoint++) {
        
    // }
    
    // for (int aZone = 0; aZone < 8; aZone++) {
    //     continue;
    // }

    // for (int bZone = 0; bZone < 8; bZone++) {
    //     continue;
    // }

    return -1;
}

buttonState MaiMenu::getZonesTouched(int touches[][2]) {

    buttonState state = buttonState();
    // for (int i = 0; i < 20; i++) {
    //     state.states[i] = true;
    // }

    for (int i = 0; i < 20; i++) {
        state.states[i] = false;
    }

    // if (this->getCoordVal(coords[0][0], coords[0][1]) == '\x23') {
    //         state.states[0] = true;
    // }
    // state.states = {
    // // A1, B1, A2, B2, x
    // false, false, false, false, false,
    // // A3, B3, A4, B4, x
    // false, false, false, false, false,
    // // A5, B5, A6, B6, x
    // false, false, false, false, false,
    // // A7, B7, A8, B8, C
    // false, false, false, false, false};
    // SerialUSB.println(touches[0][0]);

    for (int touch = 0; touch < sizeof(this->touches)/sizeof(this->touches[0]); touch++) {
        if (this->touches[touch][0] != -1) {
            // if (this->getCoordVal(this->touches[touch][0], this->touches[touch][1]) == '\x23') {
            //     state.states[0] = true;
            // }
        
            switch(this->getCoordVal(this->touches[touch][0], this->touches[touch][1])) {
                // indexing on zones follows as Centre, A, B
                case CENTRE_ZONE:
                    state.states[19] = true;
                    break;
                case ZONE_A1:
                    state.states[0] = true;
                    break;
                case ZONE_A2:
                    state.states[2] = true;
                    break;
                case ZONE_A3:
                    state.states[5] = true;
                    break;
                case ZONE_A4:
                    state.states[7] = true;
                    break;
                case ZONE_A5:
                    state.states[10] = true;
                    break;
                case ZONE_A6:
                    state.states[12] = true;
                    break;
                case ZONE_A7:
                    state.states[15] = true;
                    break;
                case ZONE_A8:
                    state.states[17] = true;
                    break;
                case ZONE_B1:
                    state.states[1] = true;
                    break;
                case ZONE_B2:
                    state.states[3] = true;
                    break;
                case ZONE_B3:
                    state.states[6] = true;
                    break;
                case ZONE_B4:
                    state.states[8] = true;
                    break;
                case ZONE_B5:
                    state.states[11] = true;
                    break;
                case ZONE_B6:
                    state.states[13] = true;
                    break;
                case ZONE_B7:
                    state.states[16] = true;
                    break;
                case ZONE_B8:
                    state.states[18] = true;
                    break;
                }
            memcpy(this->touches[touch], this->emptyTouch, this->touchSize);
            }
            
        }
    // this -> touches = {{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1},
    //                    {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}};
    return state;
    
}

bool MaiMenu::getTouchChar(int coords[][2]) {

    buttonState state = buttonState();
    // for (int i = 0; i < 20; i++) {
    //     state.states[i] = true;
    // }

    for (int i = 0; i < 20; i++) {
        state.states[i] = false;
    }

    
    // state.states = {
    // // A1, B1, A2, B2, x
    // false, false, false, false, false,
    // // A3, B3, A4, B4, x
    // false, false, false, false, false,
    // // A5, B5, A6, B6, x
    // false, false, false, false, false,
    // // A7, B7, A8, B8, C
    // false, false, false, false, false};

    for (int touch = 0; touch < sizeof(coords)/sizeof(coords[0]); touch++) {
        if (this->getCoordVal(coords[touch][0], coords[touch][1]) == '\x23') {
            state.states[0] = true;
        }
        state.states[0] = true;
    }

    return (this->getCoordVal(coords[0][0], coords[0][1]) == '\x23');
}

stateMessage genMessage(buttonState state) {
    stateMessage message = stateMessage();
    // NOTE: remember struct initialises with brackets and '@'s
    // data[0] = '(';
    for (byte i = 0; i < 4; i++) {
        char val = '@';
        for (byte j = 0; j < 5; j++) {
            if (state.states[i * 5 + j]) val |= 1 << j;
                message.message[i + 1] = val;}
    }
    return message;
// data[5] = '@';
// data[6] = '@';
// memcpy(data + 7, "@@@@@", 4);
// data[11] = '@';
// data[12] = '@';
// data[13] = ')';

}

stateMessage MaiMenu::getMessage(int coords[][2]) {
    return genMessage(this->getZonesTouched(coords));    
}




void MaiMenu::DrawMaiZones(void) {
    this -> menu = MAIN_MENU;
    this -> fill(GREY);

    // this -> drawQuad(aZones[0], WHITE);
    this -> drawQuads(this->aZones, 8, RED);
    this -> drawQuads(this->bZones, 8, GREEN);
    this -> drawShape(this->centreZone, 8, BLUE);

}



// int centreZone[8][2] = {{120, 91}, {140, 100}, {149, 120}, {140, 140}, {120, 149}, {100, 140}, {91, 120}, {100, 100}};

MaiMenu Menu = MaiMenu();
