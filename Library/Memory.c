#include <Memory.h>
#include <IO.h>

char * CopyMemory(char * Source, char * Destination,unsigned Length)
{
    char *sp = Source;
    char *dp = Destination;
    for(; Length != 0; Length--) *dp++ = *sp++;
    return Destination;
}

void * MemorySetToValueByte(void * Destination, char Value,int Times)
{
    char *Temp = (char *)Destination;
    for( ; Times != 0; Times--) *Temp++ = Value;
    return (void *)Destination;
}

void * MemorySetToValue2Bytes(void * Destination,unsigned short Value, int Times)
{
    unsigned short * Temp = (unsigned short*)Destination;

    for( ; Times != 0; Times--) *Temp++ = Value;
    return (void *)(unsigned int)Destination;
}
void EnableA20()//silly old IBM intel standards 2al A 3ashan y7afzo 3ala el compatability
{
  unsigned char x=ReadByteFromPort(0x92);
  x|=2;
  SendByteToPort(0x92,x);
}
