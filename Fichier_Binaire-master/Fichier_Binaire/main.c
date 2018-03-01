#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /*  Les classes de stockages

    Auto : Classe de stockages par defaut les variables on pour port� le bloc d'instruction dans le quelle elles ont �t� cr�ee
    Statique : Classe de stockages permettant de cr�e des variables doont la port�e est le bloque d'instruction en cours mais
    contrairement au variable auto, ne son pas d�truite lors de la sortie du bloque
    extern : Classe de sotckage utilis� dans les d�claration pour signaler que la variables ainsi d�clar� peut �tre d�fini dans un autre fichier que
    le fichier courant
    Register : Classe de stockage permettantr de cr�e une variable dont l'emplacement ce trouve dans un registre de microProcesseur
    Volatile : Classe de stockage utilis� lors de la programation syst�me
    Elle indique qu'une variable peut �tre modifi� en arri�re plan par un autre programme.
    */

typedef struct ddn
{
    int j;
    int m;
    int a;
}ddn;

typedef struct Cid {

    int NumCarte;
    char nom[20];
    char prenom[20];
    char sexe;
    ddn naissance;
    char ville[20];
} Cid;
void Ecriture(Cid * IDcarte);/* ftell example : getting size of a file */
void Lecture();
void ajouter(Cid * IDcarte);
void saisie(Cid * IDcarte);


int main()
{
    Cid IDcarte;
     int  Choix = 0;





    do {
        printf("Quelle type d'intearction voulez vous faire ?\n 1 : Ecrire dans le fichier. 2 : Lire le fichier. 3 : Ajouter. 4 : QUITTER");
        scanf ("%d",&Choix);
    switch (Choix)
    {
    case 1 :
        saisie(&IDcarte);
        Ecriture(&IDcarte);
        break;
    case 2 :
        Lecture();
        break;
    case 3 :
        saisie(&IDcarte);
        ajouter(&IDcarte);
        break;
    }
    }while (Choix != 4);

    return 0;
    /* ftell example : getting size of a file */
}

void saisie (Cid *IDcarte)
{

    printf ("Saisissez numero ");
    scanf ("%d",&IDcarte->NumCarte);
    printf ("Nom ");
    scanf ("%s",IDcarte->nom);
    fflush(stdin);
    printf ("prenom \n");
    scanf ("%s",IDcarte->prenom);
    fflush(stdin);
    printf("JJ/MM/AA \n");
    scanf ("%d%d%d",&IDcarte->naissance.j,&IDcarte->naissance.m,&IDcarte->naissance.a);
    printf("Ville \n");
    scanf("%s",IDcarte->ville);
    fflush(stdin);
}

void Ecriture (Cid *IDCarte)
{

    FILE *MonFichier;
    MonFichier = fopen("MonFichier.bin", "wb");
    char buffer[sizeof(Cid)];
    memcpy(buffer, &(*IDCarte), sizeof(Cid));

    if (MonFichier != NULL)
    {
        fwrite(buffer, sizeof(Cid), 1, MonFichier);
        fclose(MonFichier);
    }
    else
        printf ("echec de l'ouverture");
}

void Lecture()
{
    int i = 0;
    FILE *MonFichier;
    long lSize;
    Cid *buffer;
    size_t result;
    int NbCid = 0; // On suppose qu'il y ai pas de Cid dans le fichier

    MonFichier = fopen("MonFichier.bin", "rb");
    if (MonFichier == NULL)
    {
        fputs ("CA MARCHE PAS", stderr);
        exit (1);
    }

    // Obtient la taille du fichier
    fseek (MonFichier, 0, SEEK_END);   // non-portable
    lSize=ftell (MonFichier);
    rewind(MonFichier);

    // Alloue la m�moire pour tout le fichier
    buffer = (Cid*)malloc(sizeof(Cid)*lSize); // On alloue la taille qu'il faut
    if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}


    NbCid = lSize / sizeof(Cid); // On calcul le nombre de Cid dans le fichier

    //copie le file dans tout le buffer(Memoire tampon)
    result = fread(buffer, sizeof(Cid), NbCid, MonFichier); // Du coups ici on met NbFichier Cid dans le buffer
    if (result != NbCid) {fputs ("Reading error",stderr); exit (3);}

	// Et la on ecris

    for(i = 0; i < NbCid; ++i)
    {
        printf("Num Carte: %d\n", buffer[i].NumCarte);
        printf("Nom: %s\n", buffer[i].nom);
        printf("Prenom: %s\n", buffer[i].prenom);
        printf("Naissance: %d %d %d\n", buffer[i].naissance.j, buffer[i].naissance.m, buffer[i].naissance.a);
        printf("Ville: %s\n", buffer[i].ville);
    }
    fclose (MonFichier);
    free (buffer);
}

void ajouter (Cid * IDcarte){

    FILE *MonFichier;
    MonFichier = fopen("MonFichier.bin", "ab");
    char buffer[sizeof(Cid)];
    memcpy(buffer, &(*IDcarte), sizeof(Cid));

    if (MonFichier != NULL)
    {
        fwrite(buffer, sizeof(Cid), 1, MonFichier);
        fclose(MonFichier);
    }
    else
        printf ("echec de l'ouverture");
}




