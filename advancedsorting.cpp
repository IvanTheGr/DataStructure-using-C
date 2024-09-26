#include<stdio.h>
//quick sort

	void printArr(int arr[], int size){
		for(int i=0;i<size;i++){
			printf("%d ", arr[i]);
		}
		printf("\n");
	}
	
	void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;	
	}	

	int partition(int arr[], int left, int right){
	int pivotValue = arr[right];
	int i = left - 1;
	for(int j=left; j<right; j++){
		if(arr[j] <= pivotValue){
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	i++;
	//arr[right] itu pivotnya
	swap(&arr[right], &arr[i]);
	return i;
}
	void quickSorting(int arr[], int left, int right){
		if(left < right){
			int pivot = partition(arr,left,right);
			//ngebagi array bagian kiri
			quickSorting(arr,left,pivot-1);
			//ngebagi array bagian kanan
			quickSorting(arr,pivot+1,right);
		
	}
}

//mergesort

void merge(int arr[],int left, int mid,int right){
	int leftSize = mid - left + 1;
	int rightSize = right - mid;
	
	int leftArr[leftSize];
	int rightArr[rightSize];
	//i -> array kiri
	//j -> array kanan
	for(int i=0;i<leftSize;i++){
		leftArr[i] = arr[left + i];
		
	}
	for(int j=0;j<rightSize;j++){
		rightArr[j] = arr[mid + j + 1];
		
	}
	int i = 0;
	int j= 0;
	int curr = left;
	
	while(i<leftSize && j<rightSize){
		if(leftArr[i] < rightArr[j]){
			arr[curr] = leftArr[i];
			i++;
			curr++;
		}else{
			arr[curr] = rightArr[j];
			j++;
			curr++;
		}
	}
	//ngecek arr kiri udh masuk  semua atau belum
	while (i < leftSize){
		arr[curr] = leftArr[i];
		i++;
		curr++;
	}
	while(j< rightSize){
		arr[curr] = rightArr[j];
		j++;
		curr++;
	}
}

void mergeSort(int arr[],int left,int right){
	if(left<right){
		int mid = left + (right - left)/2;
		//bagi bagian kiri
		mergeSort(arr,left,mid);
		//bagi bagian kanan
		mergeSort(arr,mid+1,right);
		//gabungin array - arraynya
		merge(arr,left,mid,right);
	}
}


	int main(){
	// size of arr = ngehitung jumlah bit secara keseluruhan arraynya
	//size of arr[0] = ngehitung jumlah bit satu tipe data array
	
	int arr[] = {100,105,80,70,6,140,1,20,3};
	int size = sizeof(arr)/sizeof(arr[0]);	
	printf("%d %d\n",sizeof(arr),sizeof(arr[0]));
	
	puts("Array before sorting");
	printArr(arr,size);
//	quickSorting(arr, 0, size-1);
	mergeSort(arr, 0, size);
	puts("Array After sorting");
	printArr(arr,size);

	return 0;
}
