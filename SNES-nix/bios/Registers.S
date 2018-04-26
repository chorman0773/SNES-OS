
    ;Normal Registers.
    ;Mirrors their counterparts from x86
.alias eax $70:0000
.alias ax  $70:0000
.alias ah  $70:0000
.alias al  $70:0001
.alias ax2 $70:0002
.alias ah2 $70:0002
.alias al2 $70:0003
.alias ebx $70:0004
.alias bx  $70:0004
.alias bh  $70:0004
.alias bl  $70:0005
.alias bx2 $70:0006
.alias bh2 $70:0006
.alias bl2 $70:0007
.alias ecx $70:0008
.alias cx  $70:0008
.alias ch  $70:0008
.alias cl  $70:0009
.alias cx2 $70:000A
.alias ch2 $70:000A
.alias cl2 $70:000B
.alias edx $70:000C
.alias dx  $70:000C
.alias dh  $70:000C
.alias dl  $70:000D
.alias dx2 $70:000E
.alias dh2 $70:000E
.alias dl2 $70:000F

.alias esi $70:0010
.alias si  $70:0010
.alias si2 $70:0012
.alias edi $70:0014
.alias di  $70:0014
.alias di2 $70:0016



    ;Stack Registers
.alias ebp $70:0018
.alias bp  $70:001A
.alias esp $70:001C
.alias sp  $70:001E

    

    ;Instruction Pointer (TODO)
.alias eip $70:0020
.alias ip  $70:0020
.alias pb  $70:0022

    ;Stack Push/Pop
    ;To Push a value, write the value to sr and write the size in bytes to push (1, 2, 4, or 8)
    ;To Pop a value, write the size in bytes to pop (1, 2, 4, or 8)
.alias sr    $70:0024
.alias push  $70:002C
.alias pop   $70:002D




