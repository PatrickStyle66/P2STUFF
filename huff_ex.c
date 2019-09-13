#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 256

typedef struct node
{
	unsigned char value;
	unsigned priority;
	struct node *next;
	struct node *left;
	struct node *right;
} Node;

typedef struct priority_queue
{
	Node *head;
} Queue;

typedef struct element
{
	unsigned key;
	unsigned char byte[8];
	unsigned size;
} Element;

typedef struct hash_table
{
	unsigned size;
	Element *table[MAX];
} Hash_table;

Node* create_node(unsigned char value, unsigned p, Node *next, Node *left, Node* right)
{
	Node *new = malloc(sizeof(Node));
	new->value = value;
	new->priority = p;

	new->next = next;
	new->left = left;
	new->right = right;
	
	return new;
}

Queue* create_priority_queue()
{
	Queue *new = malloc(sizeof(Queue));
	new->head = NULL;

	return new;
}

void enqueue(Queue *pq, Node *node)
{
	if(!pq->head || pq->head->priority > node->priority)
	{
		node->next = pq->head;
		pq->head = node;
	}
	else
	{
		Node *n = pq->head;
		while(n->next && n->next->priority < node->priority) n = n->next;

		node->next = n->next;
		n->next = node;
	}
}

Node* dequeue(Queue *pq)
{
	if(!pq->head) return NULL;
	else
	{
		Node *removed = pq->head;
		pq->head = pq->head->next;

		return removed;
	}
}

Node* create_tree(Node *left, Node *right)
{
	Node *new = malloc(sizeof(Node));
	new->value = '*';
	new->priority = left->priority + right->priority;

	new->left = left;
	new->right = right;

	return new;
}

void print_tree(Node *tree)
{
	if(tree)
	{
		print_tree(tree->left);
		printf("%c", tree->value);
		print_tree(tree->right);
	}
}

void put(Hash_table *ht, unsigned char key, unsigned char *byte, unsigned size)
{
	unsigned index = key;

	//printf("%c\t-\t%s\n", key, byte);

	Element *new = malloc(sizeof(Element));
	ht->table[index] = new;

	new->key = key;
	strcpy(ht->table[index]->byte, byte);
	new->size = size;
}

void search(Hash_table *ht, Node *tree, unsigned char *byte, unsigned size)
{
	if(!tree) return;

	if(!tree->left && !tree->right)
	{
		byte[size] = '\0';
		put(ht, tree->value, byte, size);
	}
	else
	{
		byte[size] = '0';
		search(ht, tree->left, byte, size + 1);

		byte[size] = '1';
		search(ht, tree->right, byte, size + 1);
	}
}

Hash_table* create_hash_table(Node *tree)
{
	Hash_table *ht = malloc(sizeof(Hash_table));

	unsigned i;
	for(i=0; i<MAX; i++) ht->table[i] = NULL;

	unsigned char byte[8];
	search(ht, tree, byte, 0);
	return ht;
}

void print_hash(Hash_table *ht)
{
	unsigned i;
	for(i = 0; i < 256; i++)
	{
		if(ht->table[i]) printf("%c\t-\t%s\n", ht->table[i]->key, ht->table[i]->byte);
	}
}

int main()
{
	unsigned char array[256];

	scanf("%[^\n]s", array);
	//fgets(array, 256, stdin);

	unsigned i;
	unsigned char freq[256], ch;
	memset(freq, 0, 256);

	for(i = 0; i < strlen(array); i++) freq[array[i]]++;

	Queue *pq = create_priority_queue();
	for(i = 0; i < 255; i++)
    {
        if(freq[i]) enqueue(pq, create_node(i, freq[i], NULL, NULL, NULL));
    }
 
	while(pq->head->next)
	{
		Node *n1 = dequeue(pq);
		Node *n2 = dequeue(pq);
		Node *aux;

		if(n1->priority == n2->priority)
		{
			if(n1->value > n2->value)
			{
				aux = n1;
				n1 = n2;
				n2 = aux;
			}
		}

		enqueue(pq, create_node('*', n1->priority + n2->priority, NULL, n1, n2));
	}

	printf("Tree\t-\t");
	print_tree(pq->head);
	printf("\n");

	Hash_table *ht = create_hash_table(pq->head);

	print_hash(ht);
	
	return 0;
}