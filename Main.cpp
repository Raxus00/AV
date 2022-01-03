#include "av.hpp"

//Rasmus Andersen   rasmus.andersen00@gmail.com
//Erik Nordahl  eriknordahl23@gmail.com

int main(int argc, char *argv[])
{
  if(argc!=2)
  {
    std::cout<<"Wrong number of arguments"<<std::endl;

  }
  else
  {
    remove("dv1620.log");
    AV av;
    std::vector<std::string> datavector = av.read();
    
    std::vector<std::string> signatures = av.read_signatures(datavector);
    
    std::vector<std::string> virusname = av.read_virusname(datavector);
    
    av.treverase(argv[1], datavector, signatures, virusname);
  }
  
}
