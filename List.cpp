#include <stdio.h>
#include <math.h>

struct node
{
    double value = NAN;
    size_t next = -1;
    size_t prev = -1;
};


struct List {
    node* data = 0;
    size_t maxind = 0;
    size_t free = 0;
};




int list_init(List* list, size_t initsize)
{
    // printf("initiating list %p with %d", list, initsize);

    list = (List*) calloc(1, sizeof(List));

    list->data = (node*) calloc(initsize, sizeof(node));
    // printf("<%p>", list->data);
    list->maxind = initsize-1;
    list->free = 0;

    list->data[0].next = 1;

    printf("maxind is %d\n", list->maxind);

    for (int i = 1; i < initsize - 1; i++) {
        printf("%d ", i);
        (list->data[i]).next = i + 1;
        (list->data[i]).prev = i - 1;
    }

    (list->data[list->maxind]).next = 0;
    (list->data[list->maxind]).prev = list->maxind - 1;


    printf("\nend init\n");
    // printf("free is %p = %d -> %lf", &(list->free), list->free, list->data[list->free]);
    return 0;
}

size_t list_insert(List* list, size_t index, double insert_value) //вставляет в список число после элемента номер index, возвращает значение ячейки, куда была произведена запись
{
    if ((list->data)[list->free].value != NAN) {
        printf("attempt to insert in full list\n");
        return -1;
    }

    (list->data[list->free]).value  = insert_value;
    (list->data[list->free]).prev = index;
    (list->data[list->free]).next = (list->data[index]).next;

    if ( (list->data[index]).next != -1)
        list->data[list->data[index].next].prev = list->free;

    (list->data[index]).next = list->free;

    size_t freeold = list->free;

    list->free = list->data[(list->data[index].next)].next;

    return freeold;
}

size_t list_delete(List* list, size_t index)
{
    if (index > list->maxind) {
        printf("attempt to delete already void element\n");
        return -1;
    }
    if (list->data[index].value == NAN) {
        printf("attempt to delete already void element\n");
        return -2;
    }

    list->data[list->data[index].prev].next = list->data[index].next;
    list->data[list->data[index].next].prev = list->data[index].prev;

    list->data[index].value = NAN;
    list->data[index].next = -1;
    list->data[index].prev = -1;

    return index;
}

int print_list(List* list)
{
    printf("printing list:\n");
    int i = 0;
    int k = 0;
    printf("%lf", list->maxind);
    while (i < list->maxind)
    {
        // printf("\n");
        // printf("                     ----> prev = %d\n", list->data[i].prev);
        // printf("%d: value = %lf---|\n", i, list->data[i].value);
        // printf("                     ----> next = %d\n", list->data[i].next);
        printf("print №%d\n", i);
        printf("%dnd element is list is %lf (pos in array %d, next is %d, prev is %d", i, (list->data[i]).value, i, (list->data[i]).next, (list->data[i]).prev);
        i++;
    }

    return 0;
}

int main()
{
    List* list = 0;
    list_init(list, 5);
    print_list(list);

    return 0;

    // list_insert(list, 1, 1);
    // list_insert(list, 4, 2);
    // list_insert(list, 9, 3);


    // for (int i = 0; i < 5; i++)
    //     list_insert(list, i*i, i);

    // print_list(list);
    return 0;
}
