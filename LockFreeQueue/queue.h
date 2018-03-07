typedef struct node_t Node;
typedef struct pointer_t Pointer;
typedef struct queue_t Queue;
typedef struct value_t Value;

struct value_t{
   	unsigned int type;
   	void *data;
};

Queue *
q_initialize(void);

void
qpush(Queue *, void *);

Value *
qpop(Queue *,int);

void
queue_free(Queue *);
