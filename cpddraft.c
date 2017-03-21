#include <stdlib.h>
#include <stdio.h>
#include <string.h>



struct rdnode {
	int value;
	int isroot;
	int axis;
	int depth;
	struct rdnode* left;
	struct rdnode* right;
};

int* x;
int* y;
int* z;


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


int axismediana(int* x,int size,int oddoreven){
	int half;
	int holddiv;
	

	if(oddoreven==0){
		return x[size];

	}else{

		holddiv = (x[size]+x[size+1])*0.5;
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

struct rdnode* create(int *vect,int offset,char axis,int depth,int oddoreven,int end){
		int odd;
		char eixo = counter(axis);

		//a amostra inicial tem de ter logo um calculozito de par ou impar

		if(offset == 1 || offset == end)return NULL;

		struct rdnode* tmp = (struct rdnode*)malloc(sizeof(struct rdnode));
		if(depth==0){
			offset=end/2;
		}


		tmp->depth = depth;
		tmp->value = axismediana(vect,offset,oddoreven);

		depth++;

		if(offset%2!=0)odd=1;

		if(eixo == 'x'){
			tmp->left = create(x,offset/2,eixo,depth,odd,offset);
		}else if(eixo == 'y'){
			tmp->left = create(y,offset/2,eixo,depth,odd,offset);
		}else if(eixo == 'z'){
			tmp->left = create(z,offset/2,eixo,depth,odd,offset);
		}
		odd=0;
		

		if(offset%2!=0)odd=1;
		if(depth==0){
			offset = offset+(end-offset)/2;
		}
		tmp->right = create(y,offset,eixo,depth,odd,end);




		return tmp;
}


int main(int argc,char*argv[]){
	FILE* f;
	int count=0;
	
	int a,b,c,d;
	char buff[10];
	printf("%s \n",argv[1]);
	f = fopen(argv[1],"r");
	struct rdnode* root;

	{
		
	};

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
		/*printf("\n mediana de x %d \n",axismediana(x,count));
		printf("\n mediana de y %d \n",axismediana(y,count));
		printf("\n mediana de z %d \n",axismediana(z,count));*/
		//root = create(x,d,d,'x',0);

		fclose(f);

	return 0;
}