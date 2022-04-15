#include "cities.hh"
#include <fstream>

int main(int argc, char** argv) {
  if (argc < 2){
    std::cerr << "Error: Too few inputs\n";
    return -1;
  }
  if (argc > 2){
    std::cerr << "Error: Too many inputs\n"; //This might break part 8, feel free to delete
    return -2;
  }

  std::string file = argv[1];
  std::ifstream ifile(file);
  if (!ifile.is_open()){
    std::cerr << "Error: Can't open file " + file + ".\n";
    return -3;
  }

/*  file = argv[2];
  std::ofstream speedfile(file);
  if (!speedfile.is_open()){
    std::cerr << "Error: Can't open file " + file + ".\n";
    return -3;
  }*/

  Cities fastestRoute;
  ifile >> fastestRoute;

  unsigned int numberIterations = 1000000; //Note: Set to 100,000,000 in the submitted sample
  double shortestDistance = fastestRoute.total_path_distance(fastestRoute.ordered_permutation());

  cout << "1   " << shortestDistance << "\n";
  for (unsigned int i = 2; i <= numberIterations; i++){
    auto newPermutation = fastestRoute.random_permutation();
    double newDistance = fastestRoute.total_path_distance(newPermutation);
    if (newDistance < shortestDistance){                          //If this route is the new shortest,
      fastestRoute = fastestRoute.reorder(newPermutation);        //Then set it as the new shortest.
      shortestDistance = newDistance;
      cout << i << "   " << shortestDistance << "\n";
    }
  }


  file = "shortest.tsv";
  std::ofstream ofile(file);
  ofile << fastestRoute;




  std::cout << "Program terminated.\n";
  return 0;
}
