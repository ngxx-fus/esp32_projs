#ifndef TFT_22_ILI9225_MOD_H
#define TFT_22_ILI9225_MOD_H

#if SHOW_MESSAGE==true
#pragma message("\
\n--------***--------\
\nHello from ngxxfus,\n\
    This header file have packaged again from TFT_22_ILI9225 \nlib. \
For add some notes and functions :v.\n\
\
The dependencies (PlatformIO.ini):\n\
    lib_deps = \n\
        SPI\n\
        nkawu/TFT 22 ILI9225@^1.4.5\n\
" \
                "The connections:\n\
    LCD-TFT (slave)     ESP32 (master)\n\
    VCC                 VIN (5V)\n\
    GND                 GND\n\
    CLK                 HSPI-CLK  (GPIO14)\n\
    SDA                 HSPI-MOSI (GPIO13)\n\
    RS                  (any GPIO)\n\
    RST                 (any GPIO)\n\
    CS                  HSPI-CS (GPIO15)\n"\
)
#endif

#include <SPI.h>
#include <TFT_22_ILI9225.h>
#include <../fonts/FreeSerif9pt7b.h>

#ifndef TFT_RST
/// @note RST pin im TFT <-> GPIO2 is default
#define TFT_RST 2
#endif

#ifndef TFT_RS
/// @note RS pin im TFT <-> GPIO4 is default
#define TFT_RS 4
#endif

#ifndef SPI_BUS_TYPE
/// @note Set #define SPI_BUS_TYPE before include TFT_22_ILI9225_MOD.h
/// to change SPI_BUS_TYPE.
/// @note Check2 your physical board, normally, there are two type is vspi and hspi.
#define SPI_BUS_TYPE HSPI
#endif

/// @note An SPI object to using SPI communication.
SPIClass spi_obj(SPI_BUS_TYPE);

/// @brief The modified of TFT_22_ILI9225 to add somes functions (drawimage, quick add text)
class TFT_22_ILI9225_MOD : public TFT_22_ILI9225
{
private:
    /// none :v
public:
    
    /// Declare new TFT_22_ILI9225_MOD object
    /// @param rst RST pin, any available GPIO 
    /// @param rs  RS pin, any available GPIO 
    /// @note Using default pin for HSPI :
    /// @note HSPI-CLK <-> (GPIO14)
    /// @note HSPI-MOSI <-> (GPIO13)
    /// @note HSPI-CS <-> (GPIO15)
    TFT_22_ILI9225_MOD(int8_t rst, int8_t rs)
    :TFT_22_ILI9225(rst, rs, (int8_t) 15, (int8_t) 0, (uint8_t) 255)
    {
        /// hehe :v
    }

    /// Declare new TFT_22_ILI9225_MOD object
    /// @param rst RST pin, any available GPIO 
    /// @param rs  RS pin, any available GPIO 
    /// @param cs  RS pin, any available GPIO 
    /// @param others more pins paramerters can be declared, check the original header to know!
    template<class... Tpins>
    TFT_22_ILI9225_MOD(int8_t rst, int8_t rs, int8_t cs, Tpins... others )
    :TFT_22_ILI9225(rst, rs, cs, others...)
    {
        /// hehe :v
    }

    /// Initial tft
    /// @param Orientation orientation, 0=portrait, 1=right rotated landscape, 2=reverse portrait, 3=left rotated landscape
    /// @param BackgroundColor BackgroundColor,16bit-color to set the color of background
    void begin(
        uint8_t Orientation = 0,
        uint16_t BackgroundColor = 0x0
    )
    {
        TFT_22_ILI9225::begin(spi_obj);
        TFT_22_ILI9225::setGFXFont(&FreeSerif9pt7b);
        TFT_22_ILI9225::setBackgroundColor(BackgroundColor);
        TFT_22_ILI9225::setOrientation(Orientation);
        TFT_22_ILI9225::clear();
    }


