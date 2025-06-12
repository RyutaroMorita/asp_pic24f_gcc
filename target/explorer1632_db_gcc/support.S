    .section ivt, code, address(0x00004)
    .pword __OscillatorFail	; 0x0004
    .pword __AddressError	; 0x0006
    .pword __NVMError		; 0x0008
    .pword __StackError		; 0x000A
    .pword __MathError		; 0x000C
    .pword __DefaultInterrupt	; 0x000E
    .pword __DefaultInterrupt	; 0x0010
    .pword __DefaultInterrupt	; 0x0012
    .pword __DefaultInterrupt	; 0x0014
    .pword __DefaultInterrupt	; 0x0016
    .pword __DefaultInterrupt	; 0x0018
    .pword inthdr_3		; 0x001A
    .pword __DefaultInterrupt	; 0x001C
    .pword __DefaultInterrupt	; 0x001E
    .pword __DefaultInterrupt	; 0x0020
    .pword __DefaultInterrupt	; 0x0022
    .pword __DefaultInterrupt	; 0x0024
    .pword __DefaultInterrupt	; 0x0026
    .pword __DefaultInterrupt	; 0x0028    // 10
    .pword inthdr_11		; 0x002A
    .pword inthdr_12		; 0x002C
    .pword __DefaultInterrupt	; 0x002E
    .pword __DefaultInterrupt	; 0x0030
    .pword __DefaultInterrupt	; 0x0032
    .pword __DefaultInterrupt	; 0x0034
    .pword __DefaultInterrupt	; 0x0036
    .pword __DefaultInterrupt	; 0x0038
    .pword __DefaultInterrupt	; 0x003A
    .pword __DefaultInterrupt	; 0x003C    // 20
    .pword __DefaultInterrupt	; 0x003E
    .pword __DefaultInterrupt	; 0x0040
    .pword __DefaultInterrupt	; 0x0042
    .pword __DefaultInterrupt	; 0x0044
    .pword __DefaultInterrupt	; 0x0046
    .pword __DefaultInterrupt	; 0x0048
    .pword __DefaultInterrupt	; 0x004A
    .pword __DefaultInterrupt	; 0x004C
    .pword __DefaultInterrupt	; 0x004E
    .pword __DefaultInterrupt	; 0x0050    // 30
    .pword __DefaultInterrupt	; 0x0052
    .pword __DefaultInterrupt	; 0x0054
    .pword __DefaultInterrupt	; 0x0056
    .pword __DefaultInterrupt	; 0x0058
    .pword __DefaultInterrupt	; 0x005A
    .pword __DefaultInterrupt	; 0x005C
    .pword __DefaultInterrupt	; 0x005E
    .pword __DefaultInterrupt	; 0x0060
    .pword __DefaultInterrupt	; 0x0062
    .pword __DefaultInterrupt	; 0x0064    // 40
    .pword __DefaultInterrupt	; 0x0066
    .pword __DefaultInterrupt	; 0x0068
    .pword __DefaultInterrupt	; 0x006A
    .pword __DefaultInterrupt	; 0x006C
    .pword __DefaultInterrupt	; 0x006E
    .pword __DefaultInterrupt	; 0x0070
    .pword __DefaultInterrupt	; 0x0072
    .pword __DefaultInterrupt	; 0x0074
    .pword __DefaultInterrupt	; 0x0076
    .pword __DefaultInterrupt	; 0x0078    // 50
    .pword __DefaultInterrupt	; 0x007A
    .pword __DefaultInterrupt	; 0x007C
    .pword __DefaultInterrupt	; 0x007E
    .pword __DefaultInterrupt	; 0x0080
    .pword __DefaultInterrupt	; 0x0082
    .pword __DefaultInterrupt	; 0x0084
    .pword __DefaultInterrupt	; 0x0086
    .pword __DefaultInterrupt	; 0x0088
    .pword __DefaultInterrupt	; 0x008A
    .pword __DefaultInterrupt	; 0x008C    // 60
    .pword __DefaultInterrupt	; 0x008E
    .pword __DefaultInterrupt	; 0x0090
    .pword __DefaultInterrupt	; 0x0092
    .pword __DefaultInterrupt	; 0x0094
    .pword inthdr_65		; 0x0096

    .section text, code
    .global inthdr_3
inthdr_3:
    push    RCOUNT
    mov	    w1, [w15++]
    mov	    #3, w1
    mov	    w0, [w15++]
    mov.d   w2, [w15++]
    mov.d   w4, [w15++]
    mov.d   w6, [w15++]
    lnk	    #0x0
    mov	    #_exc_tb, w2
    mul.uu  w1, #2, w4
    add	    w2, w4, w2
    mov	    [w2], w0
    call    w0
    ulnk
    mov.d   [--w15], w6
    mov.d   [--w15], w4
    mov.d   [--w15], w2
    mov	    [--w15], w0   
    mov	    [--w15], w1   
    pop	    RCOUNT
    retfie

    .section text, code
    .global inthdr_11
inthdr_11:
    push    RCOUNT
    mov	    w1, [w15++]
    mov	    #11, w1
    mov	    w0, [w15++]
    mov.d   w2, [w15++]
    mov.d   w4, [w15++]
    mov.d   w6, [w15++]
    lnk	    #0x0
    mov	    #_exc_tb, w2
    mul.uu  w1, #2, w4
    add	    w2, w4, w2
    mov	    [w2], w0
    call    w0
    ulnk
    mov.d   [--w15], w6
    mov.d   [--w15], w4
    mov.d   [--w15], w2
    mov	    [--w15], w0   
    mov	    [--w15], w1   
    pop	    RCOUNT
    retfie

    .section text, code
    .global inthdr_12
inthdr_12:
    push    RCOUNT
    mov	    w1, [w15++]
    mov	    #12, w1
    mov	    w0, [w15++]
    mov.d   w2, [w15++]
    mov.d   w4, [w15++]
    mov.d   w6, [w15++]
    lnk	    #0x0
    mov	    #_exc_tb, w2
    mul.uu  w1, #2, w4
    add	    w2, w4, w2
    mov	    [w2], w0
    call    w0
    ulnk
    mov.d   [--w15], w6
    mov.d   [--w15], w4
    mov.d   [--w15], w2
    mov	    [--w15], w0   
    mov	    [--w15], w1   
    pop	    RCOUNT
    retfie

    .section text, code
    .global inthdr_65
inthdr_65:
    push    RCOUNT
    mov	    w1, [w15++]
    mov	    #65, w1
    mov	    w0, [w15++]
    mov.d   w2, [w15++]
    mov.d   w4, [w15++]
    mov.d   w6, [w15++]
    lnk	    #0x0
    mov	    #_exc_tb, w2
    mul.uu  w1, #2, w4
    add	    w2, w4, w2
    mov	    [w2], w0
    call    w0
    ulnk
    mov.d   [--w15], w6
    mov.d   [--w15], w4
    mov.d   [--w15], w2
    mov	    [--w15], w0   
    mov	    [--w15], w1   
    pop	    RCOUNT
    retfie
