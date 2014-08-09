#include<iostream>
#include<queue>
#include<vector>
#include<cstdio>
#include<algorithm>

typedef unsigned int ui;

using namespace std;

struct box{

	ui totalSize;
	ui currentSize;
	vector<ui> occupants;

};

struct compareBox{

	bool operator()(const box& b1, const box& b2){
	
		if(b1.totalSize>b2.totalSize)
			return true;
		
		else if(b1.totalSize==b2.totalSize){
			if(b1.occupants.size()>b2.occupants.size())
				return true;
			else
				return false;
		}

		else
			return false;

	}

};

void processCase(vector<ui>& boxes){

	std::sort(boxes.begin(),boxes.end());
	
	priority_queue<box,vector<box>,compareBox> nBoxes;
	queue<box> reserve;
	box nb;

	for(ui i=0;i<boxes.size();i++){
	
		nb.totalSize=nb.currentSize=boxes[i];
		nBoxes.push(nb);
	}
	
	bool move=true;
	box object, subject; 

	while(move){
	
		object=nBoxes.top();
		nBoxes.pop();
		move=false;	
	
		do{
			subject=nBoxes.top();
			nBoxes.pop();

			if(subject.currentSize>object.totalSize){

				subject.currentSize-=object.totalSize;
				subject.occupants.push_back(object.totalSize);
				nBoxes.push(subject);
				move=true;

				while(!reserve.empty()){
			
					nb=reserve.front();
					nBoxes.push(nb);
					reserve.pop();	
		
				}	

				break;
			}

			else{

				reserve.push(subject);
			}

		}while(!nBoxes.empty());
				

	}
	

	vector<box> output;

	output.push_back(object);
	while(!reserve.empty()){
	
		nb=reserve.front();
		output.push_back(nb);
		reserve.pop();
	}

	for(ui i=0;i<output.size();i++){
		std::sort(output[i].occupants.begin(),output[i].occupants.end());
		std::unique(output[i].occupants.begin(),output[i].occupants.end());
	}
		
	printf("%ld\n",output.size());
	//cout<<output.size()<<endl;
	for(ui i=0;i<output.size();i++){
	
		printf("%d",output[i].totalSize);

		if(!output[i].occupants.empty()){
			printf(" ");
			for(ui j=0;j<output[i].occupants.size();j++){
		
				if(j<(output[i].occupants.size()-1))
					printf("%d ",output[i].occupants[j]);
				else
					printf("%d\n",output[i].occupants[j]);

			}
		}
		else
			printf("\n");
	}

	printf("\n");
}

int main(){

	ui numBoxes;
	ui temp;
	vector<ui> boxes;
	while(1){
	
		scanf("%d",&numBoxes);
		if(numBoxes==0)
			break;
		else{
			for(ui i=0;i<numBoxes;i++){
				scanf("%d",&temp);
				boxes.push_back(temp);
	
			}

		processCase(boxes);
		}

	}
	
	return 0;
}
