#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "structs.h"

char particionesMontadas [50][50][256] = {""}; //una tabla de 50 * 50, que almacena strings de 256 caracteres
//lista de letras disponibles para usar como id de disco
char identificadores [26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};


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

int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
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
    char id[10] = "";
    char ruta[256] = "";

    //casoComando 0: exec
    //casoComando 1: mkdisk
    //casoComando 2: rmdisk
    //casoComando 3: fdisk
    //casoComando 4: mount
    //casoComando 5: unmount


    if(strcmp(comando,"exec") == 0)
    {
        casoComando = 0;
        comando = strtok(NULL, ":");    //elimina el token "exec"

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

                ejecutarEXEC(aux);
            }
            else
            {
                char aux[30];
                strcpy(aux,comando);
                comando = strtok(NULL, " ");
                printf("\x1B[33m****El parámetro \"%s\" no es válido****\x1B[0m\n",aux);
            }

            comando = strtok(NULL, ":");
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
                printf("\x1B[33m****El parámetro \"%s\" no es válido****\x1B[0m\n",aux);
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
                printf("\x1B[33m****El parámetro \"%s\" no es válido****\x1B[0m\n",aux);
            }

            comando = strtok(NULL, ":");
        }

        ejecutarRMDISK(path);
    }
    else if(strcmp(comando,"fdisk") == 0)
    {
        casoComando = 3;
        comando = strtok(NULL, ":");    //elimina el token "fdisk"

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
            else if(strcmp(comando,"+type") == 0)
            {
                comando = strtok(NULL, " ");
                char* aux = malloc(strlen("solo quiero ocupar espacio :v") + 100);
                strcpy(aux,comando+1); //+1 para quitar el ":" extra
                strcpy(type, aux);
//                printf("El contenido del comando +unit es: %s\n", aux);
            }
            else if(strcmp(comando,"+fit") == 0)
            {
                comando = strtok(NULL, " ");
                char* aux = malloc(strlen("solo quiero ocupar espacio :v") + 100);
                strcpy(aux,comando+1); //+1 para quitar el ":" extra
                strcpy(fit, aux);
//                printf("El contenido del comando +unit es: %s\n", aux);
            }
            else if(strcmp(comando,"+delete") == 0)
            {
                comando = strtok(NULL, " ");
                char* aux = malloc(strlen("solo quiero ocupar espacio :v") + 100);
                strcpy(aux,comando+1); //+1 para quitar el ":" extra
                strcpy(tdelete, aux);
//                printf("El contenido del comando +unit es: %s\n", aux);
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
            else if(strcmp(comando,"+add") == 0)
            {
                comando = strtok(NULL, " ");
                char* aux = malloc(strlen("solo quiero ocupar espacio :v") + 100);
                strcpy(aux,comando+1); //+1 para quitar el ":" extra
                strcpy(add, aux);
//                printf("El contenido del comando +unit es: %s\n", aux);
            }
            else
            {
                char aux[30];
                strcpy(aux,comando);
                comando = strtok(NULL, " ");
                printf("\x1B[33m****El parámetro \"%s\" no es válido****\x1B[0m\n",aux);
            }

            comando = strtok(NULL, ":");
        }
        ejecutarFDISK(size,unit,path,type,fit,tdelete,name,add);
    }
    else if(strcmp(comando,"mount") == 0)
    {
        casoComando = 4;
        comando = strtok(NULL, ":");    //elimina el token "mount"

        if(comando == NULL) //SIGNIFICIA QUE NO VIENEN PARAMETROS
        {
            mostrarParticionesMontadas();
        }
        else
        {
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
                printf("\x1B[33m****El parámetro \"%s\" no es válido****\x1B[0m\n",aux);
                }

                comando = strtok(NULL, ":");
            }
            ejecutarMOUNT(path, name);
        }
    }
    else if(strcmp(comando,"unmount") == 0)
    {
        casoComando = 5;
        comando = strtok(NULL, ":");    //elimina el token "unomunt"
        int indice = 0;
        char* idIndice = malloc(strlen("solo quiero ocupar espacio :v") + 50);

        while(comando)                  //este while recorre el comando y lo separa en una
        {                               //lista de parámetros. Luego de comparar el parámetro separa
            aMinuscula(comando);        //de la lista por ":" y guardo el contenido en algún lado
            indice++;
            strcpy(idIndice,"");
            sprintf(idIndice, "-id%d", indice);

            if(strcmp(comando,idIndice) == 0)
            {
                comando = strtok(NULL, " ");
                char* aux = malloc(strlen("solo quiero ocupar espacio :v") + 100);
                strcpy(aux,comando+1); //+1 para quitar el ":" extra
                ejecutarUNMOUNT(aux); //le va mandando uno por uno los identificadores
//                printf("El contenido del comando -size es: %s\n", aux);
            }
            else
            {
                char aux[30];
                strcpy(aux,comando);
                comando = strtok(NULL, " ");
                printf("\x1B[33m****El parámetro \"%s\" no es válido****\x1B[0m\n",aux);
            }

            comando = strtok(NULL, ":");
        }
    }
    else if(strcmp(comando,"rep") == 0)
    {
        casoComando = 6;
        comando = strtok(NULL, ":");    //elimina el token "rep"

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
            else if(strcmp(comando,"-id") == 0)
            {
                comando = strtok(NULL, " ");
                char* aux = malloc(strlen("solo quiero ocupar espacio :v") + 100);
                strcpy(aux,comando+1); //+1 para quitar el ":" extra
                strcpy(id, aux);
            }
            else if(strcmp(comando,"+ruta") == 0)
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

                strcpy(ruta, aux);
    //                printf("El contenido del comando -path es: %s\n", aux);
            }
            else
            {
                char aux[30];
                strcpy(aux,comando);
                comando = strtok(NULL, " ");
                printf("\x1B[33m****El parámetro \"%s\" no es válido****\x1B[0m\n",aux);
            }

            comando = strtok(NULL, ":");
        }
        ejecutarREP(name,path,id,ruta);
    }
    else
    {
        printf("\x1B[33m****Error: El comando \"%s\" no es válido.****\x1B[0m\n",comando);
    }

}

//busca el id de una partición con el path del disco y el nombre de la partición /**esto tabmién lo toqué :v**/
void retornarIdParticion(char* id, char* path, char* nombre)
{
    int disco = 0;
    int particion = 1;
    char* aux = malloc(strlen("solo quiero ocupar espacio :v") + 100);

    while(disco < 50) //almacena hasta el índice 49 (50 discos)
    {
        if(strcmp(particionesMontadas[disco][0] ,path)==0)
        {

            while ((strcmp(particionesMontadas[disco][particion] ,nombre)!=0) && (particion < 50))
            {
                particion++;
            }
            sprintf(aux, "vd%c%d",identificadores[disco], particion);
            strcpy(id, aux);
            break;
        }
        disco++;
    }
}

//ejecuta el comando "exec"
void ejecutarEXEC(char* path)
{
    //quitar las comillas del path
    char* pathLimpio = malloc(strlen("solo quiero ocupar espacio :v") + 100);
    strncpy(pathLimpio,path+1,strlen(path)-2); //-2 porque toma en cuenta las 2 comillas

    //Verificar que el archivo exista
    FILE *script = fopen(pathLimpio,"r");
    if(script != NULL)
    {
        char *linea = malloc(500);
        printf("\n");

        while(fgets(linea,500,script) != NULL)
        {
            if(strcmp(linea,"\n")!=0)
            {
                char lineaLimpia [500];
                strcpy(lineaLimpia,"");
                strcpy(lineaLimpia,linea);

                if(lineaLimpia[strlen(lineaLimpia) -1] =='\n')
                {
                    lineaLimpia[strlen(lineaLimpia) -1] = '\0';
                }

                if(lineaLimpia[0] != '#') //los comentarios no se ejecutan, solo se imprimen en pantalla
                {
                    if(strcmp(&lineaLimpia[strlen(lineaLimpia) -1],"\\") == 0)
                    {
                        lineaLimpia[strlen(lineaLimpia) -1] = '\0';

                        char nuevaLinea[500];
                        fgets(nuevaLinea,500,script);
                        strcat(lineaLimpia, nuevaLinea);
                        if(lineaLimpia[strlen(lineaLimpia) -1] =='\n')
                        {
                            lineaLimpia[strlen(lineaLimpia) -1] = '\0';
                        }
                    }

                    printf("\n%s\n",lineaLimpia);
                    leerComando(lineaLimpia);
                }
                else
                {
                    if(lineaLimpia[strlen(lineaLimpia) -1] =='\n')
                    {
                        lineaLimpia[strlen(lineaLimpia) -1] = '\0';
                    }
                    printf("\n\x1B[32m%s\x1B[0m",lineaLimpia);
                }

            }
            else
            {
                printf("\n");
            }
        }
    }
    else
    {
        printf("\n\x1B[33m***El archivo que intentas cargar no existe***\x1B[0m\n");
    }
}

//ejecuta el comando "mkdisk"
void ejecutarMKDISK(char* size, char* unit, char* path, char* name)
{
    if((strcmp(size, "") != 0) && (strcmp(path, "") != 0) && (strcmp(name, "") != 0))
    {
        int sizeDouble = atof(size);       //convierte "size" a un entero para poder hacer validaciones
        aMinuscula(unit);

        if(sizeDouble >= 0)
        {
            if((strcmp(unit,"k") == 0) || ((strcmp(unit,"m") == 0)) || ((strcmp(unit,"") == 0)))
            {
                //verificar la extensión del disco
                char* extension = strstr(name,".");

                if(strcasecmp(extension,".dsk\"") == 0)
                {

                    int unidades = 1024 * 1024 * atof(size); // unidad por defecto Megabytes
                    int banderaTamano = 0;

                    if(strcmp(unit,"k") == 0)
                    {
                        unidades = 1024 * atof(size);
                        if(atof(size)>=10240)
                        {
                            banderaTamano = 1;
                        }
                    }
                    else
                    {
                        if(atof(size)>=10)
                        {
                            banderaTamano = 1;
                        }
                    }
//((strcmp(unit,"k") == 0) && (size >= 10240 )) || ((strcmp(unit,"m") == 0) && (size >= 10 ))
                    if(banderaTamano == 1)
                    {
                        //quitar las comillas del path y name y concaternarlos
                        char* nameLimpio = malloc(strlen("solo quiero ocupar espacio :v") + 100);
                        strncpy(nameLimpio,name+1,strlen(name)-2); //-2 porque toma en cuenta las 2 comillas

                        char* pathLimpio = malloc(strlen("solo quiero ocupar espacio :v") + 100);
                        strncpy(pathLimpio,path+1,strlen(path)-2); //-2 porque toma en cuenta las 2 comillas

                        //crear el directorio si no existe
                        char crearDirectorio[100] = "mkdir -p ";
                        strcat(crearDirectorio, path);
                        system(crearDirectorio);

//                        int unidades = 1024 * 1024 * atof(size); // unidad por defecto Megabytes
//
//                        if(strcmp(unit,"k") == 0)
//                        {
//                            unidades = 1024 * atof(size);
//                        }

    /**
    por acá debería crear el mbr e inicializarlo
    para luego sumarle el espacio que ocupa
    al espacio total del disco
    **/
                        MBR mbr;
                        time_t tiempo = time(0);                                            //esta parte guarda la hora
                        struct tm *tlocal = localtime(&tiempo);                             //y fecha actual del sistema
                        strftime(mbr.mbr_fecha_creacion,128,"%d/%m/%y %H:%M:%S",tlocal);    //para la creación del disco

                        mbr.mbr_tamano = unidades + sizeof(mbr);
                        srand(time(NULL));                      //toma el tiempo como semilla para iniciar el random
                        mbr.mbr_disk_signature = rand();
                        mbr.mbr_particion[0].part_status = 'n'; // "n" indica que no está usada, "y" indica lo contrario
                        mbr.mbr_particion[1].part_status = 'n'; // "n" indica que no está usada, "y" indica lo contrario
                        mbr.mbr_particion[2].part_status = 'n'; // "n" indica que no está usada, "y" indica lo contrario
                        mbr.mbr_particion[3].part_status = 'n'; // "n" indica que no está usada, "y" indica lo contrario

                        //inicializa el disco con \0
                        char* ruta = malloc(strlen("solo quiero ocupar espacio :v") + 100);
                        strcpy(ruta,"");
                        strcat(ruta, pathLimpio);
                        strcat(ruta, nameLimpio);
                        FILE *disco = fopen (ruta, "w+b"); //abro y creo el archivo aquí, para tener control del puntero antes de comenzar
                                                            //a llenar de ceros

                        char llenarDisco[100] = "dd if=/dev/zero of='";
                        strcat(llenarDisco, pathLimpio);
                        strcat(llenarDisco, nameLimpio);
                        strcat(llenarDisco, "' bs=");
                        char* unidadesChar = malloc(strlen("solo quiero ocupar espacio :v") + 1);
    /**este le hace
    espacio al mbr**/   sprintf(unidadesChar, "%d", unidades + sizeof(mbr));

    /**este toma espacio
    del disco para
    el mbr**/           //sprintf(unidadesChar, "%d", unidades);

                        /**por el momento, le creo espacio aparte al disco para almacenar el mbr**/

                        strcat(llenarDisco, unidadesChar);
                        strcat(llenarDisco, " count=1");
                        system(llenarDisco);

                        //escribe el mbr en el disco
                        if(disco == NULL)
                        {
                            printf("esta charada no sirve\n");
                            printf("%s\n",ruta);
                            printf("%s\n",pathLimpio);
                            printf("%s\n",nameLimpio);
                        }
                        fseek(disco,0,SEEK_SET);
                        fwrite(&mbr,sizeof(mbr),1,disco);
                        fclose(disco);

                        printf("\n\x1B[33m****¡Disco creado con éxito!****\x1B[0m\n");
                    }
                    else
                    {
                        printf("\n\x1B[33m****El tamaño mínimo de un disco debe ser de 10MB****\x1B[0m\n");
                    }
                }
                else
                {
                    printf("\n\x1B[33m****La extensión del disco debe ser \".dsk\"****\x1B[0m\n");
                }


            }
            else
            {
                printf("\n\x1B[33m****El parámetro +unit debe ser \"K\" o \"M\"****\x1B[0m\n");
            }
        }
        else
        {
            printf("\n\x1B[33m****El parámetro -size debe ser un número mayor a 0****\x1B[0m\n");
        }

    }
    else
    {
        printf("\n\x1B[33m***Verifica que hayas incluido todos los parámetros obligatorios para el comando mkdisk***\n");
        printf("-size\n");
        printf("-path\n");
        printf("-name\x1B[0m\n\n");
    }
}

