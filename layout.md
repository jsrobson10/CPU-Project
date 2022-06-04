
# Memory

- (0x0000000000000000 -> 0x3fffffffffffffff) Zero
- (0x4000000000000000 -> 0x7fffffffffffffff) Program memory
- (0x8000000000000000 -> 0xbfffffffffffffff) Stack memory
- (0xc000000000000000 -> 0xffffffffffffffff) I/O

# Instructions

0. EXIT
0. GOTO
	- 8->1 pointer to condition
	- 8->8 pointer to location 1 if true
	- 8->8 pointer to location 2 if false
    - 8->8 pointer to store current location
0. ADD-8
	- 8->1 pointer to param 1
	- 8->1 pointer to param 2
	- 8->1 pointer to result
0. ADD-16
	- 8->2 pointer to param 1
	- 8->2 pointer to param 2
	- 8->2 pointer to result
0. ADD-32
	- 8->4 pointer to param 1
	- 8->4 pointer to param 2
	- 8->4 pointer to result
0. ADD-64
	- 8->8 pointer to param 1
	- 8->8 pointer to param 2
	- 8->8 pointer to result
0. ADD-F
	- 8->4 pointer to param 1
	- 8->4 pointer to param 2
	- 8->4 pointer to result
0. ADD-D
	- 8->8 pointer to param 1
	- 8->8 pointer to param 2
	- 8->8 pointer to result
0. SUB-8
	- 8->1 pointer to param 1
	- 8->1 pointer to param 2
	- 8->1 pointer to result
0. SUB-16
	- 8->2 pointer to param 1
	- 8->2 pointer to param 2
	- 8->2 pointer to result
0. SUB-32
	- 8->4 pointer to param 1
	- 8->4 pointer to param 2
	- 8->4 pointer to result
0. SUB-64
	- 8->8 pointer to param 1
	- 8->8 pointer to param 2
	- 8->8 pointer to result
0. SUB-F
	- 8->4 pointer to param 1
	- 8->4 pointer to param 2
	- 8->4 pointer to result
0. SUB-D
	- 8->8 pointer to param 1
	- 8->8 pointer to param 2
	- 8->8 pointer to result
0. MUL-U-8
	- 8->1 pointer to param 1
	- 8->1 pointer to param 2
	- 8->1 pointer to result
0. MUL-U-16
	- 8->2 pointer to param 1
	- 8->2 pointer to param 2
	- 8->2 pointer to result
0. MUL-U-32
	- 8->4 pointer to param 1
	- 8->4 pointer to param 2
	- 8->4 pointer to result
0. MUL-U-64
	- 8->8 pointer to param 1
	- 8->8 pointer to param 2
	- 8->8 pointer to result
0. MUL-S-8
	- 8->1 pointer to param 1
	- 8->1 pointer to param 2
	- 8->1 pointer to result
0. MUL-S-16
	- 8->2 pointer to param 1
	- 8->2 pointer to param 2
	- 8->2 pointer to result
0. MUL-S-32
	- 8->4 pointer to param 1
	- 8->4 pointer to param 2
	- 8->4 pointer to result
0. MUL-S-64
	- 8->8 pointer to param 1
	- 8->8 pointer to param 2
	- 8->8 pointer to result
0. MUL-F
	- 8->4 pointer to param 1
	- 8->4 pointer to param 2
	- 8->4 pointer to result
0. MUL-D
	- 8->8 pointer to param 1
	- 8->8 pointer to param 2
	- 8->8 pointer to result
0. DIV-U-8
	- 8->1 pointer to param 1
	- 8->1 pointer to param 2
	- 8->1 pointer to result
0. DIV-U-16
	- 8->2 pointer to param 1
	- 8->2 pointer to param 2
	- 8->2 pointer to result
0. DIV-U-32
	- 8->4 pointer to param 1
	- 8->4 pointer to param 2
	- 8->4 pointer to result
0. DIV-U-64
	- 8->8 pointer to param 1
	- 8->8 pointer to param 2
	- 8->8 pointer to result
0. DIV-S-8
	- 8->1 pointer to param 1
	- 8->1 pointer to param 2
	- 8->1 pointer to result
