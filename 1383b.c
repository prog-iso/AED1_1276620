/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Gabriel Isoton Ferreira
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1080
Data        : 26/08/2026
Objetivo    : Verificar quais configurações de jogo (sudoku) são válidas
Dificuldade : Nenhuma
Uso de IA   : Não
-------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool verif_linha(int* linha, int quant_colunas);
bool verif_coluna(int** matriz, int coluna, int quant_linhas);
bool verif_bloco(int** matriz, int linha_prim_elem_bloco, int col_prim_elem_bloco);

int main()
{
    int num_matriz;
    int **matriz = (int **) malloc(9*sizeof(int *));
    for(int i = 0; i < 9; i++) matriz[i] = (int *) malloc(9*sizeof(int));

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
            resp = verif_coluna(matriz, x, 9);
        for(int x = 0; x < 3 && resp; x++)
        {
            for(int y = 0; y < 3 && resp; y++)
                resp = verif_bloco(matriz, 3*y, 3*x);
        }

        if(resp) printf("Instancia %d\nSIM\n\n", i+1);
        else printf("Instancia %d\nNAO\n\n", i+1);
    }

    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
            matriz[i][j] = 0;
        free(matriz[i]);
        matriz[i] = NULL;
    }
    free(matriz);
    matriz = NULL;
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
bool verif_coluna(int** matriz, int coluna, int quant_linhas)
{
    for(int i = 0; i < quant_linhas-1; i++)
    {
        for(int j = i+1; j < quant_linhas; j++)
            if(matriz[i][coluna] == matriz[j][coluna])
                return false;
    }

    return true;
}

// Análoga às anteriores, mas analizando por setor agora e não por linhas ou colunas
bool verif_bloco(int** matriz, int linha_prim_elem_bloco, int col_prim_elem_bloco)
{
    int *bloco = (int *) malloc(9 * sizeof(int));
    for(int i = 0; i < 9; i++)
        bloco[i] = matriz[linha_prim_elem_bloco + i/3][col_prim_elem_bloco + i%3];
    
    bool analise = verif_linha(bloco, 9);

    for(int i = 0; i  < 9; i++)
        bloco[i] = 0;
    free(bloco);
    bloco = NULL;

    return analise;
}