//ejecuta el comando "rmdisk"
void ejecutarRMDISK(char* path)
{
    if(strcmp(path, "") != 0)
    {
        printf("\x1B[31m¿Quieres eliminar todo el contenido del disco? [S/n]\x1B[0m\n");
        char nuevaLinea[256];
        scanf(" %[^\n]", nuevaLinea);
        aMinuscula(nuevaLinea);

        if(strcmp(nuevaLinea,"s") == 0)
        {
            int disco = 0;
            int bandera = 0;
            char* pathLimpio = malloc(strlen("solo quiero ocupar espacio :v") + 100);
            strncpy(pathLimpio,path+1,strlen(path)-2); //-2 porque toma en cuenta las 2 comillas

//            FILE *archivo = fopen(pathLimpio,"r");
//
//            if(archivo != NULL)
//            {
//
//            }
//            else
//            {
//
//            }

            while(disco < 50) //almacena hasta el índice 49 (50 discos)
            {
                if(strcmp(particionesMontadas[disco][0] ,pathLimpio)==0){
                    bandera = 1;
                    break;
                }
                disco++;
            }

            /**nuevo**/
            if(bandera == 0)
            {
                char eliminarDisco [100] = "rm ";
                strcat(eliminarDisco, path);
                system(eliminarDisco);
            }
            else
            {
                printf("\n\x1B[33m****Para poder borrar el disco primero desmonta sus particiones.****\x1B[0m\n");
            }

           //printf("\n\x1B[33m****¡Disco eliminado exitosamente!****\x1B[0m\n");
        }

    }
    else
    {
        printf("\n\x1B[33m***Verifica que hayas incluido todos los parámetros obligatorios para el comando rmdisk***\n");
        printf("-path\x1B[0m\n\n");

    }
}

