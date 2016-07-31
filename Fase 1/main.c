#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main()
{
    printf("Ingrese un comando:\n");
    char comando[256];
    scanf(" %[^\n]", comando);

    while(strcmp(comando,"exit") != 0)
    {
        leerComando(comando);
        scanf(" %[^\n]", comando);
    }
    return 0;
}

//este método convierte un string a su equivalente en minúscula
void aMinuscula(char* original)
{
    char auxiliar [256];
    int i = 0;
    strcpy(auxiliar,original);

    while(auxiliar[i])
    {
        auxiliar[i] = tolower(auxiliar[i]);
        i++;
    }

    strcpy(original,auxiliar);
}

//lee toda la línea
void leerComando(char* linea)
{
    int casoComando = -1;
    char* comando;                                                          //variable que guarda los tokens de la línea
    char* lineaAux = malloc(strlen("solo quiero ocupar espacio :v") + 1);   //inicializando variable auxiliar
    strcpy(lineaAux,linea);                                                 //guardando el contenido de la línea leída
    comando = strtok(linea," ");                                            //separa el comando del resto de instrucciones
    aMinuscula(comando);

    //caso 0: exec
    //caso 1: mkdisk
    //caso 2: rmdisk
    //caso 3: fdisk
    //caso 4: mount
    //caso 5: unmount

    if(strcmp(comando,"exec") == 0)
    {
        casoComando = 0;
    }
    else if(strcmp(comando,"mkdisk") == 0)
    {
        casoComando = 1;
    }
    else if(strcmp(comando,"rmdisk") == 0)
    {
        casoComando = 2;
    }
    else if(strcmp(comando,"fdisk") == 0)
    {
        casoComando = 3;
    }
    else if(strcmp(comando,"mount") == 0)
    {
        casoComando = 4;
    }
    else if(strcmp(comando,"unmount") == 0)
    {
        casoComando = 5;
    }

    while(comando)                                                          //mientras tenga tokens
    {
        printf("%s\n", comando);
        comando = strtok(NULL, ":");
    }
    printf("Acabó de leer los tokens y la línea original era: %s\n", lineaAux);
}

void analizarLinea(char* comando)
{
    int indice = 0;
    int estado = 0;
    char lexema [256] = {0};
    char actual = malloc(strlen("solo quiero ocupar espacio :v") + 1);
    int tamanoComando = strlen(comando);

    for(indice = 0; indice <= tamanoComando; indice++)
    {
        actual = comando[indice];
//
//        switch(estado)
//        {
//            case 0:
//            case 1:
//            case 2:
//        }
    }
}
