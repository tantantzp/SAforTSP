#ifndef TSP_IMPLEMENTATION_H
#define TSP_IMPLEMENTATION_H

#include "iostream"
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>
#include "TSP.h"
#include <fstream>

using namespace std;


//////////////Node_map//////////////////////

Node_map::Node_map(int n):N(n)
	{
		node = new Node[N];
		length_table = new double*[N];
		for(int i=0; i<N; i++)
		{
		    length_table[i] = new double[N];
		}
	}
Node_map::~Node_map()
	{
	    delete []node;
		for(int i=0; i<N; i++)
		{
		    delete [] length_table[i];
		}
		delete length_table;
	}

void Node_map::init()         //读入数据
{
    for(int i=0; i<N; i++)
	{
	    char temp;
		double tempx, tempy;
		fin>>temp>>tempx>>tempy;
		node[i].set(tempx, tempy, temp);
	}
	cacu_distance();
}

void Node_map::cacu_distance()  //计算距离矩阵
{
    for(int i = 0; i< N; i++)
	{
		length_table[i][i] = (double)INT_MAX;
	    for(int j = i+1; j < N; j++)
		{
			length_table[i][j] = length_table[j][i] = sqrt(
				(node[i].x - node[j].x) * (node[i].x - node[j].x) +
				(node[i].y - node[j].y) * (node[i].y - node[j].y) );
		}
	}
}


/////////Path//////////////////

Path::Path(int n, Node_map* nm)
	{
		N = n;
		node_map = nm;
	    route = new int[N];
		for(int i = 0; i < N; i++)
		{
		    route[i] = i;
		}
		length = (double)INT_MAX;
	}

void Path::randon_route()
{
	random_shuffle(route,route + N);
	cacu_length();
}

void Path::cacu_length()     //计算路径长度
{
	int j = 0;
	length = 0;
	for(j = 1; j < N; j++)
	{
	    length += node_map->length_table[route[j -1]][route[j]];
	}
	length += node_map->length_table[route[N-1]][route[0]];
}

void Path::change()         //产生新的路径,采用了三种方式, 随机选择一种
{
    int i = rand() % N;
	int j = rand() % N;
	if(i > j)
	{
	    int t = i;
		i = j;
		j = t;
	}
	else if(i == j)
	{
	    return;
	}

	int choose = rand() % 3;

	if(choose == 0)
	{
	    int t = route[i];
		route[i] = route[j];
		route[j] = t;
	}
	else if(choose == 1)
	{
	    reverse(route + i, route + j);
	}
	else
	{
	    if(j = N - 1)    return;
		rotate(route + i, route + j, route + j + 1);
	}

	cacu_length();
}
bool Path::operator < ( Path& p )
{
	return length < p.length;
}
void Path::operator =( Path& p)
{
	for(int i=0;i < N; i++)
	{
		route[i] = p.route[i];
	}
    length = p.length;
}

void Path::output()
{
    for(int i=0; i<N ;i++)
	{
	    fout<<node_map->node[route[i]].name<<' ';
	}
	fout<<length<<endl;
}


//////////TSP/////////////////

void TSP::tsp()            //模拟退火
{
    int i = 0;
	double t = initial_temp;             
	double t_min = 0.001;

	temp_path->output();
	best_path->output();
	while( t > t_min )
	{
	    for(i = 0; i < L; i++)
		{
		    temp_path->change();
			if(temp_path->length < best_path->length)     //接收更优解
			{
				(*best_path) = (*temp_path);
			}
			else                     //一定概率接收差解
			{
				if((int)(exp((best_path->length - temp_path->length) / t) * 100) > (rand() %101))
				{
					(*best_path) = (*temp_path);
				}
				else
				{
				    (*temp_path) = (*best_path)  ;
				}
			}
		}
        t *= speed;                //温度下降
        best_path->output();
	}
	return;
}

#endif