
main.elf:     file format elf32-avr


Disassembly of section .text:

00000000 <__vectors>:
   0:	09 c0       	rjmp	.+18     	; 0x14 <__ctors_end>
   2:	21 c0       	rjmp	.+66     	; 0x46 <__bad_interrupt>
   4:	20 c0       	rjmp	.+64     	; 0x46 <__bad_interrupt>
   6:	1f c0       	rjmp	.+62     	; 0x46 <__bad_interrupt>
   8:	1e c0       	rjmp	.+60     	; 0x46 <__bad_interrupt>
   a:	1d c0       	rjmp	.+58     	; 0x46 <__bad_interrupt>
   c:	7f c0       	rjmp	.+254    	; 0x10c <__vector_6>
   e:	1b c0       	rjmp	.+54     	; 0x46 <__bad_interrupt>
  10:	1a c0       	rjmp	.+52     	; 0x46 <__bad_interrupt>
  12:	19 c0       	rjmp	.+50     	; 0x46 <__bad_interrupt>

00000014 <__ctors_end>:
  14:	11 24       	eor	r1, r1
  16:	1f be       	out	0x3f, r1	; 63
  18:	cf e9       	ldi	r28, 0x9F	; 159
  1a:	cd bf       	out	0x3d, r28	; 61

0000001c <__do_copy_data>:
  1c:	10 e0       	ldi	r17, 0x00	; 0
  1e:	a0 e6       	ldi	r26, 0x60	; 96
  20:	b0 e0       	ldi	r27, 0x00	; 0
  22:	ea ef       	ldi	r30, 0xFA	; 250
  24:	f1 e0       	ldi	r31, 0x01	; 1
  26:	02 c0       	rjmp	.+4      	; 0x2c <.do_copy_data_start>

00000028 <.do_copy_data_loop>:
  28:	05 90       	lpm	r0, Z+
  2a:	0d 92       	st	X+, r0

0000002c <.do_copy_data_start>:
  2c:	ac 36       	cpi	r26, 0x6C	; 108
  2e:	b1 07       	cpc	r27, r17
  30:	d9 f7       	brne	.-10     	; 0x28 <.do_copy_data_loop>

00000032 <__do_clear_bss>:
  32:	10 e0       	ldi	r17, 0x00	; 0
  34:	ac e6       	ldi	r26, 0x6C	; 108
  36:	b0 e0       	ldi	r27, 0x00	; 0
  38:	01 c0       	rjmp	.+2      	; 0x3c <.do_clear_bss_start>

0000003a <.do_clear_bss_loop>:
  3a:	1d 92       	st	X+, r1

0000003c <.do_clear_bss_start>:
  3c:	a0 38       	cpi	r26, 0x80	; 128
  3e:	b1 07       	cpc	r27, r17
  40:	e1 f7       	brne	.-8      	; 0x3a <.do_clear_bss_loop>
  42:	89 d0       	rcall	.+274    	; 0x156 <main>
  44:	d8 c0       	rjmp	.+432    	; 0x1f6 <_exit>

00000046 <__bad_interrupt>:
  46:	dc cf       	rjmp	.-72     	; 0x0 <__vectors>

