#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct manusia{
	char nama[100];
	int age;
	float tinggi;
	
};

struct mahasiswa{
	struct manusia datadiri;
	float ipk;
};

int main(){
	struct manusia Jade;
	strcpy(Jade.nama, "Jade");	
	Jade.age = 18;
	Jade.tinggi = 160.33;
	
	struct mahasiswa Jade2;
	strcpy(Jade2.datadiri.nama, "Jade2");
	Jade2.datadiri.age = 18;
	Jade2.datadiri.tinggi = 160.33;
	Jade2.ipk = 4.00;
	
	
	
	
	return 0;
}
