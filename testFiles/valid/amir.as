.entry LIST
.extern W
.define sz = 1
MAIN: add r3, LIST
LOOP: prn #48
mcr m1
 inc r6
 mov r3, W
endmcr
lea STR, r6
mov sz, r2
inc r6
mov r3, W
sub r1, r4
bne END
cmp val1, #-6
dec K
.entry MAIN
sub LOOP[2] ,r2
END: hlt
STR: .string "abcd"
LIST: .data 6, -9
.data -100
.entry K
K: .data 31
.extern val1