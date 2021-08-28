#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
    int number;
    struct node *next;
}
node;

// Prototypes
void create(node **list, int val);
void f_insert(node **list, int val);
void free_list(node **list);

// List name
node *head = NULL;

int main(void)
{
    for (int i = 0; i < 10; i++)
    {
        create(&head, i+1);
    }
    int x = 32;

    f_insert(&head, x);

    for (node *tmp = head; tmp != NULL; tmp = tmp->next)
    {
        printf("%i\n", tmp->number);
    }

    // Free
    free_list(&head);

}

// Insert
void create(node **list, int val)
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return;
    }
    n->number = val;
    n->next   = NULL;

    if (*list == NULL)
    {
        *list = n;
        return;
    }
    else
    {
        for (node *tmp = *list; tmp != NULL; tmp = tmp->next)
        {
            if (tmp->next == NULL)
            {
                tmp->next = n;
                return;
            }
        }
    }
}

// Front insert
void f_insert(node **list, int val)
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return;
    }
    n->number = val;
    n->next   = NULL;

    if (*list == NULL)
    {
        *list = n;
        return;
    }
    else
    {
        n->next = *list;
        *list = n;
    }
}

// Free list
void free_list(node **list)
{
    if ((*list)->next == NULL)
    {
        free(*list);
        return;
    }
    free_list(&(*list)->next);
    free(*list);
}