#ifndef DetLayers_GeometricSearchDet_h
#define DetLayers_GeometricSearchDet_h

#include "Geometry/CommonDetUnit/interface/GeomDet.h"
#include "Geometry/Surface/interface/BoundSurface.h"
#include "TrackingTools/DetLayers/interface/DetGroup.h"

#include "TrackingTools/TrajectoryState/interface/TrajectoryStateOnSurface.h"
#include "TrackingTools/GeomPropagators/interface/Propagator.h"

#include <vector>

using namespace std;
class MeasurementEstimator;


class GeometricSearchDet {
 public:
  typedef pair<const GeometricSearchDet*,TrajectoryStateOnSurface> DetWithState;
  typedef BoundSurface::PositionType        PositionType;
  typedef BoundSurface::RotationType        RotationType;
  typedef TrajectoryStateOnSurface          TrajectoryState;
  
  virtual ~GeometricSearchDet() {};
  
  /// The surface of the GeometricSearchDet
  virtual const BoundSurface& surface() const = 0;
  
  /// Returns position of the surface
  virtual const Surface::PositionType& position() const {return surface().position();}

  /// Returns basic components, if any
  //virtual std::vector< const GeomDet*> basicComponents() const = 0;

  /// Returns direct components, if any
  virtual vector<const GeometricSearchDet*> components() const = 0;

  /* Returns basic components. For the moment they are GeomDet, 
   * but they could become MeasurementDet
   */
  virtual vector<const GeomDet*> basicComponents() const = 0;


  /** tests the geometrical compatibility of the Det with the predicted state.
   *  The  FreeTrajectoryState argument is propagated to the Det surface using
   *  the Propagator argument. The resulting TrajectoryStateOnSurface is
   *  tested for compatibility with the surface bounds.
   *  If compatible, a pair< true, propagatedState> is returned.
   *  If the propagation fails, or if the state is not compatible,
   *  a pair< false, propagatedState> is returned.
   */
  virtual pair<bool, TrajectoryStateOnSurface>
  compatible( const TrajectoryStateOnSurface& ts, const Propagator&, 
	      const MeasurementEstimator&) const=0;

  /** Returns all Dets compatible with a trajectory state 
   *  according to the estimator est.
   *  The startingState should be propagated to the surface of each compatible 
   *  Det using the Propagator passed as an argument. 
   *  The default implementation should be overridden in dets with
   *  specific surface types to avoid propagation to a generic Surface
   */
  virtual vector<DetWithState> 
  compatibleDets( const TrajectoryStateOnSurface& startingState,
		  const Propagator& prop, 
		  const MeasurementEstimator& est) const=0;

  /** Similar to compatibleDets(), but the compatible Dets are grouped in 
   *  one or more groups.
   *  Dets are put in the same group if they are mutually exclusive for track crossing,
   *  i.e. a reconstructible track cannot cross more than one Det from a group.
   *  Pathological tracks (spirals etc.) can of course violate this rule. 
   *  <BR>
   *  The DetGroups are sorted in the sequence of crossing by a track.
   *  In order to define the direction of crossing the Propagator used in this method 
   *  should have a defined direction() : either "alongMomentum" or 
   *  "oppositeToMomentum" but not "anyDirection".
   *  <BR> 
   *  The three signatures of this method differ by the input trajectory state arguments:
   *  the starting state can be a TrajectoryStateOnSurface or a FreeTrajectoryState,
   *  and the state on this CompositeDet may be already known or not.
   *  The last two arguments are as for the method compatibleDets().
   *  <BR>
   *  First signature: The first argument is a TrajectoryStateOnSurface, usually not 
   *  on the surface of this CompositeDet.
   */
  virtual vector<DetGroup> 
  groupedCompatibleDets( const TrajectoryStateOnSurface& startingState,
			 const Propagator& prop,
			 const MeasurementEstimator& est) const = 0;


  virtual bool hasGroups() const = 0;  
};

#endif
