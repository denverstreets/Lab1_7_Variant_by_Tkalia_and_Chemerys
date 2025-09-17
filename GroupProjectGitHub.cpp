#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

//оператор робочий
struct PointFinder {
	void operator()(int NumberOfPoints, int NumberOfChecks, int TargetNumber) const {

		int Sheet = NumberOfPoints * NumberOfPoints;

		vector<vector<int>> sets(NumberOfChecks, vector<int>(Sheet));

		srand(time(0));

		for (int i = 0; i < NumberOfChecks; i++)
		{
			for (int j = 0; j < Sheet; j++)
			{
				sets[i][j] = rand() % Sheet + 1;
			}
		}

		double Total = 0;
		for (int i = 0; i < NumberOfChecks; i++)
		{
			int Count;
			for (int j = 0; j < Sheet; j++)
			{
				if (sets[i][j] == TargetNumber)
				{
					Count++;
				}
			}
			Total += Count;
		}

		double Average = Total / NumberOfChecks;
		cout << "number " << TargetNumber << "encounters " << Average << "times";

	}
};

int main()
{
	PointFinder PF;

	int TargetNumber, NumberOfChecks, NumberOfPoints;

	cout << "enter number for sheet ";
	cin >> NumberOfPoints;
	cout << endl;

	cout << "enter number of checks ";
	cin >> NumberOfChecks;
	cout << endl;

	cout << "enter target number ";
	cin >> TargetNumber;
	cout << endl;

}
