.alias eax $70:0000
.alias ax  $70:0000
.alias ax2 $70:0002
.alias ebx $70:0004
.alias bx  $70:0004
.alias bh  $70:0004
.alias bl  $70:0005
.alias bx2 $70:0006
.alias bh2 $70:0006
.alias bl2 $70:0007
.alias sr    $70:0024
.alias push  $70:002C
.alias pop   $70:002D

    ;clock(void)
clock:
    JSR (long) BIOS_getFrameCount
    RTL
    
    ;time(time_t*)
time:
    STA pop 4
    LDA sr
    STA ebp
    LDX 2
    LDA sr,X
    STA ebp,X
    JSR (long) BIOS_getRTC
    LDA ebp
    IFNZ time_storeptr
    LDA ebp,X
    IFNZ time_storeptr
    RTL
    time_storeptr:
    LDX 2
    LDA ax
    STA [ebp]
    LDA ax2
    STA [ebp],X
    LDX 4
    LDA bx
    STA [ebp],X
    LDX 6
    LDA bx2
    STA [ebp],X
    RTL
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
