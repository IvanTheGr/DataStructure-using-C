#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Pertanyaan 1 -> Dengan apa kita bisa melakukan alokasi memori dinamis? Dengan menggunakan pointer
struct node{
	char name[100];
	int age;
	float gpa;
	
	node* next; //Nunjuk alamat setelahnya
	node* prev; //Nunjuk alamat sebelumnya
}*head = NULL, *tail = NULL;

//Custom Constructor -> Gunanya adalah untuk membentuk sebuah node baru
struct node* createnode(char name[], int age, float gpa){
	struct node* newnode = (node*) malloc(sizeof(struct node));
	strcpy(newnode->name,name);
	newnode->age = age;
	newnode->gpa = gpa;
	
	newnode->next = newnode->prev = NULL;
	
	return newnode;
}

//Push -> Memasukkan data
//1. PushHead => masukkin data ke paling depan
void pushHead(struct node* toPush){
	if(head==NULL){
		head = tail = toPush;
	}else{
		toPush->next = head;
		head->prev = toPush;
		head = toPush;
	}
}

//2. PushTail => masukkin data ke paling belakang
void pushTail(struct node* toPush){
	if(head==NULL){
		head = tail = toPush;
	}else{
		tail->next = toPush;
		toPush->prev = tail;
		tail = toPush;
	}
}

//3. PushMid => dasar dari priority queue, dia bisa memasukkan data berdasarkan urutan tertentu
void pushMid(struct node* toPush){
	if(head==NULL){
		head = tail = toPush;
	}else{
		if(strcmp(head->name,toPush->name) > 0){
			pushHead(toPush);
		}else if(strcmp(tail->name,toPush->name) < 0){
			pushTail(toPush);
		}else{
			node* current = head;
			while(strcmp(current->name, toPush->name) < 0){
				current = current->next;
			}
			
			toPush->next = current;
			toPush->prev = current->prev;
			
			current->prev->next = toPush;
			current->prev = toPush;
		}
	}
}

//Pop -> Membuang Data
void popHead(){
	if(head==NULL){
		printf("Tidak ada Data yang bisa dibuang");
		return;
	}else if(head == tail){
		//dealokasi memori
		free(head);
		head = tail = NULL; //Untuk mencegah Dangling Pointer
	}else{
		head = head->next;
		free(head->prev);
		head->prev = NULL; //mencegah Dangling Pointer
	}
}

void popTail(){
	if(head==NULL){
		printf("Tidak ada Data yang bisa dibuang");
		return;
	}else if(head == tail){
		//dealokasi memori
		free(head);
		head = tail = NULL; //Untuk mencegah Dangling Pointer
	}else{
		tail = tail->prev;
		free(tail->next);
		tail->next = NULL; //mencegah Dangling Pointer
	}	
}

void popMid(char name[]){
	if(head==NULL){
		printf("Tidak ada Data yang bisa dibuang");
		return;
	}else if(head == tail){
		//dealokasi memori
		free(head);
		head = tail = NULL; //Untuk mencegah Dangling Pointer
	}else{
		if(strcmp(head->name,name) == 0){
			popHead();
		}else if(strcmp(tail->name,name) == 0){
			popTail();
		}else{
			node* current = head;
			while(current!=NULL && strcmp(current->name,name) != 0){
				current = current->next;
			}
			
			if(current == NULL){
				printf("The Name that you want to Pop not in the Linked List\n");
				return;
			}else{
				current->prev->next = current->next;
				current->next->prev = current->prev;
				
				free(current);
				current = NULL;
			}
		}
	}	
}


void print(){
	node* curr = head;
	while(curr!=NULL){
		printf("%s %d %.2f\n",curr->name, curr->age, curr->gpa);
		curr = curr->next;
	}
}

//Search -> Mencari Data
struct node* search(char name[]){
	node* curr = head;
	
	while(curr != NULL && strcmp(curr->name, name) != 0){
		curr = curr->next;
	}
	
	if(curr == NULL){
		return NULL;
	}else{
		return curr;
	}
}

void removeallbyname(char name[]){
	while(search(name) != NULL){
		popMid(name);
	}
}

int main(){
	pushMid(createnode("Naufal", 25, 3.99));
	pushMid(createnode("Andrew",20,3.5));
	pushMid(createnode("Cika",15,3));
	pushMid(createnode("Cika",15,3));
	pushMid(createnode("Beni",20,3.1));
	
	char toremove[100];
	printf("Input name to Remove : ");
	scanf("%[^\n]",toremove);getchar();
	
	removeallbyname(toremove);
	print();
	return 0;
}
