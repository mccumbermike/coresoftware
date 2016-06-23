#ifndef __PHG4TPCCLUSTERIZER__
#define __PHG4TPCCLUSTERIZER__

#include <fun4all/SubsysReco.h>
#include <vector>
#include <limits.h>

class PHG4TPCClusterizer : public SubsysReco {
 public:
  PHG4TPCClusterizer(const char *name = "PHG4SvtxClusterizer",
                     unsigned int phi_s = 10, unsigned int z_s = 5,
		     unsigned int min_layer = 0, unsigned int max_layer = UINT_MAX)
    : SubsysReco(name), _phi_span(phi_s), _z_span(z_s), energy_cut(-1.),
      _min_layer(min_layer), _max_layer(max_layer) {}
  ~PHG4TPCClusterizer() {}

  //! module initialization
  int Init(PHCompositeNode *topNode) { return 0; }

  //! run initialization
  int InitRun(PHCompositeNode *topNode);

  //! event processing
  int process_event(PHCompositeNode *topNode);

  //! end of process
  int End(PHCompositeNode *topNode) { return 0; }

  void setEnergyCut(double ecut) { energy_cut = ecut; }

 private:

  std::vector<int> nhits;
  std::vector<float> amps;
  std::vector<int> cellids;
  int nphibins;
  int nzbins;

  void reset();

  unsigned int _phi_span;
  unsigned int _z_span;
  double energy_cut;
  unsigned int _min_layer;
  unsigned int _max_layer;
};

#endif
