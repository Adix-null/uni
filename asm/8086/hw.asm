.MODEL small ; atminties modelis
.STACK 100h ; steko dydis
.DATA ; duomenu segmentas

hello_message db 'Hello, World!',0dh,0ah,'$'

.CODE ; kodo segmentas
strt:
    mov ax,@data ; ds registro inicializavimas
    mov ds,ax
    mov ah,9 ; eilutes isvedimas
    mov dx,offset hello_message
    int 21h
    mov ax,4C00h ; programos darbo pabaiga
    int 21h
end strt