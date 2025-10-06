#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <algorithm>
#include <stdexcept>

using namespace std;

//Compiler - Microsoft Visual C++

// Functor class: generates a random cell on a square board
class RandomCell {
public:
    explicit RandomCell(int n): 
        size(n),
        gen(random_device{}()),
        dist(0, n - 1)
    {
        if (n <= 0){
            throw invalid_argument("Board size must be positive");
        }
    }

    // operator () returns a random cell (x, y)
    pair<int, int> operator()(){
        return { dist(gen), dist(gen) };
    }

private:
    int size;
    mt19937 gen;
    uniform_int_distribution<int> dist;
};

// Compute average multiplicity
double averageMultiplicity(const map<pair<int, int>, int>& freq, int total)
{
    if (freq.empty()){
        return 0.0;
    }
    return static_cast<double>(total) / freq.size();
}

// Compute median multiplicity
double medianMultiplicity(const map<pair<int, int>, int>& freq)
{
    if (freq.empty()){
        return 0.0;
    }
    vector<int> counts;
    counts.reserve(freq.size());
    for (auto it = freq.begin(); it != freq.end(); ++it){
        counts.push_back(it->second);
    }
    sort(counts.begin(), counts.end());

    size_t n = counts.size();
    if (n % 2 == 1){
        return counts[n / 2];
    }
    else{
        return (counts[n / 2 - 1] + counts[n / 2]) / 2.0;
    }
}

int main()
{
    try{
        int boardSize, numSelections;
        cout << "Enter board size N: ";
        if (!(cin >> boardSize)){
            throw runtime_error("Invalid input for N");
        }

        cout << "Enter number of selections K: ";
        if (!(cin >> numSelections)){
            throw runtime_error("Invalid input for K");
        }

        if (boardSize <= 0 || numSelections <= 0){
            throw invalid_argument("N and K must be positive");
        }

        // Create random cell generator
        RandomCell rc(boardSize);
        map<pair<int, int>, int> freq;

        // Select cells
        for (int i = 0; i < numSelections; ++i){
            auto cell = rc();
            freq[cell]++;
        }

        // Compute results
        double avg = averageMultiplicity(freq, numSelections);
        double med = medianMultiplicity(freq);

        cout << "Average multiplicity: " << avg << "\n";
        cout << "Median multiplicity: " << med << "\n";
    }
    catch (const exception& ex){
        cerr << "Error: " << ex.what() << "\n";
        return 1;
    }

    return 0;
}
