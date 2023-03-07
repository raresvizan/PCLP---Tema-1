#include <stdio.h>

void afisareCiclu(int i, int cutie[], int aparitii[]) {
    // verific daca ciclul este unul nou
    if (aparitii[i] == 0) {
        // vectorul ciclu[] retine ciclul ce trebuie afisat
        int ciclu[501], x = 0;
        int poz = i;
        aparitii[i] = 1;
        ciclu[x++] = i;
        // deschid cutii pana gasesc numarul prizonierului i
        while (cutie[poz] != i) {
            poz = cutie[poz];
            aparitii[poz] = 1;
            ciclu[x++] = poz;
        }
        printf("%d", ciclu[0]);
        for (int j = 1; j < x; j++) {
            printf(" %d", ciclu[j]);
        }
        printf("\n");
    }
}

int joc(int p, int cutie[]) {
    int i, gasit = 0;
    // gasit - nr prizonierilor care au gasit cutia
    for (i = 1; i <= p; i++) {
        /* poz -retin numarul din cutia deschisa anterior
           incercare -contor al nr de cutii deschise*/
        int poz = i;
        int incercare = p / 2;
        while (incercare > 0) {
            if (cutie[poz] == i) {
                gasit++;
                break;
            }
            poz = cutie[poz];
            incercare--;
        }
        // cazul: nu toti prizonierii isi gasesc cutia
        if (gasit != i) {
            return 0;
        }
    }
    // cazul: toti prizonierii isi gasesc cutia
    if (gasit == p) {
        return 1;
    }
    return 0;
}

int main() {
    // p -nr de prizonieri; cutie[]- vectorul de cutii
    int p, i, cutie[501];
    scanf("%d", &p);
    for (i = 1; i <= p; i++) {
        scanf("%d", &cutie[i]);
    }
    if (joc(p, cutie)) {
        printf("Da\n");
    } else {
        printf("Nu\n");
    }
    // folosesc un vector carcateristic pentru ca ciclurile afisate sa fie unice
    int aparitii[501] = {0};
    // incerc afisarea pentru fiecare prizonier
    for (i = 1; i <= p; i++) {
        afisareCiclu(i, cutie, aparitii);
    }
    return 0;
}