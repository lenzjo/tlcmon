# TLC6502 #
## Introduction ##
This is a project I started in June of 2021. It was inspired by the [RC6502](https://hvetebolle.blogspot.com/2017/08/rc6502-apple-1-replica-sbc.html) Apple 1 replica board. Initially, I bought the all in one pcb on Ebay and played with it for a few days to get a feel for it. It was nice enough but I wasn't really interested in Apple or basic and hardware-wise I didn't care much for using a Nano or the plain old 6502.


## The PCB ##
I wanted a "proper" serial port, a cleaner memory map and a bunch of other things. So I opened up Kicad and started the redesign. It has gone thru a series of iterations as I changed/added stuff. This is the final version of the pcb. Along the way I redesigned the backplane and created a power-supply pcb. Here's a list of all the modifications:

Replaced 6502 with a WD65C02 - To get the extra instructions and higher speed.

Replaced 6821 with a WD65C22S - To get some timers.

Replaced the Nano with a 68B50 and CP2102 - So I don't have to mess withh FTDI cards!

Replaced NE555 with a DS1813 - To get a reliable reset signal.

Replaced MCP23517 with an ATtiny26 (see Daryl Richtor's [AVR PS2 keyboard](http://sbc.rictor.org/pckbavr.html))

Replaced the address decoding logic with an ATF22V10C

Replaced the AT28C64 with an AT28C256 - To get 16K of useable eeprom space.

Replaced the 1Mhz osc. with a 2Mhz osc. - For the go-faster stripes ;)

Added a USB B mini socket (for serial connection), a PS2 socket to plug in a keyboard and I brought out PortB of the 6522 to a pin header (PortA is used by the keyboard).

There are 4 sets of pin headers on the pcb.

1. Left edge: As already mentioned above there is a 12pin header that brings out PortB, CB1, CB2, Vcc and GND.
2. Top left: A 2pin header, so that an external momentary push button can activate a system reset.
3. middle of pcb: A 2 pin header that allows you to connect an external clock source.
4. Bottom:right: A 3 pin header connected to the 28c256 eeprom. These control wether the eeprom is in read-only or write mode.

Only the 62256 and 7400 remain from the original pcb.

All of this was kept within the 100mm x 100mm size for the pcb. Here is the [schematic](pcb/TLC6502-schematic.pdf) and a picture of the [pcb](pcb/TLC6502-pcb.png).


I am also currently working on a version of the TLC6502 that uses the SCC2691 in the hopes of raising the clock from 2 Mhz to 4 or possible 6 Mhz.

## Further expansion ##
This pcb is now finished but I haven't finished working on the hardware yet, I still want to add:

- VGA output
- SPI
- I2C
- Audio output
- Some form of mass storage



## Memory Map ##
$0000-$7FFF  Ram

$8000-$8FFF  Block 1

$9000-$9FFF  Block 2

$A000-$A1FF  IO_Block

$A200-$A21F  UART (68B50/SCC2691)

$A220-$A23F  6522

$C000-$FFFF  Eeprom

Block 1 and 2 are two 4K blocks of memory that might pssibly be used by the VGA interface. The IO_Block is for future hardware devices. All three block signals are brought out to the 39pin edge connector.

 


## The monitor ##
Without firmware the hardware is useless so this is my main focus now. For an assembler I am using [SB-Assembler v3](https://www.sbprojects.net/sbasm/), it is free and is written in Python so it will run on Linux, Mac and PC and I am using [Atom](https://atom.io/) to edit the src code only because there is color highlighting on it for the 6502.

I have already added some basic commands - peek, poke, fill, copy, dump and uptime. On the todo list is the keyboard driver and an x-modem rx and tx so that I can at least upload code. I also need to write the firmware so that I can then program the eeprom in-circuit.

Back in the '80's I came across the book '6502 Systems Programming' by TG Windeknecht. In it he developed an assembler called Brevity. It took a little getting use to as it is extremely terse, but after a while I found it easier and quicker to use than other assemblers. I would like to add this and it's accompanying dis-assembler to the monitor as well.

There will be other functions added as the monitor is developed (project creep??). This repository is here to document that development.

## The Future ##
At the moment I have 2.5 working versions of the TLC6502 ;) . #3 below is almost working, the uart will happily Tx all day long but refuses to Rx... :

1. My main pcb, used for software development. [front](pcb/V1_front.png), [back](pcb/V1_back.png)
2. A version with a backplane, for hardware development. [front](pcb/V2_front.png), [back](pcb/V2_back.png)
3. The SCC2691 version, so that I can work on it's drivers. [pcb](pcb/V3_SSC2691_pcb.png)

The problem is they are all tied, via the terminal interface, to the PC... To be honest, I miss the Sym SBC that I had back then. So, I would like a version that has a hex keypad and LED/LCD display making it a little more portable.