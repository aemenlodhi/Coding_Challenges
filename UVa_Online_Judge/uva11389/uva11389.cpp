#include<iostream>
#include<vector>
#include<cstdio>
#include<algorithm>

using namespace std;

typedef unsigned int ui;

ui processCase(const ui& n, const ui& d, const ui& r, vector<ui>& morning, vector<ui>& evening){

	std::sort(morning.begin(),morning.end());
	std::sort(evening.begin(),evening.end());

	ui extraCost=0;
	ui extraHours=0;
	for(ui i=0;i<morning.size();i++)
		if((extraHours=morning[i]+evening[evening.size()-1-i])>d)
			extraCost+=((extraHours-d)*r);

	return extraCost;

}


int main(){

	bool end=false;

	ui n,d,r;
	vector<ui> morning;
	vector<ui> evening;	

	ui temp;

	while(1){

		scanf("%d %d %d\n",&n,&d,&r);

		if(n==0 && d==0 && r==0)
			break;

		morning.clear();
		evening.clear();

	
		for(ui i=0;i<n;i++){
			scanf("%d",&temp);
			morning.push_back(temp);	
		}

		for(ui i=0;i<n;i++){
			scanf("%d",&temp);
			evening.push_back(temp);	
		}


		printf("%d\n",processCase(n,d,r,morning,evening));

	}	


	return 0;

}
