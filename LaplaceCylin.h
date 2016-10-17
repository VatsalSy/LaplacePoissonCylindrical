using namespace std;
#include <iostream> // input output library
#include <fstream>  // file handling library
#include <cmath>    // Mathematical operations
#include <vector>   // Vectors STL class
#include <string>   // String STL class
#include <stdlib.h> // Printing error messages
#include "nodes/nodes.h" // Class library for the nodes, written by Vatsal (vatsalsanjay@gmail.com)
#include "solvers/RungeKutta4.h" // Runge Kutta explicit solver implemented with the nodes class
#include "InputOutput.h" // handling the input and output

int ij2Lexo(int row, int column, double nNodeR){
  return column + nNodeR*row;
}
