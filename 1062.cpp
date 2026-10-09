/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Gabriel Isoton Ferreira
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1080
Data        : 23/09/2026
Objetivo    : Check the trains' disposition
Dificuldade : None
Uso de IA   : Searching about syntax (a serch machine)
-------------------------------------------------------------------------- */

#include <iostream>
#include <cstdio>
using namespace std;

//For this problem, we'll use the stack structure. So:
struct box
{
    int train;
    box *next;

    void push(int num); // This will creat a new box soon after the head
    int top(); //This method will return the first after head train's number and delete the read corresponded one
};

int main()
{
    //Creating the stack
    box station;
    station.next = NULL;
    station.train = 0;

    int quant; //It will stock the trains' number
    cin >> quant;

    while(quant != 0)
    {
        int aux = 1, train; // The first guy represents the closest train coming from A and the other the exitinsg train
        for(int i = 0; i < quant; i++)
        {
            //Reading the string, one by one
            cin >> train;

            if(train == 0) break; //If there isn't train entering, stop the verification

            //While the train's num is bigger than the wanted, all the other (from 1 to the pretended) will enter in the station
            while(aux < train)
            {
                station.push(aux);
                aux++; //After one enter, we'll avaliate if the next one is the wanted one
            }

            if(aux == train) aux++; //It's like: "Oh, you're the train, so pass and we'll check the rest"
            else if(station.next == NULL || train != station.top()) //If this occur, so that output is impossible
            {
                for(; i < quant-1; i++) cin.ignore(2); //Cleaning the input -> Cleaning the next spacebar or '\n' and next next num
                while(station.next != NULL) station.top(); //Cleaning the stack
                train = -1; // This is a flag, indicating that a error occured
                break;
            }
        }

        //If all trains passed (in the above check) correctly, the last train's number is in 1 to quant, so it's bigger than 0
        if(train > 0) cout << "Yes" << endl;
        //If train's number is minor than 0, a error occured
        else if(train < 0) cout << "No" << endl;
        //If train is equal to 0, we'll need to check if a new group'll come
        else cin >> quant;
    }
}

void box::push(int num)
{
    //Creating a new box
    box *newest = new box;
    newest->train = num;

    //Linking that to the stack
    newest->next = this->next;
    this->next = newest;
}

int box::top()
{
    //Saving the return's number
    int ret = this->next->train;

    //Deleting the next head box
    box *del = this->next;
    this->next = del->next; //Maintaining the stack
    del->train = 0;
    del->next = NULL;
    delete del;

    return ret;
}
