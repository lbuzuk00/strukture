#include <stdio.h>
#include <stdlib.h>


struct PolynomialTerm {
    double coefficient;
    int exponent;
};


int compare(const void *a, const void *b) {
    return ((struct PolynomialTerm*)b)->exponent - ((struct PolynomialTerm*)a)->exponent;
}

int main() {
  
    FILE *file = fopen("polynomial.txt", "r");
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return 1;
    }


    struct PolynomialTerm *polynomial = NULL;
    int termCount = 0;


    while (fscanf(file, "%lf %d", &polynomial[termCount].coefficient, &polynomial[termCount].exponent) == 2) {
        termCount++;


        polynomial = (struct PolynomialTerm *)realloc(polynomial, (termCount + 1) * sizeof(struct PolynomialTerm));
    }


    qsort(polynomial, termCount, sizeof(struct PolynomialTerm), compare);


    for (int i = 0; i < termCount; i++) {
        for (int j = i + 1; j < termCount; j++) {
            if (polynomial[i].exponent == polynomial[j].exponent) {
                polynomial[i].coefficient += polynomial[j].coefficient;
                
                polynomial[j].coefficient = 0;
            }
        }
    }

  
    for (int i = 0; i < termCount; i++) {
        if (polynomial[i].coefficient != 0) {
            printf("%.2fx^%d", polynomial[i].coefficient, polynomial[i].exponent);
            if (i < termCount - 1) {
                printf(" + ");
            }
        }
    }
    printf("\n");

  
    free(polynomial);


    fclose(file);

    return 0;
}
