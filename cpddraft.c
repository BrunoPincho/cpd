#include <stdlib.h>
#include <stdio.h>
#include <string.h>



struct rdnode{
	int value;
	int isroot;
	int axis;
	struct rfnode* left;
	struct rfnode* right;
};


void Merge(int *A,int *L,int leftCount,int *R,int rightCount) {
	int i,j,k;

	// i - to mark the index of left aubarray (L)
	// j - to mark the index of right sub-raay (R)
	// k - to mark the index of merged subarray (A)
	i = 0; j = 0; k =0;

	while(i<leftCount && j< rightCount) {
		if(L[i]  < R[j]) A[k++] = L[i++];
		else A[k++] = R[j++];
	}
	while(i < leftCount) A[k++] = L[i++];
	while(j < rightCount) A[k++] = R[j++];
}

void MergeSort(int *A,int n) {
	int mid,i, *L, *R;
	if(n < 2) return; // base condition. If the array has less than two element, do nothing. 

	mid = n/2;  // find the mid index. 

	// create left and right subarrays
	// mid elements (from index 0 till mid-1) should be part of left sub-array 
	// and (n-mid) elements (from mid to n-1) will be part of right sub-array
	L = (int*)malloc(mid*sizeof(int)); 
	R = (int*)malloc((n- mid)*sizeof(int)); 
	
	for(i = 0;i<mid;i++) L[i] = A[i]; // creating left subarray
	for(i = mid;i<n;i++) R[i-mid] = A[i]; // creating right subarray

	MergeSort(L,mid);  // sorting the left subarray
	MergeSort(R,n-mid);  // sorting the right subarray
	Merge(A,L,mid,R,n-mid);  // Merging L and R into A as sorted list.
        free(L);
        free(R);
}


int axismediana(int* x,int size){
	int half;
	int holddiv;

	if(size%2==0){
		return x[size/2];

	}else{

		holddiv = (x[size/2]+x[size/2+1])*0.5;
		return holddiv;
	}
	return 0;
}

char counter(char l){

	switch (l){
		case('x'):{return 'y';};
		case ('y'):{return 'z';};
		case ('z'):{return 'x';};
	}	
	return 'x';
}

void rdtree(int* x,int*y,int*z,int dimension){
int rounds = 3;
char axis='x';
int i=0;
struct rdnode* tmp;
struct rdnode* central;

while(i<rounds){
	
		tmp = (struct rdnode*)malloc(sizeof(struct rdnode));
		tmp->value = axismediana(x,dimension);
		tmp->axis = axis;
		tmp->left=NULL;
		tmp->right=NULL;
		printf("%d\n",tmp->value );
		if(i==0){
			tmp->isroot=1;
		}

		//circular até ter o nivel necessário consoante o eixo, acrescentar o valor da mediana
	

	i++;
}








}


int main(int argc,char*argv[]){
	FILE* f;
	int count=0;
	int* x;
	int* y;
	int* z;
	int a,b,c,d;
	char buff[10];
	printf("%s \n",argv[1]);
	f = fopen(argv[1],"r");

	while(fgets(buff,sizeof(buff),f)!=NULL){
		//fgets(buff,10,f);
	/*	if(count==0){
			fscanf(f,"%d",&d);
		}else{
			fscanf(f,"%d %d %d",&a,&b,&c);
		}*/
		count++;
		//printf("%d %d %d\n",a,b,c);
		

	}

	x = (int *)malloc(count*sizeof(int));
	y = (int *)malloc(count*sizeof(int));
	z = (int *)malloc(count*sizeof(int));
	
	rewind(f);
	count = 0;
	while(fgets(buff,10,f)!=NULL){
	
		if(count==0){
			fscanf(f,"%d",&d);
		}else{
			fscanf(f,"%d %d %d",&x[count],&y[count],&z[count]);
		}
		
		

		//printf("%d %d %d\n",x[count],y[count],z[count]);
		count++;
	}

		MergeSort(x,count);
		MergeSort(y,count);
		MergeSort(z,count);
		for(d=0;d<=count-1;d++){
			printf("%d %d %d\n",x[d],y[d],z[d]);
		}
		printf("\n mediana de x %d \n",axismediana(x,count));
		printf("\n mediana de y %d \n",axismediana(y,count));
		printf("\n mediana de z %d \n",axismediana(z,count));
		rdtree(x,y,z,d);

		fclose(f);

	return 0;
}