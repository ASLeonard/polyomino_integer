#include "genotype_phenotype.hpp"

namespace simulation_params
{
  extern uint16_t n_genes;
}

std::vector<Genotype> GenomesDuplication(std::vector<Genotype> genomes);
std::vector<Genotype> GeneDuplication(Genotype& genotype);
