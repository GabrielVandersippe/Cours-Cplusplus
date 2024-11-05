#include <iostream>
using namespace std;

int main() {
    cout << "Mon algorithme :" << endl;
    int tab[] = { 5, 8, 15, 6, 0 };

    cout << "Tableau avant tri :" << endl;

    for (int i = 0; i < 5; i++) {
        cout << tab[i] << endl;
    }

    for (int i = 0; i < 5; i++) {
        int mini = tab[i];
        int indice = i;

        for (int j = i; j < 5; j++) {

            if (tab[j] < tab[i]) {
                mini = tab[j];
                indice = j;
            }

            tab[indice] = tab[i];
            tab[i] = mini;
        }
    }

    cout << "Tableau après tri :" << endl;

    for (int i = 0; i < 5; i++) {
        cout << tab[i] << endl;
    }
}