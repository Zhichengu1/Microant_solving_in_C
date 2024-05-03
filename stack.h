//define memory storing type
typedef struct {
    int front, rear;
}stack;

//methods
stack* create_stack(int size);
void push(int x , int y);
int pop();
int peek();
void clear();
int is_StackFull();
int is_Stackempty();


