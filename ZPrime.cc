// Adapted form main41.cc, which is a part of the PYTHIA event generator.
// Copyright (C) 2014 Torbjorn Sjostrand.
// PYTHIA is licenced under the GNU GPL version 2, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

// author: Aidan Randle-Conde (aidan.randleconde@gmail.com)

#include "Pythia8/Pythia.h"

using namespace Pythia8;

#include <iostream>

int main(int argc, char* argv[]) {
  // This executable can take command line parameters.
  // These strings hold the variables names
  char* mass_string    = "2500" ;
  char* nEvents_string = "10" ;
  char* CM_string      = "8" ;
  if(argc>1) mass_string    = argv[1] ;
  if(argc>2) nEvents_string = argv[2] ;
  if(argc>3) CM_string      = argv[3] ;
  
  // Now convert everything to the correct types.
  int model = kZprimeSSM ;
  int model_int = atoi(model_string) ;
  if(model_int==1) model = kZprimeI ;
  int nEvents = atoi(nEvents_string) ;
  
  // Generator. Process selection. LHC initialization.
  Pythia pythia;
  
  char CMString[50] ;
  sprintf(CMString, "Beams:eCM = %s", CM_string) ;
  pythia.readString(CMString) ;
  
  // Turn on process, set mass
  pythia.readString("NewGaugeBoson:ffbar2gmZZprime  = on ");
  pythia.readString("Zprime:gmZmode = 3");
  char massString[50] ;
  sprintf(massString, "32:m0 = %s", mass_string) ;
  pythia.readString(massString); 
  
  // Switch off all Z/Z' decays and then switch back on those to light leptons.
  pythia.readString("32:onMode = off"); 
  pythia.readString("32:onIfAny = 11");
  
  // Set the random seed based on the seconds of the clock.
  //  If you run two jobs in parallel, separate them by ~2 seconds to be sure to get different seeds!
  pythia.readString("Random:setSeed = on");
  pythia.readString("Random:seed = 0");
  
  // Initialise pythia
  pythia.init();

  // Begin event loop. Generate event. Skip if error.
  for (int iEvent = 0; iEvent < nEvents; ++iEvent) {
    if (!pythia.next()) continue;
  }
  
  // Print everything to the terminal so we can take the cross section.
  pythia.stat();

  // Done.
  return 0;
}
