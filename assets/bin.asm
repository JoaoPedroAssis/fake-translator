CERTO: EQU 1
ERRADO: EQU 0
CERTO2:
EQU 1
ERRADO2:
EQU 0


    SECTION TEXT
IF CERTO2
SUB UM
IF 1
SUB UM
IF 0
SUB ZERO
IF ERRADO2
SUB ZERO
COPY LABEL, DOIS
SUB OLD_DATA + 2
COPY LABEL, OLD_DATA + 2
STOP

SECTION DATA
ZERO: CONST 0
UM:       CONST 1
OLD_DATA:   SPACE 2
NEW_SPACE:
SPACE 1
LABELNEW: SPACE CERTO
TEST: SPACE
NEW_DATA:   SPACE
TMP_DATA:   SPACE 4