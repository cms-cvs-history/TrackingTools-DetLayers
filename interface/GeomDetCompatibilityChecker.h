#ifndef DetLayers_GeomDetCompatibilityChecker_h
#define DetLayers_GeomDetCompatibilityChecker_h


#include "Geometry/CommonDetUnit/interface/GeomDet.h"
#include "TrackingTools/TrajectoryState/interface/TrajectoryStateOnSurface.h"
#include "TrackingTools/GeomPropagators/interface/Propagator.h"
#include "TrackingTools/PatternTools/interface/MeasurementEstimator.h"

/** helper class which checks if a GeomDet is geometrically 
 *  compatible with a TrajectoryState
 */

using namespace std;

class GeomDetCompatibilityChecker{
 public:
  GeomDetCompatibilityChecker(){};
  ~GeomDetCompatibilityChecker(){};

  
  /** tests the geometrical compatibility of the GeomDet with the predicted state.
   *  The  TrajectoryState argument is propagated to the GeomDet surface using
   *  the Propagator argument. The resulting TrajectoryStateOnSurface is
   *  tested for compatibility with the surface bounds.
   *  If compatible, a pair< true, propagatedState> is returned.
   *  If the propagation fails, or if the state is not compatible,
   *  a pair< false, propagatedState> is returned.
   */
  
  pair<bool, TrajectoryStateOnSurface>  isCompatible(const GeomDet* theDet,
						     const TrajectoryStateOnSurface& ts,
						     const Propagator& prop, 
						     const MeasurementEstimator& est) const;  
};



#endif