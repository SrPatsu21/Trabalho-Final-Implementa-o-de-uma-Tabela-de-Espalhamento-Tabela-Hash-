#ifndef DoubleLinkedList
#define DoubleLinkedList
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NULL ((void *)0)
#define NAME_SIZE 16
//struct
//node
typedef struct SNode
{
    struct SNode* prev;
    char name[NAME_SIZE];
    struct SNode* prox;
}NODE;
//list
typedef struct SList{
    struct SNode* head;
    struct SNode* tail;
    int size;
}LIST;
//errs
void getOverflowErr()
{
    printf("\nOverflow: exceeded the device's storage capacity!\n");
}
void getUnderflowErr()
{
    printf("\nUnderflow: list is NULL\n");
}
void getPivotErr()
{
    printf("\npivot is the last one or list empty\n");
}
//alloc LIST
LIST* createList()
{
    LIST * list =(LIST*) malloc(sizeof(LIST));
    if (list != NULL)
    {
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
        return list;
    }else
    {
        return NULL;
    }
}
//alloc node
NODE* createNode()
{
    NODE* node;
    node =(struct SNode*) malloc(sizeof(NODE));
    if (node != NULL)
    {
        node->prev= NULL;
        node->prox = NULL;
        for (int i = 0; i < NAME_SIZE; i++)
        {
            node->name[i] = '\0';
        }
        
        return node;
    }else
    {
        return NULL;
    }
}

//Node operations
/*
pivot is a reference to where place or remove
*/

//add node on list
int addNode(LIST* list, char name [NAME_SIZE], NODE* pivot)
{
    NODE* node = createNode();
    if (node != NULL)
    {
            strcpy(node->name, name);
            if(pivot == NULL)
            {
                if(list->size == 0)
                {
                    list->tail = node;
                }else
                {
                    list->head->prev = node;
                }
                node->prox = list->head;
                list->head = node;
            }else
            {
                node->prev = pivot;
                node->prox = pivot->prox;
                if (pivot->prox == NULL)
                {
                    list->tail = node;
                }else
                {
                    node->prox->prev = node;
                }
                pivot->prox = node;
            }
        list->size++;
        return 1;
    }else
    {
        getOverflowErr();
        return 0;
    }
    
}
//other add
    //add head
    int addHead(LIST* list, char name [NAME_SIZE])
    {
        return addNode(list, name, NULL);
    }
    //add tail
    int addTail(LIST* list, char name [NAME_SIZE])
    {
        return addNode(list, name, list->tail);
    }

//to find some node using info
NODE* findNode(LIST* list, char name [NAME_SIZE])
{
    NODE* node;
    if (list->head != NULL)
    {
        node = list->head;
        int i = 1;
        while (i == 1)
        {
            if (node->name == name)
            {
                i=0;
            }else if(node->prox == NULL)
            {
                node = NULL;
                i=0;
            }else
            {
                node = node->prox;
            }
        }      
    }else
    {
        getUnderflowErr();
        node = NULL;
    }
    return node;
}
//to find the prev of the node
NODE* findNodePrev(LIST* list, char name [NAME_SIZE])
{
    NODE* node = findNode(list, name);
    if (node == NULL)
    {
        return NULL;
    }else{
        return node->prev;
    }
}
//remove node on list
//in case of receiving parameter from find Pivot, if find Pivot don't find the pivot, will return NULL thats mean remove from head
int removeNode(LIST* list, NODE* pivot)
{
    if(list->size == 0){
        getUnderflowErr();
        return 0;
    }else
    {
        NODE* node;
        if(pivot == NULL)
        {
            node = list->head;
            list->head = node->prox;
            if(node->prox == NULL)
            {
                list->tail = NULL;
            }else
            {
                node->prox->prev = NULL;
            }
            free(node);
            list->size--;
            return 1;
        }else
        {
            if(pivot->prox == NULL)
            {
                getPivotErr();
                return 0;
            }else
            {
                node = pivot->prox;
                pivot->prox = node->prox;
                if(node->prox == NULL)
                {
                    list->tail = pivot;
                }else
                {
                    node->prox->prev = pivot;
                }
                free(node);
                list->size--;
                return 1;
            }
        }
    }
}
//other remove
    //remove head
    int removeHead(LIST* list)
    {
        return removeNode(list, NULL);
    }
    //remove tail
    int removeTail(LIST* list)
    {
        return removeNode(list, list->tail->prev);
    }
//print all values
int runList(LIST* list)
{
    int cont = 0;
    if (list->head != NULL)
    {
        NODE* node = list->head;
        while (node != NULL)
        {
            cont++;
            if (cont == 4)
            {
                cont = 0;
                printf("\n");
            }
            printf("%16s", node->name);
            node = node->prox;
        }
        return 1;
    }else
    {
        getUnderflowErr();
        return 0;
    }
}
//print all values end to start
int runBackList(LIST* list)
{
    if (list->tail != NULL)
    {
        NODE* node = list->tail;
        while (node != NULL)
        {
            printf("%s \n", node->name);
                node = node->prev;
        }
    }else
    {
        getUnderflowErr();
    }
}
//!important!
//clear memory 
int freeList(LIST* list)
{
    if (list->head != NULL)
    {
        NODE* node = list->head;
        while (node != NULL)
        {
            NODE* aux = node;
            node = node->prox;
            free(aux);
        }
    }
    free(list);
    return 1;
}
//------------------------------------------------------------------------------------------------------------------------
//smal or equal
int isSmaller(NODE* ns, NODE* ne)
{
    if (ns != NULL && ne != NULL)
    {
        if (ns == ne)
        {
            return 1;
        }else
        {
            int v1 = 0;
            int v2 = 0;
            for (int i = 0; i < NAME_SIZE && v1 == v2; i++)
            {
                v1 += ns->name[i];
                v2 += ne->name[i];
            }
            if (v1 <= v2)
            {
                return 1;
            }else
            {
                return 0;
            }
        }
    }else
    {
        return 0;
    }
}
//switch two values in an array
void swap(NODE* i, NODE* j)
{
    char aux [NAME_SIZE];
	strcpy(aux, i->name);
	strcpy(i->name, j->name);
	strcpy(j->name, aux);
}
//find pivot and swap
NODE* partition(NODE* start, NODE* end)   
{    
    NODE *i = start->prev;   
    for (NODE *j = start; j != end; j = j->prox)   
    {   
        if (isSmaller(j, end))   
        {   
            i = (i == NULL)? start : i->prox;   
            swap(i, j);   
        }   
    }   
    i = (i == NULL)? start : i->prox;
    swap(i, end);   
    return i;   
}
//sort list
void quickSort(NODE* start, NODE* end)   
{   
    if (end != NULL && start != end && start != end->prox)   
    {   
        NODE* p = partition(start, end);   
        quickSort(start, p->prev);   
        quickSort(p->prox, end);   
    }   
}  
#endif