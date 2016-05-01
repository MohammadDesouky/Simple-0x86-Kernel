#include <RTC.h>
#include <IO.h>
#include <VGA.h>
#include <String.h>
#include <System.h>

#define CURRENT_YEAR        2014                            // Change this each year!

int CenturyRegister = 0x00;                                // Set by ACPI table parsing code if possible

unsigned char second;
unsigned char minute;
unsigned char hour;
unsigned char day;
unsigned char month;
unsigned int year;


enum
{
      CMOSAddressPort = 0x70,
      CMOSDataPort   = 0x71
};

int IsUpdateLoading()
{
      SendByteToPort(CMOSAddressPort, 0x0A);
      return (ReadByteFromPort(CMOSDataPort) & 0x80);
}


unsigned char GetRTCRegister(int reg)
{
      SendByteToPort(CMOSAddressPort, reg);
      return  ReadByteFromPort(CMOSDataPort);
}

void ReadRTC()
 {
      unsigned char century;
      unsigned char last_second;
      unsigned char last_minute;
      unsigned char last_hour;
      unsigned char last_day;
      unsigned char last_month;
      unsigned char last_year;
      unsigned char last_century;
      unsigned char registerB;


      while (IsUpdateLoading());
      second =  GetRTCRegister(0x00);
      minute =  GetRTCRegister(0x02);
      hour =  GetRTCRegister(0x04);
      day =  GetRTCRegister(0x07);
      month =  GetRTCRegister(0x08);
      year =  GetRTCRegister(0x09);
      if(CenturyRegister != 0)
      {
            century =  GetRTCRegister(CenturyRegister);
      }

      do {
            last_second = second;
            last_minute = minute;
            last_hour = hour;
            last_day = day;
            last_month = month;
            last_year = year;
            last_century = century;
            while (IsUpdateLoading());           //loop untill update complete
            second =  GetRTCRegister(0x00);
            minute =  GetRTCRegister(0x02);
            hour =  GetRTCRegister(0x04);
            day =  GetRTCRegister(0x07);
            month =  GetRTCRegister(0x08);
            year =  GetRTCRegister(0x09);
            if(CenturyRegister != 0)
            {
                century =  GetRTCRegister(CenturyRegister);
            }
      }
       while( (last_second != second) || (last_minute != minute) || (last_hour != hour) ||
               (last_day != day) || (last_month != month) || (last_year != year) ||
               (last_century != century) );

      registerB =  GetRTCRegister(0x0B);

      // Convert BCD to binary values if necessary

      if (!(registerB & 0x04))
      {
            second = (second & 0x0F) + ((second / 16) * 10);
            minute = (minute & 0x0F) + ((minute / 16) * 10);
            hour = ( (hour & 0x0F) + (((hour & 0x70) / 16) * 10) ) | (hour & 0x80);
            day = (day & 0x0F) + ((day / 16) * 10);
            month = (month & 0x0F) + ((month / 16) * 10);
            year = (year & 0x0F) + ((year / 16) * 10);
            if(CenturyRegister != 0)
            {
                  century = (century & 0x0F) + ((century / 16) * 10);
            }
      }

      // Convert 12 hour clock to 24 hour clock if necessary

      if (!(registerB & 0x02) && (hour & 0x80))
      {
            hour = ((hour & 0x7F) + 12) % 24;
      }

      // Calculate the full (4-digit) year

      if(CenturyRegister != 0)
      {
            year += century * 100;
      }
      //error reading the century
      /*else
      {
        year=-1000;
      }*/
      else
       {
            year += (CURRENT_YEAR / 100) * 100;
            if(year < CURRENT_YEAR) year += 100;
      }
}
//30 04 2016 12:59:00 AM      2016-04-30 12:59:59 AM
char DateTime[23];
char * GetDateTime()
  {
    char * Second=IntToAscii((int)second);
    char * Minute=IntToAscii((int)minute);
    char * tt=hour>12?"PM\0":"AM\0";
    hour=hour>12?hour%12:hour;
    char * Hour=IntToAscii((int)hour);
    char * Day=IntToAscii((int)day);
    char * Month=IntToAscii((int)month);
    char * Year=IntToAscii((int)year);
    DateTime[0]=Year[0];
    DateTime[1]=Year[1];
    DateTime[2]=Year[2];
    DateTime[3]=Year[3];
    DateTime[4]=' ';
    DateTime[5]= month>9?Month[0]:'0';
    DateTime[6]= month>9?Month[1]: Month[0];
    DateTime[7]=' ';
    DateTime[8]=day>9?Day[0]:'0';
    DateTime[9]=Day[1];
    DateTime[10]=' ';
    DateTime[11]=  hour>9?Hour[0]:'0';
    DateTime[12]=Hour[1];
    DateTime[13]=':';
    DateTime[14]=minute>9?Minute[0]:'0';
    DateTime[15]=Minute[1];
    DateTime[16]=':';
    DateTime[17]=second>9?Second[0]:'0';
    DateTime[18]=Second[1];
    DateTime[19]=' ';
    DateTime[20]=  tt[0];
    DateTime[21]=tt[1];
    DateTime[22]=0;
    return DateTime;

  }


void InstallCMOSHandler()
{

    SendByteToPort(CMOSAddressPort, 0x8B);
    char PreviousValueOfRegisterB=ReadByteFromPort(CMOSAddressPort);
    SendByteToPort(CMOSAddressPort, 0x8B);
    SendByteToPort(CMOSDataPort, PreviousValueOfRegisterB | 0x40);
    //InstallIRQHandler(7,CMOSHandler);
    InstallIRQHandler(8,CMOSHandler);
    ReadRTC();
    SendByteToPort(0x70,0x0C);// select register C
    ReadByteFromPort(0x71);	// just throw away contents
    //PrintString(GetDateTime());
}
void CMOSHandler(struct regs* Registers)
{
  PrintString("CMOS Interrupt Recieved");
}
