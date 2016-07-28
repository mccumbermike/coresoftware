#ifndef PHG4Prototype2InnerHcalDetector_h
#define PHG4Prototype2InnerHcalDetector_h

#include "PHG4Parameters.h"

#include <g4main/PHG4Detector.h>

#include <Geant4/globals.hh>
#include <Geant4/G4RotationMatrix.hh>
#include <Geant4/G4SystemOfUnits.hh>
#include <Geant4/G4TwoVector.hh>
#include <Geant4/G4Types.hh>

#include <map>
#include <vector>
#include <set>

class G4AssemblyVolume;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4VSolid;

class PHG4Prototype2InnerHcalDetector: public PHG4Detector
{

  public:

  //! constructor
 PHG4Prototype2InnerHcalDetector( PHCompositeNode *Node,  PHG4Parameters *parameters, const std::string &dnam);

  //! destructor
  virtual ~PHG4Prototype2InnerHcalDetector(){}

  //! construct
  virtual void Construct( G4LogicalVolume* world );

  virtual void Print(const std::string &what = "ALL") const;

  //!@name volume accessors
  //@{
  int IsInPrototype2InnerHcal(G4VPhysicalVolume*) const;
  //@}

  void SuperDetector(const std::string &name) {superdetector = name;}
  const std::string SuperDetector() const {return superdetector;}
  int get_Layer() const {return layer;}

  G4LogicalVolume* ConstructSteelPlate(G4LogicalVolume* hcalenvelope);
  G4LogicalVolume* ConstructScintillatorBox(G4LogicalVolume* hcalenvelope);
  G4LogicalVolume* ConstructScintiTileU1(G4LogicalVolume* hcalenvelope);
  G4LogicalVolume* ConstructScintiTileU2(G4LogicalVolume* hcalenvelope);
  double GetScintiAngle();

  protected:
  int ConstructInnerHcal(G4LogicalVolume* sandwich);
  int DisplayVolume(G4VSolid *volume,  G4LogicalVolume* logvol, G4RotationMatrix* rotm=NULL);
  PHG4Parameters *params;
  G4LogicalVolume *innerhcalsteelplate;
  G4AssemblyVolume *innerhcalassembly;
  G4TwoVector steel_plate_corner_upper_left;
  G4TwoVector steel_plate_corner_upper_right;
  G4TwoVector steel_plate_corner_lower_right;
  G4TwoVector steel_plate_corner_lower_left;
  double scinti_u1_front_size;
  G4TwoVector scinti_u1_corner_upper_left;
  G4TwoVector scinti_u1_corner_upper_right;
  G4TwoVector scinti_u1_corner_lower_right;
  G4TwoVector scinti_u1_corner_lower_left;
  G4TwoVector scinti_u2_corner_upper_left;
  G4TwoVector scinti_u2_corner_upper_right;
  G4TwoVector scinti_u2_corner_lower_right;
  G4TwoVector scinti_u2_corner_lower_left;
  double inner_radius;
  double outer_radius;
  double scinti_x;
  double steel_x;
  double steel_z;
  double size_z;
  double scinti_tile_z;
  double scinti_tile_thickness;
  double scinti_box_smaller;
  double gap_between_tiles;
  double scinti_gap;
  double tilt_angle;
  double deltaphi;
  double volume_steel;
  double volume_scintillator;

  int n_scinti_plates;
  int n_steel_plates;

  int active;
  int absorberactive;

  int layer;
  std::string detector_type;
  std::string superdetector;
  std::string scintilogicnameprefix;
};

#endif
