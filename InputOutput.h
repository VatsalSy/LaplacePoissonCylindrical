#ifndef InputOutput_H
#define InputOutput_H
class InputOutput {
  // The geometric parameters
  static double R;
  static double Z;
  static int nNodeR;
  static int nNodeZ;
  static double deltaR;
  static double deltaZ;
  // Material properties
  static double ThermalCond;
  static double rho;
  static double SpecificHeat; // specific heat capacity per unit mass
  // spark characteristics
  static double r_0; // radius of spark
  static double fr;  // factor to be used in the Q_top calculation
  static double V_c; // critical voltage
  static double I_c; // critical current
  static double conc // concentration of electrolyte in %
  // time cycle parameters
  static double deltaCycle;
  static double tOnset;
  static double tOffset;
  static double factorTime;
  // Boundary conditions
  static double Phi_left;
  static double Qa_left;
  static double h_left;
  static double Phi_infLeft;
  static double Phi_right;
  static double Qa_right;
  static double h_right;
  static double Phi_infRight;
  static double Phi_bottom;
  static double Qa_bottom;
  static double h_bottom;
  static double Phi_infBottom;
};
#endif
