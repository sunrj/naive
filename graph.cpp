#include"graph.h"

void stringTOnum(string s, vector<int> &out)//把从属性文件中读取的属性数据存到节点的属性vector中
{
	bool temp = false;//读取一个数据标志位
	int data = 0;//分离的一个数据
	for (int i = 0; i < s.length(); i++)
	{
		while ((s[i] >= '0') && (s[i] <= '9'))//当前字符是数据，并一直读后面的数据，只要遇到不是数字为止
		{
			temp = true;//读数据标志位置位
			data *= 10;
			data += (s[i] - '0');//字符在系统以ASCII码存储，要得到其实际值必须减去‘0’的ASCII值
			i++;
		}
		//刚读取了数据
		if (temp)//判断是否完全读取一个数据
		{
			vector<int>::iterator te;
			te = find(out.begin(), out.end(), data);
			if (te == out.end())
				out.push_back(data);
			data = 0;
			temp = false;//标志位复位
		}
	}
}

void quickSort(vector<int> &R, int low, int high)//给vector<int> 按照递增的顺序排序
{
	if (low < high) {
		int i = low, j = high, temp = R[low];

		while (i < j) {
			while (i < j && R[j] >= temp) {
				--j;
			}
			if (i < j) {
				R[i++] = R[j];
			}
			while (i < j && R[i] <= temp) {
				++i;
			}
			if (i < j) {
				R[j--] = R[i];
			}
		}
		R[i] = temp;
		quickSort(R, low, i - 1);
		quickSort(R, i + 1, high);
	}
}

void Graph::dataInput(string edge_file, string attribute_file, string union_file, string intersec_file)
{
	int n = 0, m = 0;//n存放节点的个数，m存放边的个数
	string s = {};
	ifstream infile1, infile2, infile3, infile4;
	infile1.open(edge_file);
	infile2.open(attribute_file);
	infile3.open(union_file);
	infile4.open(intersec_file);
	infile1 >> n >> m;
	for (int i = 0; i < n; i++)//创建节点并初始化节点的各个属性
	{
		vector<int> id;
		vector<float> w;
		vector<vector<int>> se;
		vector<vector<float>> we;
		id.push_back(i);//先把节点创建出来，把节点的id存到vector<vector<int>>行首
		vertex.push_back(id);//先把节点创建出来
		attributeUnionInt.push_back(id);
		se.push_back(id);
		attributeIntersecSet.push_back(se);
		w.push_back(i);
		we.push_back(w);
		edgeWeightOnEachAtt.push_back(we);
		tempEdgeWeight.push_back(w);
		edgeWeightOnA0.push_back(w);
		exist.push_back(1);//初始化第i个节点的exist属性为1
		weight.push_back(0.0);//初始化第i个节点的weight属性为0.0
		upWeight.push_back(0.0);//初始化第i个节点的upWeight属性为0.0

		//srand(time(0));

		/**************************
		下面的代码是在创建节点时随机生成节点的属性
		*************************/
		/*int r1 = 20, r2 = 20;//这个r1是想要随机为节点生成的属性个数的最大值，这个r2是想要随机生成的属性的种类

		int z = (double)rand() / (RAND_MAX + 1) * r1;//这个20是想要随机为节点生成的属性个数的最大值

		for (int k = 0; k <= z; k++)
		{
			int u = (double)rand() / (RAND_MAX + 1) * r2; // RAND_MAX = 32767
			vex.attribute.insert(u);
		}*/


		/**************************
		下面的代码是从infile2中读取每个节点的属性
		*************************/
		vector<int> att;
		getline(infile2, s);
		stringTOnum(s, att);//获取节点i的属性
		sort(att.begin(), att.end());//把节点的属性按照从小到大排列
		//quickSort(att, 0, att.size() - 1);
		attribute.push_back(att);//把节点i的属性存进去
	}
	infile2.close();
	int id1, id2, unionInt;
	for (int j = 0; j < m; j++)//遍历所有的边，存入各个节点的邻居节点
	{
		infile1 >> id1 >> id2;
		infile3 >> unionInt;

		//unordered_set<int> in = {};
		vector<int> in = {};
		getline(infile4, s);
		stringTOnum(s, in);

		vertex[id1].push_back(id2);
		tempEdgeWeight[id1].push_back(0.0);
		edgeWeightOnA0[id1].push_back(0.0);
		attributeUnionInt[id1].push_back(unionInt);
		attributeIntersecSet[id1].push_back(in);

		/*vector<int>::iterator te1, te2;

		te1 = find(vertex[id1].begin(), vertex[id1].end(), id2);
		if (te1 == vertex[id1].end())
			vertex[id1].push_back(id2);

		te2 = find(vertex[id2].begin(), vertex[id2].end(), id1);
		if (te2 == vertex[id2].end())
			vertex[id2].push_back(id1);*/
	}
	//vector<vector<int>>::iterator vex = vertex.begin();
	//for (; vex != vertex.end(); vex++)
	//{
	//	sort(vex->begin() + 1, vex->end());//把节点的邻居按照从小到大排序
	//	//quickSort(*vex, 1, vex->size() - 1);
	//}
	infile1.close();
	infile3.close();
	infile4.close();
}

