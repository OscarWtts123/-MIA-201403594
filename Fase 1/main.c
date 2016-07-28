#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    printf("Ingrese un comando:\n");
    char comando [256];
    scanf("%[^\n]", comando);
    leerComando(comando);
    return 0;
}

void leerComando(char* linea)
{
    char* comando;                 //variable que guarda los tokens de la línea
    strcpy(&comando," ");
    comando = strtok(linea," "); //primera lectura de token

    while(comando)                 //mientras tenga tokens
    {
        printf("%s\n", comando);
        comando = strtok(NULL, " ");
    }
}
