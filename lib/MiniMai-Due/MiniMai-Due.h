//GUI 'page' IDs to keep switch cases consistent in-case the IDs change
#define MAIN_MENU 0

// class MaiButton {
//     public:
//         int x1, x2, y1, y2;
//         MaiButton(int x, int y, int width, int height, TFT Tft);
//         MaiButton();

//         bool isPressed(int touchX, int touchY);
// };

// char data[14];
// const bool p1_btn[20] = {
// // A1, B1, A2, B2, x
// false, false, false, false, false,
// // A3, B3, A4, B4, x
// false, false, false, false, false,
// // A5, B5, A6, B6, x
// false, false, false, false, false,
// // A7, B7, A8, B8, C
// false, false, false, false, false
// };

// data[0] = '(';
// for (byte i = 0; i < 4; i++) {
// char val = '@';
// for (byte j = 0; j < 5; j++)
// if (p1_btn[i * 5 + j]) val |= 1 << j;
// data[i + 1] = val;
// }
// data[5] = '@';
// data[6] = '@';
// memcpy(data + 7, "@@@@@", 4);
// data[11] = '@';
// data[12] = '@';
// data[13] = ')';

struct coordBounds {
    int bounds[2][2];
};

struct coordSet {
    int coords[][2];
};

// struct buttonState {
//     bool states[20] = {
//     // A1, B1, A2, B2, x
//     false, false, false, false, false,
//     // A3, B3, A4, B4, x
//     false, false, false, false, false,
//     // A5, B5, A6, B6, x
//     false, false, false, false, false,
//     // A7, B7, A8, B8, C
//     false, false, false, false, false};
// };

struct buttonState {
    bool states[20] = {};
};

struct stateMessage {
    char message[14] = 
    {'(', 
    '@', '@', '@', '@', 
    '@', '@', '@', '@', 
    '@', '@', '@', '@',
    ')'};
    // stateMessage() {this -> message[0] = '{'; this -> message[15] = '}'};
};

// struct touchSet
// {
//     int touches[][2];
// };


// stateMessage::stateMessage() {
    
// };

class MaiMenu {
    TFT cur_Tft;
    int zoneCount = 17;
    // NOTE: zoneMap is indexed as [y][x]
    // byte zoneMap[320][240] = {
    //     #include "zones.arr"
    //     };
    // byte zoneMap[320][240] = {
    //     #include "zones.arr"
    //     };
    // coords required to draw zones onto the screen
    int centreZone[8][2] = {{120, 91}, {140, 99}, {148, 120}, {140, 140}, {120, 148}, {99, 140}, {91, 120}, {99, 99}};

    int bZones[8][4][2] = {
    {{170, 170}, {239, 239}, {120, 239}, {120, 192}},
    {{192, 120}, {239, 120}, {239, 239}, {170, 170}},
    {{239, 0}, {239, 120}, {192, 120}, {170, 69}},
    {{120, 0}, {239, 0}, {170, 69}, {120, 48}},
    {{0, 0}, {120, 0}, {120, 48}, {69, 69}},
    {{48, 120}, {0, 120}, {0, 0}, {69, 69}},
    {{69, 170}, {0, 239}, {0, 120}, {48, 120}},
    {{120, 192}, {120, 239}, {0, 239}, {69, 170}}};

    int aZones[8][4][2] = {
    {{140, 140}, {170, 170}, {120, 192}, {120, 148}},
    {{148, 120}, {192, 120}, {170, 170}, {140, 140}},
    {{170, 69}, {192, 120}, {148, 120}, {140, 99}},
    {{120, 48}, {170, 69}, {140, 99}, {120, 91}},
    {{69, 69}, {120, 48}, {120, 91}, {99, 99}},
    {{48, 120}, {91, 120}, {99, 99}, {69, 69}},
    {{99, 140}, {91, 120}, {48, 120}, {69, 170}}, 
    {{120, 148}, {120, 192}, {69, 170}, {99, 140}}};
    
    // MaiButton buttons[8];

    private:
        void fill(int colour);
        void drawLine(int x1, int y1, int x2, int y2, int colour);
        void drawShape(int points[][2], int numPoints, int colour);
        void drawQuad(int points[][2], int colour);
        void drawQuads(int shapes[][4][2], int numQuads, int colour);
        bool inPoly(int x, int y, int polyPoints[][2], int pointNum);
    
    public:

        // touchSet touchCoords;
        int touches[10][2] = {{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1},
                           {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}};
        int emptyTouch[2] = {-1, -1};
        int touchSize = sizeof(emptyTouch);
        int menu;
        MaiMenu();
        void SetTFT(TFT Tft);
        void setCentreCoords(int centre[8][2]);
        void setaZones(int aZoneCoords[8][4][2]);
        void setbZones(int bZoneCoords[8][4][2]);
        void DrawMaiZones(void);

        char getCoordVal(int x, int y);
        coordBounds getBounds(int polyPoints[][2]);
        int getZoneTouch(int xTouch, int yTouch);
        buttonState getZonesTouched(int touches[][2]);
        stateMessage getMessage(int coords[][2]);

        char zoneMap[320][240] = {
        #include "zones.arr"
        };

        bool getTouchChar(int coords[][2]);

        // int subtract(int a, int b);
        // int add(int a, int b);
        // void newFunc(void);
        // void BuildMainMenu(void);
        // MaiButton BuildButton(int x, int y, int width, int height);
        // MaiButton BuildButton(int x, int y);
        // MaiButton buttons[8];

        // int buttonCheck(int touchX, int touchY);
};

extern MaiMenu Menu;