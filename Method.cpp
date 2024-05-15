#include "Method.h"

void Method::print(vector<vector<double>> data, string nameFile, double dx) {
    std::ofstream myfile;
    myfile.open(nameFile);

    for (int j = 0; j < data[0].size(); j++) {
        string line = to_string(j * dx);
        for (int i = 0; i < data.size(); i++) {
            line += "," + to_string(data[i][j]);
        }
        line += "\n";
        myfile << line;
    }
    myfile.close();
    cout << "Done !" << endl;
}