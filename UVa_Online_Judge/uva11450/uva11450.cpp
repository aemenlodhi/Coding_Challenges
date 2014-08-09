#include<iostream>
#include<cstdio>
#include<cstring>
#include<limits>

using namespace std;
typedef unsigned int ui;

int price[25][25];
int memo[250][25];

int shop(int money, int model,const int maxMoney,const int maxModels ){

	if(money<0)
		return std::numeric_limits<int>::min();

	if(model==maxModels)
		return maxMoney-money;

	if(memo[money][model]!=-1)
		return memo[money][model];

	int ans=std::numeric_limits<int>::min();
	for(ui i=1;i<=price[model][0];i++)
		ans=max(ans,shop(money-price[model][i],model+1,maxMoney,maxModels));

	return memo[money][model]=ans;
}

int main(){

	int numC=0,M,C;
	
	int score;
	scanf("%d\n",&numC);

	//cout<<numC<<endl;

	while(numC--){

		scanf("%d %d\n",&M,&C);
		
		//cout<<M<<" "<<C<<endl;

		memset(price, -1, sizeof price);
		memset(memo,-1,sizeof memo);

		for(int i=0;i<C;i++){
			
			scanf("%d",&price[i][0]);
			//cout<<price[i][0]<<" ";
			for(int j=1;j<=price[i][0];j++){
				scanf("%d",&price[i][j]);
				//cout<<price[i][j]<<" ";
			}
			//cout<<endl;
			
		}
		/*
		for(int i=0;i<C;i++){
			cout<<price[i][0]<<" ";
			for(int j=1;j<=price[i][0];j++)
				cout<<price[i][j]<<" ";
			cout<<endl;
	
		}*/
			
		score=shop(M,0,M,C);

		if(score<0)
			printf("no solution\n");
		else
			printf("%d\n",score);		

	}	
		
	return 0;
}
