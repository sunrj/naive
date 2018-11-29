#ifndef GRAPH
#define GRAPH
#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<algorithm>
#include<queue>
#include<iterator>
#include<ctime>
#include<fstream>

using namespace std;

class Graph
{
public:
	vector<vector<int>> vertex;//存储节点以及节点的邻居
	vector<vector<int>> attribute;//存储节点以及节点的属性
	vector<vector<int>> attributeUnionInt;//存储各个边的端点的属性集的并集的大小，与vector<vector<int>> vertex 的结构完全对应
	vector<vector<vector<int>>> attributeIntersecSet;//存储各个边的端点的属性集的交集的set，与vector<vector<int>> vertex 的结构基本对应
	vector<vector<vector<float>>> edgeWeightOnEachAtt;
	vector<vector<float>> tempEdgeWeight;//存储计算的当前属性集下的各边的权重，与vector<vector<int>> vertex 的结构完全对应
	vector<vector<float>> edgeWeightOnA0;//各个边在当前最好的属性集下的权重，与vector<vector<int>> vertex 的结构完全对应
	vector<int> exist;//size为节点个数n，表示节点是否存在与当前属性的判断中。1表示存在，0表示不存在，默认是1
	vector<float> weight;//size为节点个数n，存储节点的权重，默认为0.0
	vector<float> upWeight;//size为节点个数n，存储节点的权重上线，默认为0.0
	vector<int> allAttribute;//存储当前图的所有属性
	void getedgeWeightOnEachAtt();
	void dataInput(string edge_file, string attribute_file, string union_file, string intersec_file);//数据输入，file1是节点以及边的数据文件，file2是各个节点的属性文件
	void getIntersection(vector<int> &A, vector<int> B, vector<int> &result);//获得A与B的交集
	void getUnion(vector<int> &A, vector<int> &B, vector<int> &result);//获得A与B的并集
	void getDifference(vector<int> &A, vector<int> &B, vector<int> &result);//获得A\B，差集
	float computeEdgeWeight(int id1, int id2, int attributeId);//计算两个节点之间的边在给定的属性集下的权重
	float computeVertexWeight(int id, int attributeId);//计算节点在给定的属性集下的权重
	void existReset(vector<int> &reexist);//把非mustDelete的节点的exist属性重置为true，因需要判断不同的属性集的情况下的结果，所有每次判断时不能遗留上一次的结果
	int computeWcoreSize(float w, int attributeId, vector<int> &reexist);//返回满足attribute weighted core条件的节点集的size
	vector<int> greedy(float w, int b);//使用Greedy算法来计算最后的最优的b个属性，返回这个属性集
};

#endif // !GRAPH
