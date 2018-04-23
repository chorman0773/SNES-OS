
.alias ebp  $70:0018
.alias esp  $70:001C
.alias sr   $70:0024
.alias push $70:002C
.alias pop  $70:002D
.alias ax   $70:0000
.alias ax2  $70:0002

    ;int _setjmp(jmp_buf*)
_setjmp:
    LDA sp
    LDK sp, 1
    LDX 2
    STA [ebp]
    STK [ebp],X
    LDY 0
    STY ax
    STY ax2
    RTL

    ;void longjmp(jmp_buf,int)
longjmp:
    LDX 2
    LDA [ebp]
    LDK [ebp],X
    STA sr
    STK sr,X
    LDX 4
    LDY [ebp],X
    LDX 6
    STY ax
    LDY [ebp],X
    STY ax2
    PHA
    PHK
    RTL

    
    
