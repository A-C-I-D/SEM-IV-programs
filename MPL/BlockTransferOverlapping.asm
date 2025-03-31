section .data
    ; Messages for output
    msg_prompt db "Overlapped Block Transfer using String Instructions:", 10
    msg_len equ $-msg_prompt

    msg_before db "Before Block Transfer:", 10
    msg_before_len equ $-msg_before

    msg_after db "After Block Transfer:", 10
    msg_after_len equ $-msg_after

    ; Source and destination block, they will overlap in memory
    sblock db 0x01, 0x02, 0x03, 0x04, 0x05  ; Source Block
    dblock db 0x00, 0x00, 0x00, 0x00, 0x00  ; Destination Block

section .bss
    result resb 5  ; Reserve 5 bytes for results

section .text
    global _start

_start:
    ; Print the prompt message
    mov rsi, msg_prompt
    mov rdx, msg_len
    call print

    ; Print the "Before Block Transfer" message
    mov rsi, msg_before
    mov rdx, msg_before_len
    call print

    ; Print source block (before transfer)
    mov rsi, sblock
    call print_block

    ; Print destination block (before transfer)
    mov rsi, dblock
    call print_block

    ; Perform the overlapped block transfer
    ; Set direction flag for forward transfer (clear the direction flag)
    cld
    ; Move data from source (sblock) to destination (dblock)
    mov rsi, sblock  ; Source
    mov rdi, dblock  ; Destination
    mov rcx, 5       ; Number of bytes to transfer
    rep movsb        ; Perform the transfer

    ; Print the "After Block Transfer" message
    mov rsi, msg_after
    mov rdx, msg_after_len
    call print

    ; Print source block (after transfer)
    mov rsi, sblock
    call print_block

    ; Print destination block (after transfer)
    mov rsi, dblock
    call print_block

    ; Exit program
    mov rax, 60  ; sys_exit
    mov rdi, 0   ; exit code 0
    syscall

;----------------------------------------------------------------------
; Print function to print messages
; Arguments: rsi = pointer to the message, rdx = length of the message
print:
    mov rax, 1       ; sys_write
    mov rdi, 1       ; file descriptor (stdout)
    syscall
    ret

;----------------------------------------------------------------------
; Print a block of data (5 bytes) as hexadecimal values
; Arguments: rsi = pointer to the block (e.g., sblock or dblock)
print_block:
    mov rcx, 5      ; We have 5 bytes to print
    mov rbx, rsi    ; Save pointer to source block

.print_loop:
    mov al, [rsi]   ; Load byte from source block
    call print_byte ; Print byte as hex
    inc rsi         ; Move to the next byte
    loop .print_loop
    ret

;----------------------------------------------------------------------
; Print a byte as a two-digit hexadecimal value
print_byte:
    ; Convert the byte (al) into hexadecimal and print
    ; We'll print each nibble (4 bits) as a character

    ; Print high nibble
    mov bl, al
    shr bl, 4
    call print_nibble

    ; Print low nibble
    mov bl, al
    and bl, 0x0F
    call print_nibble
    ret

;----------------------------------------------------------------------
; Print a nibble (4 bits) as a hexadecimal character
print_nibble:
    add bl, '0'      ; Convert to ASCII
    cmp bl, '9'      ; Check if it's greater than '9'
    jg .convert_to_upper
    jmp .done

.convert_to_upper:
    add bl, 7        ; Adjust for 'A' to 'F' range

.done:
    mov [result], bl ; Store the result character
    mov rsi, result  ; Load the result to print
    mov rdx, 1       ; Length of 1 byte (the character)
    call print
    ret
