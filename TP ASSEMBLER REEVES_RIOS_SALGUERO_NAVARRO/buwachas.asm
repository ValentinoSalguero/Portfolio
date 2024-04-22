.8086
.model small
.stack 100h
.data
;mensajes
mensaje_bienvenida db  'Busca Minas',13,10,'$' ;se inicializa el titulo para el juego
img db "test.bmp", 0
perd db "perd.bmp", 0
gan db "gan.bmp", 0

start_x dw 20 ;son variables que definen las posiciones iniciales.
start_y dw 40 
ancho_celda equ 27 ;son variables que definen las dimensiones de las celdas en el juego.
alto_celda equ 27   
filas db 10 ;son variables que definen el número de filas y columnas en la grilla del juego.
columnas db 10
tipo_grilla db 0 ;es una variable que define el tipo de grilla (pequeña, mediana o grande).
;tipo = por defecto GRILLA_PEQUENIA

grilla db 480 dup(0) 
;-----------------------------------------------FORMA FACIL--------------------------------------------------------
;es un array que representa la grilla del juego, 
;donde cada celda puede estar cerrada (0),
;tener una bandera (1), abierta (2) o contener una mina (-1).
;-----------------------------------------------FORMA TECNICA------------------------------------------------------
;max grilla 16 * 30
;convenciones del array grilla
;el medio byte más significativo contiene la vista
;el segundo medio byte contiene el número
;la vista puede ser 0 -> cerrada , 1 -> con bandera , 2 -> abierta
;los datos pueden ser -1 -> bomba o número con rango(0 a 8)
;------------------------------------------------------------------------------------------------------------------
;son constantes que representan los estados de las celdas.
CELDA_CERRADA equ 0
CELDA_CON_BANDERA equ 1
CELDA_ABIERTA equ 2

;la variable aleatoria estado
rand db 0

;son constantes que representan los tipos de grillas.
GRILLA_PEQUENIA equ 0
GRILLA_MEDIANA equ 1 
GRILLA_GRANDE equ 2

;son las cantidades de minas para cada tipo de grilla.
numPequenias equ 10 ;número de minas para la pequeña grilla
numMedianas equ 30;40 ;número de minas para la medianas grilla
numGrandes equ 40; 99 número de minas para la grandes grilla

numMinas db 10 ;es la cantidad total de minas en la grilla actual.
rand_mod db 0 ;es una variable que se utilizan para generar números aleatorios.

dxAr db 0, 0FFh, 0FFh, 0FFh, 0, 1, 1, 1 ;son arrays que se utilizan para calcular las coordenadas de las celdas adyacentes.
dyAr db 0FFh, 0FFh, 0, 1, 1, 1, 0, 0FFh 

;es una matriz que se utiliza para representar un LED de 7 segmentos.
matriz_led db 44h, 3dh, 6dh, 4eh, 6bh, 7bh, 45h, 7fh

num_celdas_cerradas db 0 ;es una variable que lleva la cuenta de cuántas celdas están cerradas.

bandera_perdedora db 0 ;es una variable que indica si el jugador perdio el juego.

;contraste de color
COLOR_FONDO_CELDA_CERRADA equ 8 ;son constantes que representan los colores de fondo de las celdas cerradas y abiertas.
COLOR_FONDO_CELDA_ABIERTA equ 0

;son mensajes que se muestran cuando el jugador ingresa un parámetro inválido o elige el tipo de grilla.
mensaje_entrada_invalido db 'Parametro incorrecto, inserte uno nuevamente',10,13,'$' 
mensaje_elegir_tipo db 'Eligir dificultad:',10,13,'1) Fácil (9x9 grilla con 10 bombas)',10,13,'2) Normal (16x16 grilla con 30 bombas)',10,13,'3) Dificil (16x16 grilla con 40 bombas)',10,13,'$'

filename dw 0

filehandle dw ?

Header db 54 dup (0)

Palette db 256*4 dup (0)

ScrLine db 320 dup (0)

ErrorMsg db 'Error', 13, 10,'$'

ErrorFileNotFound db "Archivo no encontrado", 0dh, 0ah
                  db "Seguro te olvidaste del 0 al final", 0dh, 0ah
                  db "ej: archivo db 'test.bmp', 0", 0dh, 0ah, 24h

.CODE
;----------------------------------------------------------------------------------------------------------------
proc bmp 
    ; Modo gráfico
    mov filename, bx
    xor bx, bx
    mov ax, 13h
    int 10h


    ; Procesar archivo BMP
    call OpenFile
    call ReadHeader
    call ReadPalette
    call CopyPal
    call CopyBitmap

    ; CERRAR ARCHIVO

    mov ah, 3eh
    mov bx, [filehandle]
    int 21h

    ; Esperar la pulsación de una tecla
    ;mov ah,1

    ;int 21h
    ; Volver al modo de texto
    ;mov ah, 0
    ;mov al, 2
    ;int 10h
exit:
ret
bmp endp 
;----------------------------------------------------------------------------------------------------------------
proc OpenFile

    ; Abrir archivo

    mov ah, 3Dh
    xor al, al
    mov dx, filename
    int 21h

    jc openerror
    mov [filehandle], ax
    ret

    openerror:

    cmp al, 2
    jne errorGenerico
    mov dx, offset ErrorFileNotFound
    mov ah, 9h
    int 21h
errorGenerico:
    mov dx, offset ErrorMsg
    mov ah, 9h
    int 21h

    ;mov dl, al 
    ;mov ah, 2
    ;int 21h

    ; Esperar la pulsación de una tecla
    mov ah,1

    int 21h
    ; Volver al modo de texto
    mov ah, 0
    mov al, 2
    int 10h
    
    ret
endp OpenFile
;----------------------------------------------------------------------------------------------------------------
proc ReadHeader

    ; Leer encabezado del archivo BMP, 54 bytes

    mov ah,3fh
    mov bx, [filehandle]
    mov cx,54
    mov dx,offset Header
    int 21h
    ret
    endp ReadHeader
    proc ReadPalette

    ; Leer paleta de colores del archivo BMP, 256 colores * 4 bytes (400h)

    mov ah,3fh
    mov cx,400h
    mov dx,offset Palette
    int 21h
    ret
endp ReadPalette
;----------------------------------------------------------------------------------------------------------------
proc CopyPal

    ; Copiar la paleta de colores en la memoria de video
    ; El número del primer color debe enviarse al puerto 3C8h
    ; La paleta se envía al puerto 3C9h

    mov si,offset Palette
    mov cx,256
    mov dx,3C8h
    mov al,0

    ; Copiar el color inicial al puerto 3C8h

    out dx,al

    ; Copiar la paleta en sí al puerto 3C9h

    inc dx
    PalLoop:

    ; Nota: Los colores en un archivo BMP se guardan como valores BGR en lugar de RGB.

    mov al,[si+2] ; Obtener valor rojo.
    shr al,2 ; Máximo es 255, pero la paleta de video tiene un máximo

    ; valor de 63. Por lo tanto, dividir por 4.

    out dx,al ; Enviar.
    mov al,[si+1] ; Obtener valor verde.
    shr al,2
    out dx,al ; Enviar.
    mov al,[si] ; Obtener valor azul.
    shr al,2
    out dx,al ; Enviar.
    add si,4 ; Apuntar al siguiente color.

    ; (Hay un carácter nulo después de cada color.)

    loop PalLoop
    ret
