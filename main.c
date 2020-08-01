#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<conio.h>
#include <stdbool.h>
#define MAX 30

/*
    MADE BY : LOBE T. F. LOIC -- UNIVERSITE COSENDAI DOUALA CAMEROUN
*/

/// voiture.dat --> fichier qui contient de toutes les voitures du parc

///------------- Structure
typedef struct Voiture{
    char matricule[MAX];
    char modele[MAX];
    int kilo;
    char etat; // L ou D
}Voiture;

Voiture voitures;
FILE *fp, *ft_1, *ft_2;
int choix, i=0;
char ch, ch1[MAX];
bool checking;
const char type_fichier[4] = ".bin";
char nom_fichier[MAX-4]; /// nom du fichier de sauvegarde - l'extension (".bin")

void menu();
void Init(Voiture voitures, int n);
void Etat(char xMatricule[MAX], Voiture xVoitures);
void Etat_Parc();
void Location(char xMatricule[MAX], Voiture voitures);
void Retour(char xMatricule[MAX], Voiture xVoitures);
void save(char fichier[MAX], Voiture xVoitures);
void Ajout_Voitures(Voiture xVoitures, int n);

int main()
{
    system("cls");

    printf("\n\t------------------------- CREATION DU PARC DE VOITURES -------------------------\n");

    printf("\nCombien de vehicules voulez vous enregistrer(0 pour aucun enregistrement) ? ");
    scanf("%d", &choix);

    Init(voitures, choix);

    printf("\n\t------------------------- FIN CREATION PARC-------------------------\n");
   // Etat_Parc();


    main:
    system("cls");
    menu(); /// Menu
    //printf("\nMenu : ");
    scanf("\t%1d",&choix);

    fflush(stdin);
    system("cls");
    switch(choix){
        case 0:
            printf("\nETES VOUS SUR DE VOULOIR SORTIR(O/N) ? ");
            scanf(" %c", &ch);
            if(ch == 'n' || ch == 'N')
                goto main;
            break;
        case 1: //location de voiture
            printf("\n\t-------------------------LOCATION DE VOITURES-------------------------\n");

            printf("\nMatricule de la voiture ? ");
            scanf("%s", ch1);
            Location(ch1, voitures);

            printf("\n\t------------------------- FIN LOCATION DE VOITURES -------------------------\n");
            break;
        case 2: // retour d'une voiture
            printf("\n\t------------------------- RETOUR DE VOITURES -------------------------\n");

            printf("\nMatricule de la voiture ? ");
            scanf("%s", ch1);
            Retour(ch1, voitures);

            printf("\n\t------------------------- FIN RETOUR DE VOITURES -------------------------\n");
            break;
        case 3: // etat d'une voiture
            printf("\n\t------------------------- ETAT D\'UNE VOITURE -------------------------\n");

            printf("\nMatricule de la voiture ? ");
            scanf("%s", ch1);
            Etat(ch1, voitures);

            printf("\n\t------------------------- FIN ETAT D\'UNE VOITURE -------------------------******\n");
            break;
        case 4: // etat du parc de voiture
            printf("\n\t------------------------- ETAT DU PARC -------------------------\n");

            Etat_Parc();

            printf("\n\n\t------------------------- FIN ETAT DU PARC ---------------------\n");
            break;
        case 5:
            printf("\n\t------------------------- SAUVEGARDE DE L\'ETAT DU PARC -------------------------\n");// sauvegarder l'etat du parc

            printf("\nNOM DU FICHIER DE SAUVEGARDE : "); ///demande le nom du fichier de sauvegarde au user
            scanf("%s", nom_fichier);
            strcat(nom_fichier,type_fichier); /// nom_fichier = nom_fichier + ".bin"

            printf("\nINITIALISATION DE LA SAUVEGARDE...");
            save(nom_fichier,voitures);
            //delay(1000); /// temps d'attente 1000ms = 1s
            printf("\nFIN DE LA SAUVEGARDE...");

            printf("\n\t------------------------- FIN SAUVEGARDE DE L\'ETAT DU PARC -------------------------\n");
            break;
        case 6:
            printf("\n\t-------------------------  AJOUT VOITURE(S) -------------------------\n");

            printf("\nCombien de vehicules voulez vous ajouter ? ");
            scanf("%d", &choix);
            Ajout_Voitures(voitures, choix);

            printf("\n\n\t------------------------- FIN AJOUT VOITURE(S) -------------------------\n");
            break; // maintenance du parc automobile
    }
    return 0;
}

