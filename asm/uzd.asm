.model small

.stack 100h

.data
    ;u_aa db 0Ch, 04h, 08h, 05h
    ;u_cc db 0Ch, 04h, 08h, 0Dh

	msg_inp db 10, "Simboliai: ", 10, 13, "$"
    msg_otp db 10, "ASCII simboliai sesioliktainiu pavidalu: ", 10, 13, "$"
    hex_symbols db "0123456789ABCDEF"
    newline db 10, 13, "$" 

    input_buf db 255
        db 0
        db 255 dup(0)

.code
Pradzia:
	mov	ax, @data
	mov	ds, ax			; Kad ds rodytų į duomenų segmento pradžią

	lea	dx, msg_inp  ; Nuoroda į žinutės adresą
    call Write

	mov	ah, 0Ah		; Simboliu skaitymas
    lea dx, input_buf 
    int 21h ;interuptas

    lea	dx, msg_otp ; Nuoroda į žinutės adresą
	call Write

    mov cl, [input_buf + 1]  ; Buferio ilgis
    lea si, input_buf + 2     ; Nuoroda į pirmą simbolį buferyje

    print_loop:
        mov dl, [si]            ;gaunamas simbolį iš buferio
        call print_hex
        
        lea dx, newline         
        call Write

        inc si                  ; Pereiti prie kito simbolio
        dec cl                  ; Sumažinti skaitliuką
        jnz print_loop          ; Jei dar yra simbolių, tęsti

    mov ax, 04c00h          ; Programos pabaiga
    int 21h

Write PROC
    push ax

    mov ah, 09h
    int 21h ;išvedimas į ekraną

    pop ax
    ret
Write ENDP

print_hex PROC

    mov ch, 0
    push dx
    push 1  ;flagas

    find_hex_u:
        mov bx, dx      ;įvestas simbolis perkeliamas į bx

        and bx, 00F0h   ;pasilieka tik 3 hex raidė
        shr bl, 4       ;X0 -> 0X
        cmp bl, ch      ;tikrinimas
        je print_char

        inc ch          ;int i = 0; i < 16; i++ atitikmuo
        mov ah, 0Fh
        sub ah, ch

        jnz find_hex_u

    print_u:
    mov ch, 0h
    pop dx
    push 0

    find_hex_l:
        mov bx, dx      
        and bl, 000Fh   ;pasilieka tik 4 hex raidė
        cmp bl, ch
        je print_char

        inc ch
        mov ah, 0Fh
        sub ah, ch

        jnz find_hex_l

print_l:
    ret

print_hex ENDP

print_char:

    mov ah, 02h         ;spausdinamas 1 simbolis
    lea di, hex_symbols ;paruošiama hex sibolių eilė

    mov bl, ch          ;ch perkeliamas į bl
    and bh, 0           ;išvalomas bh
    add di, bx          ;nustatoma norima pozicija
    mov dl, [di]        ;į spausdinimo vietą įstatomas simbolis
    int 21h

    pop bx              
    and bx, 01h
    cmp bx, 1

    je print_u          ;jei b = 1 pereinama į 2 raidės spausdinimą, jei 0 tai pereinama į galą
    jmp print_l

end Pradzia
