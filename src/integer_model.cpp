#include "integer_model.hpp"


double IntegerAssembly::InteractionMatrix(const uint8_t face_1,const uint8_t face_2) {
  if(face_1==0 || face_2==0)
	return 0;
  else
	return (face_1+(face_1%2?1:-1))==face_2;
}
void IntegerAssembly::Mutation(Genotype& genotype) {
  for(auto& base : genotype) {
    const auto base_C=base;
    do {
      base=GenRandomSites();
    }while(base==base_C);
  }
}

int main() {


  std::vector<int> g{0,0,1,0, 2,2,2,2};
  const std::vector<std::pair<InteractionPair,double> > edges = IntegerAssembly::GetActiveInterfaces(g);

  std::vector<int8_t> assembly_information;
  Phenotype phen;
  std::set<InteractionPair > interacting_indices;
  assembly_information=IntegerAssembly::AssemblePolyomino(edges,interacting_indices);
  phen=GetPhenotypeFromGrid(assembly_information);
  std::cout<<phen<<std::endl;

}


