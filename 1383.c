/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Gabriel Isoton Ferreira
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1080
Data        : 21/08/2026
Objetivo    : Verificar quais configurações de jogo (sudoku) são válidas
Dificuldade : Como ler os blocos dentro de cada jogo
Uso de IA   : Debuggar o código
-------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdbool.h>

bool verif_linha(int* linha, int quant_colunas);
bool verif_coluna(int* pont_primeiro_elem_coluna, int quant_linhas, int quant_colunas);
bool verif_bloco(int* pont_primeiro_elem_bloco, int quant_linhas_bloco, int quant_colunas_bloco, int quant_colunas_matriz);

int main()
{
    int num_matriz, matriz[9][9];
    scanf("%d", &num_matriz);

    for(int i = 0; i < num_matriz; i++)
    {
        for(int y = 0; y < 9; y++)
        {
            for(int x = 0; x < 9; x++)
                scanf("%d", &matriz[y][x]);
        }
    
        bool resp = true;
        for(int y = 0; y < 9 && resp; y++)
            resp = verif_linha(matriz[y], 9);
        for(int x = 0; x < 9 && resp; x++)
            resp = verif_coluna(&matriz[0][x], 9, 9);
        for(int x = 0; x < 3 && resp; x++)
        {
            for(int y = 0; y < 3 && resp; y++)
                resp = verif_bloco(&matriz[y*3][x*3], 3, 3, 9);
        }

        if(resp) printf("Instancia %d\nSIM\n\n", i+1);
        else printf("Instancia %d\nNAO\n\n", i+1);
    }
}

// Função que verifica se não tem elemento repetido na mesma linha
bool verif_linha(int* linha, int quant_colunas)
{
    // Passa por cada elemento, testando com os sucessores
    for(int i = 0; i < quant_colunas-1; i++)
    {
        // Como sei que um elemento é diferente dos anteriores, posso só compará-lo com o segundo
        for(int j = i+1; j < quant_colunas; j++)
            if(linha[i] == linha[j]) return false;
    }

    return true;
}

// Análoga a verif_linha, mas para coluna
bool verif_coluna(int* pont_primeiro_elem_coluna, int quant_linhas, int quant_colunas)
{
    for(int i = 0; i < quant_linhas-1; i++)
    {
        // Como vamos andar pelas colunas, o passo é diferente - indo de n em n passos, onde n é o número de colunas
        for(int j = i+1; j < quant_linhas; j++)
            if(pont_primeiro_elem_coluna[i*quant_colunas] == pont_primeiro_elem_coluna[j*quant_colunas]) return false;
    }

    return true;
}

// Análoga às anteriores, mas analizando por setor agora e não por linhas ou colunas
bool verif_bloco(int* pont_primeiro_elem_bloco, int quant_linhas_bloco, int quant_colunas_bloco, int quant_colunas_matriz)
{
    for(int i = 1; i < quant_linhas_bloco*quant_colunas_bloco; i++)
    {
        // Setando a posição do elemento "comparador", que inicialmente é a mesma do elemento "comparado"
        int* pont_compara = pont_primeiro_elem_bloco;

        for(int j = i+1; j < quant_linhas_bloco*quant_colunas_bloco; j++)
        {
            // Adequando/Posiconando o elemento a ser comparador
            // (ex: se tornando o terceiro ou quinto elemento depois daquele que será comparado com seus sucessores)
            if(j%quant_colunas_bloco == 1) pont_compara = pont_compara -(quant_colunas_bloco- 1) + quant_colunas_matriz;
            else  pont_compara += 1;

            if(*pont_primeiro_elem_bloco == *pont_compara) return false;
        }

        /* Andando o elemento comparado

        Se ele estiver no fim da linha, ele estará na coluna máxima daquela linha, ou seja,
        seu índice será um mútiplo do N de uma matriz MxN.

        E se estiver no fim da linha, precisa voltar ao início da linha e depois andar N passos,
        para chegar ao elemento da primeira coluna na linha de baixo no mesmo bloco.

        Por fim, esse caminho no bloco parece ser diferente do feito no for anterior, mas funciona do mesmo jeito.
        Nesse caso, a diferença é que se anda antes de entrar no laço novo, em que o elemento que anda será usado e,
        antes, se andava no início do laço em que seria usado.
        
        */
        if( i%quant_colunas_bloco == 0) pont_primeiro_elem_bloco = pont_primeiro_elem_bloco -(quant_colunas_bloco - 1) + quant_colunas_matriz;
        else pont_primeiro_elem_bloco += 1;
    }

    return true;
}