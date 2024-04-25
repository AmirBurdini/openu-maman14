.entry LIST
.extern W
.extern ROO
.define arba = 4
MAIN: add r3, LIST
LOOP: prn #48
mcr moo
 prn r6
 mov r3, W
endmcr
lea STR, r6
inc r6
mov r3, W
sub r1, r4
bne END
cmp val1, #-6
bne END[arba]
dec K
.entry MAIN
sub LOOP[2] ,r3
END: hlt
STR: .string "abcd"
LIST: .data 6, -9
.data -100
.entry K
K: .data 31
.extern val1