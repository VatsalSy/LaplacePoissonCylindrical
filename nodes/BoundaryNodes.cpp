BoundaryNodes::BoundaryNodes(int column, int row, double s) : Nodes(column, row,s) {
  //std::cout << "Preparing (" <<row<<","<<column<<")"<< std::endl;
}

void BoundaryNodes::setBC(int flag, double phiW, double flux, double h, double k, double phiInf, double coeff, double deltaRZ){
  //std::cout << "Set Boundary conditions called!" << std::endl;
  if (flag == 0) {// DirichletBC
    this->DirichletBC(phiW,coeff);
  } else if (flag == 1){// NeumannBC
    this->NeumannBC(flux, k,coeff, deltaRZ);
  } else if (flag == 2){// RobinBC
    this->RobinBC(h,k,phiInf,coeff, deltaRZ);
  } else {
    std::cout << "Fatal error in setBc! Inappropriate flag of BC" << std::endl;
    exit(EXIT_FAILURE);
  }
}

void BoundaryNodes::DirichletBC(double phiW, double coeff) {
  this->Ap = this->Ap - coeff;
  this->source = this->source + 2*coeff*phiW;
}

void BoundaryNodes::NeumannBC(double flux, double k, double coeff, double deltaRZ) {
  this->Ap = this->Ap + coeff;
  this->source = this->source + coeff*flux*deltaRZ/k;
}

void BoundaryNodes::RobinBC(double h, double k, double phiInf, double coeff, double deltaRZ) {
  double temp = h*deltaRZ/k;
  //std::cout << "Value of b is " <<temp<< std::endl;
  //std::cout << "Ap = " <<this->Ap<< std::endl;
  this->Ap = this->Ap + coeff*(2-temp)/(2+temp);
  //std::cout << "Ap = " <<this->Ap<< std::endl;
  this->source = this->source + phiInf*(2*temp)/(2+temp);
}
