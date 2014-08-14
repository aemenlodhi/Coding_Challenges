#include<vector>
#include<cstdio>

using namespace std;
typedef int ui;


int maxDon(vector<int>& don,int i,vector<int>& md){

	if(i<0)
		return 0;

	if(md[i]!=0)
		return md[i];
	
	return md[i]=max(maxDon(don,i-1,md),maxDon(don,i-2,md)+don[i]);

}

int main(){

	vector<ui> input;
	ui temp;

	while(scanf("%d\n",&temp)!=EOF)
               input.push_back(temp);
	
	vector<ui> v1(input.begin(),input.end()-1),v2(input.begin()+1,input.end());
	
	vector<ui> md1(v1.size(),0), md2(v2.size(),0);

	printf("Max donation: %d\n",std::max(maxDon(v1,v1.size()-1,md1),maxDon(v2,v2.size()-1,md2)));
	
	return 0;
}
