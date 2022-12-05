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
	// exercises 51.1 to 51.3
	/* 
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

	int netsize = 100;
	int avglinks = 200;

	Web internet(netsize);
	internet.create_random_links(avglinks);	
	
	// exercise 51.5
	vector<int> landing_counts(internet.number_of_pages(), 0);
	for (auto page : internet.all_pages()) {
		cout << "Starting page: " << page -> as_string() << '\n';	
		for (int iwalk=0; iwalk<50; iwalk++){
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
	cout << '\n';
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
	cout << '\n';
	
	// exercise 51.7	
	probability_distribution random_state(internet.number_of_pages());
	random_state.set_random();
	cout << "Random Distribution: " << random_state.as_string() << '\n';
	
	// exercise 51.8
	/*
	probability_distribution test1(internet.number_of_pages());
	test1.set_pvalue(0, 1.0);
	probability_distribution output1 = internet.globalclick(test1);
	cout << "Test 1 PD Input: " << test1.as_string() << '\n';
	cout << "Output of Test 1: " << output1.as_string() << '\n';

	probability_distribution output2 = internet.globalclick(output1);
        cout << "Test 2 PD Input: " << output1.as_string() << '\n';
        cout << "Output of Test 2: " << output2.as_string() << '\n';
	*/

	cout << '\n';
	
	// one trial with global click 1
	probability_distribution random_state2(internet.number_of_pages());
        random_state2.set_random();
	cout << "Input: " << random_state2.as_string() << '\n';
	for (int i = 0; i < 20; i++){
		probability_distribution output3 = internet.globalclick(random_state2);
		// cout << "Output: " << output3.as_string() << '\n';
		random_state2 = output3;
	}
	cout << "Output: " << random_state2.as_string() << '\n';
	cout << '\n';
	
	// global click 1 with numOfTrials random trials
	/* probability_distribution gc1(internet.number_of_pages());
	int numOfTrials = 100;
	for (int j = 0; j < numOfTrials; j++){
		probability_distribution randompd(internet.number_of_pages());
        	randompd.set_random();
        	for (int i = 0; i < 20; i++){
                	probability_distribution outputpd = internet.globalclick(randompd);
                	randompd = outputpd;
        	}
        	for (int k = 0; k < numOfTrials; k++){
			gc1.add_pvalue(k, randompd.get_pvalue(k));
		}	
	}
	gc1.normalize();
	cout << "Output: " << gc1.as_string() << '\n';
	cout << '\n';*/

	//exercise 51.11
	// one trial of global click 2
	probability_distribution random_state3(internet.number_of_pages());
        random_state3.set_random();
	cout << "Input: " << random_state3.as_string() << '\n';
	for (int i = 0; i < 20; i++){
                probability_distribution output4 = internet.globalclick2(random_state3);
                random_state3 = output4;
        }
	cout << "Output: " << random_state3.as_string() << '\n';
	cout << '\n';
	
	// global click 2 with numOfTrials random trials
	/* probability_distribution gc2(internet.number_of_pages());
        for (int j = 0; j < numOfTrials; j++){
                probability_distribution randompd(internet.number_of_pages());
                randompd.set_random();
                for (int i = 0; i < 20; i++){
                        probability_distribution outputpd = internet.globalclick2(randompd);
                        randompd = outputpd;
                }
                for (int k = 0; k < numOfTrials; k++){
                        gc2.add_pvalue(k, randompd.get_pvalue(k));
                }
        }
        gc2.normalize();
        cout << "Output: " << gc2.as_string() << '\n';
	cout << '\n';*/

	// exercise 51.10
	internet.add_pages((avglinks * 4) + 1);

	for (int i = netsize + 1; i < internet.all_pages().size(); i++){
		internet.all_pages()[i]->add_link(internet.all_pages()[netsize]);
	}

	probability_distribution random_state4(internet.number_of_pages());
        random_state4.set_random();
        for (int i = 0; i < internet.number_of_pages() * 20; i++){
                probability_distribution output3 = internet.globalclick(random_state4);
                random_state4 = output3;
        }
	cout << "Output: " << random_state4.as_string() << '\n';	
	
	// page # = netsize is the artificially important page and should be ranked at the top	
	vector<vector<double>> rankedP = random_state4.rankp();
	cout << "Pages in Order by Rank: ";
	for(int i = 0; i < rankedP.size(); i++){
		cout << std::to_string((int)rankedP[i][1]) << ", ";	
	}
	cout << '\n';
	
	// exercise 51.11
	//internet.printMatrix();

	return 0;	
}
