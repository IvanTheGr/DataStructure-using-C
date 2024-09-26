#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ctype.h>

// mendeskripsikan isi-isi node
typedef struct TrieNode {
    struct TrieNode* children[26]; // mempresentasikan setiap kata dari alphabet
    bool isEndOfWord;
    char* description;
} TrieNode;

// function untuk membuat node
TrieNode* createNode() {
    TrieNode* newNode = (TrieNode*)malloc(sizeof(TrieNode));
    newNode->isEndOfWord = false;
    newNode->description = NULL;
    for (int i = 0; i < 26; i++)
        newNode->children[i] = NULL;
    return newNode;
}

// function untuk memasukkan node ke dalam trie
void insertWord(TrieNode* root, char* word, char* description) {
    TrieNode* temp = root;
    for (int i = 0; i < strlen(word); i++) {
        int index;
        if ('a' <= word[i] && word[i] <= 'z') // mengecek untuk ascii dari 97 - 122
            index = word[i] - 'a';
        else if ('A' <= word[i] && word[i] <= 'Z')  //mengecek untuk ascii dari 65 - 90
            index = word[i] - 'A';
        else { // jika lebih dari kedua kondisi tersebut maka set NULL
            return;
        }
        if (!temp->children[index])
            temp->children[index] = createNode();
        temp = temp->children[index];
    }
    if (temp->isEndOfWord && temp->description) {
        free(temp->description); // membuang data sebelumnya
    }
    temp->isEndOfWord = true;
    temp->description = strdup(description);
}

// function untuk mencari slang word yang terdapat didalam trie
char* searchWord(TrieNode* root, char* word) {
    TrieNode* temp = root;
    for (int i = 0; i < strlen(word); i++) {
        int index;
        if ('a' <= word[i] && word[i] <= 'z') // mengecek untuk ascii dari 97 - 122 
            index = word[i] - 'a';
        else if ('A' <= word[i] && word[i] <= 'Z') //mengecek untuk ascii dari 65 - 90
            index = word[i] - 'A';
        else {
            return NULL;  //jika lebih dari dua kondisi, maka set null 
        }
        if (!temp->children[index]) // jika bukan temp menuju children pada index yang diset maka return NULL
            return NULL;
        temp = temp->children[index]; // set temp menjadi temp menuju children
    }
    if (temp && temp->isEndOfWord) // jika temp dan temp menuju isEndOfWord itu ada, maka return temp menuju deskripsi
        return temp->description;
    else // selain itu return NULL
        return NULL;
}

