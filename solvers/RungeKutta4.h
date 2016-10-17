void calcfun(std::vector<Nodes*> &, std::vector<double> , std::vector<double> );
void RungeKutta4(std::vector<Nodes*> &A) {
// make dummy images
double Eta = A[0]->eta, Fourier = A[0]->Fo, n = A.size();
std::vector<double> phivec1(n), phivec2(n), phivec3(n), phivec4(n);
std::vector<double> fun1(n), fun2(n), fun3(n), fun4(n);

// save the current phi_n values in an image: phivec1
for (size_t i = 0; i < A.size(); i++) {
  phivec1[i] = A[i]->phi;
} // end for of making image of phi_n
// calculate f(phi_n)
calcfun(A,phivec1,fun1);
for (size_t i = 0; i < A.size(); i++) {
  phivec2[i] = phivec1[i] + Eta*Fourier*fun1[i]/2;
}

}

void calcfun(std::vector<Nodes*> &A, std::vector<double> phivec, std::vector<double> fun) {
  int nR = A[0]->nNodeR, nZ = A[0]->nNodeZ;
  for (size_t i = 0; i < A.size(); i++) {
    if (A[i]->iz == 0 & A[i]->jr != 0 & A[i]->jr != nR-1) {//bottom side except both corners
      fun[i] = A[i]->Aw * phivec[i-1] + A[i]->Ap * phivec[i] + A[i]->Ae * phivec[i+1] + A[i]->An * phivec[i + A[i]->nNodeR] + A[i]->source;
    } else if (A[i]->iz == nZ-1 & A[i]->jr != 0 & A[i]->jr != nR-1) {// top side
      fun[i] = A[i]->Aw * phivec[i-1] + A[i]->Ap * phivec[i] + A[i]->Ae * phivec[i+1] + A[i]->As * phivec[i - A[i]->nNodeR] + A[i]->source;
    } else if (A[i]->jr == 0 & A[i]->iz != 0 & A[i]->iz != nZ-1) {//left side
      fun[i] = A[i]->Ap * phivec[i] + A[i]->Ae * phivec[i+1] + A[i]->An * phivec[i + A[i]->nNodeR] +  A[i]->As * phivec[i - A[i]->nNodeR] + A[i]->source;
    } else if (A[i]->jr == nR-1 & i != 0 & A[i]->iz != nZ-1) {//right side
      fun[i] = A[i]->Aw * phivec[i-1] + A[i]->Ap * phivec[i] + A[i]->An * phivec[i + A[i]->nNodeR] +  A[i]->As * phivec[i - A[i]->nNodeR] + A[i]->source;
    } else if (A[i]->iz > 0 & A[i]->iz < nZ-1 & A[i]->jr > 0 & A[i]->jr < nR - 1) {// inner Nodes
      fun[i] = A[i]->Aw * phivec[i-1] + A[i]->Ap * phivec[i] + A[i]->Ae * phivec[i+1] + A[i]->An * phivec[i + A[i]->nNodeR] +  A[i]->As * phivec[i - A[i]->nNodeR] + A[i]->source;
    } else if (A[i]->iz == 0 & A[i]->jr == 0){// bottom left
      fun[i] = A[i]->Ap * phivec[i] + A[i]->Ae * phivec[i+1] + A[i]->An * phivec[i + A[i]->nNodeR] + A[i]->source;
    } else if (A[i]->iz == 0 & A[i]->jr == nR-1){// bottom right
      fun[i] = A[i]->Aw * phivec[i-1] + A[i]->Ap * phivec[i] + A[i]->An * phivec[i + A[i]->nNodeR] + A[i]->source;
    } else if (A[i]->iz == nZ-1 & A[i]->jr == nR-1){// top right
      fun[i] = A[i]->Ap * phivec[i] + A[i]->Ae * phivec[i+1] +  A[i]->As * phivec[i - A[i]->nNodeR] + A[i]->source;
    } else if (A[i]->iz == nZ-1 & A[i]->jr == 0){ // top left
      fun[i] = A[i]->Aw * phivec[i-1] + A[i]->Ap * phivec[i] +  A[i]->As * phivec[i - A[i]->nNodeR] + A[i]->source;
    } else {
      std::cout << "Fatal Error! Accessing unknown indices!" << std::endl;
      exit(EXIT_FAILURE);
  } // end if else nested loops
} // for loop of going through the A vector ended,
}
