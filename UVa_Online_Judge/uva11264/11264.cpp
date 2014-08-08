#include<vector>
#include<cstdio>
#include<iostream>
#include<cmath>

using namespace std;

typedef unsigned int ui;
typedef unsigned long int uli;

void withdraw(const uli& x,const vector<uli>& coins, vector<uli>& withdrawnCoins){

	if(x==0)
		return;

	else{
		for(ui i=(coins.size()-1);i>=0;i--)
			if(x>coins[i]){
				withdrawnCoins.push_back(coins[i]);		
				withdraw(x-coins[i],coins,withdrawnCoins);
				break;
			}
	}

}

ui processCase(const vector<uli>& coins){


	uli val=0;
	vector<uli> chosen;
	for(ui i=0;i<coins.size();i++){
		
		if(i==(coins.size()-1)||(val+coins[i])<coins[i+1]){
			val+=coins[i];
			chosen.push_back(coins[i]);
		}
		
	}

	return chosen.size();
	
}

int main(){

	ui numCases=0;
	scanf("%d\n",&numCases);

	ui numCoins=0;
	uli temp=0;
	vector<uli> coins;	

	for(ui i=0;i<numCases;i++){

		scanf("%d\n",&numCoins);
		
		coins.clear();

		for(ui j=0;j<numCoins;j++){

			scanf("%ld",&temp);
			coins.push_back(temp);
		}
		
		printf("%d\n",processCase(coins));

	}


	return 0;
}
