#ifndef InputOutput_H
#define InputOutput_H
class InputOutput {
public:
  // The geometric parameters
  double R;
  double Z;
  int FlagDeltaR;
  int FlagDeltaZ;
  int nNodeR;
  int nNodeZ;
  double deltaR;
  double deltaZ;
  // Material properties
  double ThermalCond;
  double rho;
  double SpecificHeat; // specific heat capacity per unit mass
  // spark characteristics
  double r_0; // radius of spark
  double fr;  // factor to be used in the Q_top calculation
  double V_c; // critical voltage
  double I_c; // critical current
  double conc; // concentration of electrolyte in %
  double h_top; // convective BC at top
  double Q_top; // flux from top
  // time cycle parameters
  double deltaCycle;
  double omega;
  double tOnset;
  double tOffset;
  double factorTime;
  // Boundary conditions
  int FLAGleftBC;
  int FLAGbottomBC;
  int FLAGrightBC;
  double Phi_left;
  double Qa_left;
  double h_left;
  double Phi_infLeft;
  double Phi_right;
  double Qa_right;
  double h_right;
  double Phi_infRight;
  double Phi_bottom;
  double Qa_bottom;
  double h_bottom;
  double Phi_infBottom;
  double source;
  double Tref;
  int cycleEnd;
  double PhiInitial;

  InputOutput(char[256]);
  void EventWrite(std::vector<Nodes*> &, char[256]);
  void setInputParams(std::vector<double>);
};
#include "InputOutput.cpp"
#endif
