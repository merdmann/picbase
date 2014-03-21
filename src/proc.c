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


#include <pic18fregs.h>

static unsigned int cnt_tick = 1000;

/**
 * Low prio interrupt handler
 */
void _os_proc_timer(void) __interrupt 2 {
	if( INTCONbits.TMR0IE && INTCONbits.T0IF ) {
		TMR0H = cnt_tick >> 8;
		TMR0L = cnt_tick & 0xff;

		__asm
		BTG _PORTB, 6
		__endasm;

		INTCONbits.T0IF = 0;
	}
}

void _os_init_proc_timer(void) {
#if USE_TICK_TIMER==2
                T2CONbits.TOUTPS0=1;
                T2CONbits.TOUTPS1=1;
                T2CONbits.TOUTPS2=1;
                T2CONbits.TOUTPS3=1;

                T2CONbits.T2CKPS0 = 1;
                T2CONbits.T2CKPS1 = 1;
                PR2 = cnt_tick & 0x00ff;
                tick_aux = cnt_tick >> 8 ;
                tick_aux_counter = tick_aux;

                PIE1bits.TMR2IE = 1;
                IPR1bits.TMR2IP = 0;

                T2CONbits.TMR2ON = 1;
#endif

#if USE_TICK_TIMER==0
                T0CONbits.T08BIT = 0;   // 16 Bit counter
                T0CONbits.T0CS = 0;     // FoSC/4
                T0CONbits.PSA = 0;              // prescaler included

                // 1:2
                T0CONbits.T0PS0 = 0;
                T0CONbits.T0PS1 = 0;
                T0CONbits.T0PS2 = 0;
                T0CONbits.T0CS  = 0;

                TMR0H = cnt_tick >> 8;
                TMR0L = cnt_tick & 0xff;

                INTCONbits.TMR0IE = 1;          // enable TMR0 overflow interrupt
                INTCON2bits.TMR0IP = 0;         // low prio interrupt

                T0CONbits.TMR0ON = 1;
#endif

}


