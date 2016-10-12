#include <iostream>

using namespace std;

typedef struct avlNode
{
	int value, height;
	struct avlNode *left, *right, *parent;
}node;

node *root = NULL;

node* createNode(int key)
{
	node *temp = new (node);
	temp->parent = NULL;
	temp->left = NULL;
	temp->right = NULL;
	temp->value = key;
	temp->height = 0;	
}

node* search_aux(int key)
{
	node *temp = root;
	while(1)
	{
		if(key == temp->value)
			break;
		else if(key < temp->value)
		{	
			if(temp->left == NULL)
				break;
			else
				temp = temp->left;
		}
		else
		{
			if(temp->right == NULL)
				break;
			else
				temp = temp->right;
		}
	}
	return temp;
}

void search(int key)
{
	node *temp = search_aux(key);
	if(temp->value == key)
		cout << "found\n";
	else
		cout << "nf\n";
}

int getBalance(node* temp)
{
	if(temp->left == NULL && temp->right == NULL)
		return 0;
	else if(temp->left == NULL && temp->right != NULL)
		return (-(temp->height));
	else if(temp->left != NULL && temp->right == NULL)
		return (temp->height);
	else
		return(temp->left->height - temp->right->height);
}	

void insert(int key)
{
	node *temp;
	if(root == NULL)
		root = createNode(key);
	else
	{
		temp = search_aux(key);
		if(temp->value == key)
			cout << "fa\n";
		else
		{
			if(key < temp->value)
			{
				node *temp1 = createNode(key);
				temp->left = temp1;
				temp1->parent = temp;
				while(temp != NULL)
				{
					if(temp1->height + 1 == temp->height)
						break;
					else	
					{	
						(temp->height)++;
						temp1 = temp;
						temp = temp->parent;
					}
				}
			}
			else
			{
				node *temp1 = createNode(key);
				temp->right = temp1;
				temp1->parent = temp;
				while(temp != NULL)
				{
					if(temp1->height + 1 == temp->height)
						break;
					else	
					{	
						(temp->height)++;
						temp1 = temp;
						temp = temp->parent;
					}
				}
			}
		}
	}

}

void display(node *temp)
{
	cout << temp->value << " (" << temp->height << ")(" << getBalance(temp) << ")    " ;
	if(temp->left != NULL)
		display(temp->left);
	if(temp->right != NULL)
		display(temp->right);
}

int main()
{
	insert(5);
	insert(3);
	insert(6);
	insert(1);
	insert(4);
	insert(7);
	insert(2);
	insert(9);
	/*insert(5);
	node *temp1 = new node;
	node *temp2 = new node;
	node *temp3 = new node;
	node *temp4 = new node;
	root->left = temp1;
	root->right = temp2;
	root->left->left = temp3;
	root->left->right = temp4;
	temp1->value = 3;
	temp2->value = 6;
	temp3->value = 2;
	temp4->value = 4;
	display(root);
	cout << "\n";
	search(0);
	search(4);*/
	display(root);
	cout << "\n";
	return 0;
}