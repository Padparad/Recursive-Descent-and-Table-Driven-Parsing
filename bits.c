#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

int len;
int sta;
int t;
char str[10010];
int sb;
int kkk[10010];
int kkkl;
bool iffinshed;

//ST = K, TT = D, ET = W

void readstr()
{
    memset(str, 0, len);
    len = 0;
    printf("\tEnter an input (\"quit\" to quit): ");
    scanf("%[^\n]",str);
    len = strlen(str);
    fflush(stdin);
}

typedef struct Tree* Tree;

struct Tree{
    char type;
    int childLen;
    Tree child[10010];
};

Tree NodeB();
Tree NodeST();
Tree NodeS();
Tree NodeF();
Tree NodeTT();
Tree NodeT();
Tree NodeET();
Tree NodeE();
void infukk(int);
int outfukk();
void parserRep();
void TableParser();

bool lookahead(char c)
{
    if(c == '0' || c == '1' || c == '(' || c == ')' || c == '~' || c == '&' || c == '|')
    {
        if(str[sta] == c)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool match(char c)
{
    if (lookahead(c))
    {
        sta += 1;
        return true;
    }
    else
    {
        return false;
    }
}

Tree new_Tree()
{
    Tree this = (Tree) malloc(sizeof(struct Tree));
    if (this == NULL) {
        return NULL;        // Out of memory
    }
    this->childLen = 0;
    return this;
}

Tree NodeB()
{
    Tree a = new_Tree();
    a->type = 'B';
    if(sta > len)
    {
        return NULL;
    }
    if((!lookahead('0'))&&(!lookahead('1')))
    {
        return NULL;
    }
    if(match('1'))
    {
        Tree y1 = new_Tree();
        y1->type = '1';
        a->child[0] = y1;
        a->childLen ++;
        return a;
    }
    if(match('0'))
    {
        Tree y2 = new_Tree();
        y2->type = '0';
        a->child[0] = y2;
        a->childLen ++;
        return a;
    }
    return a;
}

Tree NodeST()
{
    Tree a = new_Tree();
    a->type = 'K';
    if((!lookahead('0'))&&(!lookahead('1')))
    {
        Tree y1 = new_Tree();
        y1->type = 'e';
        a->child[0] = y1;
        a->childLen ++;
        return a;
    }
    Tree y1 = new_Tree();
    y1 = NodeS();
    if(y1 == NULL)
    {
        return NULL;
    }
    a->child[0] = y1;
    a->childLen ++;
    return a;
}

Tree NodeS()
{
    Tree a = new_Tree();
    a->type = 'S';
    if((!lookahead('0'))&&(!lookahead('1')))
    {
        return NULL;
    }
    Tree y1 = new_Tree();
    y1 = NodeB();
    if(y1 == NULL)
    {
        return NULL;
    }
    a->child[0] = y1;
    a->childLen ++;

    Tree y2 = new_Tree();
    y2 = NodeST();
    if(y2 == NULL)
    {
        return a;
    }
    a->child[1] = y2;
    a->childLen ++;
    return a;
}

Tree NodeF()
{
    Tree a = new_Tree();
    a->type = 'F';
    if(sta > len)
    {
        return NULL;
    }
    if((!lookahead('0'))&&(!lookahead('1'))&&(!lookahead('('))&&(!lookahead('~')))
    {
        return NULL;
    }
    if(match('~'))
    {
        Tree y1 = new_Tree();
        y1->type = '~';
        a->child[0] = y1;
        a->childLen ++;

        Tree y2 = new_Tree();
        y2 = NodeF();
        if(y2 == NULL)
        {
            return NULL;
        }
        a->child[1] = y2;
        a->childLen ++;
        return a;
    }
    if(match('('))
    {
        Tree y1 = new_Tree();
        y1->type = '(';
        a->child[0] = y1;
        a->childLen ++;

        Tree y2 = new_Tree();
        y2 = NodeE();
        if(y2 == NULL)
        {
            return NULL;
        }
        a->child[1] = y2;
        a->childLen ++;

        if(!match(')'))
        {
            return NULL;
        }

        Tree y3 = new_Tree();
        y3->type = ')';
        a->child[2] = y3;
        a->childLen ++;
        return a;
    }
    Tree y1 = new_Tree();
    y1 = NodeS();
    if(y1 == NULL)
    {
        return NULL;
    }
    a->child[0] = y1;
    a->childLen ++;
    return a;
}

Tree NodeTT()
{
    Tree a = new_Tree();
    a->type = 'D';
    if(sta > len)
    {
        return NULL;
    }
    if(!lookahead('&'))
    {
        Tree y1 = new_Tree();
        y1->type = 'e';
        a->child[0] = y1;
        a->childLen ++;
        return a;
    }
    if(match('&'))
    {
        Tree y1 = new_Tree();
        y1->type = '&';
        a->child[0] = y1;
        a->childLen ++;

        Tree y2 = new_Tree();
        y2 = NodeT();
        if(y2 == NULL)
        {
            return NULL;
        }
        a->child[1] = y2;
        a->childLen ++;
        return a;
    }
    return NULL;
}

Tree NodeT()
{
    Tree a = new_Tree();
    a->type = 'T';
    if((!lookahead('0'))&&(!lookahead('1'))&&(!lookahead('('))&&(!lookahead('~')))
    {
        return NULL;
    }

    Tree y1 = new_Tree();
    y1 = NodeF();
    if(y1 == NULL)
    {
        return NULL;
    }
    a->child[0] = y1;
    a->childLen ++;

    Tree y2 = new_Tree();
    y2 = NodeTT();
    if(y2 == NULL)
    {
        return NULL;
    }
    a->child[1] = y2;
    a->childLen ++;
    return a;
}

Tree NodeET()
{
    Tree a = new_Tree();
    a->type = 'W';
    if(sta > len)
    {
        return NULL;
    }
    if((!lookahead('|')))
    {
        Tree y1 = new_Tree();
        y1->type = 'e';
        a->child[0] = y1;
        a->childLen ++;
        return a;
    }
    if(match('|'))
    {
        Tree y1 = new_Tree();
        y1->type = '|';
        a->child[0] = y1;
        a->childLen ++;

        Tree y2 = new_Tree();
        y2 = NodeE();
        if(y2 == NULL)
        {
            return NULL;
        }
        a->child[1] = y2;
        a->childLen ++;
        return a;
    }
    return NULL;
}

Tree NodeE()
{
    Tree a = new_Tree();
    a->type = 'E';
    Tree y1 = new_Tree();
    y1 = NodeT();
    if(y1 == NULL)
    {
        return NULL;
    }
    a->child[0] = y1;
    a->childLen ++;

    Tree y2 = new_Tree();
    y2 = NodeET();
    if(y2 == NULL)
    {
        return NULL;
    }
    a->child[1] = y2;
    a->childLen ++;

    return a;
}

void pTree(Tree a)
{
    if(a == NULL)
    {
        return;
    }
    if(a->childLen == 0)
    {
        for(int i = 0; i < t; i ++)
        {
            printf("\t");
        }

        printf("%c", a->type);
        return;
    }
    else
    {
        for(int i = 0; i < t; i ++)
        {
            printf("\t");
        }
        printf("%c", a->type);
        for(int i = 0; i < a->childLen; i ++)
        {
            t ++;
            printf("\n");
            pTree(a->child[i]);
            t --;
        }
    }
    return;
}


struct Parser{
    int table[8][7];
};

struct Stack{
    char array[1000];
    int size;
};


void push (struct Stack* sta, char element) {
    sta->array[sta->size] = element;
    sta->size ++;
}

void initialize (struct Stack* sta) {
    for (int i = 0; i < 1000; i++) {
        sta->array[i] = '$';
    }
    sta->size = 0;
    t = 0;
    push(sta, 'E');
    infukk(1);
}

char pop (struct Stack* sta) {
    char x = sta->array[sta->size - 1];
    
    int m = outfukk();


    if(m > kkk[0] && sb < len)
    {
        t = m;
    }

    for(int i = 0; i < m; i ++)
    {
        printf("\t");
    }
    printf("%c\n", x);

    sta->array[sta->size - 1] = '$';
    sta->size --;
    return x;
}

char peek (struct Stack* sta) {
    return sta->array[sta->size - 1];
}

struct Parser* initializeTable(){
    struct Parser* parser  = (struct Parser*) malloc(sizeof(struct Parser));
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 7; j++) {
            parser->table[i][j] = -1;
        }
    }


    parser->table[0][5] = 10;
    parser->table[0][6] = 11;
    parser->table[1][5] = 8;
    parser->table[1][6] = 8;


    parser->table[2][0] = 9;
    parser->table[2][1] = 9;
    parser->table[2][2] = 9;
    parser->table[2][3] = 9;
    parser->table[2][4] = 9;
    parser->table[2][5] = 9;
    parser->table[2][6] = 9;

    parser->table[3][0] = 3;
    parser->table[3][2] = 3;
    parser->table[3][4] = 3;
    parser->table[3][5] = 3;
    parser->table[3][6] = 3;


    parser->table[4][0] = 4;
    parser->table[4][1] = 4;
    parser->table[4][2] = 4;
    parser->table[4][3] = 4;
    parser->table[4][4] = 4;
    parser->table[4][5] = 4;
    parser->table[4][6] = 4;


    parser->table[5][0] = 5;
    parser->table[5][2] = 6;
    parser->table[5][5] = 7;
    parser->table[5][6] = 7;

    parser->table[6][0] = 2;
    parser->table[6][1] = 2;
    parser->table[6][2] = 2;
    parser->table[6][3] = 2;
    parser->table[6][4] = 2;
    parser->table[6][5] = 2;
    parser->table[6][6] = 2;



    parser->table[7][0] = 1;
    parser->table[7][2] = 1;
    parser->table[7][4] = 1;
    parser->table[7][5] = 1;
    parser->table[7][6] = 1;

    return parser;
}

