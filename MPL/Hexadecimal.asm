// Write an X86/64 ALP to accept five 64 bit Hexadecimal numbers
from user and store them in an array and display the accepted numbers.

%macro IO 4
    mov rax, %1
    mov rdi, %2
    mov rsi, %3
    mov rdx, %4
    syscall
%endmacro

section .data
    m1 db "Input five 64-bit hexadecimal numbers:", 10
    l1 equ $ - m1
    m2 db "The five 64-bit numbers are:", 10
    l2 equ $ - m2
    m4 db "This program accepts and displays five 64-bit hexadecimal numbers.", 10
    l4 equ $ - m4
    m5 db "Exiting now", 10
    l5 equ $ - m5
    m6 db "Incorrect input error", 10
    l6 equ $ - m6
    newline db 10
    size equ 8
    count equ 5

section .bss
    arr resb 40
    _input resb 17
    _output resb 17

section .text
    global _start

_start:
    IO 1, 1, m4, l4
    IO 1, 1, m1, l1
    mov rcx, count
    mov rdi, arr

input:
    IO 0, 0, _input, 17
    call ascii_to_hex
    mov [rdi], rbx
    add rdi, size
    loop input

    mov rcx, count
    mov rdi, arr

display:
    mov rax, [rdi]
    call hex_to_ascii
    IO 1, 1, newline, 1
    IO 1, 1, _output, 16
    add rdi, size
    loop display

exit:
    IO 1, 1, m5, l5
    mov rax, 60
    xor rdi, rdi
    syscall

error:
    IO 1, 1, m6, l6
    jmp exit

ascii_to_hex:
    mov rsi, _input
    xor rbx, rbx
    mov rcx, 16

convert_loop:
    rol rbx, 4
    mov al, [rsi]
    cmp al, '0'
    jl error
    cmp al, '9'
    jbe digit
    cmp al, 'A'
    jl error
    cmp al, 'F'
    jbe uppercase
    cmp al, 'a'
    jl error
    cmp al, 'f'
    jg error
    sub al, 32
uppercase:
    sub al, 55
    jmp store

digit:
    sub al, 48

store:
    add rbx, rax
    inc rsi
    loop convert_loop
    ret

hex_to_ascii:
    mov rsi, _output + 15
    mov rcx, 16

convert_back:
    xor rdx, rdx
    mov rbx, 16
    div rbx
    cmp dl, 9
    jbe add30
    add dl, 7
add30:
    add dl, 48
    mov [rsi], dl
    dec rsi
    loop convert_back
    ret