endp CopyPal
;----------------------------------------------------------------------------------------------------------------
proc CopyBitmap

    ; Los gráficos BMP se guardan al revés.
    ; Leer la línea gráfica por línea (200 líneas en formato VGA),
    ; mostrando las líneas de abajo hacia arriba.

    mov ax, 0A000h
    mov es, ax
    mov cx,200
    PrintBMPLoop:
    push cx

    ; di = cx*320, apuntar a la línea de pantalla correcta

    mov di,cx
    shl cx,6
    shl di,8
    add di,cx

    ; Leer una línea

    mov ah,3fh
    mov cx,320
    mov dx,offset ScrLine
    ;add dx,0
    int 21h

    ; Copiar una línea en la memoria de video

    cld 

    ; Limpiar la bandera de dirección, para movsb

    mov cx,320
    mov si,offset ScrLine
    rep movsb 

    ; Copiar la línea a la pantalla
    ;rep movsb es lo mismo que el siguiente código:
    ;mov es:di, ds:si
    ;inc si
    ;inc di
    ;dec cx
    ;bucle hasta que cx=0

    pop cx
    loop PrintBMPLoop
    ret
endp CopyBitmap
;----------------------------------------------------------------------------------------------------------------
;Crea un retardo de aproximadamente 1 segundo al llamar a la interrupción 1Ah del BIOS para obtener el valor 
;actual del temporizador del sistema.
retraso_1seg MACRO
  LOCAL @@delay
  push ax
  push bx  ;Guardar los valores de los registros que se van a utilizar
  push dx
  push di
  push cx
@@delay:
  mov di,dx ;Guardar el valor del registro DX en el registro DI
  mov ah,0
  int 1ah ;Llamar a la interrupción 1Ah para obtener el valor actual del temporizador
  cmp dx,di ;Comparar el valor del registro DX con el valor guardado en el registro DI
  je @@delay ;Si los valores son iguales, saltar a la etiqueta @@delay
  inc bx  ; Incrementar el valor del registro BX
  cmp bx,5 ; Si el valor del registro BX no es igual a 5, saltar a la etiqua @@delay
  jne @@delay
  pop cx
  pop di  ; Restaurar los valores de los registros que se utilizaron
  pop dx
  pop bx
  pop ax
ENDM
;----------------------------------------------------------------------------------------------------------------
;genera un número aleatorio y luego calcula el módulo de ese número con un límite especificado.
gen_rand_mod MACRO limit
  gen_aleatorio ;Esta línea llama a macro gen_aleatorio que genera un número aleatorio.
  push ax
  push bx; guardan los valores actuales de los registros ax, bx, cx y dx.
  push cx
  push dx
  mov ax,0 ;inicializan el registro ax con el número aleatorio generado.
  mov al,rand
  mov bl,limit ;mueve el valor del límite proporcionado al registro bl.
  mul bl    ; multiplica el valor en el registro ax (el número aleatorio) por el valor en el registro bl (el límite). El resultado se almacena en el registro ax.
  mov cl,7  ; desplazan los bits del registro ax (el resultado de la multiplicación) a la derecha por 7 bits. Esto efectivamente divide el número por 2^7 (o 128),
  shr ax,cl ; que es equivalente a calcular el módulo del número por 128.
  mov rand_mod,al ;mueve el valor en el registro al (la parte baja del resultado de la multiplicación y el desplazamiento) al lugar de memoria rand_mod. Este es el resultado final de la macro, que es el módulo del número aleatorio por 128.
  pop dx  
  pop cx ; restauran los valores originales de los registros dx, cx, bx y ax.
  pop bx
  pop ax
ENDM
;----------------------------------------------------------------------------------------------------------------
;Este macro genera un número aleatorio utilizando el algoritmo de congruencia lineal. 
;El número aleatorio se genera utilizando la fórmula (5*rand+3) % 32, donde rand es el número aleatorio anterior.
gen_aleatorio MACRO
  ;rand = (5*rand+3) % 32
  push ax 
  push bx
  xor ax,ax ; el valor del registro ax a 0.
  mov al,rand ;mueve el valor de la variable rand al registro ax.
  mov bl,5
  mul bl ;multiplica el valor en el registro ax por el valor en el registro bx, y almacena el resultado en ax.
  add al,5
  mov bl,128
  div bl ;divide el valor en el registro ax por el valor en el registro bx, y almacena el resultado en ax. El resto de la división se almacena en dx.
  mov rand,ah ;mueve el valor en el registro ah (la parte alta del resultado de la división) a la variable rand.
  pop bx
  pop ax
ENDM
;----------------------------------------------------------------------------------------------------------------
 ;Toma un argumento dir_mensaje, imprime el mensaje almacenado en esa dirección 
imprimir MACRO dir_mensaje
  push ax
  push dx
  mov dx,OFFSET dir_mensaje ;carga la dirección de la variable dir_mensaje en el registro dx. 
                            ;OFFSET es una directiva del ensamblador que devuelve la dirección de una variable 1.
  mov ah,9
  int 21h ;imprimir una cadena de caracteres
  pop dx
  pop ax
ENDM imprimir
;----------------------------------------------------------------------------------------------------------------
; toma una fila y una columna, las incrementa en 1, multiplica la fila por el número de columnas más 2, 
; suma la columna incrementada en 1, y almacena el resultado en el registro bx.
; macro privada usada en otras macros para expandir fila y columna dadas al índice requerido en grilla
; utiliza ax como registro temporal y el resultado de la expansión se almacena en bx
_expandir MACRO fila,columna
  ;bx <- index = ((fila+1)*(columnas+2)) + (columna+1)
  push ax
  push dx
  
  mov ax,0 ; inicializa el registro ax a 0 y luego mueven el valor de la fila dada al registro al.
  mov al,fila
  inc al
  mov bx,0 ; inicializa el registro bx a 0 y luego mueven el valor de las columnas dadas al registro bl.
  mov bl,columnas
  add bx,2 
  mul bx ; multiplica el valor en el registro al por el valor en el registro bl y almacena el resultado en el registro ax.
  mov bx,0
  mov bl,columna ; inicializa el registro bx a 0 y luego mueven el valor de la columna dada al registro bl.
  inc bl
  add ax,bx 
  mov bx,ax
  
  pop dx
  pop ax
ENDM
;----------------------------------------------------------------------------------------------------------------
;Aumenta el puntero de pila en 4 bytes. El índice se calcula como ((fila+1)*(columnas+2)) + (columna+1).
; Sin embargo, este cálculo no se realiza en la macro _expandir_llamante, por lo que es posible que se realice 
;en la función _expandir_proc.
;dos argumentos de 1 byte
;el resultado se devuelve en bx
_expandir_llamante MACRO fila,columna
  ;bx <- index = ((fila+1)*(columnas+2)) + (columna+1)
  mov bx,0
  mov bl,columna ;Mueve el valor de columna al registro bl (la parte baja de bx) y luego empuja bx a la pila.
  push bx ;Mueve el valor de fila al registro bl y luego empuja bx a la pila.     
  mov bl,fila 
  push bx
  call _expandir_proc;Llama a la función _expandir_proc.
  add sp,4 ;Aumenta el puntero de pila en 4 bytes.
