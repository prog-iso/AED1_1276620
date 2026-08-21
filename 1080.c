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

int main()
{
    // Definindo variáveis de: posição do max, numero lido, max valor lido
    int pos=1, num, max;

    //Como não tem nenhum número lido além desse, ele, automaticamente, é o maior até agora
    scanf("%d", &num);
    max = num;

    for(int cont = 2; cont < 101; cont++)
    {
        scanf("%d", &num);

        if(num > max)
        {
            max = num;
            pos = cont;
        }
    }
    printf("%d\n%d\n", max, pos);
}