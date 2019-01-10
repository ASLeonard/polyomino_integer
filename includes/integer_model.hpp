#pragma once


#include "core_genotype.hpp"
#include "core_phenotype.hpp"
#include "core_evolution.hpp"


using Genotype = std::vector<uint8_t>;

class IntegerAssembly : public PolyominoAssembly<IntegerAssembly> {
  inline static uint8_t max_colour=8;
public:  
  static double InteractionMatrix(const uint8_t, const uint8_t);
  inline static thread_local auto GenRandomSites = []() {return std::uniform_int_distribution<uint8_t>(0, max_colour)(RNG_Engine);};
  static void Mutation(Genotype& genotype);
  
};
