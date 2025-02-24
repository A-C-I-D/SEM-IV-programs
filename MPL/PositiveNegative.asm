//Write an ALP to count no. of positive and negative numbers from
the array

section .data
    msg db "ALP to count the number of positive and negative numbers in an array", 10
    msg_len equ $ - msg

    array dq 7222222211111111h, -1111111100000000h, -7999999999999999h, 7FFFFFFFFFFFFFFFh, -1111111106789000h

    msg_pos db 10, "The count of positive numbers is: ", 10
    msg_pos_len equ $ - msg_pos

    msg_neg db 10, 10, "The count of negative numbers is: ", 10
    msg_neg_len equ $ - msg_neg

section .bss
    result resb 16
    pos_count resq 1
    neg_count resq 1

%macro write 2
    mov rax, 1
    mov rdi, 1
    mov rsi, %1
    mov rdx, %2
    syscall
%endmacro

section .text
    global _start

_start:
    mov rcx, 5
    xor rbx, rbx  ; stores positive count
    xor rdx, rdx  ; stores negative count
    mov rsi, array

repeat:
    mov rax, [rsi]
    test rax, rax
    js negative
    inc rbx
    jmp next

negative:
    inc rdx

next:
    add rsi, 8
    loop repeat

    mov [pos_count], rbx
    mov [neg_count], rdx

    write msg, msg_len
    write msg_pos, msg_pos_len
    mov rax, [pos_count]
    call disp

    write msg_neg, msg_neg_len
    mov rax, [neg_count]
    call disp

    mov rax, 60
    xor rdi, rdi
    syscall

disp:
    mov rbx, rax
    mov rdi, result
    mov cx, 2  

up1:
    rol rbx, 4
    mov al, bl
    and al, 0Fh
    cmp al, 9
    jg add_37
    add al, 30h
    jmp skip

add_37:
    add al, 37h

skip:
    mov [rdi], al
    inc rdi
    dec cx
    jnz up1

    write result, 2
    ret
