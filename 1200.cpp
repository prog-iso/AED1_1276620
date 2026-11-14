/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Gabriel Isoton Ferreira
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1200
Data        : 10/11/2026
Objetivo    : Implementing a three's structure with some methods
Dificuldade : Adapt to beecrowd correction 
Uso de IA   : It was used to get the idea to do the adaptation
-------------------------------------------------------------------------- */

#include <iostream>
#include <string>
using namespace std;

//We'll use the three struct, so here we'll create the nodes
struct Node
{
    char letter;

    //If the letter is bigger put in right, else put in left
    Node *right, *left;

    Node()
    {
        letter = 0;
        right = left = NULL;
    }

    void grow(char letter); // Putting the new elements in the three

    void prefix(bool *first); // Printing the three in the prefix mode ("first" is used to print correctely)
    void infix(bool *first); // Printing the three in the infix mode ("first" is used to print correctely)
    void posfix(bool *first); // Printing the three in the posfix mode ("first" is used to print correctely)

    void search(char check); // Checking if a statements is in the three

    void clear(); // Clearing the memory, deleting the three
};

int main()
{
    Node *three = new Node;

    string readed;
    char letter;

    //The first case is the inicializing the three, so:
    cin >> readed;
    cin >> letter;
    three->letter = letter;

    while(cin >> readed)
    {
        if(readed == "I")
        {
            cin >> letter;
            three->grow(letter);
        }
        else if(readed == "INFIXA")
        {
            bool first = true;
            three->infix(&first);
            cout << endl;
        }
        else if(readed == "PREFIXA")
        {
            bool first = true;
            three->prefix(&first);
            cout << endl;
        }
        else if(readed == "POSFIXA")
        {
            bool first = true;
            three->posfix(&first);
            cout << endl;
        }
        else if(readed == "P")
        {
            cin >> letter;
            three->search(letter);
        }
    }

    three->clear();
}

void Node::grow(char letter)
{   
    if(letter < this->letter)
    {
        if(this->left == NULL)
        {
            Node *newest = new Node;
            newest->letter = letter;
            this->left = newest;
        }
        else this->left->grow(letter);
    }
    else if(letter > this->letter)
    {
        if(this->right == NULL)
        {
            Node *newest = new Node;
            newest->letter = letter;
            this->right = newest;
        }
        else this->right->grow(letter);
    }
}


void Node::prefix(bool *first)
{
    // Here the value is printed in fact
    if(*first)
    {
        cout << this->letter;
        *first = false;
    }
    else cout << " " << this->letter; 
    
    if(this->left != NULL) this->left->prefix(first);
    if(this->right != NULL) this->right->prefix(first);
}

void Node::infix(bool *first)
{
    if(this->left != NULL) this->left->infix(first);
    
    // Here the value is printed in fact
    if(*first)
    {
        cout << this->letter;
        *first = false;
    }
    else cout << " " << this->letter;

    if(this->right != NULL) this->right->infix(first);
}

void Node::posfix(bool *first)
{
    if(this->left != NULL) this->left->posfix(first);
    if(this->right != NULL) this->right->posfix(first);
    
    // Here the value is printed in fact
    if(*first)
    {
        cout << this->letter;
        *first = false;
    }
    else cout << " " << this->letter;
}

void Node::search(char check)
{
    if(check != this->letter)
    {
        if(check < this->letter)
        {
            if(this->left == NULL) cout << check << " nao existe" << endl;
            else this->left->search(check);
        }
        else
        {
            if(this->right == NULL) cout << check << " nao existe" << endl;
            else this->right->search(check);
        }
    }
    else cout << check << " existe" << endl;
}

void Node::clear()
{
    if(this->left != NULL) this->left->clear();
    if(this->right != NULL) this->right->clear();
    this->letter = 0;
    delete this;
}