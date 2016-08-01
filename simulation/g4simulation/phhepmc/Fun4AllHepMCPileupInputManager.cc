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

using namespace std;

static boost::iostreams::filtering_streambuf<boost::iostreams::input> zinbuffer;
static const double toMM = 1.e-12;

Fun4AllHepMCPileupInputManager::Fun4AllHepMCPileupInputManager(const string &name, const string &nodename, const string &topnodename) :
  Fun4AllHepMCInputManager(name, nodename, topnodename) {
  return;
}

Fun4AllHepMCPileupInputManager::~Fun4AllHepMCPileupInputManager() {}

int Fun4AllHepMCPileupInputManager::run(const int nevents) {
readagain:
  if (!isopen) {
    if (!filelist.size())

    {
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
  return 0;
}