//ejecuta el comando "fdisk"
void ejecutarFDISK(char* size, char* unit, char* path, char* type, char* fit, char* tdelete, char* name, char* add)
{
    if((strcmp(path, "") != 0) && (strcmp(name, "") != 0))
    {
        aMinuscula(unit);
        aMinuscula(type);
        aMinuscula(fit);
        aMinuscula(tdelete);
        char* pathLimpio = malloc(strlen("solo quiero ocupar espacio :v") + 100);
        strncpy(pathLimpio,path+1,strlen(path)-2); //-2 porque toma en cuenta las 2 comillas

        char* nameLimpio = malloc(strlen("solo quiero ocupar espacio :v") + 100);
        memset(nameLimpio,'\0',strlen(nameLimpio));
        strncpy(nameLimpio,name+1,strlen(name)-2); //-2 porque toma en cuenta las 2 comillas

        FILE * disco = fopen(pathLimpio, "r+b");

        if(disco != NULL) //EL ARCHIVO SÍ EXISTE
        {
            if((strcmp(unit,"k") == 0) || ((strcmp(unit,"m") == 0)) || (strcmp(unit,"b") == 0) || ((strcmp(unit,"") == 0)))
            {
                if((strcmp(type,"p") == 0) || ((strcmp(type,"e") == 0)) || (strcmp(type,"l") == 0) || ((strcmp(type,"") == 0)))
                {
                    if((strcmp(fit,"bf") == 0) || ((strcmp(fit,"ff") == 0)) || (strcmp(fit,"wf") == 0) || ((strcmp(fit,"") == 0)))
                    {
                        char fitPart = 'w'; //fit por defecto

                        if(strcmp(fit,"bf") == 0)
                        {
                            fitPart = 'b';
                        }
                        else if(strcmp(fit,"ff") == 0)
                        {
                            fitPart = 'f';
                        }

                        int unidadesExtras = 1024 * atof(add); //unidad por defecto Kilobytes expresado en bytes
                        int unidades = 1024 * atof(size); // unidad por defecto Kilobytes, unidades es el size expresado en bytes
                        int banderaTamano = 0;

                        if(strcmp(unit,"m") == 0)
                        {
                            unidadesExtras = 1024 * 1024 * atof(add);
                            unidades = 1024 * 1024 * atof(size);
                            if(atof(size)>=2)
                            {
                                banderaTamano = 1;
                            }
                        }
                        else if(strcmp(unit,"b") == 0)
                        {
                            unidades = atof(size);
                            unidadesExtras = atof(add);
                            if(atof(size)>=2097152)
                            {
                                banderaTamano = 1;
                            }
                        }
                        else
                        {
                            if(atof(size)>=2048)
                            {
                                banderaTamano = 1;
                            }
                        }

                        MBR mbr; //LECTURA DEL MBR DEL DISCO Y ALMACENARLO EN RAM
                        fread (&mbr, sizeof(mbr), 1,disco);

                        if((strcmp(tdelete,"") == 0) && (strcmp(add,"") == 0)) //significa que se quiere crear una partición
                        {
                            if(banderaTamano == 1) //sí cumple con el mínimo de tamaño
                            {
                                if((strcmp(type,"p") == 0) || (strcmp(type,"") == 0)) //crear partición primaria
                                {
                                    if((mbr.mbr_particion[0].part_status == 'n') || (mbr.mbr_particion[1].part_status == 'n')
                                    || (mbr.mbr_particion[2].part_status == 'n') || (mbr.mbr_particion[3].part_status == 'n'))
                                    {
                                        int indiceParticion = -1;
/** nueva onda **/

                                        if((mbr.mbr_particion[0].part_status == 'n') && (mbr.mbr_particion[1].part_status == 'n')
                                        && (mbr.mbr_particion[2].part_status == 'n') && (mbr.mbr_particion[3].part_status == 'n'))
                                        {
                                            if((mbr.mbr_tamano - sizeof(mbr)) >= unidades) //cabe en el tamaño del archivo
                                            {
                                                strcpy(mbr.mbr_particion[0].part_name, nameLimpio);
                                                mbr.mbr_particion[0].part_start = sizeof(mbr);
                                                mbr.mbr_particion[0].part_status = 'y';
                                                mbr.mbr_particion[0].part_size = unidades;
                                                mbr.mbr_particion[0].part_type = 'p';
                                                mbr.mbr_particion[0].part_fit = fitPart;

                                                printf("\n\x1B[33m****¡La partición primaria %s se ha creado con éxito!****\x1B[0m\n", name);
                                            }
                                            else
                                            {

                                                printf("\n\x1B[33m****No queda espacio en el disco****\x1B[0m\n");
                                            }
                                        }
                                        else if((mbr.mbr_particion[0].part_start - sizeof(mbr)) >= unidades) //cabe entre el mbr y part0
                                        {
                                            strcpy(mbr.mbr_particion[3].part_name, mbr.mbr_particion[2].part_name);
                                            mbr.mbr_particion[3].part_start = mbr.mbr_particion[2].part_start;
                                            mbr.mbr_particion[3].part_status = mbr.mbr_particion[2].part_status;
                                            mbr.mbr_particion[3].part_size = mbr.mbr_particion[2].part_size;
                                            mbr.mbr_particion[3].part_type = mbr.mbr_particion[2].part_type;
                                            mbr.mbr_particion[3].part_fit = mbr.mbr_particion[2].part_fit;

                                            strcpy(mbr.mbr_particion[2].part_name, mbr.mbr_particion[1].part_name);
                                            mbr.mbr_particion[2].part_start = mbr.mbr_particion[1].part_start;
                                            mbr.mbr_particion[2].part_status = mbr.mbr_particion[1].part_status;
                                            mbr.mbr_particion[2].part_size = mbr.mbr_particion[1].part_size;
                                            mbr.mbr_particion[2].part_type = mbr.mbr_particion[1].part_type;
                                            mbr.mbr_particion[2].part_fit = mbr.mbr_particion[1].part_fit;

                                            strcpy(mbr.mbr_particion[1].part_name, mbr.mbr_particion[0].part_name);
                                            mbr.mbr_particion[1].part_start = mbr.mbr_particion[0].part_start;
                                            mbr.mbr_particion[1].part_status = mbr.mbr_particion[0].part_status;
                                            mbr.mbr_particion[1].part_size = mbr.mbr_particion[0].part_size;
                                            mbr.mbr_particion[1].part_type = mbr.mbr_particion[0].part_type;
                                            mbr.mbr_particion[1].part_fit = mbr.mbr_particion[0].part_fit;

                                            strcpy(mbr.mbr_particion[0].part_name, nameLimpio);
                                            mbr.mbr_particion[0].part_start = sizeof(mbr);
                                            mbr.mbr_particion[0].part_status = 'y';
                                            mbr.mbr_particion[0].part_size = unidades;
                                            mbr.mbr_particion[0].part_type = 'p';
                                            mbr.mbr_particion[0].part_fit = fitPart;

                                            printf("\n\x1B[33m****¡La partición primaria %s se ha creado con éxito!****\x1B[0m\n", name);
                                        }
                                        else if(mbr.mbr_particion[1].part_status == 'n')
                                        {
                                            if((mbr.mbr_tamano - (mbr.mbr_particion[0].part_size + mbr.mbr_particion[0].part_start)) >= unidades) //cabe entre part 0 y el tamaño total
                                            {
                                                strcpy(mbr.mbr_particion[1].part_name, nameLimpio);
                                                mbr.mbr_particion[1].part_start = (mbr.mbr_particion[0].part_size + mbr.mbr_particion[0].part_start);
                                                mbr.mbr_particion[1].part_status = 'y';
                                                mbr.mbr_particion[1].part_size = unidades;
                                                mbr.mbr_particion[1].part_type = 'p';
                                                mbr.mbr_particion[1].part_fit = fitPart;

                                                printf("\n\x1B[33m****¡La partición primaria %s se ha creado con éxito!****\x1B[0m\n", name);
                                            }
                                            else
                                            {

                                                printf("\n\x1B[33m****No queda espacio en el disco****\x1B[0m\n");
                                            }
                                        }
                                        else if(mbr.mbr_particion[1].part_start - (mbr.mbr_particion[0].part_size + mbr.mbr_particion[0].part_start) >= unidades) //cabe entre el part0 y part1
                                        {
                                            strcpy(mbr.mbr_particion[3].part_name, mbr.mbr_particion[2].part_name);
                                            mbr.mbr_particion[3].part_start = mbr.mbr_particion[2].part_start;
                                            mbr.mbr_particion[3].part_status = mbr.mbr_particion[2].part_status;
                                            mbr.mbr_particion[3].part_size = mbr.mbr_particion[2].part_size;
                                            mbr.mbr_particion[3].part_type = mbr.mbr_particion[2].part_type;
                                            mbr.mbr_particion[3].part_fit = mbr.mbr_particion[2].part_fit;

                                            strcpy(mbr.mbr_particion[2].part_name, mbr.mbr_particion[1].part_name);
                                            mbr.mbr_particion[2].part_start = mbr.mbr_particion[1].part_start;
                                            mbr.mbr_particion[2].part_status = mbr.mbr_particion[1].part_status;
                                            mbr.mbr_particion[2].part_size = mbr.mbr_particion[1].part_size;
                                            mbr.mbr_particion[2].part_type = mbr.mbr_particion[1].part_type;
                                            mbr.mbr_particion[2].part_fit = mbr.mbr_particion[1].part_fit;

                                            strcpy(mbr.mbr_particion[1].part_name, nameLimpio);
                                            mbr.mbr_particion[1].part_start = (mbr.mbr_particion[0].part_size + mbr.mbr_particion[0].part_start);
                                            mbr.mbr_particion[1].part_status = 'y';
                                            mbr.mbr_particion[1].part_size = unidades;
                                            mbr.mbr_particion[1].part_type = 'p';
                                            mbr.mbr_particion[1].part_fit = fitPart;

                                            printf("\n\x1B[33m****¡La partición primaria %s se ha creado con éxito!****\x1B[0m\n", name);
                                        }
                                        else if(mbr.mbr_particion[2].part_status == 'n')
                                        {
                                            if((mbr.mbr_tamano - (mbr.mbr_particion[1].part_size + mbr.mbr_particion[1].part_start)) >= unidades) //cabe entre part 1 y el tamaño total
                                            {
                                                strcpy(mbr.mbr_particion[2].part_name, nameLimpio);
                                                mbr.mbr_particion[2].part_start = (mbr.mbr_particion[1].part_size + mbr.mbr_particion[1].part_start);
                                                mbr.mbr_particion[2].part_status = 'y';
                                                mbr.mbr_particion[2].part_size = unidades;
                                                mbr.mbr_particion[2].part_type = 'p';
                                                mbr.mbr_particion[2].part_fit = fitPart;

                                                printf("\n\x1B[33m****¡La partición primaria %s se ha creado con éxito!****\x1B[0m\n", name);
                                            }
                                            else
                                            {

                                                printf("\n\x1B[33m****No queda espacio en el disco****\x1B[0m\n");
                                            }
                                        }
                                        else if(mbr.mbr_particion[2].part_start - (mbr.mbr_particion[1].part_size + mbr.mbr_particion[1].part_start) >= unidades) //cabe entre el part1 y part2
                                        {
                                            strcpy(mbr.mbr_particion[3].part_name, mbr.mbr_particion[2].part_name);
                                            mbr.mbr_particion[3].part_start = mbr.mbr_particion[2].part_start;
                                            mbr.mbr_particion[3].part_status = mbr.mbr_particion[2].part_status;
                                            mbr.mbr_particion[3].part_size = mbr.mbr_particion[2].part_size;
                                            mbr.mbr_particion[3].part_type = mbr.mbr_particion[2].part_type;
                                            mbr.mbr_particion[3].part_fit = mbr.mbr_particion[2].part_fit;

                                            strcpy(mbr.mbr_particion[2].part_name, nameLimpio);
                                            mbr.mbr_particion[2].part_start = (mbr.mbr_particion[1].part_size + mbr.mbr_particion[1].part_start);
                                            mbr.mbr_particion[2].part_status = 'y';
                                            mbr.mbr_particion[2].part_size = unidades;
                                            mbr.mbr_particion[2].part_type = 'p';
                                            mbr.mbr_particion[2].part_fit = fitPart;

                                            printf("\n\x1B[33m****¡La partición primaria %s se ha creado con éxito!****\x1B[0m\n", name);
                                        }
                                        else if(mbr.mbr_particion[3].part_status == 'n')
                                        {
                                            if((mbr.mbr_tamano - (mbr.mbr_particion[2].part_size + mbr.mbr_particion[2].part_start)) >= unidades) //cabe entre part 2 y el tamaño total
                                            {
                                                strcpy(mbr.mbr_particion[3].part_name, nameLimpio);
                                                mbr.mbr_particion[3].part_start = (mbr.mbr_particion[2].part_size + mbr.mbr_particion[2].part_start);
                                                mbr.mbr_particion[3].part_status = 'y';
                                                mbr.mbr_particion[3].part_size = unidades;
                                                mbr.mbr_particion[3].part_type = 'p';
                                                mbr.mbr_particion[3].part_fit = fitPart;

                                                printf("\n\x1B[33m****¡La partición primaria %s se ha creado con éxito!****\x1B[0m\n", name);
                                            }
                                            else
                                            {

                                                printf("\n\x1B[33m****No queda espacio en el disco****\x1B[0m\n");
                                            }
                                        }
                                        else
                                        {

                                            printf("\n\x1B[33m****No queda espacio en el disco****\x1B[0m\n");
                                        }

/** nueva onda **/
                                    }
                                    else
                                    {
                                        printf("\n\x1B[33m****No se pueden crear más particiones en este disco.****\x1B[0m\n");
                                    }
                                }
                                else if(strcmp(type,"e") == 0) //crear partición extendida
                                {
                                    /** REVISAR SI YA EXISTE UNA PARTICIÓN EXTENDIDA **/
                                    int banderaExtendida = -1;
                                    int indiceExtendida = -1;

                                    if(mbr.mbr_particion[0].part_type == 'e')
                                    {
                                        banderaExtendida = 0;
                                    }
                                    else if(mbr.mbr_particion[1].part_type == 'e')
                                    {
                                        banderaExtendida = 1;
                                    }
                                    else if(mbr.mbr_particion[2].part_type == 'e')
                                    {
                                        banderaExtendida = 2;
                                    }
                                    else if(mbr.mbr_particion[3].part_type == 'e')
                                    {
                                        banderaExtendida = 3;
                                    }

                                    if(banderaExtendida == -1) //no hay ninguna partición extendida por el momento
                                    {
                                        if((mbr.mbr_particion[0].part_status == 'n') || (mbr.mbr_particion[1].part_status == 'n')
                                        || (mbr.mbr_particion[2].part_status == 'n') || (mbr.mbr_particion[3].part_status == 'n'))
                                        {
                                            int indiceParticion = -1;
    /** nueva onda **/

                                            if((mbr.mbr_particion[0].part_status == 'n') && (mbr.mbr_particion[1].part_status == 'n')
                                            && (mbr.mbr_particion[2].part_status == 'n') && (mbr.mbr_particion[3].part_status == 'n'))
                                            {
                                                if((mbr.mbr_tamano - sizeof(mbr)) >= unidades) //cabe en el tamaño del archivo
                                                {
                                                    strcpy(mbr.mbr_particion[0].part_name, nameLimpio);
                                                    mbr.mbr_particion[0].part_start = sizeof(mbr);
                                                    mbr.mbr_particion[0].part_status = 'y';
                                                    mbr.mbr_particion[0].part_size = unidades;
                                                    mbr.mbr_particion[0].part_type = 'e';
                                                    mbr.mbr_particion[0].part_fit = fitPart;
                                                    indiceExtendida = 0;

                                                    printf("\n\x1B[33m****¡La partición extendida %s se ha creado con éxito!****\x1B[0m\n", name);
                                                }
                                                else
                                                {

                                                    printf("\n\x1B[33m****No queda espacio en el disco****\x1B[0m\n");
                                                }
                                            }
                                            else if((mbr.mbr_particion[0].part_start - sizeof(mbr)) >= unidades) //cabe entre el mbr y part0
                                            {
                                                strcpy(mbr.mbr_particion[3].part_name, mbr.mbr_particion[2].part_name);
                                                mbr.mbr_particion[3].part_start = mbr.mbr_particion[2].part_start;
                                                mbr.mbr_particion[3].part_status = mbr.mbr_particion[2].part_status;
                                                mbr.mbr_particion[3].part_size = mbr.mbr_particion[2].part_size;
                                                mbr.mbr_particion[3].part_type = mbr.mbr_particion[2].part_type;
                                                mbr.mbr_particion[3].part_fit = mbr.mbr_particion[2].part_fit;

                                                strcpy(mbr.mbr_particion[2].part_name, mbr.mbr_particion[1].part_name);
                                                mbr.mbr_particion[2].part_start = mbr.mbr_particion[1].part_start;
                                                mbr.mbr_particion[2].part_status = mbr.mbr_particion[1].part_status;
                                                mbr.mbr_particion[2].part_size = mbr.mbr_particion[1].part_size;
                                                mbr.mbr_particion[2].part_type = mbr.mbr_particion[1].part_type;
                                                mbr.mbr_particion[2].part_fit = mbr.mbr_particion[1].part_fit;

                                                strcpy(mbr.mbr_particion[1].part_name, mbr.mbr_particion[0].part_name);
                                                mbr.mbr_particion[1].part_start = mbr.mbr_particion[0].part_start;
                                                mbr.mbr_particion[1].part_status = mbr.mbr_particion[0].part_status;
                                                mbr.mbr_particion[1].part_size = mbr.mbr_particion[0].part_size;
                                                mbr.mbr_particion[1].part_type = mbr.mbr_particion[0].part_type;
                                                mbr.mbr_particion[1].part_fit = mbr.mbr_particion[0].part_fit;

                                                strcpy(mbr.mbr_particion[0].part_name, nameLimpio);
                                                mbr.mbr_particion[0].part_start = sizeof(mbr);
                                                mbr.mbr_particion[0].part_status = 'y';
                                                mbr.mbr_particion[0].part_size = unidades;
                                                mbr.mbr_particion[0].part_type = 'e';
                                                mbr.mbr_particion[0].part_fit = fitPart;
                                                indiceExtendida = 0;

                                                printf("\n\x1B[33m****¡La partición extendida %s se ha creado con éxito!****\x1B[0m\n", name);
                                            }
                                            else if(mbr.mbr_particion[1].part_status == 'n')
                                            {
                                                if((mbr.mbr_tamano - (mbr.mbr_particion[0].part_size + mbr.mbr_particion[0].part_start)) >= unidades) //cabe entre part 0 y el tamaño total
                                                {
                                                    strcpy(mbr.mbr_particion[1].part_name, nameLimpio);
                                                    mbr.mbr_particion[1].part_start = (mbr.mbr_particion[0].part_size + mbr.mbr_particion[0].part_start);
                                                    mbr.mbr_particion[1].part_status = 'y';
                                                    mbr.mbr_particion[1].part_size = unidades;
                                                    mbr.mbr_particion[1].part_type = 'e';
                                                    mbr.mbr_particion[1].part_fit = fitPart;
                                                    indiceExtendida = 1;

                                                    printf("\n\x1B[33m****¡La partición extendida %s se ha creado con éxito!****\x1B[0m\n", name);
                                                }
                                                else
                                                {

                                                    printf("\n\x1B[33m****No queda espacio en el disco****\x1B[0m\n");
                                                }
                                            }
                                            else if(mbr.mbr_particion[1].part_start - (mbr.mbr_particion[0].part_size + mbr.mbr_particion[0].part_start) >= unidades) //cabe entre el part0 y part1
                                            {
                                                strcpy(mbr.mbr_particion[3].part_name, mbr.mbr_particion[2].part_name);
                                                mbr.mbr_particion[3].part_start = mbr.mbr_particion[2].part_start;
                                                mbr.mbr_particion[3].part_status = mbr.mbr_particion[2].part_status;
                                                mbr.mbr_particion[3].part_size = mbr.mbr_particion[2].part_size;
                                                mbr.mbr_particion[3].part_type = mbr.mbr_particion[2].part_type;
                                                mbr.mbr_particion[3].part_fit = mbr.mbr_particion[2].part_fit;

                                                strcpy(mbr.mbr_particion[2].part_name, mbr.mbr_particion[1].part_name);
                                                mbr.mbr_particion[2].part_start = mbr.mbr_particion[1].part_start;
                                                mbr.mbr_particion[2].part_status = mbr.mbr_particion[1].part_status;
                                                mbr.mbr_particion[2].part_size = mbr.mbr_particion[1].part_size;
                                                mbr.mbr_particion[2].part_type = mbr.mbr_particion[1].part_type;
                                                mbr.mbr_particion[2].part_fit = mbr.mbr_particion[1].part_fit;

                                                strcpy(mbr.mbr_particion[1].part_name, nameLimpio);
                                                mbr.mbr_particion[1].part_start = (mbr.mbr_particion[0].part_size + mbr.mbr_particion[0].part_start);
                                                mbr.mbr_particion[1].part_status = 'y';
                                                mbr.mbr_particion[1].part_size = unidades;
                                                mbr.mbr_particion[1].part_type = 'e';
                                                mbr.mbr_particion[1].part_fit = fitPart;
                                                indiceExtendida = 1;

                                                printf("\n\x1B[33m****¡La partición extendida %s se ha creado con éxito!****\x1B[0m\n", name);
                                            }
                                            else if(mbr.mbr_particion[2].part_status == 'n')
                                            {
                                                if((mbr.mbr_tamano - (mbr.mbr_particion[1].part_size + mbr.mbr_particion[1].part_start)) >= unidades) //cabe entre part 1 y el tamaño total
                                                {
                                                    strcpy(mbr.mbr_particion[2].part_name, nameLimpio);
                                                    mbr.mbr_particion[2].part_start = (mbr.mbr_particion[1].part_size + mbr.mbr_particion[1].part_start);
                                                    mbr.mbr_particion[2].part_status = 'y';
                                                    mbr.mbr_particion[2].part_size = unidades;
                                                    mbr.mbr_particion[2].part_type = 'e';
                                                    mbr.mbr_particion[2].part_fit = fitPart;
                                                    indiceExtendida = 2;

                                                    printf("\n\x1B[33m****¡La partición extendida %s se ha creado con éxito!****\x1B[0m\n", name);
                                                }
                                                else
                                                {

                                                    printf("\n\x1B[33m****No queda espacio en el disco****\x1B[0m\n");
                                                }
                                            }
                                            else if(mbr.mbr_particion[2].part_start - (mbr.mbr_particion[1].part_size + mbr.mbr_particion[1].part_start) >= unidades) //cabe entre el part1 y part2
                                            {
                                                strcpy(mbr.mbr_particion[3].part_name, mbr.mbr_particion[2].part_name);
                                                mbr.mbr_particion[3].part_start = mbr.mbr_particion[2].part_start;
                                                mbr.mbr_particion[3].part_status = mbr.mbr_particion[2].part_status;
                                                mbr.mbr_particion[3].part_size = mbr.mbr_particion[2].part_size;
                                                mbr.mbr_particion[3].part_type = mbr.mbr_particion[2].part_type;
                                                mbr.mbr_particion[3].part_fit = mbr.mbr_particion[2].part_fit;

                                                strcpy(mbr.mbr_particion[2].part_name, nameLimpio);
                                                mbr.mbr_particion[2].part_start = (mbr.mbr_particion[1].part_size + mbr.mbr_particion[1].part_start);
                                                mbr.mbr_particion[2].part_status = 'y';
                                                mbr.mbr_particion[2].part_size = unidades;
                                                mbr.mbr_particion[2].part_type = 'e';
                                                mbr.mbr_particion[2].part_fit = fitPart;
                                                    indiceExtendida = 2;

                                                printf("\n\x1B[33m****¡La partición extendida %s se ha creado con éxito!****\x1B[0m\n", name);
                                            }
                                            else if(mbr.mbr_particion[3].part_status == 'n')
                                            {
                                                if((mbr.mbr_tamano - (mbr.mbr_particion[2].part_size + mbr.mbr_particion[2].part_start)) >= unidades) //cabe entre part 2 y el tamaño total
                                                {
                                                    strcpy(mbr.mbr_particion[3].part_name, nameLimpio);
                                                    mbr.mbr_particion[3].part_start = (mbr.mbr_particion[2].part_size + mbr.mbr_particion[2].part_start);
                                                    mbr.mbr_particion[3].part_status = 'y';
                                                    mbr.mbr_particion[3].part_size = unidades;
                                                    mbr.mbr_particion[3].part_type = 'e';
                                                    mbr.mbr_particion[3].part_fit = fitPart;
                                                    indiceExtendida = 3;

                                                    printf("\n\x1B[33m****¡La partición extendida %s se ha creado con éxito!****\x1B[0m\n", name);
                                                }
                                                else
                                                {

                                                    printf("\n\x1B[33m****No queda espacio en el disco****\x1B[0m\n");
                                                }
                                            }
                                            else
                                            {

                                                printf("\n\x1B[33m****No queda espacio en el disco****\x1B[0m\n");
                                            }

    /** nueva onda **/  /**POR ACÁ DEBERÍA GUARDAR EL EBR EN EL DISCO **/
                                            if(indiceExtendida != -1)
                                            {
                                                EBR ebr;
                                                ebr.part_status = 'n';
                                                ebr.part_next = -1;

                                                fseek(disco,mbr.mbr_particion[indiceExtendida].part_start,SEEK_SET);
                                                fwrite(&ebr,sizeof(ebr),1,disco);
                                            }
                                            else
                                            {
                                                printf("\n\x1B[31m****No se escribió el ebr.****\x1B[0m\n");
                                            }

                                        }
                                        else
                                        {
                                            printf("\n\x1B[33m****No se pueden crear más particiones en este disco.****\x1B[0m\n");
                                        }
                                    }
                                    else
                                    {
                                        printf("\n\x1B[33m****Solo puede existir 1 partición extendida.****\x1B[0m\n");
                                    }
                                }
                                else if(strcmp(type,"l") == 0) //crear partición logica
                                {
                                    /** REVISAR SI YA EXISTE UNA PARTICIÓN EXTENDIDA **/
                                    int banderaExtendida = -1;

                                    if(mbr.mbr_particion[0].part_type == 'e')
                                    {
                                        banderaExtendida = 0;
                                    }
                                    else if(mbr.mbr_particion[1].part_type == 'e')
                                    {
                                        banderaExtendida = 1;
                                    }
                                    else if(mbr.mbr_particion[2].part_type == 'e')
                                    {
                                        banderaExtendida = 2;
                                    }
                                    else if(mbr.mbr_particion[3].part_type == 'e')
                                    {
                                        banderaExtendida = 3;
                                    }

                                    if(banderaExtendida != -1) //significa que sí hay una partición extendida
                                    {
                                        /**Crear partición**/
                                    }
                                    else
                                    {
                                        printf("\n\x1B[33m****No se puede crear la partición lógica porque no existe una partición extendida****\x1B[0m\n");
                                    }
                                }
                            }
                            else
                            {
                                printf("\n\x1B[33m****El tamaño mínimo de una partición debe ser de 2MB****\x1B[0m\n");
                            }
                        }
                        else if((strcmp(tdelete,"") != 0) && (strcmp(add,"") == 0)) //significa que se quiere borrar una partición
                        {
                            if((strcmp(tdelete,"fast") == 0) || (strcmp(tdelete,"full") == 0))
                            {
                                printf("\x1B[31m¿Quieres eliminar todo el contenido de la partición? [S/n]\x1B[0m\n");
                                char nuevaLinea[256];
                                scanf(" %[^\n]", nuevaLinea);
                                aMinuscula(nuevaLinea);

                                if(strcmp(nuevaLinea,"s") == 0)
                                {
                                    /*** esto fue lo que toqué :v **/

                                    char* idTemporal = malloc(strlen("solo quiero ocupar espacio :v") + 100);
                                    memset(idTemporal,'\0',strlen(idTemporal));
                                    strcpy(idTemporal, "");

                                    retornarIdParticion(idTemporal,pathLimpio,nameLimpio);
                                    ejecutarUNMOUNT(idTemporal);

                                    char caracterNulo [1];

                                    /** aquí terminé **/
                                    if(strcmp(mbr.mbr_particion[0].part_name,nameLimpio) == 0) //quiero eliminar la part0
                                    {
                                        if(mbr.mbr_particion[0].part_type == 'p')
                                        {

                                            if(strcmp(tdelete,"full") == 0)
                                            {
                                                fseek(disco,mbr.mbr_particion[0].part_start,SEEK_SET);

                                                int i = 0;
                                                for(i = mbr.mbr_particion[0].part_start; i < mbr.mbr_particion[0].part_size; i++)
                                                {
                                                    fwrite (caracterNulo, sizeof(caracterNulo), 1, disco);
                                                }
                                            }

                                            strcpy(mbr.mbr_particion[0].part_name, mbr.mbr_particion[1].part_name);
                                            mbr.mbr_particion[0].part_start = mbr.mbr_particion[1].part_start;
                                            mbr.mbr_particion[0].part_status = mbr.mbr_particion[1].part_status;
                                            mbr.mbr_particion[0].part_size = mbr.mbr_particion[1].part_size;
                                            mbr.mbr_particion[0].part_type = mbr.mbr_particion[1].part_type;
                                            mbr.mbr_particion[0].part_fit = mbr.mbr_particion[1].part_fit;

                                            strcpy(mbr.mbr_particion[1].part_name, mbr.mbr_particion[2].part_name);
                                            mbr.mbr_particion[1].part_start = mbr.mbr_particion[2].part_start;
                                            mbr.mbr_particion[1].part_status = mbr.mbr_particion[2].part_status;
                                            mbr.mbr_particion[1].part_size = mbr.mbr_particion[2].part_size;
                                            mbr.mbr_particion[1].part_type = mbr.mbr_particion[2].part_type;
                                            mbr.mbr_particion[1].part_fit = mbr.mbr_particion[2].part_fit;

                                            strcpy(mbr.mbr_particion[2].part_name, mbr.mbr_particion[3].part_name);
                                            mbr.mbr_particion[2].part_start = mbr.mbr_particion[3].part_start;
                                            mbr.mbr_particion[2].part_status = mbr.mbr_particion[3].part_status;
                                            mbr.mbr_particion[2].part_size = mbr.mbr_particion[3].part_size;
                                            mbr.mbr_particion[2].part_type = mbr.mbr_particion[3].part_type;
                                            mbr.mbr_particion[2].part_fit = mbr.mbr_particion[3].part_fit;

                                            strcpy(mbr.mbr_particion[3].part_name, "");
                                            mbr.mbr_particion[3].part_start = 0;
                                            mbr.mbr_particion[3].part_status = 'n';
                                            mbr.mbr_particion[3].part_size = 0;
                                            mbr.mbr_particion[3].part_type = '\0';
                                            mbr.mbr_particion[3].part_fit = 'w';

                                            printf("\n\x1B[33m****La partición se ha eliminado exitosamente.****\x1B[0m\n");
                                        }
                                        else if(mbr.mbr_particion[0].part_type == 'e')
                                        {

                                            if(strcmp(tdelete,"full") == 0)
                                            {
                                                fseek(disco,mbr.mbr_particion[0].part_start,SEEK_SET);

                                                int i = 0;
                                                for(i = mbr.mbr_particion[0].part_start; i < mbr.mbr_particion[0].part_size; i++)
                                                {
                                                    fwrite (caracterNulo, sizeof(caracterNulo), 1, disco);
                                                }
                                            }
                                            /** y se deberían borrar las particiones logicas... DEBERÍAN.**/
                                            strcpy(mbr.mbr_particion[0].part_name, mbr.mbr_particion[1].part_name);
                                            mbr.mbr_particion[0].part_start = mbr.mbr_particion[1].part_start;
                                            mbr.mbr_particion[0].part_status = mbr.mbr_particion[1].part_status;
                                            mbr.mbr_particion[0].part_size = mbr.mbr_particion[1].part_size;
                                            mbr.mbr_particion[0].part_type = mbr.mbr_particion[1].part_type;
                                            mbr.mbr_particion[0].part_fit = mbr.mbr_particion[1].part_fit;

                                            strcpy(mbr.mbr_particion[1].part_name, mbr.mbr_particion[2].part_name);
                                            mbr.mbr_particion[1].part_start = mbr.mbr_particion[2].part_start;
                                            mbr.mbr_particion[1].part_status = mbr.mbr_particion[2].part_status;
                                            mbr.mbr_particion[1].part_size = mbr.mbr_particion[2].part_size;
                                            mbr.mbr_particion[1].part_type = mbr.mbr_particion[2].part_type;
                                            mbr.mbr_particion[1].part_fit = mbr.mbr_particion[2].part_fit;

                                            strcpy(mbr.mbr_particion[2].part_name, mbr.mbr_particion[3].part_name);
                                            mbr.mbr_particion[2].part_start = mbr.mbr_particion[3].part_start;
                                            mbr.mbr_particion[2].part_status = mbr.mbr_particion[3].part_status;
                                            mbr.mbr_particion[2].part_size = mbr.mbr_particion[3].part_size;
                                            mbr.mbr_particion[2].part_type = mbr.mbr_particion[3].part_type;
                                            mbr.mbr_particion[2].part_fit = mbr.mbr_particion[3].part_fit;

                                            strcpy(mbr.mbr_particion[3].part_name, "");
                                            mbr.mbr_particion[3].part_start = 0;
                                            mbr.mbr_particion[3].part_status = 'n';
                                            mbr.mbr_particion[3].part_size = 0;
                                            mbr.mbr_particion[3].part_type = '\0';
                                            mbr.mbr_particion[3].part_fit = 'w';

                                            printf("\n\x1B[33m****La partición se ha eliminado exitosamente.****\x1B[0m\n");
                                        }
                                        else if(mbr.mbr_particion[0].part_type == 'l')
                                        {

                                        }
                                    }
                                    else if(strcmp(mbr.mbr_particion[1].part_name,nameLimpio) == 0) //quiero eliminar la part1
                                    {
                                        if(mbr.mbr_particion[1].part_type == 'p')
                                        {

                                            if(strcmp(tdelete,"full") == 0)
                                            {
                                                fseek(disco,mbr.mbr_particion[1].part_start,SEEK_SET);

                                                int i = 0;
                                                for(i = mbr.mbr_particion[1].part_start; i < mbr.mbr_particion[1].part_size; i++)
                                                {
                                                    fwrite (caracterNulo, sizeof(caracterNulo), 1, disco);
                                                }
                                            }

                                            strcpy(mbr.mbr_particion[1].part_name, mbr.mbr_particion[2].part_name);
                                            mbr.mbr_particion[1].part_start = mbr.mbr_particion[2].part_start;
                                            mbr.mbr_particion[1].part_status = mbr.mbr_particion[2].part_status;
                                            mbr.mbr_particion[1].part_size = mbr.mbr_particion[2].part_size;
                                            mbr.mbr_particion[1].part_type = mbr.mbr_particion[2].part_type;
                                            mbr.mbr_particion[1].part_fit = mbr.mbr_particion[2].part_fit;

                                            strcpy(mbr.mbr_particion[2].part_name, mbr.mbr_particion[3].part_name);
                                            mbr.mbr_particion[2].part_start = mbr.mbr_particion[3].part_start;
                                            mbr.mbr_particion[2].part_status = mbr.mbr_particion[3].part_status;
                                            mbr.mbr_particion[2].part_size = mbr.mbr_particion[3].part_size;
                                            mbr.mbr_particion[2].part_type = mbr.mbr_particion[3].part_type;
                                            mbr.mbr_particion[2].part_fit = mbr.mbr_particion[3].part_fit;

                                            strcpy(mbr.mbr_particion[3].part_name, "");
                                            mbr.mbr_particion[3].part_start = 0;
                                            mbr.mbr_particion[3].part_status = 'n';
                                            mbr.mbr_particion[3].part_size = 0;
                                            mbr.mbr_particion[3].part_type = '\0';
                                            mbr.mbr_particion[3].part_fit = 'w';

                                            printf("\n\x1B[33m****La partición se ha eliminado exitosamente.****\x1B[0m\n");
                                        }
                                        else if(mbr.mbr_particion[1].part_type == 'e')
                                        {

                                            if(strcmp(tdelete,"full") == 0)
                                            {
                                                fseek(disco,mbr.mbr_particion[1].part_start,SEEK_SET);

                                                int i = 0;
                                                for(i = mbr.mbr_particion[1].part_start; i < mbr.mbr_particion[1].part_size; i++)
                                                {
                                                    fwrite (caracterNulo, sizeof(caracterNulo), 1, disco);
                                                }
                                            }

                                            strcpy(mbr.mbr_particion[1].part_name, mbr.mbr_particion[2].part_name);
                                            mbr.mbr_particion[1].part_start = mbr.mbr_particion[2].part_start;
                                            mbr.mbr_particion[1].part_status = mbr.mbr_particion[2].part_status;
                                            mbr.mbr_particion[1].part_size = mbr.mbr_particion[2].part_size;
                                            mbr.mbr_particion[1].part_type = mbr.mbr_particion[2].part_type;
                                            mbr.mbr_particion[1].part_fit = mbr.mbr_particion[2].part_fit;

                                            strcpy(mbr.mbr_particion[2].part_name, mbr.mbr_particion[3].part_name);
                                            mbr.mbr_particion[2].part_start = mbr.mbr_particion[3].part_start;
                                            mbr.mbr_particion[2].part_status = mbr.mbr_particion[3].part_status;
                                            mbr.mbr_particion[2].part_size = mbr.mbr_particion[3].part_size;
                                            mbr.mbr_particion[2].part_type = mbr.mbr_particion[3].part_type;
                                            mbr.mbr_particion[2].part_fit = mbr.mbr_particion[3].part_fit;

                                            strcpy(mbr.mbr_particion[3].part_name, "");
                                            mbr.mbr_particion[3].part_start = 0;
                                            mbr.mbr_particion[3].part_status = 'n';
                                            mbr.mbr_particion[3].part_size = 0;
                                            mbr.mbr_particion[3].part_type = '\0';
                                            mbr.mbr_particion[3].part_fit = 'w';

                                            printf("\n\x1B[33m****La partición se ha eliminado exitosamente.****\x1B[0m\n");
                                        }
                                        else if(mbr.mbr_particion[1].part_type == 'l')
                                        {

                                        }
                                    }
                                    else if(strcmp(mbr.mbr_particion[2].part_name,nameLimpio) == 0) //quiero eliminar la part2
                                    {
                                        if(mbr.mbr_particion[2].part_type == 'p')
                                        {

                                            if(strcmp(tdelete,"full") == 0)
                                            {
                                                fseek(disco,mbr.mbr_particion[2].part_start,SEEK_SET);

                                                int i = 0;
                                                for(i = mbr.mbr_particion[2].part_start; i < mbr.mbr_particion[2].part_size; i++)
                                                {
                                                    fwrite (caracterNulo, sizeof(caracterNulo), 1, disco);
                                                }
                                            }

                                            strcpy(mbr.mbr_particion[2].part_name, mbr.mbr_particion[3].part_name);
                                            mbr.mbr_particion[2].part_start = mbr.mbr_particion[3].part_start;
                                            mbr.mbr_particion[2].part_status = mbr.mbr_particion[3].part_status;
                                            mbr.mbr_particion[2].part_size = mbr.mbr_particion[3].part_size;
                                            mbr.mbr_particion[2].part_type = mbr.mbr_particion[3].part_type;
                                            mbr.mbr_particion[2].part_fit = mbr.mbr_particion[3].part_fit;

                                            strcpy(mbr.mbr_particion[3].part_name, "");
                                            mbr.mbr_particion[3].part_start = 0;
                                            mbr.mbr_particion[3].part_status = 'n';
                                            mbr.mbr_particion[3].part_size = 0;
                                            mbr.mbr_particion[3].part_type = '\0';
                                            mbr.mbr_particion[3].part_fit = 'w';

                                            printf("\n\x1B[33m****La partición se ha eliminado exitosamente.****\x1B[0m\n");
                                        }
                                        else if(mbr.mbr_particion[2].part_type == 'e')
                                        {

                                            if(strcmp(tdelete,"full") == 0)
                                            {
                                                fseek(disco,mbr.mbr_particion[2].part_start,SEEK_SET);

                                                int i = 0;
                                                for(i = mbr.mbr_particion[2].part_start; i < mbr.mbr_particion[2].part_size; i++)
                                                {
                                                    fwrite (caracterNulo, sizeof(caracterNulo), 1, disco);
                                                }
                                            }

                                            strcpy(mbr.mbr_particion[2].part_name, mbr.mbr_particion[3].part_name);
                                            mbr.mbr_particion[2].part_start = mbr.mbr_particion[3].part_start;
                                            mbr.mbr_particion[2].part_status = mbr.mbr_particion[3].part_status;
                                            mbr.mbr_particion[2].part_size = mbr.mbr_particion[3].part_size;
                                            mbr.mbr_particion[2].part_type = mbr.mbr_particion[3].part_type;
                                            mbr.mbr_particion[2].part_fit = mbr.mbr_particion[3].part_fit;

                                            strcpy(mbr.mbr_particion[3].part_name, "");
                                            mbr.mbr_particion[3].part_start = 0;
                                            mbr.mbr_particion[3].part_status = 'n';
                                            mbr.mbr_particion[3].part_size = 0;
                                            mbr.mbr_particion[3].part_type = '\0';
                                            mbr.mbr_particion[3].part_fit = 'w';

                                            printf("\n\x1B[33m****La partición se ha eliminado exitosamente.****\x1B[0m\n");
                                        }
                                        else if(mbr.mbr_particion[2].part_type == 'l')
                                        {

                                        }
                                    }
                                    else if(strcmp(mbr.mbr_particion[3].part_name,nameLimpio) == 0) //quiero eliminar la part3
                                    {
                                        if(mbr.mbr_particion[3].part_type == 'p')
                                        {

                                            if(strcmp(tdelete,"full") == 0)
                                            {
                                                fseek(disco,mbr.mbr_particion[3].part_start,SEEK_SET);

                                                int i = 0;
                                                for(i = mbr.mbr_particion[3].part_start; i < mbr.mbr_particion[3].part_size; i++)
                                                {
                                                    fwrite (caracterNulo, sizeof(caracterNulo), 1, disco);
                                                }
                                            }

                                            strcpy(mbr.mbr_particion[3].part_name, "");
                                            mbr.mbr_particion[3].part_start = 0;
                                            mbr.mbr_particion[3].part_status = 'n';
                                            mbr.mbr_particion[3].part_size = 0;
                                            mbr.mbr_particion[3].part_type = '\0';
                                            mbr.mbr_particion[3].part_fit = 'w';

                                            printf("\n\x1B[33m****La partición se ha eliminado exitosamente.****\x1B[0m\n");
                                        }
                                        else if(mbr.mbr_particion[3].part_type == 'e')
                                        {

                                            if(strcmp(tdelete,"full") == 0)
                                            {
                                                fseek(disco,mbr.mbr_particion[3].part_start,SEEK_SET);

                                                int i = 0;
                                                for(i = mbr.mbr_particion[3].part_start; i < mbr.mbr_particion[3].part_size; i++)
                                                {
                                                    fwrite (caracterNulo, sizeof(caracterNulo), 1, disco);
                                                }
                                            }

                                            strcpy(mbr.mbr_particion[3].part_name, "");
                                            mbr.mbr_particion[3].part_start = 0;
                                            mbr.mbr_particion[3].part_status = 'n';
                                            mbr.mbr_particion[3].part_size = 0;
                                            mbr.mbr_particion[3].part_type = '\0';
                                            mbr.mbr_particion[3].part_fit = 'w';

                                            printf("\n\x1B[33m****La partición se ha eliminado exitosamente.****\x1B[0m\n");
                                        }
                                        else if(mbr.mbr_particion[3].part_type == 'l')
                                        {

                                        }
                                    }
                                    else
                                    {
                                        printf("\n\x1B[33m****La partición que desas eliminar no existe.****\x1B[0m\n");
                                    }
                                }

                            }
                            else
                            {
                                printf("\n\x1B[33m****El parámetro +delete debe ser \"Fast\" o \"Full\"****\x1B[0m\n");
                            }
                        }
                        else if((strcmp(tdelete,"") == 0) && (strcmp(add,"") != 0)) //significa que se quiere agregar/quitar tamaño
                        {
                            if(strcmp(mbr.mbr_particion[0].part_name, nameLimpio) == 0)
                            {
                                if(mbr.mbr_particion[1].part_status == 'n') //quiere decir que solo hay 1 partición
                                {
                                    if((mbr.mbr_tamano - (mbr.mbr_particion[0].part_size + mbr.mbr_particion[0].part_start)) >= unidadesExtras) //cabe entre part 0 y el tamaño total
                                    {
                                        if((mbr.mbr_particion[0].part_size + unidadesExtras) >= 2048) // sigue siendo mayor que 3MB
                                        {
                                            if(mbr.mbr_particion[0].part_type == 'p')
                                            {
                                                mbr.mbr_particion[0].part_size = mbr.mbr_particion[0].part_size + unidadesExtras;
                                                printf("\n\x1B[33m****¡La partición se ha modificado con éxito!****\x1B[0m\n");
                                            }
                                            else if(mbr.mbr_particion[0].part_type == 'e')
                                            {
                                                mbr.mbr_particion[0].part_size = mbr.mbr_particion[0].part_size + unidadesExtras;
                                                printf("\n\x1B[33m****¡La partición se ha modificado con éxito!****\x1B[0m\n");
                                            }
                                            else if(mbr.mbr_particion[0].part_type == 'l')
                                            {

                                            }
                                        }
                                        else
                                        {
                                            printf("\n\x1B[33m****No se ha podido modificar la partición, el tamaño de la partición debe ser mayor a 2MB.****\x1B[0m\n");
                                        }
                                    }
                                    else
                                    {
                                        printf("\n\x1B[33m****No se ha podido modificar la partición, no hay espacio suficiente.****\x1B[0m\n");
                                    }
                                }
                                else
                                {
                                    if((mbr.mbr_particion[1].part_start - (mbr.mbr_particion[0].part_size + mbr.mbr_particion[0].part_start)) >= unidadesExtras) //cabe entre el part0 y part1
                                    {
                                        if((mbr.mbr_particion[0].part_size + unidadesExtras) >= 2048) // sigue siendo mayor que 3MB
                                        {
                                            if(mbr.mbr_particion[0].part_type == 'p')
                                            {
                                                mbr.mbr_particion[0].part_size = mbr.mbr_particion[0].part_size + unidadesExtras;
                                                printf("\n\x1B[33m****¡La partición se ha modificado con éxito!****\x1B[0m\n");
                                            }
                                            else if(mbr.mbr_particion[0].part_type == 'e')
                                            {
                                                mbr.mbr_particion[0].part_size = mbr.mbr_particion[0].part_size + unidadesExtras;
                                                printf("\n\x1B[33m****¡La partición se ha modificado con éxito!****\x1B[0m\n");
                                            }
                                            else if(mbr.mbr_particion[0].part_type == 'l')
                                            {

                                            }
                                        }
                                        else
                                        {
                                            printf("\n\x1B[33m****No se ha podido modificar la partición, el tamaño de la partición debe ser mayor a 2MB.****\x1B[0m\n");
                                        }
                                    }
                                    else
                                    {
                                        printf("\n\x1B[33m****No se ha podido modificar la partición, no hay espacio suficiente.****\x1B[0m\n");
                                    }
                                }
                            }
                            else if(strcmp(mbr.mbr_particion[1].part_name, nameLimpio) == 0)
                            {
                                if(mbr.mbr_particion[2].part_status == 'n') //quiere decir que solo hay 1 partición
                                {
                                    if((mbr.mbr_tamano - (mbr.mbr_particion[1].part_size + mbr.mbr_particion[1].part_start)) >= unidadesExtras) //cabe entre part 0 y el tamaño total
                                    {
                                        if((mbr.mbr_particion[1].part_size + unidadesExtras) >= 2048) // sigue siendo mayor que 3MB
                                        {
                                            if(mbr.mbr_particion[1].part_type == 'p')
                                            {
                                                mbr.mbr_particion[1].part_size = mbr.mbr_particion[1].part_size + unidadesExtras;
                                                printf("\n\x1B[33m****¡La partición se ha modificado con éxito!****\x1B[0m\n");
                                            }
                                            else if(mbr.mbr_particion[1].part_type == 'e')
                                            {
                                                mbr.mbr_particion[1].part_size = mbr.mbr_particion[1].part_size + unidadesExtras;
                                                printf("\n\x1B[33m****¡La partición se ha modificado con éxito!****\x1B[0m\n");
                                            }
                                            else if(mbr.mbr_particion[1].part_type == 'l')
                                            {

                                            }
                                        }
                                        else
                                        {
                                            printf("\n\x1B[33m****No se ha podido modificar la partición, el tamaño de la partición debe ser mayor a 2MB.****\x1B[0m\n");
                                        }
                                    }
                                    else
                                    {
                                        printf("\n\x1B[33m****No se ha podido modificar la partición, no hay espacio suficiente.****\x1B[0m\n");
                                    }
                                }
                                else
                                {
                                    if((mbr.mbr_particion[2].part_start - (mbr.mbr_particion[1].part_size + mbr.mbr_particion[1].part_start)) >= unidadesExtras) //cabe entre el part0 y part1
                                    {
                                        if((mbr.mbr_particion[1].part_size + unidadesExtras) >= 2048) // sigue siendo mayor que 3MB
                                        {
                                            if(mbr.mbr_particion[1].part_type == 'p')
                                            {
                                                mbr.mbr_particion[1].part_size = mbr.mbr_particion[1].part_size + unidadesExtras;
                                                printf("\n\x1B[33m****¡La partición se ha modificado con éxito!****\x1B[0m\n");
                                            }
                                            else if(mbr.mbr_particion[1].part_type == 'e')
                                            {
                                                mbr.mbr_particion[1].part_size = mbr.mbr_particion[1].part_size + unidadesExtras;
                                                printf("\n\x1B[33m****¡La partición se ha modificado con éxito!****\x1B[0m\n");
                                            }
                                            else if(mbr.mbr_particion[1].part_type == 'l')
                                            {

                                            }
                                        }
                                        else
                                        {
                                            printf("\n\x1B[33m****No se ha podido modificar la partición, el tamaño de la partición debe ser mayor a 2MB.****\x1B[0m\n");
                                        }
                                    }
                                    else
                                    {
                                        printf("\n\x1B[33m****No se ha podido modificar la partición, no hay espacio suficiente.****\x1B[0m\n");
                                    }
                                }
                            }
                            else if(strcmp(mbr.mbr_particion[2].part_name, nameLimpio) == 0)
                            {
                                if(mbr.mbr_particion[3].part_status == 'n') //quiere decir que solo hay 1 partición
                                {
                                    if((mbr.mbr_tamano - (mbr.mbr_particion[2].part_size + mbr.mbr_particion[2].part_start)) >= unidadesExtras) //cabe entre part 0 y el tamaño total
                                    {
                                        if((mbr.mbr_particion[2].part_size + unidadesExtras) >= 2048) // sigue siendo mayor que 3MB
                                        {
                                            if(mbr.mbr_particion[2].part_type == 'p')
                                            {
                                                mbr.mbr_particion[2].part_size = mbr.mbr_particion[2].part_size + unidadesExtras;
                                                printf("\n\x1B[33m****¡La partición se ha modificado con éxito!****\x1B[0m\n");
                                            }
                                            else if(mbr.mbr_particion[2].part_type == 'e')
                                            {
                                                mbr.mbr_particion[2].part_size = mbr.mbr_particion[2].part_size + unidadesExtras;
                                                printf("\n\x1B[33m****¡La partición se ha modificado con éxito!****\x1B[0m\n");
                                            }
                                            else if(mbr.mbr_particion[2].part_type == 'l')
                                            {

                                            }
                                        }
                                        else
                                        {
                                            printf("\n\x1B[33m****No se ha podido modificar la partición, el tamaño de la partición debe ser mayor a 2MB.****\x1B[0m\n");
                                        }
                                    }
                                    else
                                    {
                                        printf("\n\x1B[33m****No se ha podido modificar la partición, no hay espacio suficiente.****\x1B[0m\n");
                                    }
                                }
                                else
                                {
                                    if((mbr.mbr_particion[3].part_start - (mbr.mbr_particion[2].part_size + mbr.mbr_particion[2].part_start)) >= unidadesExtras) //cabe entre el part0 y part1
                                    {
                                        if((mbr.mbr_particion[2].part_size + unidadesExtras) >= 2048) // sigue siendo mayor que 3MB
                                        {
                                            if(mbr.mbr_particion[2].part_type == 'p')
                                            {
                                                mbr.mbr_particion[2].part_size = mbr.mbr_particion[2].part_size + unidadesExtras;
                                                printf("\n\x1B[33m****¡La partición se ha modificado con éxito!****\x1B[0m\n");
                                            }
                                            else if(mbr.mbr_particion[2].part_type == 'e')
                                            {
                                                mbr.mbr_particion[2].part_size = mbr.mbr_particion[2].part_size + unidadesExtras;
                                                printf("\n\x1B[33m****¡La partición se ha modificado con éxito!****\x1B[0m\n");
                                            }
                                            else if(mbr.mbr_particion[2].part_type == 'l')
                                            {

                                            }
                                        }
                                        else
                                        {
                                            printf("\n\x1B[33m****No se ha podido modificar la partición, el tamaño de la partición debe ser mayor a 2MB.****\x1B[0m\n");
                                        }
                                    }
                                    else
                                    {
                                        printf("\n\x1B[33m****No se ha podido modificar la partición, no hay espacio suficiente.****\x1B[0m\n");
                                    }
                                }
                            }
                            else if(strcmp(mbr.mbr_particion[3].part_name, nameLimpio) == 0)
                            {
                                if((mbr.mbr_tamano - (mbr.mbr_particion[3].part_size + mbr.mbr_particion[3].part_start)) >= unidadesExtras) //cabe entre part 0 y el tamaño total
                                {
                                    if((mbr.mbr_particion[3].part_size + unidadesExtras) >= 2048) // sigue siendo mayor que 3MB
                                    {
                                        if(mbr.mbr_particion[3].part_type == 'p')
                                        {
                                            mbr.mbr_particion[3].part_size = mbr.mbr_particion[3].part_size + unidadesExtras;
                                            printf("\n\x1B[33m****¡La partición se ha modificado con éxito!****\x1B[0m\n");
                                        }
                                        else if(mbr.mbr_particion[3].part_type == 'e')
                                        {
                                            mbr.mbr_particion[3].part_size = mbr.mbr_particion[3].part_size + unidadesExtras;
                                            printf("\n\x1B[33m****¡La partición se ha modificado con éxito!****\x1B[0m\n");
                                        }
                                        else if(mbr.mbr_particion[3].part_type == 'l')
                                        {

                                        }
                                    }
                                    else
                                    {
                                        printf("\n\x1B[33m****No se ha podido modificar la partición, el tamaño de la partición debe ser mayor a 2MB.****\x1B[0m\n");
                                    }
                                }
                                else
                                {
                                    printf("\n\x1B[33m****No se ha podido modificar la partición, no hay espacio suficiente.****\x1B[0m\n");
                                }
                            }
                            else
                            {
                                printf("\n\x1B[33m****La partición que desas modificar no existe.****\x1B[0m\n");
                            }
                        }

                        fseek(disco,0,SEEK_SET);
                        fwrite(&mbr,sizeof(mbr),1,disco);
                        fclose(disco);

                    }
                    else
                    {
                        printf("\n\x1B[33m****El parámetro +type debe ser \"BF\", \"FF\" o \"WF\"****\x1B[0m\n");
                    }
                }
                else
                {
                    printf("\n\x1B[33m****El parámetro +type debe ser \"P\", \"E\" o \"L\"****\x1B[0m\n");
                }
            }
            else
            {
                printf("\n\x1B[33m****El parámetro +unit debe ser \"B\", \"K\" o \"M\"****\x1B[0m\n");
            }
        }
        else
        {
            printf("\n\x1B[33m****El disco que deseas modificar no existe. Verifica la ruta.****\x1B[0m\n");
        }


    }
    else
    {
        printf("\n\x1B[33m***Verifica que hayas incluido todos los parámetros obligatorios para el comando fdisk***\n");
        printf("-size\n");
        printf("-path\n");
        printf("-name\x1B[0m\n\n");
    }
}

