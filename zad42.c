#include <stdio.h>
#include <stdlib.h>

// Structure to represent an individual polynomial term
struct PolynomialTerm {
    double coefficient;
    int exponent;
};

// Helper function to compare polynomial terms for sorting
int compare(const void *a, const void *b) {
    return ((struct PolynomialTerm*)b)->exponent - ((struct PolynomialTerm*)a)->exponent;
}

int main() {
    // Open the file for reading
    FILE *file = fopen("polynomial.txt", "r");
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return 1;
    }

    // Array to store polynomial terms
    struct PolynomialTerm *polynomial = NULL;
    int termCount = 0;

    // Read polynomial terms from the file
    while (fscanf(file, "%lf %d", &polynomial[termCount].coefficient, &polynomial[termCount].exponent) == 2) {
        termCount++;

        // Allocate additional memory as needed
        polynomial = (struct PolynomialTerm *)realloc(polynomial, (termCount + 1) * sizeof(struct PolynomialTerm));
    }

    // Sort the polynomial terms by exponents
    qsort(polynomial, termCount, sizeof(struct PolynomialTerm), compare);

    // Combine coefficients for terms with the same exponent
    for (int i = 0; i < termCount; i++) {
        for (int j = i + 1; j < termCount; j++) {
            if (polynomial[i].exponent == polynomial[j].exponent) {
                polynomial[i].coefficient += polynomial[j].coefficient;
                // Set the coefficient for duplicates to 0 to remove them later
                polynomial[j].coefficient = 0;
            }
        }
    }

    // Print the sorted and simplified polynomial
    for (int i = 0; i < termCount; i++) {
        if (polynomial[i].coefficient != 0) {
            printf("%.2fx^%d", polynomial[i].coefficient, polynomial[i].exponent);
            if (i < termCount - 1) {
                printf(" + ");
            }
        }
    }
    printf("\n");

    // Free allocated memory
    free(polynomial);

    // Close the file
    fclose(file);

    return 0;
}
