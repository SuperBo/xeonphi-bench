# mark_description "Intel(R) C Intel(R) 64 Compiler for applications running on Intel(R) MIC Architecture, Version 16.0.1.150 Bu";
# mark_description "ild 20151021";
# mark_description "-mmic -S -fsource-asm";
	.file "test_prefetch.c"
	.text
..TXTST0:
# -- Begin  main
	.text
# mark_begin;
# Threads 4
        .align    16,0x90
	.globl main
# --- main(int, char **)
main:
# parameter 1: %edi
# parameter 2: %rsi
..B1.1:                         # Preds ..B1.0 Latency 9

### int main(int argc, char* argvs[]){

	.cfi_startproc
..___tag_value_main.1:
..L2:
                                                          #4.34
        pushq     %rbp                                          #4.34
	.cfi_def_cfa_offset 16
        movq      %rsp, %rbp                                    #4.34
	.cfi_def_cfa 6, 16
	.cfi_offset 6, -16
        andq      $-128, %rsp                                   #4.34
        subq      $128, %rsp                                    #4.34 c1
        xorl      %esi, %esi                                    #4.34 c1
        movl      $3, %edi                                      #4.34 c5
        call      __intel_new_feature_proc_init                 #4.34 c9
                                # LOE rbx r12 r13 r14 r15
..B1.6:                         # Preds ..B1.1 Latency 7
        stmxcsr   (%rsp)                                        #4.34 c1

###     int a [128];
###     int i,j;
### 
###     #pragma prefetch a:1:16
###     for (i = 0; i < 64; i++){
###         a[i] = 1 + 2;
###     }
### 
###     #pragma prefetch a:1:16
###     for (i = 0; i < 64; i++){
###         for (j = 0; j < 32; j++)

        xorb      %al, %al                                      #15.9 c2
        orl       $32832, (%rsp)                                #4.34 c2
        ldmxcsr   (%rsp)                                        #4.34 c6

###             a[i] = 2 + 2;

        vmovaps   .L_2il0floatpacket.1(%rip), %zmm0             #16.20 c7
                                # LOE rbx r12 r13 r14 r15 al zmm0
..B1.2:                         # Preds ..B1.2 ..B1.6 Latency 5
        incb      %al                                           #15.9 c1
        cmpb      $32, %al                                      #15.9 c5
        jb        ..B1.2        # Prob 98%                      #15.9 c5
                                # LOE rbx r12 r13 r14 r15 al zmm0
..B1.3:                         # Preds ..B1.2 Latency 5

###     }
### 
###     #pragma noprefetch a
###     for (i = 0; i < 64; i++){
###         a[i] = 2 + 2;
###     }
### 
###     #pragma noprefetch a
###     for (i = 0; i < 64; i++){
###         for (j = 0; j < 32; j++)
###             a[i] = 2 + 2;
###     }
### 
###     return 0;

        xorl      %eax, %eax                                    #30.12 c1
        movq      %rbp, %rsp                                    #30.12 c5
        popq      %rbp                                          #30.12
	.cfi_def_cfa 7, 8
	.cfi_restore 6
        ret                                                     #30.12
        .align    16,0x90
	.cfi_endproc
                                # LOE
# mark_end;
	.type	main,@function
	.size	main,.-main
	.data
# -- End  main
	.section .rodata, "a"
	.align 64
	.align 64
.L_2il0floatpacket.0:
	.long	0x00000003,0x00000003,0x00000003,0x00000003,0x00000003,0x00000003,0x00000003,0x00000003,0x00000003,0x00000003,0x00000003,0x00000003,0x00000003,0x00000003,0x00000003,0x00000003
	.type	.L_2il0floatpacket.0,@object
	.size	.L_2il0floatpacket.0,64
	.align 64
.L_2il0floatpacket.1:
	.long	0x00000004,0x00000004,0x00000004,0x00000004,0x00000004,0x00000004,0x00000004,0x00000004,0x00000004,0x00000004,0x00000004,0x00000004,0x00000004,0x00000004,0x00000004,0x00000004
	.type	.L_2il0floatpacket.1,@object
	.size	.L_2il0floatpacket.1,64
	.data
	.section .note.GNU-stack, ""
// -- Begin DWARF2 SEGMENT .eh_frame
	.section .eh_frame,"a",@progbits
.eh_frame_seg:
	.align 8
# End
