#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

// parametres du jeu
typedef struct
{
    int min;
    int max;
    int mina;
    int maxa;
    int vies;
} pjeux;

// variables du jeu
typedef struct
{
    int coups[2];
    int vies;
}  vjeux;

// nb a trouver du jeu
typedef struct
{
    int val1;
    int val2;
} nbjeux;

int mygeti (int *result,int mini,int maxi)
{
    char c, buff [ 13 ];
    fflush(stdin);
    return fgets(buff, sizeof buff, stdin) && !isspace(*buff) && sscanf(buff, "%d%c", result, &c) == 2 && (c == '\n' || c == '\0') && *result >= mini && *result <=maxi;
}

int oui_non(char* question)
{
    char rejouer;
    while (1 == 1)
    {
        fflush(stdin);
        printf("%s", question);
        scanf("%s", &rejouer);
        if (rejouer == '1' || rejouer == 'o' || rejouer =='O') return 1;
        if (rejouer == '0' || rejouer == 'n' || rejouer =='N') return 0;
    }
}

void affiche_result(int vies)
{
    if (vies >= 7) printf("\tvous etes tres fort !!\n\n");
    if (vies >= 5 && vies < 7) printf("\tvous etes fort !!\n\n");
    if (vies >= 2 && vies <5) printf("\tvous n'etes pas tres fort !!\n\n");
    if (vies >= 1 && vies <2) printf("\tvous etes nuls !!\n\n");
    if (vies == 0) printf("vous etes tres tres nul !!\n\n");

}

void affiche_resultat_jeux(vjeux *p_coups)
{
    int i,coups[3];
    for (i=1; i<3; i++)
    {
        coups[i]=p_coups[i].coups[0] + p_coups[i].coups[1];
    };
    if (coups[1] < coups[2])
    {
        /* joueur 1 gagant */
        printf("\nle joueur 1 est gagnant avec %d coups.\nLe joueur 2 est perdant avec %d coups.\n\n",coups[1],coups[2]);
    }
    else
    {
        if (coups[1] > coups[2])

        {
            /* joueur 2 gagant */
            printf("le joueur 2 est gagnant avec %d coups.\nLe joueur 1 est perdant avec %d coups.\n\n",coups[2],coups[1]);
        }
        else
        {
            /* egalité */
            printf("egalite entre les 2 joueurs avec %d coups\n",coups[1]);
        }
    }

}
// init parametres du jeu
pjeux param1(int niveau)
{
    pjeux temp;
    pjeux *p = &temp;

    switch (niveau)
    {
    case 1:
        p->min = 1;
        p->max=15;
        p->mina = 10;
        p->maxa=25;
        p->vies=10;
        break;
    case 2:
        p->min = 10;
        p->max=150;
        p->mina = 100;
        p->maxa=250;
        p->vies=15;
        break;
    case 3:
        p->min = 100;
        p->max=1500;
        p->mina = 1000;
        p->maxa=2500;
        p->vies=25;
        break;
    case 4:
        p->min = 1000;
        p->max=15000;
        p->mina = 10000;
        p->maxa=25000;
        p->vies=35;
        break;
    }

    return temp;
}

nbjeux saisir_nb( pjeux param, int joueur)
{
    int cps = 1, joueura = 0;
    nbjeux temp;
    switch (joueur)
    {
        case 1:
            joueura =2;
            break;
        case 2:
            joueura = 1;
            break;
    }
    printf("\njoueur %d:\n\n---choisir un nombre entre %d et %d---\n\n", joueura, param.min, param.max);
    do
    {
        printf("\tproposez votre choix: \n");
    }
    while(!mygeti(&temp.val1, param.min, param.max));
    printf("\njoueur %d:\n\n---choisir un nombre entre %d et %d---\n\n", joueura, param.mina, param.maxa);
    do
    {
        printf("\tproposez votre choix: \n");
    }
    while(!mygeti(&temp.val2, param.mina, param.maxa));
    return temp;

}
int mode_jeux(void)
{
    int nb_joueur;
    do
    {
        printf("\tchoisir mode 1 ou 2 joueurs.\n");
    }
    while(!mygeti(&nb_joueur, 1, 2));
    printf ("mode: %d joueur(s)\n\n",nb_joueur );
    return nb_joueur;
}

void display(vjeux *p_coups)
{
    int i,j;
    for (i=0; i<3; i++)
    {
        for (j=0; j<2; j++)
        {
            //printf("i=%d,j=%d,coups=%d,",i,j,p_coups[i].coups[j]);
        }
        //printf("vies=%d\n",p_coups[i].vies);
    }
}
void init_jeux(vjeux *p_coups,pjeux table_param)
{


    int i,j;
    for (i=0; i<3; i++)
    {
        for (j=0; j<2; j++)
        {
            p_coups[i].coups[j]=0;
        }
        p_coups[i].vies=table_param.vies;
    }
}

