#ifndef RS_H_INCLUDED
#define RS_H_INCLUDED
#include "Padron.h"
// 2000 / (1.61 * 1) = 1242.23 -> Primo superior mas cercano: 1249
#define TAM_RS 1249

typedef struct Nodo_Lv
{
    Padron Votante;
    struct Nodo_Lv *Sig;
} Nodo_Lv;

typedef struct
{
    Nodo_Lv *rebalse[TAM_RS];
    int Ocupadas;
} RS;

void init_RS (RS *rs)
{
    int i;
    (*rs).Ocupadas = 0;
    for (i = 0; i < TAM_RS; i++)
    {
        (*rs).rebalse[i] = NULL;
    }
}

void freeRS (RS *rs){
    int i;
    for(i = 0; i < TAM_RS; i++){
        Nodo_Lv *actual = (*rs).rebalse[i];
        while(actual != NULL){
            Nodo_Lv *eliminar = actual;
            actual = actual->Sig;
            free(eliminar);
        }
        (*rs).rebalse[i] = NULL;
    }
    (*rs).Ocupadas = 0;
}
// retorna 1 si lo encuentra y 0 si no existe
// Costo = Celdas Consultadas (1 celda de tabla + 1 por cada nodo leido)
int Localizar_RS (RS *rs, int Dni, int *hash, int *costo, Nodo_Lv **pos, Nodo_Lv **prepos)
{
    *costo = 0;
    *hash = hashing(Dni, TAM_RS);
    *pos = (*rs).rebalse[*hash];
    *prepos = NULL;

    // 1 celda consultada: la posicion del arreglo rebalse[*hash]
    (*costo)++;

    if (*pos == NULL) {
        return 0;   // balde vacio
    }

    // recorrido de los nodos
    while ((*pos)->Sig != NULL && (*pos)->Votante.DNI != Dni) {
        (*costo)++;  // nodo actual
        *prepos = *pos;
        *pos = (*pos)->Sig;
    }
    (*costo)++;
    // control de salida del while y el return if de igual a dni
    if ((*pos)->Votante.DNI == Dni){ // salio por igualdad
        return 1;
    }
    else return 0;
}
// retorna 1 si es alta existosa, 0 si esta repetido, -1 si no hay memoria
int Alta_RS (RS *rs, Padron Votante){
    int hash = 0 , costo = 0;
    Nodo_Lv *pos = NULL, *prepos = NULL;

    if (Localizar_RS(rs, Votante.DNI, &hash, &costo, &pos, &prepos)==0) {
        Nodo_Lv *nuevo = (Nodo_Lv *)malloc(sizeof(Nodo_Lv));
        if (nuevo == NULL) {
            return -1;  // sin memoria
        }
        nuevo->Votante = Votante;
        // Insercion de O(1)al inicio de la lista
        nuevo->Sig = (*rs).rebalse[hash];
        (*rs).rebalse[hash] = nuevo;
        (*rs).Ocupadas++;

        return 1;  // alta exitosa
    }
    return 0;  // elemento repetido
}

int Baja_RS (RS *rs, Padron votante){
    int hash = 0 , costo = 0;
    Nodo_Lv *pos = NULL, *prepos = NULL;

    if (Localizar_RS(rs, votante.DNI, &hash, &costo, &pos, &prepos) == 0) {
        return 0;   // No existe el elemento
    }

    if (comparaPadron(pos->Votante, votante)) {
        if (prepos == NULL) {
            // el elemento esta al comienzo de la lista
            (*rs).rebalse[hash] = pos->Sig;
        } else {
            // el elemento esta en el medio o al final
            prepos->Sig = pos->Sig;
        }
        free(pos);
        (*rs).Ocupadas--;
        return 1;  // baja exitosa
    }
    return 0;  // el elemento no coincide
}

Padron Evocar_RS (RS *rs,Padron votante, int *costo, int *exito){
    int hash = 0;
    (*costo) = 0;

    Nodo_Lv *pos = NULL;
    Nodo_Lv *prevpos = NULL;

    if((*rs).Ocupadas == 0)
    {
        Padron vacio;
        *exito = 0;
        return vacio;
    }
    (*exito) = Localizar_RS (rs,votante.DNI,&hash,costo,&pos,&prevpos);

    if (*exito){
        // retorno lo que haya quedado apuntando el cursor
        return pos->Votante;
    }
    // registro nulo en caso de fracaso
    Padron vacio;
    memset(&vacio, 0, sizeof(Padron));
    vacio.DNI = -1;
    return vacio;
}

void Mostrar_RS (RS rs){
    int listasEnPagina = 0;
    int paginaActual = 1;
    int i;

    printf("\n=========== Estado de la estructura RS ==========\n");
    printf("Total de votantes registrados: %d | Capacidad (M): %d\n", (rs).Ocupadas, TAM_RS);
    printf("\n=================================================\n");

    for (i=0; i<TAM_RS; i++)
    {
        Nodo_Lv *actual = (rs).rebalse[i];
        int balde = 1;
        printf("---------------------------\n");
        printf("Poscion | Lista Hashing: %d\n", i);
        printf("---------------------------\n");

        if (actual == NULL){
            printf("[Lista Vacia]\n");
        }else {
            while (actual != NULL)
            {
                printf("-> Nodo: %d\n", balde);
                printPadron(actual->Votante);

                actual = actual->Sig;
                balde++;
            }
        }

        listasEnPagina++;


        if(listasEnPagina == 15)
        {
            printf("\n----- Fin de pagina %d (Presione ENTER para continuar) -----\n", paginaActual++);
            listasEnPagina = 0;
            while (getchar() != '\n'); // limpia buffer y espera ENTER
        }
    }
    if (listasEnPagina > 0){
        printf("\n------- Fin de listado RS -------\n");
    }
}


#endif // RS_H_INCLUDED
