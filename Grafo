#include <stdio.h>
#include <stdlib.h> 
#define MAX_SIZE 50
#define MAX_QUEUE_SIZE 50
typedef struct adj_list{
	int item;
	adj_list *next;
}adj_list;

typedef struct graph{
	adj_list *vertices[MAX_SIZE];
	short visited[MAX_SIZE];
};

adj_list *create_adj_list(int vertex){
	adj_list *list = (adj_list*)malloc(sizeof(adj_list));
	list->item = vertex;
	list->next = NULL;
	return list;
}

typedef struct queue{
	int current_size;
	int head;
	int tail;
	int items[MAX_QUEUE_SIZE];
}queue;

queue* create_queue(){
	queue *new_queue = (queue*)malloc(sizeof(queue));
	new_queue->current_size = 0;
	new_queue->head = 0;
	new_queue->tail = MAX_QUEUE_SIZE - 1;
	return new_queue;
}

void enqueue(queue *queue,int item){
	if (queue->current_size >= MAX_QUEUE_SIZE){
		printf("Queue overflow");
	}
	else{
		queue->tail = (queue->tail + 1) % MAX_QUEUE_SIZE;
		queue->items[queue->tail] = item;
		queue->current_size++;
	}
}

void dequeue(queue *queue){
	if (queue == NULL){
		printf("Queue underflow");
		return -1;
	}
	else{
		int dequeued = queue->items[queue->head];
		queue->head= (queue->head + 1) % MAX_QUEUE_SIZE;
		queue->current_size--;
		return dequeued;
	}
}

graph* create_graph(){
	graph *graph = (graph*)malloc(sizeof(graph));
	int i;
	for (i=1;i <=MAX_SIZE - 1;i++){
		graph->vertices[i] = NULL;
		graph->visited[i] = 0;
	}
	return graph;
} 

void add_edge(graph *graph, int vertex1,int vertex2){
	adj_list *vertex = create_adj_list(vertex2);
	vertex->next = graph->vertices[vertex1];
	graph->vertices[vertex1] = vertex;
	
	//grafo n direcionado
	
	vertex = create_adj_list(vertex1);
	vertex->next = graph->vertices[vertex2];
	graph->vertices[vertex2] = vertex;
}
void dfs (graph *graph, int source){
	graph->visited[source] = 1;
	printf("%d\n",source);
	
	adj_list *adj_list = graph->vertices[source];
	
	while(adj_list != NULL){
		if (!graph->visited[adj_list->item]){
			dfs(graph,adj_list->item);
		}
		adj_list = adj_list->next;
	}
}
void bfs(graph *graph,int source){
	queue *queue = create_queue();
	int dequeued;
	adj_list *adj_list = graph->vertices[source];
	graph->visited[source] = 1;
	enqueue(queue,source);
	
	while(queue != NULL){
		dequeued = dequeue(queue);
		adj_list= graph->vertices[dequeued];
		while (adj_list != NULL){
			if(!graph->visited[adj_list->item]);
			printf("%d\n",adj_list->item);
			graph->visited[adj_list->item] = 1;
			enqueue(queue,adj_list->item);
		}
		adj_list= adj_list->next;
	}
}
