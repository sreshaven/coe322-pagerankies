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
#include <chrono>
using std::shared_ptr;
using std::make_shared;
using landing_clock = std::chrono::high_resolution_clock;
using gc1_clock = std::chrono::high_resolution_clock;
using gc2_clock = std::chrono::high_resolution_clock;

int main(){
	int netsize = 100;
	int avglinks = 200;

	Web internet(netsize);
	internet.create_random_links(avglinks);	
	
	// exercise 51.5
	auto start_time = landing_clock::now();
	vector<int> landing_counts(internet.number_of_pages(), 0);
	for (auto page : internet.all_pages()) {
		for (int iwalk=0; iwalk<50; iwalk++){
			auto endpage = internet.random_walk(page, 2*avglinks);
			landing_counts.at(endpage->global_ID())++;
		}
	}
	cout << '\n';
	auto duration = landing_clock::now()-start_time;
	auto microsec_duration = std::chrono::duration_cast<std::chrono::microseconds>(duration);
	cout <<"LANDING COUNT TIMER: " << microsec_duration.count() << " microsec\n";
	
	// global click 1 with numOfTrials random trials
	start_time = gc1_clock::now();
	probability_distribution gc1(internet.number_of_pages());
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
	cout << '\n';
	duration = gc1_clock::now()-start_time;
	microsec_duration = std::chrono::duration_cast<std::chrono::microseconds>(duration);
	cout << "GC1 CLOCK: " << microsec_duration.count() << " microseconds\n";

	// global click 2 with numOfTrials random trials
	start_time = gc2_clock::now();
	probability_distribution gc2(internet.number_of_pages());
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
	cout << '\n';
	duration = gc2_clock::now()-start_time;
	microsec_duration = std::chrono::duration_cast<std::chrono::microseconds>(duration);
	cout << "GC2 CLOCK: " << microsec_duration.count() << " microsec\n";
	
	return 0;
}