ENDM
;----------------------------------------------------------------------------------------------------------------
;calcula un índice basado en dos parámetros: fila y columna.  El índice se calcula como ((fila+1)*(columnas+2)) + (columna+1).
_expandir_proc PROC
  ;bx <- index = ((fila+1)*(columnas+2)) + (columna+1)
  push bp
  mov bp,sp ;Mueve el valor del puntero de pila al puntero base. Esto se hace para que el puntero base apunte al
            ;inicio de los parámetros de la función en la pila.

  push ax
  push dx
  
  mov ax,[bp+4] ;Mueve el primer parámetro de la función (la fila) al registro ax.
  inc al
  mov bx,0
  mov bl,columnas ;Mueve el valor de columnas al registro bx y luego mueve 0 al registro bx. 
                  ;Esto se hace para preparar el cálculo del índice.
  add bx,2
  mul bx ;Multiplica el valor en el registro ax por el valor en el registro bx. Esto se hace para calcular el índice.
  mov bx,[bp+6] ;Mueve el segundo parámetro de la función (la columna) al registro bx.
  inc bl
  add ax,bx 
  mov bx,ax
  
  pop dx
  pop ax
  pop bp
  RET
ENDP
;----------------------------------------------------------------------------------------------------------------
;Con la fila y una columna, obtiene el valor de la celda en esa posición en la vista, realiza algunas operaciones en ese valor
;el valor de una celda específica en una vista y colocarlo en una posición de memoria especificada. 
;obtiene el valor de la vista de celda y lo pone en la posición de memoria especificada 
;nota : los registros pueden usarse como salida (excepto bx,cx) ya que se usan dentro de la macro
;la entrada se puede pasar en registros excepto cl , bx
obtener_vista_celda MACRO fila,columna,valor_salida
  push bx
  push cx
  ;_expandir fila,columna
  _expandir_llamante fila,columna ; llama a la macro _expandir_llamante con los argumentos fila y columna.
  mov bl,[bx + OFFSET grilla] ;mueve el valor de la celda en la vista a la posición de memoria especificada por bx a bl.
  and bl,0F0h ;realiza una operación AND bit a bit en el valor en bl con 0F0h. 
              ;Esto se utiliza para extraer un valor específico de los bits de bl.
  mov cl,4 
  shr bl,cl ;mueven el valor 4 a cl y luego realizan una operación de desplazamiento a la derecha en bl por cl bits.
            ;Esto probablemente se utiliza para mover los bits de bl a la derecha para que el valor que se quiere extraer
            ;esté en la posición correcta.
  mov valor_salida,bl ; el valor en bl a valor_salida. Esto coloca el valor de la celda en la vista en la posición de memoria
            ; especificada por valor_salida.
  pop cx
  pop bx
ENDM
;----------------------------------------------------------------------------------------------------------------
;establece una celda en una grilla a un estado "abierta".
establecer_celda_abierta MACRO fila,columna
  push ax
  push bx
  _expandir_llamante fila,columna ;llama a otra macro o función llamada la cual toma fila y columna como argumentos.
  mov al,[bx + OFFSET grilla];mueve el valor en la dirección de memoria calculada por bx + OFFSET grilla al registro al.
  ;borra el medio byte más significativo y lo pone a 2
  and al,0Fh;realiza una operación AND bit a bit entre el valor en al y 0Fh (15 en decimal).
  or al,20h;realiza una operación OR bit a bit entre el valor en al y 20h (32 en decimal). Esto establece el bit más significativo de al a 1.
  mov [bx + OFFSET grilla],al; mueve el valor en al a la dirección de memoria calculada por bx + OFFSET grilla.
  pop bx
  pop ax
ENDM
;----------------------------------------------------------------------------------------------------------------
;establece una celda en una grilla a un estado "cerrado".
establecer_celda_cerrada MACRO fila,columna
  push ax
  push bx
  ;_expandir fila,columna
  _expandir_llamante fila,columna;llama a otra macro o función llamada _expandir_llamante, que toma fila y columna como argumentos. 
  mov al,[bx + OFFSET grilla];mueve el valor en la dirección de memoria que es el valor en bx más OFFSET grilla a al.
  and al,0Fh; realiza una operación AND bit a bit en al y 0Fh (15 en decimal). Esto efectivamente limita al a los últimos 4 bits.
  mov [bx + OFFSET grilla],al;mueve el valor en al a la dirección de memoria que es el valor en bx más OFFSET grilla.
  pop bx
  pop ax
ENDM
;----------------------------------------------------------------------------------------------------------------
; establecer una celda en una grilla a un estado específico.
; La grilla es una matriz bidimensional y la celda se especifica por la fila y la columna.
; La macro modifica el valor en la celda especificada, realizando una operación AND y luego una operación OR con los valores 0Fh y 10h respectivamente.
establecer_celda_con_bandera MACRO fila,columna
  push ax
  push bx
  ;_expandir fila,columna
  _expandir_llamante fila,columna
  mov al,[bx + OFFSET grilla]; mueve el valor en la dirección de memoria calculada por bx + OFFSET grilla al registro al.
  and al,0Fh;realiza una operación AND bit a bit entre el valor en al y 0Fh (15 en decimal). El resultado se almacena en al.
  or al,10h;realiza una operación OR bit a bit entre el valor en al y 10h (16 en decimal). El resultado se almacena en al.
  mov [bx + OFFSET grilla],al; mueve el valor en al a la dirección de memoria calculada por bx + OFFSET grilla.
  pop bx
  pop ax
ENDM
;----------------------------------------------------------------------------------------------------------------
;esta macro convierte las coordenadas de pantalla en filas y columnas, teniendo en cuenta el inicio de la pantalla y el tamaño de la celda.
;convierte coordenadas de pantalla en cx y dx a filas y columnas
;cl tendrá número de columna y dl tendrá número de fila
convertir_coordenadas MACRO
  push ax   ;guarda el valor de ax
  push bx   ;guarda el valor de bx
  ;agarra el numero de columna  
  sub cx,start_x ;restan los valores de start_x y cx. Esto se hace para obtener las coordenadas de pantalla en relación con el inicio de la pantalla.
  mov ax,cx;mueven los valores de cx a ax. Esto se hace para realizar operaciones de división en ax.
  mov bl,ancho_celda;mueven los valores de ancho_celda a bl. Esto se hace para realizar la división de las coordenadas de pantalla por el ancho y el alto de la celda.
  div bl;divide el valor en ax por el valor en bl. El resultado de la división se almacena en ax.
  mov cx,ax;mueven el resultado de la división. Esto se hace para almacenar las coordenadas de fila y columna.
  ;agarra el numero de fila  
  sub dx,start_y;restan los valores de start_y y dx respectivamente. Esto se hace para obtener las coordenadas de pantalla en relación con el inicio de la pantalla.
  mov ax,dx;mueven los valores de dx a ax. Esto se hace para realizar operaciones de división en ax.
  mov bl,alto_celda;mueven los valores de alto_celda a bl. Esto se hace para realizar la división de las coordenadas de pantalla por el ancho y el alto de la celda.
  div bl;divide el valor en ax por el valor en bl. El resultado de la división se almacena en ax.
  mov dx,ax;mueven el resultado de la división. Esto se hace para almacenar las coordenadas de fila y columna.
  ;restaurar registros ax,bx
  pop bx
  pop ax
