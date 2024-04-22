; file ps.am
.entry LIST
.extern W
LOOP: prn #48
mcr m1
 clr r6
 prn r6
endmcr
bne END
bne END[r15]
dec K
.entry MAIN
END: hlt
STR: .string "abcd"
LIST: .data 6, -9
.data -100
.entry K
K: .data 31
.extern val1