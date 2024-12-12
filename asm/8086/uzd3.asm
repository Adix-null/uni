.model small
.stack 100h

.data
    ;14 užduotis klevas.mif.vu.lt/~julius/2011Rud/KompArch/Uzd3.html
    ;https://klevas.mif.vu.lt/~linas1/KompArch/AsmProg.pdf
    ;https://www.stanislavs.org/helppc/int_21.html
    ;https://klevas.mif.vu.lt/~linas1/KompArch/modulis-APV.pdf
	senasIP dw ?
	senasCS dw ?
	
	regAX dw ?
	regBX dw ?
	regCX dw ?
	regDX dw ?
	regSP dw ?
	regBP dw ?
	regSI dw ?
	regDI dw ?
	
	baitas1 db ?
	baitas2 db ?
	baitas3 db ?
	baitas4 db ?
	baitas5 db ?
	baitas6 db ?
	
	zingsn_pranesimas db "Zingsninis pertraukimas: $"
	mov_bx_kabl		  db "MOV bx, $"
	bx_lygu db "bx=$"
	enteris db 13, 10, "$"
.code

Pradzia:

	mov ax, @data
	mov ds, ax
	
	;<<<<Cia turetu buti help parametra /? apdorojantis kodas>>>>>
	
;============ISSISAUGOME SENUS PERTRAUKIMO CS,IP============
	;Zingsninis pertraukimas yra INT 1
	;Vektoriu lentele prasideda adresu 00000
	;N-tojo pertraukimo (INT n), adresu 4n
	;Pirmojo: INT 1 adresu 00004
	;IP zodis padetas: 00004, 00005 (jaun, vyr)
	;CS zodis padetas: 00006, 00007 (jaun, vyr)
	;Pertraukimo apdorojimo proceduros AA=CS*10h+IP
	mov ax, 0
	mov es, ax ;Extra segmentas prasides ten pat kur vektoriu lentele
				;To reikia, kad galetume prieiti prie vektoriu lenteles baitu reiksmiu
	
	mov ax, es:[4]
	mov bx, es:[6]
	mov senasCS, bx
	mov senasIP, ax ;neisikeliam tiesiai, nes nera perdavimo is atminties i atminti (butina panaudoti registrus, isimtis eilutines komandos, bet jas panaudoti butu sudetingiau)

;===================PERIMAME PERTRAUKIMA==========================
	;Pertraukimo CS reiksme imame tokia, kokia ji yra sioje programos vietoje
	;Pertraukimo IP reiksme imama offset pertraukimas
	;t.y. "pertraukimas" proceduros poslinkis nuo kodo segmento pradzios
	mov ax, cs
	lea bx, pertraukimas
	
	mov es:[4h], bx
	mov es:[6h], ax

;=================AKTYVUOJAME ZINGSNINI REZIMA===================
	;Tam reikia nustatyti status flag registre pozymi TF vienetu
	;Su SF registru galime "bendrauti" tik per steka (noredami keisti TF pozymi)
	pushf ;PUSH SF
	pop ax
	or ax, 0000000100000000B ;TF=1
	push ax
	popf  ;POP SF ;>Zingsninis rezimas ijungiamas po sios komandos ivykdymo - ivykdzius kiekviena sekancia komanda ivyks zingsninis pertraukimas

;==================BELEKOKIOS KOMANDOS====================
	;Testinis gabaliukas, kur vykdomos komandos, kurias pertraukimas
	;Zingsninis vykdomas PO kiekvienos komandos bandys atpazinti
	;Pirmoji komanda siame bloke nebus atpazinta todel, kad zingsninis pertraukimas
	;Ivykes po pirmosios komandos ivykdymo gauna CS,IP reiksmes, kurios rodo
	;i sekancia, o ne einamaja komanda
	mov ax, 8414h
	mov bx, 9854h
	sub ax, bx
;==================ISJUNGIAME ZINGSNINI REZIMA======================
	pushf
	pop  ax
	and  ax, 1111111011111111B ;TF=0
	push ax
	popf ;>Zingsninis rezimas isjungiamas po sios komandos ivykdymo
;===================ATSTATOME PERTRAUKIMO CS, IP===================
;Kaip reikia uzdaryti failus, taip ir kai pertraukimas nereikalingas
;butina atstatyti vektoriu lenteleje ankstesni jo adresa
;Principas - "kaip radom taip ir paliekam"
	mov ax, senasIP
	mov bx, senasCS
	mov es:[4], ax
	mov es:[6], bx
	
uzdaryti_programa:
	mov ah, 4Ch
	int 21h
	


pertraukimas:	
    ;Išsaugoti registrų reikšmes
    mov regAX, ax				
	mov regBX, bx
	mov regCX, cx
	mov regDX, dx
	mov regSP, sp
	mov regBP, bp
	mov regSI, si
	mov regDI, di

    ;Sie veiksmai reikalingi norint gauti komandos poslinki nuo kodo segmento pradzios i SI registra (kad galetume prieiti prie tu baitu reiksmiu)
		pop si ;pasiimam IP reiksme (kvieciant pertraukima ji buvo i steka padeta paskutine)
		pop di ;pasiimam CS reiksme
		push di ;padedam CS reiksme
		push si ;vel padedam atgal - nagrinejama komanda esancia CS:IP (naudosime DI:SI)
		
		;Susidedam masininio kodo baitus i atminti
		mov ax, cs:[si]
		mov bx, cs:[si+2]
		mov cx, cs:[si+4]

        mov ah, 2
		mov dl, ":"
		int 21h ;spausdinam dvitaski
		
		mov baitas1, al
		mov baitas2, ah
		mov baitas3, bl
		mov baitas4, bh
		mov baitas5, cl
		mov baitas6, ch


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

END Pradzia