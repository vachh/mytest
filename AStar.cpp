// AStar.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include<string>
#include<list>
using namespace std;

class User  
    { 
	public:
		int Age;  
        string Name ;
        User(int age, string name)  
        {  
            Age = age;  
            Name = name;  
        }  
        
    }  ;

  bool CompareByAge(User x,User y)//�Ӵ�С������  
 {  		    
	 return y.Age-x.Age>0;
  }
int _tmain(int argc, _TCHAR* argv[])
{

	std::list<User> uList ;
		User a(14,"aa");
		User b(13,"bb");
		User c(18,"cc");
		User d(9,"dd");
			uList.push_back(a);
			uList.push_back(b);
			uList.push_back(c);
			uList.push_back(d);
		uList.sort(CompareByAge);


	AStarFindPath astar;
	astar.findPath();
	return 0;
}

