#include <System.h>
#include <Memory.h>
#include <IO.h>
#include <VGA.h>
#include <String.h>

#define WHITE_TXT 0x0F //ya3ni background soda w el font color abyad (momken t3'yar feha w tshof)

//bttba3 7arf wa7ed f el mkana el mab3ot ( el 7arf ASCII (one byte), tany parameter Position unsigned 3ashan el signed byb2a feh bit bta3 el sign msh haynfa3 f el indexing  )
 unsigned int CurrentCursor=0;

char *vidmem = (char *) 0xB8000;

int MinPositionToDelete=0;



void PrintStringAndInt(char * s,int x)
{

  char *X=(char *)IntToAscii(x);
  int SLength=StringLength(s);
  int XLength=StringLength(X);
  int StringLength=SLength+XLength+1;
  char * string="";
  CopyMemory((char *)s,(char *)string,SLength);
  CopyMemory((char *)X,(char *)((unsigned)(string))+SLength,XLength);
  string[StringLength-1]='\0';
  PrintString(string);
}

void PrintS(const char *a,unsigned int Position,char Attribute)
{
  unsigned int i=0;
  while(a[i]!='\0')
  {
    if(a[i]=='\n')
    {
       CursorToNextLine();
       Position=CurrentCursor;
       i++;
       continue;
    }
   else
    {
      PrintChar(a[i],Position,Attribute);
    }
    Position++;
    i++;
  }
     ScrollScreen();
}
void PrintStringPosition(const char *a,unsigned int Position)
{
  PrintS(a,Position,0x0F);
}


void PrintString(const char *a)
{
    PrintStringPosition(a,CurrentCursor);//==0?0:CurrentCursor+1);
}
void PrintStringError(char *s)
{
  PrintS(s,CurrentCursor,0x04);
}
void PrintCursorPosition()
{
	unsigned int x=CurrentCursor;
	char * s =(char *)IntToAscii((int)CurrentCursor);
	CurrentCursor=80;
	PrintStringPosition(s,CurrentCursor);
	CurrentCursor=x;
}

void PrintoneNewLine(const char *a)
{
   CurrentCursor=CurrentCursor/80+80-CurrentCursor%80;
   PrintStringPosition(a,CurrentCursor);
}
void ClearScreen()
{
// d btmsa7 el screen kolaha w btlawebnha pink ^_^ law 3ayz tgarab

    CurrentCursor=0;
    unsigned int i=0;
    while( i <= (80 *50))
    {
        vidmem[i] = ' ';
	 vidmem[i+1] =WHITE_TXT;
	 i+=2;
    }
   //char* l1="===========In the name of ALLAH, the Most Gracious, the Most Merciful===========\0";
   PrintS("===========\0",CurrentCursor,0x0F);
   PrintS("In the name of ALLAH, the Most Gracious, the Most Merciful",CurrentCursor,0x02);PrintS("===========\0",CurrentCursor,0x0F);
   char* l3="Graduation Project (Simple OS Kernel)...........................................\0";
   char* l2="Faculty Of Science, Cairo University............................................\0";
   char* l4=">Dr.Nour AlHouda................................................................\0";
   char* l5="  -Ahmed Samir Zakaria (90505)..................................................\0";
   char* l6="  -AbdULAZIZ Mabrouk Ali(80624).................................................\0";
   char* l7="  -Mohammad Desouky (61051).....................................................\0";
   char* l8="================================================================================";
	//"________________________________________________________________________________\0";
  // PrintString(l1);
   PrintString(l2);
   PrintString(l3);
   PrintString(l4);
   PrintString(l5);
   PrintString(l6);
   PrintString(l7);
   PrintString(l8);
}
void MoveCursor()
{

    /* This sends a command to indicies 14 and 15 in the
    *  CRT Control Register of the VGA controller. These
    *  are the high and low bytes of the index that show
    *  where the hardware cursor is to be 'blinking'. To
    *  learn more, you should look up some VGA specific
    *  programming documents. A great start to graphics:
    *  http://www.brackeen.com/home/vga */

    SendByteToPort(0x3D4, 14);
    SendByteToPort(0x3D5, (CurrentCursor) >> 8);
    SendByteToPort(0x3D4, 15);
    SendByteToPort(0x3D5, (CurrentCursor));
}
void OutPutChar(char a)
{
  unsigned int Position=(CurrentCursor)*2;
  vidmem[Position]=a;
  vidmem[Position+1]=WHITE_TXT;
  CurrentCursor++;
  ScrollScreen();
}

void PrintChar(char a,unsigned int Position,char Attributes)
{
     Position*=2;
     vidmem[Position]=a;
     vidmem[Position+1]=Attributes;
     CurrentCursor=Position/2;
     CurrentCursor++;
     MoveCursor();
}
void CursorToNextLine()
{
	CurrentCursor+=80-(CurrentCursor%80);
	ScrollScreen();

}
int HeaderPreservedLength= 80*8;
void  DeleteChar()
{
   if(CurrentCursor > MinPositionToDelete && CurrentCursor > HeaderPreservedLength)
   {
       CurrentCursor=CurrentCursor-1>=0?CurrentCursor-1:0;
    	 unsigned int Position=CurrentCursor*2;
    	 vidmem[Position]=' ';
    	 vidmem[Position+1]=WHITE_TXT;
    	 MoveCursor();
   }
}
void PrintEmptyLine(int LineNumber)
{
  if(LineNumber<1||LineNumber>25)return;
   int i=(LineNumber-1)*160;
   int j=0;
  for(;j<160;j++)
    {
       vidmem[(unsigned int)i+j]=' ';
       vidmem[(unsigned int)i+j+1]=0xff;
    }
}
void ScrollScreen()
{
	//check for the Cursor if it exceed the max line do the work
	unsigned ScrollStartLine=9;

	if(CurrentCursor>=80*25)
	{
           char * ScrollSPosition=vidmem+ScrollStartLine*80*2;

  	    CopyMemory(ScrollSPosition, ScrollSPosition-80*2 ,80*(25-ScrollStartLine)*2);

	    MemorySetToValueByte(vidmem+80*24*2, 0 ,80*2);
	    CurrentCursor=80*24;//+CurrentCursor%80;
	}
	MoveCursor();

}
