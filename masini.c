#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cerintaA(int n, char **combustibil, int *nr_masini) {
    /* fiecare element din nr_masini[] este asociat tipului de combustibil
       mentionat in main() */
    int i;
    for (i = 0; i < n; i++) {
        if (strcmp(combustibil[i], "benzina") == 0) {
            nr_masini[0]++;
        } else if (strcmp(combustibil[i], "motorina") == 0) {
            nr_masini[1]++;
        } else if (strcmp(combustibil[i], "hibrid") == 0) {
            nr_masini[2]++;
        } else if (strcmp(combustibil[i], "electric") == 0) {
            nr_masini[3]++;
        }
    }
}

void cerintaB(int n, char **brand, char **combustibil, double *consum, int *km,
              char **marca, int *n_marca, double *total_l, double *total_s) {
    int i, j, x = -1, exista = 0;
    /* verific daca brand-ul masinii exista deja in marca[][];
       daca nu, il introduc */
    for (i = 0; i < n; i++) {
        for (j = 0; j <= x; j++) {
            if (strcmp(marca[j], brand[i]) == 0) {
                // brand-ul exista deja in marca[][]
                exista = 1;
                // calculez consumul masinii si il adaug la consumul total
                double consum_masina = (double)((consum[i] * km[i]) / 100);
                total_l[j] += consum_masina;
                /* calculez suma platita in functie de tipul de combustibil
                   si o adaug la suma totala */
                if (strcmp(combustibil[i], "benzina") == 0 ||
                    strcmp(combustibil[i], "hibrid") == 0) {
                    total_s[j] += (double)(consum_masina * 8.02);
                } else if (strcmp(combustibil[i], "motorina") == 0) {
                    total_s[j] += (double)(consum_masina * 9.29);
                }
                // am gasit brand-ul in marca[][] deci opresc cautarea
                break;
            }
        }
        // brand-ul nu exista
        if (exista == 0) {
            x++;
            // il adaug in marca[][]
            marca[x] = malloc((strlen(brand[i]) + 1) * sizeof(char));
            strcpy(marca[x], brand[i]);
            // calculez consumul masinii si il adaug la consumul total
            total_l[x] = (double)((consum[i] * km[i]) / 100);
            /* calculez suma platita in functie de tipul de combustibil
                   si o adaug la suma totala */
            if (strcmp(combustibil[i], "benzina") == 0 ||
                strcmp(combustibil[i], "hibrid") == 0) {
                total_s[x] = (double)(total_l[x] * 8.02);
            } else if (strcmp(combustibil[i], "motorina") == 0) {
                total_s[x] = (double)(total_l[x] * 9.29);
            }
        }
        exista = 0;
    }
    // n_marca ia valoarea lui x - nr. de brand-uri distince
    *n_marca = x;
}

