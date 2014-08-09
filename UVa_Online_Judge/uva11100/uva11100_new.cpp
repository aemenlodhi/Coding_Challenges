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

	//cout<<"Beginning processing"<<endl;

	std::sort(boxes.begin(),boxes.end());
	vector<box> nBoxes;
	box nb;

	for(ui i=0;i<boxes.size();i++){
	
		nb.totalSize=nb.currentSize=boxes[i];
		nBoxes.push_back(nb);
	}
	
	bool move=true;
	int loc=0,obj=0;

	while(move){

		move=false;

		obj=0;

		//cout<<"Starting at "<<obj<<endl;
	
		for(ui i=1;i<nBoxes.size();i++){
			
			if(nBoxes[i].totalSize>nBoxes[obj].totalSize){
				break;
			}
			
			else{
			
				if(nBoxes[i].occupants.size()<nBoxes[obj].occupants.size())
					obj=i;
				
			}
		
		}

		//cout<<"considering moving "<<nBoxes[obj].totalSize<<" at "<<obj<<endl;
			
		nb=nBoxes[obj];
	
		for(ui i=obj+1;i<nBoxes.size();i++){

			if(nBoxes[i].currentSize<=nb.totalSize){}

			else{
				loc=i;
				for(ui j=i+1;j<nBoxes.size();j++){

					if(nBoxes[j].totalSize>nBoxes[i].totalSize){
						break;
					}

					else{
						if(nBoxes[j].occupants.size()<nBoxes[loc].occupants.size()){
							loc=j;
						}
			
						else
							break;
							
					}

				}

				//cout<<"moved to "<<loc<<" with current size "<<nBoxes[loc].currentSize<<endl;

				nBoxes[loc].currentSize-=nb.totalSize;
				nBoxes[loc].occupants.push_back(nb.totalSize);
				if(!nb.occupants.empty())
					nBoxes[loc].occupants.insert(nBoxes[loc].occupants.end(),nb.occupants.begin(),nb.occupants.end());
				/*	
				//cout<<"current state of "<<loc<<" is ";
				//cout<<nBoxes[loc].totalSize<<" ";
				if(!nBoxes[loc].occupants.empty())
					for(ui x=0;x<nBoxes[loc].occupants.size();x++)
						//cout<<nBoxes[loc].occupants[x]<<" ";
				//cout<<endl;
				*/
				move=true;
				nBoxes.erase(nBoxes.begin()+obj);

			
				break;				
			}

		}
		

	}


	printf("%ld\n",nBoxes.size());
	for(ui i=0;i<nBoxes.size();i++){

		cout<<nBoxes[i].totalSize<<" ";
		std::sort(nBoxes[i].occupants.begin(),nBoxes[i].occupants.end());
		vector<ui>::iterator it=std::unique(nBoxes[i].occupants.begin(),nBoxes[i].occupants.end());
		nBoxes[i].occupants.resize(std::distance(nBoxes[i].occupants.begin(),it));

		for(vector<ui>::iterator it=nBoxes[i].occupants.begin();it!=nBoxes[i].occupants.end();it++)
			cout<<*it<<" ";
		cout<<endl;
		/*		
		printf("%d",nBoxes[i].totalSize);

		if(!nBoxes[i].occupants.empty()){
			
			std::sort(nBoxes[i].occupants.begin(),nBoxes[i].occupants.end());
			std::unique(nBoxes[i].occupants.begin(),nBoxes[i].occupants.end());

			printf(" ");
			for(ui j=0;j<nBoxes[i].occupants.size();j++){
		
				//if(j<(nBoxes[i].occupants.size()-1))
					printf("%d ",nBoxes[i].occupants[j]);
				//else
				//	printf("%d\n",nBoxes[i].occupants[j]);

			}
			printf("\n");
		}
		else
			printf("\n");

		*/	
	}

	printf("\n");

	/*
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

	printf("\n");*/
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
			boxes.clear();
			for(ui i=0;i<numBoxes;i++){
				scanf("%d",&temp);
				boxes.push_back(temp);
	
			}

			processCase(boxes);
		}

	}
	
	return 0;
}
