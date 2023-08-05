	.data			;Var's are put in R/W RAM memory
	.arch msp430g2553
	.p2align 1,0
	
JT:
	.word default
	.word case1
	.word case2
	.word case3
	.word case4

switch:	.word 1

	.text			;ROM

	.global scoreJT
	.extern buzzer_set_period
	
scoreJT:
	mov &switch, r13	;move switch value into r12 to increment in jumptable
	cmp #5, r2xs
	jnc default		;ensures JT does not go beyond number of cases to garbage address
	add r13, r13		;Each entry = 2 bytes; gets offset of bytes into the table
	mov JT(r13), r0

	cmp #1, &switch
           jz case1

	cmp #2, &switch
	   jz case2
	
	cmp #3, &switch
	   jz case3
	
	cmp #4, &swtich
	   jz case4
	
	jnc default

case1:
	mov #900, r12
	call #buzzer_set_period
	jmp break
case2:
	mov #700, r12
	call #buzzer_set_period
	jmp break
case3:
	mov #650, r12
	call #buzzer_set_period
	jmp break
case4:
	mov #600, r12
	call #buzzer_set_period
	jmp break

default:
	jmp break

break:
	mov &switch, r12
	pop r0
