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

void posfix(char *infix, char *prefix, int size);

int main()
{
    //Reading how many cases there'll be
    int quant;

    for(cin >> quant; quant != 0; quant--)
    {
        //Defining the size of the three
        int size;
        cin >> size;

        //Creating the strings, without using the string class
        char* prefix = new char[size];
        char* infix = new char[size];

        cin.ignore();
        cin.read(prefix, size);
        cin.ignore();
        cin.read(infix, size);

        posfix(infix, prefix, size);
        cout << endl;

        
        for(int i = 0; i < size; i++)
            prefix[i] = 0;
        delete[] prefix;

        for(int i = 0; i < size; i++)
            prefix[i] = 0;
        delete[] infix;
    }
}

void posfix(char *infix, char *prefix, int size)
{
    if(size == 0) return;

    char root = *prefix;

    // Count how many elements there are in left of the root
    int untill_root = 0;
    while(infix[untill_root] != root)
        untill_root++;
    
    posfix(infix, prefix+1, untill_root); //Left printing
    posfix(infix + untill_root+1, prefix + untill_root+1, size - untill_root - 1); // Right printing
    cout << root;
}