//if this fuction return 8, then the input is invalid
int getY (char input) {
    switch(input) {
        case '~':
            return 0;
            break;
        case '|':
            return 1;
            break;
        case '(':
            return 2;
            break;
        case ')':
            return 3;
            break;
        case '&':
            return 4;
            break;
        case '0':
            return 5;
            break;
        case '1':
            return 6;
            break;
        default:
            return 8;
    }
}

int getX (char expression) {
    switch(expression) {
        case 'B':
            return 0;
            break;
        case 'S':
            return 1;
            break;
        case 'K':
            return 2;
            break;
        case 'T':
            return 3;
            break;
        case 'D':
            return 4;
            break;
        case 'F':
            return 5;
            break;
        case 'W':
            return 6;
            break;
        case 'E':
            return 7;
            //case 'e': epsilon
        default:
            return 8;
    }

}


void fun(struct Stack* sta, int c, char input){
    if(c == 1) {
        t++;
        push(sta,'W');
        push(sta,'T');
        infukk(2);
    } else if (c == 2) {
        if(input == '|') {
            t++;
            push(sta,'E');
            push(sta,'|');
            infukk(2);
        } else {
            t++;
            push(sta,'e');
            infukk(1);
        }
    } else if (c == 3) {
        t++;
        push(sta,'D');
        push(sta,'F');
        infukk(2);
    } else if (c == 4) {
        if(input == '&') {
            t++;
            push(sta,'T');
            push(sta,'&');
            infukk(2);
        } else {
            t++;
            push(sta,'e');
            infukk(1);
        }
    } else if (c == 5) {
        t++;
        push(sta,'F');
        push(sta,'~');
        infukk(2);
    } else if (c == 6) {
        t++;
        push(sta,')');
        push(sta,'E');
        push(sta,'(');
        infukk(3);
    } else if (c == 7) {
        t++;
        push(sta,'S');
        infukk(1);
    } else if (c == 8) {
        t++;
        push(sta,'K');
        push(sta,'B');
        infukk(2);
    } else if (c == 9) {
        if(input == '0') {
            t++;
            push(sta,'S');
            infukk(1);
        } else if (input == '1') {
            t++;
            push(sta,'S');
            infukk(1);
        } else {
            t++;
            push(sta,'e');
            infukk(1);
        }
    } else if (c == 10) {
        t++;
        push(sta,'0');
        infukk(1);
    } else if (c == 11){
        t++;
        push(sta,'1');
        infukk(1);
    } else {
        return;
    }

}


