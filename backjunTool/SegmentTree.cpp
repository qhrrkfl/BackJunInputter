#include "SegmentTree.h"

int SegmentTree::buildRec(const int arr[], int node, int nodeLeft, int nodeRight)
{
	if (nodeLeft == nodeRight)
	{
		return data[node] = arr[nodeLeft];
	}

	int mid = nodeLeft + (nodeRight - nodeLeft) / 2;
	int leftVal = buildRec(arr, node * 2, nodeLeft, mid);
	int rightVal = buildRec(arr, node * 2 + 1, mid +1, nodeRight);
							// sum에관한 머지일뿐 이부분을 변수화 시켜서 변경 가능토록 해야함.
	return data[node] = this->merge(leftVal, rightVal);
}


int SegmentTree::merge(int left, int right)
{
	return left + right;
}

SegmentTree::SegmentTree(int arr[], int len)
{
	// 2*N < arrsize < 4*N 로 정해짐.
	arrLen = len * 4;
	data = new int[arrLen];
	baseArrNum = len;
	for (int i = 0; i < arrLen; i++)
	{
		data[i] = 0;
	}
	buildRec(arr, 1, 0, len - 1);
}



SegmentTree::~SegmentTree()
{
	// let the father do the job
}

int SegmentTree::query(int left, int right)
{
	return QueryRec(left, right, 1, 0, baseArrNum - 1);
}

int SegmentTree::update(int index, int newValue)
{
	return updateRec(index, newValue, 1, 0, baseArrNum - 1);
}

int SegmentTree::QueryRec(int left, int right, int node, int nodeLeft, int nodeRight)
{
	if (right < nodeLeft || nodeRight < left)
	{
		// sum에 관한 default value일 뿐. // 이부분은 왁꾸화 시켜서 변경 가능토록 개선해야함
		return 0;
	}

	if (left <= nodeLeft && nodeRight <= right)
	{
		return data[node];
	}

	int mid = nodeLeft + (nodeRight - nodeLeft) / 2;
	return merge(QueryRec(left, right, node * 2, nodeLeft, mid) 
		, QueryRec(left, right, node * 2 +1, mid + 1, nodeRight));
}

int SegmentTree::updateRec(int index, int newValue, int node, int nodeLeft, int nodeRight)
{
	if (index < nodeLeft || nodeRight < index)
	{
		return data[node];
	}

	if (nodeLeft == nodeRight)
	{
		return data[node] = newValue;
	}

	int mid = nodeLeft + (nodeRight - nodeLeft) / 2;
	int leftVal = updateRec(index, newValue, node * 2, nodeLeft, mid);
	int rightVal = updateRec(index, newValue, node * 2 + 1, mid + 1, nodeRight);
	return data[node] = merge(leftVal, rightVal);
}
