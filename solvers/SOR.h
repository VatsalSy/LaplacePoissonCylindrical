void SOR(std::vector<Nodes*> A, double omega, int nNodeX, int nNodeY, int maxIteration){
  std::cout << "Solution initiated for the system of equation using SOR" << std::endl;
  std::cout << "Value of Over Relaxation Factor is " <<omega<< std::endl;
  double errorTemp = 0, temp = 0, error = 0, oldphi = 0;
  int counter = 0, i, j;

  do {// iteration begins

    counter += 1;
    error = 0;

    //Initiating the solution vector with an initial guess if not zero!
    /*for (size_t i = 0; i < A.size(); i++) {
      A[i]->phi = 0;
    }*/

    for (size_t c = 0; c < A.size(); c++) { // sweeping through the matrix, finding the phi

      oldphi = A[c]->phi;
      i = A[c]->iz;
      j = A[c]->jr;

      if (i == 0 & j != 0 & j != nNodeX-1) {//bottom side except both corners
        //std::cout << c << std::endl;
        temp = A[c]->source - A[c]->Ae*A[i+1]->phi - A[c]->Aw*A[c-1]->phi - A[c]->An*A[c+nNodeX]->phi;
        temp = temp/A[c]->Ap;
        //std::cout << temp << std::endl;
      } else if (i == nNodeY-1 & j != 0 & j != nNodeX-1) {// top side
        //std::cout << c << std::endl;
        temp = A[c]->source - A[c]->Ae*A[c+1]->phi - A[c]->Aw*A[c-1]->phi - A[c]->As*A[c-nNodeX]->phi;
        temp = temp/A[c]->Ap;
        //std::cout << temp << std::endl;
      } else if (j == 0 & i != 0 & i != nNodeY-1) {//left side
        temp = A[c]->source - A[c]->Ae*A[c+1]->phi - A[c]->An*A[c+nNodeX]->phi - A[c]->As*A[c-nNodeX]->phi;
        temp = temp/A[c]->Ap;
      } else if (j == nNodeX-1 & i != 0 & i != nNodeY-1) {//right side
        temp = A[c]->source - A[c]->Aw*A[c-1]->phi - A[c]->An*A[c+nNodeX]->phi - A[c]->As*A[c-nNodeX]->phi;
        temp = temp/A[c]->Ap;
      } else if (i == 0 & j == 0) { // bottom left
        temp = A[c]->source - A[c]->Ae*A[c+1]->phi - A[c]->An*A[c+nNodeX]->phi;
        temp = temp/A[c]->Ap;
      } else if (i == 0 & j == nNodeX-1) { // bottom right
        temp = A[c]->source - A[c]->Aw*A[c-1]->phi - A[c]->An*A[c+nNodeX]->phi;
        temp = temp/A[c]->Ap;
      } else if (i == nNodeY-1 & j == nNodeX-1) { // top right
        temp = A[c]->source - A[c]->Aw*A[c-1]->phi - A[c]->As*A[c-nNodeX]->phi;
        temp = temp/A[c]->Ap;
      } else if (i == nNodeY-1 & j == 0) { // top left
        temp = A[c]->source - A[c]->Ae*A[c+1]->phi - A[c]->As*A[c-nNodeX]->phi;
        temp = temp/A[c]->Ap;
      } else { // inner nodes
        temp = A[c]->source - A[c]->Ae*A[c+1]->phi - A[c]->Aw*A[c-1]->phi - A[c]->An*A[c+nNodeX]->phi - A[c]->As*A[c-nNodeX]->phi;
        temp = temp/A[c]->Ap;
      }

      A[c]->phi = (1-omega)*A[c]->phi + omega*(temp);

      errorTemp = fabs(A[c]->phi - oldphi); // Error L1  norm
      if (errorTemp>error) {
        error = errorTemp;
      }

    } // sweeping ends

    std::cout.precision(4);
    std::cout << "For iteration = " <<counter<<", absolute error norm = "<<error<< std::endl;
  } while(error>=1e-6 & maxIteration > counter);

} // SOR function ends
