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
        Start = Start->Siguiente;
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

void marcarCompletada(Nodo **Pendientes, Nodo **Completadas, int seleccion){
    Nodo *actual = *Pendientes;
    Nodo *anterior = NULL;
    int i = 1;

    while (actual != NULL && i < seleccion) {
        anterior = actual;
        actual = actual->Siguiente;
        i++;
    }

    if (anterior == NULL) {
        *Pendientes = actual->Siguiente;
    } else {
        anterior->Siguiente = actual->Siguiente;
    }

    actual->Siguiente = NULL;

    insertarNodo(Completadas, actual);
}

void buscarTareaPorID(Nodo *Pendientes, Nodo *Realizadas, int idBuscado){
    Nodo *aux;

    printf("\n=========== Búsqueda por ID ===========\n");

    // Buscar en pendientes
    aux = Pendientes;
    while (aux) {
        if (aux->T.TareaID == idBuscado) {
            printf("-> [Pendiente]\n\tID: %d\n\tTarea: %s\n\tDuracion: %d\n",
                   aux->T.TareaID, aux->T.Descripcion, aux->T.Duracion);
            return;
        }
        aux = aux->Siguiente;
    }

    // Buscar en realizadas
    aux = Realizadas;
    while (aux) {
        if (aux->T.TareaID == idBuscado) {
            printf("-> [Realizada]\n\tID: %d\n\tTarea: %s\n\tDuracion: %d\n",
                   aux->T.TareaID, aux->T.Descripcion, aux->T.Duracion);
            return;
        }
        aux = aux->Siguiente;
    }
    printf("No se encontró ninguna tarea con el ID %d.\n", idBuscado);
}

void buscarTareaPorPalabra(Nodo *Pendientes, Nodo *Realizadas, char *clave){
    Nodo *aux;

    printf("\n=========== Búsqueda por palabra clave ===========\n");

    // Buscar en pendientes
    aux = Pendientes;
    while (aux) {
        if (strstr(aux->T.Descripcion, clave)) {
            printf("-> [Pendiente]\n\tID: %d\n\tTarea: %s\n\tDuracion: %d\n",
                   aux->T.TareaID, aux->T.Descripcion, aux->T.Duracion);
        }
        aux = aux->Siguiente;
    }

    // Buscar en realizadas
    aux = Realizadas;
    while (aux) {
        if (strstr(aux->T.Descripcion, clave)) {
            printf("-> [Realizada]\n\tID: %d\n\tTarea: %s\n\tDuracion: %d\n",
                   aux->T.TareaID, aux->T.Descripcion, aux->T.Duracion);
            return;
        }
        aux = aux->Siguiente;
    }

    printf("No se encontró ninguna tarea que contenga la palabra \"%s\".\n", clave);
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

    
    do {
        cantidadPendientes = cantidadNodos(TareasPendientes);
        printf("\n============================================================");
        listarTareas(TareasPendientes, 0);
        printf("\n0. Ninguna");
        printf("\nIngrese que tarea desea marcar como completada: ");
        scanf("%d", &seleccion);
        if (seleccion > 0 && seleccion <= cantidadPendientes){
            marcarCompletada(&TareasPendientes, &TareasRealizadas, seleccion);
        }
    } while (seleccion != 0);
    
    printf("\n===================== Pendientes ==========================");
    listarTareas(TareasPendientes, 1);

    printf("\n===================== Realizadas ==========================");
    listarTareas(TareasRealizadas, 1);

    int opcionBusqueda;
    int idBuscado;
    char palabraClave[100];

    do {
        printf("\n=============== MENU DE BUSQUEDA ===============");
        printf("\n1. Buscar tarea por ID");
        printf("\n2. Buscar tarea por palabra clave");
        printf("\n0. Salir");
        printf("\nSeleccione una opcion: ");
        scanf("%d", &opcionBusqueda);
        fflush(stdin);

        switch(opcionBusqueda) {
            case 1:
                printf("Ingrese el ID de la tarea: ");
                scanf("%d", &idBuscado);
                buscarTareaPorID(TareasPendientes, TareasRealizadas, idBuscado);
                break;
            case 2:
                printf("Ingrese la palabra clave a buscar: ");
                gets(palabraClave);
                buscarTareaPorPalabra(TareasPendientes, TareasRealizadas, palabraClave);
                break;
            case 0:
                printf("Saliendo del menú de búsqueda...\n");
                break;
            default:
                printf("Opción inválida. Intente nuevamente.\n");
        }
    } while(opcionBusqueda != 0);

    EliminarLista(TareasPendientes);
    EliminarLista(TareasRealizadas);
    free(Buff);
}