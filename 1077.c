/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Gabriel Isoton Ferreira
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1080
Data        : 07/10/2026
Objetivo    : Transform an comomn (infix) expretion in a posfix expression
Dificuldade : To make the chase with parenthesis (in my pc I have the protipes untill the operators priority)
Uso de IA   : Trying to debug, but the AI misfixed and made a caos in my original code
-------------------------------------------------------------------------- */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <cstdlib>
using namespace std;


// One time that we don't know thw expretion's size, it's necessary to use dynamic allocation
// So it'll be necessary use structs
struct box
{
    char letter; // The value, which is a char that is almost the same that a letter
    box *next; // The pointer linking the list's elements

    // To manipulate the boxes, it's necessary 2 methods:

    //push (creating a new value's memory space and saving that after the head)
    void push(char letter);

    //pop (removing the first value in the list and returning a pointer to the next value)
    box* pop();
};

// And for this project, there'll be some branchs - each for each internal list of operators
struct branch
{
    // The used structures are: stack(posfix numbers) and queue (posfix symbols)
    box *letters; // Here is where the letters or equation's variables of each excerpt will be saved (put the head of that excerpt)
    box *operators; // Here is were the relationated operator's signals will be saved
    //Ex: ABCD*+- -> letters(stack: A, B, C, D) and signal(stack: *, +, -)
    
    /* *First of all, we'll read all expression and analyse that from last to begining (A<---Z, from Z to A)
    Always that the avaluated operator is more important that the first value in the operators stack, a new branch will be created
    Ex: A*B-C+D -> A*B-C and stacks letters(D) and operators(+) -> A*B and stacks letters(C, D) and operators(-, +)
        -> But * is more important than -, so creates a new branch: [stacks letters(A, B) and operators(*)] and [stacks letters(D, C) and operators(-, +)]
    */
    branch *next;

    int quant; //It registrates how many items are in this branch

    // To manipulate the boxes, it's necessary 2 methods:

    // ramify (assigning the letters and operators to the current branch, reseting the letters and operators boxes and creating a new branch )
    //put the letters' head and operators' head too
    void ramify(box *letters, box *operators, int quant); 

    // reap (reading the values of this branch, removing this one and returning a pointer to the char vector of that section in posfix notation)
    char* reap();

};

/* Because the expression inside a parenthesis works like a term in the rest of the expressio:
1 - We could read the expression and identify a begining and a end o parenthesis term
2 - Reorganize the parenthesis inside's expression
3 - Replace that expression as a "term"
4 - Finally, organize everything as there isn't parenthesis
*/

//This function changes, in fact, the original expression - removing the parenthesis and reorder inside in posfix style
//begin(beginning of the analysed expression) and size(pointing until there the parenthesis expression goes)
void reorder(char *begin, int size);

int main()
{
    char expression[301];
    char firstLine[301];

    if (!cin.getline(firstLine, sizeof(firstLine)))
        return 0;

    bool isCount = firstLine[0] != '\0';
    for (int i = 0; firstLine[i] != '\0'; i++)
    {
        if (!isdigit(static_cast<unsigned char>(firstLine[i])))
        {
            isCount = false;
            break;
        }
    }

    int count = isCount ? atoi(firstLine) : 1;
    if (!isCount)
        strcpy(expression, firstLine);

    for (int current = 0; current < count; current++)
    {
        if (isCount && !cin.getline(expression, sizeof(expression)))
            break;

        int length = static_cast<int>(strlen(expression));
        while (length > 0 && isspace(static_cast<unsigned char>(expression[length - 1])))
            expression[--length] = '\0';

        reorder(expression, length);
        cout << expression << '\n';
    }
}

void box::push(char letter)
{
    // Creating a new space and registrating a value in it
    box *newest = new box;
    newest->letter = letter;

    // Linking the new box
    newest->next = this->next;
    this->next = newest;
}

box* box::pop()
{
    // Saving the pointer to the next one
    box *near = this->next;
    
    // Deleting the read box
    this->letter = 0;
    this->next = NULL;
    delete this;

    //Returning the pointer to the next of the next one (before: B->C->D, after: B->D)
    return near;
}

void branch::ramify(box *letters, box *operators, int quant)
{
    //First, creating a new branch
    branch *newest = new branch;
    newest->letters = letters->next; //letters is a list's head
    newest->operators = operators->next; //operators is a list's head
    newest->quant = quant;

    //Second, reset the letters and operators list
    letters->next = NULL;
    operators->next = NULL;

    //And, at last but not least, linking the new branch
    newest->next = this->next;
    this->next = newest;
}

