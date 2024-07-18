#include<stdio.h>
#include<string.h>

//--- DEFINICION DE STRUCT DE COMPETIDORES DE NATACION ---
struct competidores{
    int nroCompetidor; //mayor a cero y van en orden
    char apellido[30];
    char estilo;
    int distancia;
    float tiempo;
    int activo; //1 o 0
};

//****** MENU de opciones que retorna la opcion elegida por el usuario ******
int menuOpciones(){
    int opcionElegida;

    printf("\n*** Menu principal - Final de Laboratorio de Computacion II ***\n");
    printf("1. Crear archivo binario\n");
    printf("2. Dar de alta un competidor\n");
    printf("3. Listar los competidores\n");
    printf("4. Modificar distancia de un competidor\n");
    printf("5. Calcular el mejor tiempo de un estilo de nado\n");
    printf("6. Dar de baja a un competidor\n");
    printf("7. Filtrar competidores segun estado (activo o no)\n");
    printf("0. Para finalizar el programa\n");
    printf("OPCION ELEGIDA: ");
    scanf("%d", &opcionElegida);
    fflush(stdin);

    return opcionElegida;
}

//---------------AUXILIAR QUE CALCULA LA CANTIDAD DE REGISTROS DEL ARCHIVO. Me era mas como modularizarla para no repetir lo mismo.
int cantRegistros(FILE *punteroArchivo){
    punteroArchivo= fopen("competencia_2022.dat","r+b");
    struct competidores competidor;

    int registros;

    fseek(punteroArchivo,0,SEEK_END);
    registros = ftell(punteroArchivo) / sizeof(struct competidores);

    return registros;       //Devuelve los registros
}


//****** Funcion para la CREACION del archivo binario ******
void crearArchivo(FILE *punteroArchivo){
    punteroArchivo = fopen("competencia_2022.dat", "w+b");
    if(punteroArchivo != NULL){
        printf("\nEl archivo se creo exitosamente!\n");
    }else{
        printf("\nHubo un error en la creacion del archivo\n");
    }
    fclose(punteroArchivo);
}

