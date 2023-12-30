#include <stdio.h>

struct date {
    int j;
    int m;
    int a;
};

struct Personne {
    int num;
    char nom[20];
    char prenom[20];
    char adresse[100];
    char tel[8];
    struct date datenaiss;
};

struct Personne table[100];
int n = 0;

void ajout_personne() {
    printf("Donner le Num \n");
    scanf("%d", &table[n].num);
    printf("Donner le Nom \n");
    scanf("%s", table[n].nom);
    printf("Donner le Prenom \n");
    scanf("%s", table[n].prenom);
    printf("Donner l'adresse \n");
    scanf("%s", table[n].adresse);
    printf("Donner le telephone \n");
    scanf("%s", table[n].tel);
    printf("Donner la date de naissance \n");
    scanf("%d %d %d", &table[n].datenaiss.j, &table[n].datenaiss.m, &table[n].datenaiss.a);
    n++;
    printf("OPERATION D'AJOUT EFFECTUEE!,\n");
};

void modifier_coord() {
    int i;
    printf("donner le num de client à modifier");
    scanf("%d", &i);
    printf("Donner le Num \n");
    scanf("%d", &table[i].num);
    printf("Donner le Nom \n");
    scanf("%s", table[i].nom);
    printf("Donner le Prenom \n");
    scanf("%s", table[i].prenom);
    printf("Donner l'adresse \n");
    scanf("%s", table[i].adresse);
    printf("Donner le telephone \n");
    scanf("%s", table[i].tel);
    printf("Donner la date d'anniv \n");
    scanf("%d %d %d", &table[i].datenaiss.j, &table[i].datenaiss.m, &table[i].datenaiss.a);
};

void supprimer_personne() {
    int i;
    printf("donner le num de personne à supprimer");
    scanf("%d", &i);
    for (int j = i; j < n; j++) {
        table[j] = table[j + 1];
    }
    n--;
}

void recherchre_personne() {
    int i;
    printf("donner le num de client à chercher");
    scanf("%d", &i);

    int found = 0;
    for (int j = 0; j < n; j++) {
        if (table[j].num == i) {
            found = 1;
            printf("Num : %d\n", table[j].num);
            printf("Nom : %s\n", table[j].nom);
            printf("Prenom : %s\n", table[j].prenom);
            printf("Adresse : %s\n", table[j].adresse);
            printf("NumTel : %s\n", table[j].tel);
            printf("Date anniv : %d-%d-%d\n", table[j].datenaiss.j, table[j].datenaiss.m, table[j].datenaiss.a);
            break;
        }
    }

    if (!found) {
        printf("Non existant !\n");
    }
}

void affichage() {
    printf("NUM  |NOM                    |PRENOM         |ADRESSE                        |TEL          |ANNIVERSAIRE\n");
    printf("---------------------------------------------------------------------------------------\n");
    for (int j = 0; j < n; j++) {
        printf("%d      ", table[j].num);
        printf("%s                      ", table[j].nom);
        printf("%s                  ", table[j].prenom);
        printf("%s                ", table[j].adresse);
        printf("%s   ", table[j].tel);
        printf("%d-%d-%d\n", table[j].datenaiss.j, table[j].datenaiss.m, table[j].datenaiss.a);
        printf("---------------------------------------------------------------------------------------\n");
    }
}

void saveTableToFile(struct Personne *table, int n, const char *filename) {
    FILE *f = fopen(filename, "at");

    if (f == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    for (int i = 0; i < n; ++i) {
        fprintf(f, "%d %s %s %s %s %d-%d-%d\n", table[i].num, table[i].nom, table[i].prenom,
                table[i].adresse, table[i].tel, table[i].datenaiss.j, table[i].datenaiss.m, table[i].datenaiss.a);
    }

    fclose(f);
}

int main() {

    int choix;

    do {
        printf("GESTION DE L'ANNUAIRE \n");
        printf("* 1 *  Ajouter une personne \n");
        printf("* 2 *  Modifier les coordonnées d'une personne \n");
        printf("* 3 *  Supprimer une personne \n");
        printf("* 4 *  Rechercher une personne \n");
        printf("* 5 *  Afficher toutes les entrées  \n");
        printf("* 6 *  Quitter le programme\n");
        printf("Saisissez votre choix \n");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajout_personne();
                break;
            case 2:
                modifier_coord();
                break;
            case 3:
                supprimer_personne();
                break;
            case 4:
                recherchre_personne();
                break;
            case 5:
                affichage();
                break;
        }

    } while (choix != 6);
    saveTableToFile(table, n, "bordereau.txt");

    return 0;
}
