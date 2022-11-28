#include "IMPL/SimTrackerHitImpl.h"
#include "UTIL/LCWarning.h"

using namespace EVENT ;


namespace IMPL {
  
  int SimTrackerHitImpl::getCellID0() const { return _cellID0 ; }
  int SimTrackerHitImpl::getCellID1() const { return _cellID1 ; }

  const double * SimTrackerHitImpl::getPosition() const { return _pos ; }

  // DEPRECATED. use getEDep()
  float SimTrackerHitImpl::getdEdx() const {
        
      UTIL::LCWarning::getInstance().printWarning( "SIMTRACKERHIT_DEPRECATED_GETDEDX" ) ;

      //return _dEdx ;
      return getEDep() ;
  }

  float SimTrackerHitImpl::getEDep() const { return _EDep ; }

  float SimTrackerHitImpl::getTime() const { return _time ; }

  EVENT::MCParticle * SimTrackerHitImpl::getMCParticle() const { return _particle ; }

  float SimTrackerHitImpl::getPathLength() const { return _pathLength ; }

  const float* SimTrackerHitImpl::getMomentum() const { return _p ; }

  void SimTrackerHitImpl::setCellID0( int id0) {
    checkAccess("SimTrackerHitImpl::setCellID0") ;
    _cellID0 = id0 ; 
  }

  void SimTrackerHitImpl::setCellID1( int id1) {
    checkAccess("SimTrackerHitImpl::setCellID1") ;
    _cellID1 = id1 ; 
  }

  void SimTrackerHitImpl::setPosition( const double pos[3]){ 
    checkAccess("SimTrackerHitImpl::setPosition") ;
    _pos[0] = pos[0] ; 
    _pos[1] = pos[1] ; 
    _pos[2] = pos[2] ; 
  }

  // DEPRECATED. use setEDep()
  void SimTrackerHitImpl::setdEdx( float dedx )  {

    UTIL::LCWarning::getInstance().printWarning( "SIMTRACKERHIT_DEPRECATED_SETDEDX" ) ;

    //checkAccess("SimTrackerHitImpl::setdEdx") ;
    //_dEdx = dedx ; 
    setEDep( dedx ) ;
  }

  void SimTrackerHitImpl::setEDep( float e )  {
    checkAccess("SimTrackerHitImpl::setEDep") ;
    _EDep = e ;
  }

  void SimTrackerHitImpl::setTime( float t )  { 
    checkAccess("SimTrackerHitImpl::setTime") ;
    _time = t ; 
  }

  void SimTrackerHitImpl::setMCParticle( EVENT::MCParticle* particle)  {
    checkAccess("SimTrackerHitImpl::setMCParticle") ;
    _particle = particle; 
  }

  void SimTrackerHitImpl::setMomentum( const float p[3] )  { 

    setMomentum( p[0], p[1], p[2] ) ; 
  }

  void SimTrackerHitImpl::setMomentum( float px, float py, float pz ) {

    checkAccess("SimTrackerHitImpl::setMomentum") ;
    _p[0] = px ;
    _p[1] = py ;
    _p[2] = pz ;

  }
 	
  void SimTrackerHitImpl::setPathLength(float pathLength){
    checkAccess("SimTrackerHitImpl::setPathLength") ;
    _pathLength = pathLength ;
  }



} // namespace IMPL
