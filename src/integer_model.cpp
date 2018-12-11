#include "integer_model.hpp"
thread_local std::mt19937 RNG_Engine(std::random_device{}());
/*model_params::DETERMINISM_LEVEL*/

namespace model_params
{
uint8_t FREE_POLYOMINO=2, DETERMINISM_LEVEL=3;
  uint16_t phenotype_builds=10;
  double UND_threshold=0.2;
  bool FIXED_TABLE=false;
}


double IntegerAssembly::InteractionMatrix(const int face_1,const int face_2) {
  if(face_1==0 || face_2==0)
	return 0;
  else
	return face_1+(face_1%2?1:-1)==face_2;
}

int main() {

std::cout<<"hi"<<std::endl;

std::vector<int> g{0,0,1,0,2,2,2,2};
    const std::vector<std::pair<interaction_pair,double> > edges = IntegerAssembly::GetEdgePairs(g);

    std::vector<int8_t> assembly_information;
    Phenotype phen;
std::set<interaction_pair > interacting_indices;
   assembly_information=IntegerAssembly::AssemblePolyomino(edges,1,100,interacting_indices);
phen=GetPhenotypeFromGrid(assembly_information);
PrintShape(phen);

}


