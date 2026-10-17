	.set noreorder
	.set noat
	.text
	.globl external_value
	.globl _start
_start:
	jal	bump
	nop
	jr	$31
	nop
	.data
external_value:
	.word 0x1234
