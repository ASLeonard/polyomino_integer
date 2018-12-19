#include "integer_model.hpp"
thread_local std::mt19937 RNG_Engine(std::random_device{}());



double IntegerAssembly::InteractionMatrix(const int face_1,const int face_2) {
  if(face_1==0 || face_2==0)
	return 0;
  else
	return (face_1+(face_1%2?1:-1))==face_2;
}

int main() {

std::cout<<"hi"<<std::endl;

std::vector<int> g{0,0,0,0};//{0,0,1,0,2,2,2,2};
    const std::vector<std::pair<InteractionPair,double> > edges = IntegerAssembly::GetActiveInterfaces(g);

    std::vector<int8_t> assembly_information;
    Phenotype phen;
std::set<InteractionPair > interacting_indices;
   assembly_information=IntegerAssembly::AssemblePolyomino(edges,interacting_indices);
phen=GetPhenotypeFromGrid(assembly_information);
PrintShape(phen);

}