void menu(){
    printf("\n\t------------------------- MENU ------------------------- \n\n");
    printf("\t1 : Louer une voiture\n\n"); /// 1-location d'une voiture
    printf("\t2 : Retour une voiture\n\n"); /// 2-retour d'une voiture louer
    printf("\t3 : Etat d'une voiture\n\n"); /// 3- etat d'une voiture
    printf("\t4 : Etat du parc de voitures\n\n"); /// 4-etat du parc de voiture
    printf("\t5 : Sauvegarder l'etat du parc\n\n"); /// 5- sauvegarder l'etat  du parc dans le fichier
    printf("\t6 : Maintenance du parc automobile\n\n"); /// 6-maintenance du parc automobile
    printf("\t0 : Fin du programme\n\n"); /// 0-location d'une voiture
}

void Init(Voiture xVoitures, int n)
{
    fp = fopen("voiture.dat", "ab");
    for(; i<n; i++)
    {
        printf("\tVoiture %d", i+1);
        printf("\nMatricule: ");
        scanf("%s", xVoitures.matricule);
        fflush(stdin);

        printf("Modele : ");
        scanf("%s", xVoitures.modele);
        fflush(stdin);

        printf("Kilometrage : ");
        scanf("%d", &xVoitures.kilo);
        fflush(stdin);

        do{
            printf("Etat(d=dispo / l=location) : ");
            scanf(" %c", &xVoitures.etat);
            fflush(stdin);
        }while(xVoitures.etat != 'd' && xVoitures.etat != 'l');

        fwrite(&xVoitures, sizeof(xVoitures),1,fp);

        printf("\n");
    }
    fclose(fp);
}

/// fonction pour : Location de la voiture
void Location(char xMatricule[MAX], Voiture xVoitures)
{
    ///ouverture des fichiers
    fp = fopen("voiture.dat", "rb"); /// fp = read -> voiture.dat
    ft_1 = fopen("temp_1.dat", "at"); /// ft_1 = append -> temp_1.dat
    ft_2 = fopen("temp_2.dat", "at+"); /// ft_2 = append + read -> temp_2.dat

    fflush(stdin);
    /// placer la pointeur au debut des files voiture.dat,temp_1.dat et temp_2.dat
    rewind(fp);
    rewind(ft_1);
    rewind(ft_2);

    ///test si le fichier voiture.dat est vide
    if(fp == NULL){
        printf("\nLe fichier n'existe pas");
    }

    ///lecture de fp -> voiture.dat
    while(fread(&xVoitures, sizeof(Voiture),1, fp))
    {
        ///test si le matriule entre se trouve dans le fichier
        if(stricmp(xMatricule, xVoitures.matricule) != 0) /// si non
        {
            ///remplir temp_1 avec les structures ou xVoiture.marque != de la valeur du matricule entree par le user
            fwrite(&xVoitures, sizeof(Voiture),1, ft_1);
        }
        else /// si oui
        {
             ///remplir temp_2 avec les structures ou xVoiture.marque == de la valeur du matricule entree par le user
            fwrite(&xVoitures, sizeof(Voiture),1, ft_2); /// le fichier avec la voiture qui a un matricule semblable
        }
    }
    ///Test si la voiture existe dans la parc
    if (NULL != ft_2) {
        fseek (ft_2, 0, SEEK_END);
            int size = ftell(ft_2);

        if (0 == size) {
            printf("\nLA VOITURE N\'EXISTE PAS DANS LA PARC !!!");
        }
    }

    /// mettre dans temp_1.dat, l'etat modifie de la voiture qui est dans temp_2.dat
    rewind(fp);
    rewind(ft_1);
    rewind(ft_2);

    /// Lecture de ft_2 -> temp_2
    while(fread(&xVoitures, sizeof(Voiture),1, ft_2))
    {
        /// test si la voiture est disponible
        if(xVoitures.etat == 'd')
        {
            xVoitures.etat = 'l'; /// changer l'etat de la voiture : elle devient en location
            fwrite(&xVoitures, sizeof(Voiture),1, ft_1); ///ecrire la nouvelle structure dans temp_1
            printf("LOCATION DE LA VOITURE : %s EFFECTUE AVEC SUCCES !!!", xVoitures.matricule); ///afficher le message de succes au user
        }
        /// test si la voiture n'est pas disponible : en location
        else
        {
            printf("\n\tLA VOITURE : %s EST DEJA EN LOCATION !!!", xVoitures.matricule); ///afficher au user que la voiture est deja en location
            fwrite(&xVoitures, sizeof(Voiture),1, ft_1);  ///ecrire la nouvelle structure dans temp_1
            break;
        }
    }

    ///fermeture des fichiers
    fclose(fp);
    fclose(ft_1);
    fclose(ft_2);

    remove("voiture.dat"); ///supprimer voiture.dat
    remove("temp_2.dat"); ///supprimer voiture.dat
    rename("temp_1.dat", "voiture.dat"); ///renommer temp_1 par voiture.dat
}