ENDM
;----------------------------------------------------------------------------------------------------------------
;convierte fila y columna dadas a sus posiciones reales
;el resultado se almacena en cx y dx
;cx tendrá la posición x de la celda y dx tendrá la posición y de la celda
expandir_coordenadas MACRO fila,columna
  push ax   ;guarda el valor de ax
  push bx   ;guarda el valor de bx
  ;agarra xpos
  mov al,columna
  mov bl,ancho_celda
  mul bl;multiplica el valor en el registro al (que es el valor de columna) por el valor en el registro bl 
  ;(que es el valor de ancho_celda). El resultado se almacena en el registro ax.
  add ax,start_x;suman el valor de start_x al resultado de la multiplicación y luego mueven el resultado al registro cx.
  mov cx,ax
  ;agarra ypos
  mov al,fila
  mov bl,alto_celda
  mul bl; multiplica el valor en el registro al (que es el valor de fila) por el valor en el registro bl 
  ;(que es el valor de alto_celda). El resultado se almacena en el registro ax.
  add ax,start_x;líneas suman el valor de start_x al resultado de la multiplicación y
  ; luego mueven el resultado al registro dx.
  mov dx,ax
  ;retorna los registros de ax y bx 
  pop bx
  pop ax
ENDM
;----------------------------------------------------------------------------------------------------------------
;obtener las coordenadas de pantalla de una fila y columna específicas.  toma dos argumentos (fila y columna)
; y calcula las coordenadas de pantalla correspondientes. 
;Las coordenadas de pantalla se almacenan en los registros cx (x) y dx (y).
;proc usado para obtener coordenadas de pantalla de fila y columna
;toma dos entradas fila,columna (1 palabra cada una)
;los resultados se almacenan en cx,dx
obtener_coordenadas_pantalla PROC
  push bp
  mov bp,sp
  push ax
  push bx
  ;agarra xpos
  mov ax,[bp+6];mueve el valor de la fila (el segundo argumento del procedimiento) al registro ax.
  mov bl,ancho_celda
  mul bl;multiplica el valor en el registro ax por el valor en el registro bl. s
  add ax,start_x;suma el valor de la variable start_x al valor en el registro ax. 
  mov cx,ax
  ;agarra ypos
  mov ax,[bp+4];mueve el valor de la columna (el primer argumento del procedimiento) al registro ax.
  mov bl,alto_celda
  mul bl
  add ax,start_y
  mov dx,ax
  ;retorna los registros
  pop bx
  pop ax
  pop bp
  RET
ENDP
;----------------------------------------------------------------------------------------------------------------
obtener_coordenadas_pantalla_llamante MACRO fila,columna
  push columna
  push fila
  call obtener_coordenadas_pantalla; llama a obtener obtener_coordenadas_pantalla
  add sp,4;incrementa el puntero de pila (sp) en 4. Esto se hace para ajustar el puntero de pila después de que
  ; los valores de fila y columna se han empujado a la pila.
ENDM
;----------------------------------------------------------------------------------------------------------------
;dibuja las lineas del tablero por pantalla
;parametos startX,startY,length,Color,Vertical
dibujar_linea PROC
  push bp
  mov bp,sp
  ;Creación de variables locales
  push ax
  push bx
  push cx
  push dx
  push di
  push si
  ; manejo del stack
  mov al,[bp+10]    ;4 parametro  (color)
  mov si,[bp+8]     ;3 parametro  (longitud)
  mov dx,[bp+6]     ;2 parametro (startY)
  mov cx,[bp+4]     ;1 parametro (startX)
  mov ah,0ch
  mov di,[bp+12]    ;5 parametro (0 = horizontal de lo contrario vertical)
  mov bh,0
  cmp di,0 ;comparan el quinto parámetro (0 = horizontal, de lo contrario vertical) con 0. 
  ;Si no es igual a 0, salta a la etiqueta vertical.
  jnz vertical
  
  horizontal:;dibuja una línea horizontal.
    int 10h;interrumpe el sistema para dibujar un pixel en la pantalla.
    inc cx ; incrementan el valor de cx (la posición x del pixel) 
    dec si ;decrementan el valor de si (la longitud de la línea).
    jnz horizontal
    jmp hecho
    ;Esta instrucción salta a la etiqueta horizontal si "si" no es igual a 0.
    ;el código seguirá dibujando pixels hasta que la línea haya alcanzado la longitud especificada.

  vertical:;dibuja una línea vertical.
  ;funciona igual que "horizontal"
    int 10h
    inc dx 
    dec si
    jnz vertical
  hecho:
    ;Despejar la memoria local
    ;nada que borrar
    ;restaurar registros
    pop si
    pop di
    pop dx
    pop cx
    pop bx
    pop ax
    pop bp
    RET
ENDP
;----------------------------------------------------------------------------------------------------------------
;macro utilizada para facilitar la invocación del método dibujar línea
dibujar_linea_llamante MACRO startX,startY,longitud,color,vertical
  push vertical
  push color
  push longitud
  push startY
  push startX
  call dibujar_linea;llama a la función "dibujar_linea". Los argumentos para esta función se pasan a través de la pila.
  add sp,10;restaura el puntero de pila (sp) en 10. Esto se hace para limpiar la pila después de que se han utilizado 
  ;los argumentos de la función.
ENDM dibujar_linea_llamante
;----------------------------------------------------------------------------------------------------------------
;dibuja un rectángulo lleno en una pantalla. El rectángulo se dibuja línea por línea, y el bucle se repite
; hasta que todas las líneas han sido dibujadas.
;stack      startX,startY,lenX,lenY,color
;=========  [bp+4],[bp+6], 8 , 10  , 12
dibujar_caja_llena PROC
  push bp
  mov bp,sp
  push ax
  push cx
  mov ax,[bp+6]
  mov cx,[bp+10]

  lineas:
    ;dibujar_linea_llamante MACRO startX,startY,longitud,color,vertical
    dibujar_linea_llamante [bp+4],ax,[bp+8],[bp+12],0
    ; llamada a la macro dibujar_linea_llamante que dibuja una línea.
    ; Los parámetros son la posición inicial en x, la posición inicial en y, la longitud de la línea, el color y
    ; si la línea es vertical o no.
    inc ax
    loop lineas; bucle que repite el bucle hasta que el valor en cx se reduce a 0.

  pop cx
  pop ax
  pop bp
  RET
ENDP
;----------------------------------------------------------------------------------------------------------------
dibujar_caja_llena_llamante MACRO startX,startY,lenX,lenY,color
  push color
  push lenY
  push lenX
  push startY
  push startX
  call dibujar_caja_llena;llama a la función dibujar_caja_llena. La función dibujar_caja_llena
  ; dibuja una caja llena en la pantalla utilizando los valores que se pasaron a la pila.
  add sp,10
