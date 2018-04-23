.alias eax $70:0000
.alias ax  $70:0000
.alias ax2 $70:0002
.alias ebx $70:0004
.alias bx  $70:0004
.alias bx2 $70:0006

.alias FrameCounterH $7E:0000
.alias FrameCounterL $7E:0002

.alias RTCTimeH1     $7E:0004
.alias RTCTimeL1     $7E:0006
.alias RTCTimeH2     $7E:0008
.alias RTCTimeL2     $7E:000A

BIOS_getFrameCount:
    LDA FrameCounterH
    STA ax
    LDA FrameCounterL
    STA ax2
    RTL
    
BIOS_getRTC:
    LDA RTCTimeH1
    STA ax
    LDA RTCTimeL1
    STA ax2
    LDA RTCTimeH2
    STA bx
    LDA RTCTimeL2
    STA bx2
    RTL


