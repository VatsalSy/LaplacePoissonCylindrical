BoundaryNodes::BoundaryNodes(int column, int row) : Nodes(column, row) {
  std::cout << "Preparing (" <<row<<","<<column<<")"<< std::endl;
}
void BoundaryNodes::setBC(){
  std::cout << "Set Boundary conditions called!" << std::endl;
}
