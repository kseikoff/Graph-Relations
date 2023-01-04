#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>

using namespace std;

vector<int> split(const string& str, char delimiter) {
    vector<int> internal;
    stringstream ss(str);
    string tok;
    while(getline(ss, tok, delimiter)) {
        internal.push_back(stoi(tok));
    }
    return internal;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    int edge_vertex_container[2];
    bool deuce_presence = false;
    int count_zeroes_for_symmetric;
    int count_zeroes_for_reflexivity;

    string edge_vertex_values;
    getline(cin, edge_vertex_values);
    vector<int> split_edge_vertex_values = split(edge_vertex_values, ' ');
    edge_vertex_container[0] = split_edge_vertex_values.at(0);
    edge_vertex_container[1] = split_edge_vertex_values.at(1);
    if (edge_vertex_container[0] == 0 && edge_vertex_container[1] == 0) {
        cout << "Для пустого графа выполняются все отношения" << endl;
        return 0;
    } else if (edge_vertex_container[0] == 0 && edge_vertex_container[1] != 0) {
        cout << "Граф без ребер антирефлексивен, остальные отношения любые" << endl;
        return 0;
    }

    vector<vector<int>> paths_container;
    paths_container.reserve(edge_vertex_container[0]);

    for (int i = 0; i < edge_vertex_container[0]; i++) {
        string path_values;
        getline(cin, path_values);
        vector<int> split_path_values = split(path_values, ' ');
        paths_container.push_back(split_path_values);
    }

    count_zeroes_for_symmetric = edge_vertex_container[0];
    vector<int> symmetric;
    symmetric.reserve(edge_vertex_container[0]);
    for (int i = 0; i < edge_vertex_container[0]; i++) {
        symmetric.push_back(0);
    }

    count_zeroes_for_reflexivity = edge_vertex_container[1];
    vector<int> reflexivity;
    reflexivity.reserve(edge_vertex_container[1]);
    for (int i = 0; i < edge_vertex_container[1]; i++) {
        reflexivity.push_back(0);
    }

    vector<int> transitivity;
    transitivity.reserve(edge_vertex_container[0]);
    for (int i = 0; i < edge_vertex_container[0]; i++) {
        transitivity.push_back(0);
    }

    for (int i = 0; i < paths_container.size(); i++) {
        if (paths_container.at(i).at(0) == paths_container.at(i).at(1)) {
            reflexivity.at(paths_container.at(i).at(0) - 1) = 1;
            count_zeroes_for_reflexivity -= 1;
        }
        vector<int> reversed_path;
        reversed_path.reserve(2);
        reversed_path.push_back(paths_container.at(i).at(1));
        reversed_path.push_back(paths_container.at(i).at(0));
        if (find(paths_container.begin(), paths_container.end(),
                 reversed_path) != paths_container.end()) {
            symmetric.at(i) = 1;
            count_zeroes_for_symmetric -= 1;
        }
        if (paths_container.at(i).at(0) != paths_container.at(i).at(1)) {
            for (int j = 0; j < paths_container.size(); j++) {
                if (i != j) {
                    if (paths_container.at(i).at(1) == paths_container.at(j).at(0)) {
                        if (paths_container.at(j).at(0) != paths_container.at(j).at(1)
                            && (paths_container.at(i).at(0) != paths_container.at(j).at(1))) {
                            vector<int> transitivity_path;
                            transitivity_path.reserve(2);
                            transitivity_path.push_back(paths_container.at(i).at(0));
                            transitivity_path.push_back(paths_container.at(j).at(1));
                            __gnu_cxx::__normal_iterator<vector<int> *,
                                    vector<vector<int>>> path_presence = find(paths_container.begin(),
                                                                          paths_container.end(),
                                                                          transitivity_path);
                            if (path_presence != paths_container.end()) {
                                if (transitivity.at(i) == -1) {
                                    transitivity.at(i) = 2;
                                    deuce_presence = true;
                                } else {
                                    if (transitivity.at(i) != 2) {
                                        transitivity.at(i) = 1;
                                    }
                                }
                                if (transitivity.at(j) == -1) {
                                    transitivity.at(j) = 2;
                                    deuce_presence = true;
                                } else {
                                    if (transitivity.at(j) != 2) {
                                        transitivity.at(j) = 1;
                                    }
                                }
                                int index_of_transitivity_path = distance(paths_container.begin(), path_presence);
                                if (transitivity.at(index_of_transitivity_path) == -1) {
                                    transitivity.at(index_of_transitivity_path) = 2;
                                    deuce_presence = true;
                                } else {
                                    if (transitivity.at(index_of_transitivity_path) != 2) {
                                        transitivity.at(index_of_transitivity_path) = 1;
                                    }
                                }
                            } else if (transitivity.at(i) != 1 && transitivity.at(j) != 1
                                       && transitivity.at(i) != 2 && transitivity.at(j) != 2) {
                                transitivity.at(i) = -1;
                                transitivity.at(j) = -1;
                            } else {
                                if (transitivity.at(i) != 2) {
                                    if (transitivity.at(i) != 0 && transitivity.at(i) != -1) {
                                        transitivity.at(i) = 2;
                                        deuce_presence = true;
                                    } else {
                                        transitivity.at(i) = -1;
                                    }
                                }
                                if (transitivity.at(j) != 2) {
                                    if (transitivity.at(j) != 0 && transitivity.at(j) != -1) {
                                        transitivity.at(j) = 2;
                                        deuce_presence = true;
                                    } else {
                                        transitivity.at(j) = -1;
                                    }
                                }
                            }
                        } else {
                            if (transitivity.at(j) == 0) {
                                transitivity.at(j) = 3;
                            }
                        }
                    }
                }
            }
        } else {
            if (transitivity.at(i) == 0) {
                transitivity.at(i) = 3;
            }
        }
    }
    if (count_zeroes_for_symmetric == 0) {
        cout << "Симметричный" << endl;
    } else if (count_zeroes_for_symmetric == edge_vertex_container[0]) {
        cout << "Антисимметричный" << endl;
    } else {
        cout << "Несимметричный" << endl;
    }
    if (count_zeroes_for_reflexivity == 0) {
        cout << "Рефлексивный" << endl;
    } else if (count_zeroes_for_reflexivity == edge_vertex_container[1]) {
        cout << "Антирефлексивный" << endl;
    } else {
        cout << "Нерефлексивный" << endl;
    }
    if (deuce_presence || ((find(transitivity.begin(), transitivity.end(), 1) != transitivity.end()) &&
         find(transitivity.begin(), transitivity.end(), -1) != transitivity.end())) {
        cout << "Нетранзитивный" << endl;
    } else if (find(transitivity.begin(), transitivity.end(), -1) == transitivity.end() &&
               find(transitivity.begin(), transitivity.end(), 1) != transitivity.end()) {
        cout << "Транзитивный" << endl;
    } else if (find(transitivity.begin(), transitivity.end(), 1) == transitivity.end() &&
               find(transitivity.begin(), transitivity.end(), -1) != transitivity.end()) {
        cout << "Антитранзитивный" << endl;
    } else {
        cout << "Транзитивный/Антитранзитивный/Нетранзитивный" << endl;
    }
    return 0;
}