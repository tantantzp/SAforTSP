#ifndef TSP_H
#define TSP_H

#include "iostream"
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <random>
#include <fstream>

using namespace std;

static ifstream fin;
static ofstream fout;

class Node         //城市节点类 
{
public:
	double x,y;
	char name;
	void set(double a, double b, char c){ x = a, y = b, name = c;}
};

class Node_map         //城市节点地图类 
{
public:
	int N;
	Node* node;
    double** length_table;        //城市距离矩阵 

	Node_map(int n);
	~Node_map();
	void init();
	void cacu_distance();          //计算距离矩阵 
};

class Path             //路径类 
{
public:
	double length;        //路径长度 
	int N;                //城市数 
	int* route;           //路径标号数组 
	Node_map* node_map;

	Path(int n, Node_map* nm);
	~Path(){ delete []route; }
	void randon_route();
	void cacu_length();        //计算路径长度 
	void change();             //产生新解 
	void output();
    bool operator < ( Path& p );
	void operator =( Path& p);
};

class TSP            //旅行商类， 模拟退火算法
{
public:
	int N;
	int initial_temp;           //初始温度
	int L;                      //每个温度下的循环次数
	double speed;               //温度下降速度 
    Node_map* node_map;
	Path* best_path;
	Path* temp_path;

	TSP(int n)
	{
	    N = n;
		initial_temp = 3000;
		speed = 0.98;
		L = 1000 * N;
		node_map = new Node_map(N);
		node_map->init();
		best_path = new Path(N, node_map);
		temp_path = new Path(N, node_map);
		temp_path->randon_route();
	}
	~TSP() 
	{
	    delete node_map;
		delete best_path;
		delete temp_path;
	}

	void tsp();
};


#include "TSP_implementation.h"

#endif