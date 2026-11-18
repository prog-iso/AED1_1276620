/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Gabriel Isoton Ferreira
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1194
Data        : 01/09/2026
Objetivo    : Verifing if it there's a loop in the struct
Dificuldade : Adjusting and debugging the code
Uso de IA   : Understand the reason for divergences and causes
-------------------------------------------------------------------------- */
#include <iostream>
using namespace std;

bool **matrix(int size); // This function'll create the graf's base zero matrix
void clean(bool **graf, int size); // This function'll clean the graf allocated in the memory

// This function'll verify the conection in a sub set in the graf
// Beggining in a point, it'll stop when all the conected vertex of a subgraf have been checked 
void dfs(bool **graf, int size, int vert, bool *check, bool *loop);

int main()
{
    // Reading how many cases there'll be
    int quant;
    for(cin >> quant; quant != 0; quant--)
    {
        // These'll count how many docs there'are and dependencies in general
        int size, depend;
        cin >> size;
        cin >> depend;

        bool **graf = matrix(size);

        // Creating the graf in fact, this means saving the vert and links in the associated matrix
        for(int j = 0; j < depend; j++)
        {
            // Reading the dependency
            int vert_a, vert_b;
            cin >> vert_a;
            cin >> vert_b;

            // Saving in the matrix the link
            graf[vert_a - 1][vert_b - 1] = true;
        }

        // Creating the structure to verify the connected components' quantity
        bool *check = new bool[size];
        for(int i=0; i < size; i++) check[i] = false;
        
        //Checking, in fact, if there's a loop
        bool loop = false;
        for(int i = 0; i < size && !loop; i++)
        {
            dfs(graf, size, i, check, &loop);
        }
        if(!loop) cout << "NAO" << endl;
        else cout << "SIM" << endl;

        clean(graf, size);
        for(int i=0; i < size; i++) check[i] = false;
        delete[] check;
    }
}

bool **matrix(int size)
{
    // Creating the row of the matrix 
    bool **row = new bool*[size];

    // Creating the lines
    for(int i = 0; i < size; i++)
        row[i] = new bool[size];
    
    // Inicializing the matrix with 0
    for(int j = 0; j < size; j++)
        for(int i = 0; i < size; i++)
            row[j][i] = 0;
    
    return row;
}

void clean(bool **graf, int size)
{
    // Deleting the data in memory 
    for(int j = 0; j < size; j++)
        for(int i = 0; i < size; i++)
            graf[j][i] = 0;
    
    // Freeing the lines' space in the memory
    for(int i = 0; i < size; i++)
    {
        delete[] graf[i];
        graf[i] = NULL;
    }

    // Freeing the row's space in the memory
    delete[] graf;
}

void dfs(bool **graf, int size, int vert, bool *check, bool *loop)
{
    check[vert] = true;

    for(int i = 0; i < size && !*loop; i++)
    {       
        if(graf[vert][i] && i != vert) // The check and graf elements are bool indicators
        {
            if(check[i])
                *loop = true;
            else
                dfs(graf, size, i, check, loop);
        }
    }

    check[vert] = false;
}