#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);

    int edges_amount; int vertex_amount;
    bool deuce_presence = false;
    int count_zeroes_for_symmetric; int count_zeroes_for_reflexivity;

    std::cin >> edges_amount >> vertex_amount;
    if (edges_amount == 0 && vertex_amount == 0) {
        std::cout << "Для пустого графа выполняются все отношения" << std::endl; return 0;
    } else if (edges_amount == 0 && vertex_amount != 0) {
        std::cout << "Граф без ребер антирефлексивен, остальные отношения любые" << std::endl; return 0;
    }

    std::vector<std::vector<int>> paths_container;
    paths_container.reserve(edges_amount);

    for (int i = 0; i < edges_amount; i++) {
        int path_from; int path_to;
        std::cin >> path_from >> path_to;
        std::vector<int> path_values(2);
        path_values[0] = path_from; path_values[1] = path_to;
        paths_container.push_back(path_values);
    }

    count_zeroes_for_symmetric = edges_amount;
    std::vector<int> symmetric(edges_amount);

    count_zeroes_for_reflexivity = vertex_amount;
    std::vector<int> reflexivity(vertex_amount);

    std::vector<int> transitivity(edges_amount);

    for (int i = 0; i < paths_container.size(); i++) {
        if (paths_container.at(i).at(0) != paths_container.at(i).at(1)) {
            for (int j = 0; j < paths_container.size(); j++) {
                if (i != j) {
                    if (paths_container.at(i).at(1) == paths_container.at(j).at(0)) {
                        if (paths_container.at(j).at(0) != paths_container.at(j).at(1)) {
                            if(paths_container.at(i).at(0) != paths_container.at(j).at(1)){
                                std::vector<int> transitivity_path;
                                transitivity_path.reserve(2);
                                transitivity_path.push_back(paths_container.at(i).at(0));
                                transitivity_path.push_back(paths_container.at(j).at(1));
                                __gnu_cxx::__normal_iterator<std::vector<int> *,
                                        std::vector<std::vector<int>>> path_presence = find(paths_container.begin(),
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
                                } else if (transitivity.at(i) != 1 && transitivity.at(i) != 2) {
                                    transitivity.at(i) = -1;
                                } else {
                                    if (transitivity.at(i) != 2) {
                                        if (transitivity.at(i) != 0 && transitivity.at(i) != -1) {
                                            transitivity.at(i) = 2;
                                            deuce_presence = true;
                                        } else {
                                            transitivity.at(i) = -1;
                                        }
                                    }
                                }
                            }
                            else{
                                symmetric.at(i) = 1;
                                count_zeroes_for_symmetric -= 1;
                            }
                        }
                    }
                }
            }
        } else {
            symmetric.at(i) = 1;
            count_zeroes_for_symmetric -= 1;
            reflexivity.at(paths_container.at(i).at(0) - 1) = 1;
            count_zeroes_for_reflexivity -= 1;
            if (transitivity.at(i) == 0) {
                transitivity.at(i) = 3;
            }
        }
    }
    if (count_zeroes_for_symmetric == 0) {
        std::cout << "Симметричный" << std::endl;
    } else if (count_zeroes_for_symmetric == edges_amount) {
        std::cout << "Антисимметричный" << std::endl;
    } else {
        std::cout << "Несимметричный" << std::endl;
    }
    if (count_zeroes_for_reflexivity == 0) {
        std::cout << "Рефлексивный" << std::endl;
    } else if (count_zeroes_for_reflexivity == vertex_amount) {
        std::cout << "Антирефлексивный" << std::endl;
    } else {
        std::cout << "Нерефлексивный" << std::endl;
    }
    if (deuce_presence || ((find(transitivity.begin(), transitivity.end(), 1) != transitivity.end()) &&
         find(transitivity.begin(), transitivity.end(), -1) != transitivity.end())) {
        std::cout << "Нетранзитивный" << std::endl;
    } else if (find(transitivity.begin(), transitivity.end(), -1) == transitivity.end() &&
               find(transitivity.begin(), transitivity.end(), 1) != transitivity.end()) {
        std::cout << "Транзитивный" << std::endl;
    } else if (find(transitivity.begin(), transitivity.end(), 1) == transitivity.end() &&
               find(transitivity.begin(), transitivity.end(), -1) != transitivity.end()) {
        std::cout << "Антитранзитивный" << std::endl;
    } else {
        std::cout << "Транзитивный/Антитранзитивный/Нетранзитивный" << std::endl;
    }
    return 0;
}