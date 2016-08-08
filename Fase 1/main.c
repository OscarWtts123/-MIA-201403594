#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "structs.h"

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
    else if(strcmp(comando,"unmount:") == 0)
    {
        casoComando = 5;
    }
    else
    {
        printf("\x1B[33m****Error: El comando \"%s\" no es válido.****\x1B[0m\n",comando);
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
            char eliminarDisco [100] = "rm ";
            strcat(eliminarDisco, path);
            system(eliminarDisco);

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
        char* pathLimpio = malloc(strlen("solo quiero ocupar espacio :v") + 100);
        strncpy(pathLimpio,path+1,strlen(path)-2); //-2 porque toma en cuenta las 2 comillas

        char* nameLimpio = malloc(strlen("solo quiero ocupar espacio :v") + 100);
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

                        int unidades = 1024 * atof(size); // unidad por defecto Kilobytes, unidades es el size expresado en bytes
                        int banderaTamano = 0;

                        if(strcmp(unit,"m") == 0)
                        {
                            unidades = 1024 * 1024 * atof(size);
                            if(atof(size)>=2)
                            {
                                banderaTamano = 1;
                            }
                        }
                        else if(strcmp(unit,"b") == 0)
                        {
                            unidades = atof(size);
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

                                        if(mbr.mbr_particion[0].part_status == 'n')
                                        {
                                            //indiceParticion = 0;
                                            int inicioEspacioLibre = sizeof(mbr); //desde donde termina el MBR
                                            int finEspacioLibre = mbr.mbr_tamano; //hasta el fin del disco

                                            if((finEspacioLibre - inicioEspacioLibre) >= unidades) //sí encontré el espacio
                                            {
                                                strcpy(mbr.mbr_particion[0].part_name, nameLimpio);
                                                mbr.mbr_particion[0].part_start = inicioEspacioLibre;
                                                mbr.mbr_particion[0].part_status = 'y';
                                                mbr.mbr_particion[0].part_size = unidades;
                                                mbr.mbr_particion[0].part_type = 'p';
                                                mbr.mbr_particion[0].part_fit = fitPart;
                                            }
                                            else
                                            {
                                                printf("\n\x1B[33m****No hay espacio suficiente en el disco.****\x1B[0m\n");
                                            }
                                        }
                                        else if(mbr.mbr_particion[1].part_status == 'n')
                                        {
                                            indiceParticion = 1;
                                            int inicioEspacioLibre = mbr.mbr_particion[0].part_start +  mbr.mbr_particion[0].part_size;//desde donde termina el MBR
                                            int finEspacioLibre = mbr.mbr_tamano; //hasta el fin del disco

                                            if((finEspacioLibre - inicioEspacioLibre) >= unidades) //sí encontré el espacio
                                            {
                                                if(strcmp(mbr.mbr_particion[0].part_name, nameLimpio) != 0) //el nombre no existe
                                                {
                                                    strcpy(mbr.mbr_particion[1].part_name, nameLimpio);
                                                    mbr.mbr_particion[1].part_start = inicioEspacioLibre;
                                                    mbr.mbr_particion[1].part_status = 'y';
                                                    mbr.mbr_particion[1].part_size = unidades;
                                                    mbr.mbr_particion[1].part_type = 'p';
                                                    mbr.mbr_particion[1].part_fit = fitPart;
                                                }
                                                else
                                                {
                                                    printf("\n\x1B[33m****Ya existe una partición con ese nombre.****\x1B[0m\n");
                                                }
                                            }
                                            else
                                            {
                                                printf("\n\x1B[33m****No hay espacio suficiente en el disco.****\x1B[0m\n");
                                            }
                                        }
                                        else if(mbr.mbr_particion[2].part_status == 'n')
                                        {
                                            indiceParticion = 2;
                                            int inicioEspacioLibre = mbr.mbr_particion[1].part_start +  mbr.mbr_particion[1].part_size ;//desde donde termina el MBR
                                            int finEspacioLibre = mbr.mbr_tamano; //hasta el fin del disco

                                            if((finEspacioLibre - inicioEspacioLibre) >= unidades) //sí encontré el espacio
                                            {
                                                if((strcmp(mbr.mbr_particion[0].part_name, nameLimpio) != 0) &&
                                                   (strcmp(mbr.mbr_particion[1].part_name, nameLimpio) != 0)) //el nombre no existe
                                                {
                                                    strcpy(mbr.mbr_particion[2].part_name, nameLimpio);
                                                    mbr.mbr_particion[2].part_start = inicioEspacioLibre;
                                                    mbr.mbr_particion[2].part_status = 'y';
                                                    mbr.mbr_particion[2].part_size = unidades;
                                                    mbr.mbr_particion[2].part_type = 'p';
                                                    mbr.mbr_particion[2].part_fit = fitPart;
                                                }
                                                else
                                                {
                                                    printf("\n\x1B[33m****Ya existe una partición con ese nombre.****\x1B[0m\n");
                                                }
                                            }
                                            else
                                            {
                                                printf("\n\x1B[33m****No hay espacio suficiente en el disco.****\x1B[0m\n");
                                            }
                                        }
                                        else if(mbr.mbr_particion[3].part_status == 'n')
                                        {
                                            indiceParticion = 3;
                                            int inicioEspacioLibre = mbr.mbr_particion[2].part_start +  mbr.mbr_particion[2].part_size; //desde donde termina el MBR
                                            int finEspacioLibre = mbr.mbr_tamano; //hasta el fin del disco

                                            if((finEspacioLibre - inicioEspacioLibre) >= unidades) //sí encontré el espacio
                                            {
                                                if((strcmp(mbr.mbr_particion[0].part_name, nameLimpio) != 0) &&
                                                   (strcmp(mbr.mbr_particion[1].part_name, nameLimpio) != 0) &&
                                                   (strcmp(mbr.mbr_particion[2].part_name, nameLimpio) != 0)) //el nombre no existe
                                                {
                                                    strcpy(mbr.mbr_particion[3].part_name, nameLimpio);
                                                    mbr.mbr_particion[3].part_start = inicioEspacioLibre;
                                                    mbr.mbr_particion[3].part_status = 'y';
                                                    mbr.mbr_particion[3].part_size = unidades;
                                                    mbr.mbr_particion[3].part_type = 'p';
                                                    mbr.mbr_particion[3].part_fit = fitPart;

                                                    printf("\n\x1B[33m****¡La partición primaria se ha creado con éxito!****\x1B[0m\n");
                                                }
                                                else
                                                {
                                                    printf("\n\x1B[33m****Ya existe una partición con ese nombre.****\x1B[0m\n");
                                                }
                                            }
                                            else
                                            {
                                                printf("\n\x1B[33m****No hay espacio suficiente en el disco.****\x1B[0m\n");
                                            }
                                        }
                                        else
                                        {
                                            printf("\n\x1B[33m****No se que pasa.****\x1B[0m\n");
                                        }
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
//                            eliminarParticion();
                        }
                        else if((strcmp(tdelete,"") == 0) && (strcmp(add,"") != 0)) //significa que se quiere agregar/quitar tamaño
                        {
//                            redimensionarParticion();
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

//ejecuta el comando "mount"
void mostrarParticionesMontadas()
{
printf("holi desde la lista de particiones :3\n");
}

//ejecuta el comando "mount"
void ejecutarMOUNT(char* path, char* name)
{
printf("holi desde el mount :3\n");
}

//ejecuta el comando "unmount"
void ejecutarUNMOUNT(char* id)
{

}
