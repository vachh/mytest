// AStar.cpp : 定义控制台应用程序的入口点。
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

