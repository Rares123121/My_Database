#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


typedef struct element {
    int id;
    char nume[256];
    int varsta;
    int numar_bani;
} element;

typedef struct baza {
    element *colectie;
    int dimensiune;
} baza;

void show(baza *a, int camp);///
void insert(baza *a, int campuri_noi);///
void delete(baza *a, int id_sters);///
void update(baza *a, int id, int suma_noua);///
void create(baza *a);///
void free_data(baza *a);
void sort_tabel_asccending(baza *a, char *criteriu);///sortez tabela dupa un anume criteriu
void sort_tabel_descscending(baza *a, char *criteriu);///
void statistics(baza *a, int camp, char operatie);//selecteaza toate datele de la campul respectiv
void disp_db(baza *a);
void export_to_CSV(baza *a, char *filename);

int main(){
    
    baza *h = malloc(sizeof(*h));// imi declar baza de date

    int n;
    printf("Introduce the number of persons: ");
    scanf("%d", &n);

    h->colectie = malloc(n * sizeof(element));
    h->dimensiune = n;

    create(h);

    int ok = 1;
    while(ok == 1){
        char command[256];
        printf("Choose a command:\n");
        printf("1. show\n");
        printf("2. insert\n");
        printf("3. delete\n");
        printf("4. update\n");
        printf("5. sort_asccending\n");
        printf("6. sort_desccending\n");
        printf("7. display\n");
        printf("8. statistics\n");
        printf("9. export\n");
        printf("10. exit\n");
        printf("Select command: ");
        scanf("%s", command);
        if(strcmp(command, "show") == 0){
            int camp;
            printf("What field do you want to select?\n");
            printf("1. ID\n");
            printf("2. Name\n");
            printf("3. Age\n");
            printf("4. Money Balance\n");
            scanf("%d", &camp);
            show(h, camp);
        } else if(strcmp(command, "insert") == 0){
            int new_persons;
            printf("How many persons do you want to add?\n");
            scanf("%d", &new_persons);
            insert(h, new_persons);
        } else if(strcmp(command, "delete") == 0){
            int del_pers;
            printf("What is the ID of the person you want to delete?\n");
            scanf("%d", &del_pers);
            delete(h, del_pers);
        } else if(strcmp(command, "update") == 0){
            int new_money, id;
            printf("What is the new amount and the ID?\n");
            scanf("%d %d", &new_money, &id);
            update(h, id, new_money);
        } else if(strcmp(command, "sort_asccending") == 0){
            char criteria[256];
            printf("Choose from: name, age or money\n");
            scanf("%s", criteria);
            sort_tabel_asccending(h, criteria);
        } else if(strcmp(command, "sort_desccending") == 0){
            char criteria[256];
            printf("Choose from: name, age or money\n");
            scanf("%s", criteria);
            sort_tabel_descscending(h, criteria);
        } else if(strcmp(command, "display") == 0){
            disp_db(h);
        } else if(strcmp(command, "statistics") == 0){
            char operrand;
            int field;
            printf("Choose a field:\n");
            printf("1. Age\n");
            printf("2. Money\n");
            scanf("%d", &field);
            printf("Choose an operation:\n");
            printf("+: make the sum of the column\n");
            printf("/: make the avarage of the column\n");
            scanf("%c", &operrand);
            statistics(h, field, operrand);
        } else if(strcmp(command, "exit") == 0){
            ok = 0;
            free_data(h);
        } else if(strcmp(command, "export") == 0){
            char filename[256];
            printf("Choose a name for the filename: ");
            scanf("%s", filename);
            export_to_CSV(h, filename);
        }
    }
    
    return 0;
}

void create(baza *a){
    //id nume varsta bani
    for(int i = 0; i < a->dimensiune; i++){
        a->colectie[i].id = i + 1;
        printf("For the person with the id %d introduce: name, age and money sum\n", i + 1);
        printf("Name: ");
        scanf("%s", a->colectie[i].nume);
        printf("\nAge: ");
        scanf("%d", &a->colectie[i].varsta);
        printf("\nMoney Sum: ");
        scanf("%d", &a->colectie[i].numar_bani);
        printf("\n");
    }
}

