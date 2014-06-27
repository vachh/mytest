#include "StdAfx.h"
#include "AStarFindPath.h"
#include <iostream>  
#include <cstdio>  
#include <cmath>  
#include <string>  
#include <queue>//Ϊ��ʹ�����ȼ�����priority_queue  
#include <stack>  
#include <vector> 
using namespace std;  

const int MaxDistance=9999;

AStarFindPath::AStarFindPath():m_steps(0)
{
	//	0 1 2		����
	// 3    4
	// 5 6 7
	dx[0] =dx[3] = dx[5] = -1;  
	dx[1] =dx[6] = 0;  
	dx[2] =dx[4] = dx[7] = 1;  

	dy[0] = dy[1] = dy[2] = -1;  
	dy[3] =dy[4] = 0;  
	dy[5] =dy[6] = dy[7] = 1;  

	int	m[M_ROWS][M_COLS]={{0,0,0,0,0,0,0,0},
														{0,0,0,0,1,0,0,0},
														{0,0,0,0,1,0,0,0},
														{0,0,0,0,1,0,0,0},
														{0,0,0,0,0,0,0,0},
														{0,0,0,0,0,0,0,0}};
	m_msg = new int *[M_ROWS];  
	for (int i = 0;i < M_ROWS;++i)  
	{  
		m_msg[i] = new int[M_COLS];  
		for (int j=0;j<M_COLS;++j)
		{
			m_msg[i][j]=m[i][j];
		}
	}
	 cout<<m_msg[1][4]<<endl;
	endNode = new Node;  
	endNode->x = 6;  
	endNode->y = 2;  
	endNode->father = NULL;  

	startNode = new Node;  
	startNode->x = 2;  
	startNode->y = 2;  
	startNode->g = 0;  
	startNode->h = getVal_H(startNode->x,startNode->y);  
	startNode->f = startNode->g + startNode->h;  
	startNode->father = NULL;  

	
	
}
AStarFindPath::~AStarFindPath(void)
{
	//free(m_FileName);
	//ǧ�����������룬��ΪstartNode�Ѽ���OPEN�������ͷ�OPEN��  
	//��ʱ���ͷţ����������ظ��ͷţ�����bug  
	//delete startNode;  
	delete endNode;  

	////�ͷ��Թ��������飺ע���ά����ռ��ͷ�  
	for (int i = 0;i < M_ROWS;++i)  {  
		delete[] m_msg[i];  
		}  
		delete[] m_msg;  

	vector<Node*>::iterator iter;  
	for (iter = openTable.begin();iter != openTable.end();++iter)  {  
		delete (*iter);  
	}  
	openTable.clear();  

	vector<Node*>::iterator iter2;  
	for (iter2 = closeTable.begin();iter2 != closeTable.end();++iter2)  {  
		delete (*iter2);  
	}  
	closeTable.clear(); 
}
int AStarFindPath::getVal_H(int x,int y){
	 return (10 * (abs(endNode->x - x) + abs(endNode->y - y)));  
}
bool AStarFindPath::isPass(int x,int y)  
{  
	if (x >= 0 && x < M_ROWS &&  
		y >= 0 && y < M_COLS&& 
		m_msg[x][y] == 0)  
		return true;  
	else  
		return false;  
} 
bool AStarFindPath::findPath(){
	if (startNode->x==endNode->x&&startNode->y==endNode->y){
		cout<<"WARNNING:��The start point is the same as the end point! "<<endl;
		return true;
	}
	openTable.push_back(startNode);//��ʼ��װ��OPEN��  
	push_heap(openTable.begin(),openTable.end(),HeapCompare_f());
	

	Node* tempNode=new Node;
	
	//��ʼ����  
for (;;)  
	{  
		if (openTable.empty())//�ж�OPEN���Ƿ�Ϊ��  
		{  
			cout << "ERROR : unable to find the destination" << endl;  
			return false;  
		}  
	
	++m_steps;
	tempNode=openTable.front();
	 pop_heap(openTable.begin(),openTable.end(),HeapCompare_f());
	openTable.pop_back();
	//�ж��Ƿ��Ѿ���Ѱ��Ŀ��ڵ�  
	if (tempNode->x == endNode->x&& tempNode->y == endNode->y)  
	{  
		cout << "OK : success to find the destination" << endl;  
		endNode->g = tempNode->g;  
		endNode->h = tempNode->h;  
		endNode->f = tempNode->f;  
		endNode->father = tempNode->father;  
		
		 printPath(); 
		return true;  
	}  
	
	for (int i=0;i<8;++i)
	{
		int tempX=tempNode->x+dx[i];
		int tempY=tempNode->y+dy[i];
		if (isPass(tempX,tempY))					//�����ͨ��
		{
			int newGVal;  
			if (!dx[i] && !dy[i])							//λ�ڶԽ�����  
			{  
				newGVal = tempNode->g + 14;  
			}  
			else  
				newGVal = tempNode->g + 10;  
			//����OPEN���жϴ˵��Ƿ���OPEN����  
			vector<Node*>::iterator OPENTableResult;  
			for (OPENTableResult = openTable.begin();  
				OPENTableResult != openTable.end();++OPENTableResult)  
			{  
				if ((*OPENTableResult)->x == tempX &&  
					(*OPENTableResult)->y == tempY)  
				{  
					break;  
				}  
			}  
			//���ӽڵ��Ѿ�������OPEN����  
			if (OPENTableResult != openTable.end())  
			{  
				//OPEN���нڵ��gֵ�Ѿ������ŵģ��������˽ڵ�  
				if ((*OPENTableResult)->g <= newGVal)  
				{  
					continue;  
				}  
			}  
			//����CLOSED���жϴ˽ڵ��Ƿ��Ѿ�����������  
			vector<Node*>::iterator CLOSEDTableResult;  
			for (CLOSEDTableResult = closeTable.begin();  
				CLOSEDTableResult != closeTable.end();++CLOSEDTableResult)  
			{  
				if ((*CLOSEDTableResult)->x == tempX &&  
					(*CLOSEDTableResult)->y == tempY)  
				{  
					break;  
				}  
			}  
			//�˽ڵ��Ѿ�������CLOSED����  
			if (CLOSEDTableResult != closeTable.end())  
			{  
				//CLOSED���еĽڵ��Ѿ������ŵģ�������  
				if ((*CLOSEDTableResult)->g <= newGVal)  
				{  
					continue;  
				}  
			} 
			Node* pNode=new Node;
			pNode->x=tempX;
			pNode->y=tempY;
			pNode->g=newGVal;
			pNode->h=getVal_H(tempX,tempY);
			pNode->f=pNode->g+pNode->h;
			pNode->father=tempNode;
			
			//����Ѿ�������CLOSED���У������Ƴ�  
			if (CLOSEDTableResult != closeTable.end())  
			{  
				delete (*CLOSEDTableResult);  
				closeTable.erase(CLOSEDTableResult);  
			}  

			//����Ѿ�������OPEN������  
			if (OPENTableResult != openTable.end())  
			{  
				delete (*OPENTableResult);  
				openTable.erase(OPENTableResult);  

				//���½��ѣ�ʵ������ע�ⲻ����sort_heap����Ϊ�������Ϊ�յĻ������bug  
				make_heap(openTable.begin(),openTable.end(),HeapCompare_f());  
			}  

			openTable.push_back(pNode);//�����Žڵ����OPEN��  

			push_heap(openTable.begin(),openTable.end(),HeapCompare_f());//��������
		}
	}
		closeTable.push_back(tempNode);
}
return false;
}

void AStarFindPath::printPath(){
	Node *nodeChild = endNode;  
	Node *nodeParent = endNode->father;  
	do   
	{  
		m_msg[nodeChild->x][nodeChild->y] = 3;//���Ϊ·���ϵĵ�  
		nodeChild = nodeParent;  
		nodeParent = nodeParent->father;  
	} while (nodeChild != startNode);  
		
	 *(*(m_msg + startNode->x) + startNode->y) = 3;

	cout << "The path is " << endl;  
	for (int i = 0;i < M_ROWS;++i)  
	{  
		for (int j = 0;j < M_COLS;++j)  
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

	cout << "�����ܲ�����"  << m_steps << endl; 
}