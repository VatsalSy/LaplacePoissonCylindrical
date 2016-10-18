/**** This .cpp file belongs to the class Nodes, which is the parent class for all other nodal classes *************/
int Nodes::nNodeR = 0;
int Nodes::nNodeZ = 0;
double Nodes::Fo = 0; // Cell Fourier number for each cycle
double Nodes::deltaR = 0;
double Nodes::deltaZ = 0;
double Nodes::alpha = 0;
double Nodes::eta = 0; // time thing
double Nodes::deltaT = 0; // cyclic time interval

void Nodes::setFeaturesGrid(int nR, int nZ, double alphaIn, double delR, double delZ) {// nodes in R,z; Fo_cell; delta in R,Z
  Nodes::nNodeR = nR;
  Nodes::nNodeZ = nZ;
  Nodes::alpha = alphaIn;
  Nodes::deltaR = delR;
  Nodes::deltaZ = delZ;
}

void Nodes::setTimeMarch(double Kfrac, double tdelta) {
  Nodes::deltaT = tdelta;
  Nodes::Fo = (Nodes::alpha * Nodes::deltaT) / (Nodes::deltaR * Nodes::deltaR);

  if (Kfrac > 1 - Kfrac) {
    Nodes::eta = (1 - Kfrac)/100;
  } else {
    Nodes::eta = Kfrac/100;
  }

}

Nodes::Nodes (int column, int row, double s){// column, row and bar(S)/(kT_0)
  this->jr = column;
  this->iz = row;
  this->R = Nodes::deltaR/2 + Nodes::deltaR*this->jr;
  this->Z = Nodes::deltaZ/2 + Nodes::deltaZ*this->iz;
  this->phi = 0;
  this->setCoeffDefault(s);
}

void Nodes::setCoeffDefault(double s){ //  bar(S)/(kT_0)
  double zeta = (this->deltaR/this->deltaZ);
  double temp = ( 2 * this->jr + 1);
  this->Aw = 1 - (1/temp);
  this->Ap = -2*( 1 + zeta * zeta );
  this->Ae = 1 + (1/temp);
  this->An = zeta * zeta;
  this->As = zeta * zeta;
  this->source = s*Nodes::deltaR*Nodes::deltaR;
}

void Nodes::checkOut() {
  std::cout << "Number of nodes in R direction is " <<Nodes::nNodeR<< std::endl;
  std::cout << "Number of nodes in Z direction is " <<Nodes::nNodeZ<< std::endl;
  std::cout << "Cell Fourier Number is " <<Nodes::Fo << std::endl;
  std::cout << "Cell size in R direction is " <<Nodes::deltaR<< std::endl;
  std::cout << "Cell size in Z direction is " <<Nodes::deltaZ<< std::endl;
  std::cout << "Value of alpha is " <<Nodes::alpha<< std::endl;
  std::cout << "Value of the time interval of the cycle is " <<Nodes::deltaT << std::endl;
  std::cout << "Time marching eta is " <<Nodes::eta << std::endl;
}

void Nodes::checkOutDynamic() {
  std::cout << "(R,Z) = (" <<this->R<<","<<this->Z<<")"<< std::endl;
  std::cout << "(i,j) = (" <<this->iz<<","<<this->jr<<")"<< std::endl;
  std::cout << "West node coefficient is " <<this->Aw << std::endl;
  std::cout << "Main node coefficient is " <<this->Ap << std::endl;
  std::cout << "East node coefficient is " <<this->Ae << std::endl;
  std::cout << "North node coefficient is " <<this->An << std::endl;
  std::cout << "South node coefficient is " <<this->As << std::endl;
  std::cout << "Value of source term in discretized equation is " <<this->source<< std::endl;
}
