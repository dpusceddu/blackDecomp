# Label macros used by the splat-generated assembly (EE GNU assembler 2.10 compatible).
# Every function, data and jump-table label is global so that references resolve through the linker.
.macro glabel label
	.globl \label
\label:
.endm
.macro alabel label
	.globl \label
\label:
.endm
.macro jlabel label
	.globl \label
\label:
.endm
.macro dlabel label
	.globl \label
\label:
.endm
.macro ehlabel label
	.globl \label
\label:
.endm
.macro endlabel label
.endm
.macro enddlabel label
.endm