ENDM dibujar_caja_llena_llamante
;----------------------------------------------------------------------------------------------------------------
;colorea la celda dada
;parámetros fila,columna,color
color_celda PROC
  push bp
  mov bp,sp

  push cx
  push dx

  obtener_coordenadas_pantalla_llamante [bp+4],[bp+6]; llama a un procedimiento o función que obtiene las
  ; coordenadas de la pantalla de la celda que se va a colorear. Los parámetros de la celda (fila y columna) se 
  ;pasan a través del registro base.
  ;hacer que aparezcan líneas de borde (disminuir el área de las cajas interiores)
  inc cx
  inc dx
  ;Incrementa los valores de los registros cx y dx. 
  ;Esto se hace para "hacer que aparezcan líneas de borde (disminuir el área de las cajas interiores)".

  dibujar_caja_llena_llamante cx,dx,ancho_celda-1,alto_celda-1,[bp+8];llama a un procedimiento o función que 
  ;dibuja una caja llena en la pantalla. Los parámetros de la caja (coordenadas, ancho, alto y color) se pasan 
  ;a través del registro base.
  pop dx
  pop cx

  pop bp
  RET
ENDP
;----------------------------------------------------------------------------------------------------------------
color_celda_llamante MACRO fila,columna,color
  push color
  push columna
  push fila
  call color_celda
  add sp,6
ENDM
;----------------------------------------------------------------------------------------------------------------
dibujar_grilla MACRO filas,columnas,startX,startY,ancho_celda,alto_celda
  ;guardar registros
  push ax
  push bx
  push cx
  push dx
  
  xor cx,cx ; Inicializar el contador de filas
  mov cl,filas
  inc cx

  xor ax,ax; Inicializar el contador de columnas
  mov al,columnas

  mov bx,startY; Inicializar las coordenadas de inicio
  mov dl,ancho_celda
  mul dl ; ax contiene la longitud de la línea

  ;ax contiene la longitud de la línea
  ; Bucle para dibujar las filas
  bucle_filas:
    ; Llamar a la función dibujar_linea con las coordenadas y longitud de la línea
    dibujar_linea_llamante startX,bx,ax,58,0
    add bx,alto_celda; Añadir el alto de la celda al valor de bx para la siguiente fila
    loop bucle_filas ; Decrementar el contador de filas y saltar al inicio del bucle si no hemos llegado al final

; Inicializar el contador de columnas
  xor cx,cx
  mov cl,columnas
  inc cx

 ; Inicializar el contnador de filas
  xor al,al
  mov al,filas

 ; Inicializar las coordenadas de inicio
  mov bx,startX
  mov dl,alto_celda
  mul dl
    ;ax contiene la longitud de la línea
     ; Bucle para dibujar las columnas
  bucle_columnas:
    dibujar_linea_llamante bx,startY,ax,58,1;Llamar a la función dibujar_linea con las coordenadas y longitud de la línea
    add bx,ancho_celda; Añadir el ancho de la celda al valor de bx para la siguiente columna
    loop bucle_columnas; Decrementar el contador de columnas y saltar al inicio del bucle si no hemos llegado al final

    ;retornar registros
    pop dx
    pop cx
    pop bx
    pop ax
ENDM dibujar_grilla
;----------------------------------------------------------------------------------------------------------------
;inicializa una cuadrícula de juego. La cuadrícula se llena con ceros, que representan celdas vacías.
; Luego, se dibuja el fondo de las celdas vacías y se inicializan los marcos horizontales y verticales.
; Finalmente, se generan las bombas en la cuadrícula.
init_grid MACRO
  ;guarda los registros
  push ax
  push cx
  push dx
    
comenzar_inicializacion:;inicia la inicialización de la cuadrícula.
  ;init números de celdas abiertas a filas*columnas
  mov al,filas
  mul columnas
  mov num_celdas_cerradas,al
  mov al,numMinas
  sub num_celdas_cerradas,al
  
  ;inicializa todas las celdas a 0
  mov cl,filas
  dec cl
  mov dl,0
  
  ;bucle que recorre las filas de la cuadrícula.
  bucle_en_filas:
    mov ch,columnas
    dec ch
    ; bucle que recorre las columnas de la cuadrícula.
    bucle_en_columnas:
      _expandir_llamante cl,ch
      mov [bx + OFFSET grilla],dl; Mueve el valor en dl a la ubicación de memoria apuntada por bx más OFFSET grilla.
;Mueve el valor en dl a la ubicación de memoria apuntada por bx más OFFSET grilla.


      ;dibujar fondo de celdas vacías
      
      push cx
      push dx
      mov dl,ch
      xor dh,dh
      xor ch,ch
      color_celda_llamante cx,dx,COLOR_FONDO_CELDA_CERRADA
      pop dx
      pop cx
      
      dec ch
      cmp ch,0
    jge bucle_en_columnas;Si el valor en ch es mayor o igual a 0, salta a la etiqueta bucle_en_columnas.
    dec cl
    cmp cl,0
  jge bucle_en_filas;Si el valor en cl es mayor o igual a 0, salta a la etiqueta bucle_en_filas.
  
  ;inicializar fotograma
  mov dl,20h
  mov ch,filas
  mov cl,columnas
  
  inicializar_marco_horizontal:
    _expandir_llamante 0FFh,cl
    mov [bx + OFFSET grilla],dl; Mueve el valor en dl a la ubicación de memoria apuntada por bx más OFFSET grilla.
    
    _expandir_llamante ch,cl
    mov [bx + OFFSET grilla],dl; Mueve el valor en dl a la ubicación de memoria apuntada por bx más OFFSET grilla.
    
    dec cl
    cmp cl,0FFh
  jge inicializar_marco_horizontal
  
  mov ch,columnas
  mov cl,filas
  
  inicializar_marco_vertical:
    _expandir_llamante cl,0FFh
    mov [bx + OFFSET grilla],dl; Mueve el valor en dl a la ubicación de memoria apuntada por bx más OFFSET grilla.
    
    _expandir_llamante cl,ch
    mov [bx + OFFSET grilla],dl; Mueve el valor en dl a la ubicación de memoria apuntada por bx más OFFSET grilla.
    
    dec cl
    cmp cl,0
  jge inicializar_marco_vertical
  
  gen_bombs

  ;retornar registros
  pop dx
  pop cx
  pop ax
ENDM init_grid
;----------------------------------------------------------------------------------------------------------------
gen_bombs MACRO
  ;guarda los registros
  push ax
  push cx
  push dx
  push si
  
  ;Inicializa el contador de bombas
  mov cx,0
  mov cl,numMinas

   ; Bucle para generar bombas
  bucle_generar_bomba:

    ; Genera un número aleatorio para la fila
    gen_rand_mod filas
  
    mov al,rand_mod ;guarda el número de fila en al
  
    ; Genera un número aleatorio para la columna
    gen_rand_mod columnas
  
    mov ah,rand_mod ;guardar número de columna en ah
    
    ; Expande la llamada a la función con los números de fila y columna
    _expandir_llamante al,ah
    
    ; Comprueba que la celda no contiene ya una bomba (evita duplicados)
    mov ch,[bx + OFFSET grilla]
    cmp ch,0Fh
    jne poner_bomba
    jmp bucle_generar_bomba
    

  poner_bomba:   
    ; Coloca una bomba en la celda
    mov ch,0Fh
    mov [bx + OFFSET grilla],ch
    
   ; Incrementa las celdas circundantes
    mov si,7
    loop_en_dAr:
      lea bx,dxAr
      mov dl,[bx+si]
      lea bx,dyAr
      mov dh,[bx+si]
      add dl,al
      add dh,ah
  
      ; Expande la llamada a la función con los números de fila y columna 
      _expandir_llamante dl,dh
    
      mov ch,[bx + OFFSET grilla]
      cmp ch,0Fh
      jae no_incrementar ;la celda contiene una bomba O es una celda fronteriza (en el marco)
      inc ch
      mov [bx + OFFSET grilla],ch
      
    no_incrementar:
      
      dec si
      cmp si,0
    jge loop_en_dAr
    
    dec cl
    cmp cl,0
    jg continuar_bucle
    jmp salir_bucle
    
  continuar_bucle:
  jmp bucle_generar_bomba
  
