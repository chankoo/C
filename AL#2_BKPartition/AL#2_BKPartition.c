#include<stdio.h>
#include<stdlib.h>

int current_sum(int* A, int* flag,int n);
void is_partitable(int* A,int n);


int main(){
	int N ,n; //테스트 케이스의 개수 N과 해당 케이스의 원소개수 n 
	int i,j;
	FILE *fp;
	int* S;
	
	fp = fopen("input.txt","r");
	
	fscanf(fp, "%d",&N);
	
	for(i=0;i<N;i++){
		fscanf(fp,"%d",&n);
		S = (int*)malloc(sizeof(int)*n); //케이스의 원소를 저장하는 배열 S를 동적할당 
		for(j=0;j<n;j++){
			fscanf(fp,"%d",&S[j]);
		}
		printf("\n");
		//printf("This is %dth case\n",i+1);
		is_partitable(S,n);
		
		
		free(S);
	}
	
	
	fclose(fp);
	
	return 0;
}

int current_sum(int* A, int* flag,int n){
	int i,sum=0;
	for(i=0;i<n;i++){
		sum += A[i]*flag[i+1];
	}
	return sum;
}

void is_partitable(int* A,int n){ 
	int k; //space state tree의  k-th 레벨을 의미 
	//A는 0부터 n-1까지, k는 0부터 n까지
	int total = 0; //set 전체의 합 
	int* flag = (int*)malloc((n+1)*sizeof(int)); //현재 레벨 원소 포함 여부
	int found = 0;
		
	void partition_backtrack(int k){
		int i;
		
		if (k>n) return; //존재하지 않는 space state인 경우 탐색안함  
		if (found==1) return; // 이미 탐색결과 나온경우  
		
		//if kth state is solution
		if(current_sum(A,flag,n)==total/2){
			printf("\nPartition is possible\n");
			found = 1;
			
			for(i=0;i<n;i++){
				if(flag[i+1]==1) printf("%2d ",A[i]);
			}
			printf("/ ");
			for(i=0;i<n;i++){
				if(flag[i+1]==0) printf("%2d ",A[i]);
			}
			printf("\n");
			return;
		}
		
		else{ //다음 레벨의 state를 보자 
			//printf("Let's see next level!!\n");
			//visit LC
			if(k<n){ 
				flag[k+1] = 1;
				if ( current_sum(A,flag,n) <= total/2)//LC is promising
				{
					partition_backtrack(k+1);
				}
			}
			
		 	//visit RC
		 	if(k<n){
		 		flag[k+1] = 0;
		 		if ( current_sum(A,flag,n) <= total/2)//RC is promising
				{
					partition_backtrack(k+1);
				}
			}
			
		} 
			
	}
	
	for (k=0;k<n+1;k++)flag[k]=0; //flag 초기화 
	
	for(k=0;k<n;k++){
		total += A[k];
	}
	
	if(total%2!=0){ //set sum이 홀수인 경우 partition 불가 
		printf("\nPartition is not possible\n");
		return;
	}
	
	partition_backtrack(0);
	
	//Eventually, we cannot find the solution
	if(found==0)printf("\nPartition is not possible\n");	
	return;
} 
