
.alias sr    $70:0024
.alias push  $70:002C
.alias pop   $70:002D
.alias ebp $70:0018
.alias bp  $70:001A
.alias esp $70:001C
.alias sp  $70:001E

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
	JMP (long) [$7e:1000]
	
	
	;BRK
	SEI
	JMP (long) [$7e:1004]
	
	;NMI
	SEI
	JMP (long) nmiRoutine
	
	
	
	
	
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
	
	.db startupFile 5C 73 79 73 5C 62 6F 6F 66 5C 00
	
	
	bios:
	;TODO 
	startup:
	
	
	
	
	
	
	
	
	
	
	
	
