#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "genotype_api.hpp"

namespace py = pybind11;

PYBIND11_MODULE(polyo, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring

    // Assembly Functions
    m.def("AssemblePlasticGenotype", &AssemblePlasticGenotypeAPI,
      "A function which builds a genome, create a new phenotype table and return the Phenotype_IDs of the built polyominoes",
      py::arg("genotype"), py::arg("threshold") = 0.25, py::arg("phenotype_builds") = 40,
      py::arg("table_file") = std::string("None"));

    m.def("AssemblePlasticGenotypeFrequency", &AssemblePlasticGenotypeFrequencyAPI,
      "A function which builds a genome, create a new phenotype table and return the Phenotype_IDs of the built polyominoes",
      py::arg("genotype"), py::arg("threshold") = 0.25, py::arg("phenotype_builds") = 40,
      py::arg("table_file") = std::string("None"));

    // Genome Space generator functions

    m.def("MinimalGenomes", &MinimalGenomesAPI,
      "Create a new phenotype table and return generate minimal genomes for (n_genes, colours)",
      py::arg("n_genes") = 2, py::arg("low_colour") = 0, py::arg("high_colour") = 6,
      py::arg("genome_file") = std::string("None"), py::arg("phenotype_builds") = 40,
      py::arg("threshold") = 0.25);

    m.def("MinimalGenomesVoid", &MinimalGenomesVoidAPI,
      "Create a new phenotype table, generate minimal genomes for (n_genes, colours) and save them in genome_file",
      py::arg("n_genes") = 2, py::arg("low_colour") = 0, py::arg("high_colour") = 6,
      py::arg("genome_file") = std::string("None"), py::arg("phenotype_builds") = 40,
      py::arg("threshold") = 0.25);

    // GPmap functions

    // m.def("MinimalMap", &MinimalMapAPI,
    //   "Return the GP map built from a list of genomes or a genome file.",
    //   py::arg("genomes") = std::vector <Genotype> (), py::arg("table_file") = std::string("None"),
    //   py::arg("gpmap_file") = std::string("None"), py::arg("genome_file") = std::string("None"),
    //   py::arg("threshold") = 0.25, py::arg("phenotype_builds") = 250);

    m.def("MinimalMapVoid", &MinimalMapVoidAPI,
      "Save the GP map built from a list of genomes or a genome file.",
      py::arg("genomes") = std::vector <Genotype> (), py::arg("table_file") = std::string("None"),
      py::arg("gpmap_file") = std::string("None"), py::arg("genome_file") = std::string("None"),
      py::arg("threshold") = 0.25, py::arg("phenotype_builds") = 250);


    // // PhenotypeTable functions
    //
    // m.def("SaveNewTable", &SaveNewTableAPI,
    //   "Generate and save a new instance of the PhenotypeTable filled with the ID and Polyominoes corresponding to the provided genomes.",
    //   py::arg("genome_file") = "None", py::arg("table_file") = "None",
    //   py::arg("threshold") = 0.25, py::arg("phenotype_builds") = 250);
    //
    m.def("LoadTable", &LoadTableAPI,
      "Return a python dictionary of the unordered_map variable of the target PhenotypeTable",
      py::arg("table_file") = std::string("None"));

    // m.def("GenerateTable", &GenerateTableAPI, "Test function to print the phenotype Table", py::arg("genotype"), py::arg("filepath") = "None", py::arg("filename") = "None");
}
