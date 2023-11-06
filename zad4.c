#include <stdio.h>
#include <stdlib.h>

// Struktura za reprezentaciju pojedinog člana polinoma
struct PolinomClan {
    double koeficijent;
    int eksponent;
};

// Pomoćna funkcija za poređenje članova polinoma za sortiranje
int compare(const void *a, const void *b) {
    return ((struct PolinomClan*)b)->eksponent - ((struct PolinomClan*)a)->eksponent;
}

int main() {
    // Otvori datoteku za čitanje
    FILE *datoteka = fopen("polinom.txt", "r");
    if (datoteka == NULL) {
        printf("Nemoguće otvoriti datoteku.\n");
        return 1;
    }

    // Niz za čuvanje članova polinoma
    struct PolinomClan *polinom = NULL;
    int brojClanova = 0;

    // Učitavanje članova polinoma iz datoteke
    while (fscanf(datoteka, "%lf %d", &polinom[brojClanova].koeficijent, &polinom[brojClanova].eksponent) == 2) {
        brojClanova++;

        // Alociranje dodatne memorije po potrebi
        polinom = (struct PolinomClan *)realloc(polinom, (brojClanova + 1) * sizeof(struct PolinomClan));
    }

    // Sortiranje članova polinoma prema eksponentima
    qsort(polinom, brojClanova, sizeof(struct PolinomClan), compare);

    // Sumiranje koeficijenata za članove sa istim eksponentima
    for (int i = 0; i < brojClanova; i++) {
        for (int j = i + 1; j < brojClanova; j++) {
            if (polinom[i].eksponent == polinom[j].eksponent) {
                polinom[i].koeficijent += polinom[j].koeficijent;
                // Postavi koeficijent za duplikat na 0 kako bi se kasnije uklonio
                polinom[j].koeficijent = 0;
            }
        }
    }

    // Ispis sortiranog i sažetog polinoma
    for (int i = 0; i < brojClanova; i++) {
        if (polinom[i].koeficijent != 0) {
            printf("%.2fx^%d", polinom[i].koeficijent, polinom[i].eksponent);
            if (i < brojClanova - 1) {
                printf(" + ");
            }
        }
    }
    printf("\n");

    // Oslobađanje alocirane memorije
    free(polinom);

    // Zatvaranje datoteke
    fclose(datoteka);

    return 0;
}
