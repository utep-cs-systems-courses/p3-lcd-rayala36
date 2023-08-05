	.data			;Var's are put in R/W RAM memory
	.arch msp430g2553
	.p2align 1,0
	
JT:
	.word default
	.word case1
	.word case2
	.word case3
	.word case4

	.text			;ROM

	.global scoreJT
	.extern buzzer_set_period
	
scoreJT:	
	cmp #1, r12
           jz case1

	cmp #2, r12
	   jz case2
	
	cmp #3, r12
	   jz case3
	
	cmp #4, r12
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
	pop r0
