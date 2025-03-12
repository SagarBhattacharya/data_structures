#include <stdio.h>
#include <stdlib.h>
#define MAX_DIMS 10
#define true 1
#define false 0

typedef struct matrix_t {
  int rows;
  int cols;
  int data[MAX_DIMS][MAX_DIMS];
} matrix;

matrix Matrix(char* name, int fill){
  int rows, cols;
  printf("%s\n", name);
  printf("Enter dimensions: \n");
  scanf("%d %d", &rows, &cols);

  if (rows > MAX_DIMS || cols > MAX_DIMS){
    fprintf(stderr, "Matrix dimensions exceed maximum dimensions\n");
    return (matrix) {0, 0};
  }

  int size = rows * cols;
  matrix m = {
    .rows = rows,
    .cols = cols,
  };

  if(fill){
    printf("Enter matrix elements : \n");
    for(int i = 0; i < m.rows; i++){
      for(int j = 0; j < m.cols; j++){
        scanf("%d", &m.data[i][j]);
      }
    }
  }

  return m;
}

int Add(matrix* result, matrix* a, matrix* b) {
  if(
    (a->rows != b->rows || a->cols != b->cols) ||
    (a->rows != result->rows || a->cols != result->cols)
  ){
    fprintf(stderr, "Matrices have different dimensions\n");
    return false;
  }

  for(int i = 0; i < a->rows; i++){
    for(int j = 0; j < a->cols; j++){
      result->data[i][j] = a->data[i][j] + b->data[i][j];
    }
  }

  return true;
}

int Multiply(matrix* result, matrix* a, matrix* b) {
  if(
    (a->cols != b->rows) ||
    (result->rows != a->rows || result->cols != b->cols)
  ){
    fprintf(stderr, "Matrices are not multipliable\n");
    return false;
  }

  for(int i = 0; i < a->rows; i++){
    for(int j = 0; j < b->cols; j++){
      for(int k = 0; k < a->cols; k++){
        result->data[i][j] += a->data[i][k] * b->data[k][j];
      }
    }
  }

  return true;
}

void Print(matrix m) {
  for(int i = 0; i < m.rows; i++){
    for(int j = 0; j < m.cols; j++){
      printf("%d ", m.data[i][j]);
    }
    printf("\n");
  }
}

int main() {
  matrix m = Matrix("Matrix 1", true);
  matrix n = Matrix("Matrix 2", true);
  matrix r = Matrix("Add Matrix", false);
  matrix p = Matrix("Product Matrix", false);

  if(Add(&r, &m, &n)){
    printf("Add Result\n");
    Print(r);
  }
  

  if(Multiply(&p, &m, &n)){
    printf("Multiply Result\n");
    Print(p);
  }
  return 0;
}