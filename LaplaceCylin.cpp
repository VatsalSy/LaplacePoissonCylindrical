#include "LaplaceCylin.h"

int main () {

  // Input data
  char filename[256];
  sprintf (filename, "InputEcdm.dat");
  InputOutput in(filename);
  //Nodes::checkOut();
  double alphaIn = (in.ThermalCond)/(in.rho*in.SpecificHeat);
  double sourceTerm = in.source/(in.ThermalCond*in.Tref);
  //std::cout << "sourceTerm is " <<sourceTerm<< std::endl;
  Nodes::setFeaturesGrid(in.nNodeR, in.nNodeZ, alphaIn, in.deltaR, in.deltaZ);
  Nodes::setTimeMarch(in.omega, in.deltaCycle);
  //Nodes::checkOut();

  // Default settings for the top edge!
  int FLAGtopBC = 0;
  double Phi_top = 1;
  double Phi_infTop = 0;

  std::vector<Nodes*> A(Nodes::nNodeR * Nodes::nNodeZ);
  // Setting the coefficients and other things!
  int counter = 0;
  for (size_t i = 0; i < Nodes::nNodeZ; i++) {
    for (size_t j = 0; j < Nodes::nNodeR; j++) {
      counter = ij2Lexo(i,j,Nodes::nNodeR);
      //std::cout << counter << std::endl;
      if (i == 0 & j != 0 & j != Nodes::nNodeR-1) {//bottom side except both corners
        BoundaryNodes* tempBottom = new BoundaryNodes(j,i, sourceTerm);
        //tempBottom->checkOutDynamic();
        tempBottom->setBC(in.FLAGbottomBC, in.Phi_bottom, in.Qa_bottom, in.h_bottom, in.ThermalCond, in.Phi_infBottom,tempBottom->As,in.deltaZ);
        //tempBottom->checkOutDynamic();
        A[counter] = tempBottom;
        //A[counter]->checkOutDynamic();
      } else if (i == Nodes::nNodeZ-1 & j != 0 & j != Nodes::nNodeR-1) {// top side
        BoundaryNodes* tempTop = new BoundaryNodes(j,i, sourceTerm);
        //tempTop->checkOutDynamic();
        tempTop->setBC(FLAGtopBC, Phi_top, 0, in.h_top, in.ThermalCond, Phi_infTop,tempTop->An,in.deltaZ);
        //tempTop->checkOutDynamic();
        A[counter] = tempTop;
        //A[counter]->checkOutDynamic();
      } else if (j == 0 & i != 0 & i != Nodes::nNodeZ-1) {//left side
        BoundaryNodes* tempLeft = new BoundaryNodes(j,i, sourceTerm);
        //tempLeft->checkOutDynamic();
        tempLeft->setBC(in.FLAGleftBC, in.Phi_left, in.Qa_left, in.h_left, in.ThermalCond, in.Phi_infLeft,tempLeft->Aw,in.deltaR);
        //tempBottom->checkOutDynamic();
        A[counter] = tempLeft;
        //A[counter]->checkOutDynamic();
      } else if (j == Nodes::nNodeR-1 & i != 0 & i != Nodes::nNodeZ-1) {//right side
        BoundaryNodes* tempRight = new BoundaryNodes(j,i, sourceTerm);
        //tempLeft->checkOutDynamic();
        tempRight->setBC(in.FLAGrightBC, in.Phi_right, in.Qa_right, in.h_right, in.ThermalCond, in.Phi_infRight,tempRight->Ae,in.deltaR);
        //tempBottom->checkOutDynamic();
        A[counter] = tempRight;
        //A[counter]->checkOutDynamic();
      } else if (i > 0 & i < Nodes::nNodeZ-1 & j > 0 & j < Nodes::nNodeR - 1) {// inner Nodes
        InnerNodes* tempInner = new InnerNodes(j,i, sourceTerm);
        //tempInner->checkOutDynamic();
        A[counter] = tempInner;
        //A[counter]->checkOutDynamic();
      } else if (i == 0 & j == 0){// bottom left
        BoundaryNodes* tempCorner = new BoundaryNodes(j,i,sourceTerm);
        //tempCorner->checkOutDynamic();
        tempCorner->setBC(in.FLAGbottomBC, in.Phi_bottom, in.Qa_bottom, in.h_bottom, in.ThermalCond, in.Phi_infBottom,tempCorner->As,in.deltaZ); // bottom
        tempCorner->setBC(in.FLAGleftBC, in.Phi_left, in.Qa_left, in.h_left, in.ThermalCond, in.Phi_infLeft,tempCorner->Aw,in.deltaR); // left
        A[counter] = tempCorner;
        //A[counter]->checkOutDynamic();
      } else if (i == 0 & j == Nodes::nNodeR-1){// bottom right
        BoundaryNodes* tempCorner = new BoundaryNodes(j,i,sourceTerm);
        //tempCorner->checkOutDynamic();
        tempCorner->setBC(in.FLAGbottomBC, in.Phi_bottom, in.Qa_bottom, in.h_bottom, in.ThermalCond, in.Phi_infBottom,tempCorner->As,in.deltaZ); // bottom
        tempCorner->setBC(in.FLAGrightBC, in.Phi_right, in.Qa_right, in.h_right, in.ThermalCond, in.Phi_infRight,tempCorner->Ae,in.deltaR); // right
        A[counter] = tempCorner;
        //A[counter]->checkOutDynamic();
      } else if (i == Nodes::nNodeZ-1 & j == Nodes::nNodeR-1){// top right
        //tempCorner->checkOutDynamic();
        BoundaryNodes* tempCorner = new BoundaryNodes(j,i,sourceTerm);
        tempCorner->setBC(FLAGtopBC, Phi_top, 0, in.h_top, in.ThermalCond, Phi_infTop,tempCorner->An,in.deltaZ); // top
        tempCorner->setBC(in.FLAGrightBC, in.Phi_right, in.Qa_right, in.h_right, in.ThermalCond, in.Phi_infRight,tempCorner->Ae,in.deltaR); // right
        A[counter] = tempCorner;
        //A[counter]->checkOutDynamic();
      } else if (i == Nodes::nNodeZ-1 & j == 0){ // top left
        BoundaryNodes* tempCorner = new BoundaryNodes(j,i,sourceTerm);
        //tempCorner->checkOutDynamic();
        tempCorner->setBC(FLAGtopBC, Phi_top, 0, in.h_top, in.ThermalCond, Phi_infTop,tempCorner->An,in.deltaZ); // top
        tempCorner->setBC(in.FLAGleftBC, in.Phi_left, in.Qa_left, in.h_left, in.ThermalCond, in.Phi_infLeft,tempCorner->Aw,in.deltaR); // left
        A[counter] = tempCorner;
        //A[counter]->checkOutDynamic();
      } else {
        std::cout << "Fatal Error! Accessing unknown indices!" << std::endl;
        exit(EXIT_FAILURE);
    } // end if else nested loops
  } // sweeping for loop in columns ends
} // sweeping for loop in rows ends

int cycle = 0;
char filenameOut[256];
int sparkIdx = ceil(in.r_0/in.deltaR);
// initial condition
sprintf (filenameOut, "output/cycle%03d.dat", 0);
in.EventWrite(A,filenameOut);

while (cycle < in.cycleEnd) {
  cycle++;

  for (size_t istep = 0; istep < 1/Nodes::eta; istep++) {
    if (istep < in.omega/Nodes::eta) { // pulse on
      std::cout << "This is pulse on!" << std::endl;
      RungeKutta4(A);
    } else { // pulse off
      std::cout << "This is pulse off!" << std::endl;
      RungeKutta4(A);
    }
  } // end for loop of in cycle time integration
sprintf (filenameOut, "output/cycle%03d.dat", cycle);
in.EventWrite(A,filenameOut);

std::cout << "Cycle " <<cycle<< " is completed!"<< std::endl;
} // end while do loop for cycle marching

  return 0;
}
