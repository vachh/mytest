#pragma once
#include <queue>//为了使用优先级队列priority_queue  
#include <stack>  
#include <vector>   
#define M_ROWS 6
#define M_COLS 8
//记录路径上的点的坐标
struct Dir 
{
	const static int leftX=-1;
	const static int leftY=0;
	const static int rightX=+1;
	const static int rightY=0;
	const static int upX=0;
	const static int upY=-1;
	const static int downX=0;
	const static int downY=+1;

	const static int left_upX=-1;
	const static int left_upY=-1;
	const static int left_downX=-1;
	const static int left_downY=+1;

	const static int right_upX=+1;
	const static int right_upY=-1;
	const static int right_down=+1;
	const static int right_downY=+1;

};
 
//定义STL优先队列的排序方式  
struct Node{
	int x,y;	//当前点在迷宫的位置坐标
	int g;	//起始点到当前点的实际代价
	int h;	//当前节点到目标节点最佳路径的估计代价
	int f;	//估计函数：f=g+h;
	struct Node *father;//指向父节点的指针
};
class HeapCompare_f{  
public:  
	bool operator()(Node* x,Node* y) const  
	{  
		return x->f > y->f;//依据估价函数进行排序：升序排列  
	}  
}; 
class AStarFindPath
{
private:
	int **m_msg;						//地图信息
	Node *startNode,*endNode;
	int m_steps;//记录路径步数
	int dx[8],dy[8];//8个子节点移动方向：上、下、左、右、左上、右上、右下、左下 
	std::vector<Node*> openTable;  
	std::vector<Node*> closeTable;  
public:
	AStarFindPath();
	~AStarFindPath(void);
	bool findPath();					//寻路主函数  

	int getVal_H(int x,int y);		//估计当前点到目标点的距离：曼哈顿距离  
	bool isPass(int x,int y);			//判断某一节点是否合法  
	void printPath();
};

