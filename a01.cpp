#include<iostream>
#include<string>
#include<iostream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
//compare state data bool function
using namespace std;
struct state* allocate_states(int); //allocates space for states
void read_state_data(struct state*, int, std::ifstream&); //read data from text file and put into state struct of array
struct county* allocate_counties(int);//allocates space for counties
void read_county_data(struct county*, int, std::ifstream&);//read data from text file and put into county struct of array
void free_state_data(struct state*, int);//free memory for dynamic struct of arrays
void print(struct state*, int);
void menu(struct state*, int);
void print_hightest_med_income(struct state*, int);
void print_lowest_med_income(struct state*, int);
bool cmp_state_desc_med_income(const struct state&, const struct state&);
bool cmp_state_asc_med_income(const struct state&, const struct state&);
bool cmp_state_desc_unemployed_2015(const struct state&, const struct state&);
bool cmp_state_asc_unemployed_2015(const struct state&, const struct state&);
void print_hightest_unemployed_2015(struct state*, int);
void print_lowest_unemployed_2015(struct state*, int);

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
	//cout << n_states << endl;
	struct state* states_data = allocate_states(n_states);
	read_state_data(states_data, n_states, infile);
	//cout << states_data[0].name << " " << states_data[0].unemployed_2015 << endl;
	//cout << states_data[1].name << " " << states_data[1].unemployed_2015 << endl;
	menu(states_data, n_states);

}

void selectionSort(struct state* states_data, int n_states)
{
    int i, j, min_idx;
 
    // One by one move boundary of unsorted subarray
    for (i = 0; i < n_states-1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < n_states; j++)
          if (states_data[j].unemployed_2015-states_data[j].unemployed_2007 < states_data[min_idx].unemployed_2015-states_data[min_idx].unemployed_2007)
            min_idx = j;
 
        // Swap the found minimum element with the first element
        swap(states_data[min_idx], states_data[i]);
    }
}

void selectionSortCounties(struct state* state, int n_counties)
{
    int i, j, min_idx;
 
    // One by one move boundary of unsorted subarray
    for (i = 0; i < n_counties-1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < n_counties; j++)
          if (state->counties[j].unemployed_2015 - state->counties[j].unemployed_2007 < state->counties[min_idx].unemployed_2015 - state->counties[min_idx].unemployed_2007)
            min_idx = j;
 
        // Swap the found minimum element with the first element
        swap(state->counties[min_idx], state->counties[i]);
    }
}

void menu(struct state* states_data, int n_states) {
	int choice;
	cout << "0-hightest med_income" << endl << "1-lowest med_income" << endl << "2-highest_unemployed_2015" << endl << "3-lowest_unemployed_2015: " << endl << "4-states_med_income_in_order"<<endl<<"5-rate chenge_of_unemployed(07~15)" << endl; "ur choice: ";
	cin >> choice;
	if (choice == 0) {
		print_hightest_med_income(states_data, n_states);
	}
	else if (choice == 1) {
		print_lowest_med_income(states_data, n_states);
	}
	else if (choice == 2) {
		print_hightest_unemployed_2015(states_data, n_states);
	}
	else if (choice == 3) {
		print_lowest_unemployed_2015(states_data, n_states);
	}
	else if (choice == 4) {
    sort(states_data, states_data + n_states, cmp_state_desc_med_income);
		for (int i = 0; i < n_states; i++) {
			cout << states_data[i].name << " " << states_data[i].med_income << endl;
		}
	}
 	else if (choice == 5) {
     selectionSort(states_data, n_states);
     for(int i = 0; i < n_states; i++){ //testing
       cout << states_data[i].name << " " << states_data[i].unemployed_2015 << " " << states_data[i].unemployed_2007 << "\n";
     }
	}
}

//////////
bool cmp_state_desc_med_income(const struct state& s1, const struct state& s2) {
	return (s1.med_income > s2.med_income);
}

bool cmp_state_asc_med_income(const struct state& s1, const struct state& s2) {
	return (s1.med_income < s2.med_income);
}

bool cmp_unemployment_income(const struct state& s1, const struct state& s2){
  return s1.unemployed_2015-s1.unemployed_2007 < s2.unemployed_2015-s2.unemployed_2007;
}

void sort_states_by_unemployment_change(struct state* states_data, int n_states){
  sort(states_data, states_data + n_states, cmp_unemployment_income);
}
//hightest med income
void print_hightest_med_income(struct state* states_data, int n_states) {
	sort(states_data, states_data + n_states, cmp_state_desc_med_income);
	cout << states_data[0].name << " " << states_data[0].med_income << endl;
}
//lowest med income
void print_lowest_med_income(struct state* states_data, int n_states) {
	sort(states_data, states_data + n_states, cmp_state_asc_med_income);
	cout << states_data[0].name << " " << states_data[0].med_income << endl;
}
//highest unemployed
bool cmp_state_desc_unemployed_2015(const struct state& s1, const struct state& s2) {
	return (s1.unemployed_2015 > s2.unemployed_2015);
}

bool cmp_state_asc_unemployed_2015(const struct state& s1, const struct state& s2) {
	return (s1.unemployed_2015 < s2.unemployed_2015);
}

void print_hightest_unemployed_2015(struct state* states_data, int n_states) {
	sort(states_data, states_data + n_states, cmp_state_desc_unemployed_2015);
	cout << states_data[0].name << " " << states_data[0].unemployed_2015 << endl;
}
//lowest unemployed
void print_lowest_unemployed_2015(struct state* states_data, int n_states) {
	sort(states_data, states_data + n_states , cmp_state_asc_unemployed_2015);
	cout << states_data[0].name << " " << states_data[0].unemployed_2015 << endl;
}


///////
//test function
void print(struct state* states_data, int n_states) {
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
