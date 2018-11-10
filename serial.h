#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>
#include <windows.h>

typedef HANDLE SerialPort;

SerialPort serialInit(const char* port, int32_t baud);
int32_t serialClose(SerialPort port);
int32_t serialRead(SerialPort port, uint8_t* data, int32_t size);
int32_t serialWrite(SerialPort port, uint8_t* data, int32_t size);
#endif /*SERIAL_H*/
