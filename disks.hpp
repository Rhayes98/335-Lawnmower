///////////////////////////////////////////////////////////////////////////////
// disks.hpp
//
// Definitions for two algorithms that each solve the alternating disks
// problem.
//
// As provided, this header has four functions marked with TODO comments.
// You need to write in your own implementation of these functions.
//
///////////////////////////////////////////////////////////////////////////////

// Personal Note, size_t stands for unsigned integer value, used alot in this program
// also: teacher seems to have forgotten the TODO comments, added them back where I think they should go
#pragma once



#include <algorithm>
#include <cassert>
#include <cstddef>
#include <sstream>
#include <string>
#include <vector>
#include <functional>
#include <iostream>

enum disk_color { DISK_LIGHT, DISK_DARK};

class disk_state {
private:
  std::vector<disk_color> _colors;	// the private vector we are working on, _colors is used to store and read disk colors

public:
  disk_state(size_t light_count)	// create list, will make (light, dark) pairs in the number given
    : _colors(light_count * 2, DISK_LIGHT) {

    assert(light_count > 0);

    for (size_t i = 1; i < _colors.size(); i += 2) {
      _colors[i] = DISK_DARK;
    }
  }

  bool operator== (const disk_state& rhs) const {				// custom operator "==", will compare values in _colors and given disk_state
    return std::equal(_colors.begin(), _colors.end(), rhs._colors.begin());
  }

  size_t total_count() const {		// total_count() will return size of _colors
    return _colors.size();
  }

  size_t light_count() const {		// light_count() will return number of lights, it's actually cheating
    return total_count() / 2;
  }

  size_t dark_count() const {		// dark_count() is literally the same as light_count
    return light_count();
  }

  bool is_index(size_t i) const {	// is_index(size_t) will compare given number with size of the vector, true if less
  					// this is to see if the given number has exceeded the size of the vector we are working on
    return (i < total_count());
  }

  disk_color get(size_t index) const {		// get(size_t index) will get the color at _colors[index] for the given index
    assert(is_index(index));
    return _colors[index];
  }

  void swap(size_t left_index) {		// swap(size_t) will swap the given index with it's rightward neighbor in _colors
    assert(is_index(left_index));
    auto right_index = left_index + 1;
    assert(is_index(right_index));
    std::swap(_colors[left_index], _colors[right_index]);
  }

  std::string to_string() const {		// to_string() will create and return a string of the current values of _colors
    std::stringstream ss;
    bool first = true;
    for (auto color : _colors) {
      if (!first) {
        ss << " ";
      }

      if (color == DISK_LIGHT) {
        ss << "L";
      } else {
        ss << "D";
      }

      first = false;
    }
    return ss.str();
  }

  // Return true when this disk_state is in alternating format. That means
  // that the first disk at index 0 is light, the second disk at index 1
  // is dark, and so on for the entire row of disks.
  bool is_initialized() const {
      for (size_t i = 0; i < total_count(); i++){     //check each position before function
        if (i % 2 == 0){                              //check even position --> should be light
            if (_colors[i] == DISK_DARK) {
              return false;
            }
        } else {                                      //check odd position --> should be dark
            if (_colors[i] == DISK_LIGHT) {
              return false;
            }
        }
      }

      return true;
  }

  // Return true when this disk_state is fully sorted, with all light disks on
  // the left (low indices) and all dark disks on the right (high indices).
  // TODO... done
  bool is_sorted() const {
  
      // we want to iterate through the disk_state, seeing if it is sorted properly
      // read through the list one half at a time, if there are any unexpected values return false, otherwise return true
      
      for (size_t i = 0; i < light_count(); i++) {	// iterator for our vector, want to count number of lights in the first half, then number of darks in the second, if either don't match expected return false, otherwise return true
      		if( _colors[i] != DISK_LIGHT ) {
      			return false;
      		}
      }
      	
      for (size_t i = light_count(); i < _colors.size(); i++) {
      		if( _colors[i] != DISK_DARK ) {
      			return false;
      		}
      }
      
      return true;
  }
};

// Data structure for the output of the alternating disks problem. That
// includes both the final disk_state, as well as a count of the number
// of swaps performed.
class sorted_disks {
private:
  disk_state _after;
  unsigned _swap_count;

public:

  sorted_disks(const disk_state& after, unsigned swap_count)
    : _after(after), _swap_count(swap_count) { }

  sorted_disks(disk_state&& after, unsigned swap_count)
    : _after(after), _swap_count(swap_count) { }

  const disk_state& after() const {
    return _after;
  }

  unsigned swap_count() const {
    return _swap_count;
  }
};

// Algorithm that sorts disks using the alternate algorithm.
// TODO...
// changed name of variable "before" to "state"
sorted_disks sort_alternate(const disk_state& state) {
	int numOfSwap = 0;                                                                      //record # of step swap

	// we want to implement our alternate sorting algorithm as seen in the .pdf, also want to record the number of swaps we made
	// something wrong with the way we're iterating through it
	for (size_t j = 0; j <= state.light_count(); j++) {
		if (state.get(j) != state.get(j+1)) {
			//state.swap(j);
			numOfSwap++;
		}
	}
	/*
	for (int j = 0; j <= before.light_count(); j ++){
		for (size_t i = 0; i <= before.total_count(); i++) {
			if (before.get(i) == before.get(i+1) ) {
			} else {
				//after.swap(i);
				numOfSwap++;
			}
		} // end first for loop
		
		for (size_t i = 0; j <= before.light_count() + 1; i++) {
			if (before.get(i) == before.get(i+1) ) {
			} else {
				//before.swap(i)
				numOfSwap++;
			}
		} // end second for loop
	} // end master for loop
	*/
	// ditching this section because otherwise the code won't compile, can't fix it in time
  	return sorted_disks(disk_state(state), numOfSwap); // what the hell is going on here, where the hell is this "state", why are we making a new state
}


// Algorithm that sorts disks using the lawnmower algorithm.
// TODO...
sorted_disks sort_lawnmower(const disk_state& state) {
  	// using disk_state& before
  	
  	int numOfSwap = 0;
  	// we want to implement our lawnmower algorithm here
  	// bit of a rub, teacher already gave us a swap function, going to have to be tricky with it
  	/*
  	for ( size_t j = 0; j <= before.light_count(); j++ ) {
  		// compare forward
  		for (size_t i = 0; i <= before.total_count() - 1; i++) {
  			if ( before.get(i) == before.get(i+1) ) {
  			} else {
  				//swap the values, how the hell do I do that
  				//before.swap(i);
  				numOfSwap++;
  			}
  		} // end forward loop
  		
  		for (size_t i = before.total_count(); i >= 0; i--) {
  			if ( before.get(i) == before.get(i-1) ) {
  			} else {
  				before.swap(i=1);
  				numOfSwap++;
  			}
  		} // end backward loop
  	} // end master for loop
	*/
  return sorted_disks(disk_state(state), numOfSwap);	// seriously what the hell
}


// I have actually no idea why this isn't working, we get passed a state by reference, we operate on it (incrementing num of swaps as we go), and then return what we got
// for whatever reason how I'm trying to operate isn't working and I can't fix it (in time)
// I have no clue what "state" is supposed to be in this program. we are passed before, we have _after as private in sorted_disks
// I have no idea what I'm doing and deserve whatever grade I get
