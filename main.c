#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#define TAMANO 2000
#define ANCHO_COL0  22
#define ANCHO_DATOS 14
#include "Padron.h"
#include "RS.h"
#include "RAC.h"
#include "RAL.h"

void TablaComparadora(float costos[4][6], float maximos[4][3]); // la matriz se va a achicar por lo que parece

int Hashing (int DNI); //la defino aqui porque es generica para todas las estructuras

int main()
{
    int opcion;
    // Declaracion de las Estructuras
    // RAL Rebalse_Lineal;
    // Rac Rebalse_Cuadratico;
    // RS Rebalse_Separado;
    //aca irian los inicializadores
    float costos[4][6] = {{0}};
    float maximos[4][3] = {{0}};
    system ("color 0B");
    do {
        printf("\n----------- Menu de opciones ----------\n");
        printf("<1> Comparacion estructuras\n");
        printf("<2> Mostrar Rebalse Lineal\n");
        printf("<3> Mostrar Rebalse Cuadratico\n");
        printf("<4> Mostrar Rebalse Separado\n");
        printf("<5> Salir\n");
        scanf("%d", &opcion);
        switch(opcion)
        {
            case 1:  // Tabla de costos - comparacion
            {
                //cargar archivo
                TablaComparadora(costos, maximos);
                break;
            }
            case 2:  // Mostrar RAL
            {
                system("cls");
                //codigo
                system("pause");
                break;
            }
            case 3:  // Mostar RAC
            {
                system("cls");
                //codigo
                system("pause");
                break;
                }
            case 4:  // Mostrar RS
            {
                system("cls");
                //codigo
                system("pause");
                break;
            }
            case 5:
            {return 0;}
            default:
                printf("Opcion no valida.\n");
        }
    } while(1==1);
}

int Hashing (int DNI) //modificado ya que todos los dni miden 10 caracteres
{
    char X[10];
    int i, contador = 0;
    sprintf(X, "%d", DNI);
    for(i = 0; i < 10; i++)
    {
        contador += ((int)X[i])*(i+1);
    }
    return contador % TAMANO;
}

void TablaComparadora(float costos[4][6], float maximos[4][3]) // quedo obsoleta
{
    const char *ops[4] =
    {
        "ALTAS",
        "BAJAS",
        "EVOC. EXITOSAS",
        "EVOC. FALLIDAS"
    };
    int i, j;
    float media;

    printf("\n");
    printf("==================== COMPARACION DE ESTRUCTURAS ====================\n\n");

    printf("%-*s", ANCHO_COL0, "Operacion");
    printf("%-*s", ANCHO_DATOS, "ABB");
    printf("%-*s", ANCHO_DATOS, "LVO");
    printf("%-*s", ANCHO_DATOS, "LSOBB");
    printf("\n");
    printf("--------------------------------------------------------------------\n");

    for (i = 0; i < 4; i++)
    {
        printf("%s \n", ops[i]);

        printf("%-*s", ANCHO_COL0, "  Media");
        for (j = 0; j < 3; j++) {
            media = (costos[i][j+3] > 0.0f) ? (costos[i][j] / costos[i][j+3]) : 0.0f;
            printf("%-*.3f", ANCHO_DATOS, media);
        }
        printf("\n");

        printf("%-*s", ANCHO_COL0, "  Maxima");
        for (j = 0; j < 3; j++) {
            printf("%-*.3f", ANCHO_DATOS, maximos[i][j]);
        }
        printf("\n");
        printf("--------------------------------------------------------------------\n");
    }

    printf("\n");
    system("pause");
}
