#include <stdio.h>
#include <string.h>

void codificareA(char* s, char* cheie) {
    // m - nr linii matrice; n - nr coloane matrice
    int n = strlen(cheie), m = strlen(s);
    /* daca m divizibil cu n => nu este nevoie de o linie suplimentara
       daca m nu e divizibil cu n => este nevoie de o linie suplimentara */
    if (m % n == 0) {
        m = m / n + 1;
    } else {
        m = m / n + 2;
    }
    // construiesc matricea
    int i, j, x;
    char mat[500][500];
    for (j = 0; j < n; j++) {
        mat[0][j] = cheie[j];
    }
    i = 1, j = 0, x = 0;
    while (s[x] != '\0') {
        mat[i][j++] = s[x++];
        // conditia pentru a trece pe linie noua in matrice
        if (j == n && s[x] != '\0') {
            j = 0;
            i++;
        }
    }
    // pun spatiu in elementele matricei ramase libere
    while (j < n) {
        mat[i][j++] = ' ';
    }
    // imi initializez indicii pentru sortarea cheii
    int indice[500];
    for (i = 0; i < n; i++) {
        indice[i] = i;
    }
    // sortez cheia mutand doar elementele liniei 0 a matricei nu si restul
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (mat[0][i] > mat[0][j]) {
                int aux1 = indice[i];
                indice[i] = indice[j];
                indice[j] = aux1;
                char aux2 = mat[0][i];
                mat[0][i] = mat[0][j];
                mat[0][j] = aux2;
            }
        }
    }
    // acum indice[] contine ordinea de afisare codificata
    // rez[] va contine rezultatul codificarii
    char rez[500];
    x = 0;
    for (j = 0; j < n; j++) {
        for (i = 1; i < m; i++) {
            rez[x++] = mat[i][indice[j]];
        }
    }
    rez[x] = '\0';
    // pun rezultatul in s
    strcpy(s, rez);
}

void codificareB(char* s, int cheie) {
    int n = strlen(s), i;
    /* st[] - ultimele cheie caractere din sir care vor fi codificate
       dr[] - restul caracterelor din sir care doar se muta spre dreapta */
    char st[50], dr[450];
    strncpy(dr, s, n - cheie);
    strcpy(st, s + (n - cheie));
    /* construiesc un vector cu alfabetul cu urmatorii indici:
       A = 0, ..., Z = 25, a = 26, ..., z = 51 */
    char alfabet[52];
    for (i = 0; i < 26; i++) {
        alfabet[i] = 'A' + i;
    }
    for (i = 26; i < 52; i++) {
        alfabet[i] = 'a' + (i - 26);
    }
    // codific st[]
    for (i = 0; i < cheie; i++) {
        if (st[i] != ' ') {
            int tr_litera;
            // tr_litera - transform chr. din ASCII in indicele vectorului meu
            if (st[i] >= 'A' && st[i] <= 'Z') {
                tr_litera = st[i] - 'A';
            } else if (st[i] >= 'a' && st[i] <= 'z') {
                // in ASCII intre Z si a sunt 6 chr. care nu sunt litere
                tr_litera = st[i] - 'A' - 6;
            }
            /* restul din impartirea la 52 reprezinta cazul:
               z + 2 = B
               52 este numarul total de litere din alfabet[] */
            st[i] = alfabet[(tr_litera + cheie) % 52];
        }
    }
    // pun in s st[] - partea codificata si dr[] - partea mutata
    strcpy(s, st);
    strcat(s, dr);
    s[n] = '\0';
}

