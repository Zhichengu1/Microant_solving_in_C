//define memory storing type
typedef struct {
    int front, rear;
    int x, y;
}stack;
//methods
stack* create_stack(int size, int max_r, int max_c);
void push(int x , int y);
stack* pop();
stack* peek();
void clear();
int is_StackFull();
int is_StackEmpty();


