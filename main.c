/*projet Lotto Magique

*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_USERS  10000
#define MAX_L  50

//enregistrement des informations sur les participants

struct user {

    int id;
    char nom[MAX_L];
    char prenom[MAX_L];
    int listNum[5];

};

/*Prep : nb_users  est une variable entière et listUsers[] est un tableau de structure de type user (un tableau d’utilisateurs). nb_user et listUsers sont déclarés.
*Post : ListUser[] et nb_user sont initialisés. ListUser[] est un tableau qui contient tous les participants et leurs informations (ID, nom, prénoms, 5 numéros). nb_user est le nombre de participants.
*/

void encodageParticipants(int *nb_users, struct user listUsers[])
{
    int i=0;
    int j;
    int id=0;


    while ( (id !=-1) && (i<MAX_USERS))
    {
        printf("Nouveau participant: \n");
        printf("Entrez votre identifiant: \n");
        scanf("%d", &listUsers[i].id);

        id=listUsers[i].id;
        if(id !=-1)
        {
            printf("Entrez votre nom de famille: \n");
            scanf("%s",listUsers[i].nom);

            printf("Entrez votre prenom: \n");
            scanf("%s",listUsers[i].prenom);

            printf("Entrez vos 5 numeros: \n");

            char numero[50];
            char * numero_invalide;

            for ( j = 0; j < 5; j++)
            {
                printf("Entrez entrez votre numero %d \n", j + 1);
                scanf("%s", numero);
                listUsers[i].listNum[j] = strtol( numero, &numero_invalide, 10 );

                while (numero_invalide == numero || listUsers[i].listNum[j]< 1 || listUsers[i].listNum[j]>25 )
                {
                    printf( "Erreur, entrez un numero compris entre 1 et 25\n");
                    scanf("%s", numero);
                    listUsers[i].listNum[j] = strtol( numero, &numero_invalide, 10 );
                }

            }

            i++;
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        }
        else printf("Encodage terminé \n");


    }

    *nb_users =i;

}

//initialisation fréquences des numéros

/*Prep : listUser[] et nbUser sont initialisés. repetitionNumeros est un tableau d’entiers et est déclaré.
*Post :repetiotionNuméro est initialisé et  reprend la fréquences de chaque numéro joués (par l’ensemble des participants et en fin de journée).
*/

void initialisationFrequences(int nb_users, struct user listUsers[], int repetitionNumeros[26])
{
    int i,j,k;
    for ( i = 0; i < 26; i++)
    {
        repetitionNumeros[i] = 0;
    }

    for ( i = 1; i < 26; i++)
        for(j=0; j < nb_users ; j++ )
            for(k=0; k < 5 ; k++ )
            {
                if (listUsers[j].listNum[k] == i)
                    repetitionNumeros[i]++;
            }
}

// affichage des numéros et leurs fréquences

/*Prep : repetitionNumeros est initialisé
*Post : Affiche les numeros et leurs fréquences
*/

void affichageNumeros (int repetitionNumeros[26])
{
    int i;
    printf("Voici les numeros et leurs frequences: \n");
    for ( i = 1; i < 26; i++)
        printf("Le numero %d : %d fois \n", i, repetitionNumeros[i]);

}


//affichage premier gagnant et second gagant

/*Prep : nb_users, listUsers et repetitionNumeros sont initialisé
*Post : Les noms du premier  gagnant et du second gagnat sont  affichés.
*/

void affichageGagnants(int *nb_users, struct user listUsers[],int repetitionNumeros[26])
{
    int i,j;
    int sommeF;
    int sommeMin=50000;
    float moyenne;
    float moyenneG=0;
    float delta;
    float deltaMax=0;

    int PremierGagnant=0;
    int SecondGagnant=0;


    for ( i = 1; i < 26; i++)
        moyenneG = moyenneG + (i*repetitionNumeros[i]);

    moyenneG = moyenneG / (5*(*nb_users));


    for(i=0; i < *nb_users ; i++ )
    {
        sommeF=0;
        moyenne=0;
        for(j=0; j < 5 ; j++ )
        {

            sommeF = sommeF + repetitionNumeros[listUsers[i].listNum[j]];
            moyenne = moyenne + listUsers[i].listNum[j];
        }
        if(sommeF < sommeMin)
        {
            sommeMin=sommeF;
            PremierGagnant=i;
        }

        moyenne= moyenne/5;
        delta = moyenne-moyenneG;
        if(delta<0)
            delta= -delta;
        if(delta > deltaMax)
        {
            deltaMax=delta;
            SecondGagnant=i;
        }
    }


    printf("Le premier gagant est : %s %s \n", listUsers[PremierGagnant].nom, listUsers[PremierGagnant].prenom);
    printf("Le second gagant est : %s %s \n", listUsers[SecondGagnant].nom, listUsers[SecondGagnant].prenom);

}

int main(void)
{


    int nb_users;
    struct user listUsers[MAX_USERS];
    int repetitionNumeros[26];

    encodageParticipants(&nb_users, listUsers);
    initialisationFrequences(nb_users, listUsers, repetitionNumeros);
    affichageNumeros (repetitionNumeros);
    affichageGagnants(&nb_users, listUsers, repetitionNumeros);


    return EXIT_SUCCESS;
}