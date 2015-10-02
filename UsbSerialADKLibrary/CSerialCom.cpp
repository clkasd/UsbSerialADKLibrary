//
//  CSerialCom.cpp
//  PiribotPilotArduino
//
//  Created by Aykut Celik on 28/08/15.
//  Copyright (c) 2015 Aykut Celik. All rights reserved.
//

#include "CSerialCom.h"
#include <Arduino.h>
#include "adk.h"
bool connected;
USB Usb;
ADK adk(&Usb, "OBSSRobotics", // Manufacturer Name
        "PiribotPilot", // Model Name
        "Piribot pilot application", // Description (user-visible string)
        "1.0", // Version
        "http://obssrobotics.com", // URL (web page to visit if no installed apps support the accessory)
        "123456789"); // Serial Number (optional)

CSerialCom::CSerialCom()
{
#if !defined(__MIPSEL__)
    while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
    if (Usb.Init() == -1) {
        Serial.print("\r\nOSCOKIRQ failed to assert");
        while (1); // halt
    }
}
CSerialCom::~CSerialCom()
{
    commandList.clear();
}
String incomingData;

void CSerialCom::listen()
{
    Usb.Task();
    if(adk.isReady())
    {
        if(!connected)
        {
            connected=true;
            Serial.print(F("\r\nConnected to accessory"));
        }
        uint8_t msg[9];
        uint16_t len = sizeof(msg);
        uint8_t rcode = adk.RcvData(&len, msg);
        if (rcode && rcode != hrNAK) {
            
        }else if(len>0)
        {
            for (int i=0;i<len; i++) {
                incomingData += (char)msg[i];
            }
        }
        parseData(incomingData);
        incomingData="";
    }
    else {
        if (connected) {
            connected = false;
            Serial.print(F("\r\nDisconnected from accessory"));
        }
    }
    
}
void CSerialCom::parseData(String data)
{

    for (int i=0; i<commandList.getSize(); i++) {
        if(commandList.get(i).command==data)
        {
            Serial.print("Matched command : ");
            Serial.println(data);
            commandList.get(i).function();
        }
    }
}
void CSerialCom::send(String str)
{
    Usb.Task();
    if (adk.isReady()) {
        uint8_t payload[str.length()+1];
        str.getBytes(payload, str.length()+1);
        uint8_t rcode=adk.SndData(sizeof(payload), payload);
        
    }
}
void CSerialCom::setCommand(void (*function)(),String id)
{
    
    CommandStruct comStrct;
    comStrct.function=function;
    comStrct.command=id;
    commandList.add(comStrct);
    Serial.println("Added command");
}









