// Jacob Martin 
// CUNY ID: 23802318
// Few comments describing the class Points2D

#ifndef CSCI335_HOMEWORK1_POINTS2D_H_
#define CSCI335_HOMEWORK1_POINTS2D_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>

namespace teaching_project {

// Place comments that provide a brief explanation of the class,
// and its sample usage.
template<typename Object>
class Points2D {
public:
  // Default "big five" -- you have to alter them for your assignment.
  // That means that you will remove the "= default" statement.
  //  and you will provide an implementation.

  // Zero-parameter constructor.
  // Set size to 0.
  Points2D()
  {
    this->sequence_ = nullptr; //setting the sequence of points to null
    this->size_ = 0; //setting size for the object to 0
  }

  // Copy-constructor.
  Points2D(const Points2D &rhs)
  {
    this->size_ = rhs.size_; //copying the size of the object passed to the current object
    this->sequence_ = new std::array<Object, 2>{size_}; //allocating new space and creating a new araray with size of object passed
    for(size_t i; i < rhs.size_; i++) 
    {
      this->sequence_[i][0] = rhs[i][0];
      this->sequence_[i][1] = rhs[i][1];
    }  
  }

  // Copy-assignment. If you have already written
  // the copy-constructor and the move-constructor
  // you can just use:
  // {
  // Points2D copy = rhs; 
  // std::swap(*this, copy);
  // return *this;
  // }
  Points2D& operator=(const Points2D &rhs)
  {
    Points2D copy = rhs; //creating new object that copies the object that was passed
    std::swap(*this, copy); //swapping the copy object's array and size for the current object
    return *this; //returning the new object with copied variables
  }

  // Move-constructor.
  Points2D(Points2D &&rhs) : sequence_{std::move(rhs.sequence_)}, size_{std::move(rhs.size_)} //setting the object's variables to the object passed variables
  {
    rhs.sequence_ = nullptr; //setting the object passed variables to null
    rhs.size_ = 0; //setting the object's passed size to 0
  }

  // Move-assignment.
  // Just use std::swap() for all variables.
  Points2D& operator=(Points2D &&rhs)
  {
    if (this != &rhs) //if they are not the same object then swap the two object's variables
    {
      std::swap(this->sequence_, rhs.sequence_); //swapping the object passed array with the current object 
      std::swap(this->size_, rhs.size_); //swapping the object passed size with the current object
    }
    return *this; //returning the object with the new swapped variables
  }

  ~Points2D()
  {
    if(size_ > 0) //if there is anything to deallocate
    {
      delete sequence_; //deallocating the pointer to the object's array
    }
  }

  // End of big-five.

  // One parameter constructor.
  Points2D(const std::array<Object, 2>& item) 
  {
    size_ = 1; //setting the size to the new object to 1
    sequence_ = new std::array<Object,2>{item}; //creating new array for the object
  }

  size_t size() const 
  {
      return size_; //returning the size of the object
  }

  // @location: an index to a location in the sequence.
  // @returns the point at @location.
  // const version.
  // abort() if out-of-range.
  const std::array<Object, 2>& operator[](size_t location) const 
  {
    if (location > size_) //if the location is not within the size of the array then abort
      abort();
    return sequence_[location]; //if it is in the array then return the array point that the location is specifying
  }

  //  @c1: A sequence.
  //  @c2: A second sequence.
  //  @return their sum. If the sequences are not of the same size, append the
  //    result with the remaining part of the larger sequence.
  friend Points2D operator+(const Points2D &c1, const Points2D &c2) 
  {
    Points2D res;
    if (c1.size_ > c2.size_) //comparing the sizes, and the biggest size is used for new object
      res.size_ = c1.size_;
    else
      res.size_ = c2.size_;
    res.sequence_ = new std::array<Object, 2>[res.size_]; //creating a new array
    for (size_t i = 0; i < res.size_; i++) 
    {
        if(i<c1.size_ && i<c2.size_) //if the loop is still in bounds of either array
        {
            res.sequence_[i][0] = c1.sequence_[i][0] + c2.sequence_[i][0]; //add the array points
            res.sequence_[i][1] = c1.sequence_[i][1] + c2.sequence_[i][1];
        }
        if(i>=c1.size_) //if the new array is out of bounds of the first array
        {
            res.sequence_[i][0] = c2.sequence_[i][0]; //append the remaining points from first array to the new array
            res.sequence_[i][1] = c2.sequence_[i][1];
        }
        if(i>=c2.size_) //if the new array is out of bounds of the second array
        {
            res.sequence_[i][0] = c1.sequence_[i][0]; //append the remaining points from second array to the new array
            res.sequence_[i][1] = c1.sequence_[i][1];
        }
    }
    return res;
  }

  // Overloading the << operator.
  friend std::ostream &operator<<(std::ostream &out, const Points2D &some_points) 
  {
    if (some_points.size_ == 0) //if the array is empty
    {
      out << "()\n"; //then print an empty point
      return out;
    }

    for(size_t i = 0; i < some_points.size_; i++) //if the array is not empty then cycle through the array
    {
      out << "(";
      out << some_points[i][0]; //printing the 1st part of the point
      out << ",";
      out << some_points[i][1]; //printing the 2nd part of the point
      out << ")";
    }

    out << "\n";
    return out; //prints the complete point in the format that was specified
  }

  // Overloading the >> operator.
  // Read a chain from an input stream (e.g., standard input).
  friend std::istream &operator>>(std::istream &in, Points2D &some_points) 
  {
    std::string input_line;
    std::getline(in, input_line); //reading from input and storing it in a string
    std::stringstream input_stream(input_line); //passing the string to read a number at a time
    if (input_line.empty()) //if string if empty then return
      return in;
    int size_of_sequence;
    input_stream >> size_of_sequence; //getting the size of the new array from the string 
    
    some_points.size_ = size_of_sequence; //declaring the size of the new array from the string
    some_points.sequence_ = new std::array<Object, 2>{size_of_sequence}; //creating a new array of size that was given from the string

    Object token; //creating abject to store the points that were passed through the string
    for (size_t i = 0; i < some_points.size_; ++i)  //looping through the string for the remaining points that was given
    {
      input_stream >> token; //getting the first part of the point that was passed
      some_points.sequence_[i][0] = token; //storing the first part of the point in the array
      input_stream >> token; //getting the second part of the point that was passed
      some_points.sequence_[i][1] = token; //storing the second part of the point in the array
    }

    return in;
  }

private:
  std::array<Object, 2> *sequence_; // Sequence of points
  size_t size_; // Size of sequence.
};

}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_Points2D_H_
