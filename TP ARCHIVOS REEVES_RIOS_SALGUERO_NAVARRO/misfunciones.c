#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "misfunciones.h"

//Crea archivo
void creaArchivo(FILE *archivoBinario, const struct propiedad propiedades[], size_t numPropiedades) {
    archivoBinario = fopen("propiedades.dat", "wb");
    if (archivoBinario == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    // Escribe las propiedades en el archivo binario
    for (size_t i = 0; i < numPropiedades; i++) {
        fwrite(&propiedades[i], sizeof(struct propiedad), 1, archivoBinario);
    }

    printf("Archivo creado exitosamente\n\n");

    // Cierra el archivo
    fclose(archivoBinario);
}

//Imprime los datos
void imprimirDatos(FILE *archivoBinario) {
    archivoBinario = fopen("propiedades.dat", "rb");
    if (archivoBinario == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    printf("%-3s|%-10s|%-20s|%-19s|%-12s|%-7s|%-12s|%-16s|%-10s|%-7s|%-20s|%-20s|%-6s|%-8s\n",
        "ID", "FECHA ING", "ZONA", "CIUDAD", "DORMITORIOS", "BA\xA4OS",
        "SUP. TOTAL", "SUP. CUBIERTA", "PRECIO", "MONEDA", "TIPO PROP", "OPERACI\xA2N", "FECHA SALIDA", "ESTADO");

    struct propiedad temp;  // Variable temporal para almacenar cada registro

    fseek(archivoBinario, 0, SEEK_SET);
    while (fread(&temp, sizeof(struct propiedad), 1, archivoBinario) == 1) {
        printf("%3d|%02d/%02d/%d|%20s|%19s|%12d|%7d|%12.2f|%16.2f|%10.2f|%7s|%20s|%20s| %02d/%02d/%02d |%d\n",
            temp.id, temp.fechaIngreso.dia, temp.fechaIngreso.mes, temp.fechaIngreso.anio, temp.zona, temp.ciudad,
            temp.dormitorio, temp.banios, temp.sup_total, temp.sup_cubierta, temp.precio, temp.moneda,
            temp.tipo_propiedad, temp.operacion, temp.fechaSalida.dia, temp.fechaSalida.mes, temp.fechaSalida.anio, temp.estado);
    }
    fclose(archivoBinario);
}

//Calcula el nro de propiedades en el archivo binario
int calcularNumeroPropiedades() {
    FILE *archivoBinario = fopen("propiedades.dat", "rb");
    if (archivoBinario == NULL) {
        perror("Error al abrir el archivo");
        return -1;
    }

    // Calcula el tamaño del archivo en bytes
    fseek(archivoBinario, 0, SEEK_END);
    long tamanoArchivo = ftell(archivoBinario);

    // Calcula el número de propiedades en el archivo
    long tamanoStruct = sizeof(struct propiedad);
    //verifica tamaño del archivo
    if (tamanoArchivo % tamanoStruct != 0){
        perror("El archivo no tiene un formato v\xE1lido.");
        fclose(archivoBinario);
        return -1;
    }
    int numPropiedades = tamanoArchivo / tamanoStruct;
    fclose(archivoBinario);
    return numPropiedades;
}

//Comprueba si no estas pisando un dato
int Existe(FILE *file, int id) {
    struct propiedad prop;
    rewind(file);
    while (fread(&prop, sizeof(struct propiedad), 1, file)) {
        if (prop.id == id) {
            return 1; // ID ya existe
        }
    }
    return 0; // ID no existe
}

//Funcion para validar fecha
void validarFecha(struct fechas *auxiliar) {
    printf("Ingrese la fecha (d%ca): ", 161);
    scanf("%d", &auxiliar->dia);
    fflush(stdin);
    while(auxiliar->dia<1||auxiliar->dia>31){ //Verifica que el día sea entre 1 y 31
        printf("\nNo es un d%ca v%clido, ingrese otro: ", 161, 160);
        scanf("%d", &auxiliar->dia);
        fflush(stdin);
    }
    printf("Ingrese la fecha (mes): ");
    scanf("%d", &auxiliar->mes);
    fflush(stdin);
    while(auxiliar->mes<1||auxiliar->mes>12){ //Verifica que el mes sea entre 1 y 12
        printf("\nNo es un mes v%clido, ingrese otro: ", 160);
        scanf("%d", &auxiliar->mes);
        fflush(stdin);
    }
    if(auxiliar->dia>29&&auxiliar->mes==2){ //Si el día es mayor a 29 y el mes es febrero, vuelve a pedir el mes
        while(auxiliar->mes==2){
            printf("\nFebrero no puede tener m%cs de 29 d%cas, ingrese otro: ", 160, 161);
            scanf("%d", &auxiliar->mes);
            fflush(stdin);
        }
    } else if((auxiliar->dia==31)&&
    (auxiliar->mes!=1&&auxiliar->mes!=3&&auxiliar->mes!=5&&
    auxiliar->mes!=7&&auxiliar->mes!=8&&auxiliar->mes!=10&&
    auxiliar->mes!=12)){ //Si el día es igual a 31 y el mes no tiene 31 días, vuelve a pedir el mes
        while(auxiliar->mes!=1&&auxiliar->mes!=3&&auxiliar->mes!=5&&
        auxiliar->mes!=7&&auxiliar->mes!=8&&auxiliar->mes!=10&&
        auxiliar->mes!=12){
            printf("\nEste mes no puede tener m%cs de 30 d%cas, ingrese otro: ", 160, 161);
            scanf("%d", &auxiliar->mes);
            fflush(stdin);
        }
    }
    printf("Ingrese la fecha (a%co): ", 164);
    scanf("%d", &auxiliar->anio);
    fflush(stdin);
    while(auxiliar->anio<2000||auxiliar->anio>2023){ //Verifica que el año sea entre 2000 y 2023
        printf("\nNo es un a%co v%clido, ingrese otro: ", 164, 160);
        scanf("%d", &auxiliar->anio);
        fflush(stdin);
    }
    if((auxiliar->dia==29&&auxiliar->mes==2)&&auxiliar->anio%4!=0){
        while(auxiliar->anio%4!=0){ //Si el día es igual a 29, el mes es febrero y el año no es bisiesto, vuelve a pedir el año
        printf("\nNo es un a%co v%clido, ingrese otro: ", 164, 160);
        scanf("%d", &auxiliar->anio);
        fflush(stdin);
        }
    } else if((auxiliar->dia==29&&auxiliar->mes==2)&&(auxiliar->anio%100==0&&auxiliar->anio%400!=0)){
        while(auxiliar->anio%100==0&&auxiliar->anio%400!=0){ //Si el día es igual a 29, el mes es febrero y el año no es bisiesto, vuelve a pedir el año
            printf("\nNo es un a%co v%clido, ingrese otro: ", 164, 160);
            scanf("%d", &auxiliar->anio);
            fflush(stdin);
        }
    }
}
// Funcion que agrega un nueva propiedad
int agregarPropiedad(int numProp) {
    int opcionMoneda=0, opcionProp=0, opcionOP=0, numero, valido=0, idPersonalizado = 0;
    char inputZona[50],inputCiudad[50], inputDorm[10], inputBanio[10], inputSupTot[10], inputSupCub[10], inputPrecio[10], inputMoneda[256], inputTipoPropiedad[256], inputOperacion[256];

FILE *archivoBinario = fopen("propiedades.dat", "r+b");
struct propiedad prop;

    while (1){
        printf("\nIngrese el ID personalizado para la nueva propiedad: ");
        if (scanf("%d", &idPersonalizado) != 1 || idPersonalizado <= 0){
            fflush(stdin);
            //Validación nro positivo/caracter no válido
            printf("El ID no es v%clido, ingrese un valor numerico entero mayor a 0 \n", 160);
            while (getchar() != '\n');
        } else {
            int idExistente = 0; //flag

            fseek(archivoBinario, 0, SEEK_SET);
            while(fread(&prop, sizeof(struct propiedad), 1, archivoBinario)==1){
                if (prop.id == idPersonalizado){
                    idExistente = 1;
                    break;
                }
            }

            if (idExistente) {
                //Validación id existente
                printf ("Ya existe una propiedad con ese ID \n");
            } else {
                break;
            }
        }

    }

    struct propiedad nuevaPropiedad;

    nuevaPropiedad.id = idPersonalizado;

    time_t t;
    struct tm *fecha_actual;
    t = time(NULL);
    fecha_actual = localtime(&t);
    nuevaPropiedad.fechaIngreso.dia = fecha_actual->tm_mday;
    nuevaPropiedad.fechaIngreso.mes = fecha_actual->tm_mon + 1;
    nuevaPropiedad.fechaIngreso.anio = fecha_actual->tm_year + 1900;
    fflush(stdin);

    do {
    numero = 0;
    printf("Zona: ");
    fgets(inputZona, sizeof(inputZona), stdin);
    inputZona[strcspn(inputZona, "\n")] = '\0';  // Elimina el caracter de nueva linea si esta presente
    for (int i = 0; inputZona[i] != '\0'; i++) {
        if (isdigit(inputZona[i])) {
            numero = 1;
            break;
        }
    }
    if (strlen(inputZona) == 0 || numero) {
        printf("Error: La zona no puede estar vac%ca y no debe contener n%cmeros. Ingrese una zona v%clida.\n", 161, 163, 160);
    }
} while (strlen(inputZona) == 0 || numero);
// Convierte la primera letra de cada palabra a mayuscula
int mayuscula = 1; // Indica que la próxima letra debe ser mayúscula
for (int i = 0; inputZona[i] != '\0'; i++) {
    if (isalpha(inputZona[i])) {
        if (mayuscula) {
            inputZona[i] = toupper(inputZona[i]);
            mayuscula = 0;
        } else {
            inputZona[i] = tolower(inputZona[i]);
        }
    } else {
        mayuscula = 1; // Establece la proxima letra como mayuscula
    }
}
// Copia la zona formateada en la estructura nuevaPropiedad
strncpy(nuevaPropiedad.zona, inputZona, sizeof(nuevaPropiedad.zona));
nuevaPropiedad.zona[sizeof(nuevaPropiedad.zona) - 1] = '\0'; // Asegura que la cadena este terminadaa

    do {
    numero = 0;
    printf("Ciudad: ");
    fgets(inputCiudad, sizeof(inputCiudad), stdin);
    inputCiudad[strcspn(inputCiudad, "\n")] = '\0';  // Elimina el caracter de nueva linea si esta presente
    for (int i = 0; inputCiudad[i] != '\0'; i++) {
        if (isdigit(inputCiudad[i])) {
            numero = 1;
            break;
        }
    }
    if (strlen(inputCiudad) == 0 || numero) {
        printf("Error: La ciudad no puede estar vac%ca y no debe contener n%cmeros. Ingrese una ciudad v%clida.\n", 161, 163, 160);
    }
} while (strlen(inputCiudad) == 0 || numero);
// Convierte la primera letra de cada palabra a mayuscula
mayuscula = 1; // Indica que la proxima letra debe ser mayuscula
for (int i = 0; inputCiudad[i] != '\0'; i++) {
    if (isalpha(inputCiudad[i])) {
        if (mayuscula) {
            inputCiudad[i] = toupper(inputCiudad[i]);
            mayuscula = 0;
        } else {
            inputCiudad[i] = tolower(inputCiudad[i]);
        }
    } else {
        mayuscula = 1; // Establece la proxima letra como mayuscula
    }
}
// Copia la ciudad formateada en la estructura nuevaPropiedad
strncpy(nuevaPropiedad.ciudad, inputCiudad, sizeof(nuevaPropiedad.ciudad));
nuevaPropiedad.ciudad[sizeof(nuevaPropiedad.ciudad) - 1] = '\0'; // Asegura que la cadena este terminada

    while (1) {
        printf("Dormitorios: ");
        if (fgets(inputDorm, sizeof(inputDorm), stdin) != NULL) {
            if (sscanf(inputDorm, "%d", &nuevaPropiedad.dormitorio) == 1) { /// Si es un numero se almacena
                break;
            } else {
                printf("Error: Ingrese un n%cmero para dormitorios.\n", 163);
            }
        }
    }
    while (1) {
        printf("Ba%cos: ", 164);
        if (fgets(inputBanio, sizeof(inputBanio), stdin) != NULL) {
            if (sscanf(inputBanio, "%d", &nuevaPropiedad.banios) == 1) { /// Si es un numero se almacena
                break;
            } else {
                printf("Error: Ingrese un n%cmero para ba%cos.\n",163, 164);
            }
        }
    }
    while (1) {
        printf("Superficie Total: ");
        if (fgets(inputSupTot, sizeof(inputSupTot), stdin) != NULL) {
            if (sscanf(inputSupTot, "%f", &nuevaPropiedad.sup_total) == 1) { /// Si es un numero se almacena
                break;
            } else {
                printf("Error: Ingrese un n%cmero para superficie total.\n", 163);
            }
        }
    }

    while (1) {
        printf("Superficie Cubierta: ");
        if (fgets(inputSupCub, sizeof(inputSupCub), stdin) != NULL) {
            if (sscanf(inputSupCub, " %f", &nuevaPropiedad.sup_cubierta) == 1) { /// Si es un numero se almacena
                while(nuevaPropiedad.sup_cubierta > nuevaPropiedad.sup_total){
                    printf("La superficie cubierta no puede ser mayor a la total. \n");
                    printf("Superficie Cubierta: ");
                    if (fgets(inputSupCub, sizeof(inputSupCub), stdin) != NULL) {
                        if (sscanf(inputSupCub, " %f", &nuevaPropiedad.sup_cubierta) == 1) { /// Si es un numero se almacena
                            break;
                        }
                    }
                }
                break;
            }
        } else {
                printf("Error: Ingrese un n%cmero para superficie cubierta.\n", 163);
            }
        }

    while (1) {
        printf("Precio: ");
        if (fgets(inputPrecio, sizeof(inputPrecio), stdin) != NULL) {
            if (sscanf(inputPrecio, "%f", &nuevaPropiedad.precio) == 1) { /// Si es un numero se almacena
                break;
            } else {
                printf("Error: Ingrese un n%cmero para precio.\n", 163);
            }
        }
    }

    while (!valido){
        printf("Moneda: \n");
        printf("1. USD\n");
        printf("2. PESOS\n");
        //Validacion tipo de moneda
        if(fgets(inputMoneda, sizeof(inputMoneda), stdin)) {
            if (sscanf(inputMoneda, "%d", &opcionMoneda) == 1){
                if (opcionMoneda == 1 || opcionMoneda == 2){
                    valido = 1;
                }
            }
        }
    if (!valido){
        printf("Opcion inv%clida, ingrese una de las que se muestran en pantalla: \n", 160);
    }
    }
    valido = 0;
    if (opcionMoneda == 1){
        strcpy(nuevaPropiedad.moneda, "USD");
    } else if (opcionMoneda == 2){
        strcpy(nuevaPropiedad.moneda, "PESOS");
    }

    while (!valido){
        printf("Tipo de propiedad: \n");
        printf("1. PH\n");
        printf("2. Casa\n");
        printf("3. Departamento\n");
        //Validacion tipo de propiedad
        if(fgets(inputTipoPropiedad, sizeof(inputTipoPropiedad), stdin)){
            if (sscanf(inputTipoPropiedad, "%d", &opcionProp)==1){
                if (opcionProp == 1 || opcionProp == 2 || opcionProp == 3){
                    valido = 1;
                }
            }
        }
        if (!valido){
            printf("Opci%cn inv%clida, ingrese una de las que se muestran en pantalla: \n", 162, 160);
        }
    }
    valido = 0;
    if (opcionProp == 1) {
        strcpy(nuevaPropiedad.tipo_propiedad, "PH");
    } else if (opcionProp == 2) {
        strcpy(nuevaPropiedad.tipo_propiedad, "Casa");
    } else if (opcionProp == 3) {
        strcpy(nuevaPropiedad.tipo_propiedad, "Departamento");
    }

    while (!valido){
    printf("Operaci%cn: \n", 162);
    printf("1. Venta\n");
    printf("2. Alquiler\n");
    printf("3. Alquiler temporal\n");
    //Validacion tipo de operacion
    if (fgets(inputOperacion, sizeof(inputOperacion), stdin)){
        if (sscanf(inputOperacion, "%d", &opcionOP)==1){
            if (opcionOP == 1 || opcionOP == 2 || opcionOP == 3){
                valido = 1;
            }
        }
    }
    if (!valido){
        printf("Opci%cn inv%clida, ingrese una de las que se muestran en pantalla: \n", 162, 160);
    }
    }
    if (opcionOP == 1) {
        strcpy(nuevaPropiedad.operacion, "Venta");
    } else if (opcionOP == 2) {
        strcpy(nuevaPropiedad.operacion, "Alquiler");
    } else if (opcionOP == 3) {
        strcpy(nuevaPropiedad.operacion, "Alquiler temporal");
    }
    fflush(stdin);
    nuevaPropiedad.fechaSalida.dia = 00;
    nuevaPropiedad.fechaSalida.mes = 00;
    nuevaPropiedad.fechaSalida.anio = 00;
    nuevaPropiedad.estado = 1;


    fseek(archivoBinario, sizeof(struct propiedad)*(idPersonalizado-1), SEEK_SET);

    fwrite(&nuevaPropiedad, sizeof(struct propiedad), 1, archivoBinario);
    fclose(archivoBinario);
    printf("Nueva propiedad agregada \n");

    numProp = idPersonalizado;
    return numProp;
}

// Función para verificar si un registro ya existe en el archivo de texto
int registroExisteEnArchivo(FILE *archivo, int id) {
    char linea[512];  // Ajusta el tamaño según tus necesidades
    fseek(archivo, 0, SEEK_SET);  // Coloca el puntero al inicio del archivo
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        int registroId;
        if (sscanf(linea, "%d", &registroId) == 1) {
            if (registroId == id) {
                return 1;  // El registro ya existe
            }
        }
    }
    return 0;  // El registro no existe
}

void bajaFisica(FILE *archivoBinario, char nombreArchivo[]) {
    struct propiedad prop;
    archivoBinario = fopen("propiedades.dat", "rb");
    if (archivoBinario == NULL) {
        perror("Error al abrir el archivo para lectura");
        return;
    }
    FILE *archivoTexto = fopen(nombreArchivo, "a+");
    if (archivoTexto == NULL) {
        // Si el archivo de texto no existe, lo creamos
        archivoTexto = fopen(nombreArchivo, "w");
        if (archivoTexto == NULL) {
            perror("Error al abrir el archivo de texto");
            fclose(archivoBinario);
            return;
        }
    }
    while (fread(&prop, sizeof(struct propiedad), 1, archivoBinario) == 1) {
        if (prop.estado==0 && prop.id!=0) {
            // Verifica si el registro ya existe en el archivo de texto
            if (registroExisteEnArchivo(archivoTexto, prop.id)==0) {
                // Si no existe, lo agrega
                //Guarda las bajas del archivo binario en el archivo de texto.
                fprintf(archivoTexto, "%02d/%02d/%d|%20s|%19s|%12d|%7d|%12.2f|%16.2f|%10.2f|%7s|%20s|%20s| %02d/%02d/%02d\n",
                        prop.fechaIngreso.dia, prop.fechaIngreso.mes, prop.fechaIngreso.anio,
                        prop.zona, prop.ciudad, prop.dormitorio, prop.banios, prop.sup_total, prop.sup_cubierta, prop.precio,
                        prop.moneda, prop.tipo_propiedad, prop.operacion, prop.fechaSalida.dia, prop.fechaSalida.mes, prop.fechaSalida.anio);
            }
        }
    }
    printf("\n--Archivo actualizado--\n");
    fclose(archivoTexto);
    fclose(archivoBinario);
}

void blancos(FILE *archivoBinario) {
    struct propiedad prop;
    struct propiedad CERO={0};
    archivoBinario = fopen("propiedades.dat", "rb");
    if (archivoBinario == NULL) {
        perror("Error al abrir el archivo para escritura y lectura");
        return;
    }
    FILE *tempFile = fopen("temp.dat", "w+b");  // Archivo temporal
    if (tempFile == NULL) {
        perror("Error al abrir el archivo temporal");
        fclose(archivoBinario);
        return;
    }
    fseek(archivoBinario, 0, SEEK_SET);
    while (fread(&prop, sizeof(struct propiedad), 1, archivoBinario) == 1) {
        if (prop.estado == 1) {
            fwrite(&prop, sizeof(struct propiedad), 1, tempFile);
        } else if (prop.estado==0){
            fwrite(&CERO, sizeof(struct propiedad), 1, tempFile);
        }
    }
    fclose(archivoBinario);
    fclose(tempFile);
    remove("propiedades.dat");  // Borra el archivo original
    rename("temp.dat", "propiedades.dat");  // Cambia el nombre del archivo temporal
    remove("temp.dat");
}

int compararFechas(struct fechas fecha1, struct fechas fecha2) {
    if (fecha1.anio < fecha2.anio) {
        return -1; // fecha1 es anterior a fecha2
    } else if (fecha1.anio > fecha2.anio) {
        return 1; // fecha1 es posterior a fecha2
    } else {
        if (fecha1.mes < fecha2.mes) {
            return -1; // fecha1 es anterior a fecha2
        } else if (fecha1.mes > fecha2.mes) {
            return 1; // fecha1 es posterior a fecha2
        } else {
            if (fecha1.dia < fecha2.dia) {
                return -1; // fecha1 es anterior a fecha2
            } else if (fecha1.dia > fecha2.dia) {
                return 1; // fecha1 es posterior a fecha2
            } else {
                return 0; // Las fechas son iguales
            }
        }
    }
}