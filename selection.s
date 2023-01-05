.text
.global _start
.extern printf

_start:
.global insertion
LDR x0, =array
MOV x2, x0
ADD x2, x2, #8
MOV x6, x2
LDR x4, =length
LDR x4, [x4]
LSL x4, x4, #3
ADD x4, x4, x0
BL insertion
LDR x1, =length
LDR x1, [x1]
BL Start
B Exit

.func insertion
insertion:
Loop: CMP x2, x4
B.EQ End
Sort: LDR x1, [x6, #-8]
LDR x5, [x6]
CMP x1, x5
B.GT Swap
ADD x2,x2, #8
MOV x6, x2
B Loop
Swap: 
STR x5, [x6, #-8]
STR x1, [x6]
SUB x6, x6, #8
CMP x0, x6
B.NE Sort
ADD x2, x2, #8
MOV x6, x2
B Loop
End: BR LR
.endfunc


Start: SUB SP, SP, #24
STR LR, [SP, #0]
STR x0, [SP, #8]
STR x1, [SP, #16]
MOV x21, #0
Printer: CMP x21, x1
B.GE Final
LSL x11, x21, #3
LDR x1, [x0, x11]
LDR x0, =string
BL printf
LDR x0, [SP, #8]
LDR x1, [SP, #16]
ADD x21, x21, #1
B Printer
Final: LDR LR, [SP, #0]
LDR x0, [SP, #8]
LDR x1, [SP, #16]
ADD SP, SP, #24
BR LR


Exit:
MOV w0, #0
MOV w8, #93
SVC #0

.data
array: .dword 3,5,7,1,4,9,10,2,6,8
length: .dword 10
string: .ascii "The insertion sort sorted the array: %d\n"
.end