    /// Draw an black rectangle onto TFT 2.2" screen to clear
    /// @param line the row (line) on tft screen (start from 0) 
    /// @param line_height the distance between to line(row)
    /// @param filled_color the color will be filled onto rectangle
    /// @note - line+line_height < 220
    /// @note - filled_color must be same with backround!
    void clearTextLine(
        uint16_t line, 
        uint16_t line_height = 0xf,
        uint16_t filled_color = 0x0
    ){
        for(uint16_t x = 0; x < 176; ++x)
            for(uint16_t y = (line+1)*line_height+1; y > line*line_height+1; --y)
                TFT_22_ILI9225::drawPixel(x, y, filled_color);
    }


    ///  Draw an image onto TFT 2.2" screen
    /// @param X X position in TFT screen: 0->175 (column)
    /// @param Y Y position in TFT screen: 0->219 (row)
    /// @param Image 16bit-array
    /// @param img_x X position in Image : 0->175 (column)
    /// @param img_y Y position in Image : 0->219 (row)
    /// @param img_w Image width : 0->176
    /// @param img_h Image height : 0->220
    /// @note - The function is writen with  orientation=0
    /// @note - Max(Size(Image)) = wxh = 176x220
    /// @note - Size(Image) >= img_w*img_h
    /// @note - The image will be crop from (img_x, img_y) -> (img_w-1, img_h-1)
    /// @note - Drawing direction: from top-left -> botom-right.
    /// @note - Image to 16bit-array: https:///javl.github.io/image2cpp/.
    void drawColorImage(
        uint16_t X, uint16_t Y, 
        uint16_t* image, 
        uint16_t img_x = 0, uint16_t img_y = 0,
        uint16_t img_w = 176, uint16_t img_h = 220
    ){
        if( X >= TFT_22_ILI9225::maxX() || Y >= TFT_22_ILI9225::maxY()  ||\
            img_w > 176     || img_h > 220      ||\
            img_w < img_x+X  || img_h < img_y+Y
        ) return; 

        for(uint16_t x = 0; x < img_w-img_x-X; ++x){
            for(uint16_t y = 0; y < img_h-img_x-Y; ++y){
                TFT_22_ILI9225::drawPixel(X+x, Y+y, image[(y+img_y)*img_w+(x+img_x)]);
            }
        }
    }

    /// Print a msg into a line in tft screen.
    /// @param line the row (line) on tft screen (start from 0) 
    /// @param msg the msg will be printed  onto tft screen 
    /// @param text_color the color of msg, 16bit-color
    /// @param line_height the distance between to line(row)
    /// @note  + The limit range of row: [0, 220/line_height]
    /// @note  + The limit of msg size: 16 characters
    /// @note  + If line_height is too small, the lines can be overlapped each other!
    /// @note  + All unit are in [PIXEL]!
    template<class T>
    void drawGFXTextLine(
        uint16_t line,
        T msg, 
        uint16_t text_color = 0x46f0,
        uint16_t line_height = 0x000f
    )
    {
        TFT_22_ILI9225::drawGFXText(0, (line+1)*line_height, String(msg), text_color);
    }

    /// Print a msg into a line in tft screen.
    /// @param text_color the color of msg, 16bit-color
    /// @param line_height the distance between to line(row)
    /// @param newline add new (newline) line(s) for each msg, rcm 0 or 1.
    /// @param line the row (line) on tft screen (start from 0) 
    /// @param msg the msg will be printed  onto tft screen 
    /// @param msgs the other msg will be printed  onto tft screen 
    /// @note  + The limit range of row: [0, 220/line_height]
    /// @note  + The limit of msg size: 16 characters
    /// @note  + If line_height is too small, the lines can be overlapped each other!
    /// @note  + All unit are in [PIXEL]!
    template<class Tmsg, class...Tmsgs>
    void drawGFXTextLine(
        uint16_t text_color,
        uint16_t line_height,
        uint16_t newline,
        uint16_t line,
        Tmsg msg,
        Tmsgs... msgs
    )
    {
        
        TFT_22_ILI9225::drawGFXText(0, (line+1)*line_height, String(msg), text_color);
        line = (line+newline)%(220/line_height);
        drawGFXTextLine(text_color, line_height, newline, line, msgs...);
    }

    /// Get maximum of the number of line based on line_height
    /// @param line_height the distance between to line(row)
    /// @return Return max(line)
    uint16_t maxLine(uint16_t line_height = 0xf){
        return 176/line_height;
    }

};



#endif