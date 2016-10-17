InputOutput::InputOutput(char filenameIn[256]){
  ifstream infile;
  infile.open(filenameIn);
  // check for error in file
  if (infile.fail()){
    cerr << "Error opening file" <<endl;
    }

  std::vector<double> v(38);
  for (size_t i = 0; i < v.size(); i++){
    infile>>v[i];
    infile.ignore(500,';');
  }

  ofstream outfile;
	outfile.open("echo.dat");

	for (size_t i=0; i<v.size(); i++){
		outfile<<v[i]<<endl;
	}
  setInputParams(v);
}


void InputOutput::setInputParams(std::vector<double> InRaw){
  //std::cout << "Setting function is called!" << std::endl;
  /*for (size_t i = 0; i < InRaw.size(); i++) {
    std::cout << "InRaw[" <<i<<"] = "<<InRaw[i]<< std::endl;
  }*/
  this->R = InRaw[0];
  this->Z = InRaw[1];
  this->FlagDeltaR = (int)InRaw[2];
  this->FlagDeltaZ = (int)InRaw[5];

// Deciding whether number of elements are controlled or DeltaR is controlled

  if (this->FlagDeltaR == 1) {// to specify DeltaR and calculate nNode
    this->deltaR = InRaw[3];
    this->nNodeR = ceil(this->R/this->deltaR);
  } else if (this->FlagDeltaR == 0) {// to specify nNode and calculate DeltaR
    this->nNodeR = (int)InRaw[4];
    this->deltaR = this->R/this->nNodeR;
  } else {
    std::cout << "Check the DeltaR flag! Terminating due to fatal error." << std::endl;
    exit (EXIT_FAILURE);
  }

// Deciding whether number of elements are controlled or DeltaZ is controlled

  if (this->FlagDeltaZ == 1) {// to specify DeltaR and calculate nNode
    this->deltaZ = InRaw[6];
    this->nNodeZ = ceil(this->R/this->deltaZ);
  } else if (this->FlagDeltaZ == 0) {// to specify nNode and calculate DeltaR
    this->nNodeZ = (int)InRaw[7];
    this->deltaZ = this->Z/this->nNodeZ;
  } else {
    std::cout << "Check the DeltaZ flag! Terminating due to fatal error." << std::endl;
    exit (EXIT_FAILURE);
  }

// Material properties
  this->ThermalCond = InRaw[8];
  //std::cout << "Thermal Conductivity is " <<this->ThermalCond<< std::endl;
  this->rho = InRaw[9];
  this->SpecificHeat = InRaw[10]; // specific heat capacity per unit mass
  this->Tref = InRaw[35];
// spark characteristics
  this->r_0 = InRaw[11]; // radius of spark
  this->fr = InRaw[12];  // factor to be used in the Q_top calculation
  this->V_c = InRaw[13]; // critical voltage
  this->I_c = InRaw[14]; // critical current
  this->conc = InRaw[15]; // concentration of electrolyte in %
  this->h_top = InRaw[36]; // heat transfer coefficient at the top of domain
  this->Q_top = ( this->V_c * this->I_c * 4.45 * this->fr ) / (M_PI * this->r_0 * this->r_0 * this->Tref); // flux from the top of domain

// time cycle parameters
  this->tOnset = InRaw[16];
  this->tOffset = InRaw[17];
  this->deltaCycle = this->tOnset + this->tOffset;
  this->factorTime = 0.03 + 0.05682*this->conc + 0.0563*this->tOnset - 0.01231*this->tOffset - 0.001358*this->conc*this->conc - 0.0095*this->tOnset*this->tOnset;
  this->omega = (this->factorTime*this->tOnset)/this->deltaCycle;

// BCs
  this->FLAGleftBC = InRaw[18];
  this->FLAGbottomBC = InRaw[23];
  this->FLAGrightBC = InRaw[28];
  this->Phi_left = InRaw[19];
  this->Qa_left = InRaw[20]/this->Tref;
  this->h_left = InRaw[21];
  this->Phi_infLeft = InRaw[22];
  this->Phi_right = InRaw[24];
  this->Qa_right = InRaw[25]/this->Tref;
  this->h_right = InRaw[26];
  this->Phi_infRight = InRaw[27];
  this->Phi_bottom = InRaw[29];
  this->Qa_bottom = InRaw[30]/this->Tref;
  this->h_bottom = InRaw[31];
  this->Phi_infBottom = InRaw[32];
  this->Phi_0 = InRaw[33];
  this->source = InRaw[34];


  this->cycleEnd = InRaw[37];
}

void InputOutput::EventWrite(std::vector<Nodes*> &A, char filenameOut[256]) {
  ofstream fout;
  fout.open(filenameOut,ios::app);    // open file for appending
  fout<<"#nNodeR = "<<A[0]->nNodeR<<" ,nNodeZ = "<<A[0]->nNodeZ<<endl; // first line writes the number of grid points
  fout<<"R Z Phi"<<endl;
  /*for (size_t i = 0; i < A.size(); i++) {
    std::cout<<"At (R,Z) = (" << A[i]->R << ","<<A[i]->Z<< ") : T = " <<A[i]->phi<< std::endl;
  }*/
  for (int iout=0; iout<A.size(); iout++){
    fout<<A[iout]->R<<" "<<A[iout]->Z<<" "<<A[iout]->phi<<endl;
  }
}
