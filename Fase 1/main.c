#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char comando[256];
    int longitud = 0;
    printf("\t\t\t  Ingrese una instrucción:\n");
    scanf(" %[^\n]", comando);

    if(strcmp(&comando[strlen(comando) -1],"\\") == 0)
    {
        comando[strlen(comando) -1] = '\0';
        concatenarComandoMultilinea(comando);
    }


    while(strcmp(comando,"exit") != 0)
    {
        leerComando(comando);
        printf("\n\n\t\t\t  Ingrese una instrucción:\n");
        scanf(" %[^\n]", comando);
        if(strcmp(&comando[strlen(comando) -1],"\\") == 0)
        {
            comando[strlen(comando) -1] = '\0';
            concatenarComandoMultilinea(comando);
        }
    }
    return 0;
}

void concatenarComandoMultilinea(char* comandoCompleto)
{
    char nuevaLinea[256];
    scanf(" %[^\n]", nuevaLinea);
    //strcat(comandoCompleto, " ");
    strcat(comandoCompleto, nuevaLinea);

    if(strcmp(&nuevaLinea[strlen(nuevaLinea) -1],"\\") == 0)
    {
        comandoCompleto[strlen(comandoCompleto) -1] = '\0';
        concatenarComandoMultilinea(comandoCompleto);
    }
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

    //lista de parámetros de todos los comandos
    char size[256];
    char unit[256];
    char path[256];
    char name[256];
    char type[256];
    char fit[256];
    char delete[256];
    char add[256];
    char id[256];

    //casoComando 0: exec
    //casoComando 1: mkdisk
    //casoComando 2: rmdisk
    //casoComando 3: fdisk
    //casoComando 4: mount
    //casoComando 5: unmount

    //lista de atributos
    char atrSize = "size::";
    char atrUnit = "unit::";
    char atrPath = "path::";
    char atrName[256];
    char atrType[256];
    char atrFit[256];
    char atrDelete[256];
    char atrAdd[256];
    char atrId[256];

    if(strcmp(comando,"exec") == 0)
    {
        casoComando = 0;

//        while(comando)                  //mientras aún tenga instrucciones
//        {
//            comando = strtok(NULL, " ");
//        }
    }
    else if(strcmp(comando,"mkdisk") == 0)
    {
        casoComando = 1;
        comando = strtok(NULL, ":");    //elimina el token "mkdisk"

        while(comando)                  //este while recorre el comando y lo separa en una
        {                               //lista de parámetros. Luego de comparar el parámetro separa
            aMinuscula(comando);        //de la lista por ":" y guardo el contenido en algún lado

            if(strcmp(comando,"-size") == 0)
            {
                comando = strtok(NULL, " ");
                char * aux = comando + 1;       //para quitar el ":" extra
                printf("El contenido del comando -size es: %s\n", aux);
            }
            else if(strcmp(comando,"+unit") == 0)
            {
                comando = strtok(NULL, " ");
                char * aux = comando + 1;       //para quitar el ":" extra
                printf("El contenido del comando +unit es: %s\n", aux);
            }
            else if(strcmp(comando,"-path") == 0)
            {
                comando = strtok(NULL, " ");
                char * aux = comando + 1;       //para quitar el ":" extra
                printf("El contenido del comando -path es: %s\n", aux);
            }
            else if(strcmp(comando,"-name") == 0)
            {
                comando = strtok(NULL, " ");
                char * aux = comando + 1;       //para quitar el ":" extra
                printf("El contenido del comando -name es: %s\n", aux);
            }
            else
            {
                char aux[30];
                strcpy(aux,comando);
                comando = strtok(NULL, " ");
                printf("****El parámetro \"%s\" no es válido****\n",aux);
            }

            comando = strtok(NULL, ":");
        }
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
    else if(strcmp(comando,"unmount:") == 0)
    {
        casoComando = 5;
    }
    else
    {
        printf("****Error: El comando \"%s\" no es válido.****\n",comando);
    }


    printf("Acabó de leer los tokens y la línea original era: %s\n", lineaAux);
}

