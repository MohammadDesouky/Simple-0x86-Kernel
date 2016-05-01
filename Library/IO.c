#include <IO.h>

void SendByteToPort (unsigned short PortAddress, unsigned char Byte)
{
 __asm__ __volatile__ ("outb %1, %0" : : "dN" (PortAddress), "a" (Byte));
}

unsigned char ReadByteFromPort(unsigned short Port)
{
    unsigned char ReadedByte;

    __asm__ __volatile__ ("inb %1, %0" : "=a" (ReadedByte) : "dN" (Port));

    return ReadedByte;
}
