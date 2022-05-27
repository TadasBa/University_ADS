#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"

// Create a person
Person* createPerson(int name)
{
    Person* newPerson = malloc(sizeof(Person));
    newPerson->name = name;
    newPerson->favor = NULL;
    newPerson->asked = 0;

    return newPerson;
}

// Create a graph
Graph* createGraph(int peopleNumber)
{
    Graph* graph = malloc(sizeof(Graph));
    graph->numberOfPeople = peopleNumber;

    graph->favorLists = malloc(peopleNumber * sizeof(Person*));
    graph->edges = malloc(peopleNumber * sizeof(Person));

    for(int i=1; i <= peopleNumber; i++)
    {
        graph->favorLists[i] = NULL;
        graph->edges[i] = 0;

    }

    return graph;
}

// Add edge
void addFavor(Graph* graph, int s, int d)
{

    // Add edge from s to d
    Person* newPerson = createPerson(d);

    newPerson->favor = graph->favorLists[s];
    graph->favorLists[s] = newPerson;
    graph->favorLists[s]->money = d * 100;
    graph->edges[s]++;

}

// Print the graph
void printGraph(Graph* graph)
{
    for (int i=1; i <= graph->numberOfPeople; i++)
    {
        Person* thisPerson = graph->favorLists[i];
        printf("\nPerson: %d (%d $)(%d edges) -->  ", i, i * 100, graph->edges[i]);

        while (thisPerson != NULL)
        {
            if(thisPerson->favor == NULL)       // Checking if we are now looking at last person of the adjacency list
            {
                printf("%d (%d $)", thisPerson->name, thisPerson->money);
                thisPerson = thisPerson->favor;
                break;
            }

            printf("%d (%d $) - ", thisPerson->name, thisPerson->money);
            thisPerson = thisPerson->favor;
        }

        printf("\n");
    }
}
