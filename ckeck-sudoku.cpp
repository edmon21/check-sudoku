//Pràctica 2 programacio
//Autor: Edmon Alcoceba Carbon

#include <stdio.h>

#define MAX 9
#define MIN 0

#define LEN 9

bool llegir(int matriu[LEN][LEN]){
    printf("Llegint sudoku...\n");
    int valor;

    for(int f = 0; f < LEN; f++){
        for(int c = 0; c < LEN; c++){
            //comprovar que no hi hagi cap número fora del rang
            //i que no hi hagi cap casella amb una entrada invàlida
            if((scanf("%d", &valor) != 1) || (valor > MAX) || (valor < MIN)){
                printf("Error de lectura a la casella %d, %d.\n", f + 1, c + 1);
                return false;
            }

            matriu[f][c] = valor;
        }
    }

    printf("Sudoku llegit.\n");
    return true;
}

bool fila_valida(int fila[LEN], int num_fila){
    for(int i = 0; i < LEN; i++){ 
        for(int j = i + 1; j < LEN; j++){  
            //comprobar si hi ha algun número repetit en una fila concreta del sudoku
            if(fila[i] == fila[j]){
                printf("El Sudoku té un error a la fila %d.\n", num_fila + 1);
                return false;
            }
        }
    }
    return true;
}

bool validar_files(int matriu[LEN][LEN]){
    for(int i = 0; i < LEN; i++){
        //comprobar que no hi hagi algun número repetit en totes les files del sudoku
        if(!fila_valida(matriu[i], i)){
            return false;
        }
    }
    return true;
}

bool columna_valida(int columna[LEN], int num_columna){
    for(int i = 0; i < LEN; i++){ 
        for(int j = i + 1; j < LEN; j++){
            //comprobar si ha algun numero repetit en una columna concreta del sudoku
            if(columna[i] == columna[j]){
                printf("El Sudoku té un error a la columna %d.\n", num_columna + 1);
                return false;
            }
        }
    }
    return true;
}

bool validar_columnes(int matriu[LEN][LEN]){
    for(int i = 0; i < LEN; i ++){
        int columna[LEN];
        for(int j = 0; j < LEN; j++){
            columna[j] = matriu[j][i];
        }
        //comprobar que no hi hagi algun número repetit en totes les columnes del sudoku
        if(!columna_valida(columna, i)){
            return false;
        }
    }
    return true;
}

bool regio_valida(int regio[3][3], int num_columna, int num_fila){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            for(int k = 0; k < 3; k++){
                for(int z = 0; z < 3; z++){
                    //comprobar si ha algun numero repetit en una regió concreta del sudoku
                    if((i != k || j != z) && regio[i][j] == regio[k][z]){
                        printf("El Sudoku té un error a la regió %d, %d.\n", num_columna + 1, num_fila +1);
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

bool validar_regions(int matriu[LEN][LEN]){
    for(int i = 0; i < 3; i ++){ // i representa bloc de files
        for(int j = 0; j < 3; j++){ //j representa bloc de columnes
            int regio[3][3];

            //comprobar que no hi hagi algun número repetit en totes les regions del sudoku
            for(int k = 0; k < 3; k++){
                for(int z = 0; z < 3; z++){
                    regio[k][z] = matriu[i * 3 + k][j * 3 + z];
                }
            }
            if(!regio_valida(regio, i, j)){
                return false;
            }
        }
    }
    return true;
}

void mostrar_sudoku(int matriu[LEN][LEN]) {
    int f, c;

    printf("\n");

    // linea superior del sudoku
    printf("#===#===#===#===#===#===#===#===#===#\n");

    for (f = 0; f < LEN; f++) {
        printf("[");  //començament de cada fila
        
        for (c = 0; c < LEN; c++) {
            printf(" %d ", matriu[f][c]);
            
            if ((c + 1) % 3 == 0 && c != LEN - 1) {
                printf("[");  //separació per blocs de 3
            } else if (c != LEN - 1) {
                printf("|");  //separació per columnes
            }
        }
        
        printf("[\n");  //final de cada fila

        //sepració de files per blocs
        if ((f + 1) % 3 == 0 && f != LEN - 1) {
            printf("#===#===#===#===#===#===#===#===#===#\n");
        } else if (f != LEN - 1) {
            printf("#---+---+---#---+---+---#---+---+---#\n");
        }
    }

    // linea inferior del sudoku
    printf("#===#===#===#===#===#===#===#===#===#\n");
    printf("\n");
}

int main() {
    int matriu[LEN][LEN];
    
    if (!llegir(matriu)) {
        return 1;
    } 

    mostrar_sudoku(matriu);

    if((!validar_files(matriu)) || (!validar_columnes(matriu)) || (!validar_regions(matriu))){
        printf("La solució al Sudoku és incorrecta.\n");
        return 1;
    }

    printf("La solució al Sudoku és correcta.\n");
    return 0;
}