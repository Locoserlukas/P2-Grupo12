#ifndef RAL_H_INCLUDED
#define RAL_H_INCLUDED
#include "Padron.h"
#define TAMANO_RAL 2531

typedef struct
{
    Padron Votantes[TAMANO_RAL]; //tamano definido en base a la formula (aprox 2532)
    int Ocupadas; //indica la cantidad de celdas con elementos
} RAL;

void Inicializador_RAL (RAL *Ral)
{
    int i;
    (*Ral).Ocupadas = 0;
    for (i = 0; i < TAMANO_RAL; i++)
    {
        (*Ral).Votantes[i].Estado = 0; //cambia las celdas a virgenes
    }
}

int Localizador_RAL (RAL *Ral, int DNI, int *Posicion, int *Celdas_Consultadas)
{
    int Candidato = hashing(DNI, TAMANO_RAL), i = 0;
    *Posicion = -1;
    *Celdas_Consultadas = 0;

    while (i < TAMANO_RAL && (*Ral).Votantes[Candidato].Estado) //como la posicion solo es virgen si estado = 0, deberia funcionar
    {
        (*Celdas_Consultadas)++;
        if ((*Ral).Votantes[Candidato].DNI == DNI)
        {
            *Posicion = Candidato;
            return 1; //esta en esta posicion
        }

        if((*Ral).Votantes[Candidato].Estado == 2 && *Posicion == -1) //en caso de tratarse de un alta, este es el mejor lugar
        {
            *Posicion = Candidato;
        }
        i++;
        Candidato = (Candidato + 1) % TAMANO_RAL;
    }

    if(i < TAMANO_RAL) //por si la primera celda consultada era virgen
    {
        (*Celdas_Consultadas)++;
    }

    if (!(*Ral).Votantes[Candidato].Estado && *Posicion == -1) //por si caemos en una celda virgen y no encontramos una libre antes
    {
        *Posicion = Candidato;
    }

    return 0; //no esta en el rebalse
}

int Insertar_RAL (RAL *Ral, Padron Votante)
{
    int Celdas, Posicion;
    if((*Ral).Ocupadas == TAMANO_RAL) //esta lleno el RAL
    {
        return 0;
    }
    if(Localizador_RAL(Ral,get_DNI(Votante),&Posicion,&Celdas)) //revisa si encuentra al votante y nos da la posicion donde iria si no esta
    {
        return 0;
    }
    if(Posicion = -1) //no encontro una celda virgen ni vacia en ningun momento
    {
        return 0;
    }
    (*Ral).Votantes[Posicion] = Votante;
    return 1;
}


int Eliminar_RAL (RAL *Ral, Padron Votante)
{
    int Celdas, Posicion;
    if((*Ral).Ocupadas) //esta vacio el RAL
    {
        return 0;
    }
    if(!Localizador_RAL(Ral,get_DNI(Votante),&Posicion,&Celdas)) //no lo encontro
    {
        return 0;
    }
    if(comparaPadron(Votante,(*Ral).Votantes[Posicion]))
    {
        (*Ral).Votantes[Posicion].Estado = 2; //marca la celda como libre
        return 1;
    }
    return 0;
}

int Evocar_RAL (RAL *Ral, int DNI, Padron *Votante,int *Celdas_Consultadas)
{
    int Posicion;
    if((*Ral).Ocupadas) //esta vacio el RAL
    {
        return 0;
    }
    if(Localizador_RAL(Ral,DNI,&Posicion,Celdas_Consultadas)) //no lo encontro
    {
        *Votante = (*Ral).Votantes[Posicion];
        return 1;
    }
    return 0;
}

/* void Mostrar_RAL (RAL *Ral)
{

}
*/

#endif // RAL_H_INCLUDED