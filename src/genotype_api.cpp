#include "genotype_api.hpp"
#include <fstream>

namespace py = pybind11;

// Assembly functions

std::vector <Phenotype_ID> AssemblePlasticGenotypeAPI(Genotype genotype, double threshold,
  uint16_t phenotype_builds, const std::string table_file, py::kwargs kwargs)
{
  PhenotypeTable pt = PhenotypeTable();
  PhenotypeTable::phenotype_builds = phenotype_builds;
  PhenotypeTable::UND_threshold = threshold;
  std::string test = "None";

  if(table_file != test)
  {
    py::print("Loading table from : ", table_file);
    pt.LoadTable(table_file);
  }

  return AssemblePlasticGenotype(genotype, &pt);
}

std::map <Phenotype_ID, uint16_t> AssemblePlasticGenotypeFrequencyAPI(Genotype genotype,
  double threshold, uint16_t phenotype_builds, const std::string table_file, py::kwargs kwargs)
{
  PhenotypeTable pt = PhenotypeTable();
  PhenotypeTable::phenotype_builds = phenotype_builds;
  PhenotypeTable::UND_threshold = threshold;
  std::string test = "None";

  if(table_file != test)
  {
    py::print("Loading table from : ", table_file);
    pt.LoadTable(table_file);
  }

  return AssemblePlasticGenotypeFrequency(genotype, &pt);
}

// Minimal Generator functions

std::vector <Genotype> MinimalGenomesAPI(uint8_t n_genes, int8_t low_colour, int8_t high_colour,
  const std::string genome_file, uint16_t phenotype_builds, double threshold, py::kwargs kwargs)
{
  PhenotypeTable pt;
  PhenotypeTable::UND_threshold = threshold;
  PhenotypeTable::phenotype_builds = phenotype_builds;
  std::string test = "None";

  std::vector <Genotype> genomes = ExhaustiveMinimalGenotypesFiltered(&pt, n_genes,
     low_colour, high_colour);

  if(genome_file != test)
    PrintGenomeFile(genome_file, genomes);

  return genomes;
}

void MinimalGenomesVoidAPI(uint8_t n_genes, int8_t low_colour, int8_t high_colour,
  const std::string genome_file, uint16_t phenotype_builds, double threshold, py::kwargs kwargs)
{
  std::vector <Genotype> genomes = MinimalGenomesAPI(n_genes, low_colour,
    high_colour, genome_file, phenotype_builds, threshold, kwargs);
}


// Minimal GP_map

Set_to_Genome MinimalMap(std::vector <Genotype> genomes,
  const std::string table_file, const std::string gpmap_file,
  const std::string genome_file, double threshold, uint16_t phenotype_builds,
  py::kwargs kwargs)
{
  PhenotypeTable pt;
  PhenotypeTable::UND_threshold = threshold;
  PhenotypeTable::phenotype_builds = phenotype_builds;
  std::string test = "None";

  Set_to_Genome gpmap;

  if(genome_file != test)
    LoadGenomeFile(genome_file, genomes);

  PreProcessSampled(genomes, gpmap, &pt);

  if(table_file != test)
    pt.PrintTable(table_file);

  if(gpmap_file != test)
    PrintPreProcessFile2(gpmap_file, gpmap);

  return gpmap;
}

String_to_Genome MinimalMapAPI(std::vector <Genotype> genomes,
  const std::string table_file, const std::string gpmap_file,
  const std::string genome_file, double threshold, uint16_t phenotype_builds,
  py::kwargs kwargs)
{
  Set_to_Genome gpmap = MinimalMap(genomes, table_file, gpmap_file,
    genome_file, threshold, phenotype_builds, kwargs);

  String_to_Genome gpmap2;
  std::stringstream result;

  for(auto kv: gpmap)
  {

    result << "{";
    for(auto pID: kv.first) {
      result << "(" <<+ pID.first << "," <<+ pID.second << "),";
      py::print("(", pID.first , "," , pID.second , "),");
    }
    result << "}";
    py::print(result.str());
    std::string key = result.str();
    result.str(std::string());
    // gpmap2[key] = kv.second;
  }

  return gpmap2;
}

void MinimalMapVoidAPI(std::vector <Genotype> genomes, const std::string table_file,
  const std::string gpmap_file, const std::string genome_file,
  double threshold, uint16_t phenotype_builds, py::kwargs kwargs)
{
  Set_to_Genome gpmap = MinimalMap(genomes, table_file, gpmap_file,
    genome_file, threshold, phenotype_builds, kwargs);
}

// Mainly intended to generate the initial table

std::unordered_map <uint8_t, std::vector<Phenotype>> LoadTableAPI(const std::string table_file,
  py::kwargs kwargs)
{
  PhenotypeTable pt;
  pt.LoadTable(table_file);

  return pt.known_phenotypes;
}
