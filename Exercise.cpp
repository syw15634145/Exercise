#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[])
{
    // 检查命令行参数是否正确
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " input.csv output.csv" << endl;
        return 1;
    }

    // 打开输入文件
    ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        cout << "Error: Failed to open input file " << argv[1] << endl;
        return 1;
    }

    // 打开输出文件
    ofstream outputFile(argv[2]);
    if (!outputFile.is_open()) {
        cout << "Error: Failed to open output file " << argv[2] << endl;
        return 1;
    }
    map<string,vector<int> > symbolsdata;
    int maxgap = 0;
    // 读取输入文件中的数据
    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string field;
        vector<string> fields;

        // 将每一行数据分解为多个字段
        while (getline(ss, field, ',')) {
            fields.push_back(field);
            
        }
        // last timestamp, total volume traded, total price*share, max trade price, max timestamp gap
        if (symbolsdata.find(fields[1]) == symbolsdata.end()) {
            symbolsdata[fields[1]] = {stoi(fields[0]),stoi(fields[2]),stoi(fields[2])*stoi(fields[3]),stoi(fields[3]),0};
        } else {
            symbolsdata[fields[1]][4] = max(stoi(fields[0])-symbolsdata[fields[1]][0],symbolsdata[fields[1]][4]);
            symbolsdata[fields[1]][0] = stoi(fields[0]);
            symbolsdata[fields[1]][1] += stoi(fields[2]);
            symbolsdata[fields[1]][2] += stoi(fields[2])*stoi(fields[3]);
            symbolsdata[fields[1]][3] = max(symbolsdata[fields[1]][3],stoi(fields[3]));
        }
    }
    for (auto p:symbolsdata) {
        outputFile << p.first;
        outputFile << ",";
        outputFile << to_string(p.second[4]);
        outputFile << ",";
        outputFile << to_string(p.second[1]);
        outputFile << ",";
        outputFile << to_string(p.second[2] / p.second[1]);
        outputFile << ",";
        outputFile << to_string(p.second[3]);
        outputFile << endl;
    }
    inputFile.close();
    outputFile.close();
    // spent 30 minutes on this problem
    return 0;
}
