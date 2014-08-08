#include<numeric>
#include<string>
#include<stdio.h>
#include<vector>
#include<iostream>
#include<algorithm>
#include<sstream>

using namespace std;

void applyFlipString(const string& flipString, string& outletString){

	for(unsigned int i=0;i<flipString.length();i++)
		if(flipString[i]=='1'){
	
			if(outletString[i]=='0')
				outletString[i]='1';
			else
				outletString[i]='0';

		}
}

int minNumberOfFlips(const vector<string>& outlets, const vector<string>& devices){


	vector<int> lengthOfFlips;
	string flipString(outlets[0].length(),'0');
	bool* outletsUsage=new bool[outlets.size()];
	vector<string> outletsCopy;	
	int outletsMatch=0;
	int temp=0;
	
	for(unsigned int i=0;i<outlets.size();i++){	
		
		flipString.assign(outlets[0].length(),'0');
		
		outletsCopy.clear();

		outletsCopy=outlets;
		
		for(unsigned int k=0;k<outlets.size();k++)
			outletsUsage[k]=false;		

		for(unsigned int j=0;j<devices[0].length();j++){
			
			if(devices[0][j]!=outletsCopy[i][j])
				flipString[j]='1';
		}

		for(int q=0;q<outlets.size();q++)
			applyFlipString(flipString,outletsCopy[q]);

		outletsUsage[i]=true;
		bool match=false;

		for(unsigned int d=1;d<devices.size();d++){
			match=false;
			for(unsigned int p=0;p<outlets.size();p++){
				if(outletsUsage[p]==false){

					if(outletsCopy[p].compare(devices[d])==0){
						outletsUsage[p]=true;
						match=true;
						break;
					}
					
				}

			}

			if(match==false)
				break;

		}

		outletsMatch=std::accumulate(outletsUsage,outletsUsage+outlets.size(),0);
	
		if(outletsMatch==outlets.size()){
			
			temp=0;
			for(unsigned int y=0;y<flipString.length();y++)
				if(flipString.at(y)=='1')
					temp++;	

			lengthOfFlips.push_back(temp);
		
		}	
		

	}

	if(!lengthOfFlips.empty()){
		std::sort(lengthOfFlips.begin(),lengthOfFlips.end());

		return lengthOfFlips[0];
	}

	else
		return -1;

}


int main(){

	int numCases=0;
	scanf("%d\n",&numCases);

	int numPairs,numBits; 
	char input[100];
	vector<string> devices,outlets;	
	string tmpString;
	int minFlips=0;
	
	for(unsigned int i=1;i<=numCases;i++){

		scanf("%d %d\n",&numPairs,&numBits);
		
		devices.clear();
		outlets.clear();
		

		for(unsigned int j=1;j<=numPairs;j++){
		
			scanf("%s",input);
			
			outlets.push_back(string(input));	

		}

		for(unsigned int j=1;j<=numPairs;j++){
		
			scanf("%s",input);
			devices.push_back(string(input));	

		}	

		//("Case #%d\n",i);
//("NumPairs: %d\t NumBits: %d\n",numPairs,		//<<"Outlets: ";
		minFlips=minNumberOfFlips(outlets,devices);
	
		if(minFlips==-1){
			printf("Case #%d: NOT POSSIBLE\n",i);
		}
		

		else
			printf("Case #%d: %d\n",i,minFlips);


		//exit(0);
	}

	return 0;
}
