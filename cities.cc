#include "cities.hh"
#include <string>
#include <math.h>
#include <random>
#include <algorithm>

using namespace std;





double Cities::distance(const Cities::coord_t start, const Cities::coord_t end) const {
  return (pow(pow(start.first - end.first, 2) + pow(start.second - end.second, 2), 0.5));
  //sqrt((x1-x2)^2   +  (y1-y2)^2)
  //Pythagorean theorem!
}


double Cities::total_path_distance(const Cities::permutation_t& ordering) const {
  unsigned int prev = ordering.back(); //The first calculation done is last -> first
  double total_distance = 0.0;
  for (auto i : ordering) { //Simply sums the the distances between the cities in the permutation in order
    total_distance += distance(citylist_[prev], citylist_[i]);
    prev = i;
  }


	/* Handling rounding errors. total_distance would be slightly larger or
	smaller when calculated with an order in reverse of the current shortest,
	leading to duplicate reports of improvement. This doesn't remove all rounding
	errors, but it does equalize them so that any two distances would have the
	same ones, not breaking the < operator. */
	total_distance = std::round(total_distance * 1000) / 1000;


  return total_distance;
}

Cities Cities::reorder(const Cities::permutation_t& ordering) const {
  Cities newCities; //Returns a new city object with the ordering given
  for (auto i : ordering){
    newCities.citylist_.push_back(citylist_[i]);
  }
  return newCities;
}

Cities::permutation_t Cities::random_permutation() const{
	std::random_device generator;

	permutation_t randomList; //Create an empty permutation
	for (unsigned i = 0; i < citylist_.size(); i++){
		randomList.push_back(i); //Populate the permutation with ordered numbers, (0, 1, 2, 3, ... len-1)
	}
	std::shuffle(std::begin(randomList), std::end(randomList), generator);  //Shuffle with random_device
	return randomList;
}

Cities::permutation_t Cities::ordered_permutation() const{ //Same as random_permutation, but without the shuffle.
	permutation_t orderedList;
	for (unsigned i = 0; i < citylist_.size(); i++){
		orderedList.push_back(i);
	}
	return orderedList;
}

//void Cities::input_cities(std::vector<Cities::coord_t> input) { //Used for debugging purposes.
//	citylist_ = input;
//}

ostream& operator<<(ostream &output, Cities& city)
{
	for (auto iterator = begin(city.citylist_); iterator != end(city.citylist_); ++iterator)
	{
    output << (*iterator).first << " " << (*iterator).second << "\n"; //Outputs the cities one by one from citylist with proper formatting
	}
	return output;
}

istream& operator>>(istream& inp, Cities& city)
{
	string line;
    char curr;
	Cities::coord_t tempc;
    bool first = true;

    while(inp.get(curr)) //Gets next character
    {
        if (isdigit(curr)) //If carachter is a number, adds it to string
        {
            line.push_back(curr);
        }
        else
        {
            int num = stoi(line); //if character is not a number, converts string to an int and empties string, and adds resultant int to coordinate
            if (first)
            {
                tempc.first = num;
                first = false;
            }
            else
            {
                tempc.second = num;
                city.citylist_.push_back(tempc);
                first = true;
            }
            line = "";
        }
    }

	return inp;
}
