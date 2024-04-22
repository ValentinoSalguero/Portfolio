#ifndef MISFUNCIONES_H_INCLUDED
#define MISFUNCIONES_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//Extencion del struct de propiedades, debido a la comprobacion de fecha.
struct fechas{
    int dia;
    int mes;
    int anio;
};

//Definicion del struct de propiedades
struct propiedad{
    int id;
    struct fechas fechaIngreso;
    char zona[50];
    char ciudad[50];
    int dormitorio;
    int banios;
    float sup_total;
    float sup_cubierta;
    float precio;
    char moneda[8];
    char tipo_propiedad[25];
    char operacion[25];
    struct fechas fechaSalida;
    int estado;
};

// Funcion para crear el archivo binario
void creaArchivo(FILE *archivoBinario, const struct propiedad propiedades[], size_t numPropiedades);

// Funcion para imprimir
void imprimirDatos(FILE *archivoBinario);

// Funcion para calcular la cantidad de propiedades
int calcularNumeroPropiedades();

// Funcion para compruebra que no pise otro id
int Existe(FILE *file, int id);

// Funcion para valida la fecha
void validarFecha(struct fechas *auxiliar);

// Funcion para agregar propiedad
int agregarPropiedad(int numProp);

void blancos(FILE *archivoBinario);

int registroExisteEnArchivo(FILE *archivo, int id);
// Funcion para dar baja fisica
void bajaFisica(FILE *archivoBinario, char nombreArchivo[]);

int compararFechas(struct fechas fecha1, struct fechas fecha2);

#include "misfunciones.c"
#endif // MISFUNCIONES_H_INCLUDED