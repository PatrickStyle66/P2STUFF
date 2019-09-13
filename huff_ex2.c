#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node 
{ 
    char byte;
	struct node *left, *right; 
}Node;

bool is_empty(Node *node)
{
    return (node == NULL);
}

Node* new_node(char byte) 
{ 
	Node* new_node = (Node*)malloc(sizeof(Node)); 

    new_node->byte = byte;
	new_node->left = NULL;
    new_node->right = NULL;

	return new_node; 
} 

Node* rebuild_tree(Node* node, char post[], int *postIndex)
{
	if(post[*postIndex] == '*')
	{
		node = new_node('*');
		(*postIndex)--;
		node->right  = rebuild_tree(node->right, post, postIndex);
		node->left = rebuild_tree(node->left, post, postIndex);
	}
	else
	{
		node = new_node(post[(*postIndex)]);
		(*postIndex)--;
	}
	return node;
}

void print_post(Node* node) 
{ 
	if(!is_empty(node))
    {
        print_post(node->left); 
        print_post(node->right); 
        printf("%c", node->byte); 
    }
}

void print_tree(Node* node)
{
    if(!is_empty(node))
    {
        printf("------------------------------\n");
        printf("The tree ");
        print_post(node);
        printf(" has:\n");
        printf("- Left subtree: ");
        print_post(node->left);
        printf("\n- Right subtree: ");
        print_post(node->right);
        printf("\n------------------------------\n");

        print_tree(node->left);
        print_tree(node->right);
    }
}

void make_decode(Node* node, char* byte, int i){
	if(is_empty(node)) return;

    Node *left = node->left, *right = node->right;

	if(left == NULL && right == NULL)
	{
		byte[i] = '\0';
		printf("\n%c : %s", node->byte, byte);
	}
	else
	{
		byte[i] = '0';
		make_decode(left, byte, i + 1);

		byte[i] = '1';
		make_decode(right, byte, i + 1);
	}
}

int main() 
{ 
    char entry[200], temp[200];
    
    scanf("%s", entry);

    int tempsize = strlen(entry), i;
	int post[tempsize];

    for(i = 0; i < tempsize; i++) post[i] = entry[i];

	int size = sizeof(post) / sizeof(post[0]);
    int tam = size - 1;

    Node *root = rebuild_tree(root, entry, &tam);

    char* byte = (char*)malloc((tam + 1)*sizeof(char));

    print_tree(root);
    printf("\nDecoding Tree is:\n");
    make_decode(root, byte, 0);

	return 0; 
}