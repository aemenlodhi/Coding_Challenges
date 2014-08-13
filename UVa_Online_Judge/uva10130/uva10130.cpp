#include<vector>
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<limits>

typedef int ui;

using namespace std;

struct product{

	ui value;
	ui weight;
	
};

struct person{

	ui weight;
	ui value;
	person();
};

person::person(){

	weight=value=0;

}

int knapsack(const vector<product>& input, ui w, int i, vector< vector<int> >& mw){

	/*	
	for(ui x=0;x<mw.size();x++){
		for(ui y=0;y<mw[x].size();y++)
			cout<<mw[x][y]<<"\t";
		cout<<endl;
	}
	cout<<endl;
	*/
        if(i<0)
                return 0;

        if(mw[i][w]!=0)
                return mw[i][w];

        if(input[i].weight>w)
                return knapsack(input,w,i-1,mw);

        else{
		//cout<<i<<"\t"<<w<<endl;
                return mw[i][w]=std::max(input[i].value+knapsack(input,w-input[i].weight,i-1,mw),knapsack(input,w,i-1,mw));
	}
}

int processCase(vector<product>& pv, vector<person>& gv){

	vector< vector<int> > mw;	
	ui val=0;
	for(ui i=0;i<gv.size();i++){
		mw.clear();
		mw.assign(pv.size(),vector<int>(gv[i].weight+1,0));

		/*
		for(ui x=0;x<pv.size();x++){
			for(ui y=0;y<gv[i].weight;y++)
				cout<<mw[x][y]<<"\t";
			cout<<endl;
		}
		cout<<endl;
		*/		
		val+=knapsack(pv,gv[i].weight,pv.size()-1,mw);

		//cout<<"Val: "<<val<<endl;

	}
	
	return val;

}

int main(){

	ui TC, numProducts,numG;
	product p;
	person g;
	vector<product> pv;
	vector<person> gv;

	scanf("%d\n",&TC);

	while(TC--){

		scanf("%d\n",&numProducts);

		pv.clear();
		gv.clear();
		
		for(ui i=0;i<numProducts;i++){
			scanf("%d %d\n",&p.value,&p.weight);
			pv.push_back(p);
		}

		scanf("%d\n",&numG);
		for(ui i=0;i<numG;i++){
			scanf("%d\n",&g.weight);
			gv.push_back(g);
		}

		printf("%d\n",processCase(pv,gv));
			
	}
	
	return 0;
}
