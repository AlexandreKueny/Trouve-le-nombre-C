#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

int jeux(int mini, int maxi, int vies)
{
    int nombre, coups, nombreentrer;
    srand(time(NULL));
    nombre = (rand() % (maxi - mini + 1)) + mini;
    coups = 0;
    nombreentrer = 0;
    printf("---trouvez un nombre entre %d et %d---\n\n", mini, maxi);
    while(nombreentrer != nombre && vies > 0)
    {
        do
        {
            printf("\tproposez votre choix: \n");
            printf("\til vous reste %d vies.\n", vies);
        }
        while(!mygeti(&nombreentrer, mini, maxi));
        coups++;
        if (nombreentrer != nombre) vies--;
        if (vies == 2) printf("---attention vous n'avez plus que 2 vies !!---\n");
        if (vies == 1) printf("---attention vous n'avez plus qu'une seule vie !!---\n");
        if (nombreentrer < nombre) printf("c'est plus !\n");
        if (nombreentrer > nombre) printf("c'est moins !\n");
    }
    if (vies > 0) printf("---vous avez trouver le bon nombre en %d coups et il vous reste %d vies!!---\n\n", coups, vies);
    else printf("---vous n'avez pas trouver le bon nombre en %d coups !!---\n\n    ---vous n'avez plus aucune vies !!---\n\n", coups);
    return vies;
}
