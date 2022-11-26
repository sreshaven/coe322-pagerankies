//Names: Sresha Ventrapragada, Amy Manning, Amanda Lee
//UT EID: svv346, alm7377, awl646

#include <iostream>
#include <vector>
#include "page.hpp"
#include "link.hpp"
#include "web.hpp"
#include "pd.hpp"
#include <memory>
#include <vector>
#include <ctime>
#include <cstdlib>
using std::shared_ptr;
using std::make_shared;


int main(){
	srand(time(NULL));
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
	
	// internet.random_walk(internet.all_pages()[0], 5);
	// exercise 6.5
	vector<int> landing_counts(internet.number_of_pages(), 0);
	for (auto page : internet.all_pages()) {
		cout << "Starting page: " << page -> as_string() << '\n';	
		for (int iwalk=0; iwalk<5; iwalk++){
			auto endpage = internet.random_walk(page, 2*avglinks);
			landing_counts.at(endpage->global_ID())++;
		}
	}
	
	for (int i = 0; i < landing_counts.size(); i++){
		if (i == landing_counts.size() - 1){
			cout << landing_counts.at(i) << '\n';
		} else {
			cout << landing_counts.at(i) << ',';
		}
	}
	
	// exercise 6.6
	vector<int> distances = internet.sssp(internet.all_pages()[0]);
	cout << "Distances from page0: " << '\n';
	for (int i = 0; i < distances.size(); i++){
		if (i == distances.size() - 1){
                        cout << distances.at(i) << '\n';
                } else {
                        cout << distances.at(i) << ',';
                }
	}

	
	probability_distribution random_state(internet.number_of_pages())
	random_state.set_random();
	cout << "Initial distribution: " << random_state.as_string() << '\n';	

	return 0;
}
