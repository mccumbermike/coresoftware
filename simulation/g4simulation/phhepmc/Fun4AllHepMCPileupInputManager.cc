#include "Fun4AllHepMCPileupInputManager.h"

#include <fun4all/Fun4AllServer.h>
#include <fun4all/Fun4AllSyncManager.h>
#include <fun4all/Fun4AllReturnCodes.h>
#include <phool/recoConsts.h>
#include <phool/getClass.h>

#include <ffaobjects/RunHeader.h>
#include <PHHepMCGenEvent.h>

#include <frog/FROG.h>
#include <phool/PHCompositeNode.h>
#include <phool/PHDataNode.h>
#include <phool/PHRandomSeed.h>

#include <HepMC/IO_GenEvent.h>
#include <HepMC/GenEvent.h>

#include <TString.h>
#include <TPRegexp.h>

#include <fstream>
#include <istream>
#include <iostream>
#include <sstream>

#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/filter/bzip2.hpp>
#include <boost/iostreams/filter/gzip.hpp>

#include <cstdlib>
#include <memory>

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

using namespace std;

static boost::iostreams::filtering_streambuf<boost::iostreams::input> zinbuffer;
static const double toMM = 1.e-12;

Fun4AllHepMCPileupInputManager::Fun4AllHepMCPileupInputManager(
    const string &name, const string &nodename, const string &topnodename)
  : Fun4AllHepMCInputManager(name, nodename, topnodename),
    _min_integration_time(-1000.0),
    _max_integration_time(+1000.0),
    _collision_rate(100.0),
    _time_between_crossings(106.0),
    _ave_coll_per_crossing(1.0), // recalculated
    _min_crossing(0),            // recalculated
    _max_crossing(0) {           // recalculated

  RandomGenerator = gsl_rng_alloc(gsl_rng_mt19937);
  seed = PHRandomSeed(); // fixed seed is handled in this funtcion
  gsl_rng_set(RandomGenerator,seed);
  
  return;
}

Fun4AllHepMCPileupInputManager::~Fun4AllHepMCPileupInputManager() {
  gsl_rng_free (RandomGenerator);
}

int Fun4AllHepMCPileupInputManager::run(const int nevents) {

  // toss multiple crossings all the way back
  for (int icrossing = _min_crossing; icrossing <= _max_crossing; ++icrossing) {
  
    double crossing_time = _time_between_crossings * icrossing;

    int ncollisions = gsl_ran_poisson(RandomGenerator,_ave_coll_per_crossing);
    if (icrossing == 0) --ncollisions;

    ncollisions = 2;
    
    for (int icollision = 0; icollision < ncollisions; ++icollision) {
      double t0 = crossing_time;
      t0 *= 1.0;
      //_generator->set_t0(crossing_time);
      //_generator->process_event(topNode);
  
    readagain:

      if (!isopen) {
        if (!filelist.size()) {
          if (verbosity > 0) {
            cout << Name() << ": No Input file open" << endl;
          }
          return -1;
        } else {
          if (OpenNextFile()) {
            cout << Name() << ": No Input file from filelist opened" << endl;
            return -1;
          }
        }
      }
      //  cout << "running event " << nevents << endl;
      PHNodeIterator iter(topNode);
      PHHepMCGenEvent *genevent =
	findNode::getClass<PHHepMCGenEvent>(topNode, "PHHepMCGenEvent");
      evt = genevent->getEvent();
      if (save_evt)  // if an event was pushed back, copy saved pointer and reset
	// save_evt pointer
	{
	  evt = save_evt;
	  save_evt = NULL;
	} else {
	if (readoscar) {
	  evt = ConvertFromOscar();
	} else {
	  evt = ascii_in->read_next_event();
	}
      }
      genevent->addEvent(evt);
      if (!evt) {
	if (verbosity > 1) {
	  cout << "error type: " << ascii_in->error_type()
	       << ", rdstate: " << ascii_in->rdstate() << endl;
	}
	fileclose();
	goto readagain;
      } else {
	mySyncManager->CurrentEvent(evt->event_number());
	if (verbosity > 0) {
	  cout << "hepmc evt no: " << evt->event_number() << endl;
	}
      }
      events_total++;
      events_thisfile++;
      // check if the local SubsysReco discards this event
      if (RejectEvent() != Fun4AllReturnCodes::EVENT_OK) {
	ResetEvent();
	goto readagain;
      }

    }
  }
  
  return 0;
}
