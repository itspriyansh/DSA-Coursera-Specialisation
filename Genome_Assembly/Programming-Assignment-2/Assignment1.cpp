#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <algorithm>
#define SIZE 25

using namespace std;

// void print(vector<vector<int> >& ans){
// 	cout<<"Ans:\n";
// 	for(int i=0;i<ans.size();i++){
// 		for(int j: ans[i]){
// 			cout<<j<<" ";
// 		}cout<<endl;
// 	}
// }

int main(){
	vector<vector<string> > list(SIZE);
	vector<int> ind(SIZE);

	for(int i=0;i<SIZE;i++){
		ind[i] = i;
		string temp, ins;
		cin>>temp;
		for(int j=1;j<temp.size();j++){
			if(temp[j]==','|temp[j]==')'){
				list[i].push_back(ins);
				if(temp[j]==')') break;
				ins.clear();
			}else{
				ins += temp[j];
			}
		}
	}

	int n = sqrt(SIZE), size = SIZE;
	vector<vector<int> > ans(n, vector<int>(n));

	for(int in=0;in<size;in++){
		bool corner = true;
		int i = ind[in];
		if(list[i][0]=="black"&&list[i][1]=="black"){
			ans[0][0]=i;
		}else if(list[i][1]=="black"&&list[i][2]=="black"){
			ans[n-1][0]=i;
		}else if(list[i][2]=="black"&&list[i][3]=="black"){
			ans[n-1][n-1]=i;
		}else if(list[i][3]=="black"&&list[i][0]=="black"){
			ans[0][n-1]=i;
		}else corner = false;
		if(corner){
			swap(ind[in--], ind[--size]);
		}
	}

	for(int in=0, pos=1;in<size && pos+1<n;in++){
		int i = ind[in];
		if(list[i][0]=="black" && list[i][1]==list[ans[0][pos-1]][3]){
			ans[0][pos++] = i;
			swap(ind[in], ind[--size]);
			in = -1;
		}
		if(in+1>=size){
			in = -1;
			pos--;
			size++;
		}
	}

	for(int in=0, pos=1;in<size && pos+1<n;in++){
		int i = ind[in];
		if(list[i][2]=="black" && list[i][1]==list[ans[n-1][pos-1]][3]){
			ans[n-1][pos++] = i;
			swap(ind[in], ind[--size]);
			in = -1;
		}
		if(in+1>=size){
			in = -1;
			pos--;
			size++;
		}
	}

	for(int in=0, pos=1;in<size && pos+1<n;in++){
		int i = ind[in];
		if(list[i][1]=="black" && list[i][0]==list[ans[pos-1][0]][2]){
			ans[pos++][0] = i;
			swap(ind[in], ind[--size]);
			in = -1;
		}
		if(in+1>=size){
			in = -1;
			pos--;
			size++;
		}
	}

	for(int in=0, pos=1;in<size && pos+1<n;in++){
		int i = ind[in];
		if(list[i][3]=="black" && list[i][0]==list[ans[pos-1][n-1]][2]){
			ans[pos++][n-1] = i;
			swap(ind[in], ind[--size]);
			in = -1;
		}
		if(in+1>=size){
			in = -1;
			pos--;
			size++;
		}
	}

	// print(ans);

	bool back = false;
	for(int in=0,x=1,y=1;in<size&&x+1<n&&y+1<n;in++){
		// cout<<"Achieve to "<<x<<" "<<y<<" with size "<<size<<endl;
		// for(int l=0;l<size;l++){
		// 	cout<<ind[l]<<" ";
		// }cout<<endl;

		int i = ind[in];
		if(list[ans[x-1][y]][2]==list[i][0] && list[ans[x][y-1]][3]==list[i][1]){
			ans[x++][y] = i;
			if(back){
				swap(ind[in], ind[size]);
				back = false;
			}
			else swap(ind[in], ind[--size]);
			in =-1;
			if(x+1>=n){
				x=1;
				y++;
			}
		}
		if(in+1>=size){
			in = -1;
			x--;
			if(x<1){
				x=n-2;
				y--;
			}
			if(back) size++;
			else back = true;
		}
		// print(ans);
	}

	for(int i=0;i<n;i++){
		for(int j: ans[i]){
			cout<<"(";
			for(int k=0;k<4;k++){
				cout<<list[j][k];
				if(k<3) cout<<",";
			}cout<<")";
			if(j!=ans[i].back()) cout<<";";
		}cout<<endl;
	}

	// print(ans);
	return 0;
}