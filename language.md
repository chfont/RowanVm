# Language Specification

#### Registers

There are 16 registers, each of which can hold an integer (4 bytes). Registers are named by r[letter],
where letter is between a and p. Examples: `ra`, `re`

#### Conditions
Conditional jump statements take a condition argument. The following are legal values:

- eq - equal
- neq - not equal
- lt - less than
- le - less than or equal to
- ge - greater than or equal to
- gt - greater than

#### Instruction Types

Instructions/Opcodes are classified into several types:

- Single register: instruction followed by single register
- Two registers: instruction followed by two registers
- Nop: the nop instruction (does nothing)
- Register and Number: instruction followed by register, then a number
- Conditional: Conditional jump instruction

#### Labels

Labels use the following syntax: `NAME:`, where NAME is the label name. These are case insensitive.

#### Instructions

- ldc: Load constant. Takes a register, then a number. Ex: `ldc ra 5`
- ld: Load. Takes two registers, loads value in second register into first register. Ex: `ld ra rb`
- st: Store. Takes register and a number, stores register value into memory location specified. Ex: `st ra 50`
- add: Addition. Takes two registers, adds second register to first, stores value in first. Ex: `add ra rb`
- sub: Subtraction. Takes two registers, subtracting the second from the first, and storing the result in the first. Ex: `sub ra rb`
- mult: Multiplication. Takes two registers, multiplying them, and storing value in first. Ex: `mult ra rb`
- div: Division. Takes two registers, and computes first / second (Integer division), storing the result in the first. Ex: `div ra rb`
- nop: No-op. This instruction does nothing (takes up one execution cycle)
- cjump: Conditional jump. Evaluates condition, then jumps if satisfied. Ex: `cjump eq ra rb`
- pr: Print. Takes one register, and prints its value to the console. Ex: `pr ra`
- prb: Print as boolean. Takes one register, prints true if it is not 0, false otherwise. Ex: `prb ra`