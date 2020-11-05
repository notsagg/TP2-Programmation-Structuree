#include <stdio.h>
#include <stdlib.h>

int main() {
	int TAILLE_MAX = 20;
	int tableau[TAILLE_MAX];
	int taille = 0;
	int nbChances = 1;

	// 1. entrer de la taille du tableau
    while (taille <= 0 && taille <= TAILLE_MAX && nbChances <= 3) {
        printf("Entrez la taille du tableau à générer: ");
        scanf("%d", &taille);
        nbChances += 1;
    }

    // 2. échec si le nombre d'essais est dépassé
    if (nbChances > 3) {
        printf("Nombre de chances dépassées\n");
        return EXIT_FAILURE;
    }

    // 3. lecture des éléments du tableau
    for (int i = 0; i < taille; ++i) {
    	printf("Saisir l'élément n°%d du tableau: ", i);
    	scanf("%d", &taille);
    	printf("\n");
    }

    // 4. affichage des éléments du tableau
    for (int i = 0; i < taille; ++i) {
    	printf("V[%d] = %d", i, tableau[i]);
    }

	return 0;
}