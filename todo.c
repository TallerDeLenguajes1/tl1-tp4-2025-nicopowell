#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int TareaID; // Numérico autoincremental comenzando en 1000
    char *Descripcion;
    int Duracion; // Entre 10 - 100
} Tarea;

typedef struct Nodo{
    Tarea T;
    struct Nodo *Siguiente;
} Nodo;

Nodo *CrearListaVacia(){
    return NULL;
}

Nodo *CrearNodo(){
    Nodo * nodo = (Nodo *)malloc(sizeof(Nodo));
    nodo->Siguiente = NULL;
    return nodo;
}

void cargarTarea(Nodo *nodo,int id, char *descripcion, int duracion){
    nodo->T.TareaID = id;
    nodo->T.Descripcion = (char *)malloc(strlen(descripcion) * sizeof(char) + 1);
    strcpy(nodo->T.Descripcion, descripcion);
    nodo->T.Duracion = duracion;
}

void insertarNodo(Nodo **Start, Nodo *nodo){
    nodo->Siguiente = *Start;
    *Start = nodo;
}

void listarTareas(Nodo *Start, int detalles){
    int i = 1;
    while (Start) {
        printf("\n%d. ", i++);
        if(detalles) printf("\tID: %d\n", Start->T.TareaID);
        printf("\tTarea: %s", Start->T.Descripcion);
        if(detalles) printf("\n\tDuracion: %d\n", Start->T.Duracion);
        Start = Start->Siguiente;
    }
}

int cantidadNodos(Nodo *Start){
    int contador = 0;
    while (Start) {
        contador++;
    }
    return contador;
}

void EliminarNodo(Nodo *nodo) {
    if(nodo){
        free(nodo->T.Descripcion);
        free(nodo);
    }
}

void EliminarLista(Nodo *Start){
    Nodo *aux;
    while(Start){
        *aux = *Start;
        Start = Start->Siguiente;
        EliminarNodo(aux);
    }
}

int aleatorio(int min, int max) {
    return min + rand() % (max + 1 - min);
}

int main(){ 
    int ingresarOtra = 1, duracion, contador = 1000, seleccion, cantidadPendientes;
    char *Buff;
    Buff = (char *)malloc(100*sizeof(char));

    Nodo *TareasPendientes = CrearListaVacia();
    Nodo *TareasRealizadas = CrearListaVacia();

    do {
        fflush(stdin);
        printf("============================================================");
        printf("\nIngrese la tarea: ");
        gets(Buff);
        printf("Ingrese la duracion: ");
        scanf("%d", &duracion);

        Nodo *nodo = CrearNodo();
        cargarTarea(nodo, contador, Buff, duracion);
        insertarNodo(&TareasPendientes, nodo);

        contador++;

        do {
            printf("\n============================================================");
            printf("\nQuiere ingresar otra tarea? ");
            printf("\n1. Si");
            printf("\n0. No\n");
            scanf("%d", &ingresarOtra);
        } while (ingresarOtra != 1 && ingresarOtra != 0);
        
    } while (ingresarOtra);
    
    cantidadPendientes = cantidadNodos(TareasPendientes);
    printf("\n%d", cantidadPendientes);

    do {
        printf("\n============================================================");
        listarTareas(TareasPendientes, 0);
        printf("\n0. Ninguna");
        printf("\nIngrese que tarea desea marcar como completada: ");
        scanf("%d", &seleccion);
    } while (seleccion != 0);
    
    EliminarLista(TareasPendientes);
    EliminarLista(TareasRealizadas);
    free(Buff);
}