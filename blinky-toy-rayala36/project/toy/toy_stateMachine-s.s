	.arch msp430g2553
	.p2align 1,0

	.data

p1val:	.byte 0
p2val:	.byte 0
B1:	.word 0
B2:	.word 0
B3:	.word 0
B4:	.word 0
B5:	.word 0
	
	.text

	global toy_stateMachine
	extern P1IN, P2IN, TOPSW, TOPS1, TOPS2, TOPS3, TOPS4, P1IES, P1OUT, SW1

toy_stateMachine:

	mov &P1IN, &p1val
	mov &P2IN, &p2val

	mov &p2val, &B1
	and &TOPS1, &B1
	cmp #1, &B1
	jz p1

	mov &p2val, &B2
	and &TOPS2, &B2
	cmp #1, &B2
	jz p2

	mov &p2val, &B3
	and &TOPS3, &B3
	cmp #1, &B3
	jz p3
	
	mov &p2val, &B4
	and &TOPS4, &B4
	cmp #1, &B4
	jz p4

	mov &p1val, &B5
	and &SW1, &B5
	cmp #1, &B5
	jz p5

	and #~64, &P1OUT
	and #~0, &P1OUT
	pop r0
	mov eax, #0
	push eax
	call buzzer_set_period
	add esp, #4
	jmp toy_stateMachine


p1:
	call greenTimeAdvStateMachines
	and #~64, &P1OUT
p2:
	call redTimeAdvStateMachines
	and #~0, &P1OUT
p3:
	call song
p4:
	call song2
p5:
	call siren
