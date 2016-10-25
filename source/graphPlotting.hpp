//
//  graphPlotting.hpp
//  main
//
//  Created by Benjamin BOITRELLE on 25/10/2016.
//
//

#ifndef graphPlotting_hpp
#define graphPlotting_hpp

#include <stdio.h>
#include "TGraph.h"
#include "TGraphErrors.h"

class graphPlotting{

public:
  graphPlotting();
  void plotGraph(int numberOfEntries, float &variable1, float &variable2, std::string fit, std::string xTitle, std::string yTitle, std::string outputFile);
  void plotGraphErrors(int numberOfEntries, float &variable1, float &variable2, float &errorVariable1, float &errorVariable2, std::string fit, std::string xTitle, std::string yTitle, std::string outputFile);
  
};
#endif /* graphPlotting_hpp */

