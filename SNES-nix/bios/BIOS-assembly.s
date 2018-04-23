

	;RESET
	SEI  ;Turn off Interupts
	CLC
	XCE ;Go back into regular mode (from emulator mode)
	REP #$10 ;Set Index Registers to 16-bit mode
	SEP #$20 ;Set Accumulator Register to 16-bit mode
	STZ $420b ;Stop any DMA
	STZ $420c ;Stop any HDMA
	LDA 0 ;Loop  and clear memory
reset_loop:
	TAX
	EOR A, #$FFFF
	IFNZ reset_exit
	STZ $7e:0000,X
	TXA
	SUB A, #1
	BRA reset_loop
reset_exit:
	JMP bios ;Jump to the bios
	
	
	;IRQ
	SEI
	LDA $7e:1000
	LDX $7e:1002
	LDY $7e:1004
	JSR readSub
	JMP (long) sp
	
	
	;BRK
	SEI
	PHA
	LDA $7e:1006
	LDX $7e:1008
	LDY $7e:100A
	JSR readSub
	PLA
	JMP (long) sp
	
	
	.alias ax 
	.alias imm
	;add32(u32 -> ax, u32 -> imm (special register, 32-bit immediate bus))
	add32:
	LDA ax
	LDY imm
	ADD A, Y
	LDX 2
	LDA ax, X
	LDY imm, X
	ADC A, Y
	
	
	.alias eax
	.alias eim
	;add64(u64 -> eax, u32 -> eim (special register, 64-bit immediate bus))
	add64:
	LDA eax
	LDY eim
	ADD A, Y
	LDX 2
	LDA eax, X
	LDY eim, X
	ADC A, Y
	LDA eax
	LDY eim
	ADC A, Y
	LDX 4
	LDA eax, X
	LDY eim, X
	ADC A, Y
	LDA eax
	LDY eim
	ADC A, Y
	LDX 6
	LDA eax, X
	LDY eim, X
	ADC A, Y
	
	
	
	.alias ebp
	.alias bp
	
	.alias PROC_Read #$0001
	.alias PROC_Write #$0002
	.alias PROC_Exec #$0010
	
	;setpermissions(u32 address -> to eax, u16 permissions -> to A)
	setpermissions:
	LDA $7e:0000 ;Get Access Control
	CMP A, #$0000 ;Compare to 0
	IFEQ setpermissions_execute ;If we are being called from the OS then continue
	LDA #$0010 ;Otherwise Throw a Illegal Call Access 
	BRK
	setpermissions_execute:
	setpermissions_checkr:
	PHA
	AND A, PROC_Read
	IFNZ setpermissions_clearr
	JSR MMU_setprocRead
	setpermissions_checkw:
	PLA
	PHA
	AND A, PROC_Write
	IFNZ setpermissions_clearw
	JSR MMU_setprocWrite
	setpermissions_checkexec:
	PLA
	AND A, PROC_Exec
	IFNZ setpermissions_clearx
	JSR MMU_setprocExec
	setpermissions_end:
	RTL
	setpermissions_clearr:
	JSR MMU_clearprocRead
	BRA setpermissions_checkw
	setpermissions_clearw:
	JSR MMU_clearprocWrite
	BRA setpermissions_checkexec
	setpermissions_clearexec:
	JSR MMU_clearprocExec
	BRA setpermissions_end
	
	stop: ;GCC-Attribute noret
	LDA $7e:0000 ;Get Access control
	IFNZ stop_execute
	LDA #$0010
	BRK
	stop_execute:
	SEI
	LDA $7e:1010
	LDX $7e:1012
	LDY $7e:1014
	JSR readSub
	JSR (long) sp
	STP
	
	.alias cioBusTypeQuery
	.alias cioQueryResponse
	.alias cioBusType
	.alias sataQuery
	.db src \sys\boot
	
	
	bios:
	;TODO 
	LDA #$6e
	STA cioBusTypeQuery
	LDA cioQueryResponse
	IFNZ startup_disc
	PHB
	PEA src
	LDA #$6e
	STA cioBusType
	JSR cioBusRead
	BRA startup_finish
	startup_disc:
	
	
	
	
	
	
	
	
	
	
	
