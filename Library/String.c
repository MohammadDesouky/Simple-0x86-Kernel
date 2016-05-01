#include <String.h>


int StringLength(char s[])
{
int i=0;
   for(;;i++)
   {
    if(s[i]=='\0')return i;
   }
}

char SearchString(char * SearchThis,char * ForThis)
{
   unsigned i=0;
   for(;;i++)
	{
         if(SearchThis[i]!='\0')
	  {
	    if(SearchThis[i]== ForThis[0])
           {
		         unsigned j=0;
             int Length=StringLength(ForThis);
             for(;j<Length;j++)
             {
               if(SearchThis[i+j]!=ForThis[j])break;
               if(j==Length-1)return 1;//found Successs
             }
           }
	  }
         else
          return 0;//not found
	}
}
void ReverseString(char s[])
{
    int i, j;
    char c;

    for (i = 0, j = StringLength(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
char IntOut[11];//Max int 2 *** *** *** =10 digits and one for '\0' character ^_^
char * IntToAscii(int n)
{
  unsigned index=0;
  for(;index<11;index++)IntOut[index]=0;
  int i, sign;

    if ((sign = n) < 0)  /* record sign */
        n = -n;          /* make n positive */
    i = 0;
    do {       /* generate digits in reverse order */
        IntOut[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    if (sign < 0)
        IntOut[i++] = '-';
    IntOut[i] = '\0';
   ReverseString(IntOut);
   return IntOut;
}

char isChar(char a)
{
  return (char)((a >= 'a' && a<='z')||(a >= 'A' && a<='Z'));
}
char isNumber(char a)
{
  return (char)((a >= '0' && a<='9'));
}
