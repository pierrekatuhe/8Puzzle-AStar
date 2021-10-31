#include <bits/stdc++.h>
#include <functional>
using namespace std;

map<vector<vector<int> > , bool> visited;
map<vector<vector<int> > , vector<vector<int> > > parent;
vector<vector<int> > goal(3,vector<int> (3));

bool visit(vector<vector<int> > a)
{
	if(visited[a]==true)
		return true;
	else
		return false;
}

int manhattan(vector<vector<int> > a , int moves)
{
	int dist=moves;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(a[i][j]!=0)
			{
				for(int k=0;k<3;k++)
				{
					for(int l=0;l<3;l++)
					{
						if(a[i][j]==goal[k][l])
							dist+=abs(i-k)+abs(j-l);
					}
				}
			}
		}
	}
	
	return dist;
}

bool isGoal(vector<vector<int> > a)
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(a[i][j]!=goal[i][j])
				return false;
		}
	}

	return true;
}

bool safe(int i,int j)
{
	if(i>=0 && i<=2 && j>=0 && j<=2)
		return true;
	else
		return false;
}

int dx[]={-1,+1,0,0};
int dy[]={0,0,-1,+1};

vector<vector<vector<int> > > neighbours(vector<vector<int> > a)
{
	pair<int,int> pos;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(a[i][j]==0)
			{
				pos.first=i;
				pos.second=j;
				break;
			}
		}
	}
	vector<vector<vector<int> > > ans;
	for(int k=0;k<4;k++)
	{
		int cx = pos.first;
		int cy = pos.second;
		vector<vector<int> > n = a;
		if(safe(cx+dx[k],cy+dy[k]))
		{
			swap(n[cx+dx[k]][cy+dy[k]],n[cx][cy]);
			ans.push_back(n);
		}
	}

return ans; 
}
		
typedef pair<vector<vector<int> > , int> state;

struct cmp
{
	bool operator() (state &a, state &b)
	{
		int am = manhattan(a.first,a.second);
		int bm = manhattan(b.first,b.second);
		return am<bm;
	}
};

void print_path(vector<vector<int> > s)
{
   	if(parent.count(s))
   	print_path(parent[s]);
   
   	for(int i=0;i<3;i++)
   	{
	 	for(int j=0;j<3;j++)
	 	{
			printf("%d ",s[i][j]);
	 	}
		cout<<endl;
   	}
   
   	cout<<endl;
 	return;
}

void print(vector<vector<int> > s)
{
	for(int i=0;i<3;i++)
   	{
		for(int j=0;j<3;j++)
	 	{
			printf("%d ",s[i][j]);
	 	}
		cout<<endl;
   	}
}

void solve(vector<vector<int> > a, int moves)
{
	priority_queue<state,vector<state>,cmp > Q;
	priority_queue<state,vector<state>,cmp > Q_temp = Q;
	Q.push(state(a,moves));
	bool doneSolve = 0;
	while(!Q.empty())
	{
		vector<vector<int> > s = Q.top().first;
		Q.pop();
		
		visited[s]=true;
//		print(s);
		if(s==goal)
		{
//			printf("yeah\n");
			cout<<"\nSolution...\n";
			print_path(s);
			doneSolve = 1;
			break;
		}
		vector<vector<vector<int> > > ns = neighbours(s);
		vector<vector<vector<int> > >::iterator it;
//		printf("1..\n");
		for(it=ns.begin();it!=ns.end();it++)
		{
			//print(*it);
			//cout<<endl;
			vector<vector<int> > temp = *it;
			if(!visit(temp))
			{
				parent.insert(pair<vector<vector<int> > , vector<vector<int> > >(temp,s));
				Q.push(state(temp,moves+1));
			}
		}
	}
	if(!doneSolve)
		cout<<"Iteration limit amount reached...\n\n";
	Q = Q_temp;
	return;
}

vector<vector<int> > shuffle(vector<vector<int> > a)
{
	int temp = 0;
	int randomIndex1 = 0;
	int randomIndex2 = 0;
	
	cout<<"Shuffling...\n";
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			randomIndex1 = rand() % 3;
			randomIndex2 = rand() % 3;
			temp = a[i][j];
			a[i][j] =  a[randomIndex1][randomIndex2];
			a[randomIndex1][randomIndex2] = temp;
		}
	}
	cout<<"Done Shuffling...\n";
	return a;
}

int main()
{
	string selectOption;
	vector<vector<int> > a(3,vector<int> (3));
	
	cout << "Welcome to the 8 Puzzle Solver with A* Algorithm" << endl;
	cout << "Please input a number from 0-8 with the format below" << endl;
	cout << "1 2 3\n4 5 6\n7 8 0" << endl;
	cout << "\nYour input: " << endl;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			cin>>a[i][j];	
		}
	}
	goal[0][0] = 1;
	goal[0][1] = 2;
	goal[0][2] = 3;
	goal[1][0] = 4;
	goal[1][1] = 5;
	goal[1][2] = 6;
	goal[2][0] = 7;
	goal[2][1] = 8;
	goal[2][2] = 0;		
	
	do{
		cout<<"\nTrying to solve...\n";
		solve(a,0);
		cout << "Total Steps: " << manhattan(a, 0) << endl;
		
		cout << "Do you want to shuffle again?" << endl;
		cout << "1. Shuffle and solve" << endl;
		cout << "2. End" << endl;
		cout << "Selection: ";
		cin >> selectOption;
		
		if(selectOption == "1"){
			system("CLS");
			a = shuffle(a);
			cout << "Your Number: " << endl;
    		print(a);
		}else{
			cout << "Thanks for playing!";
			return 0;
		}
	}while(true);
}
