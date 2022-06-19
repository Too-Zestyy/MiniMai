//GUI 'page' IDs to keep switch cases consistent in-case the IDs change
#define MAIN_MENU 0

// class MaiButton {
//     public:
//         int x1, x2, y1, y2;
//         MaiButton(int x, int y, int width, int height, TFT Tft);
//         MaiButton();

//         bool isPressed(int touchX, int touchY);
// };
struct coordBounds {
    int bounds[2][2];
};

class MaiMenu {
    TFT cur_Tft;
    int zoneCount = 17;
    // NOTE: zoneMap is indexed as [y][x]
    byte zoneMap[320][240] = {
        #include "zones.arr"
        };
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
        int menu;
        MaiMenu();
        void SetTFT(TFT Tft);

        void setCentreCoords(int centre[8][2]);
        void setaZones(int aZoneCoords[8][4][2]);
        void setbZones(int bZoneCoords[8][4][2]);
        void DrawMaiZones(void);

        byte getCoordVal(int x, int y);
        coordBounds getBounds(int polyPoints[][2]);
        int getZoneTouch(int xTouch, int yTouch);

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