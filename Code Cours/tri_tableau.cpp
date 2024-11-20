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
        cout << "  " << endl;
        cout << "------------------------------***------------------------------" << endl;
        cout << "  " << endl;
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
            capacite++;
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

    IntStackVariable operator^ (const IntStackVariable& stack) const {

        IntStackVariable s;

        s.capacite = capacite + stack.capacite;
        s.longueur_max = longueur_max + stack.longueur_max;
        s.head = NULL;

        if (!head) {
            s = stack;
            return s;
        }
        else if (!stack.head) {
            s = *this;
            return s;
        }
        else {
            Case* newhead = new Case;
            newhead->elt = (stack.head)->elt;
            
            Case* temp2 = newhead;

            Case* temp1 = (stack.head)->precedent;
            while (temp1) {
                Case* nouvelle = new Case;
                nouvelle->elt = temp1->elt;
                temp2->precedent = nouvelle;
                temp2 = nouvelle;
                temp1 = temp1->precedent;
            }

            temp1 = (*this).head;
            while (temp1) {
                Case* nouvelle = new Case;
                nouvelle->elt = temp1->elt;
                temp2->precedent = nouvelle;
                temp2 = nouvelle;
                temp1 = temp1->precedent;
            }
            temp2->precedent = NULL;

            s.head = newhead;

            return s;
        }
    }

    IntStackVariable operator+ (const IntStackVariable& stack) const {

        IntStackVariable s;
        Case* temp2;
        int delta;
       

        if (capacite < stack.capacite) {
            s = stack;
            delta = stack.capacite - capacite;
            temp2 = head;
        }
        else {
            s = (*this);
            temp2 = stack.head;
            delta = capacite - stack.capacite;
        }

        Case* temp1 = s.head;

        for (int i = 0; i < delta; i++) {
            temp1 = temp1->precedent;
        }

        while (temp1) {
            temp1->elt += temp2->elt;
            temp2 = temp2->precedent;
            temp1 = temp1->precedent;
        }
        return s;
    }

    IntStackVariable operator* (const IntStackVariable& stack) const {

        IntStackVariable s;
        Case* temp2;
        int delta;


        if (capacite < stack.capacite) {
            s = stack;
            delta = stack.capacite - capacite;
            temp2 = head;
        }
        else {
            s = (*this);
            temp2 = stack.head;
            delta = capacite - stack.capacite;
        }

        Case* temp1 = s.head;

        for (int i = 0; i < delta; i++) {
            temp1->elt = 0;
            temp1 = temp1->precedent;
        }

        while (temp1) {
            temp1->elt *= temp2->elt;
            temp2 = temp2->precedent;
            temp1 = temp1->precedent;
        }
        return s;
    }

    IntStackVariable& operator* (const int& i) {
        Case* temp = head;
        while (temp) {
            temp->elt*=i;
            temp = temp->precedent;
        }
        return *this;
    }

    void operator++ () {
        Case* temp = head;
        while (temp) {
            temp->elt++;
            temp = temp->precedent;
        }
    }

    void operator-- () {
        Case* temp = head;
        while (temp) {
            temp->elt--;
            temp = temp->precedent;
        }
    }

    void operator<< (int i) {
        (*this).push(i);
    }

    int operator| (const IntStackVariable& stack) const {
        if (capacite != stack.capacite) {
            cout << "Erreur : Piles de Taille Différentes" << endl;
            exit(-1);
        }

        cout << "test" << endl;
        Case* temp1 = head;
        Case* temp2 = stack.head;
        int tot = 0;

        while (temp1) {
            tot += (temp1->elt) * (temp2->elt);
            temp1 = temp1->precedent;
            temp2 = temp2->precedent;
        }

        return tot;
    }

};

int main() {
    
    IntStackVariable s;

    for (int i = 0; i < 50; i++) {
        s.push(i);
    }
    s.print();
    s.pop(5);
    s.revert();
    s.print();

    s.print();

    cout << "   " << endl;

    {
        IntStackVariable s3(20);
        s3.push(5);
        s3.push(60);
        s3.print();

        IntStackVariable s4 = s ^ s3;

        s4.print();

        IntStackVariable s5 = s + s4;
        s5.print();

        s.print();
        IntStackVariable s6 = s * 4;
        s6.print();
    }

    
    
    /*Test du produit scalaire
    {
        IntStackVariable a;
        IntStackVariable b;
        a << 5;
        a << 6;
        b << -1;
        b << 1;
        cout << (a | b) << endl;
    } */

    s.del();
}