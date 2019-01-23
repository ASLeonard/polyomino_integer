#include "integer_model.hpp"

double IntegerAssembly::InteractionMatrix(const interface_type face_1,const interface_type face_2) {
  if(face_1==0 || face_2==0) //neutral non-interacting colours
    return 0;
  if(face_1<0) //negative colours self-interact
    return face_1==face_2;
  else //positive colours interact in pairs
    return (face_1+(face_1%2?1:-1))==face_2;
}

void IntegerAssembly::Mutation(Genotype& genotype) {
  for(auto& base : genotype) {
    const interface_type base_C=base;
    do {
      base=GenRandomSites();
    } while(base==base_C); //don't allow mutations to be the same as the initial colour
  }
}

interface_type OppositeEdge(const interface_type label) {
  if (label < 0)
    return label;
  else if ((label % 2) == 0)
    return label - 1;
  else
    return label + 1;
}



std::map<Phenotype_ID, uint16_t> AssemblePlasticGenotypeFrequency(Genotype genotype, PhenotypeTable* pt) {

  // IntegerAssembly::StripNoncodingGenotype(genotype);
  const std::vector<std::pair<InteractionPair,double> > edges = IntegerAssembly::GetActiveInterfaces(genotype);

  std::vector<int8_t> assembly_information;
  Phenotype phen;
  std::vector<Phenotype_ID> Phenotype_IDs;
  Phenotype_IDs.reserve(pt->phenotype_builds);
  std::set<InteractionPair > interacting_indices;

  for(uint16_t nth=0;nth<pt->phenotype_builds;++nth) {

    assembly_information=IntegerAssembly::AssemblePolyomino(edges,interacting_indices); //ACTUAL ASSEMBLY OCCURS HERE

    if(assembly_information.size()>0) {
      phen=GetPhenotypeFromGrid(assembly_information);
      Phenotype_IDs.emplace_back(pt->GetPhenotypeID(phen));
    }
    else { //assembly was unbound
      std::map<Phenotype_ID, uint16_t> ID_counter;
      ID_counter[std::make_pair(255,0)] = 1;

      return ID_counter;
    }

    interacting_indices.clear();
  }

  pt->RelabelPhenotypes(Phenotype_IDs);

  return (pt->PhenotypeFrequencies(Phenotype_IDs));
}

std::vector<Phenotype_ID> AssemblePlasticGenotype(Genotype genotype,PhenotypeTable* pt) {

  std::map<Phenotype_ID,uint16_t> ID_counter = AssemblePlasticGenotypeFrequency(genotype, pt);
  std::vector<Phenotype_ID> pIDs;

  for(auto kv : ID_counter)
    pIDs.emplace_back(kv.first);

  std::sort(pIDs.begin(), pIDs.end());
  return pIDs;
}

bool FilterDeathRare(std::map<Phenotype_ID,uint16_t> ID_counter) {

  Phenotype_ID unbound = std::make_pair(255,0);
  Phenotype_ID rare = std::make_pair(0,0);

  if((ID_counter.count(unbound) > 0) || (ID_counter.count(rare) > 0))
    return true;

  return false;
}

// Temporary fix

void Clean_Genome(Genotype& genome,bool Remove_Duplicates=false) {
  IntegerAssembly::StripNoncodingGenotype(genome);
  // for(int32_t t=1;t<=*std::max_element(genome.begin(),genome.end());t+=2) {
  //   if(std::count(genome.begin(),genome.end(),t)==0) //genotype doens't contain this face
  //     std::replace(genome.begin(),genome.end(),t+1,uint32_t(0));
  //   else //genotype does contain this face
  //     if(std::find(genome.begin(),genome.end(),t+1)==genome.end()) //genotype doesn't contain conjugate
  //       std::replace(genome.begin(),genome.end(),t,uint32_t(0));
  // }
}

std::map<uint8_t,uint8_t> DuplicateGenes(Genotype& genome) {
  std::map<uint8_t, uint8_t> dups;
  for(int check_index=genome.size()/4-1;check_index>0;--check_index)
    for(int compare_index=0;compare_index<check_index;++compare_index)
      if(std::equal(genome.begin()+check_index*4,genome.begin()+check_index*4+4,genome.begin()+compare_index*4)) {
        genome.erase(genome.begin()+check_index*4,genome.begin()+check_index*4+4);
        dups[check_index]=compare_index;
        break;
      }
  return dups;
}


// int main() {
//
//
//   Genotype g{0,0,0,1, 0,0,0,2};
//   PhenotypeTable p = PhenotypeTable();
//   //set params for table
//   PhenotypeTable::phenotype_builds=20;
//   PhenotypeTable::UND_threshold=.25;
//   //p.LoadTable(file_path);
//   p.FIXED_TABLE=false;
//
//   IntegerAssembly::min_colour=0; //less than zero allows self-interaction colours
//   IntegerAssembly::max_colour=6; //max colour is useable (i.e. max=4 -> {0,1,0,3, 0,2,0,4})
//
//
//   for(auto a : AssemblePlasticGenotype(g,&p))
//     std::cout<<a<<std::endl;
//
// }
