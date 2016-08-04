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
    strcat(comandoCompleto, nuevaLinea);

    if(strcmp(&nuevaLinea[strlen(nuevaLinea) -1],"\\") == 0)
    {
        comandoCompleto[strlen(comandoCompleto) -1] = '\0';
        concatenarComandoMultilinea(comandoCompleto);
    }
}//:D

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
    char* lineaAux = malloc(strlen("solo quiero ocupar espacio :v") + 100);   //inicializando variable auxiliar
    strcpy(lineaAux,linea);                                                 //guardando el contenido de la línea leída
    comando = strtok(linea," ");                                            //separa el comando del resto de instrucciones
    aMinuscula(comando);

    //lista de parámetros de todos los comandos
    char size[256] = "";
    char unit[256] = "";
    char path[256] = "";
    char name[254] = "";
    char type[256] = "";
    char fit[256] = "";
    char tdelete[256] = "";
    char add[256] = "";
    char id[256] = "";

    //casoComando 0: exec
    //casoComando 1: mkdisk
    //casoComando 2: rmdisk
    //casoComando 3: fdisk
    //casoComando 4: mount
    //casoComando 5: unmount


    if(strcmp(comando,"exec") == 0)
    {
        casoComando = 0;
        comando = strtok(NULL, " ");    //elimina el token "exec"

        if(comando)
        {
            char* aux = malloc(strlen("solo quiero ocupar espacio :v") + 100);
            strcpy(aux,comando); //+1 para quitar el ":" extra
            char auxArray[256];
            strcpy(auxArray, aux);

            while(strcmp(&auxArray[strlen(auxArray) -1],"\"") != 0)
            {
                comando = strtok(NULL, " ");
                strcat(aux, " ");
                strcat(aux, comando);
                strcpy(auxArray,aux);
            }

            printf("El script a ejecutar tiene la ruta: %s\n", aux);
            /**
            Aquí debería mandar a llamar a la función "ejecutarEXEC"
            **/
        }
        else
        {
            printf("\n***Debes agregar la ruta del script.***\n");
        }
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
                char* aux = malloc(strlen("solo quiero ocupar espacio :v") + 100);
                strcpy(aux,comando+1); //+1 para quitar el ":" extra
                strcpy(size, aux);
//                printf("El contenido del comando -size es: %s\n", aux);
            }
            else if(strcmp(comando,"+unit") == 0)
            {
                comando = strtok(NULL, " ");
                char* aux = malloc(strlen("solo quiero ocupar espacio :v") + 100);
                strcpy(aux,comando+1); //+1 para quitar el ":" extra
                strcpy(unit, aux);
//                printf("El contenido del comando +unit es: %s\n", aux);
            }
            else if(strcmp(comando,"-path") == 0)
            {
                comando = strtok(NULL, " ");
                char* aux = malloc(strlen("solo quiero ocupar espacio :v") + 100);
                strcpy(aux,comando+1); //+1 para quitar el ":" extra
                char auxArray[256];
                strcpy(auxArray, aux);

                while(strcmp(&auxArray[strlen(auxArray) -1],"\"") != 0)
                {
                    comando = strtok(NULL, " ");
                    strcat(aux, " ");
                    strcat(aux, comando);
                    strcpy(auxArray,aux);
                }

                strcpy(path, aux);
//                printf("El contenido del comando -path es: %s\n", aux);
            }
            else if(strcmp(comando,"-name") == 0)
            {
                comando = strtok(NULL, " ");
                char* aux = malloc(strlen("solo quiero ocupar espacio :v") + 100);
                strcpy(aux,comando+1); //+1 para quitar el ":" extra
                char auxArray[256];
                strcpy(auxArray, aux);

                while(strcmp(&auxArray[strlen(auxArray) -1],"\"") != 0)
                {
                    comando = strtok(NULL, " ");
                    strcat(aux, " ");
                    strcat(aux, comando);
                    strcpy(auxArray,aux);
                }

                strcpy(name, aux);
//                printf("El contenido del comando -name es: %s\n", aux);
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
        ejecutarMKDISK(size, unit, path, name);
    }
    else if(strcmp(comando,"rmdisk") == 0)
    {
        casoComando = 2;
        comando = strtok(NULL, ":");    //elimina el token "mkdisk"

        while(comando)                  //este while recorre el comando y lo separa en una
        {                               //lista de parámetros. Luego de comparar el parámetro separa
            aMinuscula(comando);        //de la lista por ":" y guardo el contenido en algún lado

            if(strcmp(comando,"-path") == 0)
            {
                comando = strtok(NULL, " ");
                char* aux = malloc(strlen("solo quiero ocupar espacio :v") + 100);
                strcpy(aux,comando+1); //+1 para quitar el ":" extra
                char auxArray[256];
                strcpy(auxArray, aux);

                while(strcmp(&auxArray[strlen(auxArray) -1],"\"") != 0)
                {
                    comando = strtok(NULL, " ");
                    strcat(aux, " ");
                    strcat(aux, comando);
                    strcpy(auxArray,aux);
                }

                strcpy(path, aux);
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

        ejecutarRMDISK(path);
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

}

//ejecuta el comando "exec"
void ejecutarEXEC(char* path)
{

}

//ejecuta el comando "mkdisk"
void ejecutarMKDISK(char* size, char* unit, char* path, char* name)
{
    if((strcmp(size, "") != 0) && (strcmp(path, "") != 0) && (strcmp(name, "") != 0))
    {
        int sizeDouble = atof(size);       //convierte "size" a un entero para poder hacer validaciones
        aMinuscula(unit);

        if(sizeDouble > 0)
        {
            if((strcmp(unit,"k") == 0) || ((strcmp(unit,"m") == 0)) || ((strcmp(unit,"") == 0)))
            {
                //verificar la extensión del disco
                char* extension = strstr(name,".");

                if(strcasecmp(extension,".dsk\"") == 0)
                {
                    //quitar las comillas del path y name y concaternarlos
                    char* nameLimpio = malloc(strlen("solo quiero ocupar espacio :v") + 100);
                    strncpy(nameLimpio,name+1,strlen(name)-2); //-2 porque toma en cuenta las 2 comillas

                    char* pathLimpio = malloc(strlen("solo quiero ocupar espacio :v") + 100);
                    strncpy(pathLimpio,path+1,strlen(path)-2); //-2 porque toma en cuenta las 2 comillas
                    printf("nombre: %s",nameLimpio);
                    printf("path: %s",pathLimpio);
                    //crear el directorio si no existe
                    char crearDirectorio[100] = "mkdir -p ";
                    strcat(crearDirectorio, path);
                    system(crearDirectorio);

                    int unidades = 1024 * 1024 * atof(size); // unidad por defecto Megabytes

                    if(strcmp(unit,"k") == 0)
                    {
                        unidades = 1024 * atof(size);
                    }

                    //inicializa el disco con \0
                    char llenarDisco[100] = "dd if=/dev/zero of='";
                    strcat(llenarDisco, pathLimpio);
                    strcat(llenarDisco, nameLimpio);
                    strcat(llenarDisco, "' bs=");
                    char* unidadesChar = malloc(strlen("solo quiero ocupar espacio :v") + 1);
                    sprintf(unidadesChar, "%d", unidades);
                    strcat(llenarDisco, unidadesChar);
                    strcat(llenarDisco, " count=1");
                    system(llenarDisco);
                    printf("\n****¡Disco creado con éxito!****\n");

                }
                else
                {
                    printf("\n****La extensión del disco debe ser \".dsk\"****\n");
                }


            }
            else
            {
                printf("\n****El parámetro +unit debe ser \"K\" o \"M\"****\n");
            }
        }
        else
        {
            printf("\n****El parámetro -size debe ser un número mayor a 0****\n");
        }

    }
    else
    {
        printf("\n***Verifica que hayas incluido todos los parámetros obligatorios para el comando mkdisk***\n");
        printf("-size\n");
        printf("-path\n");
        printf("-name\n\n");
    }
}

//ejecuta el comando "rmdisk"
void ejecutarRMDISK(char* path)
{
    if(strcmp(path, "") != 0)
    {
        printf("¿Quieres eliminar todo el contenido del disco? [S/n]\n");
        char nuevaLinea[256];
        scanf(" %[^\n]", nuevaLinea);
        aMinuscula(nuevaLinea);

        if(strcmp(nuevaLinea,"s") == 0)
        {
            char eliminarDisco [100] = "rm ";
            strcat(eliminarDisco, path);
            system(eliminarDisco);
        }

//        char* pathLimpio = malloc(strlen("solo quiero ocupar espacio :v") + 1);
//        strncpy(pathLimpio,path+1,strlen(path)-2); //-2 porque toma en cuenta las 2 comillas
//        printf("la ruta %s\n",pathLimpio);
//        FILE *disco;
//        disco = fopen(pathLimpio,"r");
//
//        if(disco == NULL)
//        {
//            printf("no hay disco :v");
//        }

    }
    else
    {
        printf("\n***Verifica que hayas incluido todos los parámetros obligatorios para el comando rmdisk***\n");
        printf("-path\n\n");

    }
}
//ejecuta el comando "fdisk"
void ejecutarFDISK(char* size, char* unit, char* path, char* type, char* fit, char* tdelete, char* name, char* add)
{

}

//ejecuta el comando "mount"
void ejecutarMOUNT(char* path, char* name)
{

}

//ejecuta el comando "unmount"
void ejecutarUNMOUNT(char* id)
{

}
