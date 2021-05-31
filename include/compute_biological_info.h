#ifndef PPI_RESILIENCE_COMPUTE_BIOLOGICAL_INFO_H_
#define PPI_RESILIENCE_COMPUTE_BIOLOGICAL_INFO_H_

#include <string>
#include <vector>

double ComputeResilience(std::vector<double> modified_shannon_entropies);
std::vector<double> ComputeModifiedShannonEntropies(std::string fragmentation_path);

#endif /* ifndef PPI_RESILIENCE_COMPUTE_BIOLOGICAL_INFO_H_ */
