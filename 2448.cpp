/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Gabriel Isoton Ferreira
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1080
Data        : 23/09/2026
Objetivo    : Test the time of binary search
Dificuldade : None
Uso de IA   : None
-------------------------------------------------------------------------- */

#include <iostream>
#include <time.h>
#include <vector>
using namespace std;

int main()
{
    // Creating the 2 variables to registrate the quantity of houses and other for the packages's one  
    int N, M;
    cin >> N;
    cin >> M;

    // Creating the 1 string to registrate the houses' adress and a variable to registrate the package destination
    vector<int> house(N);
    int pack;

    // Saving the house's number
    for(int i = 0; i < N; i++)
        cin >> house[i];

    // Saving the time of deliveries' beginning
    double time_real = clock();
    double time = 0;

    // Here, we will already deliver all the packages
    for(int i = 0; i < M; i++)
    {
        cin >> pack;

        //Here we create three variables: the beggining of the analysed vector, other to the end's one and another to the avarage of the two firsts
        int begin = 0, end = N-1, med;
        while(begin != end-1)
        {
            med = (begin+end)/2;
            time++;
            if(house[med] > pack) end = med;
            else begin = med;
        }
    }
    time_real = (double)(clock() - time_real)/CLOCKS_PER_SEC;
    cout << time << "\n";
}