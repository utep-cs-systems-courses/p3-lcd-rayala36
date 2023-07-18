	.arch msp430g2553
	.p2align 1,0
	
	.data

secondCount:	.word 0
	
	.text


	global siren
	extern P1OUT
	extern buzzer_set_period

siren:
	add #1, &secondCount
	cmp #25, &secondCount
	jnc p1

	cmp #50, &secondCount
	jz siren

	bis #64, &P1OUT
	and #~0, &P1OUT
	pop r0
	mov eax, #1500
	push eax
	call buzzer_set_period
	add esp, #4
	jmp siren
	
p1:
	bis #64, &P1OUT
	and #~0, &P1OUT
	pop r0
	mov eax, #1000
	push eax
	call buzzer_set_period
	add esp, #4
	jmp siren
