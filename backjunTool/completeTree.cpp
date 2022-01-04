#include "completeTree.h"

CompleteTree::CompleteTree()
{
}

CompleteTree::CompleteTree(int data[], int arrSize)
{
	this->data = new int[arrSize];
	memcpy(this->data, data, sizeof(int)*arrSize);
	arrLen = arrSize;
}

CompleteTree::~CompleteTree()
{
	cout << "base" << endl;
	delete[] data;
}

inline int CompleteTree::getLevel(int idx)
{

	return (int)log2(idx);
}

int CompleteTree::getMaxLevel()
{
	return getLevel(arrLen);
}

int * CompleteTree::getLChildData(int idx)
{
	//lchild = 2me + 1
		//rchild = lchid + 1
		//parent = (me - 1) / 2
	int lChildIdx = 2 * idx + 1;
	if (arrLen > lChildIdx) {
		return &(data[lChildIdx]);
	}
	else
	{
		return nullptr;
	}
}

int CompleteTree::getLChildIdx(int idx)
{
	int lChildIdx = 2 * idx + 1;
	if (arrLen > lChildIdx)
	{
		return lChildIdx;

	}
	else
	{
		return -1;
	}
}

int CompleteTree::getRChildIdx(int idx)
{
	int RChildIdx = 2 * idx + 2;
	if (arrLen > RChildIdx)
	{
		return RChildIdx;

	}
	else
	{
		return -1;
	}
}

int * CompleteTree::getRChildData(int idx)
{
	int lChildIdx = 2 * idx + 2;
	if (arrLen > lChildIdx) {
		return &(data[lChildIdx]);
	}
	else
	{
		return nullptr;
	}
}

int * CompleteTree::getParent(int idx)
{
	int parentIdx = (idx - 1) / 2;
	if (parentIdx > 0)
	{
		return &data[parentIdx];
	}
	else
	{
		return nullptr;
	}
}

int CompleteTree::getrootData()
{
	return data[0];
}
