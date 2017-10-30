# dpgen

Names: Andrew Camps (ECE 574a), Jason Tran (ECE 474a), Steve Miller (ECE 474a)

NetIDs: andrewcamps, ichikasuto, stevemiller

Description: This program converts a behavioral setlist specification into a synthesizable Verilog data path implementation. After creating the Verilog implementation, the program will report the critical path of the datapath. This will be either the longest register to register delay or the longest input to register delay.

The program will detect basic syntax errors such as not declaring particular inputs or trying to use invalid operation components. The components supported in this program are:

// REG //// ADD //// SUB //// MUL //// COMP (gt output) //
// COMP (lt output) //
// COMP (eq output) //
// MUX2x1 //// SHR //// SHL //// DIV //// MOD //// INC //// DEC //

Team Contribution Descriptions:

Andrew Camps - 
Jason Tran - 
Steve Miller - 





