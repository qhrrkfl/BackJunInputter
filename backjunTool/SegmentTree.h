#pragma once
#include "completeTree.h"
//기본적인 형태이며 advance 형태는
//생성은 bottom top
// 업데이트는 lazy propagation 
class SegmentTree : public CompleteTree
{
	int buildRec(const int arr[], int node, int nodeleft, int nodeRight);
	int merge(int left, int right);
	int QueryRec(int left, int right, int node, int nodeLeft, int nodeRight);
	int updateRec(int index, int newValue, int node, int nodeLeft, int nodeRight);
public:
	SegmentTree(int arr[], int len);
	~SegmentTree();
	int query(int left, int right);
	int update(int index, int newValue);
	
	
};

