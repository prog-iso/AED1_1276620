/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Gabriel Isoton Ferreira
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1080
Data        : 23/09/2026
Objetivo    : Calculate the circle's area
Dificuldade : None
Uso de IA   : None
-------------------------------------------------------------------------- */

#include <iostream>
using namespace std;

int main()
{
    double raio;
    cin >> raio;

    // Is necessary to set the number of floatfields
    cout.precision(4);

    // Fixed is necessary to the number in precision's field ("4") to be the number of digits in the floatfield,
    // otherwise that will be the general number's digits 
    cout << "A=" << fixed << 3.14159*raio*raio << "\n";
}