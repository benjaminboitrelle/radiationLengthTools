//
//  readerTTree.hpp
//  main
//
//  Created by Benjamin BOITRELLE on 14/07/2016.
//
//

#ifndef readerTTree_hpp
#define readerTTree_hpp

#include <stdio.h>
#include <string>
#include "TTree.h"
#include "TH1.h"

class readerTTree{
  
public:
  readerTTree();
  void openTtree(std::string fileName, std::string treeName);
  void getTreeBranch(std::string branchName, float branchInput);
  void getHistogram(std::string branchName);
  void getKinkAngle();
  void getMeanKinkFit();
  float calculateTheta0();
  float calculateTheta0Error();
  float calculateRadiationLength(double energy);
  float calculateRadiationLengthError(double energy);
  float calculateRadiationLengthCorrected();
  float calculateMeasuredEnergy(double energy);
  void printKinkAngle();
  void printEntriesNumber();
  void prindMeanKinkFit();
  TTree* getTree();
  int getEntriesNumber();
  //std::pair<float, float> GetKinkAnlge(TTree *tree, std::string variable, std::string cut, int const z);
  
private:
  TTree* m_tree;
  TH1F* m_histogram;
  float m_meanKinkFit;
  float m_kinkAngle;
  float m_kinkAngleError;
  float m_theta0;
  float m_theta0Error;
  float m_radiationLength;
  float m_radiationLengthError;
  float m_radiationLengthCorrected;
  float m_measuredEnergy;
  int m_nEntries;
};

#endif /* readerTTree_hpp */
