#include "compute_biological_info.h"

#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

double ComputeResilience(vector<double> modified_shannon_entropies) {
    int num_steps = modified_shannon_entropies.size();
    double resilience = 1.0;

    // 计算resilience（模拟微积分）
    for (vector<double>::iterator it = modified_shannon_entropies.begin();
         it != modified_shannon_entropies.end(); it++) {
        resilience -= *it * (1.0 / num_steps);
    }
    return resilience;
}

vector<double> ComputeModifiedShannonEntropies(std::string fragmentation_path) {
    vector<double> modified_shannon_entropies;

    ifstream fragmentation(fragmentation_path.c_str());
    string line;

    while (getline(fragmentation, line)) {
        double percentage_nodes_deleted;
        int num_nodes_remained;
        char components_detail[999];

        // 将当前line分为三部分
        sscanf(line.c_str(), "%lf %d, %[^\n]", &percentage_nodes_deleted,
               &num_nodes_remained, components_detail);

        // 计算shannon_entropy
        string str_components_detail = components_detail;
        int comma_pos = -1;
        double shannon_entropy = 0.0;

        // 剩余结点只有0或1会导致log2(0)以及1/log2(1)，产生NaN
        if (num_nodes_remained > 1) {
            while ((comma_pos = str_components_detail.find(",")) !=
                   string::npos) {
                string sub_detail = str_components_detail.substr(0, comma_pos);
                int component_size =
                    stoi(sub_detail.substr(0, sub_detail.find(" ")));
                int component_num =
                    stoi(sub_detail.substr(sub_detail.find(" ")));

                double pi = double(component_size) / num_nodes_remained;
                shannon_entropy += -(pi * log2(pi)) * component_num;

                // 判断是否为该line最后一个逗号，防止.substr()溢出
                if (str_components_detail.substr(comma_pos).length() != 2) {
                    str_components_detail =
                        str_components_detail.substr(comma_pos + 2);
                } else {
                    //清空该字符串，否则最后一次sscanf扫不到第三部分该字符串值不变会引起后面错误
                    strcpy(components_detail, "");
                    break;
                }
            }
            // 计算modified_shannon_entropy，并加入数组
            double modified_shannon_entropy = 0.0;
            modified_shannon_entropy = (1 / log2(num_nodes_remained)) * shannon_entropy;
            modified_shannon_entropies.push_back(modified_shannon_entropy);
        } else {
            modified_shannon_entropies.push_back(1.0);
        }
    }
    return modified_shannon_entropies;
}
