#pragma once


#include "core_genotype.hpp"
#include "core_phenotype.hpp"
#include "core_evolution.hpp"



class IntegerAssembly : public PolyominoAssembly<IntegerAssembly> {
  
public:  
  static double InteractionMatrix(const int, const int);
  
};
