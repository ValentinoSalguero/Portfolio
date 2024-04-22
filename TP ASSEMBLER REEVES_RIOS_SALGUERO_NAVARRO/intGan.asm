.8086
.model tiny
.code
	org 100h
inicio:
    jmp main
    funcion PROC FAR
    sti
    
    mov ah, 1
    int 21h
    cmp al, 0dh
    je reemplazo
    mov al, 0
    jmp fin
    reemplazo:
    mov al, 2
    fin:
    iret
endp

despIntXX dw 0
segIntXX dw 0

FinResidente LABEL BYTE

cartel db "Has sido hackead@. Muajajajajajajajaja", 0dh, 0ah, '$'

main:
	mov ax, CS
	mov DS, ax
	mov ES, ax
instalarInt:
	mov ax, 3581h
	int 21h

	mov DespIntXX, bx
	mov SegIntXX, ES

	mov ax, 2581h
	mov dx, offset funcion
	int 21h

mostrarCartel:
    mov dx, offset cartel
    mov ah, 9
    int 21h

dejarResidente:
	mov ax, (15 + offset FinResidente)
	shr ax, 1
	shr ax, 1
	shr ax, 1
	shr ax, 1
	mov dx, ax
	mov ax, 3100h
	int 21h
end inicio