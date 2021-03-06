/* Microscope controller for Arduino 
 * By Dustin Andrews, Frank Luecke, David Luecke and Allen Burnham, 2012
 * This work is licensed under a Creative Commons Attribution 3.0 Unported License.
 * http://creativecommons.org/licenses/by/3.0/
 * This program is design to run on Arduino MEGA
 * This program emulates the MFC-2000 ASI protocol described at http://www.asiimaging.com/ftp2asi/Manuals/MS2000%20Programming.pdf
 * Code available from https://github.com/dustinandrews/microscope
 */

#ifndef AsiSettings_h
#define AsiSettings_h
#if ARDUINO>=100
#include <Arduino.h> // Arduino 1.0
#else
#include <Wprogram.h> // Arduino 0022
#endif

struct AxisSettings {
  long x;
  long y;
  long z;
};

struct AxisSettingsF {
  float x;
  float y;
  float z;
};


class AsiSettings
{
  public:
    AsiSettings(); 
    AxisSettingsF currentPos;
    AxisSettingsF desiredPos;
    AxisSettingsF maxSpeed;
    AxisSettingsF backlash;
    AxisSettingsF error;
    AxisSettingsF pcros;
    AxisSettingsF setlow;
    AxisSettingsF setup;
    AxisSettingsF overshoot;
    AxisSettings accel;
    AxisSettings unitMultiplier;
    AxisSettings wait;
    AxisSettings zs;
  private:
    void setSettings(AxisSettings *s, int x, int y, int z);
    void setSettings(AxisSettingsF *s, float x, float y, float z);		
};


#endif
