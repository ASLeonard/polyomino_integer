#pragma once


#include "core_genotype.hpp"
#include "core_phenotype.hpp"
#include "core_evolution.hpp"

using interface_type = int8_t;
using Genotype = std::vector<interface_type>;

class IntegerAssembly : public PolyominoAssembly<IntegerAssembly> {
  inline static interface_type min_colour=0,max_colour=8;
  
public:  
  static double InteractionMatrix(const interface_type, const interface_type);
  inline static thread_local auto GenRandomSites = []() {return std::uniform_int_distribution<interface_type>(min_colour, max_colour)(RNG_Engine);};
  static void Mutation(Genotype& genotype);
  
};
