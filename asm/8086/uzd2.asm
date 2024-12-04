.model small

.stack 256

.data
    ;9 užduotis klevas.mif.vu.lt/~julius/2011Rud/KompArch/Uzd2.html
    ;https://klevas.mif.vu.lt/~linas1/KompArch/AsmProg.pdf
    ;https://www.stanislavs.org/helppc/int_21.html
    ;https://klevas.mif.vu.lt/~linas1/KompArch/modulis-APV.pdf

    newline db 10, 13, "$" 
    debug db 'DEBUG $'
    char db 0
    file_name db 'rez.txt'
    otp_handle dw 0
    i_debug db '0'
    handle dw 0

    err_arg db 'Argumentu nera. Zodziu tipo reik ivesti failu pavadinimus viena po kito atskirtus tarpais.$'
    err_file_open db 'Nepavyko atidaryti failo$'
    err_file_read db 'Nepavyko nuskaityti failo$'
    err_file_find db 'Nepavyko rasti failo$'
    err_file_create db 'Nepavyko sukurti failo$'
    err_file_close db 'Nepavyko uzdaryti failo$'

    arg_msg db "Programos argumentai: "
    arg_msg_len equ $ - arg_msg
    test_name db "test.txt$"

    inp_name_buf db 32
        db 0
        db 32 dup(0)

    input_buf db 255
        db 0
        db 255 dup(0)

.code

 
Pradzia:
    push ds; cia kad ds reiksme veliau galima butu naudoti

    mov	ax, @data
	mov	ds, ax		 ; Kad ds rodytų į duomenų segmento pradžią

    mov cx, arg_msg_len
    lea dx, arg_msg

    pop ds
    mov cl, [es:80h] ; gauti arg eiles ilgi
    mov ch, 0

    cmp cl, 0
    jnz no_args_lb
    lea dx, err_arg
    call error

    no_args_lb:
    mov dx, 82h ; arg eiles pradzios adresas (1 skipinti nes 1 - tarpas)

    call print_buf   

    mov ch, 0     
    push cx

    ;patikrinti ar argai yra /?    
    mov ch, [es:82h] 
    cmp ch, '/'
    jne continue
    mov ch, [es:83h] 
    cmp ch, '?'
    jne continue ; jei nenueina i continue, reiskias argas /?
    lea dx, err_arg
    call error 
    
    continue:
    ; failo sukurimas
    push dx
    push ds
    mov	ax, @data
	mov	ds, ax	
    mov ah, 3Ch
    mov cx, 0
    lea dx, file_name
    int 21h
    pop ds
    pop dx
    jnc create_file_lb
    lea dx, err_file_create
    call error

    create_file_lb:
    mov [otp_handle], ax

    pop cx
    call sep_args

    file_loop:
    
    mov ah, 3Dh ; Failo atidarymas
    mov al, 00000000B
    int 21h
    jnc open_file_lb
    lea dx, err_file_open
    call error

    open_file_lb:
    jmp skip2

    file_loop_boost_2:
    jmp file_loop

    skip2:
    ; name
    mov cx, 16 ; vardo lygiavimo ilgis
    call print_buf_null
    push dx ; issaugoti failo varda
    
    mov [handle], ax ; Issaugoti handle
    mov bx, ax

    ; hexdump
    mov ah, 3fh
    mov cx, 16
    lea dx, input_buf
    int 21h ; Failo skaitymas
    cmp ax, 0
    jnc hexdump_lb ; Jei nieko nebuvo perskaityta
    lea dx, err_file_read
    call error

    hexdump_lb:
    mov cx, ax
    call print_buf_hex
    
    ; attributes
    mov ax, 4300h
    pop dx ; atgauti failo varda
    push dx
    int 21h
    cmp ax, 0
    jnc attr_lb ; Jei nieko nebuvo perskaityta
    lea dx, err_file_read
    call error

    attr_lb:
    mov dx, cx
    call print_attr
    jmp skip1

    file_loop_boost_1:
    jmp file_loop_boost_2

    skip1:
    ; date and time
    mov bx, [handle]
    mov ax, 5700h
    int 21h
    cmp ax, 0
    jnc date_lb ; Jei nieko nebuvo perskaityta
    lea dx, err_file_read
    call error

    date_lb:
    call print_date
    mov dx, cx
    call print_time

    ;size
    mov ah, 42h ; pajudinti failo pointeri
    mov bx, [handle]
    mov al, 2 ; pajudinti fp i EOF
    mov cx, 0
    mov dx, 0
    int 21h ; dx:ax - dydis 
    jnc size_lb ; Jei nerado failo
    lea dx, err_file_find
    call error

    size_lb:
    mov bx, 0
    call print_dec ; max dydis 2^16 baitu

    mov dl, 10
    call print_dl

    mov bx, [handle]
    mov ah, 3Eh ; Uzdaryti faila
    int 21h
    jnc close_lb
    lea dx, err_file_close
    call error

    close_lb:

    ; pereiti prie kito argumento
    pop dx
    next_arg_loop:
        inc dx
        mov di, dx
        mov al, [ds:di]
        cmp al, 0
        jne next_arg_loop

    inc dx
    mov cl, [es:80h]
    mov bl, dl
    sub bl, 80h
    cmp cl, bl ; jei dx pozicija toliau nei nurodytas kiekis - argai baigesi
    jg file_loop_boost_1

    call Exit   

