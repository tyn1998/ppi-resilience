#include <iostream>
#include "compute_biological_info.h"
#include <fstream>
#include <string>
#include <vector>
#include "string"

using namespace std;

const string JOB_LIST_PATH = "../data/input/job_list.txt";
const string FRAGMENTATION_DIR = "../data/input/fragmentation";
const string OUTPUT_DIR = "../data/output";
const int RANDOM_COUNT = 1000;

struct AllStrategiesResilience {
    vector<double> randoms;
    double betweenness;
    double closeness;
    double degreecentrality;
};

// 获取jobs
vector<string> GetJobList() {
    ifstream job_list_file(JOB_LIST_PATH.c_str());
    string line;
    vector<string> job_list;
    for (int i = 0; getline(job_list_file, line); i++) {
        job_list.push_back(line);
    }
    return job_list;
}

void WriteEntropies(vector<double> entropies, string outpath) {
    ofstream out(outpath.c_str());
    // 补上0%的点
    out << 0 << endl;
    for(vector<double>::iterator it=entropies.begin(); it!=entropies.end(); it++) {
        out << *it << endl;
    }
}

AllStrategiesResilience GetAllStrategiesResilience(string species_id) {
    AllStrategiesResilience asr;

    string species_fragmentation_dir = FRAGMENTATION_DIR + "/" + species_id;
    string random_dir = species_fragmentation_dir + "/random";
    string betweenness_path = species_fragmentation_dir + "/betweenness";
    string closeness_path = species_fragmentation_dir + "/closeness";
    string degreecentrality_path = species_fragmentation_dir + "/degreecentrality";

    vector<double> modified_shannon_entropies;
    double resilience = 0.0;

    for (int i=0; i<RANDOM_COUNT; i++) {
        string random_i_path = random_dir + "/random_" + to_string(i);
        modified_shannon_entropies = ComputeModifiedShannonEntropies(random_i_path);
        WriteEntropies(modified_shannon_entropies, OUTPUT_DIR+"/"+species_id+"/entropies/random/random_"+to_string(i));
        resilience = ComputeResilience(modified_shannon_entropies);
        asr.randoms.push_back(resilience);
    }

    modified_shannon_entropies =
        ComputeModifiedShannonEntropies(betweenness_path);
    WriteEntropies(modified_shannon_entropies, OUTPUT_DIR+"/"+species_id+"/entropies/betweenness");
    resilience = ComputeResilience(modified_shannon_entropies);
    asr.betweenness = resilience;
    modified_shannon_entropies =
        ComputeModifiedShannonEntropies(closeness_path);
    WriteEntropies(modified_shannon_entropies, OUTPUT_DIR+"/"+species_id+"/entropies/closeness");
    resilience = ComputeResilience(modified_shannon_entropies);
    asr.closeness = resilience;
    modified_shannon_entropies =
        ComputeModifiedShannonEntropies(degreecentrality_path);
    WriteEntropies(modified_shannon_entropies, OUTPUT_DIR+"/"+species_id+"/entropies/degreecentrality");
    resilience = ComputeResilience(modified_shannon_entropies);
    asr.degreecentrality = resilience;

    return asr;
}

int main() {
    system(("mkdir -p " + OUTPUT_DIR).c_str());

    vector<string> jobs = GetJobList();

    int jobs_num = jobs.size();
    for (int i=0; i<jobs_num; i++) {
        string species_id = jobs[i];
        cout << "# (" << i+1 << "/" << jobs_num << ") " << species_id << endl;

        string species_dir = OUTPUT_DIR + "/" + species_id;
        string entropies_dir = species_dir + "/entropies";
        string random_dir = entropies_dir + "/random";
        system(("mkdir -p " + species_dir).c_str());
        system(("mkdir -p " + entropies_dir).c_str());
        system(("mkdir -p " + random_dir).c_str());
        
        AllStrategiesResilience asr = GetAllStrategiesResilience(species_id); 

        double random_sum = 0.0;
        double random_avg = 0.0;

        for (vector<double>::iterator it=asr.randoms.begin(); it!=asr.randoms.end(); it++) {
            random_sum += *it;
        }
        random_avg = random_sum / RANDOM_COUNT;

        string output_path = species_dir + "/resilience";
        ofstream out(output_path.c_str());
        out << random_avg << endl
            << asr.betweenness << endl 
            << asr.closeness << endl 
            << asr.degreecentrality << endl;
    }
    return 0;
}
