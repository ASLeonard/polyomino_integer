#include "assembly_model.hpp"

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

Phenotype_ID BasicPolyominoAssemblyOutcome(const Genotype& genotype,PhenotypeTable* pt) {
    const std::vector<std::pair<InteractionPair,double> > edges = IntegerAssembly::GetActiveInterfaces(genotype);

    if(edges.empty())
      return Phenotype_ID{1,0};

    Phenotype phen;
    std::set<Phenotype_ID> Phenotype_IDs;

    for(uint16_t nth=0;nth<pt->phenotype_builds;++nth) {
      [[maybe_unused]]auto [assembly_information,interacting_indices]=IntegerAssembly::AssemblePolyomino(edges);
      if(!assembly_information.empty()) {   
        phen=GetPhenotypeFromGrid(assembly_information);
        Phenotype_IDs.emplace(pt->GetPhenotypeID(phen));
        if(Phenotype_IDs.size()>1)
          return UNBOUND_pid;//nondeterministic
      }
      else {
        pt->ClearIncomplete();
        return UNBOUND_pid;
      }        
    }
    std::vector<Phenotype_ID> Phenotype_IDs_V(Phenotype_IDs.begin(),Phenotype_IDs.end());
    pt->RelabelPIDs(Phenotype_IDs_V,true);
    return Phenotype_IDs_V.front();
}


void analyseInputs(int run,PhenotypeTable* pt) {

  std::string pt_fname = "PhenotypeTable_Run" + std::to_string(run) +".txt";
  pt->LoadTable(pt_fname);
  std::vector<Genotype> genomes;
    
  std::ifstream fin("Genotype_Inputs_Run" + std::to_string(run) + ".txt");
  std::string temp;
  while (std::getline(fin, temp)) {
    std::istringstream buffer(temp);
    genomes.emplace_back(std::istream_iterator<interface_type>(buffer), std::istream_iterator<interface_type>());
  }

  std::ofstream fout("Assembly_Outputs_Run" + std::to_string(run) + ".txt");
  for(auto& genotype : genomes) {
    auto pid = BasicPolyominoAssemblyOutcome(genotype,pt);
    fout << +pid.first << " " << +pid.second<<"\n";
  }
  pt->PrintTable(pt_fname);
}
int main(int argc, char* argv[]) {
  if(argc < 2) {
    std::cout<<"Too few args."<<std::endl;
    return 1;
  }

  PhenotypeTable pt = PhenotypeTable(std::stoi(argv[1]),std::stod(argv[2]));
  pt.FIXED_TABLE=false;

  int run = std::stoi(argv[3]);  
  
  Phenotype::DETERMINISM_LEVEL = 1; //set to 2 for subunit determinism
  Phenotype::FREE_POLYOMINO = true; //set to false for chiral distinct polyomino
  
  analyseInputs(run,&pt);
  //std::cout<<"Finished analysing"<<std::endl;

}


