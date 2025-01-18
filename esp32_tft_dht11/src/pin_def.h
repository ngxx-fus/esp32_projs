#ifndef _PIN_DEF_H_
#define _PIN_DEF_H_

#include <Arduino.h>

#pragma message(                                              \
    "\n--------***--------"                                   \
    "\nHello from ngxxfus,"                                   \
    "\n    This header file was made for quick blink LED,"    \
    "\nsplit all setup command into modules, this module for" \
    "\nset-up all things related to GPIO (I/O devices only!)."\
)

#define INDICATOR_LED 26
/// #define DEV_0 25
/// #define DEV_1 27

namespace io_pin
{
    /// Blink led to indicate error.
    /// \param err_code error code
    /// @note Based on your rule about error, in this function, 
    /// the Value(err_code) is the number of times the LED will be "blink".
    /// For each "blink" period, the led will be turned off for 50ms 
    /// then on 200ms then off 50ms.
    void set_indicator(int err_code = 0)
    {
        ++err_code;
        while (err_code--)
        {
            digitalWrite(INDICATOR_LED, LOW);
            delay(50);
            digitalWrite(INDICATOR_LED, HIGH);
            delay(200);
            digitalWrite(INDICATOR_LED, LOW);
            delay(50);
        }
    }

    void init()
    {
        pinMode(INDICATOR_LED, OUTPUT);
        io_pin::set_indicator(0x0);
    }
}
#endif