00000048 <signal_tick>:
  48:	ff 92       	push	r15
  4a:	0f 93       	push	r16
  4c:	1f 93       	push	r17
  4e:	cf 93       	push	r28
  50:	df 93       	push	r29
  52:	f8 2e       	mov	r15, r24
  54:	80 91 6c 00 	lds	r24, 0x006C
  58:	0f 2d       	mov	r16, r15
  5a:	08 1b       	sub	r16, r24
  5c:	f0 92 6c 00 	sts	0x006C, r15
  60:	a0 e7       	ldi	r26, 0x70	; 112
  62:	b0 e0       	ldi	r27, 0x00	; 0
  64:	7f ef       	ldi	r23, 0xFF	; 255
  66:	60 e0       	ldi	r22, 0x00	; 0
  68:	10 e0       	ldi	r17, 0x00	; 0
  6a:	40 e0       	ldi	r20, 0x00	; 0
  6c:	50 e0       	ldi	r21, 0x00	; 0
  6e:	c1 e0       	ldi	r28, 0x01	; 1
  70:	d0 e0       	ldi	r29, 0x00	; 0
  72:	24 2f       	mov	r18, r20
  74:	ed 91       	ld	r30, X+
  76:	fc 91       	ld	r31, X
  78:	11 97       	sbiw	r26, 0x01	; 1
  7a:	30 97       	sbiw	r30, 0x00	; 0
  7c:	d1 f0       	breq	.+52     	; 0xb2 <__stack+0x13>
  7e:	82 81       	ldd	r24, Z+2	; 0x02
  80:	90 2f       	mov	r25, r16
  82:	98 0f       	add	r25, r24
  84:	98 17       	cp	r25, r24
  86:	40 f1       	brcs	.+80     	; 0xd8 <__stack+0x39>
  88:	81 81       	ldd	r24, Z+1	; 0x01
  8a:	98 17       	cp	r25, r24
  8c:	28 f5       	brcc	.+74     	; 0xd8 <__stack+0x39>
  8e:	29 2f       	mov	r18, r25
  90:	30 e0       	ldi	r19, 0x00	; 0
  92:	89 2f       	mov	r24, r25
  94:	82 83       	std	Z+2, r24	; 0x02
  96:	ed 91       	ld	r30, X+
  98:	fc 91       	ld	r31, X
  9a:	11 97       	sbiw	r26, 0x01	; 1
  9c:	81 81       	ldd	r24, Z+1	; 0x01
  9e:	90 e0       	ldi	r25, 0x00	; 0
  a0:	82 1b       	sub	r24, r18
  a2:	93 0b       	sbc	r25, r19
  a4:	27 2f       	mov	r18, r23
  a6:	30 e0       	ldi	r19, 0x00	; 0
  a8:	28 17       	cp	r18, r24
  aa:	39 07       	cpc	r19, r25
  ac:	0c f4       	brge	.+2      	; 0xb0 <__stack+0x11>
  ae:	c9 01       	movw	r24, r18
  b0:	78 2f       	mov	r23, r24
  b2:	4f 5f       	subi	r20, 0xFF	; 255
  b4:	5f 4f       	sbci	r21, 0xFF	; 255
  b6:	12 96       	adiw	r26, 0x02	; 2
  b8:	48 30       	cpi	r20, 0x08	; 8
  ba:	51 05       	cpc	r21, r1
  bc:	d1 f6       	brne	.-76     	; 0x72 <signal_tick+0x2a>
  be:	88 b3       	in	r24, 0x18	; 24
  c0:	60 95       	com	r22
  c2:	68 23       	and	r22, r24
  c4:	61 2b       	or	r22, r17
  c6:	68 bb       	out	0x18, r22	; 24
  c8:	87 2f       	mov	r24, r23
  ca:	8f 0d       	add	r24, r15
  cc:	df 91       	pop	r29
  ce:	cf 91       	pop	r28
  d0:	1f 91       	pop	r17
  d2:	0f 91       	pop	r16
  d4:	ff 90       	pop	r15
  d6:	08 95       	ret
  d8:	04 80       	ldd	r0, Z+4	; 0x04
  da:	f5 81       	ldd	r31, Z+5	; 0x05
  dc:	e0 2d       	mov	r30, r0
  de:	11 96       	adiw	r26, 0x01	; 1
  e0:	fc 93       	st	X, r31
  e2:	ee 93       	st	-X, r30
  e4:	ce 01       	movw	r24, r28
  e6:	02 c0       	rjmp	.+4      	; 0xec <__stack+0x4d>
  e8:	88 0f       	add	r24, r24
  ea:	99 1f       	adc	r25, r25
  ec:	2a 95       	dec	r18
  ee:	e2 f7       	brpl	.-8      	; 0xe8 <__stack+0x49>
  f0:	98 2f       	mov	r25, r24
  f2:	80 81       	ld	r24, Z
  f4:	81 11       	cpse	r24, r1
  f6:	19 2b       	or	r17, r25
  f8:	69 2b       	or	r22, r25
  fa:	83 81       	ldd	r24, Z+3	; 0x03
  fc:	81 83       	std	Z+1, r24	; 0x01
  fe:	ed 91       	ld	r30, X+
 100:	fc 91       	ld	r31, X
 102:	11 97       	sbiw	r26, 0x01	; 1
 104:	80 e0       	ldi	r24, 0x00	; 0
 106:	20 e0       	ldi	r18, 0x00	; 0
 108:	30 e0       	ldi	r19, 0x00	; 0
 10a:	c4 cf       	rjmp	.-120    	; 0x94 <signal_tick+0x4c>

0000010c <__vector_6>:
 10c:	1f 92       	push	r1
 10e:	0f 92       	push	r0
 110:	0f b6       	in	r0, 0x3f	; 63
 112:	0f 92       	push	r0
 114:	11 24       	eor	r1, r1
 116:	2f 93       	push	r18
 118:	3f 93       	push	r19
 11a:	4f 93       	push	r20
 11c:	5f 93       	push	r21
 11e:	6f 93       	push	r22
 120:	7f 93       	push	r23
 122:	8f 93       	push	r24
 124:	9f 93       	push	r25
 126:	af 93       	push	r26
 128:	bf 93       	push	r27
 12a:	ef 93       	push	r30
 12c:	ff 93       	push	r31
 12e:	86 b7       	in	r24, 0x36	; 54
 130:	8b df       	rcall	.-234    	; 0x48 <signal_tick>
 132:	86 bf       	out	0x36, r24	; 54
 134:	ff 91       	pop	r31
 136:	ef 91       	pop	r30
 138:	bf 91       	pop	r27
 13a:	af 91       	pop	r26
 13c:	9f 91       	pop	r25
 13e:	8f 91       	pop	r24
 140:	7f 91       	pop	r23
 142:	6f 91       	pop	r22
 144:	5f 91       	pop	r21
 146:	4f 91       	pop	r20
 148:	3f 91       	pop	r19
 14a:	2f 91       	pop	r18
 14c:	0f 90       	pop	r0
 14e:	0f be       	out	0x3f, r0	; 63
 150:	0f 90       	pop	r0
 152:	1f 90       	pop	r1
 154:	18 95       	reti

