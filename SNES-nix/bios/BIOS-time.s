.alias eax $70:0000
.alias ax  $70:0000
.alias ax2 $70:0002
.alias ebx $70:0004
.alias bx  $70:0004
.alias bx2 $70:0006
.alias ecx $70:0008
.alias cx  $70:0008
.alias cx2 $70:000A

.alias FrameCounterLatch $7E:1000
.alias RTCTimeLatch      $7E:1001
.alias RTCInstantLatch   $7E:1002

.alias FrameCounterH $7E:0000
.alias FrameCounterL $7E:0002

.alias RTCTimeH1     $7E:0004
.alias RTCTimeL1     $7E:0006
.alias RTCTimeH2     $7E:0008
.alias RTCTimeL2     $7E:000A

.alias RTCNanosH     $7E:000C
.alias RTCNanosL     $7E:000E
.alias RTCSecondsH1  $7E:0010
.alias RTCSecondsL1  $7E:0012
.alias RTCSecondsH2  $7E:0014
.alias RTCSecondsL2  $7E:0016
.alias ebp   $70:0018
.alias esp   $70:001C
.alias sr    $70:0024
.alias push  $70:002C
.alias pop   $70:002D

BIOS_getFrameCount:
    LDK 1
    STK FrameCounterLatch
    LDA FrameCounterH
    STA ax
    LDA FrameCounterL
    STA ax2
    RTL
    
BIOS_getRTC:
    LDK 1
    STK RTCTimeLatch
    LDA RTCTimeH1
    STA ax
    LDA RTCTimeL1
    STA ax2
    LDA RTCTimeH2
    STA bx
    LDA RTCTimeL2
    STA bx2
    RTL

BIOS_getRTCInstant:
    LDK 1
    STK RTCInstantLatch
    LDA RTCNanosH
    STA cx
    LDA RTCNanosL
    STA cx2
    LDA RTCSecondsH1
    STA ax
    LDA RTCSecondsL1
    STA ax2
    LDA RTCSecondsH2
    STA bx
    LDA RTCSecondsL2
    STA bx2
    RTL
    
    
