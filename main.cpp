#include "graph.h"

int main()
{
	Graph g;
	string file1 = "196591.txt", file2 = "196591_300_10-99.txt", file3 = "196591_300_10-99bing.txt", file4 = "196591_300_10-99jiao.txt";
	for (int i = 0; i < 300; i++) //这个数值是总的属性个数，用不同的数据集要改的
		g.allAttribute.push_back(i);
	g.dataInput(file1, file2, file3, file4);
	double algStartTime = (double)clock() / CLOCKS_PER_SEC;
	vector<int> A = {};
	A = g.greedy(0.1, 50);
	double runtime = (double)clock() / CLOCKS_PER_SEC - algStartTime;
	cout << "Runtime = " << runtime << endl;
	cout << "A.size = " << A.size() << endl;
	vector<int>::iterator o = A.begin();
	for (; o != A.end(); o++)
	{
		cout << *o << " ";
	}
	cout << endl;
	system("pause");
	//int out1 = 0;
	//vector<int> t = {}, A1 = { 3, 11 };
	//out1 = g.computeWcoreSize(0.5, A1, t);
	////out2 = g.computeWcoreSize(1, A2);
	//cout << out1<< endl;

	return 0;
}