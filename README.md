# Calculator
Between Binary, Octal, Hexadecimal and Decimal

The program performs addition, subtraction and multiplication in binary, octal, hexadecimal and decimal formats. It consists of two functions : generateDec and Formatter, in addition to main. The first function generates a decimal for the input and then the calculations are performed on the decimals, and the result is passed into the Formatter function , which converts the decimal into the output base.

Example input and output:

$ ./calc “*” d5 d10 d
d50

$ ./calc “+” x3C b1010 o
o106

$ ./calc “-“ -d5 -d3 d
-d2
