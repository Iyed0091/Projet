#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    int i=0;

    double v;
    double tauxDecouvert=0.09;
    double tauxmvtdebit=0.00025;
    double tauxCPFD=0.0005;
    double agios=0;
    char choix=' ';
    int *a;
    struct date {
    int jj;
    int mm;
};

struct tableRow{
    char dateOp[100];
    char dateVal[100];
    double mvtDeb;
    double mvtCred;
    double soldeDeb;
    double soldeCred;
    int nbJours;
    double nbDebit;
    double nbCred;
    double tauxInt;
    double ID;
    double CPFD;
    double CD;
};

struct tableRow table[100];
void ajoutSomme(struct tableRow *table, int i, double v)
{   
    if (v > 0) {
        (table + i)->mvtCred = v;
    } else {
        (table + i)->mvtDeb = -v;  // Ensure mvtDeb is positive for consistency
    }

    if ((table+i-1)->soldeDeb>0)
    {
        if (v<0)
        {
            (table+i)->soldeDeb=(table+i-1)->soldeDeb-v;
        }
        if (v>0)
        {
            if (v>(table+i-1)->soldeDeb)
            {
                (table+i)->soldeCred=v-(table+i-1)->soldeDeb;
            }
            else
            {
                (table+i)->soldeDeb=(table+i-1)->soldeDeb-v;
            }
        }
    }

   if ((table+i-1)->soldeCred>0)
   {
        if (v>0)
        {
            (table+i)->soldeCred=(table+i-1)->soldeCred+v;
        }
        else
        {
            if (-v>(table+i-1)->soldeCred)
            {
                (table+i)->soldeDeb=(table+i-1)->soldeCred+v;
            }
            else
            {
                (table+i)->soldeCred= (table+i-1)->soldeCred+v;
            }
        }
   }






}



struct date convertirDate(char ch[100]) {
    int i = 0;
    struct date date;
    char ch1[3], ch2[3];  // Increase the array size to accommodate two digits for each component

    // Extract day
    ch1[0]=ch[0];
    ch1[1]=ch[1];
    ch2[0] = ch[3];
    ch2[1]=ch[4];
    date.jj=atoi(ch1);
    date.mm=atoi(ch2);
    return date;
}

int memois(struct tableRow *table,int i)
{
    struct date date1=convertirDate((table+i-1)->dateVal);
    struct date date2=convertirDate((table+i)->dateVal);
    int m1=date1.mm;
    int m2=date2.mm;
    return m1==m2;
}

int diffdDates(struct tableRow *table,int i)
{
    struct date date1=convertirDate((table+i-1)->dateVal);
    struct date date2=convertirDate((table+i)->dateVal);
    int m1=date1.mm;
    int m2=date2.mm;
    int j1=date1.jj;
    int j2=date2.jj;
    int result=(m2*30+j2)-(m1*30+j1);
    return result;

}

void calcCPFD(int *a, struct tableRow *table, int i)
{   int max=*a;
    for (int j=*a;j<i;j++)
    {
        if ((table+j)->soldeDeb>(table+max)->soldeDeb)
        {
            max=j;
        }
        
    }
    (table+max)->CPFD=(table+max)->soldeDeb*tauxCPFD;
    *a=(i+1);
}

int finTrimestre(struct tableRow t) {
    return (strcmp(t.dateVal, "30-09") == 0 || strcmp(t.dateVal, "31-03") == 0 || strcmp(t.dateVal, "31-12") == 0);
}

double calcAgios(struct tableRow *table,int i)
{
    double result=0;
    for (int j=0;j<i;j++)
    {
        result+=(table+i)->ID+(table+i)->CPFD+(table+i)->CD;
    }
    return result;
}