void show(baza *a, int camp){
    if(camp == 1) {//id
        printf("ID's are:\n");
        for(int i = 0; i < a->dimensiune; i++)
            printf("%d\n", a->colectie[i].id);
    }
    if(camp == 2) {//nume
        printf("Names are:\n");
        for(int i = 0; i < a->dimensiune; i++)
            printf("%d  %s\n", a->colectie[i].id, a->colectie[i].nume);
    }
    if(camp == 3) {//bani
        printf("Money balances are:\n");
        for(int i = 0; i < a->dimensiune; i++)
            printf("%d  %d\n", a->colectie[i].id, a->colectie[i].numar_bani);
    }
    if(camp == 4) {//varsta
        printf("Ages are:\n");
        for(int i = 0; i < a->dimensiune; i++)
            printf("%d  %d\n", a->colectie[i].id, a->colectie[i].varsta);
    }
    printf("\n");
}

void insert(baza *a, int campuri_noi){
    a->colectie = realloc(a->colectie, (campuri_noi + a->dimensiune) * sizeof(element));
    int aux = a->dimensiune;
    a->dimensiune = a->dimensiune + campuri_noi;
    for(int i = aux; i < a->dimensiune; i++)
        a->colectie[i].id = i + 1;

    for(int i = aux; i < a->dimensiune; i++){
        printf("For the person new added with the ID %d introduce: name, age and money sum\n", a->colectie[i].id);
        printf("Name: ");
        scanf("%s", a->colectie[i].nume);
        printf("\nAge: ");
        scanf("%d", &a->colectie[i].varsta);
        printf("\nMoney Balance: ");
        scanf("%d", &a->colectie[i].numar_bani);
        printf("\n");
    }
}

void delete(baza *a, int id_sters){
    if(a->dimensiune == 0){
        printf("There are no persons in the Data Base\n");
        return;
    }

    if(id_sters <= 0 || id_sters > a->dimensiune){
        printf("This person doesn't exist\n");
        return;
    }

    for(int i = id_sters; i < a->dimensiune - 1; i++){
        a->colectie[i] = a->colectie[i + 1];
    }
    a->colectie = realloc(a->colectie, (a->dimensiune - 1) * sizeof(element));
    a->dimensiune--;

    for(int i = id_sters; i < a->dimensiune; i++)
        a->colectie[i].id = i + 1;
}

void update(baza *a, int id, int suma_noua){
     if(id <= 0 || id > a->dimensiune){
        printf("This person doesn't exist\n");
        return;
    }

    printf("The new sum in the account on the name %s is %d", a->colectie[id - 1].nume, suma_noua);
    a->colectie[id - 1].numar_bani = suma_noua;
}

void sort_tabel_asccending(baza *a, char *criteriu){
    if(strcmp(criteriu, "name") == 0){
        for(int i = 0; i < a->dimensiune; i++)
            for(int j = i + 1; j < a->dimensiune; j++)
                if (strcmp(a->colectie[i].nume, a->colectie[j].nume) > 0) {
                    char name[1001];
                    strcpy(name, a->colectie[i].nume);
                    strcpy(a->colectie[i].nume, a->colectie[j].nume);
                    strcpy(a->colectie[j].nume, name);

                    int age = a->colectie[i].varsta;
                    a->colectie[i].varsta = a->colectie[j].varsta;
                    a->colectie[j].varsta = age;

                    int money = a->colectie[i].numar_bani;
                    a->colectie[i].numar_bani = a->colectie[j].numar_bani;
                    a->colectie[j].numar_bani = money;
                }
    } else if(strcmp(criteriu, "age") == 0){
        for(int i = 0; i < a->dimensiune; i++)
            for(int j = i + 1; j < a->dimensiune; j++)
                if (a->colectie[i].varsta > a->colectie[j].varsta) {
                    char name[1001];
                    strcpy(name, a->colectie[i].nume);
                    strcpy(a->colectie[i].nume, a->colectie[j].nume);
                    strcpy(a->colectie[j].nume, name);

                    int age = a->colectie[i].varsta;
                    a->colectie[i].varsta = a->colectie[j].varsta;
                    a->colectie[j].varsta = age;

                    int money = a->colectie[i].numar_bani;
                    a->colectie[i].numar_bani = a->colectie[j].numar_bani;
                    a->colectie[j].numar_bani = money;
                }
    } else if(strcmp(criteriu, "money") == 0){
        for(int i = 0; i < a->dimensiune; i++)
            for(int j = i + 1; j < a->dimensiune; j++)
                if (a->colectie[i].numar_bani > a->colectie[j].numar_bani) {
                    char name[1001];
                    strcpy(name, a->colectie[i].nume);
                    strcpy(a->colectie[i].nume, a->colectie[j].nume);
                    strcpy(a->colectie[j].nume, name);

                    int age = a->colectie[i].varsta;
                    a->colectie[i].varsta = a->colectie[j].varsta;
                    a->colectie[j].varsta = age;

                    int money = a->colectie[i].numar_bani;
                    a->colectie[i].numar_bani = a->colectie[j].numar_bani;
                    a->colectie[j].numar_bani = money;
                }
    }
}

