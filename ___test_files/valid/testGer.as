; file ps.am
MAIN: add r3, r1
LOOP: jmp L1
mcr m_mcr
 inc r2
endmcr
L1: inc r3
bne LOOP
END: hlt