//imprime la lista de particiones montadas
void mostrarParticionesMontadas()
{
    int disco = 0;
    int particion = 1;
    int banderaVacio = 0;

    for(disco = 0; disco < 50; disco++)
    {
        if(strcmp(particionesMontadas[disco][0], "") != 0)
        {
            for(particion = 1; particion < 50; particion++)
            {
                if(strcmp(particionesMontadas[disco][particion], "") != 0)
                {
                    banderaVacio = 1;
                    printf("\x1B[32m# \x1B[34mid\x1B[32m::\x1B[35mvd%c%d \x1B[34m-path\x1B[32m::\x1B[35m\"%s\" \x1B[34m-name\x1B[32m::\x1B[35m\"%s\"\x1B[0m\n", identificadores[disco], particion, particionesMontadas[disco][0],particionesMontadas[disco][particion]);
                }
            }
        }
    }

    if(banderaVacio != 0) //sí habían particiones montadas
    {
        printf("\n");
    }
    else
    {
        printf("\n\x1B[33m****No hay particiones montadas.****\x1B[0m\n");
    }
}

//asigna identificadores a las particiones montadas
void asignarIdentificador(char *id, char *pathLimpio, char *nameLimpio)
{
    int disco = 0;
    int particion = 1;
    int iterador = 1;
    int bandera = 0;
    char* aux = malloc(strlen("solo quiero ocupar espacio :v") + 100);

    while(disco < 50) //almacena hasta el índice 49 (50 discos)
    {
        if((strcmp(particionesMontadas[disco][0] ,pathLimpio)==0)||(strcmp(particionesMontadas[disco][0] ,"")==0)){
            strcpy(particionesMontadas[disco][0],pathLimpio);

            while ((strcmp(particionesMontadas[disco][particion] ,"")!=0)&&(strcmp(particionesMontadas[disco][particion] ,nameLimpio)!=0)){
                particion++;
            }

            while (iterador < 50){
                if(strcmp(particionesMontadas[disco][iterador] ,nameLimpio) == 0)
                {
                    bandera = 1;
                }
                iterador++;
            }

            if(bandera != 0)
            {
                printf("\n\x1B[31m****Esta partición ya fue montada previamente.****\x1B[0m\n");
                break;
            }
            else
            {
                strcpy(particionesMontadas[disco][particion] ,nameLimpio);
                sprintf(aux, "vd%c%d",identificadores[disco], particion);
                strcpy(id, aux);
                printf("\n\x1B[33m****¡La partición se montó exitosamente! El id de la partición \"%s\" es: vd%c%d.****\x1B[0m\n", nameLimpio,identificadores[disco], particion);
                break;
            }

//            strcpy(particionesMontadas[disco][particion] ,nameLimpio);
//            sprintf(aux, "vd%c%d",identificadores[disco], particion);
//            strcpy(id, aux);
//            break;
        }
        disco++;
    }
}

