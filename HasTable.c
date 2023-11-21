#include "DoubleLinkedList.c"
#define COLUMNS 53
#define MULTIPLY 467
#define PATH "C:\\projetos\\Trabalho-Final-Implementa-o-de-uma-Tabela-de-Espalhamento-Tabela-Hash--main\\nomes.txt"

//columns
typedef struct SCol
{
    struct SCol* prev;
    struct SList* list;
    int key;
    struct SCol* prox;
}COL;
//hash table
typedef struct SHashTable{
    struct SCol* head;
    struct SCol* tail;
    int size;
}HASHTABLE;
//err
void getInitializationErr()
{
    printf("\nIt is already defined\n");
}
void getFileErr()
{
    printf("File not found or can`t be open");
}

//create hashtable
HASHTABLE* CreateTableHash()
{
    HASHTABLE* hash = (HASHTABLE*) malloc(sizeof(HASHTABLE));
    if (hash != NULL)
    {
        hash->head = NULL;
        hash->tail = NULL;
        hash->size = 0;
        return hash;
    }else
    {
        return NULL;
    }
}
//creating columns
COL* createCol(int key)
{
    COL* col =(struct SCol*) malloc(sizeof(COL));
    if (col != NULL)
    {
        col->prev= NULL;
        col->prox = NULL;
        col->list = createList();
        col->key = key;
        return col;
    }else
    {
        return NULL;
    }
}
//add columns
int addColumns(HASHTABLE* hash, int key)
{
    COL* col = createCol(key);
    if (col != NULL)
    {
        if(hash->tail == NULL)
        {
            col->prox = hash->tail;
            col->prev = hash->head;
            hash->head = col;
            hash->tail = col;
        }else
        {
            col->prev = hash->tail;
            col->prox = hash->tail->prox;
            hash->tail->prox = col;
            hash->tail = col;
        }
        hash->size++;
        return 1;
    }else
    {
        getOverflowErr();
        return 0;
    }
}
//auto create hash table
int autoDefineHashTable(HASHTABLE* hash, int Columns)
{
    if (hash->size == 0 && hash->head == NULL && hash->tail == NULL)
    {
        for (int i = 0; i < Columns; i++)
        {
            addColumns(hash, i);
        }
        return 1;
    }else
    {
        getInitializationErr();
        return 0;
    }
}
//what key will be
int hashing(HASHTABLE* hash, char name[NAME_SIZE], int size, int columns, int multiply)
{
    int key = 0;
    for (int i = 0; i < size; i++)
    {
        if (name[i]!='\0')
        {
            key = ((multiply * key) + name[i]) % columns;
        }
    }
    return key;
}
//find the key on hash table
COL* findColumn(HASHTABLE* hash, int key)
{
    COL* col = hash->head;
    while (col->key != key && col != NULL)
    {
        col = col->prox;
    }
    return col;
}
//add the name on the correct column
int addOnColumn(COL* col, char name [NAME_SIZE])
{
    return addTail(col->list, name);
}
//add the name on the correct column
int removeOnColumn(COL* col, char name [NAME_SIZE])
{
    return removeNode(col->list, findNodePrev(col->list, name));
}
//read the file
FILE* loadingData(char name[])
{
    FILE* fptr = fopen(name, "r");
    if (fptr != NULL)
    {
        return fptr;
    }else
    {
        getFileErr();
        return NULL;
    }
}
//gets all names and put at the hash
int autoHashData(FILE* fptr, HASHTABLE* hash, int size, int columns, int multiply){
    if (fptr != NULL)
    {
        char name[NAME_SIZE];  
        while(fgets(name, NAME_SIZE, fptr)) 
        {
            for (int i = 0; i < NAME_SIZE; i++)
            {
                if (name[i]=='\n' || name[i]==' ' || name[i]=='\t')
                {
                    name[i]='\0';
                }
            }
            addOnColumn(findColumn(hash, hashing(hash, name, size, columns, multiply)), name);
        }
        return 1;
    }else
    {
        return 0;
    }

}
//see the size of all elements on hash table
//print all values
int runHashTable(HASHTABLE* hash)
{
    if (hash->head != NULL)
    {
        COL* col = hash->head;
        while (col != NULL)
        {
            printf("%2i\t", col->key);
            printf("%i\n", col->list->size);
                col = col->prox;
        }
        return 1;
    }else
    {
        getUnderflowErr();
        return 0;
    }
}
//see a list
int seeHashList(HASHTABLE* hash, int key)
{
    printf("start\n");
    COL* col = findColumn(hash, key);
    runList(col->list);
    printf("\nend\n");
    return 1;
}
//sort
int sortColOnHashTable(HASHTABLE* hash)
{
    if (hash->head != NULL)
    {
        COL* col = hash->head;
        while (col != NULL)
        {
            quickSort(col->list->head, col->list->tail);
            col = col->prox;
        }
        return 1;
    }else
    {
        getUnderflowErr();
        return 0;
    }
}
//!important!
//clear memory
int freeHash(HASHTABLE* hash)
{
    if (hash->head != NULL)
    {
        COL* col = hash->head;
        while (col != NULL)
        {
            COL* aux = col;
            freeList(col->list);
            col = col->prox;
            free(aux);
        }
    }
    free(hash);
    return 1;
}
void main()
{
    //init
    int op = 1;
    char name[NAME_SIZE];
    HASHTABLE* hash = CreateTableHash(COLUMNS);
    autoDefineHashTable(hash, COLUMNS);
    //loading
    FILE* fptr = loadingData(PATH);
    autoHashData(fptr, hash, NAME_SIZE, COLUMNS, MULTIPLY);
    fclose(fptr);
    //sort
    sortColOnHashTable(hash);
    //view
    while (op > 0)
    {
        printf("---------------------------\n");
        printf("1.add a new name\n2.remove a name\n3.Sort all names \n4.See hash table size\n5.print a list\n6.find a name key\n0.close\nop:\n");
        scanf("%i", &op);
        printf("---------------------------\n");
        if (op == 1)
        {
            name[0]= 'a';
            printf("name:");
            scanf(" %[^\n]s", name);
            for (int i = 0; i < NAME_SIZE; i++)
            {
                if (name[i]=='\n' || name[i]==' ' || name[i]=='\t')
                {
                    name[i]='\0';
                }
            }
            printf("key:%i\n", hashing(hash, name, NAME_SIZE, COLUMNS, MULTIPLY));
            addOnColumn(findColumn(hash, hashing(hash, name, NAME_SIZE, COLUMNS, MULTIPLY)), name);
        }else if (op == 2)
        {
            name[0]= 'a';
            printf("name:");
            scanf(" %[^\n]s", name);
            for (int i = 0; i < NAME_SIZE; i++)
            {
                if (name[i]=='\n' || name[i]==' ' || name[i]=='\t')
                {
                    name[i]='\0';
                }
            }
            printf("key:%i\n", hashing(hash, name, NAME_SIZE, COLUMNS, MULTIPLY));
            removeOnColumn(findColumn(hash, hashing(hash, name, NAME_SIZE, COLUMNS, MULTIPLY)), name);   
        }else if(op == 3)
        {
            sortColOnHashTable(hash);
        }else if (op == 4)
        {
            runHashTable(hash);
        }else if(op == 5)
        {
            int key;
            printf("key:");
            scanf("%i", &key);
            seeHashList(hash, key);
        }else if(op == 6)
        {
            name[0]= 'a';
            printf("name:");
            scanf(" %[^\n]s", name);
            for (int i = 0; i < NAME_SIZE; i++)
            {
                if (name[i]=='\n' || name[i]==' ' || name[i]=='\t')
                {
                    name[i]='\0';
                }
            }
            printf("key:%i\n", hashing(hash, name, NAME_SIZE, COLUMNS, MULTIPLY));
        }
    }
    //close
    freeHash(hash);
}