#include "integer_model.hpp"

double IntegerAssembly::InteractionMatrix(const interface_type face_1,const interface_type face_2) {
  if(face_1==0 || face_2==0)
    return 0;
  if(face_1<0)
    return face_1==face_2;
  return (face_1+(face_1%2?1:-1))==face_2;
}

void IntegerAssembly::Mutation(Genotype& genotype) {
  for(auto& base : genotype) {
    const interface_type base_C=base;
    do {
      base=GenRandomSites();
    }while(base==base_C);
  }
}

std::vector<Phenotype_ID> AssemblePlasticGenotype(Genotype& genotype,PhenotypeTable* pt) {
    IntegerAssembly::StripNoncodingGenotype(genotype);
    const std::vector<std::pair<InteractionPair,double> > edges = IntegerAssembly::GetActiveInterfaces(genotype);
    
    std::vector<int8_t> assembly_information;
    Phenotype phen;
    std::vector<Phenotype_ID> Phenotype_IDs;
    Phenotype_IDs.reserve(pt->phenotype_builds);
    std::set<InteractionPair > interacting_indices;

    for(uint16_t nth=0;nth<pt->phenotype_builds;++nth) {
      assembly_information=IntegerAssembly::AssemblePolyomino(edges,interacting_indices);
      if(assembly_information.size()>0) {
        phen=GetPhenotypeFromGrid(assembly_information);
        Phenotype_IDs.emplace_back(pt->GetPhenotypeID(phen));
      }
      else
        Phenotype_IDs.emplace_back(0,0);
      interacting_indices.clear();
    }

    pt->RelabelPhenotypes(Phenotype_IDs);

    std::map<Phenotype_ID,uint16_t> ID_counter=pt->PhenotypeFrequencies(Phenotype_IDs);
    
    Phenotype_IDs.clear();
    for(auto& kv : ID_counter) {
      std::cout<<+kv.first.first<<" "<<+kv.first.second<<std::endl;
      Phenotype_IDs.emplace_back(kv.first);
    }
    return Phenotype_IDs;
  

  }


int main() {

  
  Genotype g{0,0,0,1, 0,-1,0,2};
  PhenotypeTable p = PhenotypeTable();
  p.phenotype_builds=20;
  p.UND_threshold=.5;
  //p.LoadTable(file_path);
  p.FIXED_TABLE=true;
  

  for(auto a : AssemblePlasticGenotype(g,&p))
    std::cout<<+a.first<<" "<<+a.second<<std::endl;

}


