SECTION TEXT
INPUT N3
INPUT N4
LOAD N3
JMPZ SOMA
JMPP SUB

SOMA:
LOAD N4
ADD DOIS
JMP FIM

SUB:
LOAD N4
SUB DOIS

FIM:
STORE N4
OUTPUT N4

STOP
SECTION DATA
N3: SPACE 1
N4: SPACE 1
result: SPACE 1
UM: CONST 1
DOIS: CONST 2