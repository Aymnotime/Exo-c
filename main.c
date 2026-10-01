#include <stdio.h>
#include "liste.h"

int main(void)
{
    Maillon *liste = NULL;
    for (int i = 1; i <= 5; i++)
        liste = liste_inserer(liste, i * 10);
    printf("blocs apres construction : %d\n", liste_blocs_en_circulation());

    printf("liste     : ");
    liste_afficher(liste);
    printf("longueur  : %d\n", liste_longueur(liste));
    printf("contient 30 : %s\n", liste_contient(liste, 30) ? "oui" : "non");

    int maximum = 0;
    if (liste_maximum(liste, &maximum))
        printf("maximum : %d\n", maximum);
    if (!liste_maximum(NULL, &maximum))
        printf("maximum liste vide : aucun\n");

    liste_liberer(liste);
    printf("blocs apres liberation : %d\n", liste_blocs_en_circulation());
    printf("liberee\n");
    return 0;
}
