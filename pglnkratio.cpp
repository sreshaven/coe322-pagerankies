//Names: Sresha Ventrapragada, Amy Manning, Amanda Lee
//UT EID: svv346, alm7377, awl646

#include <iostream>
#include <vector>
#include "page.hpp"
#include "functions.hpp"
#include "web.hpp"
#include "pd.hpp"
#include <memory>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <random>
using std::shared_ptr;
using std::make_shared;


int main(){
  
  int netsize = 20; //number of pages
  int avglinks = 20; //number of links
  
  cout << "Net size (number of pages): " << netsize << '\n';
  cout << "Average number of links: " << avglinks << '\n';
  cout << '\n';
  
  Web internet(netsize);
  internet.create_random_links(avglinks);	
	
  //one trial of global click 2
  probability_distribution random_state3(internet.number_of_pages());
  random_state3.set_random();
  cout << "Input: " << random_state3.as_string() << '\n';
  for (int i = 0; i < 20; i++){
    probability_distribution output4 = internet.globalclick2(random_state3);
    random_state3 = output4;
  }
  cout << "Output: " << random_state3.as_string() << '\n';
  cout << '\n';

  //print adjacency matrix
  internet.printMatrix();	
  cout << '\n';
	
  //page-ranking
  vector<vector<double>> rankedP = random_state3.rankp();
  cout << "Pages in Order by Rank: ";
  for(int i = 0; i < rankedP.size(); i++){
    cout << std::to_string((int)rankedP[i][1]) << ", ";	
  }
  cout << '\n';
  
  return 0;	
}
