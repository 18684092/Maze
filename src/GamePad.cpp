/*

Author: Andy Perrett 2019
Course: BSc Computer Science Level 1

*/

#include "GamePad.h"

GamePad::GamePad()
{
    // Constructor
}

joystick GamePad::ReadDevice(int deviceNumber)
{
    GetEvent(deviceNumber);
    return E;
}

void GamePad::GetEvent(int deviceNumber)
{
    struct js_event e;
    string device = "/dev/input/js";
    device += std::to_string(deviceNumber);
    int fd = open (device.c_str() , O_NONBLOCK);
    // read all events
    while (read (fd, &e, sizeof(e)) > 0)
    {
        // Buttons
        if (e.type == (JS_EVENT_INIT | JS_EVENT_BUTTON))
        {
            E.button[e.number] = e.value == 1 ? true : false;
        }

        // joy sticks
        if ( e.type == (JS_EVENT_INIT | JS_EVENT_AXIS ))
        {
            // left
            if (e.number == 1)
            {
                E.y1Value = e.value;
            }
            if (e.number == 0)
            {
                E.x1Value = e.value;
            }
            // right
            if (e.number == 2)
            {
                E.y2Value = e.value;
            }
            if (e.number == 3)
            {
                E.x2Value = e.value;
            }
        }
    }
    close(fd);
    // Set Compass
    if ((E.x1Value > SENSITIVITY) &&
        (E.y1Value < SENSITIVITY && E.y1Value > -SENSITIVITY)) E.Compass = "E";
    else if ((E.x1Value < -SENSITIVITY) &&
        (E.y1Value < SENSITIVITY && E.y1Value > -SENSITIVITY)) E.Compass = "W";
    else if ((E.x1Value < SENSITIVITY) &&
        (E.x1Value > -SENSITIVITY) && (E.y1Value > SENSITIVITY)) E.Compass = "S";
    else if ((E.x1Value < SENSITIVITY) &&
        (E.x1Value > -SENSITIVITY) && (E.y1Value < -SENSITIVITY)) E.Compass = "N";
    else if ((E.x1Value > SENSITIVITY) &&
        (E.y1Value < -SENSITIVITY)) E.Compass = "NE";
    else if ((E.x1Value < -SENSITIVITY) &&
        (E.y1Value < -SENSITIVITY)) E.Compass = "NW";
    else if ((E.x1Value < -SENSITIVITY) &&
        (E.y1Value > SENSITIVITY)) E.Compass = "SW";
    else if ((E.x1Value > SENSITIVITY) &&
        (E.y1Value > SENSITIVITY)) E.Compass = "SE";
    else E.Compass = " ";
}

GamePad::~GamePad()
{
}
