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
    }while(base==base_C); //don't allow mutations to be the same as the initial colour
  }
}

std::vector<Phenotype_ID> AssemblePlasticGenotype(Genotype genotype,PhenotypeTable* pt) {
    IntegerAssembly::StripNoncodingGenotype(genotype);
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
      else //assembly was unbound
        Phenotype_IDs.emplace_back(0,0);
      interacting_indices.clear();
    }

    pt->RelabelPhenotypes(Phenotype_IDs);
    std::map<Phenotype_ID,uint16_t> ID_counter=pt->PhenotypeFrequencies(Phenotype_IDs);
   
    Phenotype_IDs.clear();
    for(auto& kv : ID_counter) { //add all phenotypes observed 
      Phenotype_IDs.emplace_back(kv.first);
    }
    return Phenotype_IDs;
  

  }


int main() {

  
  Genotype g{0,0,0,1, 0,-1,0,2};
  PhenotypeTable p = PhenotypeTable();
  //set params for table
  PhenotypeTable::phenotype_builds=20;
  PhenotypeTable::UND_threshold=.5;
  //p.LoadTable(file_path);
  p.FIXED_TABLE=false;

  IntegerAssembly::min_colour=0; //less than zero allows self-interaction colours
  IntegerAssembly::min_colour=6; //max colour is useable (i.e. max=4 -> {0,1,0,3, 0,2,0,4})
  
  
  

  for(auto a : AssemblePlasticGenotype(g,&p))
    std::cout<<a<<std::endl;

}