void cerintaC(int n, char **brand, char **numar, int *index) {
    int i, j;
    // verific fiecare numar de inmatriculare caracter cu caracter
    for (i = 0; i < n; i++) {
        // la final daca ok = 0 => invalid; ok = 1 => valid
        int ok = 0;
        j = 0;
        if (numar[i][j] >= 'A' && numar[i][j] <= 'Z') {
            j++;
            if (numar[i][j] >= 'A' && numar[i][j] <= 'Z') {
                // numarul are 2 litere la inceput
                j++;
                if (numar[i][j] >= '0' && numar[i][j] <= '9') {
                    j++;
                    if (numar[i][j] >= '0' && numar[i][j] <= '9') {
                        j++;
                        if (numar[i][j] >= '0' && numar[i][j] <= '9') {
                            // numarul are 3 cifre
                            j++;
                            if (numar[i][j] >= 'A' && numar[i][j] <= 'Z') {
                                j++;
                                if (numar[i][j] >= 'A' && numar[i][j] <= 'Z') {
                                    j++;
                                    if (numar[i][j] >= 'A' &&
                                        numar[i][j] <= 'Z') {
                                        /* verific ca numarul de inmatriculare
                                         * sa nu aiba prea multe carcatere */
                                        if (j == strlen(numar[i]) - 1) {
                                            ok = 1;
                                        }
                                    }
                                }
                            }
                        } else if (numar[i][j] >= 'A' && numar[i][j] <= 'Z') {
                            // numarul are 2 cifre
                            j++;
                            if (numar[i][j] >= 'A' && numar[i][j] <= 'Z') {
                                j++;
                                if (numar[i][j] >= 'A' && numar[i][j] <= 'Z') {
                                    /* verific ca numarul de inmatriculare
                                     * sa nu aiba prea multe carcatere */
                                    if (j == strlen(numar[i]) - 1) {
                                        ok = 1;
                                    }
                                }
                            }
                        }
                    }
                }
            } else if (numar[i][j] >= '0' && numar[i][j] <= '9') {
                // numarul are o litera la inceput
                j++;
                if (numar[i][j] >= '0' && numar[i][j] <= '9') {
                    j++;
                    if (numar[i][j] >= '0' && numar[i][j] <= '9') {
                        // numarul are 3 cifre
                        j++;
                        if (numar[i][j] >= 'A' && numar[i][j] <= 'Z') {
                            j++;
                            if (numar[i][j] >= 'A' && numar[i][j] <= 'Z') {
                                j++;
                                if (numar[i][j] >= 'A' && numar[i][j] <= 'Z') {
                                    /* verific ca numarul de inmatriculare
                                     * sa nu aiba prea multe carcatere */
                                    if (j == strlen(numar[i]) - 1) {
                                        ok = 1;
                                    }
                                }
                            }
                        }
                    } else if (numar[i][j] >= 'A' && numar[i][j] <= 'Z') {
                        // numarul are 2 cifre
                        j++;
                        if (numar[i][j] >= 'A' && numar[i][j] <= 'Z') {
                            j++;
                            if (numar[i][j] >= 'A' && numar[i][j] <= 'Z') {
                                /* verific ca numarul de inmatriculare
                                 * sa nu aiba prea multe carcatere */
                                if (j == strlen(numar[i]) - 1) {
                                    ok = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
        // numarul este invalid
        if (ok == 0) {
            index[i] = 1;
        }
    }
}

int main() {
    int n, i;
    /* construiesc 3 matrici char si 2 vectori int/double pentru a memora datele
       despre masini:
       brand - brandul masinilor
       numar - numarul de inmatriculare
       combustibil - tipul de combustibil
       consum - consumul de combustibil al masinii
       km - numarul de km al masinii */
    char **brand, **numar, **combustibil, cerinta;
    int *km;
    double *consum;
    // citesc n - numarul de masini
    scanf("%d", &n);
    // aloc dinamic memorie matricelor si vectorilor
    km = malloc(n * sizeof(int));
    consum = malloc(n * sizeof(double));
    brand = malloc(n * sizeof(char *));
    numar = malloc(n * sizeof(char *));
    combustibil = malloc(n * sizeof(char *));
    // fac un vector char in care citesc initial datele
    char citire[20];
    for (i = 0; i < n; i++) {
        scanf("%s", citire);
        // aloc dinamic si introduc datele despre brand
        brand[i] = malloc((strlen(citire) + 1) * sizeof(char));
        strcpy(brand[i], citire);
        scanf("%s", citire);
        // aloc dinamic si introduc datele despre numarul de inmatriculare
        numar[i] = malloc((strlen(citire) + 1) * sizeof(char));
        strcpy(numar[i], citire);
        scanf("%s", citire);
        // aloc dinamic si introduc datele despre combustibil
        combustibil[i] = malloc((strlen(citire) + 1) * sizeof(char));
        strcpy(combustibil[i], citire);
        // citesc datele despre consum
        scanf("%lf", &consum[i]);
        // citesc datele despre km
        scanf("%d", &km[i]);
    }
    getchar();
    // citesc cerinta - ce cerinta trebuie rezolvata (a, b sau c)
    scanf("%c", &cerinta);
    if (cerinta == 'a') {
        /* construiesc un vector in care retin cate masini au ca combustibil:
           nr_masini[0] - benzina
           nr_masini[1] - motorina
           nr_masini[2] - hibrid
           nr_masini[3] - electric */
        int *nr_masini;
        // aloc dinamic memorie si initializez vectorul cu 0
        nr_masini = calloc(4, 4 * sizeof(int));
        // rezolv cerinta a)
        cerintaA(n, combustibil, nr_masini);
        // afisez cerinta a)
        printf("benzina - %d\n", nr_masini[0]);
        printf("motorina - %d\n", nr_masini[1]);
        printf("hibrid - %d\n", nr_masini[2]);
        printf("electric - %d\n", nr_masini[3]);
        free(nr_masini);
    } else if (cerinta == 'b') {
        /* construiesc o matrice si 2 vectori:
           marca - brandul masinii
           total_l - numarul total de combustibil
           total_s - suma totala platita
           total_l si total_s sunt initializati cu 0 */
        char **marca;
        marca = malloc(n * sizeof(char *));
        double *total_s, *total_l;
        total_l = calloc(n, n * sizeof(double));
        total_s = calloc(n, n * sizeof(double));
        // n_marca - numarul de brand-uri distince
        int n_marca;
        // rezolv cerinta b)
        cerintaB(n, brand, combustibil, consum, km, marca, &n_marca, total_l,
                 total_s);
        // afisez cerinta b)
        for (i = 0; i <= n_marca; i++) {
            printf("%s a consumat %.2lf - %.2lf lei\n", marca[i], total_l[i],
                   total_s[i]);
        }
        free(marca);
        free(total_l);
        free(total_s);
    } else if (cerinta == 'c') {
        /* construiesc un vector carcateristic:
           index[i] = 0 => masina de indice i are numarul corect
           index[i] = 1 => masina de indice i are numarul invalid;
           index[] este initializat cu 0 */
        int *index, toate_corecte = 1;
        index = calloc(n, n * sizeof(int));
        // rezolv cerinta c)
        cerintaC(n, brand, numar, index);
        // afisez cerinta c)
        for (i = 0; i < n; i++) {
            if (index[i] == 1) {
                printf("%s cu numarul %s: numar invalid\n", brand[i], numar[i]);
                // am gasit un numar invalid
                toate_corecte = 0;
            }
        }
        // nu am gasit niciun numar invalid => toate numerele sunt corecte
        if (toate_corecte == 1) {
            printf("Numere corecte!\n");
        }
        free(index);
    }
    free(brand);
    free(numar);
    free(combustibil);
    free(consum);
    free(km);
}