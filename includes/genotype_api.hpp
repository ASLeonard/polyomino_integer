#include "integer_model.hpp"
#include "genotype_generate.hpp"
#include "genotype_iofunc.hpp"
#include "pybind11/pybind11.h"

namespace py = pybind11;

// Assembly Functions
std::vector <Phenotype_ID> AssemblePlasticGenotypeAPI(Genotype genotype, double threshold,
  uint16_t phenotype_builds, const std::string table_file, py::kwargs kwargs);

std::map <Phenotype_ID, uint16_t> AssemblePlasticGenotypeFrequencyAPI(Genotype genotype,
  double threshold, uint16_t phenotype_builds, const std::string table_file,
  py::kwargs kwargs);

// Generator Functions
std::vector <Genotype> MinimalGenomesAPI(uint8_t n_genes, int8_t low_colour,
  int8_t high_colour, const std::string genome_file, uint16_t phenotype_builds,
  double threshold, py::kwargs kwargs);

void MinimalGenomesVoidAPI(uint8_t n_genes, int8_t low_colour, int8_t high_colour,
  const std::string genome_file, uint16_t phenotype_builds, double threshold,
  py::kwargs kwargs);

// GPmap functions
Set_to_Genome MinimalMap(std::vector <Genotype> genomes,
  const std::string table_file, const std::string gpmap_file,
  const std::string genome_file, double threshold, uint16_t phenotype_builds,
  py::kwargs kwargs);

String_to_Genome MinimalMapAPI(std::vector <Genotype> genomes,
  const std::string table_file, const std::string gpmap_file,
  const std::string genome_file, double threshold, uint16_t phenotype_builds,
  py::kwargs kwargs);

void MinimalMapVoidAPI(std::vector <Genotype> genomes, const std::string table_file,
  const std::string gpmap_file, const std::string genome_file,
  double threshold, uint16_t phenotype_builds, py::kwargs kwargs);

// Phenotype Table

std::unordered_map <uint8_t, std::vector<Phenotype>> LoadTableAPI(const std::string table_file, py::kwargs kwargs);
