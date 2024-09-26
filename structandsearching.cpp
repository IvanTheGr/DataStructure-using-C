#include <stdio.h>
#include <string.h>

struct ipkmhs{
	char nim[11];
	char name[30];
	float gpa;
};

void linearSearch(struct ipkmhs  array[], const char key[], int size){
	int x;
	int lintotal = 0;
	
	printf("Linear Search \n");
	for(x = 0; x < size; x++){
		if(strcmp(array[x].nim, key) == 0){
			printf("NIM berada di posisi: %d\n%d Pencarian\n", x+1, lintotal);
			return;
		}
		lintotal++;
	}
	printf("NIM not found\n");
}

void binarySearch(struct ipkmhs arr[], const char k[], int low, int high){
	int middle;
	int bintotal = 0;
	printf("Binary Search\n");
	
	while(low <= high){
		middle = (low + high) / 2;
		if(strcmp(k, arr[middle].nim) == 0){
			printf("NIM berada di posisi: %d\n%d Pencarian\n", middle+1, bintotal);
			return;
		}else if(strcmp(k, arr[middle].nim) < 0){
			high = middle - 1;
		}else if(strcmp(k, arr[middle].nim) > 0){
			low = middle + 1;
		}
		bintotal++;	
	}
	printf("NIM not found\n");
	
}

int main(){
	struct ipkmhs mhs[5];
	
	printf("Jumlah Mahasiswa (5-100): \n");
	
	int jmlh;
	do{
		scanf("%d", &jmlh);
		getchar();
	}while(jmlh < 5 || jmlh > 100);
	
	for(int i = 0; i < jmlh; i++){
		printf("Enter NIM: ");
		scanf("%s", mhs[i].nim);
		getchar();
		printf("Enter name: ");
		scanf("%[^\n]", mhs[i].name);
		getchar();
		printf("Enter GPA: ");
		scanf("%f", &mhs[i].gpa);
		getchar();
		printf("\n");
		
	}
	
	char temp1[11], temp2[30];
	float temp3;
	for(int a = 0; a < jmlh; a++){
		for(int b = 0; b < jmlh - 1 - a; b++){
			if (strcmp(mhs[b].nim, mhs[b + 1].nim) > 0) {
                strcpy(temp1, mhs[b].nim);
                strcpy(mhs[b].nim, mhs[b + 1].nim);
                strcpy(mhs[b + 1].nim, temp1);

                strcpy(temp2, mhs[b].name);
                strcpy(mhs[b].name, mhs[b + 1].name);
                strcpy(mhs[b + 1].name, temp2);

                temp3 = mhs[b].gpa;
                mhs[b].gpa = mhs[b + 1].gpa;
                mhs[b + 1].gpa = temp3;
            }
		}
	}
	
	for(int c = 0; c < jmlh; c++){
		printf("NIM: %s\nNama: %s\nGPA: %.2f\n", mhs[c].nim, mhs[c].name, mhs[c].gpa);
		printf("\n");
	}
	
	printf("Input NIM: \n");
	char n[11];
	scanf("%s", n);
	int s = sizeof(mhs) / sizeof(mhs[0]);
	
	linearSearch(mhs, n, s);
	binarySearch(mhs, n, 0, jmlh-1);
	
	return 0;
}
