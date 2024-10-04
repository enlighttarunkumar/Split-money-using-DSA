#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

map<string, double> parm;

void findPath(map<string, double>& details);
string getKeyFromValue(map<string, double>& hm, double value);
double round(double value, int places);
//map<string, vector<int>>g; // Matrix
int main() {
    parm["ALICE"] = -5.0;
    parm["BOB"] = 25.0;
    parm["CATY"] = -20.0;
    parm["DON"] = 25.0;
    parm["ELE"] = -20.0;
    parm["FRED"] = -5.0;

    findPath(parm);
    return 0;
}

void findPath(map<string, double>& details) {
    double maxValue = max_element(details.begin(), details.end(),
                                  [](const pair<string, double>& a, const pair<string, double>& b) {
                                      return a.second < b.second;
                                  })->second;

    double minValue = min_element(details.begin(), details.end(),
                                  [](const pair<string, double>& a, const pair<string, double>& b) {
                                      return a.second < b.second;
                                  })->second;

    if (maxValue != minValue) {
        string maxKey = getKeyFromValue(details, maxValue);
        string minKey = getKeyFromValue(details, minValue);
        double result = round(maxValue + minValue, 1);

        if (result >= 0.0) {
            cout << minKey << " needs to pay " << maxKey << ": " << round(abs(minValue), 2) << endl;
            details.erase(maxKey);
            details.erase(minKey);
            details[maxKey] = result;
            details[minKey] = 0.0;
        } else {
            cout << minKey << " needs to pay " << maxKey << ": " << round(abs(maxValue), 2) << endl;
            details.erase(maxKey);
            details.erase(minKey);
            details[maxKey] = 0.0;
            details[minKey] = result;
        }

        findPath(details);
    }
}

string getKeyFromValue(map<string, double>& hm, double value) {
    for (const auto& entry : hm) {
        if (entry.second == value) {
            return entry.first;
        }
    }
    return "";
}

double round(double value, int places) {
    if (places < 0) {
        throw invalid_argument("Invalid decimal places");
    }

    double factor = pow(10, places);
    return round(value * factor) / factor;
}
