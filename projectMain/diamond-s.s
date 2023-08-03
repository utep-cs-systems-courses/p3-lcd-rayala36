	.arch msp430g2553
	.p2align 1,0
	.text

	.global drawDiamond
	.extern drawPixel

drawDiamond:
	sub #10, r1
	mov r12, 0(r1)		;cCol
	mov r13, 2(r1)		;cRow
	mov r14, 4(r1)		;size
	mov r15, 6(r1)		;color
	mov #0, 8(r1)		;c = 0
	mov #0, 10(r1)		;r = 0
	mov #0, 12(r1)		;j = 0 for incrementer for left half
	mov #0, 14(r1)		;k = 0 for incrementer for right half

leftHalf:			;As in the left half of the diamond that is being drawn
	cmp 4(r1), 12(r1)
	   jc rightHalf

	mov 0(r1), r12
	add 8(r1), r12
	mov 2(r1), r13
	add 10(r1), r13
	mov 6(r1), r14
	call #drawPixel		;drawPixel(cCol+c, cRow+r, color)

	mov 0(r1), r12
	add 8(r1), r12
	mov 2(r1), r13
	sub 10(r1), r13
	mov 6(r1), r14
	call #drawPixel		;drawPixel(cCol+c, cRow-r, color)

	mov 2(r1), 16(r1)
	sub 10(r1), 16(r1)	;upper = cRow-r
	mov 2(r1), 18(r1)
	add 10(r1), 18(r1)	;lower = cRow+r

innerTop:
	cmp 16(r1), 18(r1)
	   jnc done
	mov 0(r1), r12
	add 8(r1), r12
	mov 16(r1), r13
	mov 6(r1), r14
	call #drawPixel		;drawPixel(cCol+c, upper, color)
	add #1, 16(r1)		;upper++
	jmp innerTop
done:
	add #1, 8(r1)		;c+=1
	add #1, 10(r1)		;r+=1
	add #1, 12(r1)		;c++
	jmp leftHalf

	;; Part 2
rightHalf:			;As in the right half of the diamond that is being drawn

	cmp 4(r1), 14(r1)
	   jc done

	mov 0(r1), r12
	add 8(r1), r12
	mov 2(r1), r13
	add 10(r1), r13
	mov 6(r1), r14
	call #drawPixel

	mov 0(r1), r12
	add 8(r1), r12
	mov 2(r1), r13
	sub 10(r1), r13
	mov 6(r1), r14
	call #drawPixel

	mov 2(r1), 16(r1)
	sub 10(r1), 16(r1)	;upper = cRow-r
	mov 2(r1), 18(r1)
	add 10(r1), 18(r1)	;lower = cRow+r

innerTop2:
	cmp 16(r1), 18(r1)
	   jnc done2
	mov 0(r1), r12
	add 8(r1), r12
	mov 16(r1), r13
	mov 6(r1), r14
	call #drawPixel
	add #1, 16(r1)
	jmp innerTop2
done2:
	add #1, 8(r1)		;c+=1
	sub #1, 10(r1)		;r-=1
	add #1, 14(r1)		;k++
	jmp rightHalf
out:
	mov 10(r1), r12
	add #10, r1
pop r0
