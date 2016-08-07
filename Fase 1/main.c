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
                printf("****El parámetro \"%s\" no es válido****\n",aux);
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
                printf("****El parámetro \"%s\" no es válido****\n",aux);
            }

            comando = strtok(NULL, ":");
        }
        ejecutarFDISK(size,unit,path,type,fit,tdelete,name,add);
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
                    printf("\n%s",lineaLimpia);
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
        printf("\n***El archivo que intentas cargar no existe***\n");
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

                        mbr.mbr_tamano = unidades;
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
    espacio al mbr**/   //sprintf(unidadesChar, "%d", unidades + sizeof(mbr));

    /**este toma espacio
    del disco para
    el mbr**/           sprintf(unidadesChar, "%d", unidades);

                        /**por el momento, le quito espacio al disco para almacenar el mbr**/

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

                        printf("\n****¡Disco creado con éxito!****\n");
                    }
                    else
                    {
                        printf("\n****El tamaño mínimo de un disco debe ser de 10MB****\n");
                    }
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

            printf("\n****¡Disco eliminado exitosamente!****\n");
        }

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
    printf("size: %s\n", size);
    printf("unit: %s\n", unit);
    printf("path: %s\n", path);
    printf("type: %s\n", type);
    printf("fit: %s\n", fit);
    printf("tdelete: %s\n", tdelete);
    printf("name: %s\n", name);
    printf("add: %s\n", add);
}

//ejecuta el comando "mount"
void ejecutarMOUNT(char* path, char* name)
{

}

//ejecuta el comando "unmount"
void ejecutarUNMOUNT(char* id)
{

}
