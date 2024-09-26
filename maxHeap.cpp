#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

struct heap{
	int* arr;
	int capacity;
	int curr_size;
	
};

void expand_heap(heap* heap, int expandSize){
	
	int newSize = heap->capacity + expandSize;
	int* temp_arr = (int*)realloc(heap->arr, newSize * sizeof(int));
	free(heap->arr);
	heap->arr = temp_arr;
	return;
}

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

void insert_max_heap(heap* max_heap, int value){
	if(max_heap->curr_size >= max_heap->capacity){
		puts("Overflow capacity");
		return;
	}
	
	int index = max_heap->curr_size;
	max_heap->curr_size++;
	max_heap->arr[index] = value;
	
	while(index > 0 && max_heap->arr[index] > max_heap->arr[(index - 1)/2]){
		swap(&max_heap->arr[index], &max_heap->arr[(index - 1)/2]);
		index = (index - 1)/ 2;
		
	}
	return;
}


void max_heapify(heap* heap, int index){
	
	int largest_index = index;
	int left_child = (2 * index) + 1;
	int right_child = (2 * index) + 2;
	
	if(largest_index < heap->curr_size && heap->arr[largest_index] < heap->arr[left_child]){
		largest_index = left_child;
	}
	
	if(largest_index < heap->curr_size && heap->arr[largest_index] < heap->arr[right_child]){
		largest_index = right_child;
	}
	
	if(largest_index != index){
		swap(&heap->arr[index], &heap->arr[largest_index]);
		max_heapify(heap, largest_index);
	}
	
}

void delete_max_heap(heap* max_heap){
	
	if(max_heap->curr_size == 0){
		puts("No data");
		return;
	}
	
	printf("Delete : %d\n", max_heap->arr[0]);
	
	max_heap->arr[0] = max_heap->arr[max_heap->curr_size - 1];
	max_heap->curr_size--;
	max_heapify(max_heap, 0);
	
	return;	
}


void printHeap(heap* Heap){
	for(int i = 0; i < Heap->curr_size ; i++){
		printf("%d ", Heap->arr[i]);
	}
	puts("");
}

int main(){
	
	heap* max_heap = create_heap(20);
	insert_max_heap(max_heap,20);
	insert_max_heap(max_heap,15);
	insert_max_heap(max_heap,9);
	insert_max_heap(max_heap,7);
	insert_max_heap(max_heap,12);
	
	printHeap(max_heap);
	
	delete_max_heap(max_heap);
	printHeap(max_heap);
	
	return 0;
}
