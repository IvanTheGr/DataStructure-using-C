#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct node{
	char nama[105];
	int angka;
	
	node* left;
	node* right;
} *root = NULL ;

struct node* createnode(char nama[], int angka){
	struct node* newnode = (node*)malloc(sizeof(struct node));
	strcpy(newnode->nama,nama);
	newnode->angka = angka;
	
	newnode->left = newnode->right = NULL;
	return newnode;
}

struct node* insertnode(struct node* root, char nama[], int angka){
	if(root == NULL){
		return createnode(nama, angka);
	}
	if(strcmp(root->nama,nama) > 0){
		root->left = insertnode(root->left,nama,angka);
	}else if(strcmp(root->nama,nama) < 0){
		root->right = insertnode(root->right,nama,angka);
	}
	return root;
}

struct node* deletenode(struct node* root, char nama[]){
	if(root == NULL){
		return root;
	}else if(strcmp(root->nama,nama) > 0){
		root->left = deletenode(root->left,nama);
	}else if(strcmp(root->nama,nama) < 0){
		root->right = deletenode(root->right,nama);
	}else if(strcmp(root->nama,nama) == 0){
		if(root->left == NULL && root->right == NULL){
			free(root);
			return NULL;
		}else if(root->left == NULL || root->right == NULL){
			if(root->left == NULL){
				struct node* temp = root->right;
				delete(root);
				return temp;
			}
			if(root->right == NULL){
				struct node* temp = root->left;
				delete(root);
				return temp;
			}
		}
		else if(root->left != NULL && root->right != NULL){
			struct node* predecessor = findpredecessor(root);
			strcpy(root->nama,predecessor->nama);
			root->angka = predecessor->angka;
			root->left = deletenode(root->left,predecessor->nama);
			
			
//			struct node* successor = findsuccessor(root);
//			strcpy(root->nama,successor->nama);
//			root->angka = successor->angka;
//			root->right = deletenode(root->right, successor->nama);
		}
	}
}

void print_inorder(struct node* root){
	if(root != NULL){
		print_inorder(root->left);
		printf("%s %d\n",root->nama, root->angka);
		print_inorder(root->right);
	}
}

void print_preorder(struct node* root){
	if(root != NULL){
		printf("%s %d\n",root->nama, root->angka);
		print_preorder(root->left);
		print_preorder(root->right);
	}
}

void print_postorder(struct node* root){
	if(root != NULL){
		print_postorder(root->left);
		print_postorder(root->right);
		printf("%s %d\n",root->nama, root->angka);
	}
}

int printheight(struct node* root){
	if(root == NULL){
		return -1;
	}
	int left_tree = printheight(root->left);
	int right_tree = printheight(root->right);
	
	return(left_tree > right_tree ? left_tree : right_tree) +  1;	
}

struct node* findMin(struct node* root){
	struct node* curr = root;
	while(root != NULL && root->left != NULL){
		curr = curr->left;
	}
	if(curr == NULL){
		puts("Pohon kosong");
	}
	return curr;
}

struct node* findMax(struct node* root){
	struct node* curr = root;
	while(root != NULL && root->right != NULL){
		curr = curr->right;
	}
	if(curr == NULL){
		puts("Pohon kosong");
	}
	return curr;
}


int main(){
	root = insertnode(root, "Andrew", 18);
	root = insertnode(root, "Beni", 20);
	root = insertnode(root, "Bayu", 19);
	root = insertnode(root, "Cika", 25);
	
//	root = deletenode(root, "Beni");
	printf("Height of the BST : %d\n", printheight(root));
	struct node* min = findMin(root);
	struct node* max = findMax(root);
	
//	printf("%s %d\n",min->nama, min->angka);
//	printf("%s %d\n",max->nama, max->angka);
	
	print_inorder(root);
	return 0;
}

