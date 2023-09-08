#include <stdio.h>
#include <stdlib.h>

typedef struct s_node
{
    int data;
    struct s_node* prev;
    struct s_node* next;
} t_node;

t_node* create_node(int data)
{
    t_node* new_node = (t_node*)malloc(sizeof(t_node));
    if (new_node)
    {
        new_node->data = data;
        new_node->prev = NULL;
        new_node->next = NULL;
    }
    return new_node;
}

void insert_node(t_node** head, int data)
{
    t_node* new_node = create_node(data);
    if (*head == NULL)
    {
        *head = new_node;
        (*head)->prev = *head;
        (*head)->next = *head;
    }
    else
    {
        new_node->next = *head;
        new_node->prev = (*head)->prev;
        (*head)->prev->next = new_node;
        (*head)->prev = new_node;
    }
}

void print_list(t_node* head)
{
    if (head == NULL)
        return;

    t_node* current = head;
    do
    {
        printf("Node data: %d\n", current->data);
        current = current->next;
    } while (current != head);
}

int main()
{
    t_node* head = NULL;

    insert_node(&head, 1);
    insert_node(&head, 2);
    insert_node(&head, 3);

    printf("Circular Doubly Linked List:\n");
    print_list(head);

    return 0;
}
