#include<iostream>
#include<string>
#include<iostream>
#include <fstream>

using namespace std;
struct state* allocate_states(int); //allocates space for states
void read_state_data(struct state*, int, std::ifstream&); //read data from text file and put into state struct of array
struct county* allocate_counties(int);//allocates space for counties
void read_county_data(struct county*, int, std::ifstream&);//read data from text file and put into county struct of array
void free_state_data(struct state*, int);//free memory for dynamic struct of arrays
void print(struct state*, int);

struct county {
	std::string name;
	float unemployed_2007;
	float unemployed_2015;
	int med_income;
};

struct state {
	std::string name;
	float unemployed_2007;
	float unemployed_2015;
	int med_income;
	struct county* counties;
	int n_counties;
};



int main(int argc, char* argv[]) {
	ifstream infile;
	infile.open("testdata.txt");
	if (infile.fail()) {
		cout << "fail to read" << endl;
		return 1;
	}
	cout << "read success" << endl;
	int n_states;
	infile >> n_states;
	cout << n_states << endl;
	struct state* states_data = allocate_states(n_states);
	read_state_data(states_data, n_states, infile);
	//print(states_data, n_states);

}

void print(struct state* states_data, int n_states) {//to test ....
	for (int i = 0; i < n_states; i++) {
		cout << states_data[i].counties->name << endl;
	}
}

struct state* allocate_states(int states_quantities) {
	struct state* states_data_space = new struct state[states_quantities];
	return states_data_space;
}

struct county* allocate_counties(int num_counties) {
	struct county* counties = new struct county[num_counties];
	return counties;
}

void read_county_data(struct county* counties, int n_counties, std::ifstream& infile) {
	for (int i = 0; i < n_counties; i++) {
		infile >> counties[i].name >> counties[i].unemployed_2007 >> counties[i].unemployed_2015 >> counties[i].med_income;
	}
}

void read_state_data(struct state* states_data, int n_states, std::ifstream& infile) {
	for (int i = 0; i < n_states; i++) {
		infile >> states_data[i].name >> states_data[i].unemployed_2007 >> states_data[i].unemployed_2015 >> states_data[i].med_income >> states_data[i].n_counties;
		states_data[i].counties = allocate_counties(states_data[i].n_counties);
		read_county_data(states_data[i].counties, states_data[i].n_counties, infile);
	}

}