/// fonction pour : RETOUR de la voiture
void Retour(char xMatricule[MAX], Voiture xVoitures)
{
    ///puverture des fichiers
    fp = fopen("voiture.dat", "rb"); /// fp = read -> voiture.dat
    ft_1 = fopen("temp_1.dat", "at"); /// ft_1 = append -> temp_1.dat
    ft_2 = fopen("temp_2.dat", "at+"); /// ft_2 = append + read -> temp_2.dat

    fflush(stdin);
    /// placer la pointeur au debut des files voiture.dat,temp_1.dat et temp_2.dat
    rewind(fp);
    rewind(ft_1);
    rewind(ft_2);

    ///test si le fichier voiture.dat est vide
    if(fp == NULL){
        printf("\nLe fichier n'existe pas");
    }

    ///lecture de fp -> voiture.dat
    while(fread(&xVoitures, sizeof(Voiture),1, fp))
    {
        ///test si le matriule entre se trouve dans le fichier
        if(stricmp(xMatricule, xVoitures.matricule) != 0) /// si non
        {
            ///remplir temp_1 avec les structures ou xVoiture.marque != de la valeur du matricule entree par le user
            fwrite(&xVoitures, sizeof(Voiture),1, ft_1);
        }
        else /// si oui
        {
             ///remplir temp_2 avec les structures ou xVoiture.marque == de la valeur du matricule entree par le user
            fwrite(&xVoitures, sizeof(Voiture),1, ft_2); /// le fichier avec la voiture qui a un matricule semblable
        }
    }
    ///Test si la voiture existe dans la parc
    if (NULL != ft_2) {
        fseek (ft_2, 0, SEEK_END);
            int size = ftell(ft_2);

        if (0 == size) {
            printf("\nLA VOITURE N\'EXISTE PAS DANS LA PARC !!!");
        }
    }

    /// mettre dans temp_1.dat, l'etat modifie de la voiture qui est dans temp_2.dat
    rewind(fp);
    rewind(ft_1);
    rewind(ft_2);

    /// Lecture de ft_2 -> temp_2
    while(fread(&xVoitures, sizeof(Voiture),1, ft_2))
    {
        /// test si la voiture est en location
        if(xVoitures.etat == 'l')
        {
            xVoitures.etat = 'd'; /// changer l'etat de la voiture : elle devient disponible
            fwrite(&xVoitures, sizeof(Voiture),1, ft_1); ///ecrire la nouvelle structure dans temp_1
            printf("RETOUR DE LA VOITURE : %s EFFECTUE AVEC SUCCES !!!", xVoitures.matricule); ///afficher le message de succes au user
        }
        /// test si la voiture n'est pas en location : disponible
        else
        {
            printf("\n\tLA VOITURE : %s N\'ETAIT PAS EN LOCATION!!!", xVoitures.matricule); ///afficher au user que la voiture est deja en location
            fwrite(&xVoitures, sizeof(Voiture),1, ft_1);  ///ecrire la nouvelle structure dans temp_1
            break;
        }
    }

    ///fermeture des fichiers
    fclose(fp);
    fclose(ft_1);
    fclose(ft_2);

    remove("voiture.dat"); ///supprimer voiture.dat
    remove("temp_2.dat"); ///supprimer voiture.dat
    rename("temp_1.dat", "voiture.dat"); ///renommer temp_1 par voiture.dat
}

