#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

struct Pers {
    string name;
    string file;
    double mark;
    string marks;
    Pers(string n, string f, double m, string mrks) {
        name = n;
        file = f;
        mark = m;
        marks = mrks;
    }
};

int main(int argc, char const *argv[]) {
    ifstream fin;
    vector<Pers> persons;

    double eps = 1e-6;

    for (int i = 1; i < argc; i++) {
        fin.open(argv[i]);
        int sum = 0;
        int count = 0;
        string name;
        int mark;
        while (fin >> name) {
            string m = "";
            fin >> mark;
            while (mark) {
                sum += mark;
                if (m.length()) {
                    m += " ";
                }
                m += to_string(mark);
                count++;
                fin >> mark;
            }
            persons.push_back(Pers(name, argv[i], double(sum) / count, m));
            sum = 0;
            count = 0;
        }
        fin.close();
    }

    ofstream fout("result.txt");
    double sum = 0;
    int count = 0;
    vector<Pers>::iterator it = persons.begin();
    while (it != persons.end()) {
        sum += it->mark;
        count++;
        it++;
    }

    double avg = sum / count;

    it = persons.begin();
    while (it != persons.end()) {
        if (fabs(it->mark - avg) <= eps) {
            fout << it->file << ' ' << it->name << ' ' << it->marks << endl;
        } else if (it->mark > avg) {
            fout << it->file << ' ' << it->name << ' ' << it->marks << endl;
        }
        it++;
    }
    fout.close();
    return 0;
}