//****** Funcion para DAR DE ALTA a un competidor ******
void darAltaCompetidor(FILE *punteroArchivo){
    punteroArchivo = fopen("competencia_2022.dat", "r+b");
    struct competidores competidor;

    if(punteroArchivo != NULL){
        printf("\nIngresa el nro de tu competidor (0 para terminar): ");
        scanf("%d", &competidor.nroCompetidor);
        fflush(stdin);

        while(competidor.nroCompetidor > 0){
            printf("\nIngresa el apellido de tu competidor: ");
            gets(competidor.apellido);
            fflush(stdin);

            printf("\nIngresa el estilo de nado de tu competidor (L:libre, E:espalda, B:braza o M:mariposa): ");
            scanf("%c", &competidor.estilo);
            fflush(stdin);

            printf("\nIngresa la distancia que recorrio tu competidor(metros): ");
            scanf("%d", &competidor.distancia);
            fflush(stdin);

            printf("\nIngresa el tiempo de tu competidor (minutos): ");
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

//****** Funcion que LISTA los competidores ******
void listarCompetidores(FILE *punteroArchivo){
    punteroArchivo= fopen("competencia_2022.dat","r+b");
    struct competidores competidor;

    int i=0, registros;

    if(punteroArchivo != NULL){
        registros = cantRegistros(punteroArchivo);
        fseek(punteroArchivo,0,SEEK_SET);

        while(i < registros){
            fseek(punteroArchivo,i*sizeof(struct competidores),SEEK_SET);
            fread(&competidor, sizeof(struct competidores), 1, punteroArchivo);
            printf("\nNro competidor: %d - Apellido: %s - Estilo: %c - Distancia: %d - Tiempo: %.2f - Estado activo:  %d\n", competidor.nroCompetidor, competidor.apellido, competidor.estilo, competidor.distancia, competidor.tiempo, competidor.activo);
            i++;
        }
        fclose(punteroArchivo);
    }else{
        printf("\nError en la lectura de tu archivo!\n");
    }
}

//****** Funcion para FILTRAR por competidores activos o no ******
void filtrarActivos(FILE *punteroArchivo){
    punteroArchivo= fopen("competencia_2022.dat","r+b");
    struct competidores competidor;

    int i=0, registros;

    if(punteroArchivo != NULL){
        registros = cantRegistros(punteroArchivo);
        fseek(punteroArchivo,0,SEEK_SET);

        while(i < registros){
            fseek(punteroArchivo,i*sizeof(struct competidores),SEEK_SET);
            fread(&competidor, sizeof(struct competidores), 1, punteroArchivo);
            if(competidor.activo == 1){
                 printf("\nNro competidor: %d - Apellido: %s - Estilo: %c - Distancia: %d - Tiempo: %.2f - Estado activo:  %d\n", competidor.nroCompetidor, competidor.apellido, competidor.estilo, competidor.distancia, competidor.tiempo, competidor.activo);
            }
            i++;
        }
        fclose(punteroArchivo);
    }else{
        printf("\nError en la lectura de tu archivo!\n");
    }
}


//****** Funcion para MODIFICAR distancia ******
void modificarDist(FILE *punteroArchivo){
    punteroArchivo= fopen("competencia_2022.dat","r+b");
    struct competidores competidor;

    int nroCompetidor_mod;
    float distancia_mod;

    int i=0, registros;

    if(punteroArchivo != NULL){
        //Calculo la cantidad de registros que hay en el archivo.
//        fseek(punteroArchivo,0,SEEK_END);
//        registros = ftell(punteroArchivo) / sizeof(struct competidores);
        registros = cantRegistros(punteroArchivo);

        printf("\nIngresa el id del competidor al que deseas cambiarle la distancia: ");
        scanf("%d", &nroCompetidor_mod);
        fflush(stdin);

        printf("\nCual es la nueva distancia? ");
        scanf("%f", &distancia_mod);

        while(i < registros){   //mientras que i no supere a la cantidad de registros del archivo
            fread(&competidor,sizeof(struct competidores),1, punteroArchivo);

            if(nroCompetidor_mod == competidor.nroCompetidor){
                printf("\nEl valor de la distancia del competidor %d es de %.2f", competidor.nroCompetidor, competidor.distancia);

                competidor.distancia = distancia_mod;

                //Reubica el puntero a la posicion para reescribir el struct
                fseek(punteroArchivo,(competidor.nroCompetidor-1)*sizeof(struct competidores), SEEK_SET);
                fwrite(&competidor, -sizeof(struct competidores),1, punteroArchivo);

                //printf("El NUEVO valor de la distancia del competidor %d es de %.2f", competidor.nroCompetidor, competidor.distancia);
            }
            i++;
        }
        fclose(punteroArchivo);
    }else{
        printf("\nError en la lectura de tu archivo!\n");
    }
}


//****** Funcion para calcular MEJOR TIEMPO de un estilo de nado *******
void mejorTiempo(FILE *punteroArchivo){
    punteroArchivo= fopen("competencia_2022.dat","r+b");
    struct competidores competidor;

    char categoria;
    int i=0, registros;
    float tiempoMax=0;

    printf("\nDe que estilo te interesa calcular el mejor tiempo? ");
    scanf("%c", &categoria);
    fflush(stdin);

    if(punteroArchivo != NULL){
        registros = cantRegistros(punteroArchivo);
        fseek(punteroArchivo,0,SEEK_SET);

        while(i < registros){
            fseek(punteroArchivo, i*sizeof(struct competidores), SEEK_SET);
            fread(&competidor,sizeof(struct competidores),1,punteroArchivo);

            if(categoria==competidor.estilo && competidor.tiempo > tiempoMax){
                tiempoMax = competidor.tiempo;
            }
            i++;
        }
        printf("\nEl tiempo maximo de la categoria %c es %.2f", categoria, tiempoMax);
        fclose(punteroArchivo);
    }else{
        printf("\nError en la lectura de tu archivo!\n");
    }
}

//****** Funcion para DAR DE BAJA a un competidor ******
void darBaja(FILE *punteroArchivo){
    punteroArchivo= fopen("competencia_2022.dat","r+b");
    struct competidores competidor;

    int competidorId, i=0, registros;

    printf("\nQue numero de socio queres dar de baja?: ");
    scanf("%d", &competidorId);
    fflush(stdin);

    if(punteroArchivo != NULL){
        registros = cantRegistros(punteroArchivo);
        fseek(punteroArchivo,0,SEEK_SET);

        while(i < registros){
            fread(&competidor, sizeof(struct competidores),1,punteroArchivo);
            if(competidorId == competidor.nroCompetidor){
                competidor.nroCompetidor = 0;

                fseek(punteroArchivo,(competidor.nroCompetidor-1)*sizeof(struct competidores),SEEK_SET);
                fwrite(&competidor,-sizeof(struct competidores),1,punteroArchivo);
            }
            i++;
        }
        fclose(punteroArchivo);
    }else{
        printf("\nError en la lectura de tu archivo!\n");
    }

}


//****** MAIN con todos los llamados ******
int main(){
    FILE *punteroArchivo;
    //struct competidores competidor; despues para probar

    int opcion;

    do{
        opcion = menuOpciones();
        switch(opcion){
            case 1: crearArchivo(punteroArchivo);
                break;
            case 2: darAltaCompetidor(punteroArchivo);
                break;
            case 3: listarCompetidores(punteroArchivo);
                break;
            case 4: modificarDist(punteroArchivo);
                break;
            case 5: mejorTiempo(punteroArchivo);
                break;
            case 6: darBaja(punteroArchivo);
                break;
            case 7: filtrarActivos(punteroArchivo);
                break;
            default: printf("\nIngresaste una opcion no valida!\n");
                break;
        }
    }while(opcion != 0);

    getchar();
    return 0;
}
