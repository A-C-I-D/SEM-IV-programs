// Write an X86/64 ALP to accept a string and to display its
length.

%macro IO 4
    mov rax, %1
    mov rdi, %2
    mov rsi, %3
    mov rdx, %4
    syscall
%endmacro

section .data
    m1 db "Enter a string:", 10
    l1 equ $ - m1
    m2 db "Entered:", 10
    l2 equ $ - m2
    m3 db "Length is:", 10
    l3 equ $ - m3
    m4 db "This program accepts a string and displays its length.", 10
    l4 equ $ - m4
    m5 db "Exiting now", 10
    l5 equ $ - m5
    newline db 10

section .bss
    string resb 50
    count resq 1
    _output resb 16

section .text
    global _start

_start:
    IO 1, 1, m4, l4
    IO 1, 1, m1, l1

input:
    IO 0, 0, string, 50
    dec rax  ; Remove newline character
    mov [count], rax

output:
    IO 1, 1, m2, l2
    IO 1, 1, string, 50
    IO 1, 1, m3, l3
    mov rax, [count]
    call hex_to_dec
    IO 1, 1, _output, 16
    IO 1, 1, newline, 1

exit:
    IO 1, 1, m5, l5
    mov rax, 60
    xor rdi, rdi
    syscall

hex_to_dec:
    mov rsi, _output + 15
    mov rcx, 4
convert:
    xor rdx, rdx
    mov rbx, 10
    div rbx
    add dl, '0'
    mov [rsi], dl
    dec rsi
    dec rcx
    jnz convert
    ret