// ---------------------------- ARRUMAR ---------------------------------- //
char* branch::reap()
{
    //First, creating a string with quant-elements -> This string is what we must return
    char *posfix = new char[this->next->quant];
    int count=0; //Creating a counter to use that in the construction of the new posfix string

    //Second, saving all the letters' value
    while(this->next->letters != NULL) // When the head's next pointer is NULL, the list was almost read
        {
            posfix[count] = this->next->letters->letter;
            this->next->letters = this->next->letters->pop();
            count++;
        }

    //Third, doing the same with operators. But operators is a queue, so we'll need to read behind to front
    while(this->next->operators->next != NULL)
    {
        box* pont = this->next->operators;
        while(pont->next->next != NULL) //It stop before the last one (the next pointer is NULL)
            pont = pont->next;
        posfix[count] = this->next->operators->letter;
        pont->next = pont->next->pop();
        count++;
    }
    
    posfix[count] = this->next->operators->letter;
    this->next->operators->pop();

    //And, at last, exclude the branch
    branch *del = this->next;
    this->next = del->next;
    del->letters = NULL;
    del->operators = NULL;
    del->next = NULL;
    delete del;

    return posfix;
}
// ---------------------------- ARRUMAR ---------------------------------- //

void reorder(char *begin, int size)
{
    //Creating the 3 main lists: letters(posfix letters), operators(posfix operators) and three (where the branches are)
    box letters, operators;
    branch three; //The branches' group works like a stack, the last added will be first printed
    letters.next = operators.next = three.letters = three.operators = NULL;
    three.next = NULL;
    letters.letter = operators.letter = 0;

    //Creating a counter of how many items there is in a branch
    int quant = 0;

    for(size--; size != 0; size--)
    {
        int count = 0; //It's a counter of how many ")", that's how many open expressions there are
        if(begin[size] == ')')
        {
            
            do //We'll copy the elements untill the original expression is closed
            {
                letters.push(begin[size]);
                if(begin[size] == ')') count++;
                else if(begin[size] == '(') count--;

                quant++;
                size--;
            } while(count);

            if(size == -1) break; //If the parenthesis closes in the expression's end, so the loop is stopped, without pass throught the rest
        }
        else if(begin[size] == '+' || begin[size] == '-' || begin[size] == '*' || begin[size] == '/' || begin[size] == '^')
        {
            if(operators.next != NULL &&
                                         (((begin[size] == '^' || begin[size] == '*' || begin[size] == '/') && (operators.next->letter == '-' || operators.next->letter == '+')) ||
                                         (begin[size] == '^' && (operators.next->letter == '*' || operators.next->letter == '/'))))
            {
                three.ramify(&letters, &operators, quant); //Ramifying and reseting the lists to continue analysing the expression
                quant = 0; //Resets the counter ->The reset is caused by the lack of members in the new branch (all elements registered are in older branches, at this moment)
            }
            else
            {
                operators.push(begin[size]);
                quant++;
            }
        }
        else
        {
            letters.push(begin[size]);
            quant++;
        }
    }

    //Adding the final letter in expression and conecting the last letters and operators in a branch
    if(size == 0)
    {
        letters.push(begin[0]);
        quant++;
    }
    
    three.ramify(&letters, &operators, quant);

    quant = 0; //Now quant will represents the begining position of replacing
    
    // ---------------------------- ARRUMAR ---------------------------------- //
    // We'll organize the list, except the terms in the last branch (without counting the head)
    while(three.next->next != NULL)
    {
        int size = three.next->quant;
        char *replacing = three.reap();
        for(int i = 0; i < size; i++)
        {
            begin[quant] = replacing[i];
            replacing[i] = 0;

            quant++;
        }
        delete[] replacing;
    }

    //Now, for the last branch
    //First, saving all the letters' value
    while (three.next->letters->next != nullptr)
    {
        while(three.next->letters != NULL) // When the head's next pointer is NULL, the list was almost read
        {
            begin[quant] = three.next->letters->letter;
            three.next->letters = three.next->letters->pop();
            quant++;
        }
    }
    


    //Second, doing the same with operators. But operators is a queue, so we'll need to read behind to front
    while(three.next->operators->next != nullptr)
    {
        while(three.next->operators->next != NULL)
        {
            box* pont = three.next->operators;
            while(pont->next->next != NULL) //It stop before the last one (the next pointer is NULL)
                pont = pont->next;
            begin[quant] = three.next->operators->letter;
            pont->next = pont->next->pop();
            quant++;
        }
    }

    begin[quant] = three.next->operators->letter;
    three.next->operators->pop();

    //And, at last, exclude the branch
    three.next->letters = NULL;
    three.next->operators = NULL;
    three.next->next = NULL;
    delete three.next;
}

