#include<stdio.h>
#include<string.h>

int main(){
	int arr[5] = {1,2,3,4,5};
	//1 integer = 4 bytes , program kamu dipesenin memori 20 bytes
	//Ciri - ciri Array
	//1. Alokasi Memorinya Statis / hanya bisa dialokasikan saat compile time
	//Memori yang dibutuhkan program dipesan hanya saat compile
	//Kalo program udah jalan, gabisa nambah / alokasi memori lagi
	
	//2. Array bisa diakses secara acak
//	printf("%d", arr[3]);

	//3. Alamat memori dalam array itu berdekatan
//	for(int i = 0 ; i<5 ; i++){
//		printf("%d\n", &arr[i]);
//	}
	
//	char x[10] = "Andrew";
//	for(int i=0;i<strlen(x);i++){
//		printf("%d\n",&x[i]);
//	}
	
	
	return 0;
}
