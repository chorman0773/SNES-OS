.alias ebp  $70:0018
.alias esp  $70:001C
.alias sr   $70:0024
.alias push $70:002C
.alias pop  $70:002D
.alias ax   $70:0000
.alias ax2  $70:0002
.alias bx   $70:0004
.alias bx2  $70:0006

    ;signal(void(*)(int))
signal:
    LDA ax
    STA bx
    LDA ax2
    STA bx2
    LDA #5
    STA ax
    LDA #0
    STA ax2
    JSR (long) syscall
    RTL
    
    
    ;raise(int)
raise:
    LDA ax
    BRK
    RTL 
    