salir_bucle:
  ;restaurar registros
  pop si
  pop dx
  pop cx
  pop ax
ENDM gen_bombs
;----------------------------------------------------------------------------------------------------------------
;led valor toma un número y dibuja las lineas correspondientes del mapa 7seg
dibujar_valor_led PROC
  push bp
  mov bp,sp

  push ax
  push bx
  push cx
  push dx

  mov cx,[bp + 4] ;1 parametro ==> xpos
  mov dx,[bp + 6] ;2 parametro ==> ypos
  mov ax,[bp + 8] ;3 parametro ==> num (sólo se utilizará al, ah se ignorará)

  test al,1
  jz seg_2

  add cx,ancho_celda/3 ;La división se hace en tiempo de compilar
  add dx,alto_celda/6
  mov bx,ancho_celda/3
  dibujar_linea_llamante cx,dx,bx,13,0
  
seg_2:
  shr al,1
  test al,1
  jz seg_3
  mov cx,[bp + 4] 
  mov dx,[bp + 6]
  add cx,ancho_celda/3
  add dx,alto_celda/6
  mov bx,alto_celda/6*2
  dibujar_linea_llamante cx,dx,bx,13,1

seg_3:
  shr al,1
  test al,1
  jz seg_4
  mov cx,[bp + 4] 
  mov dx,[bp + 6]
  add cx,ancho_celda/3*2
  add dx,alto_celda/6
  mov bx,alto_celda/6*2
  dibujar_linea_llamante cx,dx,bx,13,1
  
seg_4:
  shr al,1
  test al,1
  jz seg_5
  mov cx,[bp + 4] 
  mov dx,[bp + 6]
  add cx,ancho_celda/3
  add dx,alto_celda/6*3
  mov bx,ancho_celda/3
  dibujar_linea_llamante cx,dx,bx,13,0

seg_5:
  shr al,1
  test al,1
  jz seg_6
  mov cx,[bp + 4] 
  mov dx,[bp + 6]
  add cx,ancho_celda/3
  add dx,alto_celda/6*3
  mov bx,alto_celda/3
  dibujar_linea_llamante cx,dx,bx,13,1

seg_6:
  shr al,1
  test al,1
  jz seg_7
  mov cx,[bp + 4] 
  mov dx,[bp + 6]
  add cx,ancho_celda/3
  add dx,alto_celda/6*5
  mov bx,ancho_celda/3
  dibujar_linea_llamante cx,dx,bx,13,0

seg_7:
  shr al,1
  test al,1
  jz led_terminar
  mov cx,[bp + 4] 
  mov dx,[bp + 6]
  add cx,ancho_celda/3*2
  add dx,alto_celda/6*3
  mov bx,alto_celda/3
  dibujar_linea_llamante cx,dx,bx,13,1

led_terminar:
  pop dx
  pop cx
  pop bx
  pop ax
  pop bp
  RET
ENDP
;----------------------------------------------------------------------------------------------------------------
;simprime el número especificado por valor en la ubicación especificada por fila y columna
imprimir_valor_celda MACRO fila,columna,valor
  LOCAL @@skip
  push bx
  push dx
  push cx
  push si
  cmp valor,0
  je @@skip
  ;expandir_coordenadas fila,columna
  obtener_coordenadas_pantalla_llamante fila,columna
  ;push parametros
  mov bx,OFFSET matriz_led
  mov si,valor
  push [bx+si-1]
  push dx
  push cx
  call dibujar_valor_led
  add sp,6
@@skip:
  pop si
  pop cx
  pop dx
  pop bx
ENDM
;----------------------------------------------------------------------------------------------------------------
;dibuja un icono de bandera en los lugares especificados
;parametros xpos,ypos
dibujar_proceso_bandera PROC
  push bp
  mov bp,sp
  push ax
  push bx

  mov cx,[bp+4]
  mov dx,[bp+6]
  ;Dibujar el mástil de la bandera
  add cx,ancho_celda/12*3
  add dx,alto_celda/6
  mov ax,ancho_celda/12
  mov bx,alto_celda/6*4

  dibujar_caja_llena_llamante cx,dx,ax,bx,7

  ;dibujar la propia bandera
  add cx,ancho_celda/12 ;añadir sólo aumento de x
  mov ax,ancho_celda/3  ;ajustar el ancho de la bandera
  mov bx,alto_celda/6*2 ;ajustar la altura de la bandera

  dibujar_caja_llena_llamante cx,dx,ax,bx,12

  pop bx
  pop ax
  pop bp
  RET
ENDP
;----------------------------------------------------------------------------------------------------------------
dibujar_bandera_llamante MACRO fila,columna
  push cx
  push dx
  ;expandir_coordenadas fila,columna
  obtener_coordenadas_pantalla_llamante fila,columna
  ;push parametros
  push dx
  push cx
  call dibujar_proceso_bandera
  add sp,4
  pop dx
  pop cx
ENDM
;----------------------------------------------------------------------------------------------------------------
;Dibuja un icono de bomba en los lugares especificados.
;parametros xpos,ypos
dibujar_proceso_bomba PROC
  push bp
  mov bp,sp
  push ax
  push bx

  mov cx,[bp+4]
  mov dx,[bp+6]

  mov ax,ancho_celda/7
  mov bx,alto_celda/7
  ;1 parte
  add cx,ancho_celda/7*3
  add dx,alto_celda/7

  dibujar_caja_llena_llamante cx,dx,ax,bx,4

  ;2 parte
  sub cx,ancho_celda/7
  add dx,alto_celda/7
  mov ax,ancho_celda/7*3

  dibujar_caja_llena_llamante cx,dx,ax,bx,4

  ;3 parte
  sub cx,ancho_celda/7
  add dx,alto_celda/7
  mov ax,ancho_celda/7*5
  dibujar_caja_llena_llamante cx,dx,ax,bx,4

  ;4 parte
  add cx,ancho_celda/7
  add dx,alto_celda/7
  mov ax,ancho_celda/7*3
  dibujar_caja_llena_llamante cx,dx,ax,bx,4

  ;5 parte
  add cx,ancho_celda/7
  add dx,alto_celda/7
  mov ax,ancho_celda/7
  dibujar_caja_llena_llamante cx,dx,ax,bx,4

  pop bx
  pop ax
  pop bp
  RET
