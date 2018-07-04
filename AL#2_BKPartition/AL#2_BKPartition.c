#include<stdio.h>
#include<stdlib.h>

int current_sum(int* A, int* flag,int n);
void is_partitable(int* A,int n);


int main(){
	int N ,n; //�׽�Ʈ ���̽��� ���� N�� �ش� ���̽��� ���Ұ��� n 
	int i,j;
	FILE *fp;
	int* S;
	
	fp = fopen("input.txt","r");
	
	fscanf(fp, "%d",&N);
	
	for(i=0;i<N;i++){
		fscanf(fp,"%d",&n);
		S = (int*)malloc(sizeof(int)*n); //���̽��� ���Ҹ� �����ϴ� �迭 S�� �����Ҵ� 
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
	int k; //space state tree��  k-th ������ �ǹ� 
	//A�� 0���� n-1����, k�� 0���� n����
	int total = 0; //set ��ü�� �� 
	int* flag = (int*)malloc((n+1)*sizeof(int)); //���� ���� ���� ���� ����
	int found = 0;
		
	void partition_backtrack(int k){
		int i;
		
		if (k>n) return; //�������� �ʴ� space state�� ��� Ž������  
		if (found==1) return; // �̹� Ž����� ���°��  
		
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
		
		else{ //���� ������ state�� ���� 
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
	
	for (k=0;k<n+1;k++)flag[k]=0; //flag �ʱ�ȭ 
	
	for(k=0;k<n;k++){
		total += A[k];
	}
	
	if(total%2!=0){ //set sum�� Ȧ���� ��� partition �Ұ� 
		printf("\nPartition is not possible\n");
		return;
	}
	
	partition_backtrack(0);
	
	//Eventually, we cannot find the solution
	if(found==0)printf("\nPartition is not possible\n");	
	return;
} 
