#include<vector>
#include<cstdio>

using namespace std;
typedef int ui;

int main(){

	vector<ui> input;
	ui temp;


	while(scanf("%d\n",&temp)!=EOF)
               input.push_back(temp);
	
	vector<ui> don(input.size(),0);

	ui maxdon=0;

	for(ui i=0;i<input.size();i++){
		
		temp=0;
		if((i-2)>=0)
			temp=don[i-2];	
			
		don[i]=input[i]+temp;
		
		if(input.size()%2==1 && i==input.size()-1)
			don[i]-=don[0];
		
		if(don[i]>maxdon)
			maxdon=don[i];

	}

	printf("Max donation: %d\n",maxdon);
	
	return 0;
}
