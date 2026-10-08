#ifndef RAC_H_INCLUDED
#define RAC_H_INCLUDED
#include "Padron.h" 
#define TAMANO_RAC 2411

typedef struct
{
    Padron Votantes[TAMANO_RAC]; //tamano definido en base a la formula (aprox 2410)
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

    while (i < TAMANO_RAC && (*Rac).Votantes[Candidato].Estado) //como la posicion solo es virgen si estado = 0, deberia funcionar
    {
        (*Celdas_Consultadas)++;
        if ((*Rac).Votantes[Candidato].DNI == DNI)
        {
            *Posicion = Candidato;
            return 1; //esta en esta posicion
        }

        if((*Rac).Votantes[Candidato].Estado == 2 && *Posicion == -1) //en caso de tratarse de un alta, este es el mejor lugar
        {
            *Posicion = Candidato;
        }
        i++;
        Candidato = (Candidato + k) % TAMANO_RAC;
        k = k + 1; //esto calcula el salto cuadratico necesario
    }

    if(i < TAMANO_RAC) //por si la primera celda consultada era virgen
    {
        (*Celdas_Consultadas)++;
    }

    if ((*Rac).Votantes[i].Estado && *Posicion == -1) //por si caemos en una celda virgen y no encontramos una libre antes
    {
        *Posicion = Candidato;
    }

    return 0; //no esta en el rebalse
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
    if(Posicion = -1) //no encontro una celda virgen ni vacia en ningun momento
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
    if((*Rac).Ocupadas) //esta vacio el RAC
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

int Evocar_RAC (RAL *Rac, int DNI, Padron *Votante,int *Celdas_Consultadas)
{
    int Posicion;
    if((*Rac).Ocupadas) //esta vacio el RAL
    {
        return 0;
    }
    if(Localizador_RAC(Rac,DNI,&Posicion,Celdas_Consultadas)) //no lo encontro
    {
        *Votante = (*Rac).Votantes[Posicion];
        return 1;
    }
    return 0;
}

void Mostrar_RAC (RAC *Rac)
{
    int i, Condicion;
    printf ("\t Votantes Rebalse Abierto Cuadratico (RAC) \n");
    for (i = 0; i < TAMANO_RAC; i++)
    {
        Condicion = (*Rac).Votantes[i].Estado;
        if(!Condicion) //la celda es virgen
        {
            pritnf ("\n La posicion %d es virgen \n", i);
        }
        if(Condicion == 1) //la celda esta ocupada
        {
            printPadron((*Rac).Votantes[i]);
        }
        if(Condicion == 2) //la celda esta libre
        {
            pritnf ("\n La posicion %d esta libre \n", i);
        }
    }
}

#endif // RAC_H_INCLUDED