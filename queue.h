#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

typedef struct {
    int x, y, dist;
} Node;

void init(int *head, int *tail);
void enqueue(Node *q,int *tail, Node element);
Node dequeue(Node *q,int *head);
int empty(int head,int tail);
int full(int tail,const int size);

#endif // QUEUE_H_INCLUDED
