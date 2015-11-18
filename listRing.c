#include <stdio.h>

typedef struct node
{
    int data;
    struct  node *next;
} node;

void createRing(node **head, node **last)
{
    (*last)->next=(*head);
}

void cheackRing(node *head)
{
    node *p1;
    node *p2;
    p1 = head;
    p2 = head;
    int k = 0;
    node *tmp = p2->next;

    if (tmp == head)
    {
         printf("yes\n");
         k = 1;
    }

    while((tmp->next)&&(p1)&&(k != 1))
    {
        p1 = p1->next;
        p2 = tmp->next;
        tmp = p2->next;

        if (p1 == p2)
        {
            printf("yes\n");
            k = 1;
        }

    }

    if(k != 1)
    {
        printf("no\n");
    }

}
void add(node **head, node **last, int val)
{
    node *tmp = (node*) malloc(sizeof(node));
    tmp->data = val;

    if(*head == NULL)
    {
	tmp->next = *head;
	*head = tmp;
	*last = *head;
    }

    else
    {
        tmp->next = NULL;
        (*last)->next = tmp;
        (*last) = tmp;
    }
}

void rem(node **head, int val)
{
    node *cur = *head;
    node *prev = NULL;
    while (cur != NULL)
    {
        if (cur->data == val)
        {
            if (prev != NULL)
            {
                prev->next = cur->next;
            }

            else
            {
                *head = cur->next;
            }
            cur = NULL;
        }

        else
        {
            prev = cur;
            cur = cur->next;
        }
    }
}


void print(node *head)
{

   while (head != NULL)
   {
       printf("%d ",head->data);
       head = head->next;
   }
}

void quit(node *head)
{
    node *tmp;
    while (head != NULL)
    {
        tmp = head;
        head =(head)->next;
        free(tmp);
    }
}

int main()
{
    node *head = NULL;
    node *last = NULL;
    int j = 0;
    while(j == 0)
    {
        char enter;
        int val;
        scanf("%c", &enter);
        switch (enter)
        {
            case 'a':
                scanf("%d", &val);
                add(&head, &last, val);
            break;
            case 'r':
                scanf("%d", &val);
                rem(&head, val);
            break;
            case 'p':
                print(head);
                printf("\n");
            break;

            case 'q':
                quit(&head);
                j++;
            break;

            case 'n':
               createRing(&head,&last);
            break;

            case 't':
               cheackRing(head);
            break;

        }
        }
}
