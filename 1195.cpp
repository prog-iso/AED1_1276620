/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Gabriel Isoton Ferreira
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1195
Data        : 10/11/2026
Objetivo    : Constructing the three and printing it in prefix, infix and posfix mode
Dificuldade : None
Uso de IA   : None
-------------------------------------------------------------------------- */

#include <iostream>
using namespace std;

//We'll use the three struct, so here we'll create the nodes
struct Node
{
    int num;

    //If the num is bigger put in right, else put in left
    Node *right, *left;

    Node()
    {
        num = 0;
        right = left = NULL;
    }

    void grow(Node *knock); // Putting the new elements in the three -> *knock is the pointer to the node with the new number

    void prefix(); // Printing the three in the prefix mode
    void infix(); // Printing the three in the infix mode
    void posfix(); // Printing the three in the posfix mode
};

int main()
{
    int quant;
    cin >> quant;

    for(int i = 1; i <= quant; i++)
    {
        //Defining the elements' number in the three
        int size;
        cin >> size;
        Node *three = new Node[size];

        //For the first node, we'll save the first value manually
        int input;
        cin >> input;
        three[0].num = input;
        
        //For the rest, we'll use a loop
        for(int j = 1; j < size; j++)
        {
            //Saving the input
            cin >> input;
            three[j].num = input;

            //Putting the value in the three
            three->grow(three+j);
        }

        //Printing the three
        cout << "Case " << i << ":\n";
        
        //In the prefix mode
        cout << "Pre.:";
        three->prefix();
        cout << endl;

        //In the infix mode
        cout << "In..:";
        three->infix();
        cout << endl;

        //In the posfix mode
        cout << "Post:";
        three->posfix();
        cout << endl;

        cout << endl;
    }
}

void Node::grow(Node *knock)
{
    if(knock->num < this->num)
    {
        if(this->left == NULL) this->left = knock;
        else this->left->grow(knock);
    }
    else if(knock->num > this->num)
    {
        if(this->right == NULL) this->right = knock;
        else this->right->grow(knock);
    }
}


void Node::prefix()
{
    cout << " " << this->num;
    if(this->left != NULL) this->left->prefix();
    if(this->right != NULL) this->right->prefix();
}

void Node::infix()
{
    if(this->left != NULL) this->left->infix();
    cout << " " << this->num;
    if(this->right != NULL) this->right->infix();
}

void Node::posfix()
{
    if(this->left != NULL) this->left->posfix();
    if(this->right != NULL) this->right->posfix();
    cout << " " << this->num;
}