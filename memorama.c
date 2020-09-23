#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define ren 4
#define col 4

char jugador1[11], jugador2[11];

int tamMatriz = ren * col; // Saber si es par o no
int mitadTamMatriz = ren * col / 2; // Saber cuantas palabras habrá en la matriz
int puntajeJ1 = 0, puntajeJ2 = 0;
int X1 = 0, Y1 = 0, X2 = 0, Y2 = 0;

char* listaDeCaracteres[] = {"Leche", "Crema", "Queso", "Huevo", "Oveja", "Pecan", "Carne",
"Pollo", "Mango", "Palta", "Licor", "Chile", "Limas", "Fresa", "Cerdo", "Arroz", "Moras", "Tacos"}; // Lista de strings

char* matrizDeCaracteres[ren][col]; // Se va dibujar
char* copiaMatrizDeCaracteres[ren][col]; // Toda la informacion de la matriz, la matriz de los strings

bool turno = true, fallaste = false;

void CrearMatriz(char* listaChar[], char* M[ren][col]){
    srand(time(NULL));
    char* tempLista[tamMatriz]; // Lista de strings temporal
    char* tempPalabra[1]; // Barajear cartas temporal
    int contador = 0;

    for(int i = 0; i < 2; i++){
        for (int j = 0; j < mitadTamMatriz; j++){
            tempLista[contador] = listaChar[j]; // Asigna las tarjetas , los pares de palabras
            contador++;
        }
    }

    // Barajear Cartas
    for (int i = 0; i < tamMatriz; i++){
        int j = rand()%tamMatriz;
        tempPalabra[0] = tempLista[i];
        tempLista[i] = tempLista[j]; // Intercambia valores en i por j
        tempLista[j] = tempPalabra[0]; // Intercambia valores en j por palabra temporal que antes era i
    }

    contador = 0;

    for (int i = 0; i < ren; i++) {
        for (int j = 0; j < col; j++) {
            M[i][j] = tempLista[contador]; // Asigna en la matriz los valores de la lista temporal de strings
            contador++;
        }
    }
}


void ImprimeMatriz(char* M[ren][col]) {
    for (int i = 0; i < ren; i++) {
        for (int j = 0; j < col; j++) {
            printf("%8s ", M[i][j]); // "8s" le da espaciado entre cada impresión de palabra.... hola   -------      hola
        }
        printf("\n");
    }
    printf("\n");
}

void CopiarMatriz(char* M[ren][col], char* C[ren][col]) {
    for(int i = 0; i < ren; i++) {
        for(int j = 0; j < col; j++) {
            C[i][j] = M[i][j]; // Asigna los valores de una matriz a la otra
        }
    }
}

void EnmascararMatriz(char* M[ren][col]) {
    for(int i = 0; i < ren; i++){
        for(int j = 0; j < col; j++){
            M[i][j] = "*****"; // Asigna los valores de la matriz a "*****"
        }
    }
}

void DesenmascararMatriz(char* A[ren][col], char* Amascara[ren][col]){
    if (X1 <= 0 || X1 > ren || Y1 <= 0 || Y1 > col || X2 <= 0 || X2 > ren || Y2 <= 0 || Y2 > col){
        printf("Tiene un numero fuera del rango\n");
        printf("Perdiste tu turno por no prestar atencion\n");
        turno = !turno;
    }
    else if (X1 == X2 && Y1 == Y2){
        printf("No se pueden repetir las casillas durante la misma jugada\n");
        printf("Perdiste tu turno por no prestar atencion\n");
        turno = !turno;
    }
    else if(Amascara[X1-1][Y1-1] != "*****" || Amascara[X2-1][Y2-1] != "*****"){
        printf("No se pueden obtener las casillas que ya han sido desbloqueadas\n");
        printf("Perdiste tu turno por no prestar atencion\n");
        turno = !turno;
    }
    else if(A[X1-1][Y1-1] == A[X2-1][Y2-1]){ // Se comparan las palabras correctas
        Amascara[X1-1][Y1-1] = A[X1-1][Y1-1]; // Se asigna los valores de la matriz copia en la enmascarada
        Amascara[X2-1][Y2-1] = A[X2-1][Y2-1]; // Se asigna los valores de la matriz copia en la enmascarada
        AgregarPuntaje();

        printf("Primera palabra elegida: %s\n", A[X1-1][Y1-1]);
        printf("Segunda palabra elegida: %s\n", A[X2-1][Y2-1]);
    }
    else{
        printf("Fallaste\n");
        turno = !turno;
        fallaste = true; // Sirve para la función DestaparPalabrasTemp
    }
}

