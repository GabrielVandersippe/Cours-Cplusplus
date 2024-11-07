#include <iostream>
using namespace std;

struct IntStack20 {

    int stack [20];
    int indice_courant = -1;

    void Init() {
        for (int i = 0; i < 20; i++) {
            stack[i] = 0;
        }
    }

    void push(int x) {
        if (indice_courant >= 19) {
            cout << "Erreur : Stack Pleine" << endl;
        }
        else {
            indice_courant += 1;
            stack[indice_courant] = x;
        }
    }

    void pop() {
        if (indice_courant <= -1) {
            cout << "Erreur : Stack Vide" << endl;
        }
        else {
            indice_courant -= 1;
            cout << "Popped :" << stack[indice_courant] << endl;
        }
    }

    void empty() {
        cout << ((indice_courant == -1) ? "true" : "false") << endl;
    }

    void print() {
        cout << "[ ";
        for (int i = 0; i <= indice_courant; i++) {
            cout << stack[i] << " ";
        } cout << "]" << endl;
    }

};
   






int main() {

    cout << "Mon algorithme :" << endl;
    int tab[] = { 5, 8, 15, 6, 0 };

    cout << "Tableau avant tri :" << endl;

    for (int i = 0; i < 5; i++) {
         cout << tab[i] << endl ;
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

    struct Date {
    private:
        int day;
        int month;
        int year;
    
    public:
        void InitDate(int d, int m, int y) {
            (*this).day = d;
            (*this).month = m;
            (*this).year = y;
        }

        void AfficheDate() {
            cout << "Date : " << (*this).day << "/" << (*this).month << "/" << (*this).year << endl;
        }

        void SetDay(int d) {
            if ((0 <= d) && (d <= 30)) {
                this->day = d;
            }
            else { cout << "Erreur" << endl; }
        }
    };

    Date x;
    x.InitDate(7, 11, 2024);
    x.AfficheDate();

    x.SetDay(500);
    x.SetDay(8);
    x.AfficheDate();

    IntStack20 s;
    s.Init();
    s.push(5);
    s.push(50);
    s.push(65);
    s.pop();
    s.print();
}