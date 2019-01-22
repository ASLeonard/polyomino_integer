#include "integer_model.hpp"

std::vector <Phenotype_ID> AssemblePlasticGenotypeAPI(Genotype genotype, double threshold,
  uint16_t phenotype_builds, const std::string table_file);

std::map <Phenotype_ID, uint16_t> AssemblePlasticGenotypeFrequencyAPI(Genotype genotype,
  double threshold, uint16_t phenotype_builds, const std::string table_file);