//ejecuta el comando "mount"
void ejecutarMOUNT(char* path, char* name)
{

    char* nameLimpio = malloc(strlen("solo quiero ocupar espacio :v") + 100);
    strncpy(nameLimpio,name+1,strlen(name)-2); //-2 porque toma en cuenta las 2 comillas

    char* pathLimpio = malloc(strlen("solo quiero ocupar espacio :v") + 100);
    strncpy(pathLimpio,path+1,strlen(path)-2); //-2 porque toma en cuenta las 2 comillas

    FILE * disco = fopen(pathLimpio, "r+b");

    if(disco != NULL) //EL ARCHIVO SÍ EXISTE
    {
        char* id = malloc(strlen("solo quiero ocupar espacio :v") + 100);
        strcpy(id,"vd"); //el char* id ya tiene "vd" para después agregarle el identificador de disco y partición

        MBR mbr; //LECTURA DEL MBR DEL DISCO Y ALMACENARLO EN RAM
        fread (&mbr, sizeof(mbr), 1,disco);
        fclose(disco);

        int indiceParticion = -1;

        if(strcmp(mbr.mbr_particion[0].part_name, nameLimpio) == 0)
        {
            indiceParticion = 0;
        }
        else if(strcmp(mbr.mbr_particion[1].part_name, nameLimpio) == 0)
        {
            indiceParticion = 1;
        }
        else if(strcmp(mbr.mbr_particion[2].part_name, nameLimpio) == 0)
        {
            indiceParticion = 2;
        }
        else if(strcmp(mbr.mbr_particion[3].part_name, nameLimpio) == 0)
        {
            indiceParticion = 3;
        }
        else
        {
            /** SI EL NOMBRE NO ES DE UNA DE LAS PARTICIONES PRIMARIAS O EXTENDIDAS
                ENTONCES ES DE UNA DE LAS PARTICIONES LÓGICAS. AQUÍ DEBERÍA IR A BUSCAR
                SI EXISTE UNA PARTICIÓN EXTENDIDA, SINO EXISTE ES ERROR (-1). LUEGO ENCONTRAR EL
                EBR, IR COMPARANDO LOS NOMBRES DE LAS PARTICIONES LÓGICAS, Y SINO EXISTE
                ES ERROR (-1)**/
                printf("\n\x1B[31m****Me quedé trabado en el else de la extendida****\x1B[0m\n");
        }

        if(indiceParticion != -1) //sí encontró el nombre
        {
            asignarIdentificador(id, pathLimpio, nameLimpio);
            //el mensaje de montado existoso está en el método
        }
        else
        {
            printf("\n\x1B[33m****La partición que deseas montar no existe. Verifica el nombre.****\x1B[0m\n");
        }

    }
    else
    {
        printf("\n\x1B[33m****El disco que deseas montar no existe. Verifica la ruta.****\x1B[0m\n");
    }
}

