#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
// Libreria personalizada
#include "misfunciones.h"

int main(){
    int opcion; //variable de opción para el switch
    int sub_opcion;
    int sub_opcion2;
    int sub_opcion3;
    int sub_sub_opcion;
    int sub_sub_opcion2;
    int flag;
    int valido=0;
    int IDModif=0;
    int id; //variable para la búsqueda por id
    char tipoPropiedad[50];
    char inputPropiedad[50];
    char tipoOperacion[50];
    FILE *archivoBinario;
    FILE *archivoTexto;
    struct propiedad prop;

    time_t t;
    struct tm *fecha_actual;
    char fecha_str[20];

    t = time(NULL);
    fecha_actual = localtime(&t);

    // Formatea la fecha como "YYYY-MM-DD"
    strftime(fecha_str, sizeof(fecha_str), "%Y-%m-%d", fecha_actual);

    // Construye el nombre del archivo de texto con la fecha actual
    char nombreArchivo[50];
    sprintf(nombreArchivo, "propiedades_bajas_%s.xyz", fecha_str);


    struct propiedad propiedades[] = {
                    {1, {23, 12, 2019}, "Capital Federal", "San Cristobal", 7, 2, 140.0, 140.0, 153000.0, "USD", "Departamento", "Venta", {0, 0, 0}, 1},
                    {2, {21, 11, 2019}, "Capital Federal", "Boedo", 1, 2, 70.0, 58.0, 159000.0, "USD", "PH", "Venta", {5, 1, 2020}, 0},
                    {3, {1, 11, 2019}, "Capital Federal", "Palermo", 1, 1, 45.0, 45.0, 125000.0, "USD", "Departamento", "Venta", {0, 0, 0}, 1},
                    {4, {23, 12, 2019}, "Capital Federal", "Palermo", 1, 1, 85.0, 50.0, 295000.0, "PESOS", "PH", "Alquiler", {1, 4, 2020}, 0},
                    {5, {11, 3, 2020}, "G.B.A. Zona Sur", "La Plata", 1, 1, 50.0, 35.0, 40000.0, "USD", "Casa", "Venta", {24, 7, 2021}, 0},
                    {6, {1, 11, 2019}, "Capital Federal", "Villa Crespo", 1, 1, 56.0, 56.0, 150000.0, "USD", "PH", "Venta", {9, 2, 2020}, 0},
                    {7, {31, 10, 2019}, "Capital Federal", "Villa Crespo", 1, 1, 70.0, 70.0, 159500.0, "USD", "Departamento", "Venta", {0, 0, 0}, 0},
                    {8, {31, 10, 2019}, "Capital Federal", "Villa Crespo", 1, 1, 70.0, 70.0, 159500.0, "PESOS", "PH", "Alquiler", {8, 2, 2020}, 0},
                    {9, {23, 12, 2019}, "Capital Federal", "Parque Patricios", 1, 1, 45.0, 37.0, 2400.0, "USD", "Departamento", "Alquiler temporal", {0, 0, 0}, 1},
                    {10, {23, 12, 2019}, "Capital Federal", "Parque Patricios", 1, 1, 45.0, 37.0, 89000.0, "USD", "Casa", "Venta", {5, 1, 2020}, 0},
                    {11, {7, 12, 2019}, "Capital Federal", "Villa Pueyrred\xA2n", 1, 2, 66.0, 49.0, 170000.0, "USD", "PH", "Venta", {16, 3, 2020}, 0},
                    {12, {26, 10, 2019}, "Capital Federal", "Boedo", 1, 1, 68.0, 59.0, 149000.0, "PESOS", "Departamento", "Alquiler", {1, 4, 2020}, 0},
                    {13, {19, 12, 2019}, "Capital Federal", "Boedo", 1, 1, 50.0, 44.0, 115000.0, "USD", "Departamento", "Venta", {28, 3, 2020}, 0},
                    {14, {30, 11, 2019}, "G.B.A. Zona Norte", "Pilar", 1, 1, 50.0, 35.0, 145000.0, "PESOS", "Departamento", "Alquiler", {0, 0, 0}, 1},
                };

    struct fechas auxiliar1, auxiliar2;//struct auxiliar

    int numProp = sizeof(propiedades) / sizeof(propiedades[0]);
    do {
        printf("\n--------------------------------\n");
        printf("|Men%c de opciones inmobiliarias|\n", 163);
        printf("--------------------------------\n");
        printf("1. Crear archivo binario \n");
        printf("2. Listado archivo binario \n");
        printf("3. Alta de propiedad \n");
        printf("4. B%csqueda de propiedad \n", 163);
        printf("5. Modificaci%cn de propiedad \n", 162);
        printf("6. Baja l%cgica de propiedad \n", 162);
        printf("7. Baja f%csica de propiedad \n", 161);
        printf("8. Listar bajas \n");
        printf("9. Cerrar men%c \n", 163);
        printf("Seleccione una opci%cn: ", 162);
        scanf("%d", &opcion);
        printf("\n");

        switch (opcion) {
            case 1:
                creaArchivo(archivoBinario, propiedades, numProp);
                break;

            case 2:
                do {
                    archivoBinario = fopen("propiedades.dat", "rb");
                                if (archivoBinario == NULL) {
                                    perror("Error al abrir el archivo para lectura");
                                    return 1;
                                }
                    printf("1. Listar todo \n");
                    printf("2. Solo clientes activos \n");
                    printf("3. Ingreso por teclado de un tipo de propiedad \n");
                    printf("4. Ingreso de un rango de tiempo de ingreso \n");
                    printf("5. Volver al men%c principal \n", 163);
                    printf("Seleccione una opci%cn \n", 162);
                    scanf("%d", &sub_opcion);
                    printf("\n");

                    switch (sub_opcion) {
                        case 1:
                            imprimirDatos(archivoBinario);
                            printf("\n-------------------------------------------------------------------------------------------------------------\n");
                            sub_opcion = 5;
                            break;

                        case 2:;

                            //Emite unicamente los que poseen estado ACTIVO
                            printf("%-3s|%-10s|%-20s|%-19s|%-12s|%-7s|%-12s|%-16s|%-10s|%-7s|%-20s|%-20s|%-6s\n",
                                "ID", "FECHA ING", "ZONA", "CIUDAD", "DORMITORIOS", "BA\xA4OS",
                                "SUP. TOTAL", "SUP. CUBIERTA", "PRECIO", "MONEDA", "TIPO PROP", "OPERACI\xA2N", "FECHA SALIDA");
                            fseek(archivoBinario, 0, SEEK_SET);
                            while (fread(&prop, sizeof(struct propiedad), 1, archivoBinario) == 1) {
                                if(prop.estado==1){
                                    printf("%3d|%02d/%02d/%d|%20s|%19s|%12d|%7d|%12.2f|%16.2f|%10.2f|%7s|%20s|%20s| %02d/%02d/%02d\n",
                                        prop.id, prop.fechaIngreso.dia, prop.fechaIngreso.mes, prop.fechaIngreso.anio,
                                        prop.zona, prop.ciudad, prop.dormitorio, prop.banios, prop.sup_total, prop.sup_cubierta, prop.precio,
                                        prop.moneda, prop.tipo_propiedad, prop.operacion, prop.fechaSalida.dia, prop.fechaSalida.mes, prop.fechaSalida.anio);
                                    }
                            }
                            printf("\n-------------------------------------------------------------------------------------------------------------\n");
                            fclose(archivoBinario);
                            sub_opcion = 5;
                            break;

                        case 3:;
                            fflush(stdin);
                            valido=0;
                            // Lista los datos según un tipo de propiedad
                            while(!valido){
                            printf("Ingrese el tipo de propiedad: \n");
                            printf("1. PH\n");
                            printf("2. Casa\n");
                            printf("3. Departamento\n");
                            if(fgets(inputPropiedad, sizeof(inputPropiedad), stdin)){
                                if(sscanf(inputPropiedad, "%d", &sub_sub_opcion)==1){
                                    if(sub_sub_opcion == 1 || sub_sub_opcion == 2 || sub_sub_opcion == 3){
                                        valido = 1;
                                    }
                                }
                            }
                            if(!valido){
                                printf("Opci%cn inv%clida, elija una de las que se muestra en pantalla \n",162,160);
                            }
                            }
                            valido = 0;
                            if (sub_sub_opcion == 1) {
                            strcpy(tipoPropiedad, "PH");
                            } else if (sub_sub_opcion == 2) {
                            strcpy(tipoPropiedad, "Casa");
                            } else if (sub_sub_opcion == 3) {
                            strcpy(tipoPropiedad, "Departamento");
                            }
                            printf("%-3s|%-10s|%-20s|%-19s|%-12s|%-7s|%-12s|%-16s|%-10s|%-7s|%-20s|%-20s|%-6s\n",
                                "ID", "FECHA ING", "ZONA", "CIUDAD", "DORMITORIOS", "BA\xA4OS",
                                "SUP. TOTAL", "SUP. CUBIERTA", "PRECIO", "MONEDA", "TIPO PROP", "OPERACI\xA2N", "FECHA SALIDA");
                            fseek(archivoBinario, 0, SEEK_SET);
                            while (fread(&prop, sizeof(struct propiedad), 1, archivoBinario) == 1) {
                                if(strcmp(prop.tipo_propiedad, tipoPropiedad)==0){
                                    printf("%3d|%02d/%02d/%d|%20s|%19s|%12d|%7d|%12.2f|%16.2f|%10.2f|%7s|%20s|%20s| %02d/%02d/%02d\n",
                                        prop.id, prop.fechaIngreso.dia, prop.fechaIngreso.mes, prop.fechaIngreso.anio,
                                        prop.zona, prop.ciudad, prop.dormitorio, prop.banios, prop.sup_total, prop.sup_cubierta, prop.precio,
                                        prop.moneda, prop.tipo_propiedad, prop.operacion, prop.fechaSalida.dia, prop.fechaSalida.mes, prop.fechaSalida.anio);
                                    }
                            }
                            printf("\n-------------------------------------------------------------------------------------------------------------\n");
                            fclose(archivoBinario);
                            sub_opcion = 5;
                            break;

                        case 4:
                            // Lista los datos según una fecha de ingreso
                            archivoBinario = fopen("propiedades.dat", "rb");
                                if (archivoBinario == NULL) {
                                    perror("Error al abrir el archivo para lectura");
                                    return 1;
                                }
                            printf("\n--------DESDE-------\n");
                            validarFecha(&auxiliar1);

                            printf("\n--------HASTA-------\n");
                            validarFecha(&auxiliar2);

                            printf("%-3s|%-10s|%-20s|%-19s|%-12s|%-7s|%-12s|%-16s|%-10s|%-7s|%-20s|%-20s|%-6s\n",
                                "ID", "FECHA ING", "ZONA", "CIUDAD", "DORMITORIOS", "BA\xA4OS",
                                "SUP. TOTAL", "SUP. CUBIERTA", "PRECIO", "MONEDA", "TIPO PROP", "OPERACI\xA2N", "FECHA SALIDA");
                                fseek(archivoBinario, 0, SEEK_SET);
                            while (fread(&prop, sizeof(struct propiedad), 1, archivoBinario) == 1) {
                                if(compararFechas(prop.fechaIngreso, auxiliar1) >= 0 &&
                                    compararFechas(prop.fechaIngreso, auxiliar2) <= 0){
                                    printf("%3d|%02d/%02d/%d|%20s|%19s|%12d|%7d|%12.2f|%16.2f|%10.2f|%7s|%20s|%20s| %02d/%02d/%02d\n",
                                        prop.id, prop.fechaIngreso.dia, prop.fechaIngreso.mes, prop.fechaIngreso.anio,
                                        prop.zona, prop.ciudad, prop.dormitorio, prop.banios, prop.sup_total, prop.sup_cubierta, prop.precio,
                                        prop.moneda, prop.tipo_propiedad, prop.operacion, prop.fechaSalida.dia, prop.fechaSalida.mes, prop.fechaSalida.anio);
                                    }
                            }
                            printf("\n-------------------------------------------------------------------------------------------------------------\n");
                            fclose(archivoBinario);
                            sub_opcion = 5;
                            break;

                        case 5:
                            printf("Vuelve al men%c principal \n", 163); //Agrego el mensajito para que tire este y no el del default cuando cierra
                            break;

                        default:
                            printf("No es una opci%cn v%clida dentro del men%c \n", 162, 160, 163);
                    }
                } while (sub_opcion != 5);
                break;

            case 3:
                if (archivoBinario == NULL) {
                    perror("Error al abrir el archivo");
                    return 1;
                }

                // Llamar a la función para agregar una nueva propiedad con ID personalizado
                numProp = agregarPropiedad(propiedades, numProp);

                break;

            case 4:
                do {
                    printf("1. B%csqueda por id \n", 163);
                    printf("2. B%csqueda por tipo de operaci%cn y tipo de propiedad \n", 163, 162);
                    printf("3. Volver al men%c principal \n", 163);
                    printf("Selecciona una opci%cn: ", 162);
                    scanf("%d", &sub_opcion2);
                    printf("\n");

                    switch (sub_opcion2) {
                        case 1:
                            flag=0;
                            // Busca y emite los datos según un id
                            archivoBinario = fopen("propiedades.dat", "rb");
                                if (archivoBinario == NULL) {
                                    perror("Error al abrir el archivo para lectura");
                                    return 1;
                                }
                            printf("Ingrese el ID: ");
                            scanf("%d", &id);
                            fflush(stdin);
                            while(id<1){ // Corrobora que el id sea un número positivo
                                printf("No es un ID v%clido\n", 160);
                                printf("Ingrese el ID: ");
                                scanf("%d", &id);
                                fflush(stdin);
                            }
                            
                            while (flag == 0 && fread(&prop, sizeof(struct propiedad), 1, archivoBinario)==1){
                                if (prop.id == id){
                                    printf("%-3s|%-10s|%-20s|%-19s|%-12s|%-7s|%-12s|%-16s|%-10s|%-7s|%-20s|%-20s|%-6s\n",
                                        "ID", "FECHA ING", "ZONA", "CIUDAD", "DORMITORIOS", "BA\xA4OS",
                                        "SUP. TOTAL", "SUP. CUBIERTA", "PRECIO", "MONEDA", "TIPO PROP", "OPERACI\xA2N", "FECHA SALIDA");
                                    printf("%3d|%02d/%02d/%d|%20s|%19s|%12d|%7d|%12.2f|%16.2f|%10.2f|%7s|%20s|%20s| %02d/%02d/%02d\n",
                                        prop.id, prop.fechaIngreso.dia, prop.fechaIngreso.mes, prop.fechaIngreso.anio,
                                        prop.zona, prop.ciudad, prop.dormitorio, prop.banios, prop.sup_total, prop.sup_cubierta, prop.precio,
                                        prop.moneda, prop.tipo_propiedad, prop.operacion, prop.fechaSalida.dia, prop.fechaSalida.mes, prop.fechaSalida.anio);
                                    flag=1;
                                }
                            }

                            if (flag==0) { // Si el id ingresado no existe muestra un mensaje
                                printf("ID no encontrado\n\n");
                            } else {
                                printf("\n-------------------------------------------------------------------------------------------------------------\n");
                                sub_opcion2 = 3;
                            }

                            fclose(archivoBinario);
                            break;

                        case 2:
                            do {
                                printf("1. Alquiler \n");
                                printf("2. Venta \n");
                                printf("3. Alquiler temporal \n");
                                printf("4. Volver al men%c anterior \n", 163);
                                printf("Selecciona una opci%cn: ", 162);
                                scanf("%d", &sub_sub_opcion);
                                printf("\n");

                                switch (sub_sub_opcion) {
                                        case 1:
                                            do {
                                                strcpy(tipoOperacion, "Alquiler");
                                                //Si el usuario busca por alquler, se pide ingresar el tipo de propiedad
                                                printf("1. PH \n");
                                                printf("2. Casa \n");
                                                printf("3. Departamento \n");
                                                printf("4. Volver al men%c anterior \n", 163);
                                                printf("Selecciona una opci%cn: ", 162);
                                                scanf("%d", &sub_sub_opcion2);

                                                switch (sub_sub_opcion2) {
                                                    case 1:
                                                        strcpy(tipoPropiedad, "PH");
                                                        archivoBinario = fopen("propiedades.dat", "rb");
                                                        if (archivoBinario == NULL) {
                                                            perror("Error al abrir el archivo para lectura");
                                                            return 1;
                                                        }
                                                        int encontrado=0;
                                                        printf("%-3s|%-10s|%-20s|%-19s|%-12s|%-7s|%-12s|%-16s|%-10s|%-7s|%-20s|%-20s|%-6s\n",
                                                            "ID", "FECHA ING", "ZONA", "CIUDAD", "DORMITORIOS", "BA\xA4OS",
                                                            "SUP. TOTAL", "SUP. CUBIERTA", "PRECIO", "MONEDA", "TIPO PROP", "OPERACI\xA2N", "FECHA SALIDA");
                                                        fseek(archivoBinario, 0, SEEK_SET);
                                                        while (fread(&prop, sizeof(struct propiedad), 1, archivoBinario) == 1) {
                                                            if((strcmp(prop.tipo_propiedad, tipoPropiedad)==0)&&(strcmp(prop.operacion, tipoOperacion)==0)){
                                                                printf("%3d|%02d/%02d/%d|%20s|%19s|%12d|%7d|%12.2f|%16.2f|%10.2f|%7s|%20s|%20s| %02d/%02d/%02d\n",
                                                                    prop.id, prop.fechaIngreso.dia, prop.fechaIngreso.mes, prop.fechaIngreso.anio,
                                                                    prop.zona, prop.ciudad, prop.dormitorio, prop.banios, prop.sup_total, prop.sup_cubierta, prop.precio,
                                                                    prop.moneda, prop.tipo_propiedad, prop.operacion, prop.fechaSalida.dia, prop.fechaSalida.mes, prop.fechaSalida.anio);
                                                            encontrado=1;
                                                            }
                                                        }
                                                        if(encontrado==0){
                                                            printf("No existen los datos buscados\n");
                                                        } else {
                                                            printf("\n-------------------------------------------------------------------------------------------------------------\n");
                                                            sub_sub_opcion2 = 4;
                                                        }
                                                        fclose(archivoBinario);
                                                        break;

                                                    case 2:
                                                        strcpy(tipoPropiedad, "Casa");
                                                        archivoBinario = fopen("propiedades.dat", "rb");
                                                        if (archivoBinario == NULL) {
                                                            perror("Error al abrir el archivo para lectura");
                                                            return 1;
                                                        }
                                                        encontrado=0;
                                                        printf("%-3s|%-10s|%-20s|%-19s|%-12s|%-7s|%-12s|%-16s|%-10s|%-7s|%-20s|%-20s|%-6s\n",
                                                            "ID", "FECHA ING", "ZONA", "CIUDAD", "DORMITORIOS", "BA\xA4OS",
                                                            "SUP. TOTAL", "SUP. CUBIERTA", "PRECIO", "MONEDA", "TIPO PROP", "OPERACI\xA2N", "FECHA SALIDA");
                                                        fseek(archivoBinario, 0, SEEK_SET);
                                                        while (fread(&prop, sizeof(struct propiedad), 1, archivoBinario) == 1) {
                                                            if((strcmp(prop.tipo_propiedad, tipoPropiedad)==0)&&(strcmp(prop.operacion, tipoOperacion)==0)){
                                                                printf("%3d|%02d/%02d/%d|%20s|%19s|%12d|%7d|%12.2f|%16.2f|%10.2f|%7s|%20s|%20s| %02d/%02d/%02d\n",
                                                                    prop.id, prop.fechaIngreso.dia, prop.fechaIngreso.mes, prop.fechaIngreso.anio,
                                                                    prop.zona, prop.ciudad, prop.dormitorio, prop.banios, prop.sup_total, prop.sup_cubierta, prop.precio,
                                                                    prop.moneda, prop.tipo_propiedad, prop.operacion, prop.fechaSalida.dia, prop.fechaSalida.mes, prop.fechaSalida.anio);
                                                            encontrado=1;
                                                            }
                                                        }
                                                        if(encontrado==0){
                                                            printf("No existen los datos buscados\n");
                                                        } else {
                                                            printf("\n-------------------------------------------------------------------------------------------------------------\n");
                                                            sub_sub_opcion2 = 4;
                                                        }
                                                        fclose(archivoBinario);
                                                        break;

                                                    case 3:
                                                        strcpy(tipoPropiedad, "Departamento");
                                                        archivoBinario = fopen("propiedades.dat", "rb");
                                                        if (archivoBinario == NULL) {
                                                            perror("Error al abrir el archivo para lectura");
                                                            return 1;
                                                        }
                                                        encontrado=0;
                                                        printf("%-3s|%-10s|%-20s|%-19s|%-12s|%-7s|%-12s|%-16s|%-10s|%-7s|%-20s|%-20s|%-6s\n",
                                                            "ID", "FECHA ING", "ZONA", "CIUDAD", "DORMITORIOS", "BA\xA4OS",
                                                            "SUP. TOTAL", "SUP. CUBIERTA", "PRECIO", "MONEDA", "TIPO PROP", "OPERACI\xA2N", "FECHA SALIDA");
                                                        fseek(archivoBinario, 0, SEEK_SET);
                                                        while (fread(&prop, sizeof(struct propiedad), 1, archivoBinario) == 1) {
                                                            if((strcmp(prop.tipo_propiedad, tipoPropiedad)==0)&&(strcmp(prop.operacion, tipoOperacion)==0)){
                                                                printf("%3d|%02d/%02d/%d|%20s|%19s|%12d|%7d|%12.2f|%16.2f|%10.2f|%7s|%20s|%20s| %02d/%02d/%02d\n",
                                                                    prop.id, prop.fechaIngreso.dia, prop.fechaIngreso.mes, prop.fechaIngreso.anio,
                                                                    prop.zona, prop.ciudad, prop.dormitorio, prop.banios, prop.sup_total, prop.sup_cubierta, prop.precio,
                                                                    prop.moneda, prop.tipo_propiedad, prop.operacion, prop.fechaSalida.dia, prop.fechaSalida.mes, prop.fechaSalida.anio);
                                                            encontrado=1;
                                                            }
                                                        }
                                                        if(encontrado==0){
                                                            printf("No existen los datos buscados\n");
                                                        } else {
                                                            printf("\n-------------------------------------------------------------------------------------------------------------\n");
                                                            sub_sub_opcion2 = 4;
                                                        }
                                                        fclose(archivoBinario);
                                                        break;

                                                    case 4:
                                                        printf("Vuelve al men%c anterior \n", 163); //Agrego el mensajito para que tire este y no el del default cuando cierra
                                                        break;

                                                    default:
                                                        printf("No es una opci%cn v%clida dentro del men%c \n", 162, 160, 163);
                                                }
                                            } while (sub_sub_opcion2 != 4);
                                            sub_sub_opcion = 4;
                                            break;

                                        case 2:
                                            do {
                                                strcpy(tipoOperacion, "Venta");
                                                //Si el usuario busca por venta, se pide ingresar el tipo de propiedad
                                                printf("1. PH \n");
                                                printf("2. Casa \n");
                                                printf("3. Departamento \n");
                                                printf("4. Volver al men%c anterior \n", 163);
                                                printf("Selecciona una opci%cn: ", 162);
                                                scanf("%d", &sub_sub_opcion2);
                                                printf("\n");

                                                switch (sub_sub_opcion2) {
                                                    case 1:
                                                        strcpy(tipoPropiedad, "PH");
                                                        archivoBinario = fopen("propiedades.dat", "rb");
                                                        if (archivoBinario == NULL) {
                                                            perror("Error al abrir el archivo para lectura");
                                                            return 1;
                                                        }
                                                        int encontrado=0;
                                                        printf("%-3s|%-10s|%-20s|%-19s|%-12s|%-7s|%-12s|%-16s|%-10s|%-7s|%-20s|%-20s|%-6s\n",
                                                            "ID", "FECHA ING", "ZONA", "CIUDAD", "DORMITORIOS", "BA\xA4OS",
                                                            "SUP. TOTAL", "SUP. CUBIERTA", "PRECIO", "MONEDA", "TIPO PROP", "OPERACI\xA2N", "FECHA SALIDA");
                                                        fseek(archivoBinario, 0, SEEK_SET);
                                                        while (fread(&prop, sizeof(struct propiedad), 1, archivoBinario) == 1) {
                                                            if((strcmp(prop.tipo_propiedad, tipoPropiedad)==0)&&(strcmp(prop.operacion, tipoOperacion)==0)){
                                                                printf("%3d|%02d/%02d/%d|%20s|%19s|%12d|%7d|%12.2f|%16.2f|%10.2f|%7s|%20s|%20s| %02d/%02d/%02d\n",
                                                                    prop.id, prop.fechaIngreso.dia, prop.fechaIngreso.mes, prop.fechaIngreso.anio,
                                                                    prop.zona, prop.ciudad, prop.dormitorio, prop.banios, prop.sup_total, prop.sup_cubierta, prop.precio,
                                                                    prop.moneda, prop.tipo_propiedad, prop.operacion, prop.fechaSalida.dia, prop.fechaSalida.mes, prop.fechaSalida.anio);
                                                            encontrado=1;
                                                            }
                                                        }
                                                        if(encontrado==0){
                                                            printf("No existen los datos buscados\n");
                                                        } else {
                                                            printf("\n-------------------------------------------------------------------------------------------------------------\n");
                                                            sub_sub_opcion2 = 4;
                                                        }
                                                        fclose(archivoBinario);
                                                        break;

                                                    case 2:
                                                        strcpy(tipoPropiedad, "Casa");
                                                        archivoBinario = fopen("propiedades.dat", "rb");
                                                        if (archivoBinario == NULL) {
                                                            perror("Error al abrir el archivo para lectura");
                                                            return 1;
                                                        }
                                                        encontrado=0;
                                                        printf("%-3s|%-10s|%-20s|%-19s|%-12s|%-7s|%-12s|%-16s|%-10s|%-7s|%-20s|%-20s|%-6s\n",
                                                            "ID", "FECHA ING", "ZONA", "CIUDAD", "DORMITORIOS", "BA\xA4OS",
                                                            "SUP. TOTAL", "SUP. CUBIERTA", "PRECIO", "MONEDA", "TIPO PROP", "OPERACI\xA2N", "FECHA SALIDA");
                                                        fseek(archivoBinario, 0, SEEK_SET);
                                                        while (fread(&prop, sizeof(struct propiedad), 1, archivoBinario) == 1) {
                                                            if((strcmp(prop.tipo_propiedad, tipoPropiedad)==0)&&(strcmp(prop.operacion, tipoOperacion)==0)){
                                                                printf("%3d|%02d/%02d/%d|%20s|%19s|%12d|%7d|%12.2f|%16.2f|%10.2f|%7s|%20s|%20s| %02d/%02d/%02d\n",
                                                                    prop.id, prop.fechaIngreso.dia, prop.fechaIngreso.mes, prop.fechaIngreso.anio,
                                                                    prop.zona, prop.ciudad, prop.dormitorio, prop.banios, prop.sup_total, prop.sup_cubierta, prop.precio,
                                                                    prop.moneda, prop.tipo_propiedad, prop.operacion, prop.fechaSalida.dia, prop.fechaSalida.mes, prop.fechaSalida.anio);
                                                            encontrado=1;
                                                            }
                                                        }
                                                        if(encontrado==0){
                                                            printf("No existen los datos buscados\n");
                                                        } else {
                                                            printf("\n-------------------------------------------------------------------------------------------------------------\n");
                                                            sub_sub_opcion2 = 4;
                                                        }
                                                        fclose(archivoBinario);
                                                        break;

                                                    case 3:
                                                        strcpy(tipoPropiedad, "Departamento");
                                                        archivoBinario = fopen("propiedades.dat", "rb");
                                                        if (archivoBinario == NULL) {
                                                            perror("Error al abrir el archivo para lectura");
                                                            return 1;
                                                        }
                                                        encontrado=0;
                                                        printf("%-3s|%-10s|%-20s|%-19s|%-12s|%-7s|%-12s|%-16s|%-10s|%-7s|%-20s|%-20s|%-6s\n",
                                                            "ID", "FECHA ING", "ZONA", "CIUDAD", "DORMITORIOS", "BA\xA4OS",
                                                            "SUP. TOTAL", "SUP. CUBIERTA", "PRECIO", "MONEDA", "TIPO PROP", "OPERACI\xA2N", "FECHA SALIDA");
                                                        fseek(archivoBinario, 0, SEEK_SET);
                                                        while (fread(&prop, sizeof(struct propiedad), 1, archivoBinario) == 1) {
                                                            if((strcmp(prop.tipo_propiedad, tipoPropiedad)==0)&&(strcmp(prop.operacion, tipoOperacion)==0)){
                                                                printf("%3d|%02d/%02d/%d|%20s|%19s|%12d|%7d|%12.2f|%16.2f|%10.2f|%7s|%20s|%20s| %02d/%02d/%02d\n",
                                                                    prop.id, prop.fechaIngreso.dia, prop.fechaIngreso.mes, prop.fechaIngreso.anio,
                                                                    prop.zona, prop.ciudad, prop.dormitorio, prop.banios, prop.sup_total, prop.sup_cubierta, prop.precio,
                                                                    prop.moneda, prop.tipo_propiedad, prop.operacion, prop.fechaSalida.dia, prop.fechaSalida.mes, prop.fechaSalida.anio);
                                                            encontrado=1;
                                                            }
                                                        }
                                                        if(encontrado==0){
                                                            printf("No existen los datos buscados\n");
                                                        } else {
                                                            printf("\n-------------------------------------------------------------------------------------------------------------\n");
                                                            sub_sub_opcion2 = 4;
                                                        }
                                                        fclose(archivoBinario);
                                                        break;

                                                    case 4:
                                                        printf("Vuelve al men%c anterior \n", 163); //Agrego el mensajito para que tire este y no el del default cuando cierra
                                                        break;

                                                    default:
                                                        printf("No es una opci%cn v%clida dentro del men%c \n", 162, 160, 163);
                                                }
                                            } while (sub_sub_opcion2 != 4);
                                            sub_sub_opcion = 4;
                                            break;

                                        case 3:
                                            do {
                                                strcpy(tipoOperacion, "Alquiler temporal");
                                                //Si el usuario busca por alquler temporal, se pide ingresar el tipo de propiedad
                                                printf("1. PH \n");
                                                printf("2. Casa \n");
                                                printf("3. Departamento \n");
                                                printf("4. Volver al men%c anterior \n", 163);
                                                printf("Selecciona una opci%cn: ", 162);
                                                scanf("%d", &sub_sub_opcion2);
                                                printf("\n");

                                                switch (sub_sub_opcion2) {
                                                    case 1:
                                                        strcpy(tipoPropiedad, "PH");
                                                        archivoBinario = fopen("propiedades.dat", "rb");
                                                        if (archivoBinario == NULL) {
                                                            perror("Error al abrir el archivo para lectura");
                                                            return 1;
                                                        }
                                                        int encontrado=0;
                                                        printf("%-3s|%-10s|%-20s|%-19s|%-12s|%-7s|%-12s|%-16s|%-10s|%-7s|%-20s|%-20s|%-6s\n",
                                                            "ID", "FECHA ING", "ZONA", "CIUDAD", "DORMITORIOS", "BA\xA4OS",
                                                            "SUP. TOTAL", "SUP. CUBIERTA", "PRECIO", "MONEDA", "TIPO PROP", "OPERACI\xA2N", "FECHA SALIDA");
                                                        fseek(archivoBinario, 0, SEEK_SET);
                                                        while (fread(&prop, sizeof(struct propiedad), 1, archivoBinario) == 1) {
                                                            if((strcmp(prop.tipo_propiedad, tipoPropiedad)==0)&&(strcmp(prop.operacion, tipoOperacion)==0)){
                                                                printf("%3d|%02d/%02d/%d|%20s|%19s|%12d|%7d|%12.2f|%16.2f|%10.2f|%7s|%20s|%20s| %02d/%02d/%02d\n",
                                                                    prop.id, prop.fechaIngreso.dia, prop.fechaIngreso.mes, prop.fechaIngreso.anio,
                                                                    prop.zona, prop.ciudad, prop.dormitorio, prop.banios, prop.sup_total, prop.sup_cubierta, prop.precio,
                                                                    prop.moneda, prop.tipo_propiedad, prop.operacion, prop.fechaSalida.dia, prop.fechaSalida.mes, prop.fechaSalida.anio);
                                                            encontrado=1;
                                                            }
                                                        }
                                                        if(encontrado==0){
                                                            printf("No existen los datos buscados\n");
                                                        } else {
                                                            printf("\n-------------------------------------------------------------------------------------------------------------\n");
                                                            sub_sub_opcion2 = 4;
                                                        }
                                                        fclose(archivoBinario);
                                                        break;

                                                    case 2:
                                                        strcpy(tipoPropiedad, "Casa");
                                                        archivoBinario = fopen("propiedades.dat", "rb");
                                                        if (archivoBinario == NULL) {
                                                            perror("Error al abrir el archivo para lectura");
                                                            return 1;
                                                        }
                                                        encontrado=0;
                                                        printf("%-3s|%-10s|%-20s|%-19s|%-12s|%-7s|%-12s|%-16s|%-10s|%-7s|%-20s|%-20s|%-6s\n",
                                                            "ID", "FECHA ING", "ZONA", "CIUDAD", "DORMITORIOS", "BA\xA4OS",
                                                            "SUP. TOTAL", "SUP. CUBIERTA", "PRECIO", "MONEDA", "TIPO PROP", "OPERACI\xA2N", "FECHA SALIDA");
                                                        fseek(archivoBinario, 0, SEEK_SET);
                                                        while (fread(&prop, sizeof(struct propiedad), 1, archivoBinario) == 1) {
                                                            if((strcmp(prop.tipo_propiedad, tipoPropiedad)==0)&&(strcmp(prop.operacion, tipoOperacion)==0)){
                                                                printf("%3d|%02d/%02d/%d|%20s|%19s|%12d|%7d|%12.2f|%16.2f|%10.2f|%7s|%20s|%20s| %02d/%02d/%02d\n",
                                                                    prop.id, prop.fechaIngreso.dia, prop.fechaIngreso.mes, prop.fechaIngreso.anio,
                                                                    prop.zona, prop.ciudad, prop.dormitorio, prop.banios, prop.sup_total, prop.sup_cubierta, prop.precio,
                                                                    prop.moneda, prop.tipo_propiedad, prop.operacion, prop.fechaSalida.dia, prop.fechaSalida.mes, prop.fechaSalida.anio);
                                                            encontrado=1;
                                                            }

                                                        }
                                                        if(encontrado==0){
                                                            printf("No existen los datos buscados\n");
                                                        } else {
                                                            printf("\n-------------------------------------------------------------------------------------------------------------\n");
                                                            sub_sub_opcion2 = 4;
                                                        }
                                                        fclose(archivoBinario);
                                                        break;

                                                    case 3:
                                                        strcpy(tipoPropiedad, "Departamento");
                                                        archivoBinario = fopen("propiedades.dat", "rb");
                                                        if (archivoBinario == NULL) {
                                                            perror("Error al abrir el archivo para lectura");
                                                            return 1;
                                                        }
                                                        encontrado=0;
                                                        printf("%-3s|%-10s|%-20s|%-19s|%-12s|%-7s|%-12s|%-16s|%-10s|%-7s|%-20s|%-20s|%-6s\n",
                                                            "ID", "FECHA ING", "ZONA", "CIUDAD", "DORMITORIOS", "BA\xA4OS",
                                                            "SUP. TOTAL", "SUP. CUBIERTA", "PRECIO", "MONEDA", "TIPO PROP", "OPERACI\xA2N", "FECHA SALIDA");
                                                        fseek(archivoBinario, 0, SEEK_SET);
                                                        while (fread(&prop, sizeof(struct propiedad), 1, archivoBinario) == 1) {
                                                            if((strcmp(prop.tipo_propiedad, tipoPropiedad)==0)&&(strcmp(prop.operacion, tipoOperacion)==0)){
                                                                printf("%3d|%02d/%02d/%d|%20s|%19s|%12d|%7d|%12.2f|%16.2f|%10.2f|%7s|%20s|%20s| %02d/%02d/%02d\n",
                                                                    prop.id, prop.fechaIngreso.dia, prop.fechaIngreso.mes, prop.fechaIngreso.anio,
                                                                    prop.zona, prop.ciudad, prop.dormitorio, prop.banios, prop.sup_total, prop.sup_cubierta, prop.precio,
                                                                    prop.moneda, prop.tipo_propiedad, prop.operacion, prop.fechaSalida.dia, prop.fechaSalida.mes, prop.fechaSalida.anio);
                                                            encontrado=1;
                                                            }
                                                        }
                                                        if(encontrado==0){
                                                            printf("No existen los datos buscados\n");
                                                        } else {
                                                            printf("\n-------------------------------------------------------------------------------------------------------------\n");
                                                            sub_sub_opcion2 = 4;
                                                        }
                                                        fclose(archivoBinario);
                                                        break;

                                                    case 4:
                                                         printf("Vuelve al men%c anterior \n", 163); //Agrego el mensajito para que tire este y no el del default cuando cierra
                                                        break;

                                                    default:
                                                        printf("No es una opci%cn v%clida dentro del men%c \n", 162, 160, 163);
                                                }
                                            } while (sub_sub_opcion2 != 4);
                                            sub_sub_opcion = 4;
                                            break;

                                        case 4:
                                            printf("Vuelve al men%c anterior \n", 163); //Agrego el mensajito para que tire este y no el del default cuando cierra
                                            break;

                                        default:
                                        printf("No es una opci%cn v%clida dentro del men%c \n", 162, 160, 163);
                                }
                            } while (sub_sub_opcion != 4);
                            sub_opcion2 = 3;
                            break;

                        case 3:
                            printf("Vuelve al men%c principal \n", 163); //Agrego el mensajito para que tire este y no el del default cuando cierra
                            break;

                        default:
                            printf("No es una opci%cn v%clida dentro del men%c \n", 162, 160, 163);
                    }
                } while (sub_opcion2 != 3);
                break;

            case 5:
                do {
                    archivoBinario = fopen("propiedades.dat", "r+b");
                            if (archivoBinario == NULL) {
                                perror("Error al abrir el archivo para lectura");
                                return 1;
                            }
    
                    printf("1. Modificar ciudad/barrio \n");
                    printf("2. Modificar precio \n");
                    printf("3. Modificar fecha de salida \n");
                    printf("4. Volver al men%c principal \n", 163);
                    printf("Selecciona una opci%cn: ", 162);
                    scanf(" %d", &sub_opcion3);
                    printf("\n");

                    switch (sub_opcion3) {
                        case 1:
                            printf("Ingrese el ID de la propiedad a modificar: ");
                            scanf("%d", &IDModif);
                            fflush(stdin);
                            if (IDModif < 1 || IDModif > numProp) {
                            printf("ID de propiedad fuera del rango v%clido.\n", 160);
                            fclose(archivoBinario);
                            return 1;
                            }
                            // Calcula el offset en función del ID
                            long offset1 = (IDModif - 1) * sizeof(struct propiedad);
                            fseek(archivoBinario, offset1, SEEK_SET); // Coloca el puntero en la posición del struct en el archivo
                            fread(&prop, sizeof(struct propiedad), 1, archivoBinario); // Lee el struct existente
                            printf("\nIngrese la nueva ciudad/barrio: ");
                            gets(prop.ciudad); // Modifica el campo del struct
                            fflush(stdin);
                            fseek(archivoBinario, offset1, SEEK_SET); // Vuelve a colocar el puntero en la misma posición
                            fwrite(&prop, sizeof(struct propiedad), 1, archivoBinario); // Escribe el struct modificado en el archivo
                            printf("Ciudad/barrio modificado correctamente.\n");
                            fclose(archivoBinario);
                            sub_opcion3 = 4;
                            break;

                        case 2:
                            printf("Ingrese el ID de la propiedad a modificar: ");
                            scanf("%d", &IDModif);
                            if (IDModif < 1 || IDModif > numProp) {
                            printf("ID de propiedad fuera del rango v%clido.\n", 160);
                            fclose(archivoBinario);
                            return 1;
                            }
                            // Calcula el offset en función del ID
                            offset1 = (IDModif - 1) * sizeof(struct propiedad);
                            fseek(archivoBinario, offset1, SEEK_SET); // Coloca el puntero en la posición del struct en el archivo
                            fread(&prop, sizeof(struct propiedad), 1, archivoBinario); // Lee el struct existente
                            printf("\nIngrese el nuevo precio: ");
                            scanf(" %f", &prop.precio); //Modifico los campos del struct
                            fseek(archivoBinario, offset1, SEEK_SET); // Vuelve a colocar el puntero en la misma posición
                            fwrite(&prop, sizeof(struct propiedad), 1, archivoBinario); //Escribo el struct modificado en el archivo
                            printf("Precio modificado correctamente.\n");
                            fclose(archivoBinario);
                            sub_opcion3 = 4;
                            break;

                        case 3:
                            printf("Ingrese el ID de la propiedad a modificar: ");
                            scanf("%d", &IDModif);
                            fflush(stdin);
                            if (IDModif < 1 || IDModif > numProp) {
                            printf("ID de propiedad fuera del rango v%clido.\n", 160);
                            fclose(archivoBinario);
                            return 1;
                            }
                            // Calcula el offset en función del ID
                            offset1 = (IDModif - 1) * sizeof(struct propiedad);
                            fseek(archivoBinario, offset1, SEEK_SET); // Coloca el puntero en la posición del struct en el archivo
                            fread(&prop, sizeof(struct propiedad), 1, archivoBinario); // Lee el struct existente
                            if(prop.estado==1){
                                printf("Solo se puede modificar la fecha de salida de las propiedades inactivas.\n\n");
                                break;
                            }
                            validarFecha(&auxiliar1);
                            auxiliar2.dia = fecha_actual->tm_mday;
                            auxiliar2.mes = fecha_actual->tm_mon + 1;
                            auxiliar2.anio = fecha_actual->tm_year + 1900;
                            while (auxiliar2.dia<auxiliar1.dia && auxiliar2.mes<auxiliar1.mes && auxiliar2.anio<auxiliar1.anio){
                                printf("La fecha de salida no puede superar a la fecha actual.\n");
                                validarFecha(&auxiliar1);
                            }
                            prop.fechaSalida = auxiliar1;
                            fseek(archivoBinario, offset1, SEEK_SET); // Vuelve a colocar el puntero en la misma posición
                            fwrite(&prop, sizeof(struct propiedad), 1, archivoBinario); //Escribo el struct modificado en el archivo
                            printf("Fecha modificada correctamente.\n");
                            fclose(archivoBinario);
                            sub_opcion3 = 4;
                            break;

                        case 4:
                            printf("Vuelve al men%c principal \n", 163); //Agrego el mensajito para que tire este y no el del default cuando cierra
                            break;

                        default:
                            printf("No es una opci%cn v%clida dentro del men%c \n", 162, 160, 163);
                    }
                } while (sub_opcion3 != 4);
                break;

            case 6: ;
                // aca punto 9
                archivoBinario = fopen("propiedades.dat", "r+b");
                    if (archivoBinario == NULL) {
                    perror("Error al abrir el archivo para lectura");
                    return 1;
                    }
                
                int idBuscado;
                struct propiedad propiedadEncontrada; //puntero a la propiedad que se va a dar de baja
                int encontrado = 0;

                printf("Ingrese el ID de la propiedad que quiere dar de baja: ");
                scanf("%d",&idBuscado); //id que se va a buscar
                fflush(stdin);

                fseek(archivoBinario, 0, SEEK_SET);
                while(fread(&prop, sizeof(struct propiedad), 1, archivoBinario)==1){
                    if(prop.id == idBuscado && prop.estado==1){
                        encontrado = 1;
                        propiedadEncontrada=prop;
                        break;
                    }
                }

                if (encontrado == 0){
                    printf("No se encontr%c una propiedad con el ID ingresado, o el ID ingresado ya est%c dado de baja \n", 162, 160);
                    continue;
                }

                //printeo de la propiedad a dar de baja
                printf("Propiedad encontrada: \n");
                printf("%-3s|%-10s|%-20s|%-19s|%-12s|%-7s|%-12s|%-16s|%-10s|%-7s|%-20s|%-20s|%-6s\n",
                    "ID", "FECHA ING", "ZONA", "CIUDAD", "DORMITORIOS", "BA\xA4OS",
                    "SUP. TOTAL", "SUP. CUBIERTA", "PRECIO", "MONEDA", "TIPO PROP", "OPERACI\xA2N", "FECHA SALIDA");
                printf("%3d|%02d/%02d/%d|%20s|%19s|%12d|%7d|%12.2f|%16.2f|%10.2f|%7s|%20s|%20s| %02d/%02d/%02d\n",
                            propiedadEncontrada.id, propiedadEncontrada.fechaIngreso.dia, propiedadEncontrada.fechaIngreso.mes, propiedadEncontrada.fechaIngreso.anio,
                            propiedadEncontrada.zona, propiedadEncontrada.ciudad, propiedadEncontrada.dormitorio, propiedadEncontrada.banios, propiedadEncontrada.sup_total, propiedadEncontrada.sup_cubierta, propiedadEncontrada.precio,
                            propiedadEncontrada.moneda, propiedadEncontrada.tipo_propiedad, propiedadEncontrada.operacion, propiedadEncontrada.fechaSalida.dia, propiedadEncontrada.fechaSalida.mes, propiedadEncontrada.fechaSalida.anio);
                //confirmacion de la baja
                char confirmacion;
                printf("%cEst%c seguro de que desea dar de baja la propiedad? (S/N) \n",168,160);
                scanf(" %c",&confirmacion);
                fflush(stdin);
                //guardado de la baja en el archivo binario
                if(confirmacion == 's' || confirmacion == 'S') {
                    propiedadEncontrada.estado = 0;

                    printf("Modifique la fecha de salida: \n", 161);
                        validarFecha(&propiedadEncontrada.fechaSalida);
                    fseek(archivoBinario, -sizeof(struct propiedad), SEEK_CUR); //Lleva el puntero al principio de la linea
                    fwrite(&propiedadEncontrada, sizeof(struct propiedad), 1, archivoBinario); //Reescribe la linea poniendo el estado en 0
                    printf ("La propiedad se ha dado de baja correctamente \n");
                } else if (confirmacion == 'n' || confirmacion == 'N') {
                    printf("La propiedad no se ha dado de baja \n");
                    continue;
                } else {
                    printf("Confirmaci%cn inv%clida \n", 162, 160);
                    continue;
                }

                printf("Las propiedades activas actualmente: \n");
                //Emite unicamente los que poseen estado ACTIVO

                printf("%-3s|%-10s|%-20s|%-19s|%-12s|%-7s|%-12s|%-16s|%-10s|%-7s|%-20s|%-20s|%-6s\n",
                    "ID", "FECHA ING", "ZONA", "CIUDAD", "DORMITORIOS", "BA\xA4OS",
                    "SUP. TOTAL", "SUP. CUBIERTA", "PRECIO", "MONEDA", "TIPO PROP", "OPERACI\xA2N", "FECHA SALIDA");

                fseek(archivoBinario, 0, SEEK_SET);

                while (fread(&prop, sizeof(struct propiedad), 1, archivoBinario) == 1) {
                    if(prop.estado==1){
                        printf("%3d|%02d/%02d/%d|%20s|%19s|%12d|%7d|%12.2f|%16.2f|%10.2f|%7s|%20s|%20s| %02d/%02d/%02d\n",
                            prop.id, prop.fechaIngreso.dia, prop.fechaIngreso.mes, prop.fechaIngreso.anio,
                            prop.zona, prop.ciudad, prop.dormitorio, prop.banios, prop.sup_total, prop.sup_cubierta, prop.precio,
                            prop.moneda, prop.tipo_propiedad, prop.operacion, prop.fechaSalida.dia, prop.fechaSalida.mes, prop.fechaSalida.anio);
                        }
                }
                printf("\n-------------------------------------------------------------------------------------------------------------\n");
                fclose(archivoBinario);
            break;

            case 7:
                // aca punto 10
                bajaFisica(archivoBinario, nombreArchivo);
                blancos(archivoBinario);
                imprimirDatos(archivoBinario);
                break;

            case 8:
                //aca punto 11
                archivoTexto = fopen(nombreArchivo, "r");
                if (archivoTexto == NULL) {
                    perror("Error al abrir el archivo para lectura");
                    return -1;
                }
                char linea[1024];
                printf("%-10s|%-20s|%-19s|%-12s|%-7s|%-12s|%-16s|%-10s|%-7s|%-20s|%-20s|%-6s\n",
                    "FECHA ING", "ZONA", "CIUDAD", "DORMITORIOS", "BA\xA4OS",
                    "SUP. TOTAL", "SUP. CUBIERTA", "PRECIO", "MONEDA", "TIPO PROP", "OPERACI\xA2N", "FECHA SALIDA");
                while (fgets(linea, sizeof(linea), archivoTexto) != NULL){
                    sscanf(linea, "%d/%d/%d|%20[^|]|%19[^|]|%d|%d|%f|%f|%f|%8[^|]|%20[^|]|%20[^|]| %d/%d/%d",
                    &prop.fechaIngreso.dia, &prop.fechaIngreso.mes, &prop.fechaIngreso.anio,
                    prop.zona, prop.ciudad, &prop.dormitorio, &prop.banios, &prop.sup_total, &prop.sup_cubierta, &prop.precio,
                    prop.moneda, prop.tipo_propiedad, prop.operacion, &prop.fechaSalida.dia, &prop.fechaSalida.mes, &prop.fechaSalida.anio);

                    printf("%02d/%02d/%d|%s|%s|%12d|%7d|%12.2f|%16.2f|%10.2f|%s|%s|%s| %02d/%02d/%02d\n",
                    prop.fechaIngreso.dia, prop.fechaIngreso.mes, prop.fechaIngreso.anio,
                    prop.zona, prop.ciudad, prop.dormitorio, prop.banios, prop.sup_total, prop.sup_cubierta, prop.precio,
                    prop.moneda, prop.tipo_propiedad, prop.operacion, prop.fechaSalida.dia, prop.fechaSalida.mes, prop.fechaSalida.anio);
                }

                printf("\n-------------------------------------------------------------------------------------------------------------\n");
                fclose(archivoTexto);
                break;

            case 9:
                printf("Sale del programa \n"); //Agrego el mensajito para que tire este y no el del default cuando cierra
                break;

            default:
                printf("La opci%cn no se encuentra dentro del men%c \n", 162, 163);
        }
    } while (opcion != 9);

return 0;

}