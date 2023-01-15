#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int weight = INFINITY;
int arrlenth = 0;
pnode graph = 0;
int mini = INFINITY;


////////////Dijkstra/////////////


int isEmpty(pnode p){
    if(p==NULL){
    return 1;
    }
    return 0;
}

int isEmpty_d(pnodeD p){
    if(p==NULL){
    return 1;
    }
    return 0;
}

pnodeD getD(pnodeD head, int id) 
{
    while (!(isEmpty_d(head))) 
    {
        if (head->node->id == id) {
            return head;
        }

        head = head->next;
    }
    return NULL;
}


pnodeD getD_wet(pnodeD head, int wet) 
{
    while (!(isEmpty_d(head))) 
    {
        if(head->visit==0){
            if (head->weight == wet) {
                head->visit =1;
                return head;
            }
        }
        head = head->next;
    }
    return NULL;
}



void deleteD(pnodeD p) 
{
    while (p != NULL)
    {
        pnodeD temp = p;
        p = p->next;
        free(temp);
    }
}



pnode GetNode2(int id,pnode head ){
    pnode cur =head;
    while (!(isEmpty(cur)))
    {
        if(cur->id == id){
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}


int relax(pnodeD src,pnodeD dest, pedge e)
{
    
    int Wedge = e->weight;
    int Wsrc = src->weight;
    int Wdest = dest->weight;
    if (Wdest > Wsrc + Wedge)
    {
        dest->weight = Wsrc + Wedge;
       // dest->parent = src;
    }
return dest->weight;
}

pnodeD reset(pnode first, int src) 
{
    pnodeD head = NULL;
    pnodeD *n = &head;

    while (!(isEmpty(first))) 
    {
        (*n) = (pnodeD) malloc(sizeof(nodeD));
        if ((*n) == NULL) 
        {
            exit(0);
        }

        (*n)->node = first;
        if (first == GetNode2(src, first))
        {
            (*n)->weight = 0;
        } 
        else 
        {
            (*n)->weight = INFINITY;
        }
        (*n)->visit = 0;
        (*n)->next = NULL;
        n = &((*n)->next);
        first = first->next;
    }
    return head;
}

////////////////////SHORTEST PASH/////////////////

int shortest_Path(pnode head, int src, int des) 
{
    // GET SRC
    pnodeD headD = reset(head, src);

    pnodeD temp = getD_wet(headD,0);


     while (!(isEmpty_d(temp))) 
    {
        pedge E_ind = temp->node->edges;

        while (E_ind != NULL) 
        {
            //faind dest
           pnodeD n = getD(headD, E_ind->endpoint->id);
        
            // apdayt the min 
            int relax1 = relax(temp, n, E_ind);
             if(relax1 < mini){
                  mini = relax1;
              }
            E_ind = E_ind->next;

        }

        // find the node of min
        temp = getD_wet(headD,mini);
        mini = INFINITY; 

    }
    int D = getD(headD, des)->weight;

    if (D == INFINITY)
    {
        D = -1;
    }
   deleteD(headD);

    return D;
}





/////////////////TSP////////////////

void input_Array(int* fromArr,int* toArr, int arrLenght) 
{
    for (int i = 0; i < arrLenght; ++i) 
    {
        toArr[i] = fromArr[i];
    }
}

void swap(int* arr, int i, int j)
{
    int temp = arr[i];
    arr[i]= arr[j];
    arr[j] = temp;
}

void PermotitionOfArr(int* arr, int arrLength)
{
    int tempWeight = 0;
    for (int i = 0; i < arrLength-1; ++i) 
    {
        int D = shortest_Path(graph,arr[i], arr[i+1]);
        if (D == -1)
        {
            tempWeight = INFINITY;
            return;
        }
        tempWeight += D;
    }
    if (tempWeight < weight)
    {
        weight = tempWeight;
    }
}

void permotion( int start ,int* arr, int arrLength){
    if (start == arrLength -1 ){
        PermotitionOfArr(arr, arrLength);
        return;
    }
    for (int i = start; i < arrLength; ++i) {
        int* arrCopy = (int*)(calloc(arrLength, sizeof(int)));
        input_Array(arr,arrCopy,arrLength);
        swap(arrCopy,start, i);
        permotion(start + 1, arrCopy, arrLength);
        free(arrCopy);
    }
}

int TSP(pnode head)
{
    weight = INFINITY;
	arrlenth = -1;
    graph = head;
    scanf("%d", &arrlenth);
    int *arr = (int *) (calloc(arrlenth, sizeof(int)));

    for (int i = 0; i < arrlenth; i++) {
        scanf("%d", &arr[i]);
    }
    int *arrCopy = (int *) (calloc(arrlenth, sizeof(int)));
    input_Array(arr,arrCopy,arrlenth);
    permotion(0,arrCopy,arrlenth);
    free(arr);
    free(arrCopy);
    if (weight == INFINITY){
        weight = -1;
    }
    return weight;
}
