.alias eax   $70:0000
.alias ax    $70:0002
.alias ebx   $70:0004
.alias bx    $70:0006
.alias ecx   $70:0008
.alias cx    $70:000A
.alias edx   $70:000C
.alias dx    $70:000E
.alias sr    $70:0024
.alias push  $70:002C
.alias pop   $70:002D


.alias OPFirst  $70:4000
.alias OPSecond $70:4008
.alias OPResult $70:4010
.alias DIVRem   $70:4018

.alias OPSize   $70:4020
.alias OPCode   $70:4022
.alias FPCode   $70:4023


.alias OPAdd  #0
.alias OPSub  #1
.alias OPMul  #2
.alias OPDiv  #3

ADD_Word:
    LDX 2
    LDA eax
    STA OPFirst
    LDA ax
    STA OPFirst,X
    LDA ebx
    STA OPSecond
    LDA bx
    STA OPSecond,X
    LDA 4
    STA OPSize
    LDK OPAdd
    STK OPCode
    LDA OPResult
    STA eax
    LDA OPResult,X
    STA ax
    RTL
    
ADD_DWord:
    LDX 2
    LDA eax
    STA OPFirst
    LDA ax
    STA OPFirst,X
    LDA ecx
    STA OPSecond
    LDA cx
    STA OPSecond,X
    LDY 4
    LDX 6
    LDA ebx
    STA OPFirst,Y
    LDA bx
    STA OPFirst,X
    LDA edx
    STA OPSecond,Y
    LDA dx
    STA OPSecond,X
    LDX 4
    LDA 8
    STA OPSize
    LDK OPAdd
    STK OPCode
    LDX 2
    LDA OPResult
    STA eax
    LDA OPResult,X
    STA ax
    LDX 6
    LDA OPResult,Y
    STA ebx
    LDA OPResult,X
    STA bx
    RTL

SUB_Word:
    LDX 2
    LDA eax
    STA OPFirst
    LDA ax
    STA OPFirst,X
    LDA ebx
    STA OPSecond
    LDA bx
    STA OPSecond,X
    LDA 4
    STA OPSize
    LDK OPSub
    STK OPCode
    LDA OPResult
    STA eax
    LDA OPResult,X
    STA ax
    RTL
    
SUB_DWord:
    LDX 2
    LDA eax
    STA OPFirst
    LDA ax
    STA OPFirst,X
    LDA ecx
    STA OPSecond
    LDA cx
    STA OPSecond,X
    LDY 4
    LDX 6
    LDA ebx
    STA OPFirst,Y
    LDA bx
    STA OPFirst,X
    LDA edx
    STA OPSecond,Y
    LDA dx
    STA OPSecond,X
    LDX 4
    LDA 8
    STA OPSize
    LDK OPSub
    STK OPCode
    LDX 2
    LDA OPResult
    STA eax
    LDA OPResult,X
    STA ax
    LDX 6
    LDA OPResult,Y
    STA ebx
    LDA OPResult,X
    STA bx
    RTL

    
    
    
MUL_Word:
    LDX 2
    LDA eax
    STA OPFirst
    LDA ax
    STA OPFirst,X
    LDA ebx
    STA OPSecond
    LDA bx
    STA OPSecond,X
    LDA 4
    STA OPSize
    LDK OPMul
    STK OPCode
    LDA OPResult
    STA eax
    LDA OPResult,X
    STA ax
    RTL
    
MUL_DWord:
    LDX 2
    LDA eax
    STA OPFirst
    LDA ax
    STA OPFirst,X
    LDA ecx
    STA OPSecond
    LDA cx
    STA OPSecond,X
    LDY 4
    LDX 6
    LDA ebx
    STA OPFirst,Y
    LDA bx
    STA OPFirst,X
    LDA edx
    STA OPSecond,Y
    LDA dx
    STA OPSecond,X
    LDX 4
    LDA 8
    STA OPSize
    LDK OPMul
    STK OPCode
    LDX 2
    LDA OPResult
    STA eax
    LDA OPResult,X
    STA ax
    LDX 6
    LDA OPResult,Y
    STA ebx
    LDA OPResult,X
    STA bx
    RTL
    
DIV_Word:
    LDX 2
    LDA eax
    STA OPFirst
    LDA ax
    STA OPFirst,X
    LDA ebx
    STA OPSecond
    LDA bx
    STA OPSecond,X
    LDA 4
    STA OPSize
    LDK OPDiv
    STK OPCode
    LDA OPResult
    STA eax
    LDA OPResult,X
    STA ax
    LDA DIVRem
    STA ebx
    LDA DIVRem,X
    STA bx
    RTL
    
DIV_DWord:
    LDX 2
    LDA eax
    STA OPFirst
    LDA ax
    STA OPFirst,X
    LDA ecx
    STA OPSecond
    LDA cx
    STA OPSecond,X
    LDY 4
    LDX 6
    LDA ebx
    STA OPFirst,Y
    LDA bx
    STA OPFirst,X
    LDA edx
    STA OPSecond,Y
    LDA dx
    STA OPSecond,X
    LDX 4
    LDA 8
    STA OPSize
    LDK OPDiv
    STK OPCode
    LDX 2
    LDA OPResult
    STA eax
    LDA OPResult,X
    STA ax
    LDA DIVRem
    STA ecx
    LDA DIVRem,X
    STA cx
    LDX 6
    LDA OPResult,Y
    STA ebx
    LDA OPResult,X
    STA bx
    LDA DIVRem,Y
    STA edx
    LDA DIVRem,X
    STA dx
    RTL
    
    
    
    