void DestaparPalabrasTemp(char* A[ren][col], char* Amascara[ren][col]) {
    if (fallaste) { // Si es verdadero
        Amascara[X1-1][Y1-1] = A[X1-1][Y1-1]; // Asigna temporalmente los valores de la matriz copia en la enmascarada
        Amascara[X2-1][Y2-1] = A[X2-1][Y2-1]; // Asigna temporalmente los valores de la matriz copia en la enmascarada

        ImprimeMatriz(Amascara);

        Amascara[X1-1][Y1-1] = "*****"; // Devuelve su estado original de la palabra
        Amascara[X2-1][Y2-1] = "*****"; // Devuelve su estado original de la palabra

        fallaste = false; // Regresa el valor a falso
    }
}

void Coordenadas(){
    printf("Introduzca el primer numero de la fila, entre 1 a %i:\t", ren);
    scanf("%i", &X1);

    printf("Introduzca el primer numero de la columna, entre 1 a %i:\t", col);
    scanf("%i", &Y1);

    printf("Introduzca el segundo numero de la fila, entre 1 a %i:\t", ren);
    scanf("%i", &X2);

    printf("Introduzca el segundo numero de la columna, entre 1 a %i:", col);
    scanf("%i", &Y2);
}

void AgregarPuntaje() {
    if (turno) { puntajeJ1++; }
    else { puntajeJ2++; }
}

void PuntajeGeneral(){
    printf("El puntaje de %s es de %i\n", jugador1, puntajeJ1);
    printf("El puntaje de %s es de %i\n", jugador2, puntajeJ2);
}

void Continuar() {
    char op;
    bool temp = true;
    do {
        printf("Seguir jugando: ");
        fflush(stdin);
        scanf("%c", &op);

        switch(op) {
            case 's':
            case 'S':
                temp = false;
                break;
            case 'n':
            case 'N':
                printf("FIN DE LA PARTIDA\n");
                PuntajeGeneral();
                _exit(0);
            default:
                printf("No se entiende el caracter\n");
                printf("S/s para si\nN/n para no\n");
        }
    } while(temp);
}

void FinDelJuego(char* Amascara[ren][col]) {
    int contador = 0;
    for (int i = 0; i < ren; i++){
        for (int j = 0; j < col; j++) {
            if(Amascara[i][j] != "*****"){
                contador++;
            }
        }
    }

    if(contador == tamMatriz) { // Comprueba si todas las tarjetas han sido desbloqueadas
        printf("FIN DEL JUEGO\n");
        if(puntajeJ1 == puntajeJ2){ printf("EMPATE\n"); }
        else if(puntajeJ1 > puntajeJ2){ printf("%s es el ganador con %i\n", jugador1, puntajeJ1); }
        else{ printf("%s es el ganador con %i\n", jugador2, puntajeJ2); }
        system("PAUSE");
        _exit(0);
    }
}

void ComprobarDimensionMatriz() {
    if(tamMatriz%2 == 0 && tamMatriz <= 36) {  printf("Matriz es par, es jugable\n"); }
    else { printf("El tamaño de la matriz debe ser par o menor a 36 cartas, favor de checarla"); _exit(0); }
}

void Bienvenida(){
    printf("BIENVENIDOS AL JUEGO DEL MEMORAMA\n");
    printf("Introduzca el nombre del primer jugador: ");
    scanf("%s.\n", jugador1);
    printf("Introduzca el nombre del segundo jugador: ");
    scanf("%s.\n", jugador2);
}

void main() {
    ComprobarDimensionMatriz(); // Comprobar tamaño de la matriz para saber si es par

    CrearMatriz(listaDeCaracteres, matrizDeCaracteres); // Crea matriz principal con posiciones aleatorias
    CopiarMatriz(matrizDeCaracteres, copiaMatrizDeCaracteres); // Copiamos la matriz original
    EnmascararMatriz(matrizDeCaracteres); // Enmascaramos la matriz original "*****"

    Bienvenida(); // Bienvenida del juego, pregunta nombres de los jugadores

    while (true) {
        ImprimeMatriz(copiaMatrizDeCaracteres); // Muestra las respuestas de las palabras
        PuntajeGeneral(); // Puntaje actual
        ImprimeMatriz(matrizDeCaracteres); // Muestra la matriz del juego

        if (turno) { printf("El turno es de: %s\n", jugador1); }
        else { printf("El turno es de: %s\n", jugador2); }

        Coordenadas(); // X1, Y1, X2, Y2 coordenadas
        DesenmascararMatriz(copiaMatrizDeCaracteres, matrizDeCaracteres); // Comprobamos los pares
        DestaparPalabrasTemp(copiaMatrizDeCaracteres, matrizDeCaracteres); // Muestra las palabras falladas

        FinDelJuego(matrizDeCaracteres); // Comprueba si el juego ya acabó
        Continuar(); // Pregunta al usuario si desea seguir jugando
        system("cls"); // Limpia la consola
    }
}
