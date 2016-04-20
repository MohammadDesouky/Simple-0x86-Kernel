#define WHITE_TXT 0x0F //ya3ni background soda w el font color abyad (momken t3'yar feha w tshof)

// tb3an f el C 3ashan tsta5dem function 2bl matkteb el definition 
//lazem t3arf 3am el compiler b l header

void PrintChar(char a,unsigned int b);
void PrintString(char *a);
void ClearScreen();

void KernelMain() //d el function elly nadenaha mn file el assembly bta3 el entry point 
{
	ClearScreen( );
	PrintString("Bsm ALLAH!\nWe start writing the operating system\nThanks to ALLAH\0");

}


//bttba3 7arf wa7ed f el mkana el mab3ot ( el 7arf ASCII (one byte), tany parameter Position unsigned 3ashan el signed byb2a feh bit bta3 el sign msh haynfa3 f el indexing  )

void PrintChar(char a,unsigned int Position)
{
   char *vidmem = (char *) 0xb8000;
	  Position*=2;
	  vidmem[Position+1]=a;
	  vidmem[Position+2]=WHITE_TXT;
	
}
void PrintString(char *a)
{
 	unsigned int i=1;
	unsigned int index=0;

       while(a[i]!='\0')
	{
	  if(a[i]=='\n')
	  {
	     index+=80-index%80-1;//el satr feh 80 7arf w kol 7arf bytsagel f 2 byte 
	  }
	 else
	  {
	    PrintChar(a[i],index);    
	  }
	  index++;
	  i++;
	}
}
void ClearScreen() 
{
// d btmsa7 el screen kolaha w btlawebnha pink ^_^ law 3ayz tgarab
    char *vidmem = (char *) 0xb8000;
    unsigned int i=1;
    while( i <= (80 *50))
    {
        vidmem[i] = ' ';
	 vidmem[i+1] =0x00;
	i+=2;
        
    }

    /*unsigned int i=0;
    while( i <= (80 *25))
    {
       PrintChar(' ',++i);       
    }*/


}