00000156 <main>:
 156:	df 93       	push	r29
 158:	cf 93       	push	r28
 15a:	00 d0       	rcall	.+0      	; 0x15c <main+0x6>
 15c:	00 d0       	rcall	.+0      	; 0x15e <main+0x8>
 15e:	cd b7       	in	r28, 0x3d	; 61
 160:	de b7       	in	r29, 0x3e	; 62
 162:	9f ef       	ldi	r25, 0xFF	; 255
 164:	97 bb       	out	0x17, r25	; 23
 166:	83 e0       	ldi	r24, 0x03	; 3
 168:	83 bf       	out	0x33, r24	; 51
 16a:	84 e0       	ldi	r24, 0x04	; 4
 16c:	89 bf       	out	0x39, r24	; 57
 16e:	96 bf       	out	0x36, r25	; 54
 170:	80 e6       	ldi	r24, 0x60	; 96
 172:	90 e0       	ldi	r25, 0x00	; 0
 174:	90 93 6b 00 	sts	0x006B, r25
 178:	80 93 6a 00 	sts	0x006A, r24
 17c:	86 e6       	ldi	r24, 0x66	; 102
 17e:	90 e0       	ldi	r25, 0x00	; 0
 180:	90 93 65 00 	sts	0x0065, r25
 184:	80 93 64 00 	sts	0x0064, r24
 188:	90 93 71 00 	sts	0x0071, r25
 18c:	80 93 70 00 	sts	0x0070, r24
 190:	80 e0       	ldi	r24, 0x00	; 0
 192:	5a df       	rcall	.-332    	; 0x48 <signal_tick>
 194:	78 94       	sei
 196:	2e e1       	ldi	r18, 0x1E	; 30
 198:	33 e0       	ldi	r19, 0x03	; 3
 19a:	19 82       	std	Y+1, r1	; 0x01
 19c:	1a 82       	std	Y+2, r1	; 0x02
 19e:	1b 82       	std	Y+3, r1	; 0x03
 1a0:	1c 82       	std	Y+4, r1	; 0x04
 1a2:	89 81       	ldd	r24, Y+1	; 0x01
 1a4:	9a 81       	ldd	r25, Y+2	; 0x02
 1a6:	ab 81       	ldd	r26, Y+3	; 0x03
 1a8:	bc 81       	ldd	r27, Y+4	; 0x04
 1aa:	80 51       	subi	r24, 0x10	; 16
 1ac:	97 42       	sbci	r25, 0x27	; 39
 1ae:	a0 40       	sbci	r26, 0x00	; 0
 1b0:	b0 40       	sbci	r27, 0x00	; 0
 1b2:	a0 f4       	brcc	.+40     	; 0x1dc <main+0x86>
 1b4:	89 81       	ldd	r24, Y+1	; 0x01
 1b6:	9a 81       	ldd	r25, Y+2	; 0x02
 1b8:	ab 81       	ldd	r26, Y+3	; 0x03
 1ba:	bc 81       	ldd	r27, Y+4	; 0x04
 1bc:	01 96       	adiw	r24, 0x01	; 1
 1be:	a1 1d       	adc	r26, r1
 1c0:	b1 1d       	adc	r27, r1
 1c2:	89 83       	std	Y+1, r24	; 0x01
 1c4:	9a 83       	std	Y+2, r25	; 0x02
 1c6:	ab 83       	std	Y+3, r26	; 0x03
 1c8:	bc 83       	std	Y+4, r27	; 0x04
 1ca:	89 81       	ldd	r24, Y+1	; 0x01
 1cc:	9a 81       	ldd	r25, Y+2	; 0x02
 1ce:	ab 81       	ldd	r26, Y+3	; 0x03
 1d0:	bc 81       	ldd	r27, Y+4	; 0x04
 1d2:	80 51       	subi	r24, 0x10	; 16
 1d4:	97 42       	sbci	r25, 0x27	; 39
 1d6:	a0 40       	sbci	r26, 0x00	; 0
 1d8:	b0 40       	sbci	r27, 0x00	; 0
 1da:	60 f3       	brcs	.-40     	; 0x1b4 <main+0x5e>
 1dc:	82 2f       	mov	r24, r18
 1de:	84 51       	subi	r24, 0x14	; 20
 1e0:	89 3c       	cpi	r24, 0xC9	; 201
 1e2:	08 f0       	brcs	.+2      	; 0x1e6 <main+0x90>
 1e4:	31 95       	neg	r19
 1e6:	23 0f       	add	r18, r19
 1e8:	20 93 69 00 	sts	0x0069, r18
 1ec:	82 2f       	mov	r24, r18
 1ee:	80 95       	com	r24
 1f0:	80 93 63 00 	sts	0x0063, r24
 1f4:	d2 cf       	rjmp	.-92     	; 0x19a <main+0x44>

000001f6 <_exit>:
 1f6:	f8 94       	cli

000001f8 <__stop_program>:
 1f8:	ff cf       	rjmp	.-2      	; 0x1f8 <__stop_program>
