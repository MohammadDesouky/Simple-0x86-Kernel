
#include <System.h>
#include <IO.h>
void Restart()
{
    //restart dirty way :D :D triple fault >.<
    /*  __asm__ __volatile__ ("cli");
     ZeroTheIDT();
     LoadIDTToProcessor();
   __asm__ __volatile__ ("sti");*/
   unsigned short good = 0x02;
   while (good & 0x02)
     good = ReadByteFromPort(0x64);
   SendByteToPort(0x64, 0xFE);

}
