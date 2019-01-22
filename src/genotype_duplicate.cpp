#include "genotype_duplicate.hpp"

// Necessary to check that genotype.size() / 4 returns desired value

std::vector<Genotype> GenomesDuplication(std::vector<Genotype> genomes)
{
  std::vector<Genotype> genomes_dup;
  std::cout << "Adding duplicate genes to " <<+ genomes.size() << " genomes \n";

  for(auto genome: genomes)
    for(auto duplicate: GeneDuplication(genome))
      genomes_dup.emplace_back(duplicate);

  return genomes_dup;
}

std::vector<Genotype> GeneDuplication(Genotype& genotype)
{
  std::vector <Genotype> duplicates;

  for(uint8_t index=0; index < (genotype.size() / 4); ++index)
  {
    Genotype duplicate(genotype.size() / 4);
    std::copy(std::begin(genotype), std::end(genotype), std::begin(duplicate));

    for(uint8_t tail=0; tail < 4; tail++)
      duplicate.emplace_back(genotype[(4 * index) + tail]);

    duplicates.emplace_back(duplicate);
  }

  return duplicates;
}
