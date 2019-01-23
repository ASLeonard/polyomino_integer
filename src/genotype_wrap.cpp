#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "genotype_api.hpp"

namespace py = pybind11;

PYBIND11_MODULE(polyo, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring

    m.def("AssemblePlasticGenotype", &AssemblePlasticGenotypeAPI,
      "A function which builds a genome, create a new phenotype table and return the Phenotype_IDs of the built polyominoes",
      py::arg("genotype"), py::arg("threshold") = 0.25, py::arg("phenotype_builds") = 40,
      py::arg("table_file") = "None");

    m.def("AssemblePlasticGenotypeFrequency", &AssemblePlasticGenotypeFrequencyAPI,
      "A function which builds a genome, create a new phenotype table and return the Phenotype_IDs of the built polyominoes",
      py::arg("genotype"), py::arg("threshold") = 0.25, py::arg("phenotype_builds") = 40,
      py::arg("table_file") = "None");

    m.def("GenerateMinimalGenomes", &GenerateMinimalGenomesAPI,
      "Create a new phenotype table, generate minimal genomes for (n_genes, colours) and save them in genome_file",
      py::arg("n_genes") = 2, py::arg("low_colour") = 0, py::arg("high_colour") = 7,
      py::arg("genome_file") = "None", py::arg("phenotype_builds") = 40, py::arg("threshold") = 0.25);

    // m.def("GenerateTable", &GenerateTableAPI, "Test function to print the phenotype Table", py::arg("genotype"), py::arg("filepath") = "None", py::arg("filename") = "None");
}
