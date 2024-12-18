.model small
.stack 100h

.data
    ;14 užduotis 
	;klevas.mif.vu.lt/~julius/2011Rud/KompArch/Uzd3.html
	;https://klevas.mif.vu.lt/~linas1/KompArch/KomKodaiViso.pdf

	prev_IP dw ?
	prev_CS dw ?
	
	regAX dw ?
	regBX dw ?
	regCX dw ?
	regDX dw ?
	regSP dw ?
	regBP dw ?
	regSI dw ?
	regDI dw ?

	opc_code dw ?
	opc_d dw ?
	opc_w dw ?
	opc_mod dw ?
	opc_r1 dw ?
	opc_r2 dw ?
	
	b1 db ?
	b2 db ?
	b3 db ?
	b4 db ?

	n1 dw ?
	n2 dw ?

	reg_r1 dw 0
	reg_r2 dw 0
	reg_of dw 0
	
	step_msg db "Interuptas $"
	sub_msg db " SUB $"
	sub_msg_r db "-SUB $"
	reg_w0_names db "AL$ CL$ DL$ BL$ AH$ CH$ DH$ BH$ "
	reg_w1_names db "AX$ CX$ DX$ BX$ SP$ BP$ SI$ DI$ "
	reg_m1_names db "BX+SI$  BX+DI$  BP+SI$  BP+DI$  SI$     DI$     EF_AD$   BX$     "
	reg_m2_names db "BX+SI$  BX+DI$  BP+SI$  BP+DI$  SI$     DI$        BP$   BX$     "
.code

Pradzia:

	mov ax, @data
	mov ds, ax
	
	;Int 1h nuo 0004 nes po 4 eina
	mov ax, 0 ;Į vector table  reik įrašyti savo duomenis	
	mov es, ax ;es pradzia - vektorių lentelės pradžia
	mov ax, es:[4] ;IP
	mov bx, es:[6] ;CS
	mov prev_CS, bx
	mov prev_IP, ax 

	mov ax, cs
	lea bx, interuptas_inj
	
	;custom reikšmių įrašymas
	mov es:[4h], bx
	mov es:[6h], ax

	pushf 
	pop ax
	or ax, 0000000100000000B ;TF=1
	push ax
	popf  
	;Debugas veikia

	;Testavimas SUB funkcijų
	mov ax, 8414h
	mov bx, 0254h
	mov cx, 0053h
	mov dx, 0001h
	sub cx, ax
	sub cx, dx
	sub bl, dl
	sub bl, cl
	sub bl, dl
	sub ax, bp
	sub di, sp
	sub si, cx
	sub ds:[3967h], sp ;efektyvus adresas
	sub ax, [bx + si]
	sub cx, [bp + di]
	sub [bx + di + 35h], sp
	sub [bp + si + 6924h], dx
	sub [bp + 6h], cx
	sub bl, cl

	pushf
	pop ax
	and ax, 1111111011111111B ;TF=0
	push ax
	popf 
	;Debugas nebeveikia

	;CS ir IP legendinis sugrįžimas
	mov ax, prev_IP
	mov bx, prev_CS
	mov es:[4], ax
	mov es:[6], bx
	
	mov ah, 4Ch
	int 21h


