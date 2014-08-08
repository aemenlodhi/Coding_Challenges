#include<stdio.h>
#include<vector>
#include<list>
#include<unordered_map>
#include<stack>
#include<iostream>
using namespace std;

typedef unsigned int ui;
typedef vector<ui>::const_iterator c_iVi;
typedef list<ui>::iterator iLi;

struct childCount{

	ui id;
	ui cCount;

};

bool childrenCompare(const childCount& n1, const childCount& n2){

	if(n1.cCount<n2.cCount)
		return true;
	else
		return false;
}

ui findChildren(const vector< vector <ui> >& tree, const ui& target, std::unordered_map<ui,int>& childrenRecord){

	//cout<<"Finding children for node "<<target<<endl;
	
	list<ui> children;
	stack<ui> traversal;
	ui temp;
	ui numC=0;		

	if(childrenRecord[target]!=-1){
		//cout<<"At first return condition: the number of children of node "<<target<<" are "<<childrenRecord[target]<<endl;
		return childrenRecord[target];
	}
	if(tree[target].empty()){
		
		childrenRecord[target]=0;
		//cout<<"At second return condition: the number of children of node "<<target<<" are "<<childrenRecord[target]<<endl;
		return childrenRecord[target];	
	
	}

	for(c_iVi it=tree[target].begin();it!=tree[target].end();it++){
		++numC+=findChildren(tree,*it,childrenRecord);
	
	
	}

	childrenRecord[target]=numC;

	//cout<<"Number of children of node "<<target<<" are: "<<childrenRecord[target]<<endl;

	return childrenRecord[target];
	
}

ui convertToFullBinary(const ui& root, vector< vector<ui> > tree, const ui& numV){

	std::stack<ui> traversal;
	std::unordered_map<ui,int> numChildren;
	std::list<childCount> counter;
	ui node;	
	childCount tempC;
	ui numDel=0;
	ui temp=0;

	for(ui i=1;i<=numV;i++)
		numChildren[i]=-1;

	//cout<<"Processing for root: "<<root<<endl;

	traversal.push(root);

	while(!traversal.empty()){
	
		node=traversal.top();
		traversal.pop();

		//cout<<"Processing node: "<<node<<endl;
	
		if(tree[node].size()>2){
			
			counter.clear();
			
			for(vector<ui>::iterator it=tree[node].begin();it!=tree[node].end();it++){

				tempC.id=*it;
				if(numChildren[*it]!=-1)
					tempC.cCount=numChildren[*it];

				else
					tempC.cCount=findChildren(tree,*it,numChildren);	
				
				counter.push_back(tempC);
						
			}

			counter.sort(childrenCompare);
			
			temp=0;
			for(list<childCount>::iterator it=counter.begin();it!=counter.end();it++,temp++){
		
				if(temp<(counter.size()-2)){
					++numDel+=(*it).cCount;
					//cout<<"Deleting node "<<(*it).id<<" with children "<<(*it).cCount<<endl;
					//cout<<numDel<<" nodes deleted so far"<<endl;
				}

				else
					traversal.push((*it).id);
			}
					
		}

		else if(tree[node].size()==1){
			++numDel+=findChildren(tree,tree[node][0],numChildren);
			//cout<<"Deleting node "<<tree[node][0]<<" with possibly some children"<<endl;
			//cout<<numDel<<" nodes deleted so far"<<endl;
		}	

		else{

			for(vector<ui>::iterator it=tree[node].begin();it!=tree[node].end();it++){
				traversal.push(*it);				
			}
		
		}

	}
	
	//cout<<"Num deletions for root "<<root<<" are: "<<numDel<<endl;

	return numDel;

}

void createTreeRepresentation(const ui& root, const vector< vector<ui> >& aRep, vector< vector<ui> >& tRep,const int& numV){

	//cout<<"Node "<<root<<" has been marked as root"<<endl;

	tRep.clear();
	tRep.resize(aRep.size());	
	std::unordered_map<ui,bool> markedNodes;	
	for(ui i=0;i<numV;i++)
		markedNodes[i]=false;	

	list<ui> traversal;

	markedNodes[root]=true;
	for(c_iVi it=aRep[root].begin();it!=aRep[root].end();it++){
		tRep[root].push_back(*it);
		markedNodes[*it]=true;
		traversal.push_back(*it);
	}	

	for(iLi it=traversal.begin();it!=traversal.end();it++){
		for(c_iVi itV=aRep[*it].begin();itV!=aRep[*it].end();itV++){
			if(markedNodes[*itV]==false){
				tRep[*it].push_back(*itV);
				markedNodes[*itV]=true;
				traversal.push_back(*itV);
			}
		}
	}
	

	//debug
	/*	
	for(ui i=1;i<=numV;i++){
		cout<<i<<": ";
		for(vector<ui>::iterator it=tRep[i].begin();it!=tRep[i].end();it++)
			cout<<*it<<" ";
		cout<<endl;
	}
	*/
	

}

int processCase(const ui& numV, const vector< vector<ui> >& aRep){

	list<ui> possibleRoots;
	int numDeletions=numV+1;
	vector< vector<ui> > tRep;
	int temp;

	//find possible roots
	//iterate over each possible root
	//create tree representation for each root
	//process each tree and record the number of deletions required

	//find possible roots. nodes with two or more elements in the adjacency list
	//cout<<"Possible roots: ";
	for(ui i=1;i<=numV;i++)
		if(aRep[i].size()>=1){
			possibleRoots.push_back(i);
			//cout<<i<<"\t";
		}
	//cout<<endl;
	
	for(list<ui>::iterator it=possibleRoots.begin();it!=possibleRoots.end();it++){
	//create tree representation
		tRep.clear();
		createTreeRepresentation(*it,aRep,tRep,numV);
		
		if((temp=convertToFullBinary(*it,tRep,numV))<numDeletions)
			numDeletions=temp;
	}
	
	return numDeletions;	

}

int main(){

	int numCases=0;
	scanf("%d\n",&numCases);
	
	int numNodes;
	vector< vector<ui> > aR;
	ui x,y;

	for(int i=1;i<=numCases;i++){
	
		aR.clear();	

		scanf("%d\n",&numNodes);
		aR.resize(numNodes+1);

		//<<"Case #"<<i<<" : NumNodes: "<<numNodes<<endl;

		for(int n=1;n<=(numNodes-1);n++){
	
			////<<"Finding edge "<<n<<endl;	
			scanf("%d %d\n",&x,&y);
			
			//<<"Creating edge between "<<x<<"\t"<<y<<endl;

			aR[x].push_back(y);
			aR[y].push_back(x);

			////<<"Created edge between "<<x<<"\t"<<y<<endl;

		}

		////<<"Edges created "<<endl;
		/*
		for(int i=1;i<=numNodes;i++){
			//<<i<<": ";
			
			for(vector<ui>::iterator it=aR[i].begin();it!=aR[i].end();it++)
				//<<*it<<" ";
			//<<endl;

		}
		*/	
		printf("Case #%d: %d\n",i,processCase(numNodes,aR));
	
	}
	
	return 0;


}
