    ;exit(int) attribute noreturn
exit:
    LDA 32
    BRK
    
    ;abort() attribute noreturn
abort:
    LDA 33
    BRK
    
    ;atExit(void(*)(int))
atExit:
    LDA ax
    STA bx
    LDA ax2
    STA bx2
    LDA #6
    STA ax
    LDA #0
    STA ax2
    JSR (long) syscall
