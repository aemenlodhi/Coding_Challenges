#include<vector>
#include<iostream>
#include<cstdio>

using namespace std;

struct z{

	int length=0;
	int loc=0;
	int diff=1;
};

int zz(vector<int>& seq, vector<z>& len, int i, int loc){

	if(loc==0){
		len[i].loc=0;
		return 1;
	}
	
	if((len[i].diff=(seq[i]-seq[loc])%2)!=len[i-1].diff && len[i].diff!=0){
		len[i].length=1+len[loc].length;
		len[i].loc=loc;
	}

	else{
		len[i].length=1+zz(seq,len,i,len[loc].loc);
	}

	return len[i].length;
}

int longestZigZag(vector<int>& seq){

	if(seq.size()<=2)
		return seq.size();

	vector<z> len(seq.size());
	len[0].length=1;
	len[1].length=2;
	len[1].diff=(seq[1]-seq[0])%2;	
	len[1].loc=0;

	int maxLength=2;

	for(int i=2;i<seq.size();i++){
	
		len[i].length=zz(seq,len,i,i-1);
		if(len[i].length>maxLength)
			maxLength=len[i].length;
	}
		
	return maxLength;

}

int main(){

	vector<int> seq;
	int temp;

	while(scanf("%d",&temp)!=EOF){
		seq.push_back(temp);
	}

	printf("%d\n",longestZigZag(seq));

	return 0;

}
