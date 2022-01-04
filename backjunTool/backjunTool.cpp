
#include <iostream>
#include "SegmentTree.h"
int main()
{
	int arr[] = { 1,3,5 };
	SegmentTree sg = SegmentTree(arr, 3);
	cout << sg.query(0, 2) << endl;
	cout << sg.query(1, 2) << endl;

	return 0;
}
