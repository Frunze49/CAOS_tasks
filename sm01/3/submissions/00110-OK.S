    .global main  
fin:    
    call finish  
main:
    call readi32
    and %eax, %eax
    js fin
loop:
    call writei32
    dec %eax
    jge loop
    call finish
