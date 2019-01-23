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

void GenerateMinimalGenomesAPI(uint8_t n_genes, int8_t low_colour, int8_t high_colour,
  const std::string genome_file, uint16_t phenotype_builds, double threshold)
{
  PhenotypeTable pt;
  PhenotypeTable::UND_threshold = threshold;
  PhenotypeTable::phenotype_builds = phenotype_builds;

  std::vector <Genotype> genomes = ExhaustiveMinimalGenotypesFiltered(&pt, n_genes, low_colour, high_colour);

  std::ofstream fout(genome_file);
  if(fout.good())
    PrintGenomeFile(genome_file, genomes);
}

// Reduce GP_map

// void GenerateTableAPI(std::string genome_file, std::string table_file,
//   double threshold, uint16_t phenotype_builds)
// {
//   PhenotypeTable pt;
//   PhenotypeTable::UND_threshold = threshold;
//   PhenotypeTable::phenotype_builds = phenotype_builds;
//
//   std::ifstream fin(genome_file);
//   std::vector <Genotype> genomes;
//   Set_to_Genome gpmap;
//
//   if(fin.good())
//     LoadGenomeFile(genome_file, genomes);
//
//   PreProcessSampled(genomes, gpmap, &pt);
//
// }