void saveTableToFile(struct tableRow *table, int size, const char *filename) {
    FILE *f = fopen(filename, "at");

    if (f == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    for (int i = 0; i < size; ++i) {
        fprintf(f, "%s %s %.2f %.2f %.2f %.2f %d %.2f %.2f %.2f %.2f %.2f %.2f\n",
                (table + i)->dateOp, (table + i)->dateVal, (table + i)->mvtDeb, (table + i)->mvtCred,
                (table + i)->soldeDeb, (table + i)->soldeCred, (table + i)->nbJours, (table + i)->nbDebit,
                (table + i)->nbCred, (table + i)->tauxInt, (table + i)->ID, (table + i)->CPFD, (table + i)->CD);
    }

    fclose(f);
    printf("Table saved to file successfully.\n");
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ... (previous code)

int main() {
    a = (int*)malloc(sizeof(int));
    *a = 0;

    do {
        printf("donner date valeur \n");
        scanf("%s", (table + i)->dateVal);
        printf("donner l'opération à effectuer \n");
        scanf("%lf", &v);

        if (i == 0) {
            if (v < 0) {
                table[i].mvtDeb = -v;
                table[i].mvtCred = 0;
                table[i].soldeCred = 0;
                table[i].soldeDeb = -v;
                table[i].nbJours = 0;
                table[i].nbCred = 0;
                table[i].nbDebit = 0;
                table[i].tauxInt = 0.09;
                table[i].ID = 0;
                table[i].CPFD = 0;
                table[i].CD = 0;
            } else {
                table[i].mvtDeb = 0;
                table[i].mvtCred = v;
                table[i].soldeCred = v;
                table[i].soldeDeb = 0;
                table[i].nbJours = 0;
                table[i].nbCred = 0;
                table[i].nbDebit = 0;
                table[i].tauxInt = 0.09;
                table[i].ID = 0;
                table[i].CPFD = 0;
                table[i].CD = 0;
            }
            } 

        else {
                if (agios != 0) {
                    ajoutSomme(table, i, agios);
                }
                ajoutSomme(table, i, v);
                table[i-1].nbJours = 0;
                table[i-1].nbDebit = 0;
                table[i-1].tauxInt = 0.09;
                table[i-1].ID = 0;
                table[i-1].CPFD = 0;
                table[i-1].CD = 0;
                int j = diffdDates(table, i);
                table[i-1].nbJours = j;
                table[i-1].nbCred = j * table[i-1].soldeCred;
                table[i-1].nbDebit = j * table[i-1].soldeDeb;
                table[i-1].ID = table[i-1].nbDebit * tauxDecouvert / 360;
                table[i-1].CD = table[i-1].mvtDeb * tauxmvtdebit;

                if (!memois(table, i)) {
                    calcCPFD(a, table, i - 1);
                 }

                 if (finTrimestre(table[i])) {
                    calcCPFD(a, table, i - 1);
                    agios = calcAgios(table, i - 1);
                    printf("******fin de Trimestre**********\n");
                    printf("***********AGIOS=%.2f\n*********",agios);
                }
            }

        i++;
        printf("Taper 'a' pour quitter !\n");
        scanf(" %c", &choix);

    } while (choix != 'a');

    free(a); // Free the allocated memory

    for (int k = 0; k < i; k++) {
    printf("DateVal  MVT DEB  MVTCRED   SOLDEDEB  SOLDECRED NBJOURS  NBREDEB  NBRECRED  TAUXINT  ID   CPFD     CD    \n ");
    printf("%-10s  %.2f    %.2f   %.2f    %.2f      %d      %.2f     %.2f    %.2f    %.2f    %.2f    %.2f\n",
           table[k].dateVal, table[k].mvtDeb, table[k].mvtCred, table[k].soldeDeb, table[k].soldeCred, table[k].nbJours,
           table[k].nbDebit, table[k].nbCred, table[k].tauxInt, table[k].ID, table[k].CPFD, table[k].CD);
    printf("****************************************************************************************************************************************************");
    printf("\n");
}

    saveTableToFile(table,i-1, "bordereau.txt");
    return 0;}//