void sort_tabel_desccending(baza *a, char *criteriu){
    if(strcmp(criteriu, "name") == 0){
        for(int i = 0; i < a->dimensiune; i++)
            for(int j = i + 1; j < a->dimensiune; j++)
                if (strcmp(a->colectie[i].nume, a->colectie[j].nume) < 0) {
                    char name[1001];
                    strcpy(name, a->colectie[i].nume);
                    strcpy(a->colectie[i].nume, a->colectie[j].nume);
                    strcpy(a->colectie[j].nume, name);

                    int age = a->colectie[i].varsta;
                    a->colectie[i].varsta = a->colectie[j].varsta;
                    a->colectie[j].varsta = age;

                    int money = a->colectie[i].numar_bani;
                    a->colectie[i].numar_bani = a->colectie[j].numar_bani;
                    a->colectie[j].numar_bani = money;
                }
    } else if(strcmp(criteriu, "age") == 0){
        for(int i = 0; i < a->dimensiune; i++)
            for(int j = i + 1; j < a->dimensiune; j++)
                if (a->colectie[i].varsta < a->colectie[j].varsta) {
                    char name[1001];
                    strcpy(name, a->colectie[i].nume);
                    strcpy(a->colectie[i].nume, a->colectie[j].nume);
                    strcpy(a->colectie[j].nume, name);

                    int age = a->colectie[i].varsta;
                    a->colectie[i].varsta = a->colectie[j].varsta;
                    a->colectie[j].varsta = age;

                    int money = a->colectie[i].numar_bani;
                    a->colectie[i].numar_bani = a->colectie[j].numar_bani;
                    a->colectie[j].numar_bani = money;
                }
    } else if(strcmp(criteriu, "money") == 0){
        for(int i = 0; i < a->dimensiune; i++)
            for(int j = i + 1; j < a->dimensiune; j++)
                if (a->colectie[i].numar_bani < a->colectie[j].numar_bani) {
                    char name[1001];
                    strcpy(name, a->colectie[i].nume);
                    strcpy(a->colectie[i].nume, a->colectie[j].nume);
                    strcpy(a->colectie[j].nume, name);

                    int age = a->colectie[i].varsta;
                    a->colectie[i].varsta = a->colectie[j].varsta;
                    a->colectie[j].varsta = age;

                    int money = a->colectie[i].numar_bani;
                    a->colectie[i].numar_bani = a->colectie[j].numar_bani;
                    a->colectie[j].numar_bani = money;
                }
    }
}

void disp_db(baza *a){
    printf("ID   Name    Age   Money\n");
    for(int i = 0; i < a->dimensiune; i++)
        printf("%d  %s    %d     %d\n", a->colectie[i].id, a->colectie[i].nume, 
                a->colectie[i].varsta, a->colectie[i].numar_bani);
}

void statistics(baza *a, int camp, char operatie){
    if(camp == 2){
        if(operatie == '+'){
            int suma = 0;
            for(int i = 0; i < a->dimensiune; i++)
                suma += a->colectie[i].varsta;
            printf("The sum is: %d\n", suma);
        }

        if(operatie == '/'){
            int suma = 0;
            for(int i = 0; i < a->dimensiune; i++)
                suma += a->colectie[i].varsta;
            
            float medie = suma * 1.0 / a->dimensiune;
            printf("The avarage is: %f\n", medie);
        }
    }

    if(camp == 3){
        if(operatie == '+'){
            int suma = 0;
            for(int i = 0; i < a->dimensiune; i++)
                suma += a->colectie[i].numar_bani;
            printf("The sum is: %d\n", suma);
        }

        if(operatie == '/'){
            int suma = 0;
            for(int i = 0; i < a->dimensiune; i++)
                suma += a->colectie[i].numar_bani;
            
            float medie = suma * 1.0 / a->dimensiune;
            printf("The avarage is: %f\n", medie);
        }
    }
}

void export_to_CSV(baza *a, char *filename){
    FILE *in = fopen(filename, "w");
    if(in == NULL){
        printf("Can't open this file.\n");
        return;
    }

    for(int i = 0; i < a->dimensiune; i++)
        fprintf(in, "%d, %s, %d, %d\n", 
                a->colectie[i].id,
                a->colectie[i].nume,
                a->colectie[i].varsta,
                a->colectie[i].numar_bani);

    fclose(in);
}

void free_data(baza *a){
    free(a->colectie);
    free(a);
}