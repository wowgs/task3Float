#include <stdio.h>
typedef struct binTree
{
    int data;
    struct binTree *left;
    struct binTree *right;
}binTree;

binTree* newBinTree(int value)
{
    binTree *tmp = (binTree*)malloc(sizeof(binTree));
    if (tmp == NULL)
    {
        printf("malloc failed");
        return;
    }
    tmp->left = tmp->right = NULL;
    tmp->data = value;
    return tmp;
}

 binTree* addElement (binTree *root, int value)
{
    if (root == NULL)
    {
       return newBinTree(value);
    }
    if (root->data < value)
    {
        root->right = addElement(root->right, value);
    }
    if (root->data > value)
    {
        root->left= addElement(root->left, value);
    }
return root;
}

binTree *min (binTree *root)
{
    if (root->left)
    {
        min(root->left);
    }
    return root;
}


binTree* removeElement (binTree *root, int value)
{
    if (root == NULL)
    {
        printf("ERROR: %d doesn't belong to set", value);
        return NULL;
    }
    if (root->data > value)
    {
        root->right = removeElement(root->right, value);
    }
    else  if (root->data < value)
    {
        root->left = removeElement(root->left, value);
    }
    else
    {
        if(!(root->right) && !(root->left))
        {
            return NULL;
        }
        else if (root->right)
        {
            binTree *cur = root->right;
            free(root);
            return(cur);
        }
         else if (root->left)
        {
            binTree *cur = root->left;
            free(root);
            return(cur);
        }
        else
        {
            binTree *rightMin = min(root->right);
            root->data = rightMin->data;
            root->right = removeElement(root->right,rightMin->data);
            return root;
        }
    }
    return root;
}

void findElement(binTree *root, int value)
{

    if (root == NULL)
    {
        printf("%d doesn't belong to set\n", value);
        return;
    }
    if (root->data > value)
    {
        findElement(root->right, value);
    }
    else if (root->data < value)
    {
        findElement(root->left, value);
    }
    else
    {
        printf("YES, %d belongs to set\n", value);
        return;
    }
}

void printDesc(binTree *root) //descending >
{
    if (root == NULL)
    {
        return;
    }
    printDesc(root->right);
    printf("%d ",root->data);
    printDesc(root->left);
}

void printAsc(binTree *root) //ascending <
{
   if (root == NULL)
    {
        return;
    }
    printAsc(root->left);
    printf("%d ",root->data);
    printAsc(root->right);
}

void print(binTree *root)
{
    if (root == NULL)
    {
        return;
    }
    if (root)
    {
        printf("(%d ",root->data);
    }
    if (root->left)
    {
        print(root->left);
    }
    else
    {
        printf("null");
    }
    printf(" ");
    if (root->right)
    {
        print(root->right);
        printf(")");
    }
    else
    {
        printf(" null)");
    }
}

void quit(binTree *root)
{
    if (root == NULL)
    {
    return;
    }
    quit(root->left);
    quit(root->right);
    free(root);
    return;
}
int main ()
{
    int j=0;
    binTree* root=NULL;
    while(j == 0)
    {
        char enter;
        int val;
        scanf("%c", &enter);
        switch (enter)
        {
            case 'a':
                scanf("%d", &val);
                root = addElement(root, val);
            break;
            case 'r':
                scanf("%d", &val);
                root = removeElement(root, val);
            break;
             case 'f':
                scanf("%d", &val);
                findElement(root, val);
            break;
            case 'p':
                print(root);
                printf("\n");
            break;
             case 's':
                printAsc(root);
                printf("\n");
            break;
             case 'd':
                printDesc(root);
                printf("\n");
            break;
            case 'q':
                quit(root);
                j = 1;
            break;
        }
    }
}
