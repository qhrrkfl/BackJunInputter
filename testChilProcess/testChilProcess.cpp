// testChilProcess.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
struct Score {
	int A;
	int B;
	int dif;
};

bool customSorting(Score const& rhs, Score const& lhs)
{
	if (rhs.dif != lhs.dif)
	{
		return rhs.dif > lhs.dif;
	}
	else {
		return  rhs.A > lhs.A;
	}

}


int main()
{

	int testCase = 0;
	cin >> testCase;

	for (int i = 0; i < testCase; i++)
	{
		int inputCnt = 0;
		cin >> inputCnt;
		vector<Score> vScore;

		for (int j = 0; j < inputCnt; j++)
		{
			Score score;
			cin >> score.A >> score.B;
			if (score.A > score.B)
			{
				score.dif = score.A - score.B;
			}
			else
			{
				score.dif = score.B - score.A;
			}
			vScore.push_back(score);

		}

		sort(vScore.begin(), vScore.end(), customSorting);

		for (auto &ele : vScore)
		{
			cout << "A : " << ele.A << " B: " << ele.B << " DIF : " << ele.dif << endl;
		}


	}

	return 1;

}


