//Names: Sresha Ventrapragada, Amy Manning, Amanda Lee
//UT EID: svv346, alm7377, awl646

#include <iostream>
#include <vector>
#include "page.hpp"
#include "link.hpp"
#include "web.hpp"
#include <memory>
#include <vector>
using std::shared_ptr;
using std::make_shared;


int main(){
	
	// exercise 51.1
	auto homepage = make_shared<Page>("My Home Page");
	cout << "Homepage has no links yet: " << '\n';
	cout << homepage -> as_string() << '\n';

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
	
	}
	return 0;
}
