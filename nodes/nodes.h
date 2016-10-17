#ifndef NodesAbstract_H
#define NodesAbstract_H
class NodesAbstract {
public:
// These three functions can be called using the pointer to parent class as well!
  virtual void setCoeffDefault() = 0;
  virtual void setBC(int, double, double, double, double, double, double, double) = 0;
  virtual void checkOutDynamic() = 0;
};
#endif

#ifndef  Nodes_H
#define Nodes_H

class Nodes : public NodesAbstract {
public:
  static int nNodeR; // Number of nodes in Radial direction
  static int nNodeZ; // Number of nodes in Axial direction
  static double Fo; // Cell Fourier number for each cycle
  static double deltaR; // Cell length in Radial direction
  static double deltaZ; // Cell length in Axial direction
  static double eta; // time step for temporal marching
  static double deltaT; // cyclic time interval
  static double alpha; // diffusion coefficient
  double source; // source term in discretized equation
  double Aw; // West coefficient
  double Ap; // Nodal temperature coefficient
  double Ae; // East coefficient
  double An; // North coefficient
  double As; // South coefficient
  int jr; // index of column
  int iz; // index of row
  double R; // value of radius
  double Z; // value of axial distance
  double phi;
  static void setFeaturesGrid(int, int, double, double, double); // nodes in R,z; Fo_cell; delta in R,Z
  static void setTimeMarch(double, double); // stability for time marching
  Nodes (int, int, double); // jx, iy and bar(S)/(kT_0)
  void setCoeffDefault();
  static void checkOut();
  void checkOutDynamic();
};
#include "nodes.cpp"
#endif


#ifndef InnerNodes_H
#define InnerNodes_H

class InnerNodes : public Nodes {
public:
  InnerNodes(int, int, double);
  void setBC(int, double, double, double, double, double, double, double){std::cout << "Never call this function!" << std::endl;}
};
#include "InnerNodes.cpp"
#endif

#ifndef  BoundaryNodes_H
#define BoundaryNodes_H

class BoundaryNodes : public Nodes {
public:
  BoundaryNodes(int,int, double);
  void setBC(int, double, double, double, double, double, double, double); // In order -- flag, Phiwall, flux, h, k, PhiInf, coeff, deltaRZ
  void DirichletBC(double, double); // Phiwall, coeff
  void NeumannBC(double, double, double, double); // flux, K, coeff, deltaRZ
  void RobinBC(double, double, double, double, double);// h, k, phiInf, coeff, deltaRZ
};
#include "BoundaryNodes.cpp"
#endif
