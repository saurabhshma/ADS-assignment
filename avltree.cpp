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

void heightFixUp(node *temp)
{
	node *tempParent = temp->parent;
	while(tempParent != NULL)
	{
		tempParent->height = temp->height + 1;
		temp = tempParent;
		tempParent = tempParent->parent;
	}
}

int max(int a, int b)
{
	if(a > b)
		return a;
	else
		return b;
}

void setHeight(node *temp)
{
	if(temp->left != NULL && temp->right != NULL)
		temp->height = 1 + max(temp->left->height, temp->right->height);
	else if(temp->left == NULL && temp->right != NULL)
		temp->height = 1 + temp->right->height;
	else if(temp->left != NULL && temp->right == NULL)
		temp->height = 1 + temp->left->height; 
	else if(temp->left == NULL && temp->right == NULL)
		temp->height = 0;

}

void leftRotation(node *temp)
{}

void rightRotation(node *temp)
{
	node *tempParent, *leftChild, *left_rightChild;
	tempParent = temp->parent;
	leftChild = temp->left;
	left_rightChild = temp->left->right;
	if(tempParent == NULL)
	{
		root = leftChild;
		temp->left->parent = temp->parent;
		leftChild->right = temp;
		temp->parent = leftChild;
		temp->left = left_rightChild;
		if(left_rightChild != NULL)
			left_rightChild->parent = temp;	
	}
	else
	{
		temp->left->parent = temp->parent;
		temp->parent->left = leftChild;
		leftChild->right = temp;
		temp->parent = leftChild;
		temp->left = left_rightChild;
		if(left_rightChild != NULL)
			left_rightChild->parent = temp;	
	}
	setHeight(temp);
	setHeight(leftChild);
	heightFixUp(leftChild);	 
}

void insert(int key)
{
	node *temp, *temp1;
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
				temp1 = createNode(key);
				temp->left = temp1;
				temp1->parent = temp;
			}
			else
			{
				temp1 = createNode(key);
				temp->right = temp1;
				temp1->parent = temp;
			}
			heightFixUp(temp1);
			while(temp != NULL)
			{
				if(getBalance(temp) < 2 && getBalance(temp) > -2)
					temp = temp->parent;
				else	
				{	
					if(getBalance(temp) == 2)
					{
						if(key < temp->left->value)
						{	
							rightRotation(temp);
							temp = NULL;
						}
						else
						{
							if(key > temp->left->value)
							{
								leftRotation(temp->left);
								rightRotation(temp);
								temp = NULL;
							}
						}
					}
					else
					{
						if(key > temp->right->value)
							leftRotation(temp);
						else
						{
							if(key < temp->right->value)
							{
								rightRotation(temp->right);
								leftRotation(temp);
							}
						}
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
	display(root);
	cout << "\n";
	insert(1);
	display(root);
	cout << "\n";
	insert(-1);
	display(root);
	cout << "\n";
	insert(-2);
	display(root);
	cout << "\n";
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
	//display(root);
	//cout << "\n";
	return 0;
}