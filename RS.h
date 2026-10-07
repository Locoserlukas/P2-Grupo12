#ifndef RS_H_INCLUDED
#define RS_H_INCLUDED
#include "Padron.h"
#define TAM_RS 1249   // Numero primo mas cercano a 2000/1.61*1 = 1242.23

typedef struct
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
    for(int i = 0; i < TAM_RS; i++){
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

int Localizar_RS (RS *rs, int Dni, int *hash, int *costo, Nodo_Lv **pos, Nodo_Lv **prepos)
{
    *hash = hashing(Dni, TAM_RS), 
    *pos = (*rs).rebalse[*hash];
    *prepos = NULL;

    if (*pos == NULL) {
        (*costo)++;  
        return 0;   // balde vacio
    }

    while ((*pos)->Sig != NULL && (*pos)->Votante.DNI != Dni) {
        (*costo)++;
        *prepos = *pos;
        *pos = (*pos)->Sig;
    }

    (*costo)++;
    return (*pos)->Votante.DNI == Dni;  // devuelve 1 si lo encontro, 0 si no
}

int Alta_RS (RS *rs, Padron Votante){
    int hash = 0 , costo = 0;
    Nodo_Lv *pos = NULL, *prepos = NULL;

    if (Localizar_RS(rs, Votante.DNI, &hash, &costo, &pos, &prepos)==0) {
        Nodo_Lv *nuevo = (Nodo_Lv *)malloc(sizeof(Nodo_Lv));
        if (nuevo == NULL) {
            return -1;  // sin memoria
        }
        nuevo->Votante = Votante;
        // Insertar al inicio de la lista
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

void Mostrar_RS (RS rs){
    int elementosEnPagina = 0, paginaActual = 1, i;
    for (i=0; i<TAM_RS; i++){
        Nodo_Lv *actual = rs.rebalse[i];
        int balde = 1;
        printf("---------------------\n");
        printf("Lista numero %d\n", i);
        printf("---------------------\n");

        if (actual == NULL){
            printf("Esta lista esta vacia\n");
        }else {
            while (actual != NULL)
            {
                printf("Balde/Nodo: %d\n", balde);
                printPadron(actual->Votante);

                actual = actual->Sig;
                balde++;
                elementosEnPagina++;
                if (elementosEnPagina==10){   // 10 elementos por pagina
                    printf("------ Fin de pagina %d ------\n\n", paginaActual++);
                    elementosEnPagina = 0;
                    printf("Presione ENTER para continuar...");
                    getchar();
                }
            }
        }
    }
}


#endif // RS_H_INCLUDED
