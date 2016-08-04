#ifndef PHG4TruthTrackingAction_h
#define PHG4TruthTrackingAction_h

#include "PHG4TrackingAction.h"

#include <Geant4/G4LorentzVector.hh>

#include <map>

class PHG4TruthInfoContainer;
class PHG4TruthEventAction;

class PHG4TruthTrackingAction : public PHG4TrackingAction
{
public:

  //! constructor
  PHG4TruthTrackingAction( PHG4TruthEventAction* );

  //! destructor
  virtual ~PHG4TruthTrackingAction() {}

  //! tracking action
  virtual void PreUserTrackingAction(const G4Track*);

  virtual void PostUserTrackingAction(const G4Track*);

  //! Set pointers to the i/o nodes
  virtual void SetInterfacePointers( PHCompositeNode* );

  int ResetEvent(PHCompositeNode *);

private:

  std::map<G4LorentzVector,int> VertexMap;

  //! pointer to the "owning" event action
  PHG4TruthEventAction* eventAction_;

  //! pointer to truth information container
  PHG4TruthInfoContainer* truthInfoList_;
};


#endif