ENDP
;----------------------------------------------------------------------------------------------------------------
dibujar_bomba_llamante MACRO fila,columna
  push cx
  push dx
  ;expandir_coordenadas fila,columna
  obtener_coordenadas_pantalla_llamante fila,columna
  ;push parametros
  push dx
  push cx
  call dibujar_proceso_bomba
  add sp,4
  pop dx
  pop cx
ENDM
;----------------------------------------------------------------------------------------------------------------
;descubre la célula y muestra su número o bomba
;parametros : fila,columna
mostrar_celda PROC
  push bp
  mov bp,sp
  push ax
  push bx
  color_celda_llamante [bp+4],[bp+6],COLOR_FONDO_CELDA_ABIERTA
  _expandir_llamante [bp+4],[bp+6]
  mov al,[bx + OFFSET grilla]
  ;borrar el medio byte más significativo y ponerlo a 2 (abierto)
  and al,0Fh
  cmp al,0fh
  je bmb
  imprimir_valor_celda [bp+4],[bp+6],ax
  jmp fin
bmb:
  dibujar_bomba_llamante [bp+4],[bp+6]
  ;establecer la celda como abierta
fin:  or al,20h
  mov [bx + OFFSET grilla],al
  dec num_celdas_cerradas
  pop bx
  pop ax
  pop bp
  RET
ENDP
;----------------------------------------------------------------------------------------------------------------
mostrar_celda_llamante_byte MACRO fila_b_dl,columna_b_dh
  push cx
  push dx
  mov cx,0
  mov cl,fila_b_dl
  mov dx,0
  mov dl,columna_b_dh
  mostrar_celda_llamante cx,dx
  pop dx
  pop cx
ENDM
;----------------------------------------------------------------------------------------------------------------
mostrar_celda_llamante MACRO fila,columna
  push columna
  push fila
  call mostrar_celda
  add sp,4
ENDM
;----------------------------------------------------------------------------------------------------------------
;obtener la vista de celda especificada
;introduce fila,columna (2 bytes cada una)
;devuelve el resultado en al
obtener_vista_celda_proceso PROC
  push bp
  mov bp,sp
  push bx
  push cx
  _expandir_llamante [bp+4],[bp+6]
  mov bl,[bx + OFFSET grilla]
  and bl,0F0h
  mov cl,4
  shr bl,cl
  mov al,bl
  pop cx
  pop bx
  pop bp
  RET
ENDP
;----------------------------------------------------------------------------------------------------------------
; esta MACRO usa ax, asi que NO PUEDE ENVIAR LOS PARAMETROS A ESTA MACRO EN AX
;ADVERTENCIA: ESTA MACRO DEBE COLOCARSE ANTES DEL PROCESO abrir_celda, DE LO CONTRARIO OCURRIRÁN ERRORES PORQUE NECESITARÁ UN MONTAJE MULTIPASO.
;IMPORTANTE: esta macro será llamada inicialmente por el manejador de click del ratón. el manejador de click del ratón es responsable de comprobar si esta celda 
; es una bomba o está fuera de la grilla o ... . En otras palabras, sólo llamará a la macro si la celda sobre la que se ha hecho clic está cerrada.
abrir_celda_llamante MACRO fila,columna
  push ax
  mov ax,0
  mov al,columna
  push ax
  mov al,fila
  push ax
  call abrir_celda
  add sp,4
  pop ax
ENDM abrir_celda_llamante
;----------------------------------------------------------------------------------------------------------------
abrir_celda PROC
  ; guarda bp
  push bp
  mov bp,sp
  ; guarda los registros
  push ax
  push bx
  push cx
  push dx
  push si
  
  mov ax,[bp+4] ;1 parametro (fila)
  mov dx,[bp+6] ;2 parametro (columna)
  _expandir_llamante al,dl

  ;si la celda no está "cerrada" (abierta o con bandera), entonces return
  mov cl,[bx + OFFSET grilla]
  and cl,0F0h
  cmp cl,CELDA_CERRADA
  jnz ret_abrir_celda
  
  mostrar_celda_llamante ax,dx

  
  ;si la celda tiene valor entonces devuelve
  mov cl,[bx + OFFSET grilla]
  and cl,0Fh
  cmp cl,0Fh ;si la celda contiene una bom
  jne verificar_no_vacio
  mov bandera_perdedora,1
  
verificar_no_vacio:
  cmp cl,0
  jne ret_abrir_celda

  mov ah,dl ;(al,ah) = (fila,columna)
  ;abrir celdas adyacentes
  mov si,7
  bucle_en_dAr:
    lea bx,dxAr
    mov dl,[bx+si]
    lea bx,dyAr
    mov dh,[bx+si]
    add dl,al
    add dh,ah
    
    _expandir_llamante dl,dh
    mov cl,[bx + OFFSET grilla]
    cmp cl,0Fh
    jge continuar
    abrir_celda_llamante dl,dh

  continuar:
    dec si
    cmp si,0
  jge bucle_en_dAr
  
ret_abrir_celda:
  ; retornar registros
  pop si
  pop dx
  pop cx
  pop bx
  pop ax
  pop bp
  RET
ENDP abrir_celda
;----------------------------------------------------------------------------------------------------------------
obtener_vista_celda_proceso_llamante MACRO fila,columna
  push columna
  push fila
  call obtener_vista_celda_proceso
  add sp,4
ENDM
;----------------------------------------------------------------------------------------------------------------
;obtener el valor de la celda especificada
;introduce fila,columna (2 bytes cada una)
;devuelve el resultado en al
obtener_valor_celda_proceso PROC
  push bp
  mov bp,sp
  push bx
  _expandir_llamante [bp+4],[bp+6]
  mov bl,[bx + OFFSET grilla]
  and bl,0Fh
  mov al,bl
  pop bx
  pop bp
  RET
ENDP
;----------------------------------------------------------------------------------------------------------------
obtener_valor_celda_proceso_llamante MACRO fila,columna
  push columna
  push fila
  call obtener_valor_celda_proceso
  add sp,4
ENDM
;----------------------------------------------------------------------------------------------------------------
ayuda_llamante MACRO columna_w,fila_w
  push fila_w
  push columna_w
  call ayuda
  add sp,4
ENDM ayuda_llamante
;----------------------------------------------------------------------------------------------------------------
ayuda PROC
  ; guarda bp
  push bp
  mov bp,sp
  
  ;guarda los registros
  push ax
  push bx
  push cx
  push dx
  push si
  
  mov cx,[bp+4] ;1 parametro
  mov bx,[bp+6] ;2 parametro
  mov ch,bl ;ahora cl tiene la fila, y ch tiene la columna
  
  mov di,0 ;di contará el número de banderas alrededor de la celda
  mov si,7
  bucle_contador_en_dAr:
    lea bx,dxAr
    mov dl,[bx+si]
    lea bx,dyAr
    mov dh,[bx+si]
    add dl,cl
    add dh,ch

    ;poner dl,dh en puntero word
    push cx
    push dx
    mov cx,0
    mov cl,dh
    mov dh,0
    obtener_vista_celda_proceso_llamante dx,cx ;retorna los resultados en al
    pop dx
    pop cx
    
    cmp al,CELDA_CON_BANDERA
    jne continuar_contador
    inc di
    
  continuar_contador:
    dec si
    cmp si,0
  jge bucle_contador_en_dAr

  ;comprobar si se trata de una solicitud de ayuda válida o no válida
  _expandir_llamante cl,ch
  mov ax,0
  mov al,[bx + OFFSET grilla]
  and al,0Fh
  cmp ax,di
  je ayuda_valida
  jmp ayuda_invalida
  
