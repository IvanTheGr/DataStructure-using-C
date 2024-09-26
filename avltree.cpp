#include<stdio.h>
#include<malloc.h>

struct Node{
	int value;
	int height;
	Node *left, *right;
};

Node *createNode(int value){
	Node *newNode = (Node*)malloc(sizeof(Node));
	newNode->value = value;
	newNode->height = 1;
	newNode->left = NULL;
	newNode->right = NULL;
	
	return newNode;
}

int max(int a, int b){
	if(a > b){
		return a;
	}
	
	return b;
}

int getHeight(Node *curr){
	if(curr == NULL){
		return 0;
	}
	
	return 1 + max(getHeight(curr->left), getHeight(curr->right));
}

int getBF(Node *curr){
	return getHeight(curr->left) - getHeight(curr->right);
}

Node *rotateLeft(Node *curr){
	Node *pivot = curr->right;
	Node *pivotLeft = pivot->left;
	
	curr->right = pivotLeft;
	pivot->left = curr;

	curr->height = getHeight(curr);
	pivot->height = getHeight(curr);
	
	return pivot;
}


Node *rotateRight(Node *curr){
	Node *pivot = curr->left;
	Node *pivotRight = pivot->right;
	
	curr->left = pivotRight;
	pivot->right = curr;

	curr->height = getHeight(curr);
	pivot->height = getHeight(curr);
	
	return pivot;
}


Node *balance(Node *curr){
	curr->height = getHeight(curr);
	int bf = getBF(curr);
	
	if(bf > 1 && getBF(curr->left) >= 0){
		return rotateRight(curr);
	}else if(bf > 1 && getBF(curr->left) < 0){
		curr->left = rotateLeft(curr->left);
		return rotateRight(curr);
	}else if(bf <-1 && getBF(curr->right) <= 0){
		return rotateLeft(curr);
	}else if(bf < -1 && getBF(curr->right) > 0){
		curr->right = rotateRight(curr->right);
		return rotateLeft(curr);
	}
	
	return curr;
}

Node *insertNode(Node *root, int value){
	if(root == NULL){
		return createNode(value);
	}else if(value < root->value){
		root->left = insertNode(root->left, value);
	}else if(value > root->value){
		root->right = insertNode(root->right, value);
	}else{
		return root;
	}
	
	return balance(root);
}

void preOrder(Node *root){
	if(root == NULL){
		return;
	}
	
	printf("%d\n", root->value);
	preOrder(root->left);
	preOrder(root->right);
}





int main(){
	Node *root = NULL;
	root = insertNode(root, 15);
	root = insertNode(root, 13);
	root = insertNode(root, 10);
	
	preOrder(root);
	return 0;
}
