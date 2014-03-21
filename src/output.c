/***************************************************************************
 *  $Id: ior5e.c 262 2011-01-29 19:07:36Z merdmann $
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
 * This module contains code which is specific for the ior5e board of
 * modtronix which allows to control the LEDS and and relay which are
 * installed on board.
 */

#include <pic18fregs.h>
#include "output.h"

#define DS      1
#define SH_CP  (1<<1)
#define ST_CP  (1<<2)
#define NOT_OE (1<<7)    /* C5 is actually wired with C7 on the SBC44ucr1 board */

static unsigned long obits = 0x000000;

void LED_Update() {
    int i;

    LATC &= ~(DS|SH_CP|ST_CP);

    for(i=0; i<24; ++i ) {
	    if( obits & (unsigned long)(1L<<i) )
	        LATC |= DS;

        LATC &= ~SH_CP;
        LATC |=  SH_CP;

        LATC &= ~(DS|SH_CP);
    }
    /* store the result */
    LATC |=  ST_CP;
    LATC &= ~ST_CP;

}

void Set_LEDS(unsigned q) {
    int i,p;

    obits &= 0xff0000;

    /* lower 8 bits */
	p = (q>>4) | ((q<<4) & 0xf0);
    for( i=0; i<8; ++i )
		if( p & (1<<i) )
			obits |= (1<<(i*2));

    /* upper 8 bits */
    q = q >> 8;
	p = (q>>4) | ((q<<4) & 0xf0);
    for( i=0; i<8; ++i )
		if( p & (1<<i) )
			obits |= (1<<(i*2+1));

   LED_Update();
}

void LED_On(unsigned nbr) {
    obits |= (1L<<nbr);

    LED_Update();
}

void LED_Off(unsigned nbr) {
    obits &= ~(1L<<nbr);

    LED_Update();
}

void Relay_On(unsigned nbr) {
    obits |= (1L<<nbr);
}

void Relay_Off(unsigned nbr) {
    obits &= ~(1L<<nbr);
}

void _os_init_output(void){

    TRISC = 0x00;
    LATC = 0;


    // initialize the hardware to drive the LED onboard of the
    // SBC boot loader board.
    PORTB  = 0x00;
    LATB   = 0x00;
    ADCON1 = 0x0f;

    /* 1011 1100 */
    TRISB  = 0xbc;  /* i/o setup as given above */

}


