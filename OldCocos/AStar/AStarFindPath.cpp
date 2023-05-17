#include "StdAfx.h"
#include "AStarFindPath.h"
#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include <list>
using namespace std;

const int MaxDistance = 9999;

AStarFindPath::AStarFindPath() : m_steps(0)
{
	//	0 1 2		方向
	// 3    4
	// 5 6 7
	dx[0] = dx[3] = dx[5] = -1;
	dx[1] = dx[6] = 0;
	dx[2] = dx[4] = dx[7] = 1;

	dy[0] = dy[1] = dy[2] = -1;
	dy[3] = dy[4] = 0;
	dy[5] = dy[6] = dy[7] = 1;

	int m[M_ROWS][M_COLS] = {{0, 0, 0, 0, 0, 0, 0, 0},
							 {0, 0, 0, 0, 1, 0, 0, 0},
							 {0, 0, 0, 0, 1, 0, 0, 0},
							 {0, 0, 0, 0, 1, 0, 0, 0},
							 {0, 0, 0, 0, 1, 0, 0, 0},
							 {0, 0, 0, 0, 0, 0, 0, 0}};
	m_msg = new int *[M_ROWS];
	for (int i = 0; i < M_ROWS; ++i)
	{
		m_msg[i] = new int[M_COLS];
		for (int j = 0; j < M_COLS; ++j)
		{
			m_msg[i][j] = m[i][j];
		}
	}

	cout << m_msg[2][4] << endl;
	endNode = new Node;
	endNode->x = 4;
	endNode->y = 6;
	endNode->father = NULL;

	startNode = new Node;
	startNode->x = 2;
	startNode->y = 2;
	startNode->g = 0;
	startNode->h = getVal_H(startNode->x, startNode->y);
	startNode->f = startNode->g + startNode->h;
	startNode->father = NULL;
}
bool AStarFindPath::findPath()
{
	if (startNode->x == endNode->x && startNode->y == endNode->y)
	{
		cout << "WARNNING:　The start point is the same as the end point! " << endl;
		return true;
	}
	openTable.push_back(startNode); // 起始点装入OPEN表
	Node *tempNode = new Node;

	// 开始遍历
	for (;;)
	{
		if (openTable.empty()) // 判断OPEN表是否为空
		{
			cout << "ERROR : unable to find the destination" << endl;
			return false;
		}

		++m_steps;					  // 步数加1
		tempNode = openTable.front(); // 取得f值最小的第一个值
		// pop_heap(openTable.begin(),openTable.end(),HeapCompare_f());
		closeTable.push_back(openTable.front()); // 添加到close表
		openTable.pop_front();					 // 从open表中删除
		// 判断是否已经搜寻到目标节点
		if (tempNode->x == endNode->x && tempNode->y == endNode->y)
		{
			cout << "OK : success to find the destination" << endl;
			endNode->g = tempNode->g;
			endNode->h = tempNode->h;
			endNode->f = tempNode->f;
			endNode->father = tempNode->father;

			printPath();
			return true;
		}

		for (int i = 0; i < 8; ++i)
		{
			int tempX = tempNode->x + dx[i];
			int tempY = tempNode->y + dy[i];
			// 搜索CLOSED表，判断此节点是否已经存在于其中
			list<Node *>::iterator CLOSEDTableResult;
			for (CLOSEDTableResult = closeTable.begin();
				 CLOSEDTableResult != closeTable.end(); ++CLOSEDTableResult)
			{
				if ((*CLOSEDTableResult)->x == tempX &&
					(*CLOSEDTableResult)->y == tempY)
				{
					break;
				}
			}
			// 此节点已经存在于CLOSED表中  ,跳过该节点
			if (CLOSEDTableResult != closeTable.end())
			{
				continue;
			}

			if (isPass(tempX, tempY)) // 如果能通过
			{

				///////////////////////////////////////////////////////////////////
				int newGVal;		  // 计算g值
				if (!dx[i] && !dy[i]) // 位于对角线上
				{
					newGVal = tempNode->g + 14;
				}
				else
					newGVal = tempNode->g + 10;
				////////////////////////////////////////////////////////////////////////
				// 搜索OPEN表，判断此点是否在OPEN表中
				list<Node *>::iterator OPENTableResult;
				for (OPENTableResult = openTable.begin();
					 OPENTableResult != openTable.end(); ++OPENTableResult)
				{
					if ((*OPENTableResult)->x == tempX &&
						(*OPENTableResult)->y == tempY)
					{
						break;
					}
				}
				// 此子节点已经存在于OPEN表中
				if (OPENTableResult != openTable.end())
				{
					// OPEN表中节点的g值已经是最优的，则跳过此节点
					if ((*OPENTableResult)->g <= newGVal)
					{
						continue;
					}
				}
				// 如果已经存在于OPEN表，删除该节点，从新插入新值
				if (OPENTableResult != openTable.end())
				{
					delete (*OPENTableResult);
					openTable.erase(OPENTableResult);
					//	openTable.sort();
				}
				//////////////////////////////////////////////////////

				Node *pNode = new Node;
				pNode->x = tempX;
				pNode->y = tempY;
				pNode->g = newGVal;
				pNode->h = getVal_H(tempX, tempY);
				pNode->f = pNode->g + pNode->h;
				pNode->father = tempNode;

				openTable.push_back(pNode); // 将该节点放入OPEN表
				openTable.sort(CompareByF); // 重新排序
			}
		}
		closeTable.push_back(tempNode);
	}
	return false;
}

void AStarFindPath::printPath()
{
	Node *nodeChild = endNode;
	Node *nodeParent = endNode->father;
	do
	{
		m_msg[nodeChild->x][nodeChild->y] = 3; // 标记为路径上的点
		nodeChild = nodeParent;
		nodeParent = nodeParent->father;
	} while (nodeChild != startNode);

	*(*(m_msg + startNode->x) + startNode->y) = 3;

	cout << "The path is " << endl;
	for (int i = 0; i < M_ROWS; ++i)
	{
		for (int j = 0; j < M_COLS; ++j)
		{
			if (3 == *(*(m_msg + i) + j))
			{
				cout << "# ";
			}
			else
				cout << *(*(m_msg + i) + j) << " ";
		}
		cout << endl;
	}

	cout << "搜索总步数：" << m_steps << endl;
}
int AStarFindPath::getVal_H(int x, int y)
{ // x,y距离和
	return (10 * (abs(endNode->x - x) + abs(endNode->y - y)));
}
bool AStarFindPath::isPass(int x, int y) // 如果为0表示可以通过。
{
	if (x >= 0 && x < M_ROWS &&
		y >= 0 && y < M_COLS)
	{
		if (m_msg[x][y] == 0)
			return true;
	}
	else
		return false;
}
AStarFindPath::~AStarFindPath(void)
{
	// free(m_FileName);
	// 千万不能有这句代码，因为startNode已加入OPEN表，会在释放OPEN表
	// 的时候释放，否则会造成重复释放，出现bug
	// delete startNode;
	delete endNode;

	////释放迷宫布局数组：注意多维数组空间释放
	for (int i = 0; i < M_ROWS; ++i)
	{
		delete[] m_msg[i];
	}
	delete[] m_msg;

	list<Node *>::iterator iter;
	for (iter = openTable.begin(); iter != openTable.end(); ++iter)
	{
		delete (*iter);
	}
	openTable.clear();

	list<Node *>::iterator iter2;
	for (iter2 = closeTable.begin(); iter2 != closeTable.end(); ++iter2)
	{
		delete (*iter2);
	}
	closeTable.clear();
}
