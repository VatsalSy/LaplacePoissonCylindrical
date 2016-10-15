#ifndef NodesAbstract_H
#define NodesAbstract_H
class NodesAbstract {
public:
// These three functions can be called using the pointer to parent class as well!
  virtual void setCoeffDefault() = 0;
  virtual void setBC() = 0;
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
  static double source; // source term in discretized equation
  double Aw; // West coefficient
  double Ap; // Nodal temperature coefficient
  double Ae; // East coefficient
  double An; // North coefficient
  double As; // South coefficient
  int jr; // index of column
  int iz; // index of row
  double R; // value of radius
  double Z; // value of axial distance
  static void setFeaturesGrid(int, int, double, double, double, double); // nodes in R,z; Fo_cell; delta in R,Z and bar(S)/(kT_0)
  static void setTimeMarch(double, double); // stability for time marching
  Nodes (int, int); // jx and iy
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
  InnerNodes(int, int);
};
#include "InnerNodes.cpp"
#endif

#ifndef  BoundaryNodes_H
#define BoundaryNodes_H

class BoundaryNodes : public Nodes {
public:
  BoundaryNodes(int,int);
  void setBC();
};
#include "BoundaryNodes.cpp"
#endif