// function untuk memvalidasi slangword apakah kata tersebut kurang dari 2 ataupun spaces
bool validateSlangWord(char* word) {
    int len = strlen(word);
    if (len < 2) // harus lebih dari 1 karakter
        return false;
    for (int i = 0; i < len; i++) {
        if (!((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z') || word[i] == ' ' )) // hanya mengandung abjad jika tidak maka set false
            return false;
    }
    return true; // jika lebih dari 2 maka return true
}

// function untuk memvalidasi deskripsi yang diinput
bool validateDescription(char* description) {
    int len = strlen(description); // panjang string dari deskripsi yang diinput
    if (len < 1) // jika kurang dari 1 kata, set false
        return false;
    int wordCount = 0; 
    bool inWord = false; 
    for (int i = 0; i < len; i++) { //looping untuk mengecek dari 0 sampai dengan panjang string tersebut
        if ((description[i] >= 'a' && description[i] <= 'z') || (description[i] >= 'A' && description[i] <= 'Z')) { // hanya mengandung abjad
            if (!inWord) { //jika bukan inWord maka set inWord menjadi true dan wordCount diincrement
                inWord = true;
                wordCount++;
            }
        } else { // selain itu, inWord diset false
            inWord = false;
        }
    }
    return wordCount > 1;
}

// function untuk print seluruh kata
int printLexicographicalWithIndex(TrieNode* root, char* word, int pos, int index) {
    if (root == NULL) // cek apakah root itu NULL, jika ya return index
        return index;

    if (root->isEndOfWord) { // cek apakah root menuju isEndofWord itu ada, lalu set word pada posisi sekarang adalah NULL
        word[pos] = '\0';
        printf("%d. %s\n", index, word); // maka print index dan kata tersebut lalu index diincrement
        index++;
    }

    for (int i = 0; i < 26; i++) { //looping untuk mengecek satu - satu root menuju children itu tidak sama dengan NULL
        if (root->children[i] != NULL) {
            word[pos] = i + 'a'; // maka kata pada posisi sekarang adalah i + a
            index = printLexicographicalWithIndex(root->children[i], word, pos + 1, index); // set index = function printLexicographicalWithIndex pada root menuju children dari seluruh kata pada abjad, kata, posisi + 1 dan pada index sekarang
        }
    }
    return index; // jika NULL, maka return index
}
//function untuk print kata sesuai dengan prefix yang dicari
void printWordsStartingWithPrefix(TrieNode* root, char* prefix) {
    TrieNode* temp = root;
    // mengarahkan ke node paling terakhir pada prefix
    for (int i = 0; i < strlen(prefix); i++) {  // melakukan looping untuk mengubah uppercase menjadi lowercase dengan kurangkan 97 / a
        int index = tolower(prefix[i]) - 'a'; 
        if (!temp->children[index]) { //untuk mengecek apakah terdapat pada trie tersebut
            printf("There is no prefix \"%s\" in the dictionary.\n", prefix);
            return;
        }
        temp = temp->children[index]; 
    }
    
    // jika node ditemukan dan kata tersebut memang ada
    bool isEmpty = true; //set isEmpty menjadi true
    char word[50];
    strcpy(word, prefix); // untuk copy prefix ke word
    int pos = strlen(prefix); // set posisi menjadi panjang string dari prefix yang disimpan
    int index = 1;
    index = printLexicographicalWithIndex(temp, word, pos, index); // set index untuk menjalankan function yang akan print seluruh prefix yang disimpan dari index 1
    if (index == 1) { // jika index == 1 maka set tidak ada prefix dalam kamus tersebut
        printf("There is no prefix \"%s\" in the dictionary.\n", prefix); 
    }
}



int main() {
    TrieNode* root = createNode(); // membuat node yang menyimpan node yang akan dibentuk
    int action;
    char word[50], description[100];

    do {
        system("cls"); // memindahkan ke terminal baru
		puts("========================");
        puts("	  Boogle	");
        puts("========================\n");

        puts("1. Release a new slang word");
        puts("2. Search a slang word");
        puts("3. View all slang words starting with a certain prefix word");
        puts("4. View all slang words");
        puts("5. Exit");

        printf("\n>> ");
        scanf("%d", &action);
        getchar();

        if (action == 1) {
    system("cls");  // memindahkan ke terminal baru
    bool isNewWord = true;
    
    do { // lakukan function tersebut jika bukan function validateSlangWord ang berisi kata yang dimasukkan 
        printf("Input a new slang word [Must be more than 1 character and contains no space]: "); 
        scanf("%s", word); //mengisi slang word yang akan dicari
        getchar();
        fflush(stdin); //membersihkan tempat data yang dimasukkin pengguna sebelum terbaca oleh program
    } while (!validateSlangWord(word));
    
    char* existingDescription = searchWord(root, word); // menyimpan root dan string yang diterima pada alamat kosong
    if (existingDescription) { // jika terdapat pada function existingDescription, set isNewWord = 0 lalu print string yang terdapat pada existingDescription, dan copy existingDescriptrion tersebut pada description
        isNewWord = false; 
        printf("Input a new slang word description [Must be more than 2 words]: Same meaning as word \"%s\"\n", existingDescription);
        strcpy(description, existingDescription);
    } else {
        do { //lakukan function ini jika bukan function validateDescription yang berisi deskripsi yang kita isi
            printf("Input a new slang word description [Must be more than 2 words]: ");
            scanf("%[^\n]", description);
            getchar();
            fflush(stdin); //membersihkan tempat data yang dimasukkin pengguna sebelum terbaca oleh program
        } while (!validateDescription(description));
    }

    printf("\n");
    if(isNewWord) { // jika kata tersebut baru , maka insert root,word beserta description dan print sudah dimasukkan
        insertWord(root, word, description);
        printf("Successfully released new slang word.\n");
    } else { // selain itu, maka insert root,word beserta description dan print kata sudah diperbarui 
        insertWord(root, word, description);
        printf("Successfully updated a slang word.");
    }
    printf("\nPress enter to continue...");
    getchar();
}


        else if (action == 2) {
            system("cls");
    
            do { // lakukan function tersebut jika bukan function validateSlangWord ang berisi kata yang dimasukkan 
    	    	printf("Input a new slang word [Must be more than 1 characters and contains no space]:  "); 
    	   		scanf("%s", word); //mengisi slang word yang akan dicari
    	    	getchar();
    	    	fflush(stdin); // membersihkan tempat data yang dimasukkin pengguna sebelum terbaca oleh program
    		}while (!validateSlangWord(word));

            char* result = searchWord(root, word); // menyimpan root dan string yang diterima pada alamat kosong
            if (result){  // jika terdapat slang word yang dicari
			
            	printf("\nSlang word  : %s\n", word);
                printf("Description : %s\n\n", result);
            }
            else{
                printf("\nThere is no word \"%s\" in the dictionary.", word); // jika tidak terdapat slang word yang dicari
			}
            printf("\nPress enter to continue...");
            getchar();
        }

       
		else if (action == 3) {
            system("cls"); // memindahkan ke terminal baru
            printf("Input a prefix to be searched: ");
            scanf("%s", word);
            getchar();
            fflush(stdin); //membersihkan tempat data yang dimasukkin pengguna sebelum terbaca oleh program
            printf("Words starts with \"%s\"\n",word); // menampilkan prefix yang dicari
            printWordsStartingWithPrefix(root, word); // menampilkan kata - kata yang berakaitan dengan prefix yang dicari
            printf("\nPress enter to continue...");
            getchar();
        }
        
        else if (action == 4) {
    		system("cls"); // memindahkan ke terminal baru
    		bool isEmpty = true;
    		// dilakukan pengecekan, apakah kosong atau tidak
    		for (int i = 0; i < 26; i++) {
    		    if (root->children[i] != NULL) {
    		        isEmpty = false;
    		        break;
    		    }
    		}
    		
    		// jika kamus tidak kosong, maka ditampilkan kata - kata yang tersimpan
    		if (!isEmpty) {
    		    printf("List of all slang words in the dictionary:\n");
    		    char word[50];
    		    int index = 1;
    		    printLexicographicalWithIndex(root, word, 0, index); // menampilkan seluruh kata dari index 1
    		} 
			else {
    		    printf("There is no slang word yet in the dictionary\n"); // jika kamus benar benar kosong
    		}
    		printf("\nPress enter to continue...");
    		getchar();
	}


        
        else if (action == 5) { 
            break;
        }

    } while (true);

    system("cls"); // memindahkan ke terminal baru
    printf("\"This is the end so... Thank You :) \"\n");

    return 0;
}

