#include "genotype_api.hpp"
#include "pybind11/pybind11.h"
#include <fstream>

namespace py = pybind11;

// Assembly functions

std::vector <Phenotype_ID> AssemblePlasticGenotypeAPI(Genotype genotype, double threshold,
  uint16_t phenotype_builds, const std::string table_file)
{
  PhenotypeTable pt = PhenotypeTable();
  PhenotypeTable::phenotype_builds = phenotype_builds;
  PhenotypeTable::UND_threshold = threshold;

  std::ifstream fin(table_file.c_str());
  if(fin.good()) {
    py::print("Loading table from : ", table_file);
    pt.LoadTable(table_file);
  }

  return AssemblePlasticGenotype(genotype, &pt);
}

std::map <Phenotype_ID, uint16_t> AssemblePlasticGenotypeFrequencyAPI(Genotype genotype,
  double threshold, uint16_t phenotype_builds, const std::string table_file)
{
  PhenotypeTable pt = PhenotypeTable();
  PhenotypeTable::phenotype_builds = phenotype_builds;
  PhenotypeTable::UND_threshold = threshold;

  std::ifstream fin(table_file.c_str());
  if(fin.good()) {
    py::print("Loading table from : ", table_file);
    pt.LoadTable(table_file);
  }

  return AssemblePlasticGenotypeFrequency(genotype, &pt);
}


// Minimal Generator functions
