#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

struct heap{
	int* arr;
	int capacity;
	int curr_size;
	
};

heap* create_heap(int capacity){
	heap* new_heap = (heap*)malloc(sizeof(heap));
	new_heap->capacity = capacity;
	new_heap->curr_size = 0;
	new_heap->arr = (int*)malloc(capacity * sizeof(int));
	
	return new_heap;
}

void swap(int *x, int* y){
	int temp = *x;
	*x = *y;
	*y = temp;
	return;
	
}

void insert_min_heap(heap* min_heap, int value){
	if(min_heap->curr_size >= min_heap->capacity){
		puts("Overflow capacity");
		return;
	}
	
	int index = min_heap->curr_size;
	min_heap->curr_size++;
	min_heap->arr[index] = value;
	
	while(index > 0 && min_heap->arr[index] < min_heap->arr[(index - 1)/2]){
		swap(&min_heap->arr[index], &min_heap->arr[(index - 1)/2]);
		index = (index - 1)/ 2;
		
	}
	return;
}


void min_heapify(heap* heap, int index){
	
	int smallest_index = index;
	int left_child = (2 * index) + 1;
	int right_child = (2 * index) + 2;
	
	if(left_child < heap->curr_size && heap->arr[smallest_index] > heap->arr[left_child]){
		smallest_index = left_child;
	}
	
	if(right_child < heap->curr_size && heap->arr[smallest_index] > heap->arr[right_child]){
		smallest_index = right_child;
	}
	
	if(smallest_index != index){
		swap(&heap->arr[index], &heap->arr[smallest_index]);
		min_heapify(heap, smallest_index);
	}
	
}

void delete_min_heap(heap* min_heap){
	
	if(min_heap->curr_size == 0){
		puts("No data");
		return;
	}
	
	printf("Delete : %d\n", min_heap->arr[0]);
	
	min_heap->arr[0] = min_heap->arr[min_heap->curr_size - 1];
	min_heap->curr_size--;
	min_heapify(min_heap, 0);
	
	return;	
}


void printHeap(heap* Heap){
	for(int i = 0; i < Heap->curr_size ; i++){
		printf("%d ", Heap->arr[i]);
	}
	puts("");
}

int main(){
	
	heap* min_heap = create_heap(20);
	insert_min_heap(min_heap,5);
	insert_min_heap(min_heap,12);
	insert_min_heap(min_heap,25);
	insert_min_heap(min_heap,15);
	insert_min_heap(min_heap,7);
	
	printHeap(min_heap);
	
	delete_min_heap(min_heap);
	printHeap(min_heap);
	
	return 0;
}
