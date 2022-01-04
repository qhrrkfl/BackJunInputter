#pragma once
#include "completeTree.h"
//�⺻���� �����̸� advance ���´�
//������ bottom top
// ������Ʈ�� lazy propagation 
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

