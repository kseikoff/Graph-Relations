#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);

    int edges_amount; int vertex_amount;
    bool overwrite = false; bool transitive = false; bool non_transitive = false;
    int count_zeroes_for_symmetric; int count_zeroes_for_reflexivity;

    std::cin >> edges_amount >> vertex_amount;
    if (edges_amount == 0 && vertex_amount == 0) {
        std::cout << "Для пустого графа выполняются все отношения" << std::endl; return 0;
    } else if (edges_amount == 0 && vertex_amount != 0) {
        std::cout << "Граф без ребер антирефлексивен, остальные отношения любые" << std::endl; return 0;
    }

    std::vector<std::vector<int>> paths_container(edges_amount);

    for (int i = 0; i < edges_amount; i++) {
        int path_from; int path_to;
        std::cin >> path_from >> path_to;
        std::vector<int> path_values(2);
        path_values[0] = path_from; path_values[1] = path_to;
        paths_container[i] = path_values;
    }

    count_zeroes_for_symmetric = edges_amount;

    count_zeroes_for_reflexivity = vertex_amount;

    std::vector<int> transitivity(edges_amount);

    for (int i = 0; i < paths_container.size(); i++) {
        if (paths_container.at(i).at(0) != paths_container.at(i).at(1)) {
            for (int j = 0; j < paths_container.size(); j++) {
                if (i != j) {
                    if (paths_container.at(i).at(1) == paths_container.at(j).at(0)) {
                        if (paths_container.at(j).at(0) != paths_container.at(j).at(1)) {
                            if(paths_container.at(i).at(0) != paths_container.at(j).at(1)){
                                std::vector<int> transitivity_path(2);
                                transitivity_path[0] = paths_container.at(i).at(0);
                                transitivity_path[1] = paths_container.at(j).at(1);
                                if (find(paths_container.begin(),paths_container.end(),
                                         transitivity_path) != paths_container.end()) {
                                    if (transitivity.at(i) == -1) {
                                        transitivity.at(i) = 2;
                                        overwrite = true;
                                    } else if (transitivity.at(i) != 2) {
                                            transitivity.at(i) = 1;
                                            transitive = true;
                                    }
                                } else {
                                    if (transitivity.at(i) != 1 && transitivity.at(i) != 2) {
                                        transitivity.at(i) = -1;
                                        non_transitive = true;
                                    }
                                    else {
                                        transitivity.at(i) = 2;
                                        overwrite = true;
                                    }
                                }
                            }
                            else{
                                count_zeroes_for_symmetric -= 1;
                            }
                        }
                    }
                }
            }
        } else {
            count_zeroes_for_symmetric -= 1;
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
    if (overwrite || (transitive && non_transitive)) {
        std::cout << "Нетранзитивный" << std::endl;
    } else if (!non_transitive && transitive) {
        std::cout << "Транзитивный" << std::endl;
    } else if (non_transitive) {
        std::cout << "Антитранзитивный" << std::endl;
    } else {
        std::cout << "Транзитивный/Антитранзитивный/Нетранзитивный" << std::endl;
    }
    return 0;
}