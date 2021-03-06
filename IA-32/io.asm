; =====================================
LerChar:
ENTER 0,0
PUSHA
MOV EAX, 3
MOV EBX, 0
MOV ECX, [EBP + 8]
MOV EDX, 1
INT 80h
POPA
LEAVE
RET

; ======================================

EscreverChar:
ENTER 0,0
PUSHA
MOV EAX, 4
MOV EBX, 1
MOV ECX, [EBP + 8]
MOV EDX, 1
INT 80h
POPA
LEAVE
RET

; ======================================

LerString:
ENTER 0,0

PUSH EBX
PUSH ECX
PUSH EDX

MOV EAX,0
MOV EDX, [EBP + 8]
ADD EDX, 1

Loop:
MOV ECX,[EBP + 12]
MOV EBX,EAX
ADD ECX,EBX
PUSH ECX
CALL LerChar
ADD ESP,4
INC EAX
CMP DWORD [ECX], 0xa
JE  Exit
CMP EAX, EDX
JNE Loop

Exit:
MOV DWORD [ECX], 0

POP EDX
POP ECX
POP EBX

DEC EAX

ADD ESP, 4
LEAVE
RET

; ======================================

EscreverString:
ENTER 0,0
PUSHA
MOV EAX, 4
MOV EBX, 1
MOV ECX, [EBP + 12]
MOV EDX, [EBP + 8]
INT 80h
POPA
LEAVE
RET

; =====================================

LerInteiro:
ENTER 0,0
PUSH EBX
PUSH ECX
PUSH EDX
PUSH EDI

MOV EAX, 3
MOV EBX, 0
MOV ECX, BUFFER
MOV EDX, BUFFER_SIZE
INT 80h

XOR ECX, ECX
XOR EAX, EAX
MOV EBX, BUFFER

LOOP_CONVERSAO:
MOV DL, 0x0a
CMP DL, [EBX + ECX]
JE RI32_Cont
PUSH EAX
SHL EAX, 3
ADD EAX, [ESP]
ADD EAX, [ESP]
MOV DL, 0x2d
CMP DL, [EBX + ECX]
JE SINAL_NEGATIVO
SUB EDX, EDX
MOV DL, [EBX + ECX]
SUB EDX, 0x30
ADD EAX, EDX
SINAL_NEGATIVO:
INC ECX
JMP LOOP_CONVERSAO
RI32_Cont:
MOV DL, 0x2d
CMP byte DL, [EBX]
JNE SINAL_POSITIVO
PUSH EAX
XOR EAX, EAX
SUB EAX, [ESP]
ADD ESP, 4
SINAL_POSITIVO:

MOV EDX, [EBP + 8]
MOV [EDX], EAX
MOV EAX, ECX

POP EDI
POP EDX
POP ECX
POP EBX
LEAVE
RET

; ====================================

EscreverInteiro:
ENTER 0,0
PUSHA
XOR EAX, EAX
XOR EDX, EDX
XOR ECX, ECX
XOR EDI, EDI
MOV EBX, BUFFER
MOV EAX, [EBP + 8]
CMP EAX, 0
JNE PRINT_SINAL_NEGATIVO
MOV DL, 0
ADD DL, 0x30
MOV byte [EBX], DL
MOV DL, [EBX]
INC ECX
JMP PRINT_CONTADOR3
PRINT_SINAL_NEGATIVO:  
TEST EAX, 0x80000000
JE PRINT_SINAL_POSITIVO
XOR EAX, EAX
SUB EAX, [EBP + 8]
MOV byte [EBX], 0x2d 
INC EBX
MOV EDI, 1
JMP PRINT_LOOP_CONVERSAO
PRINT_SINAL_POSITIVO:
MOV EAX, [EBP + 8]
PRINT_LOOP_CONVERSAO:
XOR EDX, EDX
PUSH EBX
MOV EBX, 10
DIV EBX
POP EBX
CMP EAX, 0
JNE PRINT_CONTADOR
CMP EDX, 0
JE PRINT_CONTADOR3
PRINT_CONTADOR:  
ADD EDX, 0x30
PUSH ECX
PI32_Shift_R:
CMP ECX, 0
JE PRINT_CONTADOR2
MOV byte DH, [EBX + ECX - 1]
MOV byte [EBX + ECX], DH 
DEC ECX
JMP PI32_Shift_R
PRINT_CONTADOR2:  
MOV byte [EBX], DL
POP ECX
INC ECX
JMP PRINT_LOOP_CONVERSAO
PRINT_CONTADOR3:
CMP EDI, 1
JNE PRINT
INC ECX
DEC EBX
PRINT:  
PUSH EBX
PUSH ECX
CALL EscreverString
ADD ESP, 8
POPA
LEAVE
RET

; =============================================

EscreveTamanho:
ENTER 0,0
PUSH lenMsgStart
PUSH 19
CALL EscreverString
PUSH eax
CALL EscreverInteiro
PUSH lenMsgEnd
PUSH 12
CALL EscreverString
LEAVE
RET