bool isTerminal (char input) {
    switch(input) {
        case  '~':
            return true;
        case  '|':
            return true;
        case  '(':
            return true;
        case  ')':
            return true;
        case  '&':
            return true;
        case  '0':
            return true;
        case  '1':
            return true;
        case  'e':
            return true;
        case  '$':
            return true;
        default:
            return false;
    }
}

char search (struct Stack* stack, struct Parser* table, char input) {



    if(isTerminal(peek(stack))) {
        return pop(stack);
    }
    int x = getX(pop(stack));
    int y = getY(input);
    if (table->table[x][y] != -1) {
        fun(stack,table->table[x][y],input);
    } else {
        return '$';
    }

    char element = peek(stack);
    if(!isTerminal(element)) {
        element = search(stack, table, input);
    }
    else
    {
        element = pop(stack);
    }

    return element;
}

void eSearch (struct Stack* stack, char input) {
    int lpl = kkk[0];
    char c = pop(stack);

    if (c == 'W' || c == 'D' || c == 'K') {
        for(int i = 0; i < lpl + 1; i ++)
        {
            printf("\t");
        }
        printf("e\n");
    }
    iffinshed = false;
}

bool run (struct Stack* stack, struct Parser* table, char* input) {
    char current;
    char element;
    while(true){
        current = input[sb];
        element = search(stack, table, current);

        if (element == 'e') {
            continue;
        } else if (element == '$') {
            return false;
        } else if (current != element) {

            return false;
        }  else{
            sb ++;
        }

        if(sb == strlen(input)) {
            iffinshed = true;
            while(stack->size != 0) {
                eSearch(stack, peek(stack));
            }
            break;
        }


    }
    return true;
}


