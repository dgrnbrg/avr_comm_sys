/*
	ledramp.c
	
	Copyright 2008, 2009 Michel Pollet <buserror@gmail.com>

 	This file is part of simavr.

	simavr is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	simavr is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with simavr.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdio.h>
#include <libgen.h>
#include <pthread.h>

#include "sim_avr.h"
#include "avr_timer.h"
#include "avr_ioport.h"
#include "sim_elf.h"
#include "sim_gdb.h"
#include "sim_vcd_file.h"

avr_t * avr = NULL;
avr_vcd_t vcd_file;

/*
 * called when the AVR change any of the pins on port B
 * so lets update our buffer
 */
void pin_changed_hook(struct avr_irq_t * irq, uint32_t value, void * param)
{
	int pin_state = (pin_state & ~(1 << irq->irq)) | (value << irq->irq);
}

int main(int argc, char *argv[])
{
	elf_firmware_t f;
	const char * fname =  "atmega48_comms.axf";
	char path[256];

	sprintf(path, "%s/%s", dirname(argv[0]), fname);
	printf("Firmware pathname is %s\n", path);
	elf_read_firmware(fname, &f);

	printf("firmware %s f=%d mmcu=%s\n", fname, (int)f.frequency, f.mmcu);

	avr = avr_make_mcu_by_name(f.mmcu);
	if (!avr) {
		fprintf(stderr, "%s: AVR '%s' now known\n", argv[0], f.mmcu);
		exit(1);
	}
	avr_init(avr);
	avr_load_firmware(avr, &f);

#if 0
	// "connect" the output irw of the button to the port pin of the AVR
	avr_connect_irq(
		button.irq + IRQ_BUTTON_OUT,
		avr_io_getirq(avr, AVR_IOCTL_IOPORT_GETIRQ('C'), 0));

	// connect all the pins on port B to our callback
	for (int i = 0; i < 8; i++)
		avr_irq_register_notify(
			avr_io_getirq(avr, AVR_IOCTL_IOPORT_GETIRQ('B'), i),
			pin_changed_hook, 
			NULL);
#endif

	// even if not setup at startup, activate gdb if crashing
	if (0) {
		avr->gdb_port = 1234;
		avr->state = cpu_Stopped;
		avr_gdb_init(avr);
	}

	/*
	 *	VCD file initialization
	 *	
	 *	This will allow you to create a "wave" file and display it in gtkwave
	 *	Pressing "r" and "s" during the demo will start and stop recording
	 *	the pin changes
	 */
#if 1
	avr_vcd_init(avr, "gtkwave_output.vcd", &vcd_file, 10000 /* usec */);
	avr_vcd_add_signal(&vcd_file, 
		avr_io_getirq(avr, AVR_IOCTL_IOPORT_GETIRQ('B'), IOPORT_IRQ_PIN_ALL), 8 /* bits */ ,
		"portb" );
	avr_vcd_add_signal(&vcd_file, 
		avr_io_getirq(avr, AVR_IOCTL_IOPORT_GETIRQ('C'), IOPORT_IRQ_PIN_ALL), 8 /* bits */ ,
		"portc" );
#endif
#if 0
	avr_vcd_add_signal(&vcd_file, 
		button.irq + IRQ_BUTTON_OUT, 1 /* bits */ ,
		"button" );
#endif

	// 'raise' it, it's a "pullup"
	//avr_raise_irq(button.irq + IRQ_BUTTON_OUT, 1);

	avr_vcd_start(&vcd_file);

	for (int i = 0; i < 1e6; i++) {
		avr_run(avr);
	}
	avr_vcd_stop(&vcd_file);
}
