#include "fourth.h"
// driver
// jesus take the wheel
int main(int argc, char ** argv) {
    FILE *input;
    input = fopen(argv[1], "r");

    if (input == NULL) {
        printf("error");
        return 0;
    }

    int M1; // defines how many lines to read until the next matrix
    int N1;

    fscanf(input, "%d\t%d\t\n", &M1, &N1);

    // malloc something here
    int ** mat1;
    mat1 = (int **) malloc(M1*sizeof(int *));

    int i,j;
    for (i = 0; i < M1; i++) {
        mat1[i] = (int *) malloc(N1*sizeof(int)); // malloc the rows
        for (j = 0; j < N1; j++) {
            fscanf(input, "%d", &mat1[i][j]); // store the numbers in each i,j element
        } 
    }

    int M2; // how many lines to read or we can just do until feof
    int N2;

    fscanf(input,"%d\t%d\t\n", &M2, &N2);

    int ** mat2;
    mat2 = (int **) malloc(M2*sizeof(int *));

    for (i = 0; i < M2; i++) {
        mat2[i] = (int *) malloc(N2*sizeof(int)); // malloc the rows
        for (j = 0; j < N2; j++) {
            fscanf(input, "%d", &mat2[i][j]); // store the numbers in each i,j element
        }
    }

    fclose(input);

    // resultant matrix
    // size n1 x m2
    int ** mat3;
    mat3 = (int **) calloc(M1,M1*sizeof(int *)); // use calloc so we can directly add to the resultant

    if (N1 != M2) {
        printf("bad-matrices");
        return 0;
    } else {
        mat3 = multiplyArrays(mat1, mat2, mat3, M1, N2, M2);
    }

    printArray(mat3, M1, N2);

    // free nested mallocs
    freeArray(mat1, M1);
    freeArray(mat2, M2);
    freeArray(mat3, M1);

    return 0;
}

int ** multiplyArrays(int ** matrixA, int ** matrixB, int ** resMatrix, int rows, int cols, int rows2) {
    // rows = M2 and is used to determine how many elements need to be multiplied in the resultant row 
    // mat multiplication rows * cols, rows * cols .... rows2
    int i,j,k;
    for (i = 0; i < rows; i++){
        resMatrix[i] = (int *) calloc(cols, cols * sizeof(int)); // malloc the rows, clearing them as we go
        for (j = 0; j < cols; j++) {
            for (k = 0; k < rows2; k++) {
                resMatrix[i][j] += matrixA[i][k] * matrixB[k][j];
            } 
        }
    }
    return resMatrix;
}

void freeArray(int ** matrix, int rows) {
    // free each row then free the top level pointer
    int i;
    for (i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void printArray(int ** matrix, int rows, int cols) {
    // printing is the same as scanning in this case
    int i,j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}