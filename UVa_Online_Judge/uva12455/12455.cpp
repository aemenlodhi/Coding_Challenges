#include<stdio.h>

typedef unsigned int ui;

void printCase(const ui& cN, const ui& rL, const ui& nB, ui* bL){
	
	printf("Case Number: %d\nRequired Length: %d\nNumber of Bars: %d\n",cN,rL,nB);
	printf("Bar Lengths: ");
	for(int i=0;i<nB;i++)
		printf("%d ",bL[i]);
	printf("\n");
	

}

bool processCase(const ui& rL, const ui& nB, ui* bL){

	long unsigned int i;

	ui sum=0;
	for(i=0;i<(1<<nB);i++){
		sum=0;
		
		for(ui j=0;j<nB;j++)
			if(i & (1<<j))
				sum+=bL[j];


		if(sum==rL)
			return true;

	}

	return false;
}

int main(){

	ui numCases=0;
	ui requiredLength, numBars;
	ui* barLengths;

	scanf("%d\n",&numCases);

	for(ui i=1;i<=numCases;i++){
		
		scanf("%d\n%d\n",&requiredLength,&numBars);

		if(barLengths==NULL)
			barLengths=new ui[numBars];
		else{
			delete []barLengths;
			barLengths=new ui[numBars];
		}
		
		for(ui n=0;n<numBars;n++)
			scanf("%d",&barLengths[n]);

		//printCase(i,requiredLength,numBars,barLengths);		
		if(processCase(requiredLength,numBars,barLengths))
			printf("YES\n");
		else
			printf("NO\n");
	}	


	return 0;
}
