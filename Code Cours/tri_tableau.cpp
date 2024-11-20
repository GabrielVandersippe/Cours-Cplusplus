#include <iostream>
using namespace std;

struct IntStack20 {

    int stack[20];
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
 
struct Case {
    int elt = 0;
    Case* precedent = 0;
};

struct IntStackVariable {
    
    Case* head; 
    int longueur_max;
    int capacite;

    IntStackVariable (int n = NULL) {
        head = NULL;
        longueur_max = n; /*si longueur_max = NULL, on a une stack infinie*/
        capacite = 0;
    }

    ~IntStackVariable() {
        (*this).del();
    }

    void push(int i) {
        if (!longueur_max || (longueur_max>capacite)) {
            Case* suivant = new Case();
            (*suivant).elt = i;
            (*suivant).precedent = head;
            head = suivant;
            capacite += 1;
        }
        else {
            cout << "Stack Remplie !" << endl;
        }
    }

    void pop(int i = 1) {
        for (int j = 0; j < i; j++) {
            if (head != NULL) {
                cout << "Popped : " << (*head).elt << endl;
                Case* temp = (*head).precedent;
                delete head;
                head = temp;
                capacite -= 1;
            }
            else {
                is_empty();
                break;
            }
        }
    }

    void is_empty() {
        cout << ((head == NULL) ? "Stack is empty" : "Stack is not empty") << endl;
    }

    void print() {
        Case* temp = head; /*on note où est la fin de la pile*/
        while (temp != NULL) {
            cout << temp->elt << "->";
            temp = temp->precedent;
        }
        cout << "Origine" << endl;
    }

    void ajout_debut(int i) {
        if (!longueur_max || (longueur_max > capacite)) {
            Case* nouvelle = new Case();
            (*nouvelle).elt = i;
            (*nouvelle).precedent = NULL;

            if (head == NULL) {
                head = nouvelle;
            }
            else {
                Case* temp = head;
                while (temp->precedent) {
                    temp = temp->precedent;
                }
                temp->precedent = nouvelle;
            }
        }
        else {
            cout << "Stack Pleine !" << endl;
        }
    } 

    void revert() {
        Case* temp1 = NULL;
        Case* temp2 = head;
        while (temp2) {
            temp2 = temp2->precedent;
            head->precedent = temp1;
            temp1 = head;
            head = temp2;
        }
        head = temp1;
    }

    void del() {
        while (head) {
            Case* temp = head->precedent;
            delete head;
            head = temp;
        }
    }

    IntStackVariable(const IntStackVariable& stack) {
        longueur_max = stack.longueur_max;
        capacite = stack.capacite;
        head = NULL;
        if (stack.head) {
            Case* temp1 = (stack.head)->precedent;
            Case* newhead = new Case;
            newhead->elt = (stack.head)->elt;
            head = newhead;
            Case* temp2 = head;
            while (temp1) {
                Case* nouvelle = new Case;
                nouvelle->elt = temp1->elt;
                temp2->precedent = nouvelle;
                temp2 = nouvelle;
                temp1 = temp1->precedent;
            }
            temp2->precedent = NULL;
        }
    }

    IntStackVariable& operator=(const IntStackVariable& stack) {
        longueur_max = stack.longueur_max;
        capacite = stack.capacite;
        (*this).del();
        head = NULL;
        if (stack.head) {   
            Case* temp1 = (stack.head)->precedent;
            Case* newhead = new Case;
            newhead->elt = (stack.head)->elt;
            head = newhead;
            Case* temp2 = head;
            while (temp1) {
                Case* nouvelle = new Case;
                nouvelle->elt = temp1->elt;
                temp2->precedent = nouvelle;
                temp2 = nouvelle;
                temp1 = temp1->precedent;
            }
            temp2->precedent = NULL;
        }

        return *this;
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



    IntStackVariable s;

    for (int i = 0; i < 50; i++) {
        s.push(i);
    }
    s.print();
    s.pop(5);
    s.revert();
    s.print();

    {
        IntStackVariable s2 = s;
        s2.pop(4);
        s2.push(500505);
        s2.print();
    }

    s.print();

    cout << "   " << endl;

    {
        IntStackVariable s3(20);
        s3.push(5);
        s3.push(60);
        s3.print();

        s = s3;
    }

    s.print();

    s.del();
}