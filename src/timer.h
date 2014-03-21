/***************************************************************************
 *  $Id: timer.h 205 2008-09-22 17:39:04Z merdmann $
 *
 *  Wed Dec  5 07:07:57 2007
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

/** @file
  * Handle timers.
  *
  * \section intro_sec Introduction
  *
  * This module contains all timer related code. The kernel tick timer
  * is implemented by means of timer 2. Since timer 1 and timer 3 are
  * are sharing the same reset the from the CPP module, only timer 1
  * is available for programming.
  *
  * All timers are derived from the CPU clock and a counter which is
  * reset when a certain counter value cnt is reached and some sort
  * of pre and post scaler.
  * \code
  *               t * Fclock * 1000
  *    cnt = --------------------------
  *            prescale * postscale
  *
  *
  *    t = timer value [ms]
  *    Fclock = timer base in Mhz
  *    postscale / prescale factors according your hardware conf.
  * \endcode
  *
  * The value Fclock depends on your oscillator configuration and is
  * normally  Fxtal / 4.
  *
  * \section tick_sec Kernel Tick
  * The generate the kernel tick, timer 2 will be used. The counter allows
  * values from 1..255 with postscale = 8,prescale = 16.
  *
  * \section aux_sec Auxilary Timer
  *
  * The kernel provides an additional timer which utilizes the timer 1. This
  * timer has a resolution of CLOCK_BASE_MS (default 100ms, max. 104 ms).
  *
  * \subsection aux_rest Restrictions
  *
  * Since the timer interrupt causes no rescheduling wakeup, Task_Send
  * have no efect till the next tick interrupt.
  */
#ifndef _TIMER_H
#define _TIMER_H

void _os_init_timers();
void _os_timer_tick() __interrupt 1;


#endif /* _TIMER_H */
