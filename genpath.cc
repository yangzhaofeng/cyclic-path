#include <iostream>

using namespace std;

#define MAX_NODE_NUMBER 200

typedef struct node_path
{
	int node_number;
	struct node_path* next;
} node_path;

int connect[MAX_NODE_NUMBER][MAX_NODE_NUMBER] = {};

void genpath(int node, int node1, int node2){
	int nodecount = 2;
	node_path path[MAX_NODE_NUMBER];
	for(int i=0; i<MAX_NODE_NUMBER; i++){
		path[i].node_number = 0;
		path[i].next = NULL;
	}
	path[0].node_number = node1;
	path[0].next = &path[1];
	path[1].node_number = node2;
	int current_node = 1;
	while(path[current_node - 1].next != path){
		bool flag_break = false;
		//path[current_node].next = &path[current_node+1];
		for(int i=1; i<=node; i++){
			if(connect[path[current_node].node_number][i] > 1 && i == node1){
				path[current_node].next = path;
				flag_break = true;
				break;
			}
		}
		if (flag_break){
			break;
		}
		for(int i=1; i<=node; i++){
			if(path[current_node].next != path && connect[path[current_node].node_number][i] > 1){
				path[current_node + 1].node_number = i;
				path[current_node].next = &path[current_node + 1];
			}
		}
		current_node++;
	}
	for(int i=0; path[i].next != NULL; i++){
		cout<<path[i].node_number<<" ";
	}
	cout<<path[0].node_number<<endl;
}

void DFS(int node, bool* visited, int node_start){
	visited[node_start] = true;
	for(int i=1; i<=node; i++){
		if(connect[node_start][i] == 0){
			continue;
		}else{
			if(!visited[i]){
				connect[node_start][i]++;
				connect[i][node_start]++;
				DFS(node, visited, i);
			}
		}
	}
}

int main(){
	int edge, node;
	cin>>edge>>node;
//	int connect[MAX_NODE_NUMBER][MAX_NODE_NUMBER] = {};
//	int 
	for(int i=1; i<=edge/2; i++){
		int node1, node2;
		cin>>node1>>node2;
		connect[node1][node2]=1;
		connect[node2][node1]=1;
	}
/*
	int index_x=0, index_y=0;
	for(int i=1; i<=node; i++){
		bool flag_break = false;
		for(int j=1; j<=node; j++){
			if( connect[i][j] >= 1 ){
				index_x = i;
				index_y = j;
				flag_break = true
				break;
			}
		}
		if(flag_break){
			break;
		}
	}
*/
	int node_start = 1;  // assume there is no independent node
	bool visited[MAX_NODE_NUMBER] = {false};
	DFS(node, visited, node_start);
	for(int i=1; i<=node; i++){
		for(int j=1; j<=i; j++){
			if(connect[i][j] >= 1){
				cout<<i<<" "<<j<<" "<<i<<endl;
			}
			if(connect[i][j] == 1){
				//cout<<i<<" "<<j<<endl;
				genpath(node, i,j);
			}
		}
	}
	return 0;
}