Exit PROC    
    mov bx, [otp_handle]
    mov ah, 3Eh ; Uzdaryti faila
    int 21h
    mov bx, 0
    mov ah, 4Ch ; Programos pabaiga
    int 21h

Exit ENDP

error PROC
    mov	ax, @data
	mov	ds, ax
    mov ah, 09h
    int 21h  
    call Exit
error ENDP

sep_args PROC
    push dx ; issaugoti pradine dx pozicija
    separate_args:
        mov di, dx 
        mov al, [es:di] 
        cmp al, ' '
        jne replace_space_not
        mov byte ptr [es:di], 0
        replace_space_not:
        cmp al, 0Dh
        je separate_args_end
        inc dx
        jmp separate_args

    separate_args_end:
    mov byte ptr [es:di], 0
    pop dx ; grazinti pradine dx pozicija
    ret
sep_args ENDP

print_date PROC
    push ax 
    push bx
    push cx
    push dx

    ; year - 1980
    pop dx
    push dx
    and dx, 1111111000000000B
    mov cl, 9
    shr dx, cl
    add dx, 1980 ; pataisymas
    mov ax, dx
    call print_dec

    mov dl, '-'
    call print_dl

    ; month
    pop dx
    push dx
    and dx, 0000000111100000B
    mov cl, 5
    shr dx, cl
    mov ax, dx
    call print_dec

    mov dl, '-'
    call print_dl

    ; day
    pop dx
    push dx
    and dx, 0000000000011111B
    mov ax, dx
    call print_dec

    mov dl, ' '
    call print_dl

    pop dx
    pop cx
    pop bx
    pop ax
    ret
print_date ENDP

print_time PROC
    push ax 
    push bx
    push cx
    push dx

    ; hour
    pop dx
    push dx
    and dx, 1111100000000000B
    mov cl, 11
    shr dx, cl
    mov ax, dx
    call print_dec

    mov dl, ':'
    call print_dl

    ; minute
    pop dx
    push dx
    and dx, 0000011111100000B
    mov cl, 5
    shr dx, cl
    mov ax, dx
    call print_dec

    mov dl, ':'
    call print_dl

    ; second
    pop dx
    push dx
    and dx, 0000000000011111B
    mov cl, 1
    shl dx, cl ; *2 pataisymas (sekundes saugomos 2s intervalais)
    mov ax, dx
    call print_dec

    mov dl, ' '
    call print_dl

    pop dx
    pop cx
    pop bx
    pop ax
    ret
print_time ENDP

print_attr PROC
    push ax 
    push bx
    push cx
    push dx
    ;galejau glaudziau bet px

    ;archive
    pop dx
    push dx
    and dx, 100000B
    cmp dx, 0
    jz print_attr_1F

    mov dl, 'a'    
    jmp print_attr_1T

    print_attr_1F:
    mov dl, '-'

    print_attr_1T:
    call print_dl

    mov dl, '-'
    call print_dl
    call print_dl

    ;system
    pop dx
    push dx
    and dx, 000100B
    cmp dx, 0
    jz print_attr_2F

    mov dl, 's'    
    jmp print_attr_2T

    print_attr_2F:
    mov dl, '-'

    print_attr_2T:
    call print_dl

    ;hidden
    pop dx
    push dx
    and dx, 000010B
    cmp dx, 0
    jz print_attr_3F

    mov dl, 'h'    
    jmp print_attr_3T

    print_attr_3F:
    mov dl, '-'

    print_attr_3T:
    call print_dl

    ;readonly
    pop dx
    push dx
    and dx, 000001B
    cmp dx, 0
    jz print_attr_4F

    mov dl, 'r'    
    jmp print_attr_4T

    print_attr_4F:
    mov dl, '-'

    print_attr_4T:
    call print_dl

    mov dl, ' '
    call print_dl  

    pop dx
    pop cx
    pop bx
    pop ax
    ret