ayuda_valida:
;imprimir mensaje_ganar
  mov ax,cx ;ahora al tiene la fila y ah la columna
  mov si,7
  bucle_en_dAr_abierto:
    lea bx,dxAr
    mov dl,[bx+si]
    lea bx,dyAr
    mov dh,[bx+si]
    add dl,al
    add dh,ah

    abrir_celda_llamante dl,dh
    
  continuar_abierto:
    dec si
    cmp si,0
  jge bucle_en_dAr_abierto
  jmp ret_ayuda
  
ayuda_invalida:
;imprimir mensaje_perder
  mov ah,2
  mov dl,7
  int 21h
  
ret_ayuda:
  ;retornar registros
  pop si
  pop dx
  pop cx
  pop bx
  pop ax
  pop bp
  
  RET
ENDP ayuda
;----------------------------------------------------------------------------------------------------------------
elegir_tipo PROC
  push ax
  push dx

  ; limpiar pantalla
  mov ax,03h
  int 10h 

  ;Logica
  mov dh,19 ;configurar fila
  mov dl,0 ;configurar columna
  mov ah,2
  int 10h ;configurar cursor

PROMPT:
  imprimir mensaje_elegir_tipo
  mov ah,1
  int 21h
  dec al
  sub al,'0'
  mov tipo_grilla,al
  cmp al,0
  je tipo_0
  cmp al,1
  je tipo_1
  cmp al,2
  je tipo_2

  ;limpiar pantalla
  mov ax,03h
  int 10h 
  
  mov dh,18 ;configurar fila
  mov dl,0 ;configurar columna
  mov ah,2
  int 10h ;configurar cursor
  imprimir mensaje_entrada_invalido
jmp PROMPT
  
tipo_0:
  mov filas,9
  mov columnas,9
  mov numMinas,numPequenias
  jmp ret_elegir_tipo
  
tipo_1:
  mov filas,16
  mov columnas,16
  mov numMinas,numMedianas
  jmp ret_elegir_tipo
  
tipo_2:
  mov filas, 16
  mov columnas, 16
  mov numMinas, numGrandes
  
ret_elegir_tipo:
  pop dx
  pop ax
  RET
ENDP elegir_tipo
;----------------------------------------------------------------------------------------------------------------
comenzar:
  mov ax, @data
  mov ds, ax                  
again:
  mov bx, offset img
  call bmp

  push ax
  mov ah, 8
  int 21h
  pop ax

  call elegir_tipo
  
  ;comenzar vga
  mov ax, 12h
  int 10h

  imprimir mensaje_bienvenida 
  
  ;inicializar velocidad usando la hora actual del sistema
  mov ah, 0
  int 1Ah
  mov rand, dh
  ;inicializar grilla
  init_grid
  dibujar_grilla filas,columnas,start_x,start_y,ancho_celda,alto_celda

  ;iniciar mouse
  mov ax,0
  int 33h
  ;mostrar mouse 
  mov ax,1
  int 33h

  mov bx,0
    ;di representa la bandera de estado de los botones del ratón (1 cuando el botón del ratón está abajo,0 cuando el botón del ratón está arriba)
  mov di,0
bucle_juego:
  xor ax, ax
  mov al, 2
  cmp al, 1
  jne verificar_ganar
  jmp perder

verificar_ganar:
  ; ver si gano
  cmp num_celdas_cerradas, 0  
  jne no_perder
  jmp ganar
  
no_perder:
  ;retraso_1seg
  mov ax,3
  int 33h
  and di,bx
  ;el usuario maneja el mouse
  jnz bucle_juego

  cmp bx,0
  jz bucle_juego ;no se pulsa ningún botón del mouse

  ; comprueba si el click está dentro de la grilla o no
  ; cx tiene las posiciones horizontales del ratón, y dx tiene la vertical
  cmp cx,start_x
  jl bucle_juego

  cmp dx,start_y
  jl bucle_juego

  convertir_coordenadas ;dl tiene el número de fila, cl tiene el número de columna
  ; guardar la salida de convertir_coordenadas en la pila
  push cx
  push dx
  
  cmp dl,filas
  jge bucle_juego
  cmp cl,columnas
  jge bucle_juego

  ;ocultar el mouse
  mov ax,2
  int 33h

  ;comprobar botón derecho
  cmp bx,2
  jne salto_auxiliar
    mov di,0fh
    ;convertir_coordenadas //ya llamado una vez anteriormente
    ;recupera la salida de convertir_coordenadas llamada anteriormente
    pop dx
    pop cx
    
    mov dh,cl
    obtener_vista_celda_proceso_llamante dx,cx
    cmp al,CELDA_ABIERTA
    je verificar_boton_izquierdo
    cmp al,CELDA_CON_BANDERA
    je celda_tiene_bandera
    establecer_celda_con_bandera dl,dh
    dibujar_bandera_llamante dx,cx
    jmp verificar_boton_izquierdo
  salto_auxiliar:
    cmp bx,2
    jne verificar_boton_izquierdo
    celda_tiene_bandera:
      color_celda_llamante dx,cx,COLOR_FONDO_CELDA_CERRADA
      establecer_celda_cerrada dl,dh
  ;compruebo el botón izquierdo
  verificar_boton_izquierdo:
    cmp bx,1
    jne resetear_raton
    mov di,0fh
    ;convertir_coordenadas
    ;recuperar la salida de convertir_coordenadas previamente llamada
    pop dx
    pop cx

obtener_vista_celda_proceso_llamante dx,cx
cmp al,CELDA_ABIERTA
jne llamar_abrir_celda
ayuda_llamante dx,cx
jmp resetear_raton

llamar_abrir_celda:
    abrir_celda_llamante dl,cl
    xor dh,dh
    xor ch,ch
    ;si la celda no fue abierta (con bandera) omitir la comprobación de la bomba
    obtener_vista_celda_proceso_llamante dx,cx
    cmp al,CELDA_ABIERTA
    jne resetear_raton
    ;checkear bomba
    obtener_valor_celda_proceso_llamante dx, cx
    cmp al, 0fh ;bomba
    je perder
    ;checkear ganador
    cmp num_celdas_cerradas, 0
    je ganar    
  resetear_raton:
    ;mostrar cursor del mouse
    mov ax, 1
    int 33h
  jmp bucle_juego

perder:
  mov bx, offset perd
  call bmp
  jmp cerrar

ganar:
  mov bx, offset gan
  call bmp
  jmp cerrar

intermedio:
  xor bx, bx
  xor ax, ax
  xor dx, dx
  xor cx, cx
  xor si, si
  xor di, di
  jmp again

cerrar:
  int 81h
  cmp al, 2
  je intermedio
  mov ax, 4c00h                 
  int 21h                    ;termina el programa
End comenzar