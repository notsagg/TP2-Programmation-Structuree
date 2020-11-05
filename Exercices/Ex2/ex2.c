#include <stdio.h>
#include <stdlib.h>

int main() {
	const int TAILLE_MAX = 20;
	int matrice[TAILLE_MAX][TAILLE_MAX];
	int nbChances, nbLignes, nbColonnes;

	// 1. entrer de la taille de la matrice
	while ((nbLignes < 1 || nbLignes > TAILLE_MAX) && (nbLignes < 1 || nbLignes > TAILLE_MAX) && nbChances <= 3 ) {
		printf("Entrez le nombre de lignes: ");
		scanf("%d", &nbLignes);
		printf("Entrez le nombre de colonnes: ");
		scanf("%d", &nbColonnes);
	}

    // 2. échec si le nombre d'essais est dépassé
    if (nbChances > 3) {
        printf("Nombre de chances dépassées\n");
        return EXIT_FAILURE;
    }

    // 3. lecture des éléments du tableau
    int element = 0;
    for (int i = 0; i < nbLignes; ++i) {
    	for (int j = 0; j < nbColonnes; ++j) {
    		printf("Saisir l'élément [%d][%d] du tableau: ", i, j);
    		scanf("%d", &element);
    		matrice[i][j] = element;
    	}
    }

    // 4. affichage des éléments du tableau
    printf("\n");
    for (int i = 0; i < nbLignes; ++i) {
    	for (int j = 0; j < nbColonnes; ++j) {
			printf("V[%d][%d] = %d\n", i, j, matrice[i][j]);
    	}
    }

	return 0;
}