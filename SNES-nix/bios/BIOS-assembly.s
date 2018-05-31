.no-elf-header ;When all linkages are satisfied the Binary generator will generate this as a raw SNES ROM. (without the normal header)
		;IE something that can be burned onto an EPROM... 
.alias sr    $70:0024
.alias push  $70:002C
.alias pop   $70:002D
.alias ebp $70:0018
.alias bp  $70:001A
.alias esp $70:001C
.alias sp  $70:001E
.extern hblank
.extern nmiRoutine

.section primary_header $01:0000 r ;Address unimportant, but sections have to have a position header
.db 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00
.db 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00
	;SHA-256 Hash of everything thats the headers.
.section bios_header $01:2000 r
.db "SNES-OS BIOS" ;Name of the system
.db "Connor Horman" ;Name of the Author
.db 0x48 0xac 0x2f 0x74 0x36 0x77 0xe6 0x98 0x19 0xd0 0x96 0xbc 0xa9 0x6e 0x9e ;Developer UUID 
.db 0x00 0x00 ;Version Code, "1.0"


.section header $00:ffc0 r ;Everything that will actually get mapped into memory is going to be placed at the correct address in the ASM file.
.db "SNES-OS BIOS" 
.db 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00
.db 0x31 0x00 0x00 0x00
.db 0x00 0x00
.db 0x00
.db 0xFF 0xFF
.db 0x00 0x00
.reposition $00:ffe4
.db 0xFF 0xFF
.db 0x00 0x00
.db 0x0B 0x00
.db 0x10 0x00
.db 0x15 0x00
.db 0x00 0x00
.db 0x1A 0x00
.reposition $00:fff4
.db 0xFF 0xFF
.db 0xFF 0xFF
.db 0xFF 0xFF
.db 0x00 0x00
.db 0xFF 0xFF
.db 0xFF 0xFF


.section interrupts $00:0000 rx
reset:
	SEI  ;Turn off Interupts
	CLC
	XCE ;Go back into regular mode (from emulator mode)
	REP #$10 ;Set Index Registers to 16-bit mode
	SEP #$20 ;Set Accumulator Register to 16-bit mode
	JMP (long) bios ;Jump to the bios
brk:
	SEI
	JMP (long) [$7e:1004]
	
abort:
	SEI
	JMP (long) stop_execute
	
nmi:
	SEI
	JMP (long) nmiRoutine

irq:
	SEI
	LDA $70:8104
	IFZ +4
	JMP (long) hblank
	AND 1
	IFZ +4
	JMP (long) [$7e:1000]
	BRK
	



.section bios_functions $fe:0000
stop: ;GCC-Attribute noret
	LDA $7e:0000 ;Get Access control
	IFNZ stop_execute
	LDA #$0010
	BRK
stop_execute:
	SEI
	JSL [$7e:1010]
	STP
	
	
	
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
	setpermissions_clearw:syscall
	JSR MMU_clearprocWrite
	BRA setpermissions_checkexec
	setpermissions_clearexec:
	JSR MMU_clearprocExec
	BRA setpermissions_end
	
	
	
	
bios:
	
	
	
	
	
	
	
	
	
	
	
	
	
