.text
.global _start
.extern printf

_start:
LDR x19, =xvalue
LDR d10, [x19]
LDR x19, =terms
LDR x19, [x19] // number of terms = n+1
FMOV d15, #1.0
MOV x20, #0 // counter for terms
FMOV d11, #1.0 
FSUB d11, d11, d15 // total approximation stored here
Mainloop: CMP x20, x19
B.EQ printing
BL power
BL factorial
SCVTF d13, x23
FDIV d14, d15, d13
FMUL d14, d14, d12
FADD d11, d11, d14
ADD x20, x20, #1
B Mainloop
printing:
FMOV d0, d11
LDR x0, =string
BL printf
B Exit

.func power
power: MOV x24, x20
FMOV d12, #1
Powloop: CMP x24, #0
B.EQ Pbranch
FMUL d12, d12, d10
SUB x24, x24, #1
B Powloop
Pbranch: BR LR
.endfunc

.func factorial
factorial: 
MOV x23, #1
MOV x22, x20
Factloop: CMP x22, #0
B.EQ Fbranch 
MUL x23, x23, x22
SUB x22, x22, #1
B Factloop
Fbranch: BR LR
.endfunc

Exit:
MOV w0, #0
MOV w8, #93
SVC #0
.data
xvalue: .double 2.5
terms: .dword 20
string: .ascii "The approximation is %f\n"
.end
