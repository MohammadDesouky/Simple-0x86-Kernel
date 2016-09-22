@echo off


set "crpth=%cd%"

nasm "Assembly/BootLoader.asm" -f bin -o "CU FOS OS/BootLoader.bin"
nasm "Assembly/AssemblyToCInterface.asm" -f elf32 -o "Assembly/ASMInterface.o"
nasm "Assembly/KernelEntryPoint.asm" -f elf32 -o "Assembly/KernelEntryPoint.o"
 


i686-elf-gcc.exe  -Wall -ffreestanding -I "%crpth%\Include"  -c "%crpth%\Library\Memory.c" -o "%crpth%\Library\Memory.o" 
i686-elf-gcc.exe  -Wall -ffreestanding -I "%crpth%\Include"  -c  "%crpth%\Library\IO.c" -o  "%crpth%\Library\IO.o"
i686-elf-gcc.exe  -Wall -ffreestanding -I  "%crpth%\Include"  -c  "%crpth%\Library\String.c" -o  "%crpth%\Library\String.o"
i686-elf-gcc.exe  -Wall -ffreestanding -I "%crpth%\Include"  -c  "%crpth%\Library\RTC.c" -o  "%crpth%\Library\RTC.o"
i686-elf-gcc.exe  -Wall -ffreestanding -I "%crpth%\Include"  -c  "%crpth%\Library\Restart.c" -o  "%crpth%\Library\Restart.o"

i686-elf-gcc.exe  -Wall -ffreestanding -I "%crpth%\Include"  -c "%crpth%\Hardware\0x86 CPU\GDT.c" -o  "%crpth%\Hardware\0x86 CPU\GDT.o"
i686-elf-gcc.exe  -Wall -ffreestanding -I "%crpth%\Include"  -c  "%crpth%\Hardware\0x86 CPU\IDT.c" -o  "%crpth%\Hardware\0x86 CPU\IDT.o"
i686-elf-gcc.exe  -Wall -ffreestanding -I "%crpth%\Include"  -c  "%crpth%\Hardware\0x86 CPU\IRQs.c" -o  "%crpth%\Hardware\0x86 CPU\IRQs.o"
i686-elf-gcc.exe  -Wall -ffreestanding -I "%crpth%\Include"  -c  "%crpth%\Hardware\0x86 CPU\ISRs.c" -o  "%crpth%\Hardware\0x86 CPU\ISRs.o"
i686-elf-gcc.exe  -Wall -ffreestanding -I "%crpth%\Include"  -c  "%crpth%\Hardware\0x86 CPU\Timer.c" -o  "%crpth%\Hardware\0x86 CPU\Timer.o"
i686-elf-gcc.exe  -Wall -ffreestanding -I "%crpth%\Include"  -c  "%crpth%\Hardware\Basic Drivers\USKeyboard.c" -o  "%crpth%\Hardware\Basic Drivers\USKeyboard.o"
i686-elf-gcc.exe  -Wall -ffreestanding -I "%crpth%\Include"  -c  "%crpth%\Hardware\Basic Drivers\VGA.c" -o  "%crpth%\Hardware\Basic Drivers\VGA.o"

i686-elf-gcc.exe   -Wall -ffreestanding   -I "%crpth%\Include" -c "%crpth%\Kernel\TheKernel.c" -o "%crpth%\Kernel\TheKernel.o"


i686-elf-gcc.exe  -Wall -ffreestanding -I "%crpth%\Include"  -c "%crpth%\Apps [Kernel Mode]\Main.c" -o "%crpth%\Apps [Kernel Mode]\Main.o"


i686-elf-gcc.exe -o "%crpth%\CU FOS OS\Kernel.bin"  -T link.ld  "%crpth%\Assembly\KernelEntryPoint.o" "%crpth%\Assembly\ASMInterface.o" "%crpth%\Apps [Kernel Mode]\Main.o"  "%crpth%\Library\RTC.o"  "%crpth%\Library\Memory.o"  "%crpth%\Library\IO.o"  "%crpth%\Library\String.o"  "%crpth%\Hardware\0x86 CPU\GDT.o"   "%crpth%\Hardware\0x86 CPU\ISRs.o"  "%crpth%\Hardware\0x86 CPU\IDT.o"  "%crpth%\Hardware\0x86 CPU\IRQs.o"   "%crpth%\Hardware\Basic Drivers\VGA.o"  "%crpth%\Library\Restart.o"  "%crpth%\Hardware\Basic Drivers\USKeyboard.o"   "%crpth%\Hardware\0x86 CPU\Timer.o" "%crpth%\Kernel\TheKernel.o" -ffreestanding -nostdlib

del"%crpth%\Kernel\TheKernel.o"
del"%crpth%\Assembly\ASMInterface.o" 
del"%crpth%\Assembly\KernelEntryPoint.o"
del"%crpth%\Hardware\Basic Drivers\VGA.o" 
del"%crpth%\Hardware\0x86 CPU\IDT.o" 
del"%crpth%\Hardware\0x86 CPU\GDT.o"
del"%crpth%\Hardware\0x86 CPU\IRQs.o" 
del"%crpth%\Hardware\0x86 CPU\ISRs.o" 
del"%crpth%\Hardware\0x86 CPU\Timer.o"
del"%crpth%\Hardware\Basic Drivers\USKeyboard.o"
del"%crpth%\Library\Restart.o"
del"%crpth%\Apps [Kernel Mode]\Main.o"
del"%crpth%\Library\Memory.o"  
del"%crpth%\Library\IO.o" 
del"%crpth%\Library\String.o" 
del"%crpth%\Library\RTC.o"

rem copy "%crpth%\CU FOS OS\BootLoader.bin" + "%crpth%\CU FOS OS\Kernel.bin"   "%crpth%\CU FOS OS\OS Binary Image"

copy /b "%crpth%\CU FOS OS\BootLoader.bin" + "%crpth%\CU FOS OS\Kernel.bin"   "%crpth%\CU FOS OS\OS Binary Image" 
rem %crpth%\CU FOS OS\*.bin" "%crpth%\CU FOS OS\OS Binary Image"

echo "Running the emulator..."

qemu-system-i386.exe  "%crpth%\CU FOS OS\OS Binary Image" -m 256M

rem bochs   -f MHM  -q