void decodificareA(char* s, char* cheie) {
    // m - linii; n - coloane (ca in codificare)
    int n = strlen(cheie), m = strlen(s);
    if (m % n == 0) {
        m = m / n + 1;
    } else {
        m = m / n + 2;
    }
    // imi initializez indicii pentru sortarea cheii
    int i, j, x;
    int indice[50];
    for (i = 0; i < n; i++) {
        indice[i] = i;
    }
    // sortez cheia
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (cheie[i] > cheie[j]) {
                char aux1 = cheie[i];
                cheie[i] = cheie[j];
                cheie[j] = aux1;
                int aux2 = indice[i];
                indice[i] = indice[j];
                indice[j] = aux2;
            }
        }
    }
    /* construiesc matricea: acum pun textul codificat pe coloane ([1][0],
       [2][0],...,[1][1],[2][1],...[1][n-1],[2][n-1],...,[m-1][n-1]) */
    char mat[11][50];
    for (j = 0; j < n; j++) {
        mat[0][j] = cheie[j];
    }
    i = 1, j = 0, x = 0;
    while (s[x] != '\0') {
        mat[i++][j] = s[x++];
        // conditia pentru a trece pe coloana noua in matrice
        if (i == m && s[x] != '\0') {
            i = 1;
            j++;
        }
    }
    // pun spatiu in elementele matricei ramase libere
    while (j < n) {
        while (i < m) {
            mat[i++][j] = ' ';
        }
        i = 1;
        j++;
    }
    /* observ ca indice[i] este de fapt pozitia pe care se afla i in indice2[];
       indice2[] - contine indicii corecti pentru decodificare
       exemplu: indice[0] = 3 => indice2[3] = 0 */
    int indice2[50];
    for (i = 0; i < n; i++) {
        indice2[indice[i]] = i;
    }
    // acum indice2[] contine ordinea de afisare decodificata
    // rez[] va contine rezultatul codificarii
    char rez[500];
    x = 0;
    for (i = 1; i < m; i++) {
        for (j = 0; j < n; j++) {
            rez[x++] = mat[i][indice2[j]];
        }
    }
    rez[x] = '\0';
    // pun rezultatul in s
    strcpy(s, rez);
}

void decodificareB(char* s, int cheie) {
    int n = strlen(s), i;
    /* st[] - restul caracterelor din sir care doar se muta spre stanga
       dr[] - primele cheie caractere din sir care vor fi decodificate */
    char st[450], dr[50];
    strcpy(st, s + cheie);
    strncpy(dr, s, cheie);
    // construiesc acelasi alfabet ca in codificare
    char alfabet[52];
    for (i = 0; i < 26; i++) {
        alfabet[i] = 'A' + i;
    }
    for (i = 26; i < 52; i++) {
        alfabet[i] = 'a' + (i - 26);
    }
    // decodific dr[]
    for (i = 0; i < cheie; i++) {
        if (dr[i] != ' ') {
            int tr_litera;
            // tr_litera - la fel ca in codificare
            if (dr[i] >= 'A' && dr[i] <= 'Z') {
                tr_litera = dr[i] - 'A';
            } else if (dr[i] >= 'a' && dr[i] <= 'z') {
                tr_litera = dr[i] - 'A' - 6;
            }
            /* restul din impartirea la 52 reprezinta cazul:
               z + 2 = B
               52 este numarul total de litere din alfabet[];
               deoarece scadem cheia, rezultatul poate fi negativ =>
               => adunam 52 la rezultat si vom face
               restul la impartirea la 52 iar
               exemplu caz: A - 2 = y */
            dr[i] = alfabet[(52 + (tr_litera - cheie) % 52) % 52];
        }
    }
    // pun in s st[] - partea mutata si dr[] - partea decodificata
    strcpy(s, st);
    strcat(s, dr);
    s[n] = '\0';
}

int main() {
    char s[500], cheie_A[50], operatie[15];
    int cheie_B;
    // citesc textul
    fgets(s, 500, stdin);
    s[strlen(s) - 1] = '\0';
    // citesc operatie - ce codificare/decodificare voi efectua
    scanf("%s", operatie);
    while (strcmp(operatie, "STOP") != 0) {
        if (strcmp(operatie, "CodificareA") == 0) {
            getchar();
            // citesc cheia
            fgets(cheie_A, 50, stdin);
            cheie_A[strlen(cheie_A) - 1] = '\0';
            // fac codificarea
            codificareA(s, cheie_A);
        } else if (strcmp(operatie, "CodificareB") == 0) {
            // citesc cheia
            scanf("%d", &cheie_B);
            // fac codificarea
            codificareB(s, cheie_B);
        } else if (strcmp(operatie, "DecodificareB") == 0) {
            // citesc cheia
            scanf("%d", &cheie_B);
            // fac decodificarea
            decodificareB(s, cheie_B);
        } else if (strcmp(operatie, "DecodificareA") == 0) {
            getchar();
            // citesc cheia
            fgets(cheie_A, 50, stdin);
            cheie_A[strlen(cheie_A) - 1] = '\0';
            // fac decodificarea
            decodificareA(s, cheie_A);
        }
        // afisez rezultatul
        puts(s);
        // citesc noua operatie
        scanf("%s", operatie);
    }
}