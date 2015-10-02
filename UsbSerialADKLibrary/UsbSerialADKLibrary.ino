//
// UsbSerialADKLibrary
//
// arduino - android serial communication library example
// Developed with [embedXcode](http://embedXcode.weebly.com)
//
// Author 		Aykut Celik
// 				Aykut Celik
//
// Date			30/09/15 14:55
// Version		1.0
//
// Copyright	© Aykut Celik, 2015
//
// See         ReadMe.txt for references
//
#include "adk.h"
#include "CSerialCom.h"
#include <Arduino.h>
#include "GlobalDef.h"

CSerialCom cSerialcom;
void setup()
{
    Serial.begin(115200);
    cSerialcom.setCommand(getBatteryVoltage, "getBV");
}
void loop()
{
    cSerialcom.listen();
}
void getBatteryVoltage()
{
    cSerialcom.send("batterry voltage: 13.6");
}