void Graph::getIntersection(vector<int> &A, vector<int> B, vector<int> &result)
{
	int i = 0, j = 0;
	while (i < A.size() && j < B.size())
	{
		if (A[i] > B[j])
			j++;
		else if (A[i] < B[j])
			i++;
		else
		{
			result.push_back(A[i]);
			i++;
			j++;
		}
	}
}

void Graph::getUnion(vector<int> &A, vector<int> &B, vector<int> &result)
{
	int i = 0, j = 0;
	while (i < A.size() && j < B.size())
	{
		if (A[i] > B[j])
		{
			result.push_back(B[j]);
			j++;
		}
		else if (A[i] < B[j])
		{
			result.push_back(A[i]);
			i++;
		}
		else
		{
			result.push_back(A[i]);
			i++;
			j++;
		}
	}
	while (i < A.size())
	{
		result.push_back(A[i]);
		i++;
	}
	while (j < B.size())
	{
		result.push_back(B[j]);
		j++;
	}
}

void Graph::getDifference(vector<int> &A, vector<int> &B, vector<int> &result)
{
	int i = 0, j = 0;
	while (i < A.size() && j < B.size())
	{
		if (A[i] > B[j])
			j++;
		else if (A[i] < B[j])
		{
			result.push_back(A[i]);
			i++;
		}
		else
		{
			i++;
			j++;
		}
	}
	while (i < A.size())
	{
		result.push_back(A[i]);
		i++;
	}
}

float Graph::computeEdgeWeight(int id1, int count, int attributeId)
{
	float result = 0.0;
	vector<int> temp = {}, molecule = {};
	/*getIntersection(attribute[id1], attribute[id2], temp);
	getIntersection(temp, A, molecule);
	getUnion(attribute[id1], attribute[id2], denominator);*/
	temp = attributeIntersecSet[id1][count];
	getIntersection(temp, { attributeId }, molecule);
	result = float(molecule.size()) / float(attributeUnionInt[id1][count]);
	return result;//保留小数点后三位
}

float Graph::computeVertexWeight(int id, int attributeId)
{
	int count = 0;
	float result = 0.0;
	vector<int>::iterator nei;
	for (nei = vertex[id].begin() + 1; nei != vertex[id].end(); nei++)
	{
		count++;
		//float temp = computeEdgeWeight(id, count, A);
		float temp = edgeWeightOnA0[id][count] + edgeWeightOnEachAtt[id][count][attributeId];
		tempEdgeWeight[id][count] = temp;
		result = result + temp;
	}
	return result;
}

