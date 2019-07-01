/*

Author: Andy Perrett 2019
Course: BSc Computer Science Level 1

*/

#ifndef GAMEPAD_H
#define GAMEPAD_H

#include <iostream>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <cstdint> // uint8_t

#define JS_EVENT_BUTTON         0x01    /* button pressed/released */
#define JS_EVENT_AXIS           0x02    /* joystick moved */
#define JS_EVENT_INIT           0x80    /* initial state of device */

#define SENSITIVITY             500     /* sensitivity of stick 1 */

using namespace std;

struct js_event
{
    uint32_t time;  /* event timestamp in milliseconds */
    int16_t value;  /* value */
    uint8_t type;   /* event type */
    uint8_t number; /* axis/button number */
};

struct joystick
{
    // left joy
    int16_t x1Value;  // -32767 --> 32767
    int16_t y1Value;  // -32767 --> 32767
    // right joy
    int16_t x2Value;  // -32767 --> 32767
    int16_t y2Value;  // -32767 --> 32767
    // Button array
    bool button[50];
    string Compass;
};

class GamePad
{
    public:
        GamePad();
        joystick ReadDevice(int);
        virtual ~GamePad();

    protected:

    private:
        joystick E;
        void GetEvent(int);
};

#endif // GAMEPAD_H
