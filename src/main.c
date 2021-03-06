/***************************************************************************
 *  $Id: output.c 267 2011-02-05 18:36:32Z merdmann $
 *
 *  Fri Nov 23 06:55:51 2007
 *  Copyright  2007  Michael Erdmann
 *  Email: michael.erdmann@snafu.de
 ****************************************************************************/

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

/*
 * This module contains code which is specific for the pt24er1 board of
 * modtronix which provides an 8 bit shift register  with  connected
 * LEDS.
 */

#pragma config XINST = OFF


#include <pic18fregs.h>

#include "timer.h"
#include "proc.h"
#include "output.h"


int main() {
	// initialize display
	_os_init_output();
    _os_init_timers();
    _os_init_proc_timer();

    LED_On(LED_PWR);
	LED_On(LD4_B);

    /* Initialize oscillators */
    OSCCONbits.IDLEN=1;                             // enter idle on sleep

    OSCCONbits.IRCF2=1;                             // INTOSC drives clock
    OSCCONbits.IRCF1=1;
    OSCCONbits.IRCF0=1;
    OSCCONbits.SCS1=0;                              // primary oscillator
    OSCCONbits.SCS0=0;


    INTCON = 0;
    RCONbits.IPEN = 1;                              // interrupt priority active

    INTCONbits.GIEL = 1;
    INTCONbits.GIEH = 1;

	LED_On(LD4_A);

	while(1) 
	   LED_Update();

}  
