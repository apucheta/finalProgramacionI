#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Un sistema encargado de registrar los distintos usuarios que acceden a una determinada aplicación almacena en un archivo denominado (usuarios.txt)
 los nombres de usuarios y un código numérico para controlar que usuarios entraron al sistema y con qué frecuencia 
*/

#define users "usuarios.txt"
#define MAX_USUARIO 5
#define CANT_USUARIOS 30

int codigo;

void abrirYListar();
void buscaUsuario( FILE *archivousuarios, int);

typedef struct
{
    int cod;
    char nom[30];
} datos;

void guardaDatos(datos []);
void imprimir(datos [], int);


int main()
{
    // 1. Crear una función que abra el archivo y liste el fichero completo
    abrirYListar();
    
    // 2.Ingresar un código de usuario luego, 
    //a través de una función que tome como parámetros de entrada el fichero y
    // el numero ingresado, indique en el programa principal cuantas veces dicho
    // usuario ingreso al sistema

    printf("Ingrese un codigo: ");
    fflush(stdin);
    scanf("%d", &codigo);
    FILE * archivo_users;
    archivo_users = fopen(users, "rt");
    if(archivo_users ==NULL){
        printf("Error al abrir el archivo_users");
    }else{
        buscaUsuario(archivo_users,codigo);
    }
    fclose(archivo_users);

    datos todos[CANT_USUARIOS];
    guardaDatos(todos);
    return 0;

}
void abrirYListar(){
    char usuario[MAX_USUARIO];
    FILE * archivo;
    archivo = fopen(users, "rt");
    if(archivo == NULL){
        printf("Hubo un error al abrir el archivo. \n");
    }else{
        fscanf(archivo, "%s\t%d\n", usuario, &codigo);
        while (!feof(archivo))
        {
            printf("%s\t%d\n", usuario, codigo);
        fscanf(archivo, "%s\t%d\n", usuario, &codigo);
            
        }
    }
    fclose(archivo);
}


void buscaUsuario(FILE * fichero, int codBuscado){
    int contador = 0;
    char usuario[50];
    char usuarioBuscado[50]; 
    int cod;

    fscanf(fichero,"%s\t%d\n", usuario, &cod);
    if(codBuscado == cod)
    {
        strcpy(usuarioBuscado, usuario);
        contador++;
    }
    while (!feof(fichero))
    {    
        fscanf(fichero,"%s\t%d\n", usuario, &cod);
        if(codBuscado == cod)
        {
            strcpy(usuarioBuscado, usuario);
            contador++;
        }
    }
    if(contador > 1){
        printf("El usuario %s ingreso %d veces.\n", usuarioBuscado, contador);
    }else if(contador == 1){
        printf("El usuario %s ingreso %d vez.\n", usuarioBuscado, contador);

    }else{
        printf("El usuario no ingreso todavia.\n");
    }
}

void guardaDatos(datos todos[])
{
    FILE * archivo_txt;
    int contador = 0;
    char usuario[50];
    int cod;

    archivo_txt = fopen("usuarios.txt", "rt");

    if(archivo_txt == NULL)
        printf("Error al abrir el archivo.\n");
    else
    {
        fscanf(archivo_txt,"%s\t%d\n", usuario, &cod);
        if(cod > 200 && cod < 450)
        {
            strcpy(todos[contador].nom, usuario);
            todos[contador].cod = cod;
            contador++;
        }
        while (!feof(archivo_txt))
        {
            fscanf(archivo_txt,"%s\t%d\n", usuario, &cod);
            if(cod > 200 && cod < 450)
            {
                strcpy(todos[contador].nom, usuario);
                todos[contador].cod = cod;
                contador++;
            }
        }
        fclose(archivo_txt);
    }

    imprimir(todos, contador);
}

void imprimir(datos todos[], int cant)
{
    if(cant == 1)
    {
        printf("%s\t%d\n", todos[cant-1].nom, todos[cant-1].cod);
    } 
    else
    {
        imprimir(todos, cant - 1);
        printf("%s\t%d\n", todos[cant-1].nom, todos[cant-1].cod);
    }
}