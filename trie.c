#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define C_MAX 45
#define ALPHABET_SIZE 28 // 26 + ' and space

typedef struct node
{
    char *name;
    struct node *next[ALPHABET_SIZE];
}
node;

// Declarations
void insert(node **list, char *name, int loop_count);
void free_list(node **list);

node *head = NULL;

int main(void)
{
    // Clears log file
    remove("trie_log.txt");
    // Head
    head = malloc(sizeof(node));
    if (head == NULL)
    {
        return 1;
    }
    // Initialize head to NULL
    head->name = NULL;
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        head->next[i] = NULL;
    }
    // Name Malloc
    char *name = malloc(C_MAX + 2);
    if (name == NULL)
    {
        return 1;
    }

    FILE *file = fopen("Nomes.txt", "r");
    char c = 'a';
    int loop_count;

    // Reads file into trie
    while (true)
    {
        loop_count = 0;
        while (true)
        {
            // Check if str is within character limit
            if (loop_count > C_MAX)
            {
                printf("%i char max!\n", C_MAX);
                printf("%s\n", name);
                break;
            }
            c = fgetc(file);
            // Check for str end
            if (c == '\n' || c == EOF)
            {
                break;
            }
            name[loop_count] = c;
            loop_count++;
        }
        // Check for EOF
        if (c == EOF && loop_count == 0)
        {
            free(name);
            break;
        }
        // Insert str
        insert(&head, name, loop_count);
        // Clears the buffer
        for (int i = 0; i < loop_count; i++)
        {
            name[i] = '\0';
        }
    }
    node *debug = head; // Local pointer to HEAD

    // Free
    free_list(&head);
    fclose(file);
    return 0;
}

void insert(node **list, char *name, int c_count)
{
    int map[c_count];
    // Copy str
    char* node_name = malloc(c_count + 1);
    for (int i = 0; i <= c_count; i++)
    {
        node_name[i] = name[i];
    }
        if (!strcmp(node_name, "he'd"))
    {
        printf("subcommittee's \n");
    }
    FILE *loge = fopen("trie_log.txt", "a");
    fprintf(loge, "%s - %p\n", node_name, &node_name);
    fclose(loge);

    // Populate map
    for (int i = 0; i < c_count; i++)
    {
        if ((int) name[i] > 96 && (int) name[i] < 123)
        {
            map[i] = (int) name[i] - 97;
        }
        else if((int) name[i] > 64 && (int) name[i] < 91)
        {
            map[i] = (int) name[i] - 65;
        }
        else if((int) name[i] == 32)
        {
            map[i] = 26;
        }
        else if((int) name[i] == 39)
        {
            map[i] = 27;
        }
    }

    // Create path
    node *nav = *list;
    for (int i = 0; i < c_count; i++)
    {
        // 1 - Opens new path
        if (nav->next[map[i]] == NULL)
        {
            // Create node
            node *tmp = malloc(sizeof(node));
            tmp->name = NULL;
            if (tmp == NULL)
            {
                return;
            }
            // Initialize node pointers to NULL
            for (int j = 0; j < ALPHABET_SIZE; j++)
            {
                tmp->next[j] = NULL;
            }

            // Checks for end of chain
            if (i == c_count - 1)
            {
                tmp->name = node_name;
                nav->next[map[i]] = tmp;
            }
            else
            {
                nav->next[map[i]] = tmp;
                nav = nav->next[map[i]];
            }
        }
        // 2 - Navigate through existing path
        else
        {
            if (i == c_count - 1)
            {
                // Check for already saved str
                if (nav->next[map[i]]->name != NULL)
                {
                    free(node_name);
                }
                else
                {
                    nav->next[map[i]]->name = node_name;
                }
            }
            nav = nav->next[map[i]];
        }
    }
    return;
}

void free_list(node **list)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if ((*list)->next[i] != NULL)
        {
            free_list(&(*list)->next[i]);
            (*list)->next[i] = NULL;
        }
    }
    free((*list)->name);
    free(*list);
    return;
}