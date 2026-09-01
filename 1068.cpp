/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Gabriel Isoton Ferreira
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1080
Data        : 01/09/2026
Objetivo    : Check if the opening an closing of statements are corrects
Dificuldade : Time optimization and to understand and model what's happening at the end of input (if there's a '\n' or a ' ')
Uso de IA   : Learning an improve the comprehention of syntax and debug
-------------------------------------------------------------------------- */

// The structure for this project is stack, conderig this:

#include <iostream>
#include <string>
using namespace std;

struct box
{
    char let;
    box *next;
};

// The first position is 0 and that's root's position

//This create the new container, after the head
void push(box *root, char let);
// This excludes the first container after the head
void pop(box *root);
// This read and delete the first container after the head
char read(box *root);
// This exclude the stack
void clear_stack(box *root);

int main()
{
    box *open = new box;
    open->next = NULL;

    char input;
    bool compare = true;
    int count = 0;
    while(cin.get(input))
    {
        // Create the stack only with the (, [ and {
        if(input == '(' || input == '[' || input == '{')
        {
            push(open, input);
            count++; // Count the open elements' number
        }
        // Check if the closest element of the statement, which is the first after the root in the stack, is the same that is closing
        else if(input == ')' || input == ']' || input == '}')
        {
            count--;
            // If fail the comparation, the reading could stop, still begin the next line and say the mesage: "Oh, that's a problem"
            if(count >= 0)
            {
                    if(read(open) != input)
                {
                    // Update the reading untill the end of line || string
                    while(input != '\n' && input != '\0')
                        if(!(cin.get(input))) // If a problem occurs (that isn't a endline mark) and there isn't more reading, stop the refresh
                            break;
                    cout << "incorrect\n";
                    clear_stack(open);
                }
            }
            else
            {
                while(input != '\n' && input != '\0')
                        if(!(cin.get(input)))
                            break;
                    cout << "incorrect\n";
                    clear_stack(open);
            }
        }
        // Always there is a space in the end of the line
        if(input == ' ')
        {
            // It's the same above
            while(input != '\n' && input != '\0')
                if(!(cin.get(input)))
                    break;
                    
            // After the verification, if all closings are corrects say the mesage: "Oh, it's ok"
            if(count == 0)
                cout << "correct\n";
            else
            {
                cout << "incorrect\n";

                count = 0;
                clear_stack(open);
            }
        }
    }

    open->let = 0;
    open->next = NULL;
    delete open;
}

void push(box *root, char let)
{
    box *newest = new box;
    newest->next = root->next;
    newest->let = let;
    root->next = newest;
}

void pop(box *root)
{
    box *del = root->next;
    root->next = del->next;

    del->let = 0;
    del->next = NULL;
    delete del;
}

char read(box *root)
{
    char let = root->next->let;
    pop(root);

    return let;
}

void clear_stack(box *root)
{
    while(root->next != NULL)
        pop(root);
}