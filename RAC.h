#ifndef RAC_H_INCLUDED
#define RAC_H_INCLUDED
#include "Padron.h"
#define TAMANO_RAC 2411

typedef struct
{
    Padron Votantes[TAMANO_RAC]; //tamano definido en base al numero primo mas cercano obtenido mediante la formula (aprox 2410)
    int Ocupadas; //indica la cantidad de celdas con elementos
} RAC;

void Inicializador_RAC (RAC *Rac)
{
    int i;
    (*Rac).Ocupadas = 0;
    for (i = 0; i < TAMANO_RAC; i++)
    {
        (*Rac).Votantes[i].Estado = 0; //cambia las celdas a virgenes
    }
}

int Localizador_RAC (RAC *Rac, int DNI, int *Posicion, int *Celdas_Consultadas)
{
    int Candidato = hashing(DNI, TAMANO_RAC), i = 0, k = 1;
    *Posicion = -1;
    *Celdas_Consultadas = 0;

    while (i < TAMANO_RAC && (*Rac).Votantes[Candidato].Estado) //como estado es virgen con 0, esto sirve
    {
        (*Celdas_Consultadas)++;
        if ((*Rac).Votantes[Candidato].Estado == 1 && (*Rac).Votantes[Candidato].DNI == DNI)
        {
            *Posicion = Candidato;
            return 1;
        }

        if ((*Rac).Votantes[Candidato].Estado == 2 && *Posicion == -1) //guarda la primer celda libre para un alta
        {
            *Posicion = Candidato;
        }

        i++;
        Candidato = (Candidato + k) % TAMANO_RAC;
        k = k + 1;
    }

    if (i < TAMANO_RAC) //por si se rompe el while por virgen
    {
        (*Celdas_Consultadas)++;
    }

    if (!(*Rac).Votantes[Candidato].Estado && *Posicion == -1) //guarda la celda virgen si no hay una libre antes
    {
        *Posicion = Candidato;
    }

    return 0;
}

int Insertar_RAC (RAC *Rac, Padron Votante)
{
    int Celdas, Posicion;
    if((*Rac).Ocupadas == TAMANO_RAC) //esta lleno el RAC
    {
        return 0;
    }
    if(Localizador_RAC(Rac,get_DNI(Votante),&Posicion,&Celdas)) //revisa si encuentra al votante y nos da la posicion donde iria si no esta
    {
        return 0;
    }
    if(Posicion == -1) //no encontro una celda virgen ni vacia en ningun momento
    {
        return 0;
    }
    (*Rac).Votantes[Posicion] = Votante;
    (*Rac).Ocupadas++;
    return 1;
}

int Eliminar_RAC (RAC *Rac, Padron Votante)
{
    int Celdas, Posicion;
    if((*Rac).Ocupadas == 0) //esta vacio el RAC
    {
        return 0;
    }
    if(!Localizador_RAC(Rac,get_DNI(Votante),&Posicion,&Celdas)) //no lo encontro
    {
        return 0;
    }
    if(comparaPadron(Votante,(*Rac).Votantes[Posicion]))
    {
        (*Rac).Votantes[Posicion].Estado = 2; //marca la celda como libre
        (*Rac).Ocupadas--;
        return 1;
    }
    return 0;
}

int Evocar_RAC (RAC *Rac, int DNI, Padron *Votante,int *Celdas_Consultadas)
{
    int Posicion;
    if((*Rac).Ocupadas == 0) //esta vacio el RAC
    {
        return 0;
    }
    if(Localizador_RAC(Rac,DNI,&Posicion,Celdas_Consultadas)) //lo encontro
    {
        *Votante = (*Rac).Votantes[Posicion];
        return 1;
    }
    return 0;
}

void Mostrar_RAC (RAC *Rac)
{
    int i, Condicion;
    int elementosEnPagina = 0;
    int paginaActual = 1;

    printf("\t Votantes Rebalse Abierto Cuadratico (RAC) \n");
    printf("=================================================\n");

    for (i = 0; i < TAMANO_RAC; i++)
    {
        Condicion = (*Rac).Votantes[i].Estado;

        if(!Condicion) // la celda es virgen
        {
            printf("\n La posicion %d es virgen \n", i);
        }
        else if(Condicion == 1) // la celda esta ocupada
        {
            printPadron((*Rac).Votantes[i]);
        }
        else if(Condicion == 2) // la celda esta libre
        {
            printf("\n La posicion %d esta libre \n", i);
        }

        elementosEnPagina++;


        if(elementosEnPagina == 15)
        {
            printf("\n----- Fin de pagina %d (Presione ENTER para continuar) -----\n", paginaActual++);
            elementosEnPagina = 0;
            while (getchar() != '\n'); // limpia buffer y espera ENTER
        }
    }

    if (elementosEnPagina > 0){
        printf("\n------- Fin de listado RAC -------\n");
    }
}

#endif // RAC_H_INCLUDED
