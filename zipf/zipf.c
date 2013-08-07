#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MAX_NO_SONGS 50000

/* STRUCT */
typedef struct s_list {
	int count;
	char name[30];
	int quality;
}songlist;

/* ERROR FUNCTION */
int errout(char * err_msg) {
	printf("%s \n", err_msg);
	exit(1);	
}

/* COMPARISION FN */
int compar_int(const void *a, const void *b)
{
	int *tmpa = &((songlist*)a)->quality;
	int *tmpb = &((songlist*)b)->quality;
	return *tmpb -*tmpa;
}
/* QUICK SORT HELPER FN */
/* QUICK SORT 
void * quick_sort(void *base, size_t nmemb, size_t size,int(*compar)(const void *, const void *)){

	void *less, *greater,*pivot,*concat;
	size_t len;
	int i;

	if (nmemb <=1)
	return base;

	//Malloc pointers
	//base = malloc(size*nmemb);
	less =    malloc(size*((nmemb)/2));
	greater = malloc(size*((nmemb)/2));
	pivot = malloc(size); 

	//Fetch pivot
	int median = (nmemb)/2;
	pivot = base+(size*(median));
	//loop through array
	for(i=0;i<nmemb;i++) {
		if (compar(base+(i*size),pivot) <= 0)
		less=base+(i*size);
		else
		greater=base+(i*size);
	}
	
	//recursive call
	concat = malloc(size*nmemb); 
	quick_sort(less,nmemb/2,size,compar);
	memcpy(concat,less,sizeof(less));
	memcpy(concat+sizeof(less),pivot,sizeof(pivot));
	quick_sort(greater,nmemb/2,size,compar);
	memcpy(concat+sizeof(less)+sizeof(pivot),greater,sizeof(greater));	
	memcpy(base,concat,sizeof(concat));
	//free(less);	
	//free(greater);	
	//free(pivot);	
}*/

/* ZIPF FUNCTION */
void zipf(songlist* song_list,int n) {
	int i=0,base_value=0;
	base_value = song_list[0].count;
	for (i=0;i<n;i++){
		song_list[i].quality = song_list[i].count/(base_value/(i+1));
	}
}

/* MAIN */
int main (int argc, char *argv[]) {

	int n=0, m=0, i=0;
	songlist *song_list;

	if (argc == 3) {
		n = atoi(argv[1]);
		if(n>MAX_NO_SONGS)
		errout("Exceeded Max # of songs in album");

		m = atoi(argv[2]);
		if(m>n)
		errout("Exceeded # of songs in album");

	}else 
	errout("incorrect arguments");

	// Malloc for # of songs
	song_list = (songlist*) malloc(sizeof(songlist)*n);
	


	for(i=0;i<n;i++) {
		fscanf(stdin, "%d %s \n", &song_list[i].count, song_list[i].name);
	}

	zipf(song_list,n);
	qsort(song_list,n,sizeof(songlist),compar_int);

	for(i=0;i<m;i++) {
		printf("name - %s quality %d \n",song_list[i].name,song_list[i].quality);	
	}

	free(song_list);
	return 0;
}
