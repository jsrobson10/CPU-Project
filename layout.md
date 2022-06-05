
# Memory

- (0x0000000000000000 -> 0x3fffffffffffffff) Zero
- (0x4000000000000000 -> 0x7fffffffffffffff) Program memory (read only)
- (0x8000000000000000 -> 0xbfffffffffffffff) Stack memory
- (0xc000000000000000 -> 0xffffffffffffffff) I/O

# Register

- 256 64 bit ints

# Instructions

- 0 EXIT
- 1 BREAK
- 2 GOTO
	- 1 condition
	- 1 location 1 if true
	- 1 location 2 if false
	- 1 storage
- 3 EQUAL
	- 1 param 1
	- 1 param 2
	- 1 result

- 4 AND
- 5 OR
- 6 XOR
- 7 NOT

- 8 U-GTHAN
- 9 GTHAN
- 10 U-LTHAN
- 11 LTHAN

- 12 U-MUL
- 13 MUL
- 14 U-DIV
- 15 DIV

- 16 ADD
- 17 SUB
- 18 BIT-RSHIFT
- 19 BIT-LSHIFT

- 20 BIT-AND
- 21 BIT-OR
- 22 BIT-XOR
- 23 BIT-NOT

- 24 SKIP-8
	- 1 bytes
- 25 SKIP-16
	- 2 bytes
- 26 SKIP-32
	- 4 bytes
- 27 SKIP-64
	- 8 bytes

- 28 SLOAD-8
	- 1 location
	- 1 value
- 29 SLOAD-16
	- 1 location
	- 2 value
- 30 SLOAD-32
	- 1 location
	- 4 value
- 31 SLOAD-64
	- 1 location
	- 8 value

- 32 LOAD-8
	- 1 value
	- 1 address
- 33 LOAD-16
- 34 LOAD-32
- 35 LOAD-64

- 36 STORE-8
- 37 STORE-16
- 38 STORE-32
- 39 STORE-64

- 40 FLOAT-ADD
- 41 FLOAT-SUB
- 42 FLOAT-MUL
- 43 FLOAT-DIV

- 44 DOUBLE-ADD
- 45 DOUBLE-SUB
- 46 DOUBLE-MUL
- 47 DOUBLE-DIV

- 48 FLOAT-SQRT
- 49 FLOAT-EQUAL
- 50 FLOAT-GTHAN
- 51 FLOAT-LTHAN

- 52 DOUBLE-SQRT
- 53 DOUBLE-EQUAL
- 54 DOUBLE-GTHAN
- 55 DOUBLE-LTHAN

- 56 FLOAT-TO-UINT
	- 1 from
	- 1 to
- 57 FLOAT-TO-INT
- 58 UINT-TO-FLOAT
- 59 INT-TO-FLOAT

- 60 DOUBLE-TO-UINT
- 61 DOUBLE-TO-INT
- 62 UINT-TO-DOUBLE
- 63 INT-TO-DOUBLE

