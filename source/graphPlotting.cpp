//
//  graphPlotting.cpp
//  main
//
//  Created by Benjamin BOITRELLE on 25/10/2016.
//
//

#include "graphPlotting.hpp"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TStyle.h"

graphPlotting::graphPlotting(){

}

void graphPlotting::plotGraph(int numberOfEntries, float &variable1, float &variable2, std::string fit, std::string xTitle, std::string yTitle, std::string outputFile){
  
  std::unique_ptr<TCanvas> canvas (new TCanvas("canvas", "canvas", 1200, 1100));
  gStyle->SetOptFit(1);
  std::unique_ptr<TGraph> graph(new TGraph(numberOfEntries, &variable1, &variable2));
  graph->Draw("A*");
  graph->Fit(fit.c_str());
  graph->GetHistogram()->SetXTitle(xTitle.c_str());
  graph->GetHistogram()->SetYTitle(yTitle.c_str());
  canvas->SaveAs(outputFile.c_str());
}

void graphPlotting::plotGraphErrors(int numberOfEntries, float &variable1, float &variable2, float &errorVariable1, float &errorVariable2, std::string fit, std::string xTitle, std::string yTitle, std::string outputFile){
  
  std::unique_ptr<TCanvas> canvas (new TCanvas("canvas", "canvas", 1200, 1100));
  gStyle->SetOptFit(1);
  std::unique_ptr<TGraphErrors> graphErrors (new TGraphErrors(numberOfEntries, &variable1, &variable2, &errorVariable1, &errorVariable2));
  graphErrors->Draw("A*");
  graphErrors->Fit(fit.c_str());
  graphErrors->GetHistogram()->SetXTitle(xTitle.c_str());
  graphErrors->GetHistogram()->SetYTitle(yTitle.c_str());
  canvas->SaveAs(outputFile.c_str());
  
}