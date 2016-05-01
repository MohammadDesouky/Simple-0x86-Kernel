/* bkerndev - Bran's Kernel Development Tutorial
*  By:   Brandon F. (friesenb@gmail.com)
*  Desc: Timer driver
*
*  Notes: No warranty expressed or implied. Use at own risk. */
#include <System.h>

/* This will keep track of how many ticks that the system
*  has been running for */
int timer_ticks = 0;

/* Handles the timer. In this case, it's very simple: We
*  increment the 'timer_ticks' variable every time the
*  timer fires. By default, the timer fires 18.222 times
*  per second. Why 18.222Hz? Some engineer at IBM must've
*  been smoking something funky */

int Seconds=0;
char Stopped=0;
void timer_handler(struct regs *r)
{
  //if(Stopped)return;
    /* Increment our 'tick count' */
  //  timer_ticks++;

    /* Every 18 clocks (approximately 1 second), we will
    *  display a message on the screen */

    //char s[10];
/*    if (timer_ticks % 2== 0 )
    {
	     Seconds++;
       PrintStringAndInt("\nOne second has passed:\0",Seconds);
    }*/
}
void Stop()
{
  Stopped=1;
}
/* This will continuously loop until the given time has
*  been reached */
void timer_wait(int ticks)
{
    unsigned long eticks;

    eticks = timer_ticks + ticks;
    while(timer_ticks < eticks);
}

void InstallTimer()
{
    InstallIRQHandler(0, timer_handler);
}
