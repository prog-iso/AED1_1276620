/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Gabriel Isoton Ferreira
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1194
Data        : 01/09/2026
Objetivo    : Decribe the posfix structre, beginning with prefix and infix
Dificuldade : 
Uso de IA   : 
-------------------------------------------------------------------------- */

#include <iostream>
using namespace std;

//We'll use the three's structure
//First we'll construct the three, using the inputs and, then, output the postfix line
struct branch
{
    char let; // The value

    //The next elements, under is the left one and over is the right one
    branch *under, *over;

    //This function associates a new value in the branch, if over == 1 the new element's put in over position 
    void put(char let, bool over = 1);
};

int main()
{
    int quant;
    cin >> quant;

    for(; quant != 0; quant--)
    {
        //Understanding the size of the expression in prefix and in infix style and saving them
        int size;
        cin >> size;
        char *prefix = new char[size];
        char *infix = new char[size];

        //Preparing the three
        branch root;
    }
}

void branch::put(char let, bool over)
{
    branch *newest = new branch;
    newest->let = let;
    newest->over = newest->under = NULL;
    
    if(over) this->over = newest;
    else this->over = newest;
}
