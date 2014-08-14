#include<iostream>
#include<vector>
#include<cstdio>
#include<algorithm>
#include<unordered_map>
#include<string>

using namespace std;

int numPaths(int x, int y, const int& width, const int& height, unordered_map<string,bool>& bb){

	//cout<<x<<"\t"<<y<<endl;

	if(x<0 || x>width || y<0 || y>height)
		return 0;
	
	if(x==0 && y==0)
		return 1;
	
	int nx, ny;
	string s;
	int count=0;

	//left
	nx=x-1;ny=y;
	s=to_string(x)+to_string(y)+to_string(nx)+to_string(ny);

	//cout<<"Left: "<<s<<endl;
		
	if(bb.find(s)!=bb.end()){
		if(bb[s]==false){
			//cout<<"Moving left1"<<endl;
			count+=numPaths(nx,ny,width,height,bb);
		}
	}
	
	else{
		//cout<<"Moving left2"<<endl;
		count+=numPaths(nx,ny,width,height,bb);	

	}
	
	//down
	nx=x;ny=y-1;
	s=to_string(x)+to_string(y)+to_string(nx)+to_string(ny);

	//cout<<"Down: "<<s<<endl;
	
	if(bb.find(s)!=bb.end()){
		if(bb[s]==false){
			count+=numPaths(nx,ny,width,height,bb);
		}
	}
	
	else{
		count+=numPaths(nx,ny,width,height,bb);	
	}
	return count;
}

int main(){

	int width, height;
	scanf("%d\n%d",&width,&height);
	unordered_map<string,bool> badBlocks;
	
	vector<int> bb(4,0);
	
	string s1,s2;

	while(scanf("%d %d %d %d",&bb[0],&bb[1],&bb[2],&bb[3])!=EOF){
	
		s1=std::to_string(bb[0])+std::to_string(bb[1])+std::to_string(bb[2])+std::to_string(bb[3]);
		s2=std::to_string(bb[2])+std::to_string(bb[3])+std::to_string(bb[0])+std::to_string(bb[1]);
		
		//cout<<s1<<"\t"<<s2<<endl;
		
		badBlocks[s1]=true;
		badBlocks[s2]=true;
	}

	printf("%d\n",numPaths(width,height,width,height,badBlocks));

	return 0;
}
