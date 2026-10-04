#ifndef PADRON_H_INCLUDED
#define PADRON_H_INCLUDED
#define MAX_NOMBRE 51
#define MAX_DOMICILIO 81

typedef struct Padron
{
    int DNI;
    char Nombre_Apellido[MAX_NOMBRE];
    char Domicilio[MAX_DOMICILIO];
    int Cod_Postal;
    int Mesa;
    int Circuito;
} Padron;

void init_Padron (Padron *padron)
{
    padron->DNI = 0;
    strcpy(padron->Nombre_Apellido, "");
    strcpy(padron->Domicilio, "");
    padron->Cod_Postal = 0;
    padron->Mesa = 0;
    padron->Circuito = 0;
}

int get_DNI (Padron Auxiliar)
{
    return Auxiliar.DNI;
}

void printPadron (Padron padron)
{
    printf("\nDNI: %d", padron.DNI);
    printf("\nNombre completo: %s \n", padron.Nombre_Apellido);
    printf("\nDomicilio: %s \n", padron.Domicilio);
    printf("\nCodigo postal: %d", padron.Cod_Postal);
    printf("\nMesa: %d", padron.Mesa);
    printf("\nCircuito: %d", padron.Circuito);
}

int comparaPadron (Padron p1, Padron p2)
{
    if (strcasecmp(p1.Nombre_Apellido, p2.Nombre_Apellido) == 0 &&
        strcasecmp(p1.Domicilio, p2.Domicilio) == 0 &&
        p1.Cod_Postal == p2.Cod_Postal &&
        p1.Mesa == p2.Mesa &&
        p1.Circuito == p2.Circuito)
        return 1;
    return 0;
}

#endif // PADRON_H_INCLUDED
