#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "lib.h"

struct my_struct {
    std::string text1;
    std::string text2;
    std::string text3;
};

int main (int, char **) {
    std::cout << "Version: " << version() << std::endl;
    std::cout << "For write ip address press 'w', for download ip address press 'd', for exit press any other letter:" << std::endl;

    int count = 0;
    int max_count = 100;
    std::vector<my_struct> ip_addresses(max_count);

    std::string line;
    std::ifstream in ("ip_address.txt");

    std::string letter;
    std::cin >> letter;

    // входные параметры
    if (letter == "w") {
        std::cout << "Write number ip address (max count = 100):";
        std::cin >> count;

        for(int i = 0; i < count; i++) {
            int n1, n2, n3, n4;
            std::cin >> n1;
            std::cin >> n2;
            std::cin >> n3;
            std::cin >> n4;
            ip_addresses.at(i).text1 = std::to_string(n1) + "." + std::to_string(n2) + "." +
                                       std::to_string(n3) + "." + std::to_string(n4);
            std::cout << ip_addresses.at(i).text1 << std::endl;
        }
        
        std::cout << "_______________" << std::endl;
        for(int i = 0; i < count; i++) {
            std::cout << ip_addresses.at(i).text1 << std::endl;
        }
        std::cout << "_______________" << std::endl;
        
    // сохранение
        std::cout << "For write ip adress press 's':" << std::endl;
        std::cin >> letter;
        if (letter == "s") {
            std::ofstream out;
            out.open("ip_address.txt");
            if(out.is_open()) {
                for(int i = 0; i < count; i++) {
                    out << ip_addresses.at(i).text1 << std::endl;
                }
            }
            out.close();
            std::cout << "File has been written" << std::endl;
        }
    }
    else if (letter == "d") {
        std::cout << "Download file ip_address.txt" << std::endl;

        if (in.is_open()){
            while (std::getline(in, line)){
                ip_addresses.at(count).text1 = line;
                count += 1;
            }
        }
        in.close();
        
        std::cout << "_______________" << std::endl;
        for(int i = 0; i < count; ++i) {
            std::cout << ip_addresses.at(i).text1 << std::endl;
        }
        std::cout << "_______________" << std::endl;
    }

    // сортировка
    std::cout << "Sorting in ascending order:" << std::endl;
    std::cout << "_______________" << std::endl;

    // количество различных элементов по первому числу
    int first = 0, second = 0, third = 0, fourthd = 0;
    std::string text, first_el, second_el, third_el, fourthd_el;
    std::vector<int> vs;
    
    for (int i = 0; i < count; i++) {
        text = ip_addresses.at(i).text1;
        for (int j = 0; j < text.length(); j++) {
            if (text[j] == '.') {
                if(first == 0){
                    vs.push_back(std::stoi(first_el));
                    first_el.clear();
                    first ++;
                    break;
                }
                if(first != 0) {
                    for(int k = 0; k < first; k++) {
                        if(vs[k] == std::stoi(first_el)) {
                            first_el.clear();
                            break;
                        }
                        else if(k == first - 1) {
                            vs.push_back(std::stoi(first_el));
                            first_el.clear();
                            first ++;
                            break;
                        }
                    }
                    first_el.clear();
                    break;
                }
            }
            else {
                first_el += text[j];
            }
        }
    }

    // сортируем по второму элементу
    std::vector<int> vs1, vs2, vs3, vs4;
    bool isWrite1 = false;
    bool isWrite2 = false;
    bool isWrite3 = false;
    bool isWrite4 = false;
    int iter = 0;
    
    for (int i = 0; i < count; i++) {
        text = ip_addresses.at(i).text1;
        for (int j = 0; j <= text.length(); j++) {
            if (text[j] == '.' || j == text.length()) {
                if(!isWrite1) {
                    vs1.push_back(std::stoi(first_el));
                    iter ++;
                    isWrite1 = true;
                    continue;
                }
                if(!isWrite2) {
                    vs2.push_back(std::stoi(second_el));
                    iter ++;
                    isWrite2 = true;
                    continue;
                }
                if(!isWrite3) {
                    vs3.push_back(std::stoi(third_el));
                    iter ++;
                    isWrite3 = true;
                    continue;
                }
                if(!isWrite4) {
                    vs4.push_back(std::stoi(fourthd_el));
                    isWrite4 = true;
                    continue;
                }
            }
            else {
                if(!isWrite1)
                    first_el += text[j];
                if(isWrite1 && !isWrite2)
                    second_el += text[j];
                if(isWrite1 && isWrite2 && !isWrite3)
                    third_el += text[j];
                if(isWrite1 && isWrite2 && isWrite3 && !isWrite4)
                    fourthd_el += text[j];
            }
        }
            first_el.clear();
            second_el.clear();
            third_el.clear();
            fourthd_el.clear();
            isWrite1 = false;
            isWrite2 = false;
            isWrite3 = false;
            isWrite4 = false;
            iter = 0;
    }

    //сортируем по первому элементу
    for(int i = 0; i < first; i ++) {
        for(int j = 0; j < first - 1; j++) {
            if(vs[j] < vs[j + 1]) {
                int b = vs[j];
                vs[j] = vs[j + 1];
                vs[j + 1] = b;
            } 
        }
    }
    
    //сортируем
    std::vector<int> sort_vector;
    for(int i = 0; i < first; i ++) {
        int count_f = 0;
        std::vector<int> list_ip;
        for(int j = 0; j < count; j++) {
            if(vs[i] == vs1[j]) {
                count_f ++;
                list_ip.push_back(j);
            }
        }
        for(int j = 0; j < count_f; j ++) {
            for(int k = 0; k < (count_f - 1); k++) {
                if(vs2[list_ip[k]] < vs2[list_ip[k+1]]) {
                    int b = vs2[list_ip[k]];
                    vs2[list_ip[k]] = vs2[list_ip[k+1]];
                    vs2[list_ip[k+1]] = b;
                }
                if(vs2[list_ip[k]] <= vs2[list_ip[k+1]] && 
                   vs3[list_ip[k]] <  vs3[list_ip[k+1]]) {
                    int b = vs3[list_ip[k]];
                    vs3[list_ip[k]] = vs3[list_ip[k+1]];
                    vs3[list_ip[k+1]] = b;
                }
                if(vs2[list_ip[k]] <= vs2[list_ip[k+1]] && 
                   vs3[list_ip[k]] <= vs3[list_ip[k+1]] && 
                   vs4[list_ip[k]] <  vs4[list_ip[k+1]]) {
                    int b = vs4[list_ip[k]];
                    vs4[list_ip[k]] = vs4[list_ip[k+1]];
                    vs4[list_ip[k+1]] = b;
                }
            }
        }
        for(int k = 0; k < count_f; k++) {
            std::cout << vs1[list_ip[k]] << "." << vs2[list_ip[k]] << "." <<
                         vs3[list_ip[k]] << "." << vs4[list_ip[k]] << std::endl;
            sort_vector.push_back(list_ip[k]);
        }
    }
    //first bite = 1
    std::cout << "first bite = 1" << std::endl;
    for(int i = 0; i < count; i ++) {
        if(vs1[sort_vector[i]] == 1) {
            std::cout << vs1[sort_vector[i]] << "." << vs2[sort_vector[i]] << "." <<
                         vs3[sort_vector[i]] << "." << vs4[sort_vector[i]] << std::endl;
        }
    }
    //first bite = 46, second bite = 70
    std::cout << "first bite = 46, second bite = 70" << std::endl;
    for(int i = 0; i < count; i ++) {
        if(vs1[sort_vector[i]] == 46 && vs2[sort_vector[i]] == 70) {
            std::cout << vs1[sort_vector[i]] << "." << vs2[sort_vector[i]] << "." <<
                         vs3[sort_vector[i]] << "." << vs4[sort_vector[i]] << std::endl;
        }
    }
    //other bite = 46
    std::cout << "other bite = 46" << std::endl;
    for(int i = 0; i < count; i ++) {
        if(vs1[sort_vector[i]] == 46 || vs2[sort_vector[i]] == 46 || 
           vs3[sort_vector[i]] == 46 || vs4[sort_vector[i]] == 46) {
            std::cout << vs1[sort_vector[i]] << "." << vs2[sort_vector[i]] << "." <<
                         vs3[sort_vector[i]] << "." << vs4[sort_vector[i]] << std::endl;
        }
    }

    return 0;
}