void Graph::getedgeWeightOnEachAtt()
{
	for (int i = 0; i < edgeWeightOnEachAtt.size(); i++)
	{
		double algStartTime2 = (double)clock() / CLOCKS_PER_SEC;
		int count = 0;
		vector<int>::iterator nei;
		for (nei = vertex[i].begin() + 1; nei != vertex[i].end(); nei++)
		{
			count++;
			vector<float> edgeWeight = {};
			for (int j = 0; j < allAttribute.size(); j++)
			{
				float weight = 0.0;
				weight = Graph::computeEdgeWeight(i, count, j);
				edgeWeight.push_back(weight);
			}
			edgeWeightOnEachAtt[i].push_back(edgeWeight);
		}
		double runtime2 = (double)clock() / CLOCKS_PER_SEC - algStartTime2;
		cout << i << "  runtime = " << runtime2 << endl;
	}
}

int Graph::computeWcoreSize(float w, int attributeId, vector<int> &reexist)
{
	int result = 0;
	queue<int> delVertexId = {};//用队列存储所有不满足条件的节点的id
	for (int i = 0; i < weight.size(); i++)
	{
		weight[i] = computeVertexWeight(i, attributeId);
		if (weight[i] < w)
		{
			exist[i] = 0;
			delVertexId.push(i);
		}
	}
	int delId;
	while (!delVertexId.empty())
	{
		int count = 0;
		delId = delVertexId.front();
		delVertexId.pop();
		vector<int>::iterator nei;
		for (nei = vertex[delId].begin() + 1; nei != vertex[delId].end(); nei++)
		{
			count++;
			if (exist[*nei])
			{
				//weight[*nei] = weight[*nei] - computeEdgeWeight(delId, *nei, A);
				weight[*nei] = weight[*nei] - tempEdgeWeight[delId][count];
				if (weight[*nei] < w)
				{
					exist[*nei] = 0;
					delVertexId.push(*nei);
				}
			}
		}
	}

	for (int i = 0; i < exist.size(); i++)//计算剩下的依然存在的节点的个数就是满足attribute weighted core条件的节点集的size
	{
		if (exist[i])
		{
			result++;
			//cout << i << " ";
		}
		else
			reexist.push_back(i);
		//if (exist[i])
		//{
		//	result++;
		//	//cout << i << " ";
		//}
	}
	return result;
}

void Graph::existReset(vector<int> &reexist)
{
	for (int i = 0; i < reexist.size(); i++)
	{
		exist[reexist[i]] = 1;
	}
}

vector<int> Graph::greedy(float w, int b)
{
	vector<int> A = {};//A是最后要输出的最优的属性集
	Graph::getedgeWeightOnEachAtt();
	for (int i = 0; i < b; i++)
	{
		vector<int> diff = {};
		int x = 0, count = 0;//x存放当前最好的属性，count存放当前最好的属性集所生成的attribute wrighted core的size
		//getDifference(allAttribute, A, diff);//diff存放candidate属性
		vector<int>::iterator xi;
		for (xi = allAttribute.begin(); xi != allAttribute.end(); xi++)
		{
			if (*xi == -1)
				continue;
			double algStartTime = (double)clock() / CLOCKS_PER_SEC;
			vector<int> reexist = {};
			int c = computeWcoreSize(w, *xi, reexist);
			existReset(reexist);//判断这个属性是否是当前最优时先重置节点的exist属性，防止受到上一次判断的影响
			//cout << endl;
			double runtime = (double)clock() / CLOCKS_PER_SEC - algStartTime;
			cout << "i = " << i << "  xi = " << *xi << "  size = " << c << "  runtime = " << runtime << endl;
			if (c > count)
			{
				count = c;
				x = *xi;
			}
		}

		for (int k = 0; k < vertex.size(); k++)
		{
			int count = 0;
			vector<int>::iterator nei;
			for (nei = vertex[k].begin() + 1; nei != vertex[k].end(); nei++)
			{
				count++;
				edgeWeightOnA0[k][count] = edgeWeightOnA0[k][count] + edgeWeightOnEachAtt[k][count][x];
			}
		}

		cout << "nowbest: " << x << endl;
		vector<int> x2 = { x }, temp = {};
		getUnion(A, x2, temp);
		A = temp;
		allAttribute[x] = -1;
	}
	return A;
}