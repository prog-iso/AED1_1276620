/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Gabriel Isoton Ferreira
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1466
Data        : 14/11/2026
Objetivo    : Print the three in breadth first search (BFS) mode
Dificuldade : 
Uso de IA   : 
-------------------------------------------------------------------------- */
#include <iostream>
using namespace std;

//We'll use the three struct, so here we'll create the nodes
struct Node
{
    int num;

    //If the letter is bigger put in right, else put in left
    Node *right, *left;

    Node()
    {
        num = 0;
        right = left = NULL;
    }

    void grow(int num); // Putting the new elements in the three
    void clear(); // Clearing the memory, deleting the three
};

void bfs(Node *three, int size);

int main()
{

// --------------------------- The beginning --------------------------- //

    // Receiving the quantity of cases there will be
    int cases;
    cin >> cases;

    for(int i = 1; i <= cases; i++)
    {
        // Receiving the size of the three (elements' quantity)
        int size;
        cin >> size;
        
        // Creating the three with size-elements
        Node *three = new Node;
        cin >> three->num;
        for(int j = 0; j < size-1; j++) //How it there's one number in the three, we must add size-1 elements 
        {
            int num;
            cin >> num;
            three->grow(num);
        }


// --------------------------- The output and freeing memory--------------------------- //

        // Printing the three in bfs mode
        cout << "Case " << i << ":" << endl;
        bfs(three, size);
        cout << endl;

        //Freeing the memory
        three->clear();
    }
}

void Node::grow(int num)
{   
    if(num < this->num)
    {
        if(this->left == NULL)
        {
            Node *newest = new Node;
            newest->num = num;
            this->left = newest;
        }
        else this->left->grow(num);
    }
    else if(num > this->num)
    {
        if(this->right == NULL)
        {
            Node *newest = new Node;
            newest->num = num;
            this->right = newest;
        }
        else this->right->grow(num);
    }
}

void Node::clear()
{
    if(this->left != NULL) this->left->clear();
    if(this->right != NULL) this->right->clear();
    this->num = 0;
    delete this;
}

void bfs(Node *three, int size)
{
    Node *reord = new Node[size];
    int pos_reord, pos_read;

    // Inicialize the reord queue
    reord[0] = *three;

    // How we've already read one value os the three and the fisrt element is the zero-one, the next one must be the 1-one
    pos_read = 1;

    // pos_reord is the counter prepared to indicate where in the three, based in the reord queue, we should pick up the next element
    pos_reord = 0;

    while(pos_reord < size)
    {
        if(reord[pos_reord].left != 0)
        {
            reord[pos_read] = *reord[pos_reord].left;
            pos_read++;
        }

        if(reord[pos_reord].right != 0)
        {
            reord[pos_read] = *reord[pos_reord].right;
            pos_read++;
        }

        pos_reord++;
    }

    // The output
    for(int i = 0; i < size-1; i++)
    {
        cout << reord[i].num << " ";
        reord[i] = {};
    }
    cout << reord[size-1].num << "\n";
    reord[size-1] = {};

    // Freeing the memory
    delete[] reord;
}
