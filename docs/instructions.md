# Instructions of VBC (in hex)
00 -- ADD
  - Description:
    Adds values of two registers
  - Example:
    00 07 06 -- ADD %r7 %r6

01 -- ADDV
  - Description:
    Adds some number to register
  - Example:
    01 07 1A -- ADDV %r7 x1A

02 -- MOV
  - Description:
    Moves some number to register
  - Example:
    02 0C 45 -- MOV %r12 x45

03 -- SUB
  - Description:
    Subtracts values of two registers
  - Example:
    03 07 06 -- SUB %r7 %r6

04 -- SUBV
  - Description:
    Subtracts some number to register
  - Example:
    04 07 1A -- SUBV %r7 x1A

05 -- MUL
  - Description:
    Adds values of two registers
  - Example:
    05 07 06 -- MUL %r7 %r6

06 -- MULV
  - Description:
    Multiples some number to register
  - Example:
    06 07 1A -- MULV %r7 x1A

0A -- LOD
  - Description:
    Loads some value into the register
  - Example:
    0A 07 00 00 00 00 -- LOD %r7 x00000000

0E -- CMP
  - Description:
    Compares two values from two registers and sets the flags (%flags 16-bit register).
  - Example:
    0E 01 02 -- CMP %r1 %r2

10 -- JUMP
  - Description:
    Jumps to some 32-bit location in code
  - Example:
    10 08 00 F0 23 -- JMP x0800F023

11 -- JEQ
  - Description:
    Jumps to some 32-bit location in code if comparison result set the zero flag.
  - Example:
    10 08 00 F0 23 -- JMP x0800F023

2A -- KCALL
  - Description:
    Makes kernel call with arguments from registers %r7-%r13.
  - Example:
    2A -- KCALL
    2A 40 -- KCALL NOP
    * KCALL NOP is used for the end, next byte being not segfault.

