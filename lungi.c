#include <stdio.h>
#include <string.h>

void adunare(int n, char* a, char* b, char* rez) {
    int i, x = n / 2 - 1;
    char cifra = 0;
    for (i = n / 2 - 1; i > 0; i--) {
        cifra += a[i] + b[i] - '0';
        // daca rezultatul adunarii este de 2 cifre
        if (cifra > '9') {
            // scad -10 pentru a reveni la 0
            rez[x--] = cifra - 10;
            // retin 1 pentru al pune la urmatoarele cifre adunate
            cifra = 1;
        } else {
            rez[x--] = cifra;
            cifra = 0;
        }
    }
}

void scadere(int n, char* a, char* b, char* rez) {
    int i, x = n / 2 - 1;
    char cifra = 0;
    for (i = n / 2 - 1; i > 0; i--) {
        // exemplu caz: 2-7
        if (a[i] + cifra < b[i]) {
            cifra += 10 + a[i] - b[i] + '0';
            rez[x--] = cifra;
            // pun -1 pentru al scadea la urm. cifre
            cifra = -1;
        } else {
            cifra += a[i] - b[i] + '0';
            rez[x--] = cifra;
            cifra = 0;
        }
    }
}

// cand operatia este +
void operatorPlus(int n, char* real_a, char* real_b, char* img_a, char* img_b,
                  char* rez_real, char* rez_img) {
    // partea reala
    if (real_a[0] == '0') {
        if (real_b[0] == '0') {
            // pozitiv + pozitiv => adunare(semn +)
            adunare(n, real_a, real_b, rez_real);
            rez_real[0] = '0';
        } else {
            /* pozitiv + negativ => scadere in functie de care numar
               este mai mare */
            if (strcmp(real_a + 1, real_b + 1) >= 0) {
                // a > b => scadere(semn +)
                scadere(n, real_a, real_b, rez_real);
                rez_real[0] = '0';
            } else {
                // a < b => scadere(inversata semn -)
                scadere(n, real_b, real_a, rez_real);
                rez_real[0] = '1';
            }
        }
    } else {
        if (real_b[0] == '0') {
            /* negativ + pozitiv => scadere in functie de care numar
               este mai mare */
            if (strcmp(real_a + 1, real_b + 1) > 0) {
                // a > b => scadere(semn -)
                scadere(n, real_a, real_b, rez_real);
                rez_real[0] = '1';
            } else {
                // a < b => scadere(inversata semn +)
                scadere(n, real_b, real_a, rez_real);
                rez_real[0] = '0';
            }
        } else {
            // negativ + negativ => adunare(semm -)
            adunare(n, real_a, real_b, rez_real);
            rez_real[0] = '1';
        }
    }
    // fac exact la fel si pentru partea imaginara
    // partea imaginara
    if (img_a[0] == '0') {
        if (img_b[0] == '0') {
            // adunare(semn +)
            adunare(n, img_a, img_b, rez_img);
            rez_img[0] = '0';
        } else {
            if (strcmp(img_a + 1, img_b + 1) >= 0) {
                // scadere(semn +)
                scadere(n, img_a, img_b, rez_img);
                rez_img[0] = '0';
            } else {
                // scadere(inversata semn -)
                scadere(n, img_b, img_a, rez_img);
                rez_img[0] = '1';
            }
        }
    } else {
        if (img_b[0] == '0') {
            if (strcmp(img_a + 1, img_b + 1) > 0) {
                // scadere(semn -)
                scadere(n, img_a, img_b, rez_img);
                rez_img[0] = '1';
            } else {
                // scadere(inversata semn +)
                scadere(n, img_b, img_a, rez_img);
                rez_img[0] = '0';
            }
        } else {
            // adunare(semn -)
            adunare(n, img_a, img_b, rez_img);
            rez_img[0] = '1';
        }
    }
}

