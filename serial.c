#include "serial.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

#define STRING_MAX 256

SerialPort serialInit(const char* port, int32_t baud)
{
    SerialPort com;
    DCB dcb;
    int32_t res = 0;
    char dcbSettings[STRING_MAX];
    
    com = CreateFile(port, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
    
    if(com == INVALID_HANDLE_VALUE)
    {
        perror("serialInit: unable to initialize serial port");
        return INVALID_HANDLE_VALUE;
    }
    
    sprintf(dcbSettings, "%d,n,8,1", baud);
    
    memset(&dcb, 0, sizeof(dcb));
    dcb.DCBlength = sizeof(dcb);
    res = BuildCommDCB(dcbSettings, &dcb);
    if(!res)
    {
        perror("serialInit: unable to create serial port settings");
        return INVALID_HANDLE_VALUE;
    }
    
    res = SetCommState(com, &dcb);
    if(!res)
    {
        perror("serialInit: unable set serial port settings");
        return INVALID_HANDLE_VALUE;
    }
    
    /*This seems to be necessary in order for the connection to function properly.*/
    Sleep(2000);
    
    return com;
}

int32_t serialClose(SerialPort port)
{
    return CloseHandle(port);
}

int32_t serialRead(SerialPort port, uint8_t* data, int32_t size)
{
    DWORD read = 0;
    int32_t res = ReadFile(port, data, size, &read, NULL);
    
    if(res == 0)
    {
        perror("serialRead: unable to read serial port");
        return -1;
    }
    
    return (int32_t)read;
}

int32_t serialWrite(SerialPort port, uint8_t* data, int32_t size)
{
    DWORD written = 0;
    int32_t res = WriteFile(port, data, size, &written, NULL);
    
    if(!res)
    {
        perror("serialRead: unable to write to serial port");
        return -1;
    }
    
    if(written != size)
    {
        perror("serialRead: unable to write full buffer to serial port");
    }
    
    return (int32_t)written;
}