interuptas_inj PROC	
    ;Išsaugoti registrų reikšmes
    mov regAX, ax				
	mov regBX, bx
	mov regCX, cx
	mov regDX, dx
	mov regSP, sp
	mov regBP, bp
	mov regSI, si
	mov regDI, di

    ;Offsetas nuo pradžios
	pop si ;IP -> SI
	pop di ;CS -> DI
	push di
	push si 
	
	;gaunami opkodai ir jei yra extra š
	mov ax, cs:[si]
	mov b1, ah
	mov b2, al
	mov bx, cs:[si+2]
	mov b3, bh
	mov b4, bl

	;call print_AX

	;mov ah, 2
	;mov dl, " "
	;int 21h
	
	;Tikrinama pagal opkodą ar yra sub reg~r/m
	;opkodas 0010 10.. reg r/m  SUB registras -= registras/atmintis
	;Pasirašymai nes paskui pamiršiu
	; B1        B2        B3
	; OOOO OODW MMRR RKKK ... 	O - opkodas 	D - direction 		W - word 	M - mod		R - reg		K - kitas reg (arba m)

	;B1 ir B2 susikeičia vietomis

	push ax
	and ax, 0000000011111100B ;1111 1100 0000 0000
	mov cl, 2
	shr ax, cl
	mov opc_code, ax
	pop ax

	push ax
	and ax, 0000000000000010B ;0000 0010 0000 0000
	mov cl, 1
	shr ax, cl
	mov opc_d, ax
	pop ax

	push ax
	and ax, 0000000000000001B ;0000 0001 0000 0000
	mov cl, 0
	shr ax, cl
	mov opc_w, ax
	pop ax

	push ax
	and ax, 1100000000000000B ;0000 0000 1100 0000
	mov cl, 14
	shr ax, cl
	mov opc_mod, ax
	pop ax

	push ax
	and ax, 0011100000000000B ;0000 0000 0011 1000
	mov cl, 11
	shr ax, cl
	mov opc_r1, ax
	pop ax

	push ax
	and ax, 0000011100000000B ;0000 0000 0000 0111
	mov cl, 8
	shr ax, cl
	mov opc_r2, ax
	pop ax

	;testavimas ar tinkamas opkodas
	mov ax, opc_code
	cmp al, 00001010B
	je testi_int
	call nutraukti_int

	testi_int:
	
	;Interuptas
	lea dx, step_msg
	mov ah, 9 
	int 21h

	;CS
	mov ax, di
	call print_AX

	mov ah, 2
	mov dl, ":"
	int 21h
	
	;IP
	mov ax, si
	call print_AX

	mov ah, 2
	mov dl, " "
	int 21h

	;Kodas
	mov ah, b1
	mov al, b2
	call print_AX

	mov ah, 2
	mov dl, " "
	int 21h

	lea dx, sub_msg
	cmp opc_d, 1
	jne sksm
	cmp opc_mod, 11B
	je sksm
	lea dx, sub_msg_r

	sksm:
	mov ah, 9 
	int 21h

	;tikrinimas pagal mod opc memory

	;Pavadinimo 1 spausdinimas
	cmp opc_mod, 11B
	je opc_mod_11b
	cmp opc_mod, 00B
	je opc_mod_00

	mov si, opc_r1
	mov reg_r1, si
	add reg_r1, 24

	mov di, opc_r2
	mov cl, 3
	shl di, cl
	mov ah, 9 
	lea dx, reg_m2_names + di
	mov n1, dx
	int 21h

	mov ah, 2
	mov dl, "+"
	int 21h

	;jei mod = 01, tai offsetas baitas, jei 10 tai wordas
	mov ah, b3
	mov al, b4
	cmp opc_mod, 10B
	je op_mod_word
	mov ah, 0

	op_mod_word:
	mov reg_of, ax
	call print_AX
	jmp opc_mod_end


	opc_mod_00:
	cmp opc_r2, 110B
	jne skip_ea_ld
	mov ah, b3
	mov al, b4
	mov reg_of, ax
	call print_AX

	mov di, opc_r2
	mov cl, 3 ;Padauginti iš 8 nes toks teksto ilgis
	shl di, cl
	mov ah, 9 
	lea dx, reg_m1_names + di
	mov n1, dx
	jmp opc_mod_end

	opc_mod_11b:
	jmp opc_mod_11

	skip_ea_ld:
	mov si, opc_r1
	mov reg_r1, si
	add reg_r1, 16

	mov di, opc_r2
	mov cl, 3 ;Padauginti iš 8 nes toks teksto ilgis
	shl di, cl
	mov ah, 9 
	lea dx, reg_m1_names + di
	mov n1, dx
	int 21h

	jmp opc_mod_end


	opc_mod_11:
	mov si, opc_r1
	mov reg_r1, si
	cmp opc_w, 0
	je skip_n1
	add reg_r1, 8

	skip_n1:
	mov di, opc_r1
	call print_reg_pos_di
	mov n1, dx

	opc_mod_end:
	mov ah, 2
	mov dl, ","
	int 21h
	mov dl, " "
	int 21h


	;Pavadinimo 2 spausdinimas
	mov di, opc_r2
	
	cmp opc_mod, 11B
	je skip_r2
	mov di, opc_r1

	skip_r2:
	mov reg_r2, di
	call print_reg_pos_di
	mov n2, dx

	mov ah, 2
	mov dl, ";"
	int 21h
	mov dl, " "
	int 21h



	;Reikšmių spausdinimas
	mov ah, 9 
	mov dx, n1
	int 21h

	mov ah, 2
	mov dl, "="
	int 21h

	;gaunama reikiama registro reikšmė į ax
	mov ax, reg_r2
	call ret_val_by_name
	call print_AX

	mov ah, 2
	mov dl, " "
	int 21h

	;Reikšmių spausdinimas
	mov ah, 9 
	mov dx, n2
	int 21h

	mov ah, 2
	mov dl, "="
	int 21h

	;gaunama registro reikšmė į ax
	mov ax, reg_r1
	call ret_val_by_name
	call print_AX

	;\n
	mov ah, 2
	mov dl, 10
	int 21h

	call nutraukti_int
ENDP

;krč užkniso out of range jmp
nutraukti_int PROC
	;Atgauti registrų reikšmes
	mov ax, regAX
	mov bx, regBX
	mov cx, regCX
	mov dx, regDX
	mov sp, regSP
	mov bp, regBP
	mov si, regSI
	mov di, regDI
IRET
ENDP

