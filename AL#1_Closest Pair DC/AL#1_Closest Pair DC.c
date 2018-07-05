//20130602 백찬규 
#include<stdio.h>
#include<stdlib.h>
#include<math.h> 
#define	MIN(x,y) ( (x) < (y) ? (x) : (y) )
#define	ABS(x)	( ((x)<0) ? -(x) : (x) )

typedef struct
{
	double x;
	double y;
}coord;

coord CP[2];  //closest Pair 저장배열  
double min_dst = 9999;   // 최단거리 저장변수 

double dst_cal(coord* a,coord* b)
{//거리계산하는 dst_cal
	double dst;
	dst = sqrt( pow( a->x - b->x , 2)+pow( a->y - b->y ,2)  );
	
	return dst;	
}
void Sort_by_X(coord* a, coord* p1, int n){

	void mergeSort(coord* a, int p, int q){
		void merge(coord* a, int p, int middle, int q){
			int i,j,d,t;
			i=p;j=middle+1;d=p;
			while(i<=middle && j<=q){
				if((a+i)->x <= (a+j)->x){
					(p1+d)->x = (a+i)->x;
					(p1+d)->y = (a+i)->y;
					i++;
				}
				else{
					(p1+d)->x = (a+j)->x;
					(p1+d)->y = (a+j)->y;
					j++;
				}
				d++;
			}
			
			if(i>middle){
				for(t=j;t<=q;t++,d++){
					(p1+d)->x = (a+t)->x;
					(p1+d)->y = (a+t)->y;
					
				}
			}
			else{
				for(t=p;t<=middle;t++,d++){
					(p1+d)->x = (a+t)->x;
					(p1+d)->y = (a+t)->y;
				}
			}
			for(t=p;t<=q;t++){
				(a+t)->x = (p1+t)->x;
				(a+t)->y = (p1+t)->y;
			}
		}
		
		int middle;
			if(p<q){
				middle  = (p+q)/2;
				mergeSort(a, p, middle);
				mergeSort(a, middle+1, q);
				merge(a, p, middle, q);
		}
	}	
	
	mergeSort(a, 0, n-1);

}


double Closest_Pair_DC(coord Pairs[], int L, int R, int THR)
{	
	int i,j;
	if (R-L+1<=THR){
		//bruteForcely return
			for(i=L;i<R;i++){
				for(j=i+1;j<=R;j++){
					if(dst_cal(&Pairs[i],&Pairs[j]) <min_dst){
						min_dst = dst_cal(&Pairs[i],&Pairs[j]); //최단거리 업데이트  
						*CP = Pairs[i];    //최단거리점 업데이트  
						*(CP +1) = Pairs[j];
					}
				}
			}
		return min_dst; 
	}
	else{
		int mid = (L+R)/2;
		double dstRange;
		double CPL;
		double CPR;
		
		CPL = Closest_Pair_DC(Pairs,L,mid,THR);
		CPR = Closest_Pair_DC(Pairs,mid+1,R,THR);
		dstRange = MIN(CPL,CPR);
		
		//CPC 계산위한 임시 저장 변수 할당 
		coord* tmpPairs = (coord*)malloc(sizeof(coord)*(R-L+1));
		int cnt = 0;
		double subMin = -1;  //부분 최솟값 
		
		for(i=L;i<=R;i++){
			if( ABS( (Pairs+i)->x - (Pairs+mid)->x ) < dstRange ){
				(tmpPairs+cnt)->x = (Pairs+i)->x;
				(tmpPairs+cnt)->y = (Pairs+i)->y;
				cnt++;
			}
		}
		for(i=0;i<cnt;i++){
			for(j=i+1;j<cnt;j++){
				subMin = MIN(dstRange, dst_cal(tmpPairs+i, tmpPairs+j) );
				
				if(subMin < dstRange){
					dstRange = subMin;
					if(subMin<min_dst){
						*CP = *(tmpPairs+i);
						*(CP+1) = *(tmpPairs + j);  //CP값을 CPC로 갱신 
					}
				}
			}
		}
		free(tmpPairs);
		
		return dstRange;
	} 
	
	
}



int main(){
	int N;
	int THR;
	int i;
	FILE *fp;
	fp = fopen("./A.txt","r");
	fscanf(fp,"%d %d",&N,&THR);

	double X[N];
	double Y[N];
	double cd;
	
	coord* Pairs = (coord*)malloc(sizeof(coord)*N);
	coord* P1 = (coord*)malloc(sizeof(coord)*N); //Pairs를 정렬하는데 사용할 임시배열 
	
	for (i=0;i<N;i++){ // (x,y)입력  
		fscanf(fp,"%lf %lf",&X[i],&Y[i]);
		(Pairs+i)->x = X[i];
		(Pairs+i)->y = Y[i];
		//printf("(X,Y) : %.2lf %.2lf \n", X[i],Y[i]);
		//printf("Pairs : (%.2lf,%.2lf) \n",(Pairs+i)->x,(Pairs+i)->y);
	}
	
	//Sort_by_X(Pairs, P1, N);
		
	cd = Closest_Pair_DC(Pairs, 0, N-1, THR);
	
	printf("%.2lf %.2lf\n",CP->x,CP->y);
	printf("%.2lf %.2lf\n",(CP+1)->x,(CP+1)->y);
	printf("%lf\n",cd);
	
	free(Pairs);
	free(P1);
	
	return 0;
}

	

