#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#define ANCHO_COL0  22
#define ANCHO_DATOS 14
#include "Padron.h"
#include "RS.h"
#include "RAC.h"
#include "RAL.h"

void CargaArchivo(RAL *ral, RAC *rac, RS *rs, float costos[2][6], float maximos[2][6]);
void TablaComparadora(float costos[2][6], float maximos[2][3]); //ahora solo contiene evocaciones

int main()
{
    int opcion;
    // Declaracion de las Estructuras
    RAL Rebalse_Lineal;
    RAC Rebalse_Cuadratico;
    RS Rebalse_Separado;
    Inicializador_RAL(&Rebalse_Lineal);
    Inicializador_RAC(&Rebalse_Cuadratico);
    init_RS(&Rebalse_Separado);
    float costos[2][6] = {{0}};
    float maximos[2][3] = {{0}};
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
                Mostrar_RAL(&Rebalse_Lineal);
                system("pause");
                break;
            }
            case 3:  // Mostar RAC
            {
                system("cls");
                Mostrar_RAC(&Rebalse_Cuadratico);
                system("pause");
                break;
                }
            case 4:  // Mostrar RS
            {
                system("cls");
                Mostrar_RS(Rebalse_Separado);
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

void CargarArchivo(RAL *ral, RAC *rac, RS *rs, float costos[2][6], float *maximos[2][3])
{
    FILE *Fp; Padron aux;
    int costo;
    int Exito;
    int i, j;
    for (i = 0; i < 2; i++) //limpia los costos si por error se toca 2 veces la opcion 1
    {
        for (j = 0; j < 6; j++)
            costos[i][j] = 0.0;
        for (j = 0; j < 3; j++)
            maximos[i][j] = 0.0;
    }
    Fp = fopen("Operaciones.txt", "r");
    if (Fp == NULL) {
        printf("Error al abrir el archivo.\n");
        return 0;
    }
    Inicializador_RAL(ral);
    Inicializador_RAC(rac);
    init_RS(rs);
    int tarea;
    while (fscanf(Fp, "%d", &tarea) == 1)
    {
        switch (tarea)
        {
            case 1:
                // leer datos
                fscanf(Fp, "%d",&aux.DNI);
                fgetc(Fp);
                fscanf(Fp, " %[^\n]", aux.Nombre_Apellido);
                for(i = 0; aux.Nombre_Apellido[i] != '\0'; i++){
                    aux.Nombre_Apellido[i] = toupper(aux.Nombre_Apellido[i]);
                }
                fscanf(Fp, " %[^\n]", aux.Domicilio);
                for(i = 0; aux.Domicilio[i] != '\0'; i++){
                    aux.Domicilio[i] = toupper(aux.Domicilio[i]);
                }
                fscanf(Fp, "%d", &aux.Cod_Postal);
                fgetc(Fp);
                fscanf(Fp, "%d", &aux.Mesa);
                fgetc(Fp);
                fscanf(Fp, "%d", &aux.Circuito);
                fgetc(Fp);
                aux.Estado = 1; //marca el padron para que cuando se ubique en su celda salga ocupada

                // RAL
                Insertar_RAL(ral, aux);
                
                // RAC
                Insertar_RAC(rac, aux);
                
                // RS
                Alta_RS(rs, aux);
                break;
            case 2:
                // lectura de datos
                fscanf(Fp, "%d",&aux.DNI);
                fgetc(Fp);
                fscanf(Fp, " %[^\n]", aux.Nombre_Apellido);
                for(i = 0; aux.Nombre_Apellido[i] != '\0'; i++){
                    aux.Nombre_Apellido[i] = toupper(aux.Nombre_Apellido[i]);
                }
                fscanf(Fp, " %[^\n]", aux.Domicilio);
                for(i = 0; aux.Domicilio[i] != '\0'; i++){
                    aux.Domicilio[i] = toupper(aux.Domicilio[i]);
                }
                fscanf(Fp, "%d", &aux.Cod_Postal);
                fgetc(Fp);
                fscanf(Fp, "%d", &aux.Mesa);
                fgetc(Fp);
                fscanf(Fp, "%d", &aux.Circuito);
                fgetc(Fp);

                // RAL
                Eliminar_RAL(ral, aux);
                
                // RAC
                Eliminar_RAC(rac, aux);
                
                // RS
                Baja_RS(rs, aux);
                break;
            case 3:
                fscanf(Fp, "%d",&aux.DNI);
                // RAL
                costo = 0;
                Exito = Evocar_RAL(ral, aux.DNI, &aux, &costo);
                int fila_ral = (Exito) ? 0 : 1;  // 0: exitosa, 1: fallida
                costos[fila_ral][0] += costo;
                costos[fila_ral][3]++;
                if (costo > maximos[fila_ral][0]) maximos[fila_ral][0] = costo;

                //RAC
                costo = 0;
                Exito = Evocar_RAC(rac, aux.DNI, &aux, &costo);
                int fila_rac = (Exito) ? 0 : 1;
                costos[fila_rac][1] += costo;
                costos[fila_rac][4]++;
                if (costo > maximos[fila_ral][1]) maximos[fila_ral][1] = costo;

                //RS
                costo = 0;
                // Exito = rs(lso, &aux, &costo);
                int fila_rs = (Exito) ? 0 : 1;
                costos[fila_rs][2] += costo;
                costos[fila_rs][5]++;
                if (costo > maximos[fila_rs][2])maximos[fila_rs][2] = (float)costo;
                break;
            default:
                printf("Tarea no reconocida.\n");
        }
    }
    fclose(Fp);
    return 1;
}
}

void TablaComparadora(float costos[4][6], float maximos[4][3])
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
