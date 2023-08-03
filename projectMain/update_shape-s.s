	.arch msp430g2553
	.p2align 1,0
	.text
	
	.global update_shape
	.extern screen_update_ball
	.extern screen_update_defense
	.extern screen_update_offense
update_shape:
	call #screen_update_ball
	call #screen_update_defense
	call #screen_update_offense
	pop r0
