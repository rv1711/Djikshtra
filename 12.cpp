#include<iostream>
#include<limits>
#define N 100

using namespace std;

struct g{
    int val,flag=0;
};

class djikstra{
private:
    int no_vertices;
    int graph[N][N];
    g com[N][N];
    int dis[N];
    int st_pt,cur;
    int end_pt;
    char stpt,endpt;

public:
    djikstra(int no)
    {
        int choice;
        no_vertices=no;
        input_info();
        cout<<"\nGraph Information:"<<endl;
        print();
        do{
        cout<<"\nStarting Point: ";cin>>stpt;st_pt=stpt-65;
        rty:{
        cout<<"\nEnd Point: ";
        cin>>endpt;end_pt=endpt-65;}
        if(end_pt>=no_vertices)
        {
            cout<<"\nWrong Entry";
            goto rty;
        }
        shortestPath();
        cout<<"\nAgain(0->Yes)"<<endl;cin>>choice;
        }while(choice==0);
        /*stpt=st_pt-65;endpt=end_pt-65;
        cout<<stpt<<" "<<endpt;*/
    }
    void input_info()
    {
        int ch;
        cout<<"\n1.Data in graph\n2.Data in list form:\t";
        cin>>ch;
         cout<<"\nEnter the Distances btw various vertices: "<<endl;
        if(ch==1){
        char st='A';
        for(int i=0;i<no_vertices;i++)
        {
            char lt='A';
            for(int j=0;j<no_vertices;j++)
            {
                if(i==j)
                {
                    graph[i][j]=INT_MAX-100;
                }
                else if(i<j){
                        cout<<"Between "<<st<<" and "<<lt<<": ";
                    cin>>graph[i][j];
                    if(graph[i][j]==0)
                        graph[i][j]=INT_MAX-100;
                }
                else
                {
                    graph[i][j]=graph[j][i];
                }
                lt++;
            }st++;
        }}
        else{
        for(int i=0;i<no_vertices;i++)
        {
            for(int j=0;j<no_vertices;j++)
            {
                cin>>graph[i][j];
                if(graph[i][j]==0)
                    graph[i][j]=INT_MAX-100;
            }
        }}
    }
    void print()
    {
        char st='A';
        for(int i=0;i<no_vertices;i++)
        {
            char lt='A';
            if(i==0){
                    cout<<"\t";
            for(int k=0;k<no_vertices;k++)
                {
                    cout<<lt++<<"\t";
                }
                cout<<endl;}
            for(int j=0;j<no_vertices;j++)
            {
                if(j==0)
                {
                    cout<<st++<<"\t";
                }
                if(graph[i][j]!=INT_MAX-100)
                cout<<graph[i][j]<<"\t";
                else
                    cout<<"%\t";
            }
            cout<<endl;
        }
    }
    void shortestPath()
    {
        int stptq=st_pt;cur=0;
        for(int i=0;i<no_vertices;i++)
        {
            com[0][i].val=INT_MAX-100;
        }
        com[0][st_pt].val=0;

        do{
                cur++;
                for(int j=0;j<no_vertices;j++)
                {
                    com[cur][j].val=minimum(com[cur-1][j].val,com[cur-1][stptq].val+graph[stptq][j]);
                    if(com[cur][j].val!=com[cur-1][j].val)
                    {
                        for(int i=0;i<N;i++)
                            com[i][j].flag=0;
                    }
                }
                inc_flag(stptq);
                println(cur);
                stptq=minimum_index(cur);
                //cout<<stptq<<endl;

        }while(checkFlag());
        println(cur);
        result(cur);
    }
    void println(int k)
    {
        for(int i=0;i<no_vertices;i++)
        {
            if(com[k][i].val!=INT_MAX-100)
                cout<<com[k][i].val<<"\t";
            else
                cout<<"%\t";
        }
        cout<<endl;
    }
    int minimum(int a,int b)
    {
        return(a>b?b:a);
    }
    int minimum_index(int k)
    {

        int minval,min_index=-1;
        minval=10000;
        for(int i=0;i<no_vertices;i++)
        {
            if(com[k][i].val<minval&&com[k][i].flag==0)
            {
                minval=com[k][i].val;
                min_index=i;
            }
        }
        return min_index;
    }
    void inc_flag(int k)
    {
        for(int i=0;i<N;i++)
        {
            com[i][k].flag=1;
        }
    }
    bool checkFlag()
    {
        for(int i=0;i<no_vertices;i++)
        {
            if(com[0][i].flag==0)
                return true;
        }
        return false;
    }
    void result(int k)
    {
        cout<<"\nDistance between "<<stpt<<" and "<<endpt<<" : "<<com[k][end_pt].val<<endl;
        cout<<"\nPath :"<<endl;
        /*int arr[N];
        for(int i=0;i<no_vertices;i++)
        {
            arr[i]=com[cur][i].val;
        }

        for(int i=0;i<no_vertices;i++)
            cout<<arr[i]<<" ";*/
            g tmp[N];
            for(int i=0;i<no_vertices;i++)
            {
                tmp[i].val=com[cur][i].val;
                tmp[i].flag=i;
            }
            int j;
    int flg=0;
    for(int i=0;i<no_vertices-1;i++)
    {
        flg=0;
        j=0;
        while(j<no_vertices-i-1)
        {
            if(tmp[j].val>tmp[j+1].val)
            {
                {
                    g temp;
                    temp=tmp[j];tmp[j]=tmp[j+1];
                    tmp[j+1]=temp;
                }

                flg=1;

            }
            j++;
        }
        if(flg==0)
            break;
    }
    /*for(int i=0;i<no_vertices;i++)
            cout<<tmp[i].val<<" ";*/
        cout<<endl;
    path(tmp);
    }
    void path(g path[])
    {
        int temp,v=0;
        for(int i=0;i<no_vertices;i++)
        {
            if(end_pt==path[i].flag){
                    temp=i;
                break;
            }
        }
        dis[v]=end_pt;
        for(int i=temp;path[i].flag!=st_pt;i--)
        {
            if(graph[path[temp].flag][path[i-1].flag]==path[temp].val-path[i-1].val){
                    v++;
                    temp=i-1;
                dis[v]=path[i-1].flag;
            }
        }
        for(int i=v;i>=0;i--)
            cout<<char(dis[i]+65)<<"\t";

        cout<<endl;
    }

};

int main()
{
    int cha;
    do{
    int no;
    cout<<"Enter no. of Vertices: ";
    cin>>no;

    djikstra graph(no);

    cout<<"\nAgain (0->Yes): ";
    cin>>cha;
}while(cha==0);
}
