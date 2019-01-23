#include "integer_model.hpp"
#include "genotype_generate.hpp"
#include "genotype_iofunc.hpp"

std::vector <Phenotype_ID> AssemblePlasticGenotypeAPI(Genotype genotype, double threshold,
  uint16_t phenotype_builds, const std::string table_file);

std::map <Phenotype_ID, uint16_t> AssemblePlasticGenotypeFrequencyAPI(Genotype genotype,
  double threshold, uint16_t phenotype_builds, const std::string table_file);

void GenerateMinimalGenomesAPI(uint8_t n_genes, int8_t low_colour, int8_t high_colour, 
  const std::string genome_file, uint16_t phenotype_builds, double threshold);
