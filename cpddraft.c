#include <stdlib.h>
#include <stdio.h>
#include <string.h>



struct rdnode {
	int value;
	int isroot;
	char axis;
	int depth;
	struct rdnode* left;
	struct rdnode* right;
};

int* x;
int* y;
int* z;
int size;

struct rdnode* root;

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

int medianaintervalo(int* x,int begin,int end){
	int half;
	int holddiv;

	if((end)%2==0){
		return x[(end-begin)/2+begin];

	}else{
		holddiv = (x[(end-begin)/2+begin]+x[(end-begin)/2+begin+1])*0.5;
		return holddiv;
	}
	return 0;
}

int indexmediana(int begin,int end){
	int holddiv;

	if((end)%2==0){
		return (end-begin)/2+begin;

	}else{
		holddiv = (end)*0.5;
		return holddiv;
	}

}


char counter(char l){
	switch (l){
		case('x'):{return 'y';};
		case ('y'):{return 'z';};
		case ('z'):{return 'x';};
	}	
	return 'x';
}

struct rdnode*LFN(struct rdnode* node){

	if(node->left==NULL){
		return node;
	}else{
		LFN(node->left);
	}

}

struct rdnode* create(int *vect,char axis,int depth,int begin,int end){
		int odd;
		int newoffset;

		struct rdnode* colisionsolver;
		
		
		//a amostra inicial tem de ter logo um calculozito de par ou impar

		struct rdnode* tmp = (struct rdnode*)malloc(sizeof(struct rdnode));
		
		tmp->depth = depth;
		tmp->value = medianaintervalo(vect,begin,end);
		tmp->axis = axis;
		tmp->left=NULL;
		tmp->right=NULL;

		/*if(end-begin<=1){
			return tmp;
		}*/

		if(depth == 10){
			return tmp;
		}
		//if(offset == 1 || offset == end || (end-offset)<=1 )return tmp;

		char eixo = counter(axis);

		depth++;

		if(eixo == 'x'){
			tmp->left = create(x,eixo,depth,begin,indexmediana(begin,end));
		}else if(eixo == 'y'){
			tmp->left = create(y,eixo,depth,begin,indexmediana(begin,end));
		}else if(eixo == 'z'){
			tmp->left = create(z,eixo,depth,begin,indexmediana(begin,end));
		}
		//odd=0;
		

		
		
		/*offset = offset+(end-offset)/2;
		if(offset%2!=0){
			offset += 1;
			odd=1;
		}*/

		if(eixo=='x'){
			tmp->right = create(x,eixo,depth,indexmediana(begin,end)+1,end);
		}else if(eixo=='y'){
			tmp->right = create(y,eixo,depth,indexmediana(begin,end)+1,end);
		}else if(eixo=='z'){
			tmp->right = create(z,eixo,depth,indexmediana(begin,end)+1,end);
		}


		//tentar resolver os nodos duplicados
		/*if(((tmp->right)->value)==((tmp->left)->value)){
			colisionsolver = LFN(tmp->right);
			colisionsolver->left = tmp->left;
			tmp->left = NULL;
		}*/

		return tmp;
}


int main(int argc,char*argv[]){
	FILE* f;
	int count=0;
	int odd;
	int a,b,c,d,i;
	char buff[10];
	//printf("%s \n",argv[1]);
	f = fopen("s20e400.in","r");
	//f = fopen("sample.txt","r");
		

	

	while(fgets(buff,sizeof(buff),f)!=NULL){		
		count++;		
	}

	memset(buff,'\0',10);

	x = (int *)malloc((count-1)*sizeof(int));
	y = (int *)malloc((count-1)*sizeof(int));
	z = (int *)malloc((count-1)*sizeof(int));
	x[0]=y[0]=z[0]=0;
	rewind(f);
	count = 0;
	while(fgets(buff,10,f)!= NULL){
	
		if(count==0){
			sscanf(buff,"%d",&d);
		}else{
			sscanf(buff,"%d %d %d",&x[count-1],&y[count-1],&z[count-1]);
		}
		
		//printf("%d %d %d\n",x[count],y[count],z[count]);
		count++;
	}

		for(d=0;d<count-1;d++){
			printf("%d %d %d\n",x[d],y[d],z[d]);
		}
		printf("\n");

		MergeSort(x,count-1);
		MergeSort(y,count-1);
		MergeSort(z,count-1);
		for(i=0;i<count-1;i++){
			printf("%d %d %d\n",x[i],y[i],z[i]);
		}

		/*printf("\n mediana de x %d \n",axismediana(x,count));
		printf("\n mediana de y %d \n",axismediana(y,count));
		printf("\n mediana de z %d \n",axismediana(z,count));*/

		if((count-1)%2==0){
			odd=0;
		}else{
			odd=1;
		}
		size = d;
		root = create(x,'x',0,0,count-2);
		fclose(f);

	return 0;
}