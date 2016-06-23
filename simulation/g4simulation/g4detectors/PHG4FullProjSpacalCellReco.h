#ifndef PHG4FullProjSpacalCellReco_H
#define PHG4FullProjSpacalCellReco_H

#include <fun4all/SubsysReco.h>
#include <phool/PHTimeServer.h>
#include <string>
#include <map>
#include <vector>

class PHCompositeNode;
class PHG4CylinderCell;

class PHG4FullProjSpacalCellReco : public SubsysReco
{
 public:

  PHG4FullProjSpacalCellReco(const std::string &name = "HCALCELLRECO");

  virtual ~PHG4FullProjSpacalCellReco(){}
  
  //! module initialization
  int InitRun(PHCompositeNode *topNode);
  
    //! event processing
  int process_event(PHCompositeNode *topNode);
  
  //! end of process
  int End(PHCompositeNode *topNode);
  
  void Detector(const std::string &d) {detector = d;}

  void checkenergy(const int i=1) {chkenergyconservation = i;}

  double get_timing_window_min(const int i) {return tmin_default;}
  double get_timing_window_max(const int i) {return tmax_default;}
  void   set_timing_window(const int i, const double tmin, const double tmax) {
    tmin_default = tmin; tmax_default = tmax;
  }
  void   set_timing_window_defaults(const double tmin, const double tmax) {
    tmin_default = tmin; tmax_default = tmax;
  }
  
 protected:

  int CheckEnergy(PHCompositeNode *topNode);

  std::string detector;
  std::string hitnodename;
  std::string cellnodename;
  std::string geonodename;
  std::string seggeonodename;

  PHTimeServer::timer _timer;
  int chkenergyconservation;
  std::map<unsigned int, PHG4CylinderCell *> celllist;

  //! timing window size in ns. This is for a simple simulation of the ADC integration window starting from 0ns to this value. Default to infinity, i.e. include all hits
  double tmin_default;
  double tmax_default;
  std::map<int, std::pair<double,double> > tmin_max;
};

#endif