//ejecuta el comando "unmount"
void ejecutarUNMOUNT(char* id)
{
    char *idDisco = malloc(strlen("solo quiero ocupar espacio :v") + 1);
    strncpy(idDisco,id+2,1);
    char *idParticion = malloc(strlen("solo quiero ocupar espacio :v") + 1);
    strncpy(idParticion,id+3,1);

    int disco = 0;
    int particion = 0;
    char *valoresLetras = "abcdefghijklmnopqrstuvwxyz";

    particion = atof(idParticion);

    char* punteroLetra = strchr(valoresLetras,*idDisco);
    disco = punteroLetra - valoresLetras;

    if(strcmp(particionesMontadas[disco][particion],"") != 0)
    {
        strcpy(particionesMontadas[disco][particion],""); //se desmonta la partición

        int iterador = 1;
        int banderaColumnaVacia = 0;

        while(iterador < 50)
        {
            if(strcmp(particionesMontadas[disco][iterador],"") != 0) //verifica que la columna del disco todavía tenga particiones montadas
            {
                banderaColumnaVacia = 1;
                break;
            }
            iterador++;
        }

        if(banderaColumnaVacia == 0) //ya no hay particiones
        {
            strcpy(particionesMontadas[disco][0],"");
        }
        printf("\n\x1B[33m****Se ha desmontado correctamente la partición con id: %s****\x1B[0m\n",id);
    }
    else
    {
        printf("\n\x1B[33m****No existe una partición montada con el id: %s****\x1B[0m\n",id);
    }
}

