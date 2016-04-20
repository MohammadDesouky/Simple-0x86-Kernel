[BITS 32]
[global _start]    ; 3ashan el compiler [D el entry point zy el main f el C++ w el java] 
[extern KernelMain] 

_start:
  call KernelMain  ;mt3arafa f file el C elly bylink el donya d bba3d hwa el linker (ld linker bta3 GNU m3a el GCC), Note: ynfa3 tsta5dm el GCC fel link hwa haysha3'l el LD bardo w y link beh

  hlt ; Halt el processor 3ashan may3mlsh restart
