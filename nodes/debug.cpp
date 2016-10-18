#include <iostream>
#include <stdlib.h>
#include "nodes.h"
#include <vector>
#include <algorithm>

//int Nodes::nNodeX = 100;
using namespace std;

int main () {
  //std::cout << "Static data out " <<test.nNodeX<< std::endl;
  //int n = 100;
  //Nodes::setFeaturesGrid(400,100,20,1,1);
  //Nodes defaultNode (-1,2,-1,-1,-1);
  //Nodes::checkOut();
  //Nodes* myptr;
  //InnerNodes testing;
  //testing.setBC();
  //myptr = &testing;

  Nodes::checkOut();
  Nodes::setFeaturesGrid(100,100,0.25,0.1,0.1,0.001);
  Nodes::setTimeMarch(0.25,0.002);
  Nodes::checkOut();
  BoundaryNodes temp(5,5);
  temp.setCoeffDefault();
  temp.checkOut();
  temp.checkOutDynamic();
  Nodes* see;
  see = &temp;
  see->checkOutDynamic();
  see->setBC();
  return 0;
}
