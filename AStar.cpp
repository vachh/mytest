// AStar.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
using namespace std;
class Test{
public:
	int x;
	Test(){
		x=1;
	};
	~Test();
};

int _tmain(int argc, _TCHAR* argv[])
{
	AStarFindPath astar;
	astar.findPath();
	return 0;
}