//ejecuta el reporte solicitado
void ejecutarREP(char *name, char *path, char *id, char *ruta)
{
    aMinuscula(name);

    if((strcmp(name, "") != 0) && (strcmp(path, "") != 0) && (strcmp(id, "") != 0))
    {

        char *idDisco = malloc(strlen("solo quiero ocupar espacio :v") + 1);
        strncpy(idDisco,id+2,1);
        char *idParticion = malloc(strlen("solo quiero ocupar espacio :v") + 1);
        strncpy(idParticion,id+3,1);

        int disco = 0;
        int particion = 0;
        char *valoresLetras = "abcdefghijklmnopqrstuvwxyz";

        particion = atof(idParticion);

        char* punteroLetra = strchr(valoresLetras,*idDisco);
        disco = punteroLetra - valoresLetras;

        char * archivo = strrchr(path,'/');
        char directorio [256];
        memset(directorio,'\0',256);
        int tamano = strlen(path) - strlen(archivo);
        strncpy(directorio, path, tamano);

        if(directorio[strlen(directorio)-1] != '\"')
        {
            strcat(directorio, "\"");
        }


        char crearDirectorio[256] = "mkdir -p ";
        strcat(crearDirectorio, directorio);
        system(crearDirectorio);

        if(strcmp(particionesMontadas[disco][particion],"") != 0) //no existe la partición solicitada
        {
            if(strcmp(name,"\"mbr\"") == 0)
            {
                reporteMBR(path, particionesMontadas[disco][0], particionesMontadas[disco][particion]);
            }
            else if(strcmp(name,"\"disk\"") == 0)
            {
                reporteDISK(path, particionesMontadas[disco][0], particionesMontadas[disco][particion]);
            }
            else if(strcmp(name,"\"inode\"") == 0)
            {

            }
            else if(strcmp(name,"\"journaling\"") == 0)
            {

            }
            else if(strcmp(name,"\"block\"") == 0)
            {

            }
            else if(strcmp(name,"\"bm_inode\"") == 0)
            {

            }
            else if(strcmp(name,"\"bm_block\"") == 0)
            {

            }
            else if(strcmp(name,"\"tree\"") == 0)
            {

            }
            else if(strcmp(name,"\"sb\"") == 0)
            {

            }
            else if(strcmp(name,"\"file\"") == 0)
            {

            }
            else if(strcmp(name,"\"ls+i\"") == 0)
            {

            }
            else if(strcmp(name,"\"ls+l\"") == 0)
            {

            }
            else
            {
                printf("\n\x1B[33m****No existe un reporte llamado: \"%s\"****\x1B[0m\n",name);
            }
        }
        else
        {
            printf("\n\x1B[33m****No existe una partición montada con el id: %s****\x1B[0m\n",id);
        }
    }
    else
    {
        printf("\n\x1B[33m***Verifica que hayas incluido todos los parámetros obligatorios para el comando rep***\n");
        printf("-name\x1B[0m\n");
        printf("-path\x1B[0m\n");
        printf("-id\x1B[0m\n\n");
    }
}

