/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Gabriel Isoton Ferreira
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1082
Data        : 12/11/2026
Objetivo    : Counting how many subgrafs there are in the graf
Dificuldade : Formating and a little mistake in logic
Uso de IA   : Debugging, formating and reading syntax 
-------------------------------------------------------------------------- */
#include <iostream>
using namespace std;


bool **matrix(int size); // This function'll create the graf's base zero matrix
void clean(bool **graf, int size); // This function'll clean the graf allocated in the memory

// This function'll verify the conection in a sub set in the graf
// Beggining in a point, it'll stop when all the conected vertex of a subgraf have been checked 
void dfs(bool **graf, int size, int vert, int *check, int set);

int main()
{
    int cases, size, link; // Save the num of cases, the size of matrix associated to the graf and the num of links in the graf
    char vert_a, vert_b; // Save the 2 vertex in a link

    // Beginning to analize the cases
    cin >> cases;
    for(int i = 1; i <= cases; i++)
    {
        // ----------- The beginning ------------- //

        // Reading the size of the associated matrix and the num of links
        cin >> size;
        cin >> link;

        // Creating the graf's associated matrix
        bool **graf = matrix(size);
        
        // Creating the graf in fact, this means saving the vert and links in the associated matrix
        for(int j = 0; j < link; j++)
        {
            // Reading the link
            cin >> vert_a;
            cin >> vert_b;

            // Saving in the matrix the link
            graf[vert_a - 'a'][vert_b - 'a'] = true;
            graf[vert_b - 'a'][vert_a - 'a'] = true;
        }

        // Creating the structure to verify the connected components' quantity
        int verify = 0;
        int *check = new int[size];
        int set = 0; // It counts the connected set's num
        
        // Inicializing the check with 0
        for(int j = 0; j < size; j++)
            check[j] = 0;

        int begin = 0;
        


        // ----------- The analizis ------------- //

        do
        {
            // In each loop, a new connected set will be counted
            set++;
            
            //Check the connected set's existence
            dfs(graf, size, begin, check, set);
        
            // The next analize should begin in the first check[j] == false
            begin = 0;
            while(check[begin] != 0 && begin < size)
                begin++;
        }while(begin < size); //If begin == size all elements belong to a set



        // ----------- The output ------------- //
        
        cout << "Case #" << i << ":\n";
        
        // Printing the connected set's
        for(int j = 1; j <=set; j++)
        {
           for(int k = 0; k < size; k++)
                if(check[k] == j)
                    cout << char(k + 'a') << ",";
           
         cout << endl;
        }

        cout << set << " connected components\n\n";



        // ----------- The cleaning ------------- //

        // Cleaning the graf
        clean(graf, size);
        
        // Cleaning the check list
        for(int j = 0; j < size; j++)
            check[j] = 0;
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

void dfs(bool **graf, int size, int vert, int *check, int set)
{
    check[vert] = set;

    for(int i = 0; i < size; i++)
        if(graf[vert][i] && check[i] == 0) // The check and graf elements are bool indicators
            dfs(graf, size, i, check, set);
}
