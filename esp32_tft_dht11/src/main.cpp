#include <Arduino.h>

#include "image.h"

#define TFT_RST 2
#define TFT_RS 4
#define SHOW_MESSAGE true
#include "mod/TFT_22_ILI9225_MOD.h"

TFT_22_ILI9225_MOD tft(TFT_RST, TFT_RS);

void setup(){
    tft.begin(0, 0xFFFF);
}

void loop(){
    // tft.drawColorImage(0, 0, _176x220_bitmap, 0, 0, 176, 220);
    tft.drawGFXTextLine(0xFFFF, 0xF, 1, 0, "Author: ", "ngxxfus");
    tft.drawGFXTextLine(0xFFFF, 0xF, 1, 3, "Contact: ", "fb.com/ngxx.fus", "Max line: ", tft.maxLine(0xF));
    while(1);
}