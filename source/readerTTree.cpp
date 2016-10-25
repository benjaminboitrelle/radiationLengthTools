//
//  readerTTree.cpp
//  main
//
//  Created by Benjamin BOITRELLE on 14/07/2016.
//
//

#include "readerTTree.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TF1.h"
#include "TSystem.h"
#include "TCanvas.h"

readerTTree::readerTTree(){
  m_kinkAngle = 0.;
  m_kinkAngleError  =0.;
  m_meanKinkFit = 0.;
  m_theta0 = 0.;
  m_theta0Error = 0.;
  m_nEntries = 0;
  m_radiationLength = 0.;
  m_radiationLengthError = 0.;
  m_radiationLengthCorrected = 0.;
  m_measuredEnergy = 0.;
  m_tree = nullptr;
  m_histogram = nullptr;
}

void readerTTree::openTtree(std::string fileName, std::string treeName){
  TFile *file = TFile::Open(fileName.c_str());
  m_tree = (TTree*)file->Get(treeName.c_str());
  m_nEntries = m_tree->GetEntries();
}

void readerTTree::getTreeBranch(std::string branchName, float branchInput){
  m_tree->SetBranchAddress(branchName.c_str(), &branchInput);
}

void readerTTree::getHistogram(std::string branchName){
  TCanvas canvas;
  std::string outputHisto = "hTmp";
  std::ostringstream ss;
  ss << branchName << " >> " << outputHisto;
  m_tree->Draw(ss.str().c_str());
  m_histogram = (TH1F*)gDirectory->Get(outputHisto.c_str());
  if (m_histogram == nullptr){
    std::cout << "No histogram" << std::endl;
  }
}

void readerTTree::getMeanKinkFit(){
  m_meanKinkFit = m_histogram->GetMean();
}

void readerTTree::getKinkAngle(){
 
  TCanvas canvas;
  std::unique_ptr<TF1> fit (new TF1("fit","gaus",-m_histogram->GetRMS(),m_histogram->GetRMS()));
  fit->SetParLimits(1,-m_histogram->GetRMS(),m_histogram->GetRMS());
  fit->SetParLimits(2,0.5*m_histogram->GetRMS(),2*m_histogram->GetRMS());
  TFitResultPtr p = m_histogram->Fit("fit","QEMRIS");
  m_kinkAngle = fit->GetParameter(2);
  m_kinkAngleError = fit->GetParError(2);
}

float readerTTree::calculateTheta0(){
  m_theta0 = sqrt((m_kinkAngle*m_kinkAngle) - m_meanKinkFit);
  return m_theta0;
}

float readerTTree::calculateTheta0Error(){
  m_theta0Error = m_kinkAngleError;
  return m_theta0Error;
}

float readerTTree::calculateRadiationLength(double energy){
  m_radiationLength = pow((m_theta0*energy)/13.6, 1/0.555);
  return m_radiationLength;
}

float readerTTree::calculateRadiationLengthError(double energy){
  m_radiationLengthError = sqrt(pow(1.8/13.6,2)*pow(energy*m_theta0/13.6,2*(1.8-1))*(pow(energy*0.05,2)*pow(m_theta0,2) + pow(energy,2)*pow(m_theta0Error, 2)));
  return m_radiationLengthError;
}

float readerTTree::calculateMeasuredEnergy(double energy){
  m_measuredEnergy = (13.6/m_theta0)*pow(m_radiationLength,0.555);
  return m_measuredEnergy;
}

float readerTTree::calculateRadiationLengthCorrected(){
  m_radiationLengthCorrected = pow((m_theta0*m_measuredEnergy)/13.6, 1/0.555);
  return m_radiationLengthCorrected;
}

void readerTTree::prindMeanKinkFit(){
  std::cout << "Mean kink fit: " << m_meanKinkFit << std::endl;
}

void readerTTree::printEntriesNumber(){
  std::cout << "Number of entries: " << m_nEntries << std::endl;
}

void readerTTree::printKinkAngle(){
  std::cout << "Kink angle: " << m_kinkAngle << " +/- " << m_kinkAngleError << std::endl;
}

TTree* readerTTree::getTree(){
  return m_tree;
}

int readerTTree::getEntriesNumber(){
  return m_nEntries;
}

