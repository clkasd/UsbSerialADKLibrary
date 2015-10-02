//
//  CSerialCom.h
//  PiribotPilotArduino
//
//  Created by Aykut Celik on 28/08/15.
//  Copyright (c) 2015 Aykut Celik. All rights reserved.
//


#include "adk.h"
#include "CList.h"
class CSerialCom
{
public:
    CSerialCom();
    ~CSerialCom();
    void listen();
    void parseData(String data);
    void setCommand(void (*function)(),String identifier);
    void send(String data);
    
private:
    typedef struct _callback {
        String command;
        void (*function)();
    } CommandStruct;
    
    CList<CommandStruct> commandList;
    };
