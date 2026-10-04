#ifndef RAC_H_INCLUDED
#define RAC_H_INCLUDED
#include "Padron.h"

typedef struct
{
    Padron Votantes[TAMANO];
    int Ocupadas; //indica la cantidad de celdas con elementos
} RAC;

void Inicializador_RAC (RAC *Rac)
{
    int i;
    (*Rac).Ocupadas = 0;
    for (i = 0; i < TAMANO; i++)
    {
        (*Rac).Votantes[i].Estado = 0; //cambia las celdas a virgenes
    }
}

int Localizador_RAC (RAC *Rac, int DNI, int *Posicion, int *Celdas_Consultadas)
{
    int Candidato = Hashing(DNI), i = 0, k = 0;
    *Posicion = -1;
    *Celdas_Consultadas = 0;

    while (i < TAMANO && (*Rac).Votantes[i].Estado) //como la posicion solo es virgen si estado = 0, deberia funcionar
    {
        (*Celdas_Consultadas)++;
        if ((*Rac).Votantes->DNI == DNI)
        {
            *Posicion = Candidato;
            return 1; //esta en esta posicion
        }

        if((*Rac).Votantes[i].Estado == 2 && *Posicion == -1) //en caso de tratarse de un alta, este es el mejor lugar
        {
            *Posicion = Candidato;
        }
        i++;
        k = k + i + 1; //esto calcula el salto cuadratico necesario
        Candidato = (Candidato + k) % TAMANO;
    }

    if(i < TAMANO) //por si la primera celda consultada era virgen
    {
        (*Celdas_Consultadas)++;
    }

    if ((*Rac).Votantes[i].Estado && *Posicion == -1) //por si caemos en una celda virgen y no encontramos una libre antes
    {
        *Posicion = Candidato;
    }

    return 0; //no esta en el rebalse
}


/* int Insertar_RAC (RAC *Rac, Padron Votante)
{

}
*/

/* int Eliminar_RAC (RAC *Rac, Padron Votante)
{

}
*/

/* int Evocar_RAC (RAC *Rac, Padron *Votante)
{

}
*/

/* void Mostrar_RAC (RAC *Rac)
{

}
*/

#endif // RAC_H_INCLUDED