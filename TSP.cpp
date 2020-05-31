#include"TSP.h"

using namespace std;

ofstream output_sol,output_trace;

int main(int argc, char* argv[])
{
    string Methods []= {"Greedy"};
    
    
    int **distance;
    int *d=new int;
    int *o=new int;
    distance=readgraph(argv[1],d,o);
    cout << "NAME" << NAME << endl;
    int dim=*d;
    int opt=*o;
    double cutoff = strtod(argv[2],NULL);
    int seed=atoi(argv[4]);
    
    int i;
    int pathlength = 0;
    double gap;

    if(Method[0])
    {
        cout << "Method:" << "Greedy"<<endl;
        int *path;
        path=greedy_algo(distance, dim);

        cout<<"Path:";
        
        for(i=0;i<dim-1;i++)
            pathlength += distance[path[i]][path[i+1]];
        pathlength += distance[path[dim-1]][path[0]];
        output_sol << pathlength <<endl;
        for(i=0;i<dim-1;i++)
        {
            cout<<path[i]+1<<",";
            output_sol << path[i]+1<<",";
        }
        cout<<path[dim-1]+1<<","<<path[0]+1<<endl;
        output_sol<<path[dim-1]+1<<","<<path[0]+1<<endl;
        
        cout<<"Path Length:";
        cout<<pathlength<<endl;
        return 0;
    }
        int *min;
        if(solution->time<cutoff)
        {
            cout << "Optimal solution found:"<< endl;
            cout << "Total cost:" << solution->value << endl;
            cout << "Optimal cycle:" ;
            for(vector<int>::const_iterator it=solution->path->begin();it!=solution->path->end();it++)
            {
                cout<<*it+1<<",";
                output_sol <<*it+1<<",";
            }
            cout << source+1 << endl;
            output_sol<< source+1 << endl;
            cout << "Elapsed time:"<< solution->time << "s" << endl;
        }
        else
        {
            cout << "Total cost:" << solution->value << endl;
            gap = (float)(solution->value-opt)/opt;
            cout << "Solution cycle:" ;
            for(vector<int>::const_iterator it=solution->path->begin();it!=solution->path->end();it++)
            {
                cout<<*it+1<<",";
                output_sol <<*it+1<<",";
            }
            cout << source+1 << endl;
            output_sol<< source+1 << endl;
            cout << "Elapsed time:"<< solution->time << "s" << endl;
        }
        return 0;
    }
}