/// fonction pour : Etat d'une voiture
void Etat(char xMatricule[MAX], Voiture xVoitures)
{
    checking = false;
    fp = fopen("voiture.dat", "rb");
    fflush(stdin);

    rewind(fp);
    if(fp == NULL){
        printf("LE FICHIER EST VIDE !!!");
        exit(0);
    }

    while(fread(&xVoitures, sizeof(Voiture),1,fp) == 1 ){
        if(stricmp(xMatricule, xVoitures.matricule) == 0)
        {
            checking = true;
            printf("\nMatricule: %s\
                \nModele: %s\
                \nKilometrage: %d\
                \nEtat: %c\n",xVoitures.matricule,
                        xVoitures.modele,xVoitures.kilo,xVoitures.etat);
            fclose(fp);
            exit(0);
        }
    }
    if(checking == false)
        printf("\n\t LA VOITURE N'EXISTE PAS DANS LE PARC !!!");

    fclose(fp);
}

/// fonction pour : Etat du parc de voiture
void Etat_Parc()
{
    int nbre_voitures = 0;
    int nbre_V_location = 0;
    int nbre_V_dispo = 0;
    float nbre_kilo = 0;

    fp = fopen("voiture.dat", "rb");
    fflush(stdin);
    rewind(fp);

    if(fp == NULL){
        printf("Le fichier est vide");
        fclose(fp);
        exit(0);
    }

    printf("\n\t***************** LISTE DES VOITURES DISPONIBLES ***************\n");

    while(fread(&voitures, sizeof(Voiture),1,fp) == 1){
        nbre_voitures++;
        nbre_kilo = nbre_kilo + voitures.kilo;

        if(voitures.etat == 'd')
        {
            nbre_V_dispo++;
             printf("\n\tMatricule : %s", voitures.matricule);
        }
    }
    printf("\n\n\tNOMBRE TOTAL DE VOITURES DISPONIBLES: %d",nbre_V_dispo);
    printf("\n\n\t****************************************************************");

    rewind(fp);

    printf("\n\t***************** LISTE DES VOITURES EN LOCATION ***************\n");

    while(fread(&voitures, sizeof(Voiture),1,fp) == 1)
    {
        if(voitures.etat == 'l')
        {
            nbre_V_location++;
             printf("\n\tMatricule : %s", voitures.matricule);
        }
    }
    printf("\n\n\tNOMBRE TOTAL DE VOITURES EN LOCATION: %d",nbre_V_location);
    printf("\n\n\t****************************************************************");

    printf("\n\n\tNOMBRE TOTAL DE VOITURES : %d\
            \n\n\tKILOMETRAGE MOYEN : %.4f",nbre_voitures,nbre_kilo/nbre_voitures);

}

void Ajout_Voitures(Voiture xVoitures, int n)
{
    fp = fopen("voiture.dat", "ab");

    for(i = 0; i<n; i++)
    {
        printf("\tVoiture %d", i+1);
        printf("\nMatricule: ");
        scanf("%s", xVoitures.matricule);
        fflush(stdin);

        printf("Modele : ");
        scanf("%s", xVoitures.modele);
        fflush(stdin);

        printf("Kilometrage : ");
        scanf("%d", &xVoitures.kilo);
        fflush(stdin);

        do{
            printf("Etat(d=dispo / l=location) : ");
            scanf(" %c", &xVoitures.etat);
            fflush(stdin);
        }while(xVoitures.etat != 'd' && xVoitures.etat != 'l');

        fwrite(&xVoitures, sizeof(xVoitures),1,fp);
        printf("\n");
    }
    fclose(fp);
}

void save(char fichier[MAX], Voiture xVoitures)
{
    fp = fopen("voiture.dat", "rb");
    ft_1 = fopen(fichier, "ab");

    ///fwrite les voitures dispo
    while(fread(&xVoitures, sizeof(Voiture),1,fp)){
        if(xVoitures.etat == 'd'){
            fwrite(&xVoitures, sizeof(Voiture),1,ft_1);
        }
    }

    rewind(fp);
    ///fwrite les voitures en location
    while(fread(&xVoitures, sizeof(Voiture),1,fp)){
        if(xVoitures.etat == 'l'){
            fwrite(&xVoitures, sizeof(Voiture),1,ft_1);
        }
    }

    fclose(fp);
    fclose(ft_1);

}





