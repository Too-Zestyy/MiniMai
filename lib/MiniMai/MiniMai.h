//GUI 'page' IDs to keep switch cases consistent in-case the IDs change
#define MAIN_MENU 0

class MaiButton {
    public:
        int x1, x2, y1, y2;
        MaiButton(uint16_t x, uint16_t y, uint16_t width, uint16_t height, TFT Tft);
        MaiButton();

        bool isPressed(int touchX, int touchY);
};

class MaiMenu {
    TFT cur_Tft;
    // MaiButton buttons[8];
    
    public:
        MaiMenu();
        MaiButton buttons[8];
        int menu;
        void SetTFT(TFT Tft);
        int add(int a, int b);
        void BuildMainMenu(void);
        MaiButton BuildButton(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
        MaiButton BuildButton(uint16_t x, uint16_t y);

        int buttonCheck(int touchX, int touchY);
};

extern MaiMenu Menu;