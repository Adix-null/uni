.model small
.stack 100h

.data
    ;14 užduotis 
	;klevas.mif.vu.lt/~julius/2011Rud/KompArch/Uzd3.html
    ;https://klevas.mif.vu.lt/~linas1/KompArch/modulis-APV.pdf

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
	
	b1 db ?
	b2 db ?

	n1 dw ?
	n2 dw ?
	
	step_msg db "Interuptas $"
	sub_msg db "SUB $"
	reg_names db "ALCLDLBLAHCHDHBHAXCXDXBXSPBPSIDI"
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
	sub bl, dl
	sub bl, dl
	sub bl, dl
	sub bl, cl
	sub ax, bp
	sub cx, bp
	sub si, di
	sub bp, cx
	sub bx, si

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
		
		;machine opkodai
		mov ax, cs:[si]
		mov b1, al
		mov b2, ah
		
		;Tikrinama pagal opcoda ar yra sub reg~r/m
		;opkodas 0010 10.. reg r/m  SUB registras -= registras/atmintis
		;Pasirašymai nes paskui pamiršiu
		; B1        B2        B3
		; OOOO OODW MMRR RKKK ... 	O - opkodas 	D - direction 		W - word 	M - mod		R - reg		K - kitas reg

		;testavimas ar tinkamas opkodas
		and al, 11111100B
		cmp al, 00101000B
		je testi_int
		call nutraukti_int

		testi_int:
		
		;Interuptas
		mov ah, 9 
		lea dx, step_msg
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

		mov ah, 9
		lea dx, sub_msg
		int 21h

		;R1 gavimas
		mov ah, b1
		mov al, b2
		and ax, 0000000000111000B
		mov cl, 3
		shr ax, cl
		mov dx, ax

		;W gavimas
		mov ah, b1
		mov al, b2
		and ax, 0000000100000000B

		cmp ax, 0
		je skip_shifting_1		
		add dx, 8 ;Pashiftinti pagal w reikšmę 8 kartus 

		skip_shifting_1:

		;Pavadinimo spausdinimas
		mov ah, 0Eh
		shl dx, 1
		mov di, dx
		mov n1, di
		mov al, [reg_names + di]
		int 10h  
		inc di
		mov al, [reg_names + di]
		int 10h  


		mov ah, 2
		mov dl, ","
		int 21h
		mov dl, " "
		int 21h


		;R2 gavimas
		mov ah, b1
		mov al, b2
		and ax, 0000000000000111B
		mov dx, ax

		;W gavimas
		mov ah, b1
		mov al, b2
		and ax, 0000000100000000B

		cmp ax, 0
		je skip_shifting_2		
		add dx, 8 ;Pashiftinti pagal w reiksme 8 kartus

		skip_shifting_2:

		;Pavadinimo spausdinimas
		mov ah, 0Eh
		shl dx, 1 ;Pavadinimas turi 2 simbolius, todel reikia x2
		mov di, dx
		mov n2, di
		mov al, [reg_names + di]
		int 10h  
		inc di
		mov al, [reg_names + di]
		int 10h  

		mov ah, 2
		mov dl, ";"
		int 21h
		mov dl, " "
		int 21h

		;Reiksmiu spausdinimas
		mov ah, 0Eh
		mov di, n1
		mov al, [reg_names + di]
		int 10h  
		inc di
		mov al, [reg_names + di]
		int 10h  

		mov ah, 2
		mov dl, "="
		int 21h

		;gaunama reikiama registro reiksme ax
		mov ax, n1
		call ret_reg_by_name
		call print_AX

		mov ah, 2
		mov dl, " "
		int 21h

		;Reiksmiu spausdinimas
		mov ah, 0Eh
		mov di, n2
		mov al, [reg_names + di]
		int 10h  
		inc di
		mov al, [reg_names + di]
		int 10h  

		mov ah, 2
		mov dl, "="
		int 21h

		;gaunama reikiama registro reiksme ax
		mov ax, n2
		call ret_reg_by_name
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

;pagal AL CL DL BL AH CH DH BH AX CX DX BX SP BP SI DI
ret_reg_by_name PROC
	cmp ax, 0
	je ret_al
	cmp ax, 2
	je ret_cl
	cmp ax, 4
	je ret_dl
	cmp ax, 6
	je ret_bl

	cmp ax, 8
	je ret_ah
	cmp ax, 10
	je ret_ch
	cmp ax, 12
	je ret_dh
	cmp ax, 14
	je ret_bh

	cmp ax, 16
	je ret_ax
	cmp ax, 18
	je ret_cx
	cmp ax, 20
	je ret_dx
	cmp ax, 22
	je ret_bx

	cmp ax, 24
	je ret_sp
	cmp ax, 26
	je ret_bp
	cmp ax, 28
	je ret_si
	cmp ax, 30
	je ret_di


	ret_al:
	mov ax, regAX
	mov ah, 0
	RET
	ret_cl:
	mov ax, regCX
	mov ah, 0
	RET
	ret_dl:
	mov ax, regDX
	mov ah, 0
	RET
	ret_bl:
	mov ax, regBX
	mov ah, 0
	RET

	ret_ah:
	mov ax, regAX
	mov al, 0
	RET
	ret_ch:
	mov ax, regCX
	mov al, 0
	RET
	ret_dh:
	mov ax, regDX
	mov al, 0
	RET
	ret_bh:
	mov ax, regBX
	mov al, 0
	RET

	ret_ax:
	mov ax, regAX
	RET
	ret_cx:
	mov ax, regCX
	RET
	ret_dx:
	mov ax, regDX
	RET
	ret_bx:
	mov ax, regDX
	RET

	ret_sp:
	mov ax, regSP
	RET
	ret_bp:
	mov ax, RegBP
	RET
	ret_si:
	mov ax, RegSI
	RET
	ret_di:
	mov ax, RegDI
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