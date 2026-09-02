/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Gabriel Isoton Ferreira
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1080
Data        : 31/08/2026
Objetivo    : Discover the list's output order and the remnant
Dificuldade : Adapt to the new syntax
Uso de IA   : Learning the codinging in C++ (I started in C)
-------------------------------------------------------------------------- */

#include <iostream>
#include <string>
using namespace std;

struct box
{
    int num;
    box *next;
};

// Considering that the fist position is the 0 one
// Normally, the first element is the heap or the root
void push(box *head, int pos, int num);
void pop(box *head, int pos);

int main()
{
    // First, we will start two heaps, one for the original stack and other for the discards
    box *stack = new box;
    int read;

    cin >> read;
    while(read != 0)
    {
        // Creating the stack representing the pile of cards
        // If I always put the new number after the heap, it's only put in the inverse order - allocating the last one first and the first one at last
        for(int count = read; count != 0; count--)
            push(stack, 1, count);
        

        /*Now, always when we remove the first one and realocate the second one
        1 - Removing one card and reduce the stack in one (resting n-1 elements) -> Or I can show the card and discard it already, jumping the second step
        2 - Reallocating that card to the other stack
        3 - Reallocating the second card to the last position ([n-1])
            -> Remove the card of the pile and put in the end

        In the end, we will made n-1 operations, removing n-1 cards from the stack
        *The order of remove and put steps will be swaped, in reason of the code
        */

        cout << "Discarded cards:";
        while(read != 2)
        {
            cout << " " << stack->next->num << ",";
            pop(stack, 1);
            push(stack, read, stack->next->num);
            pop(stack, 1);

            read--;
        }

        // The last one is different, that isn't ","
        cout << " " << stack->next->num;
            pop(stack, 1);
            push(stack, read, stack->next->num);
            pop(stack, 1);
        
        cout << "\nRemaining card: " << stack->next->num << "\n";
        pop(stack, 1);

        cin >> read;
    }
    stack->next = NULL;
    stack->num = 0;
    delete stack;
}

void push(box *head, int pos, int num)
{
    box *pont = head;

    // How the position is equal to the number of passes, begining of heap
    // But, it's better to stop in the position before we will put the new number
    pos--; 
    while(pos)
    {
        pont = pont->next;
        pos--;
    }

    box *newest = new box;
    newest->num = num;
    newest->next = pont->next;
    pont->next = newest;
}

void pop(box *head, int pos)
{
    box *pont = head;

    // It's better stop in the element before the one that we will delete
    pos--;
    while(pos)
    {
        pont = pont->next;
        pos--;
    }

    box *del = pont->next;
    pont->next = del->next;

    del->num = 0;
    del->next = NULL;
    delete del;
}