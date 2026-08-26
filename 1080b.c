/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Gabriel Isoton Ferreira
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1080
Data        : 21/08/2026
Objetivo    : Determinar o maior número lido
Dificuldade : Saber que precisava colocar um \n no final da saida, para o Beecrowd aceitar minha resposta
Uso de IA   : Não
-------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Definindo variáveis de: posição do max, numero lido, max valor lido
    int pos=1, max;
    int *vetor = (int *) malloc(sizeof(int)*100);

    //Como não tem nenhum número lido além desse, ele, automaticamente, é o maior até agora
    scanf("%d", &vetor[0]);
    max = vetor[0];

    for(int cont = 1; cont < 100; cont++)
    {
        scanf("%d", &vetor[cont]);

        if(vetor[cont] > max)
        {
            max = vetor[cont];
            pos = cont+1;
        }
    }
    printf("%d\n%d\n", max, pos);
    
    for(int i = 0; i <100; i++) vetor[i] = 0;
    free(vetor);
    vetor = NULL;
}