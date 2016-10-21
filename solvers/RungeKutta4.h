void calcfun(std::vector<Nodes*> &, std::vector<double> &, std::vector<double> &);

void RungeKutta4(std::vector<Nodes*> &A) {
// make dummy images
double Eta = A[0]->eta, Fourier = A[0]->Fo, n = A.size();
//std::cout << "Eta*Fourier = " <<Eta*Fourier<< std::endl;
std::vector<double> phivec1(n), phivec2(n), phivec3(n), phivec4(n);
std::vector<double> fun1(n), fun2(n), fun3(n), fun4(n);

// save the current phi_n values in an image: phivec1
for (size_t i = 0; i < A.size(); i++) {
  phivec1[i] = A[i]->phi;
} // end for of making image of phi_n

// calculate f(phi_n)
calcfun(A,phivec1,fun1);
// Step 1 finding phi(n+0.5)*
for (size_t i = 0; i < A.size(); i++) {
  phivec2[i] = phivec1[i] + Eta*Fourier*fun1[i]/2;
  //std::cout << fun1[i] << std::endl;
}

// calculate f(phi(n+0.5)*)
calcfun(A,phivec2,fun2);
// Step 2 finding phi(n+0.5)**
for (size_t i = 0; i < A.size(); i++) {
  phivec3[i] = phivec1[i] + Eta*Fourier*fun2[i]/2;
}

// calculate f(phi(n+0.5)**)
calcfun(A,phivec3,fun3);
// Step 3 finding phi(n+1)*
for (size_t i = 0; i < A.size(); i++) {
  phivec4[i] = phivec1[i] + Eta*Fourier*fun3[i];
}

// calculate f(phi(n+1)*)
calcfun(A,phivec4,fun4);
// Step 4 getting phi(n+1)
for (size_t i = 0; i < A.size(); i++) {
  A[i]->phi = phivec1[i] + Eta*Fourier*( fun1[i] + 2 * ( fun2[i] + fun3[i] ) + fun4[i] )/6;
  if (A[i]->phi < -25) {
    std::cout << "There is stability problem in Runge Kutta method! You can - \n 1.Change 4th order explicit RK to 5th order embedded RK \n 2. Change eta factor in source code\n 3. Increase deltaR " << std::endl;
  }
/*  if (A[i]->phi != 0) {
    std::cout <<"phi = "<< A[i]->phi << std::endl;
  }*/
}

} // RungeKutta4 ends

void calcfun(std::vector<Nodes*> &A, std::vector<double> &phivec, std::vector<double> &fun) {
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
