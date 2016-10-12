/*Skip List*/
#include <iostream>
#include <climits>
#include <ctime>

using namespace std;

int maxHeight;

typedef struct Node
{
	int value;
	struct Node *top;
	struct Node *down;
	struct Node *left;
	struct Node *right;
}node;

node* skiplist;
int rand_num = time(0);

int getrand()
{
	srand(rand_num);
	rand_num = rand();
	return (rand_num % 2);
}

node* createNew()
{
	node* temp1 = new (node);
	node* temp2 = new (node);
	node* temp3 = new (node);
	node* temp4 = new (node);
	temp1->value = INT_MIN;
	temp1->top = temp3;
	temp1->down = NULL;
	temp1->left = NULL;
	temp2->value = INT_MAX;
	temp2->top = temp4;
	temp2->down = NULL;
	temp2->right = NULL;
	temp2->left = temp1;
	temp1->right = temp2;
	temp3->top = NULL;
	temp3->down = temp1;
	temp3->right = temp4;
	temp3->left = NULL;
	temp3->value = INT_MIN;
	temp4->value = INT_MAX;
	temp4->left = temp3;
	temp4->right = NULL;
	temp4->top = NULL;
	temp4->down = temp2;
	maxHeight = 1;
	skiplist = temp3;
}

void display()
{
	node *temp1, *temp2;
	temp2 = skiplist;
	while(temp2 != NULL)
	{
		temp1 = temp2;
		while(temp1 != NULL)
		{
			cout << temp1->value << "     ";
			temp1 = temp1->right;
		}
		cout << "\n";
		temp2 = temp2->down;
	}
}

node* search(int key)
{
	node *temp = skiplist;
	while(temp->down != NULL)
	{
		temp = temp->down;
		while(((temp->right)->value) <= key)
		{
			temp = temp->right;
		}
	}
	return(temp);
}

node* insert_aux(int key, node **after, node **above)
{
	node *newNode = new node;
	newNode->value = key;
	newNode->right = (*after)->right;
	(*after)->right = newNode;
	if(above == NULL)
		newNode->down = NULL;
	else
	{	
		newNode->down = *above;
		(*above)->top = newNode;
	}
	newNode->top = NULL;
	newNode->left = *after;
	newNode->right->left = newNode;
	return(newNode);
}

void insert(int key)
{
	//srand(rand_num);
	int x = 0;
	node *temp;
	while(getrand() != 0)
		x++;
	cout << x << "\n";;
	if(x > (maxHeight - 1))
	{
		for(int i = 0; i < (x - (maxHeight - 1)); i++)
		{
			temp = skiplist;
			node *temp1 = new node;
			node *temp2 = new node;
			temp1->value = INT_MIN;
			temp1->top = NULL;
			temp1->down	= temp;
			temp1->left = NULL;
			temp2->value = INT_MAX;
			temp2->top = NULL;
			temp2->right = NULL;
			temp1->right = temp2;
			temp2->left = temp1;
			temp->top = temp1;
			temp->right->top = temp2;
			temp2->down = temp->right;
			skiplist = temp1;
		}
		maxHeight = x + 1;
	}
	temp = search(key);
	node *node_aux = insert_aux(key, &temp, NULL);
	node *temp1 = node_aux;
	temp = node_aux;
	
	while(x > 0)
	{
		while(temp->top == NULL)
		{	
			temp = temp->left;
		}
		temp = temp->top;
		temp1 = insert_aux(key, &temp, &temp1);
		temp = temp1;
		x--;
	}
	rand_num = rand();
}

int main()
{
	createNew();
	insert(0);
	insert(1);
	insert(2);
	insert(3);
	insert(4);
	//cout << maxHeight << "\n";
	display();
	return 0;
}