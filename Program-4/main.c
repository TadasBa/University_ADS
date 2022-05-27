/// NAME: Tadas Baltrūnas
/// Group: 5
/// PROGRAM NR: 8
/// 2022.05
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

#define me 1 /// (BUGAS) Veikia tik kai me = 1

//-------------------------------------------------------------------------
int main()
{
    int amount = 1000;  // Integer to save amount of money that I want to ask
    int number = 8;     // Number of people

    struct Graph* graph = createGraph(number);

    // Connecting graph elements / people

    addFavor(graph, 1, 8);
    addFavor(graph, 1, 3);
    addFavor(graph, 2, 8);
    addFavor(graph, 2, 5);
    addFavor(graph, 2, 4);
    addFavor(graph, 3, 1);
    addFavor(graph, 3, 5);
    addFavor(graph, 4, 6);
    addFavor(graph, 4, 2);
    addFavor(graph, 5, 1);
    addFavor(graph, 5, 6);
    addFavor(graph, 5, 7);
    addFavor(graph, 5, 2);
    addFavor(graph, 6, 2);
    addFavor(graph, 7, 6);
    addFavor(graph, 7, 5);
    addFavor(graph, 8, 5);
    addFavor(graph, 1, 2);
    addFavor(graph, 1, 4);
    addFavor(graph, 2, 6);
    addFavor(graph, 2, 3);
    addFavor(graph, 2, 1);
    addFavor(graph, 3, 6);
    addFavor(graph, 3, 7);
    addFavor(graph, 4, 8);
    addFavor(graph, 4, 3);
    addFavor(graph, 5, 4);
    addFavor(graph, 6, 7);
    addFavor(graph, 7, 2);
    addFavor(graph, 7, 8);
    addFavor(graph, 8, 4);

    printGraph(graph);

    printf("\n");

    int check = 0;

    printf("--------------------------------------------\n\n");

    for(int i=1; i<=graph->numberOfPeople; i++)
    {
        // Getting adjacency list

        Person* thisPerson = graph->favorLists[i];

        // Terminating program if I have been asked for a favor after I myself asked for a favor

        if(i == me && check != 0)
        {
            printf("STOP: I got requested\n");
            exit(0);
        }

        // Checking if it is a first iteration

        if(i==me)
        {
            printf("I request %d $ from person: ", amount);
        }

        else
        {
            printf("Person: %d requests from person: ", i);
        }

        // Cycle to iterate through graph

        while(thisPerson != NULL)
        {
            // Checking if current person has been already asked and still has other people to ask for a favor

            if(thisPerson->asked == 1 && graph->edges[i] > 0)
            {
                while(thisPerson->favor != NULL)
                {
                    thisPerson = thisPerson->favor;

                    // Checking if the person that has been asked for a favor by the previous person has been asked before

                    if(thisPerson->asked == 0)
                    {
                        break;
                    }
                }

                // Checking for unexpected case

                if(thisPerson == NULL)
                {
                    printf("\n\nFavor can't be done\n");
                    exit(0);
                }
            }

            // Checking if the person has enough money for my request

            if(thisPerson->money < amount)
            {
                // Checking for unexpected case

                if(thisPerson->name == me && check != 0)
                {
                    printf("me\n\n");
                    printf("STOP: I got requested\n");
                    exit(0);
                }

                // Setting person that we found to ask to be asked

                thisPerson->asked = 1;
                printf("%d\n", thisPerson->name);

                // Setting next person that current person is going to ask for a favor

                i = thisPerson->name - 1;
                check++;

                // After one person has been asked marking one edge, of the adjacency list person was in, as seen

                graph->edges[i]--;

                break;
            }
            else
            {
                printf("%d\n", thisPerson->name);
                printf("\nYey, we found that %d is going to lend me %d $\n", thisPerson->name, amount);
                exit(1);
            }
        }
        printf("\n");
    }

    return 0;
}


/*
8.

Duota informacija:

 - kiek kiekvienas žmogus turi atliekamų (skolinamų) pinigų
 - kas kam yra padaręs paslaugą (gali būti situacijos, kad du žmonės yra padarę po paslaugą vienas kitam).

Jei A trūksta pinigų ---> tai jis gali paprašyti bet kurio žmogaus, kuriam yra padaręs paslaugą,
paskolinti jam reikiamą sumą ---> jei tas neturi reikiamos sumos, elgiasi taip pat,.

Patikrinti:

ar aš paprašęs, pavyzdžiui, paskolinti 1000 LT galiu savo ruožtu sulaukti prašymo paskolinti pinigų,
jei šiuo metu kitiems papildomų pinigų nereikia.

*/