0. DIV-S-16
	- 8->2 pointer to param 1
	- 8->2 pointer to param 2
	- 8->2 pointer to result
0. DIV-S-32
	- 8->4 pointer to param 1
	- 8->4 pointer to param 2
	- 8->4 pointer to result
0. DIV-S-64
	- 8->8 pointer to param 1
	- 8->8 pointer to param 2
	- 8->8 pointer to result
0. DIV-F
	- 8->4 pointer to param 1
	- 8->4 pointer to param 2
	- 8->4 pointer to result
0. DIV-D
	- 8->8 pointer to param 1
	- 8->8 pointer to param 2
	- 8->8 pointer to result
0. BIT-AND-8
	- 8->1 pointer to param 1
	- 8->1 pointer to param 2
	- 8->1 pointer to result
0. BIT-AND-16
	- 8->2 pointer to param 1
	- 8->2 pointer to param 2
	- 8->2 pointer to result
0. BIT-AND-32
	- 8->4 pointer to param 1
	- 8->4 pointer to param 2
	- 8->4 pointer to result
0. BIT-AND-64
	- 8->8 pointer to param 1
	- 8->8 pointer to param 2
	- 8->8 pointer to result
0. BIT-OR-8
	- 8->1 pointer to param 1
	- 8->1 pointer to param 2
	- 8->1 pointer to result
0. BIT-OR-16
	- 8->2 pointer to param 1
	- 8->2 pointer to param 2
	- 8->2 pointer to result
0. BIT-OR-32
	- 8->4 pointer to param 1
	- 8->4 pointer to param 2
	- 8->4 pointer to result
0. BIT-OR-64
	- 8->8 pointer to param 1
	- 8->8 pointer to param 2
	- 8->8 pointer to result
0. BIT-XOR-8
	- 8->1 pointer to param 1
	- 8->1 pointer to param 2
	- 8->1 pointer to result
0. BIT-XOR-16
	- 8->2 pointer to param 1
	- 8->2 pointer to param 2
	- 8->2 pointer to result
0. BIT-XOR-32
	- 8->4 pointer to param 1
	- 8->4 pointer to param 2
	- 8->4 pointer to result
0. BIT-XOR-64
	- 8->8 pointer to param 1
	- 8->8 pointer to param 2
	- 8->8 pointer to result
0. BIT-NOT-8
	- 8->1 pointer to param
	- 8->1 pointer to result
0. BIT-NOT-16
	- 8->2 pointer to param
	- 8->2 pointer to result
0. BIT-NOT-32
	- 8->4 pointer to param
	- 8->4 pointer to result
0. BIT-NOT-64
	- 8->8 pointer to param
	- 8->8 pointer to result
0. BIT-SHIFTL-8
	- 8->1 pointer to param 1
	- 8->1 pointer to param 2
	- 8->1 pointer to result
0. BIT-SHIFTL-16
	- 8->2 pointer to param 1
	- 8->1 pointer to param 2
	- 8->2 pointer to result
0. BIT-SHIFTL-32
	- 8->4 pointer to param 1
	- 8->1 pointer to param 2
	- 8->4 pointer to result
0. BIT-SHIFTL-64
	- 8->8 pointer to param 1
	- 8->1 pointer to param 2
	- 8->8 pointer to result
0. BIT-SHIFTR-8
	- 8->1 pointer to param 1
	- 8->1 pointer to param 2
	- 8->1 pointer to result
0. BIT-SHIFTR-16
	- 8->2 pointer to param 1
	- 8->1 pointer to param 2
	- 8->2 pointer to result
0. BIT-SHIFTR-32
	- 8->4 pointer to param 1
	- 8->1 pointer to param 2
	- 8->4 pointer to result
0. BIT-SHIFTR-64
	- 8->8 pointer to param 1
	- 8->1 pointer to param 2
	- 8->8 pointer to result
0. LOG-AND
	- 8->1 pointer to param 1
	- 8->1 pointer to param 2
	- 8->1 pointer to result