print_attr ENDP

print_buf PROC
    push ax ; Issaugoti registrus
    push bx

    mov ah, 40h
    mov bx, 1
    int 21h ; isvedimas 

    pop bx
    pop ax
    ret
print_buf ENDP

print_buf_null PROC
    push ax
    push bx
    push cx ; cx krc bus ilgis lygiuotei
    push dx

    mov cx, 0
    print_buf_loop: ; gauti ilgi iki null byte
        mov di, dx
        mov al, [ds:di]
        cmp al, 0
        je print_buf_end
        inc dx
        inc cx
        jmp print_buf_loop

    print_buf_end:
    sub dx, cx
    mov ah, 40h
    mov bx, [otp_handle]
    int 21h 

    mov ax, cx
    pop dx
    pop cx
    push dx
    print_buf_loop_sp:
        mov dl, ' '
        call print_dl

        inc ax
        cmp ax, cx
        jl print_buf_loop_sp

    pop dx

    pop bx
    pop ax
    ret
print_buf_null ENDP

print_buf_hex PROC
    push ax 
    push bx
    push cx
    push dx

    loop_print:  
        mov di, dx
        mov al, [ds:di] ; paloadinti 1 baita
        inc dx

        call print_hex_nibble

        push dx
        mov dl, ' '
        call print_dl
        pop dx

        dec cx ; patikrinti ar baigiasi stringas
        cmp cx, 0
        jne loop_print

    pop dx
    pop cx
    pop bx
    pop ax

    ret
print_buf_hex ENDP

print_dl PROC
    push ax 
    push bx
    push cx
    push dx

    mov [char], dl
    lea dx, char
    mov bx, [otp_handle]
    mov cx, 1
    mov ah, 40h
    int 21h

    pop dx
    pop cx
    pop bx
    pop ax
    ret
print_dl ENDP

print_hex_nibble PROC
    mov ah, al ; issaugoti al i ah kad veliau butu
    push cx    
    mov cl, 4     
    shr al, cl ; pashiftinti XY -> 0X
    mov cx, 1

    print_hex_nibble_s:
    ; jei al 0-9
    cmp al, 9
    jbe num

    ; jei A-F
    add al, 37h ; 'A' - 10h
    jmp print

    num:
        add al, '0'

    print:
        mov dl, al
        call print_dl

    cmp cx, 0
    jz print_hex_nibble_end
    mov al, ah
    and al, 0Fh           ; XY -> 0Y
    mov cx, 0
    jmp print_hex_nibble_s

    print_hex_nibble_end:
    pop cx
    ret
print_hex_nibble ENDP

print_dec PROC
	push ax
    push bx
	push cx
	push dx

    cmp ax, 9
    jg start_div

    push ax
    mov dl, '0'
    call print_dl ; atspausdinti leading 0
    pop ax

    start_div:

	mov	cx, 10		
	push "#" ; kad printinant is steko galima rasti pabaiga
    divide:
        mov	dx, 0		
        div	cx ; {DX,AX}/10 = AX + liekana DX)
        push dx		
        cmp	ax, 0		
        ja divide ; jei ne visas skaicius kartoti

	mov	ah, 2		
    print_dec_loop:
        pop	dx		
        cmp	dx, "#"	
        je	print_dec_end		
        add	dl, '0'		; liekana
        call print_dl
        jmp	print_dec_loop	

    print_dec_end:
	
	pop	dx
	pop	cx
    pop bx
	pop	ax

    ret
print_dec ENDP

debug_print PROC
    push ax
    push dx
    push ds

    mov	ax, @data
	mov	ds, ax

    mov ah, 9h
    lea dx, newline
    int 21h

    mov ah, 9h ; eilutes isvedimas
    lea dx, debug
    int 21h

    mov ah, 2h
    mov dl, i_debug
    int 21h

    mov ah, 9h
    lea dx, newline
    int 21h

    inc i_debug

    pop ds
    pop dx
    pop ax
    ret
debug_print ENDP

END Pradzia