FPADD_Word:
    LDX 2
    LDA eax
    STA OPFirst
    LDA ax
    STA OPFirst,X
    LDA ebx
    STA OPSecond
    LDA bx
    STA OPSecond,X
    LDA 4
    STA OPSize
    LDK OPAdd
    STK FPCode
    LDA OPResult
    STA eax
    LDA OPResult,X
    STA ax
    RTL
    
FPADD_DWord:
    LDX 2
    LDA eax
    STA OPFirst
    LDA ax
    STA OPFirst,X
    LDA ecx
    STA OPSecond
    LDA cx
    STA OPSecond,X
    LDY 4
    LDX 6
    LDA ebx
    STA OPFirst,Y
    LDA bx
    STA OPFirst,X
    LDA edx
    STA OPSecond,Y
    LDA dx
    STA OPSecond,X
    LDX 4
    LDA 8
    STA OPSize
    LDK OPAdd
    STK FPCode
    LDX 2
    LDA OPResult
    STA eax
    LDA OPResult,X
    STA ax
    LDX 6
    LDA OPResult,Y
    STA ebx
    LDA OPResult,X
    STA bx
    RTL

FPSUB_Word:
    LDX 2
    LDA eax
    STA OPFirst
    LDA ax
    STA OPFirst,X
    LDA ebx
    STA OPSecond
    LDA bx
    STA OPSecond,X
    LDA 4
    STA OPSize
    LDK OPSub
    STK FPCode
    LDA OPResult
    STA eax
    LDA OPResult,X
    STA ax
    RTL
    
FPSUB_DWord:
    LDX 2
    LDA eax
    STA OPFirst
    LDA ax
    STA OPFirst,X
    LDA ecx
    STA OPSecond
    LDA cx
    STA OPSecond,X
    LDY 4
    LDX 6
    LDA ebx
    STA OPFirst,Y
    LDA bx
    STA OPFirst,X
    LDA edx
    STA OPSecond,Y
    LDA dx
    STA OPSecond,X
    LDX 4
    LDA 8
    STA OPSize
    LDK OPSub
    STK FPCode
    LDX 2
    LDA OPResult
    STA eax
    LDA OPResult,X
    STA ax
    LDX 6
    LDA OPResult,Y
    STA ebx
    LDA OPResult,X
    STA bx
    RTL

    
    
    
FPMUL_Word:
    LDX 2
    LDA eax
    STA OPFirst
    LDA ax
    STA OPFirst,X
    LDA ebx
    STA OPSecond
    LDA bx
    STA OPSecond,X
    LDA 4
    STA OPSize
    LDK OPMul
    STK FPCode
    LDA OPResult
    STA eax
    LDA OPResult,X
    STA ax
    RTL
    
FPMUL_DWord:
    LDX 2
    LDA eax
    STA OPFirst
    LDA ax
    STA OPFirst,X
    LDA ecx
    STA OPSecond
    LDA cx
    STA OPSecond,X
    LDY 4
    LDX 6
    LDA ebx
    STA OPFirst,Y
    LDA bx
    STA OPFirst,X
    LDA edx
    STA OPSecond,Y
    LDA dx
    STA OPSecond,X
    LDX 4
    LDA 8
    STA OPSize
    LDK FPMul
    STK OPCode
    LDX 2
    LDA OPResult
    STA eax
    LDA OPResult,X
    STA ax
    LDX 6
    LDA OPResult,Y
    STA ebx
    LDA OPResult,X
    STA bx
    RTL
    
FPDIV_Word:
    LDX 2
    LDA eax
    STA OPFirst
    LDA ax
    STA OPFirst,X
    LDA ebx
    STA OPSecond
    LDA bx
    STA OPSecond,X
    LDA 4
    STA OPSize
    LDK OPDiv
    STK FPCode
    LDA OPResult
    STA eax
    LDA OPResult,X
    STA ax
    RTL
    
FPDIV_DWord:
    LDX 2
    LDA eax
    STA OPFirst
    LDA ax
    STA OPFirst,X
    LDA ecx
    STA OPSecond
    LDA cx
    STA OPSecond,X
    LDY 4
    LDX 6
    LDA ebx
    STA OPFirst,Y
    LDA bx
    STA OPFirst,X
    LDA edx
    STA OPSecond,Y
    LDA dx
    STA OPSecond,X
    LDX 4
    LDA 8
    STA OPSize
    LDK OPDiv
    STK FPCode
    LDX 2
    LDA OPResult
    STA eax
    LDA OPResult,X
    STA ax
    LDX 6
    LDA OPResult,Y
    STA ebx
    LDA OPResult,X
    STA bx
    RTL
