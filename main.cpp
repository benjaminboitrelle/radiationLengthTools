/******************
   Tools to measure radiation length
   Author: Benjamin BOIRELLE, with the help of Phillip Hamnet
   Institute: DESY
 *****************/
#include <iostream>
#include <vector>
#include <memory>
#include <string> 
#include <sstream>
#include <tuple>
#include <algorithm>
#include <iterator>

#include "TTree.h"
#include "TBranch.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TStyle.h"

#include "source/readerTTree.hpp"
#include "source/graphPlotting.hpp"

int main(){
  
  std::vector<std::string> fileInput;
  fileInput.push_back("../plume1GeV_run746.root");
  fileInput.push_back("../plume2GeV_run735.root");
  fileInput.push_back("../plume3GeV_run724.root");
  fileInput.push_back("../plume4GeV_run713.root");
  fileInput.push_back("../plume5GeV_run702.root");
  std::vector<float> theta0, theta0Error, radiationLength, radiationLengthError, measuredEnergy, momentum, momentumError;
  
  double energy = 1000.;
  int iterator = 0;
  
  for (auto file: fileInput) {
    std::cout << "Processing file " << file << std::endl;
    readerTTree myTree;
    myTree.openTtree(file.c_str(), "tree");
    myTree.getHistogram("kinkX");
    myTree.getKinkAngle();
    myTree.getHistogram("kinkXFit");
    myTree.getMeanKinkFit();
    myTree.printKinkAngle();
    theta0.push_back( myTree.calculateTheta0());
    theta0Error.push_back( myTree.calculateTheta0Error());
    radiationLength.push_back( myTree.calculateRadiationLength(energy));
    radiationLengthError.push_back( myTree.calculateRadiationLengthError(energy));
    measuredEnergy.push_back( myTree.calculateMeasuredEnergy(energy));
    momentum.push_back(energy);
    momentumError.push_back(energy*0.05);
    energy += 1000.0;
    
    std::cout << "Theta0 = " << theta0.at(iterator) << " +/- " << theta0Error.at(iterator) << std::endl;
    std::cout << "x/X0 = " << radiationLength.at(iterator) << " +/- " << radiationLengthError.at(iterator) << std::endl;
    std::cout << "Measured energy p = " << measuredEnergy.at(iterator) << std::endl;
    
    iterator++;
    
  }
  
  auto energyMax = std::max_element(std::begin(momentum), std::end(momentum));
  auto energyMin = std::min_element(std::begin(momentum), std::end(momentum));
  std::cout << "Fit will be in the range: [" << *energyMin << ";" << *energyMax << "]" << std::endl;
  
  graphPlotting myGraph;
  std::string highlandFormula = "13.6*pow([0],0.555)/x"; // \theta_{0} = \frac{13.6 (MeV)}{p} \cdot \left( \frac{x}{X_{0}} \right)^{0.555}
  std::unique_ptr<TF1> fitHighland( new TF1("fitHighland", highlandFormula.c_str(), *energyMin, *energyMax));
  fitHighland->SetParameter(0, 1.);
  std::unique_ptr<TF1> fitPolynome1(new TF1("fitPolynome1", "pol1", *energyMin, *energyMax));
  if (theta0.size() == momentum.size()){
    myGraph.plotGraphErrors(theta0.size(), momentum[0], theta0[0], momentumError[0], theta0Error[0], "fitHighland", "p (MeV)", "#theta_{0}", "theta0VsMomentum.png");
  }
  if (momentum.size() == radiationLength.size()) {
    myGraph.plotGraph(radiationLength.size(), momentum[0], radiationLength[0], "fitPolynome1", "p (MeV)", "#frac{x}{X_{0}}", "radiationLengthVsMomentum.png" );
  }
  if (momentum.size() == measuredEnergy.size()) {
    myGraph.plotGraph(measuredEnergy.size(), momentum[0], measuredEnergy[0], "fitPolynome1", "p (MeV)", "Measured p (Mev)", "momentumMeasuredVsMomentumTB.png");
  }
  
  return 0;
}
