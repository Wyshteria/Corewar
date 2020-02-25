# Corewar

**[42]** group project in C - assembler and virtual machine of Corewar game (in 42's style)

The assignment is to create an assembler, a virtual machine and a simple champion for Corewar game.

## What is ? 
It's a battle royale of champions. The objective of the game is to be the last champion that is alive in the arena.
A champion has a set of instructions that will run when the game start. The champion file is .s type.
```bash 
.name "player1"
.comment "I'm player 1"

alive:
add r2, r2, r2
live %-1
zjmp %:alive
```
An assembler will comply a champion into a byte code or .cor type.
```bash
00000000: 00ea 83f3 706c 6179 6572 3100 0000 0000  ....player1.....
00000010: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000020: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000030: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000040: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000050: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000060: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000070: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000080: 0000 0000 0000 0000 0000 000d 4927 6d20  ............I'm
00000090: 706c 6179 6572 2031 0000 0000 0000 0000  player 1........
000000a0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000000b0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000000c0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000000d0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000000e0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000000f0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000100: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000110: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000120: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000130: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000140: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000150: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000160: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000170: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000180: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000190: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000001a0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000001b0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000001c0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000001d0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000001e0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000001f0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000200: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000210: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000220: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000230: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000240: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000250: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000260: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000270: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000280: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000290: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000002a0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000002b0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000002c0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000002d0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000002e0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000002f0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000300: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000310: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000320: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000330: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000340: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000350: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000360: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000370: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000380: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000390: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000003a0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000003b0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000003c0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000003d0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000003e0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000003f0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000400: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000410: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000420: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000430: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000440: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000450: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000460: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000470: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000480: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000490: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000004a0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000004b0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000004c0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000004d0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000004e0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000004f0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000500: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000510: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000520: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000530: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000540: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000550: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000560: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000570: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000580: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000590: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000005a0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000005b0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000005c0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000005d0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000005e0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000005f0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000600: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000610: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000620: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000630: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000640: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000650: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000660: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000670: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000680: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000690: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000006a0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000006b0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000006c0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000006d0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000006e0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000006f0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000700: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000710: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000720: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000730: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000740: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000750: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000760: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000770: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000780: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000790: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000007a0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000007b0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000007c0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000007d0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000007e0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000007f0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000800: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000810: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000820: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000830: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000840: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000850: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000860: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000870: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000880: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000890: 0454 0202 0201 ffff ffff 09ff f60a       .T............
```
A virtual machine will run the game. It takes .cor files, places each champion in the memory.
The read byte codes, interpret them and run them if it's valid.
The game run until there is a winner.

## How to use

We compile the project : 
```bash
make
```
We compile a champion : **./asm <champion1.s> <...>** 
```bash
./asm champs/srcsok/zork.s champs/srcsok/wave.s
>>>Cor file champs/srcsok/zork.cor generated
>>>Cor file champs/srcsok/wave.cor generated
```
We launch the virtual machine : **./corewar [-dump N] [-n N] <champion1.cor> <...>**
```bash
./corewar champs/srcsok/zork.cor champs/srcsok/wave.cor
>>>Introducing contestants...
>>>* Player 1, weighing 23 bytes, "zork" ("I'M ALIIIIVE") !
>>>* Player 2, weighing 427 bytes, "Wave" ("I'm coming") !
>>>Player 1, "Wave" has won
```
* flag dump - will show the memory of stated cycle
```bash
./corewar -dump 1 champs/srcsok/wave.cor champs/srcsok/zork.cor
>>>Introducing contestants...
>>>* Player 1, weighing 427 bytes, "Wave" ("I'm coming") !
>>>* Player 2, weighing 23 bytes, "zork" ("I'M ALIIIIVE") !
>>>0x0000 : 0b 68 01 00 13 00 01 02 90 03 70 03 01 03 03 70 03 01 c2 01 00 00 00 00 0c 01 ae 03 70 03 01 ba 03 70 03 01 ba 03 70 03 01 ba 03 70 03 01 ba 03 70 03 01 ba 03 70 03 01 ba 03 70 03 01 ba 03 70
>>>0x0040 : 03 01 ba 03 70 03 01 ba 03 70 03 01 ba 03 70 03 01 ba 03 70 03 01 ba 03 70 03 01 ba 03 70 03 01 ba 03 70 03 01 ba 03 70 03 01 ba 03 70 03 01 ba 03 70 03 01 ba 03 70 03 01 ba 03 70 03 01 ba 03
>>>0x0080 : 70 03 01 ba 03 70 03 01 ba 03 70 03 01 ba 03 70 03 01 ba 03 70 03 01 ba 03 70 03 01 ba 03 70 03 01 ba 03 70 03 01 ba 03 70 03 01 ba 03 70 03 01 ba 03 70 03 01 ba 03 70 03 01 ba 03 70 03 01 ba
>>>0x00c0 : 03 70 03 01 ba 03 70 03 01 ba 03 70 03 01 ba 03 70 03 01 ba 03 70 03 01 ba 03 70 03 01 ba 03 70 03 01 ba 03 70 03 01 ba 03 70 03 01 ba 03 70 03 01 ba 03 70 03 01 ba 03 70 03 01 ba 03 70 03 01
>>>0x0100 : ba 03 70 03 01 ba 03 70 03 01 ba 03 70 03 01 ba 03 70 03 01 ba 03 70 03 01 ba 02 90 00 09 ff f2 08 0b 68 08 fe df 00 00 0b 68 01 00 38 00 01 0b 68 08 ff f9 00 00 0b 68 01 00 45 00 01 0b 68 01
>>>0x0140 : ff f9 00 02 0b 68 01 00 24 00 01 0b 68 01 ff f9 00 02 0b 68 01 00 51 00 01 0b 68 01 ff f9 00 02 01 00 00 00 00 09 ff fb 01 00 00 00 00 09 ff fb 06 a4 00 00 00 00 00 00 00 00 09 01 00 00 00 00
>>>0x0180 : 0c ff fb 01 ff ff fc 18 0c ff d8 01 ff ff fc 18 0c ff d8 01 ff ff fc 18 0c 00 0b 01 ff ff fc 18 09 ff db 01 00 00 00 00 09 fe 6b 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x01c0 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0200 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0240 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0280 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x02c0 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0300 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0340 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0380 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x03c0 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0400 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0440 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0480 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x04c0 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0500 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0540 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0580 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x05c0 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0600 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0640 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0680 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x06c0 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0700 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0740 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0780 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x07c0 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0800 : 0b 68 01 00 0f 00 01 06 64 01 00 00 00 00 01 01 00 00 00 01 09 ff fb 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0840 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0880 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x08c0 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0900 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0940 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0980 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x09c0 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0a00 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0a40 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0a80 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0ac0 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0b00 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0b40 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0b80 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0bc0 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0c00 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0c40 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0c80 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0cc0 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0d00 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0d40 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0d80 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0dc0 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0e00 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0e40 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0e80 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0ec0 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0f00 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0f40 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0f80 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
>>>0x0fc0 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
```
* flag n - will change the number of the player
```bash
./corewar -n 42 champs/srcsok/wave.cor -n 21 champs/srcsok/zork.cor
>>>Introducing contestants...
>>>* Player 42, weighing 427 bytes, "Wave" ("I'm coming") !
>>>* Player 21, weighing 23 bytes, "zork" ("I'M ALIIIIVE") !
>>>Player 42, "Wave" has won
```

## Contributions
* Toliver - virtual machine 
* jates- (me) - assembler 
* lboukrou  - assembler

[42]: https://42.fr/
