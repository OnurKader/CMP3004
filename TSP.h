#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<string>
#include<cmath>
#include<ctime>
#include<cstdlib>
#include<climits>
#include<stack>
#include <map>
#include <cassert>

using namespace std;

extern string NAME;
extern ofstream output_sol,output_trace;

int findpathLength(int **distance);


int *greedy_algo(int **distance, int dim);




struct Edge{

    int length;
};
/*
class CompareEdge{
public:
    bool operator()(Edge*& e1, Edge*& e2)
    {
        return e1->length > e2->length;
    }
};


int Kruskal(int **distance, vector<int> *set);

int FindMin(int *v, vector<int> *range);


struct Node *BranchAndBound(int **distance, int dim, int *min, int start, double cutoff);
*/
