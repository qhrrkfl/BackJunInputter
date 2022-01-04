#pragma once
#include <string>
#include <iostream>
using namespace std;
class CompleteTree
{
protected:
	int arrLen;
	int* data;
	// �ڽ��� �����ڸ� �������̵� �ϵ���
	CompleteTree();
public:
	
	CompleteTree(int data[], int arrSize);


	virtual ~CompleteTree();

	inline int getLevel(int idx);
	int getMaxLevel();
	int* getLChildData(int idx);
	int getLChildIdx(int idx);
	int getRChildIdx(int idx);
	int* getRChildData(int idx);
	int* getParent(int idx);
	int getrootData();
};

