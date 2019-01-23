#pragma once

#include "core_genotype.hpp"
#include "core_phenotype.hpp"
#include "core_evolution.hpp"

using interface_type = int8_t;
using Genotype = std::vector<interface_type>;

class IntegerAssembly : public PolyominoAssembly<IntegerAssembly> {

public:
  inline static interface_type min_colour=-1, max_colour=8;
  static double InteractionMatrix(const interface_type, const interface_type);
  inline static thread_local auto GenRandomSites = []() {return std::uniform_int_distribution<interface_type>(min_colour, max_colour)(RNG_Engine);};
  static void Mutation(Genotype& genotype);
};

std::vector<Phenotype_ID> AssemblePlasticGenotype(Genotype genotype, PhenotypeTable* pt);
std::map<Phenotype_ID, uint16_t> AssemblePlasticGenotypeFrequency(Genotype genotype, PhenotypeTable* pt);
bool FilterDeathRare(std::map<Phenotype_ID,uint16_t> ID_counter);

// Temporary fix for compatibility purpose
typedef std::map<std::vector<Phenotype_ID>, std::vector<Genotype>> Set_to_Genome;
typedef std::map<std::string, std::vector<Genotype>> String_to_Genome;

void Clean_Genome(Genotype& genome, bool Remove_Duplicates);
std::map<uint8_t,uint8_t> DuplicateGenes(Genotype& genome);
interface_type OppositeEdge(const interface_type label);
