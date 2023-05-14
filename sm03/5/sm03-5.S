    .text

Test_letter:
    pushl %ebp
    movl %esp, %ebp

test_small:
    cmpl $97, %eax
    jl test_big

    cmpl $122, %eax
    jg test_big

    subl $32, %eax 

    leave
    ret
    
test_big:
    cmpl $65, %eax
    jl continue
    
    cmpl $90, %eax
    jg continue

    addl $32, %eax
    
    leave
    ret

continue:
    leave
    ret



    .global main    
main:
    pushl %ebp
    movl %esp, %ebp

    call getchar

read_first:

    cmpl $10, %eax
    jz next

    addl $1, arr(, %eax, 4)  
    call Test_letter

    addl $1, arr(, %eax, 4)
    call getchar

    jmp read_first       

next:
    call getchar

read_second:
    cmpl $10, %eax
    jz print

    subl $1, arr(, %eax, 4)
    call Test_letter
        
    subl $1, arr(, %eax, 4)
    call getchar 

    jmp read_second

print:
    xor %edx, %edx
print_loop:
    movl arr(, %edx,4), %ecx
    incl %edx

    cmpl $128, %edx
    jz yes
    
    cmpl $33, %edx
    jz print_loop

    cmpl $0, %ecx
    jz print_loop

    cmpl $0, %ecx
    jnz no


no:
    pushl $print_no
    call puts

    xor %eax, %eax
    leave
    ret
    
yes:
    pushl $print_yes
    call puts

    xor %eax, %eax
    leave
    ret


    .bss
arr: .skip 4 * 128

    .section .rodata
print_yes: .asciz "YES"
print_no: .asciz "NO"