void parserRep(){
    t = 0;
    sta = 0;
    readstr();

    while(strcmp(str,"quit") != 0){
        Tree root = new_Tree();
        root = NodeE();
        if(root == NULL)
        {
            printf("The string is not accepted\n");
            TableParser();
        }
        else if(sta != len)
        {
            printf("The string is not accepted\n");
            TableParser();
        }
        else
        {
            pTree(root);
            printf("\n\nThe table parser: \n\n");
            TableParser();
        }


    }

}

void TableParser(){
    t = 0;
    struct Parser* parser = initializeTable();
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
    initialize(stack);
    sb = 0;
    bool result = run(stack, parser, str);
    if (result) {
        printf("\nThe string is accepted\n");
        parserRep();
    } else {
        printf("\nThe string is not accepted\n");
        parserRep();
    }
}

void infukk(int a)
{
    kkkl+=a;
    for(int i = kkkl-1; i >= a; i --)
    {
        kkk[i] = kkk[i-a];
    }
    for(int i = 0; i < a; i ++)
    {
        kkk[i] = t;
    }
}

int outfukk()
{
    int kkkk = kkk[0];
    for(int i = 0; i < kkkl-1; i ++)
    {
        kkk[i] = kkk[i+1];
    }
    kkkl--;
    return kkkk;
}
int main(int argc, char* argv[])
{

    kkkl = 0;
    parserRep();


    return 0;
}