print_reg_pos_di PROC
	mov cl, 2 ;Padauginti iš 4 nes toks teksto ilgis
	shl di, cl
	lea dx, reg_w0_names + di

	cmp opc_w, 0
	je skip_shifting_1		
	lea dx, reg_w1_names + di ;Imti iš kito stringo

	skip_shifting_1:
	mov ah, 9
	int 21h
	RET
ENDP

;pagal registrų pavadinimus
ret_val_by_name PROC
	val_1:
	cmp ax, 1d
	jne val_2
	mov ax, regAX
	mov ah, 0
	RET

	val_2:
	cmp ax, 2d
	jne val_3
	mov ax, regCX
	mov ah, 0
	RET

	val_3:
	cmp ax, 3d
	jne val_4
	mov ax, regDX
	mov ah, 0
	RET

	val_4:
	cmp ax, 4d
	jne val_5
	mov ax, regBX
	mov ah, 0
	RET

	val_5:
	cmp ax, 5d
	jne val_6
	mov ax, regAX
	mov al, 0
	RET

	val_6:
	cmp ax, 6d
	jne val_7
	mov ax, regCX
	mov al, 0
	RET

	val_7:
	cmp ax, 7d
	jne val_8
	mov ax, regDX
	mov al, 0
	RET

	val_8:
	cmp ax, 8d
	jne val_9
	mov ax, regBX
	mov al, 0
	RET

	val_9:
	cmp ax, 9d
	jne val_10
	mov ax, regAX
	RET

	val_10:
	cmp ax, 10d
	jne val_11
	mov ax, regCX
	RET

	val_11:
	cmp ax, 11d
	jne val_12
	mov ax, regDX
	RET

	val_12:
	cmp ax, 12d
	jne val_13
	mov ax, regBX
	RET

	val_13:
	cmp ax, 13d
	jne val_14
	mov ax, regSP
	RET

	val_14:
	cmp ax, 14d
	jne val_15
	mov ax, regBP
	RET

	val_15:
	cmp ax, 15d
	jne val_16
	mov ax, regSI
	RET

	val_16:
	cmp ax, 16d
	jne val_17
	mov ax, regDI
	RET


	val_17:
	cmp ax, 17d
	jne val_18
	mov ax, regBX
	add ax, regSI
	RET

	val_18:
	cmp ax, 18d
	jne val_19
	mov ax, regBX
	add ax, regDI
	RET

	val_19:
	cmp ax, 19d
	jne val_20
	mov ax, regBP
	add ax, regSI
	RET

	val_20:
	cmp ax, 20d
	jne val_21
	mov ax, regBP
	add ax, regDI
	RET

	val_21:
	cmp ax, 21d
	jne val_22
	mov ax, regSI
	RET

	val_22:
	cmp ax, 22d
	jne val_23
	mov ax, regDI
	RET

	val_23:
	cmp ax, 23d
	jne val_24
	mov ax, reg_of
	RET

	val_24:
	cmp ax, 24d
	jne val_25
	mov ax, regBX
	RET

	val_25:
	cmp ax, 25d
	jne val_26
	mov ax, regBX
	add ax, regSI
	add ax, reg_of
	RET

	val_26:
	cmp ax, 26d
	jne val_27
	mov ax, regBX
	add ax, regDI
	add ax, reg_of
	RET

	val_27:
	cmp ax, 27d
	jne val_28
	mov ax, regBP
	add ax, regSI
	add ax, reg_of
	RET

	val_28:
	cmp ax, 28d
	jne val_29
	mov ax, regBP
	add ax, regDI
	add ax, reg_of
	RET

	val_29:
	cmp ax, 29d
	jne val_30
	mov ax, RegSI
	add ax, reg_of
	RET

	val_30:
	cmp ax, 30d
	jne val_31
	mov ax, RegDI
	add ax, reg_of
	RET

	val_31:
	cmp ax, 31d
	jne val_32
	mov ax, RegBP
	add ax, reg_of
	RET

	val_32:
	mov ax, RegBX
	add ax, reg_of
	RET

ENDP

print_AX PROC
	push ax
	mov al, ah
	call print_AL
	pop ax
	call print_AL
	RET
ENDP

print_AL PROC
	push ax
	push cx

	mov ah, al
	mov cl, 4
	shr al, cl
	call print_hex
	mov al, ah
	call print_hex
	
	pop cx
	pop ax
	RET
ENDP

print_hex:
	push ax
	push dx
	
	and al, 0Fh 
	cmp al, 9
	jbe print_hex_9

	; Jeigu A-F
	add al, 37h ; 'A' - 10h
	mov dl, al

	mov ah, 2
	int 21h
	jmp print_hex_end
	
	; Jeigu 0-9
	print_hex_9: 
	mov dl, al
	add dl, '0'

	mov ah, 2
	int 21h

	print_hex_end:
	pop dx
	pop ax
RET

END Pradzia