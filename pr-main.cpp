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
#include <iomanip>
using std::shared_ptr;
using std::make_shared;


int main(){
	// srand(time(NULL));

	/* 
	// exercise 51.1
	auto homepage = make_shared<Page>("My Home Page");

	// add links to the page as a vector, method click follows the link
	auto utexas = make_shared<Page>("University Home Page");
	homepage -> add_link(utexas);
	auto searchpage = make_shared<Page>("google");
	homepage -> add_link(searchpage);
	auto aboutAmy = make_shared<Page>("About Amy");
	homepage -> add_link(aboutAmy);
	auto aboutSresha = make_shared<Page>("About Sresha");
	homepage -> add_link(aboutSresha);
	auto aboutAmanda = make_shared<Page>("About Amanda");
	homepage -> add_link(aboutAmanda);
	auto contact = make_shared<Page>("Contact");
	homepage -> add_link(contact);
	cout << homepage -> as_string()<<'\n';

	// random click
	for (int iclick=0; iclick < 20; iclick++){
		auto newpage = homepage -> random_click();
		cout << "To: " << newpage -> as_string() << '\n';
	
	} */
	

	int netsize = 10;
	int avglinks = 20;

	Web internet(netsize);
	internet.create_random_links(avglinks);	
	
	// exercise 51.5
	vector<int> landing_counts(internet.number_of_pages(), 0);
	for (auto page : internet.all_pages()) {
		cout << "Starting page: " << page -> as_string() << '\n';	
		for (int iwalk=0; iwalk<5; iwalk++){
			auto endpage = internet.random_walk(page, 2*avglinks);
			landing_counts.at(endpage->global_ID())++;
		}
	}
	cout << "Landing counts: ";	
	for (int i = 0; i < landing_counts.size(); i++){
		if (i == landing_counts.size() - 1){
			cout << landing_counts.at(i) << '\n';
		} else {
			cout << landing_counts.at(i) << ',';
		}
	}
	
	// exercise 51.6
	for (int i = 0; i < internet.all_pages().size(); i++){
		vector<int> distances = internet.sssp(internet.all_pages()[i]);
        	cout << "Distances from " << internet.all_pages()[i]->getName() << ": ";
        	for (int i = 0; i < distances.size(); i++){
                	if (i == distances.size() - 1){
                        	cout << distances.at(i) << '\n';
                	} else {
                        	cout << distances.at(i) << ',';
                	}
        	}
	}
	
	cout << std::fixed;
 	cout.precision(4);
	// exercise 51.7	
	probability_distribution random_state(internet.number_of_pages());
	random_state.set_random();
	cout << "Initial Distribution: " << random_state.as_string() << '\n';
	
	// exercise 51.8
	probability_distribution test1(internet.number_of_pages());
	test1.set_pvalue(0, 1.0);
	probability_distribution output1 = internet.globalclick(test1);
	cout << "Test 1 PD Input: " << test1.as_string() << '\n';
	cout << "Output of Test 1: " << output1.as_string() << '\n';

	probability_distribution output2 = internet.globalclick(output1);
        cout << "Test 2 PD Input: " << output1.as_string() << '\n';
        cout << "Output of Test 2: " << output2.as_string() << '\n';
	
	probability_distribution random_state2(internet.number_of_pages());
        random_state2.set_random();
	for (int i = 0; i < netsize * 1.5; i++){
		probability_distribution output3 = internet.globalclick(random_state2);
		cout << "Output: " << output3.as_string() << '\n';
		random_state2 = output3;
	}
	
	// exercise 51.10
	internet.add_pages((avglinks * 4) + 1);

	for (int i = netsize + 1; i < internet.all_pages().size(); i++){
		internet.all_pages()[i]->add_link(internet.all_pages()[netsize]);
	}

	/* for (auto page : internet.all_pages()) {
                cout << "Starting page: " << page -> as_string() << '\n';
        } */

	probability_distribution random_state3(internet.number_of_pages());
        random_state3.set_random();
        for (int i = 0; i < 5; i++){
                probability_distribution output3 = internet.globalclick(random_state2);
                random_state3 = output3;
        }
	cout << "Output: " << random_state3.as_string() << '\n';	
		
	vector<vector<double>> rankedP = random_state3.rankp();
	cout << "Pages in Order by Rank: ";
	for(int i = 0; i < rankedP.size(); i++){
		cout << std::to_string((int)rankedP[i][1]) << ", ";	
	}
	cout << '\n';
	return 0;
	
}
