#include<cmath>
#include<cstdio>
#include<cstring>

using namespace std;

bool isPrime(const int& p){

        if(p<1)
                return false;

        if(p==1 || p==2)
                return true;

        for(int i=2;i<=ceil(sqrt(static_cast<float>(p)));i++)
                if((p%i)==0)
                        return false;

        return true;

}


void printCase(const int& n, const int* rings){


	for(int i=0;i<n;i++)
		printf("%d ",rings[i]);
	printf("\n");

}

bool place(const int& i, const int& pos, const int* rings, const int& n){

	for(int p=0;p<=(pos-1);p++)
		if(rings[p]==i)
			return false;

	return true;

}

void backTrack(int nextElem, int* rings,const int& n){

	if(nextElem==n){
		printCase(n,rings);
		return;
	}

	else if(nextElem<(n-1)){
	
		for(int i=1;i<=n;i++)
			if(place(i,nextElem,rings,n) && isPrime(rings[nextElem-1]+i)){
				rings[nextElem]=i;
				backTrack(nextElem+1,rings,n);
			}
		
	}

	else{
	
		for(int i=1;i<=n;i++)	
			if(place(i,nextElem,rings,n) && isPrime(rings[nextElem-1]+i) && isPrime(rings[0]+i)){
	
				rings[nextElem]=i;
				backTrack(nextElem+1,rings,n);		
			}
				

	}
	
}

void processCase(const int& n,const int& cN){

	int* rings=new int[n];
	memset(rings,0,n);
	rings[0]=1;

	
	printf("Case %d:\n",cN);
	backTrack(1,rings,n);
	printf("\n");
	

	delete []rings;

}

int main(){

	int n=0,counter=1;
		
	while(scanf("%d",&n)!=EOF){

		processCase(n,counter++);	
	
	}

	return 0;
}
