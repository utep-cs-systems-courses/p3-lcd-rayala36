	.arch msp430g2553
	.p2align 1,0

	.text
	.global siren
	.extern P1OUT
	.extern buzzer_set_period

siren:
	sub #1, r1
	mov #0, 0(r1)
top:
	cmp #25, 0(r1)
           jc p2
	bis #64, &P1OUT
	and #~1, &P1OUT
	mov #1500, r12
	call #buzzer_set_period
	add #1, 0(r1)
	jmp top

p2:
	cmp #50, 0(r1)
	   jc siren
	bis #1, &P1OUT
	and #~64, &P1OUT
	mov #1000, r12
	call #buzzer_set_period
	add #1, 0(r1)
	jmp p2

	pop r0