// cand operatia este -
void operatorMinus(int n, char* real_a, char* real_b, char* img_a, char* img_b,
                   char* rez_real, char* rez_img) {
    // partea reala
    if (real_a[0] == '0') {
        if (real_b[0] == '0') {
            /* pozitiv - pozitiv => scadere in functie de care numar
               este mai mare */
            if (strcmp(real_a + 1, real_b + 1) >= 0) {
                // a > b => scadere(semn +)
                scadere(n, real_a, real_b, rez_real);
                rez_real[0] = '0';
            } else {
                // a < b => scadere(inversata semn -)
                scadere(n, real_b, real_a, rez_real);
                rez_real[0] = '1';
            }
        } else {
            // pozitiv - negativ => adunare(semn +)
            adunare(n, real_a, real_b, rez_real);
            rez_real[0] = '0';
        }
    } else {
        if (real_b[0] == '0') {
            // negativ - pozitiv => adunare(semn -)
            adunare(n, real_a, real_b, rez_real);
            rez_real[0] = '1';
        } else {
            /* negativ - negativ => scadere in functie de care numar
               este mai mare */
            if (strcmp(real_a + 1, real_b + 1) > 0) {
                // a > b => scadere(semn -)
                scadere(n, real_a, real_b, rez_real);
                rez_real[0] = '1';
            } else {
                // a < b => scadere(inversata semn+)
                scadere(n, real_b, real_a, rez_real);
                rez_real[0] = '0';
            }
        }
    }
    // fac exact la fel si pentru partea imaginara
    // partea imaginara
    if (img_a[0] == '0') {
        if (img_b[0] == '0') {
            if (strcmp(img_a + 1, img_b + 1) >= 0) {
                // scadere(semn +)
                scadere(n, img_a, img_b, rez_img);
                rez_img[0] = '0';
            } else {
                // scadere(inversata semn -)
                scadere(n, img_b, img_a, rez_img);
                rez_img[0] = '1';
            }
        } else {
            // adunare(semn +)
            adunare(n, img_a, img_b, rez_img);
            rez_img[0] = '0';
        }
    } else {
        if (img_b[0] == '0') {
            // adunare(semn -)
            adunare(n, img_a, img_b, rez_img);
            rez_img[0] = '1';
        } else {
            if (strcmp(img_a + 1, img_b + 1) > 0) {
                // scadere(semn -)
                scadere(n, img_a, img_b, rez_img);
                rez_img[0] = '1';
            } else {
                // scadere(inversata semn+)
                scadere(n, img_b, img_a, rez_img);
                rez_img[0] = '0';
            }
        }
    }
}

int main() {
    int n;
    char a[1001], b[1001], operatie;
    char real_a[501], real_b[501], img_a[501], img_b[501];
    // operatie - retin semnul citit: + sau -
    scanf("%d", &n);
    scanf("%s", a);
    getchar();
    scanf("%c", &operatie);
    while (operatie != '0') {
        /* voi memora rezultatul operatiei pentru partea reala in rez_real[]
           si pentru partea imaginara in rez_img[]*/
        char rez_real[1001] = {0}, rez_img[1001] = {0};
        scanf("%s", b);
        /*separ numerele a,b in 4 vectori: parte reala a,b => real_a[], real_b[]
          si parte imaginara a,b => img_a[], img_b[] */
        strncpy(real_a, a, n / 2);
        strncpy(real_b, b, n / 2);
        strcpy(img_a, a + n / 2);
        strcpy(img_b, b + n / 2);
        /* atat la adunare cat si la scadere, cazurile difera in functie de
           semnul numerelor => am creat functii diferite */
        if (operatie == '+') {
            operatorPlus(n, real_a, real_b, img_a, img_b, rez_real, rez_img);
            /* dupa apelarea functiei rez_real[] si rez_img[] vor contine
               rezultatul operatiei*/
        } else if (operatie == '-') {
            operatorMinus(n, real_a, real_b, img_a, img_b, rez_real, rez_img);
            /* dupa apelarea functiei rez_real[] si rez_img[] vor contine
               rezultatul operatiei*/
        }
        // pun in a[] rezultatele obtinute
        strcpy(a, rez_real);
        strcat(a, rez_img);
        // afisez rezultatul operatiei
        printf("%s\n", a);
        getchar();
        // citesc noul semn de operatie sau 0
        scanf("%c", &operatie);
    }
}