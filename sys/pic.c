#include <sys/sbunix.h>
#define PIC1 0x20
#define PIC2 0xA0

#define ICW1 0x11
#define ICW4 0x01

/* init_pics()
 * init the PICs and remap them
 */
static void outb(int port, uint8_t data)
{
__asm __volatile("outb %0,%w1" : : "a" (data), "d" (port));
}
void init_pics(int pic1, int pic2)
{
	/* send ICW1 */
	outb(PIC1, ICW1);
	outb(PIC2, ICW1);

	/* send ICW2 */
	outb(PIC1 + 1, pic1);	/* remap */
	outb(PIC2 + 1, pic2);	/*  pics */

	/* send ICW3 */
	outb(PIC1 + 1, 4);	/* IRQ2 -> connection to slave */
	outb(PIC2 + 1, 2);

	/* send ICW4 */
	outb(PIC1 + 1, ICW4);
	outb(PIC2 + 1, ICW4);

	/* disable all IRQs */
//	outb(PIC1 + 1, 0xFF);
	outb(0x21, 0x00);
	outb(0xA1, 0x00);
}
