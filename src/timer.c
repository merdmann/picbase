/***************************************************************************
 *  $Id: timer.c 259 2011-01-17 18:55:36Z merdmann $
 *
 *  Thu Nov 29 20:55:57 2007
 *  Copyright  2007 Michael Erdmann
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
  * This module handles the tick timer and the auxilary process level
  * timer.
  *
  * The software uses T1 and T2 and the CPP1 register which is operated in
  * compare mode.
  */

#include <pic18fregs.h>

#include "timer.h"

/*
 * Setup T1 Timer. The T1  timer is used as a clock reference for the
 * alarm functionality.
 */
void _os_init_timers( void ) {

	T1CONbits.T1OSCEN  = 0;		/* oscillator disabled */
	T1CONbits.TMR1CS   = 0;		/* timer 1 counter input FOSC/4 */

    T1CONbits.T1CKPS0  = 1;		/* prescaler: 1/8 */
    T1CONbits.T1CKPS1  = 1;

    T1CONbits.T1SYNC   = 0;		/* do not sync */

	T1CONbits.RD16     = 1;		/* 16 bit values */

	TMR1H = 1;
	TMR1L = 0;

	IPR1bits.TMR1IP = 1;
    PIE1bits.TMR1IE = 1;

    T1CONbits.TMR1ON = 1;

	__asm
	BTG _PORTB,6
	__endasm;

}


void _os_timer_tick(void) __interrupt 1 {

	if( PIE1bits.TMR1IE && PIR1bits.TMR1IF ) {
		__asm
		BTG _PORTB,6
		__endasm;

		TMR1H = 1;
		TMR1L = 0;

		PIR1bits.TMR1IF = 0;
	}
}



