#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <time.h>
//------------------------------------------------------------
typedef struct Person
{
    int money;
    int name;                // Vertex
    int asked;
    struct Person *favor;    // Edge
} Person;
//------------------------------------------------------------
typedef struct Graph
{
    int numberOfPeople;
    Person **favorLists;       // Adjacency lists array that represents graph
    int *edges;
} Graph;
//------------------------------------------------------------
Person* createPerson(int name);
Graph* createGraph(int peopleNumber);
void addFavor(Graph* graph, int s, int d);
void printGraph(Graph* graph);

#endif // GRAPH_H_INCLUDED