int niveau_jeux(void)
{
    int niveau;
    do
    {
        printf("\tchoisir niveau:\n\nniveau 1: 1-15 et 10-25\nniveau 2: 10-150 et 100-250\nniveau 3: 100-1500 et 1000-2500\nniveau 4: 1000-15000 et 10000-25000\n");
    }
    while(!mygeti(&niveau, 1, 4));

    printf ("niveau choisi: %d\n",niveau );
    return niveau;
}

int jeux(int mini, int maxi, int xvies, int nb_a_trouver, int joueur, int num_question, vjeux *t_coups)
{
    int nombre, coups, nombreentrer;
    if (nb_a_trouver == 0)
    {
        srand(time(NULL));
        nombre = (rand() % (maxi - mini + 1)) + mini;
    }
    else
    {
        nombre = nb_a_trouver;
    }
    //coups = 0;
    nombreentrer = 0;

    if (joueur != 0) printf("joueur %d:\n\n",joueur);
    printf("\n---trouvez un nombre entre %d et %d---\n\n", mini, maxi);
    while(nombreentrer != nombre && t_coups[joueur].vies > 0)
    {
        do
        {
            printf("\tproposez votre choix: \n");
            printf("\til vous reste %d vies.\n", t_coups[joueur].vies);
        }
        while(!mygeti(&nombreentrer, mini, maxi));
        t_coups[joueur].coups[num_question]++;
        if (nombreentrer != nombre) t_coups[joueur].vies--;
        if (t_coups[joueur].vies == 2) printf("---attention vous n'avez plus que 2 vies !!---\n");
        if (t_coups[joueur].vies == 1) printf("---attention vous n'avez plus qu'une seule vie !!---\n");
        if (nombreentrer < nombre) printf("c'est plus !\n");
        if (nombreentrer > nombre) printf("c'est moins !\n");
    }
    //t_coups[joueur].vies=vies;
    if (joueur != 0) printf("joueur %d:\n",joueur);
    if (t_coups[joueur].vies > 0) printf("---vous avez trouver le bon nombre en %d coups et il vous reste %d vies!!---\n\n", t_coups[joueur].coups[num_question], t_coups[joueur].vies);
    else printf("---vous n'avez pas trouver le bon nombre en %d coups !!---\n\n    ---vous n'avez plus aucune vies !!---\n\n", t_coups[joueur].coups[num_question]);
    return t_coups[joueur].vies;
}

void mono_joueur()
{
    int niveau, vies=0,rejouer=1;
    pjeux table_param;
    vjeux coups[3];
    vjeux *p_coups = &coups[0];


    niveau=niveau_jeux();
    while (rejouer == 1)
    {
        table_param = param1(niveau); // init param du jeu
        init_jeux(p_coups,table_param); //init compteurs
        vies = jeux(table_param.min, table_param.max, table_param.vies,0,0,0,p_coups);
        if (vies > 0) vies = jeux(table_param.mina, table_param.maxa, vies,0,0,1,p_coups);


        display(p_coups);

        affiche_result(vies);
        printf("et voila c'est fini !!\n\n");
        rejouer=oui_non("voulez-vous rejouer?\n\nSi oui tapez 1, o ou O sinon tapez 0, n ou N.\n");
    }
    return;
}

void bi_joueur()
{
    int niveau, vies=0,rejouer=1,joueur;
    pjeux table_param;
    nbjeux val_a_trouver;
    vjeux coups[3];
    vjeux *p_coups = &coups[0];

    while (rejouer == 1)
    {
        niveau=niveau_jeux();
        table_param = param1(niveau); // init param du jeu
        init_jeux(p_coups,table_param); //init compteurs
        for (joueur=1; joueur <=2; joueur++)
        {

            val_a_trouver = saisir_nb(table_param,joueur);
            vies = jeux(table_param.min, table_param.max, table_param.vies,val_a_trouver.val1,joueur,0,p_coups);
            if (vies > 0) vies = jeux(table_param.mina, table_param.maxa, vies,val_a_trouver.val2,joueur,1,p_coups);

            display(p_coups);


            affiche_result(vies);
            printf(" et voila c'est fini !!\n");
            printf("________________________\n\n");
        };

        affiche_resultat_jeux(p_coups);
        rejouer=oui_non("voulez-vous rejouer?\n\nsi oui tapez 1, o ou O sinon tapez 0, n ou N.\n");

    }
    return;

}

int main(void)
{
    int nb_joueur =0;

    nb_joueur=mode_jeux();
    switch (nb_joueur)
    {
    case 1:
        mono_joueur();
        break;
    case 2:
        bi_joueur();
        break;
    }

    return 0;

}




