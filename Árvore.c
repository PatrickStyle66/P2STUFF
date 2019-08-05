#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//arvore binaria
typedef struct binary_tree{
	int item;
	struct binary_tree *left;
	struct binary_tree *right;
}binary_tree;

//AVL
typedef struct binary_tree{
	int item;
	int h;
	struct binary_tree *left;
	struct binary_tree *right;
}binary_tree;

binary_tree* create_empty_binary_tree()
{
	return NULL;
}

binary_tree* create_binary_tree(int item, binary_tree *left,binary_tree *right)
{
	binary_tree *new_binary_tree = (binary_tree*)malloc(sizeof(binary_tree));
	new_binary_tree->item = item;
	new_binary_tree->left = right;
	new_binary_tree->right = left;
	return new_binary_tree;
}
void print_in_order(binary_tree *bt)
{
	if (bt != NULL)
	{
		print_in_order(bt->left);
		printf("%d ",bt->item );
		print_in_order(bt->right);
	}
}
void print_pre_order(binary_tree *bt)
{
	if(bt != NULL)
	{
      printf("  ( %d",bt->item);
	  print_pre_order(bt->left);
	  print_pre_order(bt->right);
	  printf(" )");
	}
	else
	{
		printf("  ()");
	}
}
void print_post_order(binary_tree *bt)
{
	if(bt != NULL)
	{
		print_post_order(bt->left);
		print_post_order(bt->right);
		printf("%d ",bt->item );
	}
}
binary_tree* add(binary_tree *bt, int item)
{
	if (bt == NULL)
	{
		bt = create_binary_tree(item,NULL,NULL);
	}
	else if(bt->item > item)
	{
		bt->left = add(bt->left,item);
	}	
	else
	{
		bt->right = add(bt->right,item);
	}
	return bt;
}
binary_tree* search(binary_tree *bt,int item)
{
	if ((bt == NULL) || (bt->item == item))
	{
		return bt;
	}
    else if(bt->item > item)
    {
    	return search(bt->left,item);
    }
    else
    {
    	return search(bt->right,item);
    }
}

binary_tree *arvore_bi;

binary_tree* char_tree(char arvore[])
{
	if(i == strlen(arvore))
	{
		return NULL;
	}
	
	while((arvore[i] == '(') || (arvore[i] == ' '))
	{
		i++;
	}
	
	if(arvore[i] == ')')
	{
		while(arvore[i] == ')')
		{
			i++;
		}
		return NULL;
	}
	int j,k;
	char n[500];
	for(k=0;k<500;k++)
	{
		n[k] = ' ';
	}
	for(j=0;(arvore[i] > '/') && (arvore[i] < ':');j++)
	{
		n[j] = arvore[i];
		i++;
	}
	int aux = atoi(n);
	strcpy(n,"\0");
	arvore_bi = add(arvore_bi,aux);
	return create_binary_tree(aux, char_tree(arvore),char_tree(arvore));
}

//AVL----------------------------------------------------
int max(int a, int b){
    return (a > b) ? a : b;
}
int height(binary_tree *bt){
    if(bt == NULL){
        return -1;
    }
    else{
        return 1 + max(height(bt->left),height(bt->right));
    }
}

int is_balanced(binary_tree *bt)
{
int bf = h(bt->left) – h(bt->right);
return ((-1 <= bf) && (bf <= 1));
}

int balance_factor(binary_tree *bt)
{
	if (bt == NULL) {
		return 0;
	} 
	else if ((bt->left != NULL) && (bt->right != NULL)) {
		return (bt->left->h - bt->right->h);
	}
	 else if ((bt->left != NULL) && (bt->right == NULL)) {
		return (1 + bt->left->h);
	} 
	else {
		return (-bt->right->h - 1);
	}
}

binary_tree* rotate_left(binary_tree *bt)
{
binary_tree *subtree_root = NULL;
if (bt != NULL && bt->right != NULL) {
subtree_root = bt->right;
bt->right = subtree_root->left;
subtree_root->left = bt;
}
subtree_root->h = h(subtree_root);
bt->h = h(bt);
return subtree_root;
}

binary_tree* rotate_right(binary_tree *bt)
{
binary_tree *subtree_root = NULL;
if (bt != NULL && bt->left != NULL) {
subtree_root = bt->left;
bt->left = subtree_root->right;
subtree_root->right = bt;
}
subtree_root->h = h(subtree_root);
bt->h = h(bt);
return subtree_root;
}

binary_tree* add(binary_tree *bt, int item)
{
if (bt == NULL) {
return create_binary_tree(item, NULL, NULL);
} else if (bt->item > item) {
bt->left = add(bt->left, item);
} else {
bt->right = add(bt->right, item);
}
bt->h = h(bt);
binary_tree *child;
if (balance_factor(bt) == 2 || balance_factor(bt) == -2) {
if (balance_factor(bt) == 2) {
child = bt->left;
if (balance_factor(child) == -1) {
bt->left = rotate_left(child);
}
bt = rotate_right(bt);
} else if (balance_factor(bt) == -2) {
child = bt->right;
if (balance_factor(child) == 1) {
bt->right = rotate_right(child);
}
bt = rotate_left(bt);
}
}
return bt;
}