//reporte MBR
void reporteMBR(char *path, char *rutaDisco, char *nombreParticion)
{
    FILE *disco = fopen (rutaDisco, "r+b");
    FILE *reporte = fopen ( "/home/dacore/Escritorio/ReporteMBR.dot", "w" );

    MBR mbr;
    fread (&mbr, sizeof(mbr), 1,disco);

    fprintf ( reporte, "digraph \"ReporteMBR\" {\n");
    fprintf ( reporte, "node [shape=plaintext]\n");
    fprintf ( reporte, "nodoMbr [fontname=\"ubuntu\",label=<<table border=\"0\" cellborder=\"1\" cellspacing=\"0\">\n");
    fprintf ( reporte, "<tr><td colspan=\"2\"><b>%s</b></td></tr>\n", rutaDisco);
    fprintf ( reporte, "<tr><td align=\"LEFT\"><b>mbr_tamano</b></td><td>%d</td></tr>\n",mbr.mbr_tamano);
    fprintf ( reporte, "<tr><td align=\"LEFT\"><b>mbr_fecha_creacion</b></td><td>%s</td></tr>\n",mbr.mbr_fecha_creacion);
    fprintf ( reporte, "<tr><td align=\"LEFT\"><b>mbr_disk_signature</b></td><td>%d</td></tr>\n",mbr.mbr_disk_signature);

if(mbr.mbr_particion[0].part_status != 'n')
    {

        if(mbr.mbr_particion[0].part_type == 'e')
        {

        }

        fprintf ( reporte, "<tr><td align=\"LEFT\"><b><font color=\"purple\">mbr_particion[0].part_status</font></b></td><td><font color=\"purple\">%c</font></td></tr>\n",mbr.mbr_particion[0].part_status);
        fprintf ( reporte, "<tr><td align=\"LEFT\"><b><font color=\"purple\">mbr_particion[0].part_type</font></b></td><td><font color=\"purple\">%c</font></td></tr>\n",mbr.mbr_particion[0].part_type);
        fprintf ( reporte, "<tr><td align=\"LEFT\"><b><font color=\"purple\">mbr_particion[0].part_fit</font></b></td><td><font color=\"purple\">%c</font></td></tr>\n",mbr.mbr_particion[0].part_fit);
        fprintf ( reporte, "<tr><td align=\"LEFT\"><b><font color=\"purple\">mbr_particion[0].part_start</font></b></td><td><font color=\"purple\">%d</font></td></tr>\n",mbr.mbr_particion[0].part_start);
        fprintf ( reporte, "<tr><td align=\"LEFT\"><b><font color=\"purple\">mbr_particion[0].part_size</font></b></td><td><font color=\"purple\">%d</font></td></tr>\n",mbr.mbr_particion[0].part_size);
        fprintf ( reporte, "<tr><td align=\"LEFT\"><b><font color=\"purple\">mbr_particion[0].part_name</font></b></td><td><font color=\"purple\">%s</font></td></tr>\n",mbr.mbr_particion[0].part_name);
    }

    if(mbr.mbr_particion[1].part_status != 'n')
    {

        if(mbr.mbr_particion[1].part_type == 'e')
        {

        }

        fprintf ( reporte, "<tr><td align=\"LEFT\"><b><font color=\"green\">mbr_particion[1].part_status</font></b></td><td><font color=\"green\">%c</font></td></tr>\n",mbr.mbr_particion[1].part_status);
        fprintf ( reporte, "<tr><td align=\"LEFT\"><b><font color=\"green\">mbr_particion[1].part_type</font></b></td><td><font color=\"green\">%c</font></td></tr>\n",mbr.mbr_particion[1].part_type);
        fprintf ( reporte, "<tr><td align=\"LEFT\"><b><font color=\"green\">mbr_particion[1].part_fit</font></b></td><td><font color=\"green\">%c</font></td></tr>\n",mbr.mbr_particion[1].part_fit);
        fprintf ( reporte, "<tr><td align=\"LEFT\"><b><font color=\"green\">mbr_particion[1].part_start</font></b></td><td><font color=\"green\">%d</font></td></tr>\n",mbr.mbr_particion[1].part_start);
        fprintf ( reporte, "<tr><td align=\"LEFT\"><b><font color=\"green\">mbr_particion[1].part_size</font></b></td><td><font color=\"green\">%d</font></td></tr>\n",mbr.mbr_particion[1].part_size);
        fprintf ( reporte, "<tr><td align=\"LEFT\"><b><font color=\"green\">mbr_particion[1].part_name</font></b></td><td><font color=\"green\">%s</font></td></tr>\n",mbr.mbr_particion[1].part_name);
    }

    if(mbr.mbr_particion[2].part_status != 'n')
    {

        if(mbr.mbr_particion[2].part_type == 'e')
        {

        }

        fprintf ( reporte, "<tr><td align=\"LEFT\"><b><font color=\"orange\">mbr_particion[2].part_status</font></b></td><td><font color=\"orange\">%c</font></td></tr>\n",mbr.mbr_particion[2].part_status);
        fprintf ( reporte, "<tr><td align=\"LEFT\"><b><font color=\"orange\">mbr_particion[2].part_type</font></b></td><td><font color=\"orange\">%c</font></td></tr>\n",mbr.mbr_particion[2].part_type);
        fprintf ( reporte, "<tr><td align=\"LEFT\"><b><font color=\"orange\">mbr_particion[2].part_fit</font></b></td><td><font color=\"orange\">%c</font></td></tr>\n",mbr.mbr_particion[2].part_fit);
        fprintf ( reporte, "<tr><td align=\"LEFT\"><b><font color=\"orange\">mbr_particion[2].part_start</font></b></td><td><font color=\"orange\">%d</font></td></tr>\n",mbr.mbr_particion[2].part_start);
        fprintf ( reporte, "<tr><td align=\"LEFT\"><b><font color=\"orange\">mbr_particion[2].part_size</font></b></td><td><font color=\"orange\">%d</font></td></tr>\n",mbr.mbr_particion[2].part_size);
        fprintf ( reporte, "<tr><td align=\"LEFT\"><b><font color=\"orange\">mbr_particion[2].part_name</font></b></td><td><font color=\"orange\">%s</font></td></tr>\n",mbr.mbr_particion[2].part_name);
    }

    if(mbr.mbr_particion[3].part_status != 'n')
    {

        if(mbr.mbr_particion[3].part_type == 'e')
        {

        }

        fprintf ( reporte, "<tr><td align=\"LEFT\"><b><font color=\"blue\">mbr_particion[3].part_status</font></b></td><td><font color=\"blue\">%c</font></td></tr>\n",mbr.mbr_particion[3].part_status);
        fprintf ( reporte, "<tr><td align=\"LEFT\"><b><font color=\"blue\">mbr_particion[3].part_type</font></b></td><td><font color=\"blue\">%c</font></td></tr>\n",mbr.mbr_particion[3].part_type);
        fprintf ( reporte, "<tr><td align=\"LEFT\"><b><font color=\"blue\">mbr_particion[3].part_fit</font></b></td><td><font color=\"blue\">%c</font></td></tr>\n",mbr.mbr_particion[3].part_fit);
        fprintf ( reporte, "<tr><td align=\"LEFT\"><b><font color=\"blue\">mbr_particion[3].part_start</font></b></td><td><font color=\"blue\">%d</font></td></tr>\n",mbr.mbr_particion[3].part_start);
        fprintf ( reporte, "<tr><td align=\"LEFT\"><b><font color=\"blue\">mbr_particion[3].part_size</font></b></td><td><font color=\"blue\">%d</font></td></tr>\n",mbr.mbr_particion[3].part_size);
        fprintf ( reporte, "<tr><td align=\"LEFT\"><b><font color=\"blue\">mbr_particion[3].part_name</font></b></td><td><font color=\"blue\">%s</font></td></tr>\n",mbr.mbr_particion[3].part_name);
    }

    fprintf ( reporte, "</table>>];\n");

    fprintf ( reporte, "}\n");
    fclose(disco);
    fclose(reporte);
    char comandoDOT[500];
    sprintf(comandoDOT, "dot -Tpng \"/home/dacore/Escritorio/ReporteMBR.dot\" -o %s", path);
    system(comandoDOT);
    strcpy(comandoDOT,"");
    sprintf(comandoDOT, "shotwell %s &", path);
    system(comandoDOT);
}

//reporte Disk
void reporteDISK(char *path, char *rutaDisco, char *nombreParticion)
{
    FILE *disco = fopen (rutaDisco, "r+b");
    FILE *reporte = fopen ( "/home/dacore/Escritorio/ReporteDISK.dot", "w" );

    MBR mbr;
    fread (&mbr, sizeof(mbr), 1,disco);

    fprintf ( reporte, "digraph \"ReporteDISK\" {\n");
    fprintf ( reporte, "node [shape=record, fontname=\"ubuntu\"]\n");
    fprintf ( reporte, "disco[label=\"{ %s | { MBR ", rutaDisco);

//lleno el arreglo con los datos de donde inicia cada partición
    int particionesLlenas [4] = {mbr.mbr_particion[0].part_start,mbr.mbr_particion[1].part_start,mbr.mbr_particion[2].part_start,mbr.mbr_particion[3].part_start};
    int indicesParticiones[4] = {-1,-1,-1,-1};
//ordeno los datos
    qsort (particionesLlenas, 4, sizeof(int), compare);

    int i = 0;
    for(i = 0; i<4; i++)
    {
        if(particionesLlenas[i] != 0)
        {
            if(mbr.mbr_particion[0].part_start == particionesLlenas[i])
            {
                indicesParticiones[i] = 0;
            }
            else if(mbr.mbr_particion[1].part_start == particionesLlenas[i])
            {
                indicesParticiones[i] = 1;
            }
            else if(mbr.mbr_particion[2].part_start == particionesLlenas[i])
            {
                indicesParticiones[i] = 2;
            }
            else if(mbr.mbr_particion[3].part_start == particionesLlenas[i])
            {
                indicesParticiones[i] = 3;
            }
        }
    }

    /**
        EN ESTE PUNTO TENGO ALMACENADOS EN "particionesLLenas" LOS part_start ORDENADOS ASCENDENTEMENTE
        Y EN "indicesParticion" LOS ÍNDICES DE LAS PARTICIONES ORDENADOS RESPECTO AL ORDEN DE "particionesLlenas"
    **/
    int menorActual = sizeof(mbr); //iniciamos desde el mbr
    for(i=0; i<4; i++)
    {
        if(particionesLlenas[i] != 0)
        {
            if(menorActual == particionesLlenas[i]) //quiere decir que no hay espacio libre entre ellos
            {
                if(mbr.mbr_particion[indicesParticiones[i]].part_type == 'p')
                {
                    fprintf ( reporte, "| PRIMARIA&#92;nNombre: %s ", mbr.mbr_particion[indicesParticiones[i]].part_name);
                }
                else if(mbr.mbr_particion[indicesParticiones[i]].part_type == 'e')
                {
                    fprintf ( reporte, "| {EXTENDIDA&#92;nNombre: %s | {EBR | libre}}", mbr.mbr_particion[indicesParticiones[i]].part_name);
                }
                else
                {

                }
            }
            else
            {
                if(mbr.mbr_particion[indicesParticiones[i]].part_type == 'p')
                {
                    fprintf ( reporte, "| libre&#92;n%d bytes  | PRIMARIA&#92;nNombre: %s ",particionesLlenas[i]-menorActual, mbr.mbr_particion[indicesParticiones[i]].part_name);
                }
                else if(mbr.mbr_particion[indicesParticiones[i]].part_type == 'e')
                {
                    fprintf ( reporte, "| libre&#92;n%d bytes  | {EXTENDIDA&#92;nNombre: %s | {EBR | libre}}",particionesLlenas[i]-menorActual, mbr.mbr_particion[indicesParticiones[i]].part_name);
                }
                else
                {

                }
            }

            menorActual = mbr.mbr_particion[indicesParticiones[i]].part_size + particionesLlenas[i];
        }
    }

    if(menorActual < mbr.mbr_tamano)
    {
        fprintf ( reporte, "| libre&#92;n%d bytes ",mbr.mbr_tamano-menorActual);
    }


    fprintf ( reporte, "}}\"];\n");
    fprintf ( reporte, "}");

    fclose(disco);
    fclose(reporte);

    char comandoDOT[500];
    sprintf(comandoDOT, "dot -Tpng \"/home/dacore/Escritorio/ReporteDISK.dot\" -o %s", path);
    system(comandoDOT);
    strcpy(comandoDOT,"");
    sprintf(comandoDOT, "shotwell %s &", path);
    system(comandoDOT);
}



