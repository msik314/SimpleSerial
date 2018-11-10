#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "serial.h"

int main(int argc, char** argv)
{
    SerialPort port;
    int res = 0;
    char ostr[8] = {};
    char istr[8] = {};
    
    if(argc < 2)
    {
        fputs("Invalid usage: no port given\n", stderr);
        return -1;
    }
    
    srand(time(NULL));
    
    port = serialInit(argv[1], 9600);
    
    for(int i = 0; i < 10; ++i)
    {
        for(int j = 0; j < 8; ++j)
        {
            ostr[j] = (char)(rand() % 256);
        }
        
        printf("Sending %c%c%c%c%c%c%c%c to serial port\n", ostr[0], ostr[1], ostr[2], ostr[3], ostr[4], ostr[5], ostr[6], ostr[7]);
        serialWrite(port, (uint8_t*)ostr, 8);
    
        printf("Waiting for response...\n");
        res = serialRead(port, (uint8_t*)istr, 8);
        
        if(res < 0)
        {
            fputs("Error: unable to read from serial port\n", stderr);
            break;
        }
        else
        {
            printf("%c%c%c%c%c%c%c%c\n", istr[0], istr[1], istr[2], istr[3], istr[4], istr[5], istr[6], istr[7]);
        }
    }
    
    serialClose(port);
    
    return 0;
}
