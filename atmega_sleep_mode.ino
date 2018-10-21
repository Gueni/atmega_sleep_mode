#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>
volatile int f_wdt=1;
volatile int tempo=0;

/******************************************Watchdog Interrupt Service. This is executed when watchdog timed out.***********************/

ISR(WDT_vect)
{ 
    tempo++;
    //Serial.println(tempo);
}
/**************************************************Enters the arduino into sleep mode.***************************************************/
void enterSleep(void)
{
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
  sleep_enable();                                             
  
  /* Now enter sleep mode. */
  //Serial.println("Action1");
  sleep_mode();
  //Serial.println("Action2");
  /* The program will continue from here after the WDT timeout*/
  
 
  sleep_disable(); /* First thing to do is disable sleep. */
 
  
  /* Re-enable the peripherals. */
  power_all_enable();
  
  
}

/***********************************Setup for the serial comms and the Watch dog timeout.***************************************************/
void setup()
{
  Serial.begin(9600);
  Serial.println("Initialising...");
  delay(100); //Allow for serial print to complete.

 

  /*** Setup the WDT ***/
  
  /* Clear the reset flag. */
  MCUSR &= ~(1<<WDRF);
  
  /* In order to change WDE or the prescaler, we need to
   * set WDCE (This will allow updates for 4 clock cycles).
   */
  WDTCSR |= (1<<WDCE) | (1<<WDE);

  /* set new watchdog timeout prescaler value */
  //WDTCSR = 1<<WDP0 | 1<<WDP3; /* 8.0 seconds */
  WDTCSR = ( 1 << WDP3) | (0<< WDP2) | ( 0 << WDP1) | ( 1 << WDP0);/*2seconde*/
  /* Enable the WD interrupt (note no reset). */
  WDTCSR |= _BV(WDIE);
  
  Serial.println("Initialisation complete.");
  delay(100); //Allow for serial print to complete.
}



/***************************************************
 *  Name:        enterSleep
 *
 *  Returns:     Nothing.
 *
 *  Parameters:  None.
 *
 *  Description: Main application loop.
 *
 ***************************************************/
void loop()
{
enterSleep();
analogWrite (6,50);
delay(2000);

}
