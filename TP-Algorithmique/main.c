//
//  main.c
//  TP-Algorithmique
//
//  Created by Gaston Pelletier on 11/3/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define TAB_MAX 50
#define VALEUR_MAX 1000
#define VALEUR_MIN -1000

typedef struct timeval timeval;

#pragma mark - Prototypes
// prototype de fonctions de génération de tableaux
void genAleatoire(float*, int);
void genCroissant(float*, int);
void genDecroissant(float*, int);

// prototype de fonctions de tri
void triParSelection(float*, int);
void triABulle(float*, int);
void triParInsertion(float*, int);

// autres prototypes
double retournerStatistiques(timeval, timeval);
void afficher(float*);

#pragma mark - Main
int main(int argc, const char * argv[]) {
    float tab[TAB_MAX];
    timeval debut, fin;
    srand((int)time(0));
    int taille = 0;
    int type = 0;

    // 1. générer un tableau à trier
    // a. déterminer la taille du tableau à générer
    while (taille < 1 || taille > TAB_MAX) {
        printf("Entrez la taille du tableau à générer: ");
        scanf("%d", &taille);
    }

    // b. déterminer le type de tableau à générer
    printf("\n---------------------------------------------\n");
    printf("1 - Tableau avec ordre aléatoire\n");
    printf("2 - Tableau en ordre croissant\n");
    printf("3 - Tableau en ordre décroissant\n\n");

    // c. générer un tableau de taille `taille` de type `type`
    while (type != 1 && type != 2 && type != 3) {
        printf("Entrez le type de tableau désiré: ");
        scanf("%d", &type);
        getchar(); // suppresion du retour chariot

        // d. générer le tableau
        switch (type) {
            case 1:
                genAleatoire(tab, taille);
                break;
            case 2:
                genCroissant(tab, taille);
                break;
            case 3:
                genDecroissant(tab, taille);
                break;
            default: printf("Ce type de tableau n'existe pas\n\n");
        }
    }

    // e. affichage tu tableau généré
    printf("Tableau généré: \n");
    afficher(tab);

    // 2. trier le tableau
    printf("\n---------------------------------------------\n");
    printf("1 - Tri par sélection\n");
    printf("2 - Tri à bulle\n");
    printf("3 - Tri par insertion\n\n");

    double tempsTri[3]; // temps de tri pour chaque méthodes
    for (int i = 1; i <= 3; ++i) {
        type = i;

        // a. effectuer le tri
        switch (type) {
            case 1:
                gettimeofday(&debut, NULL);
                triParSelection(tab, taille);
                gettimeofday(&fin, NULL);
                break;
            case 2:
                gettimeofday(&debut, NULL);
                triABulle(tab, taille);
                gettimeofday(&fin, NULL);
                break;
            case 3:
                gettimeofday(&debut, NULL);
                triParInsertion(tab, taille);
                gettimeofday(&fin, NULL);
                break;
            default: return EXIT_FAILURE;
        }

        // b. afficher le résultat
        afficher(tab);

        // c. récupérer les statistiques de tri
        double tempRequis = retournerStatistiques(debut, fin);
        tempsTri[i] = tempRequis;
    }

    // d. afficher les statisques
    printf("\n---------------------------------------------\n");
    printf("  Méthode Employée    |     Temps de tri    ");
    printf("\n---------------------------------------------");

    for (int i = 1; i <= 3; ++i) {
        printf("\n          ");
        printf("%d", i);
        printf("           ");
        printf("|%12lf secondes", tempsTri[i-1]);
    }
    printf("\n---------------------------------------------\n\n");

    // 3. tableau trié avec succés
    return EXIT_SUCCESS;
}

#pragma mark - Tri
void triParSelection(float tab[], int taille) {
    for (int i = 0; i < taille; ++i) {
        int min = i;

        for (int j = i+1; j < taille; ++j) {
            if (tab[min] > tab[j]) {
                min = j;
            }
        }

        float aux = tab[min];
        tab[min] = tab[i];
        tab[i] = aux;
    }
}

void triABulle(float tab[], int taille) {
    for (int i = 0; i < taille-1; ++i) {
        for (int j = 0; j < taille-i-1; ++j) {

            if (tab[j] > tab[j+1]) {
                float aux = tab[j];
                tab[j] = tab[j+1];
                tab[j+1] = aux;
            }
        }
    }
}

void triParInsertion(float tab[], int taille) {
    for (int i = 1; i <= taille-1; ++i) {
        int j = i;
        while (j > 0 && tab[j-1] > tab[j]) {
            float aux = tab[j];
            tab[j] = tab[j-1];
            tab[j-1] = aux;
            --j;
        }
    }
}

#pragma mark - Outils
void genAleatoire(float tab[], int taille) {
    for (int i = 0; i < taille; ++i) {
        tab[i] = (VALEUR_MAX - VALEUR_MIN) * ((float)rand() / RAND_MAX) + VALEUR_MIN;
    }
}
void genCroissant(float tab[], int taille) {
    int maxPrecedent = VALEUR_MIN;
    int pas = (abs(VALEUR_MIN) + abs(VALEUR_MAX)) / taille;

    for (int i = 0; i < taille; ++i) {
        int valeurMin = maxPrecedent + 1;
        maxPrecedent = VALEUR_MIN + ((i+1) * pas);

        tab[i] = (maxPrecedent - valeurMin) * ((float)rand() / RAND_MAX) + valeurMin;
        // tab[i] = (rand() % (maxPrecedent - valeurMin + 1)) + valeurMin;
    }
}
void genDecroissant(float tab[], int taille) {
    int tabDecroissant[taille];
    genCroissant(tab, taille);

    // on génère un tableau croissant puis on inverse les éléments
    for (int i = 0; i < taille; ++i) {
        tabDecroissant[i] = tab[taille - i - 1];
    }
    for (int i = 0; i < taille; ++i) {
        tab[i] = tabDecroissant[i];
    }
}

double retournerStatistiques(timeval debut, timeval fin) {
    double tempRequis = (fin.tv_sec - debut.tv_sec) * 1e6;
    return (tempRequis + (fin.tv_usec - debut.tv_usec)) * 1e-6;
}
void afficher(float tab[]) {
    for (int i = 0; i < taille; ++i) {
        printf("%.2f ", tab[i]);
    }
    printf("\n");
}
