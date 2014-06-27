#pragma once
#include <queue>//Ϊ��ʹ�����ȼ�����priority_queue  
#include <stack>  
#include <vector>   
#define M_ROWS 6
#define M_COLS 8
//��¼·���ϵĵ������
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
 
//����STL���ȶ��е�����ʽ  
struct Node{
	int x,y;	//��ǰ�����Թ���λ������
	int g;	//��ʼ�㵽��ǰ���ʵ�ʴ���
	int h;	//��ǰ�ڵ㵽Ŀ��ڵ����·���Ĺ��ƴ���
	int f;	//���ƺ�����f=g+h;
	struct Node *father;//ָ�򸸽ڵ��ָ��
};
class HeapCompare_f{  
public:  
	bool operator()(Node* x,Node* y) const  
	{  
		return x->f > y->f;//���ݹ��ۺ�������������������  
	}  
}; 
class AStarFindPath
{
private:
	int **m_msg;						//��ͼ��Ϣ
	Node *startNode,*endNode;
	int m_steps;//��¼·������
	int dx[8],dy[8];//8���ӽڵ��ƶ������ϡ��¡����ҡ����ϡ����ϡ����¡����� 
	std::vector<Node*> openTable;  
	std::vector<Node*> closeTable;  
public:
	AStarFindPath();
	~AStarFindPath(void);
	bool findPath();					//Ѱ·������  

	int getVal_H(int x,int y);		//���Ƶ�ǰ�㵽Ŀ���ľ��룺�����پ���  
	bool isPass(int x,int y);			//�ж�ĳһ�ڵ��Ƿ�Ϸ�  
	void printPath();
};

