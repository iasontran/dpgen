# dpgen

Names: Andrew Camps (ECE 574a), Jason Tran (ECE 474a), Steve Miller (ECE 474a), Maria Walshe (ECE 474a)

NetIDs: andrewcamps, ichikasuto, stevenmiller, mcwalshe

Description: This program converts a behavioral netlist specification into a synthesizable Verilog data path implementation. After creating the Verilog implementation, the program will report the critical path of the datapath. This will be either the longest register to register delay or the longest input to register delay.

The program will detect basic syntax errors such as not declaring particular inputs or trying to use invalid operation components. The components supported in this program are listed below. 

Register types in the high level code are converted to wire types. Inputs, outputs, and wires are defined as signed upon definition using the signed keyword in Verilog.

Unsigned Modules:

REG
ADD
SUB
MUL
COMP (gt output)
COMP (lt output)
COMP (eq output)
MUX2x1
SHR
SHL
DIV
MOD
INC
DEC

Signed Modules:

SREG
SADD
SSUB
SMUL
SCOMP (gt output)
SCOMP (lt output)
SCOMP (eq output)
SMUX2x1
SSHR
SSHL
SDIV
SMOD
SINC
SDEC


Team Contribution Descriptions:

Andrew Camps - Worked on various aspects of the including creating a skeleton outline of the project, parsing of input file, creating graph of nodes, outputting to Verilog file, and writing critical path algorithm.

Jason Tran - Worked on various aspects of the including creating a skeleton outline of the project, parsing of input file, creating graph of nodes, outputting to Verilog file, and writing critical path algorithm.

Steve Miller - Bug fixes, function refactoring, build testing on submission environment.

Maria Walshe - Confirmed program output results in synthesizable Verilog modules.