0. LOG-OR
	- 8->1 pointer to param 1
	- 8->1 pointer to param 2
	- 8->1 pointer to result
0. LOG-XOR
	- 8->1 pointer to param 1
	- 8->1 pointer to param 2
	- 8->1 pointer to result
0. LOG-NOT
	- 8->1 pointer to param
	- 8->1 pointer to result
0. EQUAL-8
	- 8->1 pointer to param 1
	- 8->1 pointer to param 2
	- 8->1 pointer to result
0. EQUAL-16
	- 8->2 pointer to param 1
	- 8->2 pointer to param 2
	- 8->1 pointer to result
0. EQUAL-32
	- 8->4 pointer to param 1
	- 8->4 pointer to param 2
	- 8->1 pointer to result
0. EQUAL-64
	- 8->8 pointer to param 1
	- 8->8 pointer to param 2
	- 8->1 pointer to result
0. EQUAL-F
	- 8->4 pointer to param 1
	- 8->4 pointer to param 2
	- 8->1 pointer to result
0. EQUAL-D
	- 8->8 pointer to param 1
	- 8->8 pointer to param 2
	- 8->1 pointer to result
0. GTHAN-U-8
	- 8->1 pointer to param 1
	- 8->1 pointer to param 2
	- 8->1 pointer to result
0. GTHAN-U-16
	- 8->2 pointer to param 1
	- 8->2 pointer to param 2
	- 8->1 pointer to result
0. GTHAN-U-32
	- 8->4 pointer to param 1
	- 8->4 pointer to param 2
	- 8->1 pointer to result
0. GTHAN-U-64
	- 8->8 pointer to param 1
	- 8->8 pointer to param 2
	- 8->1 pointer to result
0. GTHAN-S-8
	- 8->1 pointer to param 1
	- 8->1 pointer to param 2
	- 8->1 pointer to result
0. GTHAN-S-16
	- 8->2 pointer to param 1
	- 8->2 pointer to param 2
	- 8->1 pointer to result
0. GTHAN-S-32
	- 8->4 pointer to param 1
	- 8->4 pointer to param 2
	- 8->1 pointer to result
0. GTHAN-S-64
	- 8->8 pointer to param 1
	- 8->8 pointer to param 2
	- 8->1 pointer to result
0. GTHAN-F
	- 8->4 pointer to param 1
	- 8->4 pointer to param 2
	- 8->1 pointer to result
0. GTHAN-D
	- 8->8 pointer to param 1
	- 8->8 pointer to param 2
	- 8->1 pointer to result
0. LTHAN-U-8
	- 8->1 pointer to param 1
	- 8->1 pointer to param 2
	- 8->1 pointer to result
0. LTHAN-U-16
	- 8->2 pointer to param 1
	- 8->2 pointer to param 2
	- 8->1 pointer to result
0. LTHAN-U-32
	- 8->4 pointer to param 1
	- 8->4 pointer to param 2
	- 8->1 pointer to result
0. LTHAN-U-64
	- 8->8 pointer to param 1
	- 8->8 pointer to param 2
	- 8->1 pointer to result
0. LTHAN-S-8
	- 8->1 pointer to param 1
	- 8->1 pointer to param 2
	- 8->1 pointer to result
0. LTHAN-S-16
	- 8->2 pointer to param 1
	- 8->2 pointer to param 2
	- 8->1 pointer to result
0. LTHAN-S-32
	- 8->4 pointer to param 1
	- 8->4 pointer to param 2
	- 8->1 pointer to result
0. LTHAN-S-64
	- 8->8 pointer to param 1
	- 8->8 pointer to param 2
	- 8->1 pointer to result
0. LTHAN-F
	- 8->4 pointer to param 1
	- 8->4 pointer to param 2
	- 8->1 pointer to result
0. LTHAN-D
	- 8->8 pointer to param 1
	- 8->8 pointer to param 2
	- 8->1 pointer to result
0. SKIP-8
	- 1 bytes to skip cursor
0. SKIP-16
	- 2 bytes to skip cursor
0. SKIP-32
	- 4 bytes to skip cursor
0. SKIP-64
	- 8 bytes to skip cursor


