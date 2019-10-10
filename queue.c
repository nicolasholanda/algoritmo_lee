typedef struct {
    int x, y, dist;
} Node;

void init(int *head, int *tail) {
    *head = *tail = 0;
}

void enqueue(Node *q,int *tail, Node element) {
    q[(*tail)++] = element;
}

Node dequeue(Node *q,int *head) {
    return q[(*head)++];
}

int full(int tail,const int size) {
    return tail == size;
}

int empty(int head, int tail) {
    return tail == head;
}
