#include<stdio.h>
#include<string.h>

struct competidores{
    int nroCompetidor; //mayor a cero y van en orden
    char apellido[30];
    char estilo;
    int distancia;
    float tiempo;
    int activo; //1 o 0
};

//Menu de opciones que retorna la opcion elegida por el usuario.
int menuOpciones(){
    int opcionElegida;

    printf("*** Menu principal ***\n");
    printf("1. Crear archivo binario\n");
    printf("2. Dar de alta un competidor\n");
    printf("3. Listar los competidores\n");
    printf("4. Modificar distancia de un competidor\n");
    printf("5. Calcular el mejor tiempo de un estilo de nado\n");
    printf("6. Dar de baja a un competidor\n");
    printf("0. Para finalizar el programa\n");
    printf("OPCION ELEGIDA: ");
    scanf("%d", &opcionElegida);
    fflush(stdin);

    return opcionElegida;
}
//Funcion para la creacion del archivo binario
void crearArchivo(FILE *punteroArchivo){
    punteroArchivo = fopen("competencia_2022.dat", "w+b");
    if(punteroArchivo != NULL){
        printf("El archivo se creo exitosamente!\n");
    }else{
        printf("Hubo un error en la creacion del archivo\n");
    }
    fclose(punteroArchivo);
}
//Funcion para dar de alta a un competidor
void darAltaCompetidor(FILE *punteroArchivo){
    punteroArchivo = fopen("competencia_2022.dat", "r+b");
    struct competidores competidor;

    if(punteroArchivo != NULL){
        printf("Ingresa el nro de tu competidor (0 para terminar): ");
        scanf("%d", &competidor.nroCompetidor);
        fflush(stdin);

        while(competidor.nroCompetidor >= 0){
            printf("Ingresa el apellido de tu competidor: ");
            gets(competidor.apellido);
            fflush(stdin);

            printf("Ingresa el estilo de nado de tu competidor (L:libre, E:espalda, B:braza o M:mariposa): ");
            scanf("%c", &competidor.estilo);
            fflush(stdin);

            printf("Ingresa la distancia que recorrio tu competidor(metros): ");
            scanf("%d", &competidor.distancia);
            fflush(stdin);

            printf("Ingresa el tiempo de tu competidor (minutos): ");
            scanf("%f", &competidor.tiempo);
            fflush(stdin);

            competidor.activo= 1;           //Por default todos estan activos al principio

            //Me paro en el inicio y me muevo al nro de competidor menos 1 que vendria a ser el nro de bytes de su posicion.
            fseek(punteroArchivo, (competidor.nroCompetidor - 1)*sizeof(struct competidores), SEEK_SET);
            fwrite(&competidor, sizeof(struct competidores), 1, punteroArchivo);

            printf("\nIngresa otro nro de un competidor (0 para terminar): ");
            scanf("%d", &competidor.nroCompetidor);
            fflush(stdin);
        }
        fclose(punteroArchivo);
    }else{
        printf("\nNro de competidor no valido!\n");
    }
}

//Funcion que lista los competidores
void listarCompetidores(FILE *punteroArchivo){
}


//Main con todos los llamados
int main(){
    FILE *punteroArchivo;

    int opcion;

    do{
        opcion = menuOpciones();
        switch(opcion){
            case 1: crearArchivo(punteroArchivo);
                break;
            case 2: darAltaCompetidor(punteroArchivo);
                break;
            case 3: listarCompetidores(punteroArchivo)
                break;
            case 4:
                break;
        }
    }while(opcion != 0);

    getchar();
    return 0;
}
