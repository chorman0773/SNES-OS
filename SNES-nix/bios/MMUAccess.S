.alias MMUAddressRegisterH $70:4000
.alias MMUAddressRegisterL $70:4002
.alias MMUSetPermissionsRegister $70:4004
.alias MMUClearPermissionsRegister $70:4005
.alias MMUUpdateProcRegister $70:4006
.alias ax $70:0000
.alias ah $70:0000
.alias al $70:0001
.alias bx $70:0002
.alias bh $70:0002
.alias bl $70:0003


MMU_setprocRead:
    LDA ax
    LDX bx
    LDK #01
    STA MMUAddressRegisterH
    STX MMUAddressRegisterL
    STK MMUSetPermissionsRegister
    LDK #01
    STK MMUUpdateProcRegister
    RTS

MMU_clearprocRead:
    LDA ax
    LDX bx
    LDK #01
    STA MMUAddressRegisterH
    STX MMUAddressRegisterL
    STK MMUClearPermissionsRegister
    LDK #01
    STK MMUUpdateProcRegister
    

MMU_setprocWrite:
    LDA ax
    LDX bx
    LDK #02
    STA MMUAddressRegisterH
    STX MMUAddressRegisterL
    STK MMUSetPermissionsRegister
    LDK #01
    STK MMUUpdateProcRegister
    RTS

MMU_clearprocWrite:
    LDA ax
    LDX bx
    LDK #02
    STA MMUAddressRegisterH
    STX MMUAddressRegisterL
    STK MMUClearPermissionsRegister
    LDK #01
    STK MMUUpdateProcRegister  
    
    
 MMU_setprocExec:
    LDA ax
    LDX bx
    LDK #04
    STA MMUAddressRegisterH
    STX MMUAddressRegisterL
    STK MMUSetPermissionsRegister
    LDK #01
    STK MMUUpdateProcRegister
    RTS

MMU_clearprocExec:
    LDA ax
    LDX bx
    LDK #04
    STA MMUAddressRegisterH
    STX MMUAddressRegisterL
    STK MMUClearPermissionsRegister
    LDK #01
    STK MMUUpdateProcRegister   
    
    

    
