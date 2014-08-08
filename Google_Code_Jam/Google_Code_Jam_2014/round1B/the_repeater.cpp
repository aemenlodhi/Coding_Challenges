#include<cstdio>
#include<vector>
#include<string>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<iostream>
#include<limits>
using namespace std;

typedef unsigned int ui;

int minActionsRequired(vector< vector<ui> > fTable){

	vector<ui> tempVector;
	bool draw=true;
	for(ui j=0;j<fTable[0].size();j++){
			tempVector.clear();
			for(ui i=0;i<fTable.size();i++){
				tempVector.push_back(fTable[i][j]);
			}

			std::sort(tempVector.begin(),tempVector.end());

			if(tempVector[0]==0 && tempVector[tempVector.size()-1]>0)
				return -1;	//Fegla Won
		
			if(tempVector[0]!=tempVector[tempVector.size()-1])	
				draw=false;
	}
	
	if(draw==true){
		//cout<<"Returning a draw"<<endl;
		return 0;
	}

	int minSum=0,minActions,temp;
	
	for(ui j=0;j<fTable[0].size();j++){

		minActions=std::numeric_limits<int>::max();

		for(ui i=0;i<fTable.size();i++){
			temp=0;
			for(ui k=0;k<fTable.size();k++){
				
				if(k!=i)
					temp+=abs(static_cast<int>(fTable[i][j])-static_cast<int>(fTable[k][j]));
			
			}

			if(temp<minActions){
				minActions=temp;
			}				

		}

		minSum+=minActions;
	
	}
	
	return minSum;
}

void populateFTEntries(const string& input, vector<char>& entries){

	char loc=input[0];
	entries.push_back(loc);

	for(ui i=1;i<input.length();i++)
		if(input[i]!=loc){
			loc=input[i];
			entries.push_back(loc);
		}

	/*
	for(ui i=0;i<entries.size();i++)
		//cout<<entries[i]<<"\t";
	//cout<<endl;
	*/
}

void populateFTable(const vector<char>& ftEntries, const vector<string>& input, vector< vector<ui> >& fTable){

	for(ui i=0;i<ftEntries.size();i++)
		for(ui j=0;j<input.size();j++)
			fTable[j][i]=0;

	ui k=0;
	for(ui i=0;i<input.size();i++){
		k=0;
		for(ui j=0;j<ftEntries.size();j++){
			
			while(k<input[i].size()){
				
				if(input[i][k]==ftEntries[j]){
					fTable[i][j]++;
					k++;
				}
	
				else
					break;

			}
	
		}

	}

	/*		
	for(ui i=0;i<fTable.size();i++){
		for(ui j=0;j<fTable[i].size();j++){
			//cout<<fTable[i][j]<<"\t";
		}
		//cout<<endl;
	}*/	

}

int processCase(const vector<string>& input){

	ui maxLengthIndex=0;
	ui maxLength=0;

	for(ui i=0;i<input.size();i++)
		if(input[i].length()>maxLength){
			maxLengthIndex=i;
			maxLength=input[i].length();
		}
	
	//cout<<input[maxLengthIndex]<<endl;


	vector<char> fTEntries;
	populateFTEntries(input[maxLengthIndex],fTEntries);

	vector< vector<ui> > fTable;

	fTable.resize(input.size());
	for(ui i=0;i<input.size();i++)
		fTable[i].resize(fTEntries.size());
	
	
	populateFTable(fTEntries,input,fTable);

	return minActionsRequired(fTable);
}

int main(){

	ui numCases=0;
	ui numStrings=0;
	char inputs[110];
	string iS;
	vector<string> vS;
	int numActions=0;

	scanf("%d\n",&numCases);

	for(ui i=1;i<=numCases;i++){

		vS.clear();
		scanf("%d\n",&numStrings);
	
		for(ui j=1;j<=numStrings;j++){
			
			scanf("%s\n",inputs);
			iS=inputs;
			vS.push_back(iS);	
		
		}

		printf("Case #%d: ",i);
		numActions=processCase(vS);

		if(numActions==-1)
			printf("Fegla Won\n");
		else
			printf("%d\n",numActions);
	
	}


	return 0;
}

