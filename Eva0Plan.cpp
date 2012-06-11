/**
 * @file Eva0Plan.cpp
 * @brief Planning code using RRT
 * @author A. Huaman / M. Grey
 * @date 2012-06-11
 */
#include <wx/wx.h>
#include <GUI/Viewer.h>
#include <GUI/GUI.h>
#include <GUI/RSTSlider.h>
#include <GUI/RSTFrame.h>

#include "Eva0Tab.h"

/**
 * @function ArmPlanning  
 */
bool Eva0Tab::ArmPlanning() {

  switch( mConfMode ) {
    
    /** LEFT ARM */
  case LEFT_ARM: {
    printf( "**Start Left Arm Plan only** \n" );
    mPPa = new PathPlanner<RRT>( *world, false );
    bool la = mPPa->planPath( mRobotId, 
			      mLA_Links, 
			      mStartConf_L, 
			      mTargetConf_L, 
			      mPath_L, 
			      true,  
			      true, 
			      5000 );
    if( la == true ) {
      printf("** Found a path with %d nodes \n", mPath_L.size() );
    } else {
      printf( "** Did not find a path \n" );
    }
    
    printf( "** End Left Arm Plan only ** \n" );
  } break;

    /** RIGHT ARM*/
  case RIGHT_ARM: {
    printf( "**Start Right Arm Plan only ** \n" );
    mPPa = new PathPlanner<RRT>( *world, false );
    bool ra = mPPa->planPath( mRobotId, 
			      mRA_Links, 
			      mStartConf_R, 
			      mTargetConf_R, 
			      mPath_R, 
			      true,  
			      true, 
			      5000 );
    if( ra == true ) {
      printf("** Found a path with %d nodes \n", mPath_R.size() );
    } else {
      printf( "** Did not find a path \n" );
    }
    
    printf( "** End Right Arm Plan only ** \n" );
  } break;

    /** BOTH ARMS */
  case BOTH_ARMS: {

    printf("** Start Both Arms Plan ** \n");
    mPPa = new PathPlanner<RRT>( *world, false );
    bool ra = mPPa->planPath( mRobotId, 
			      mRA_Links, 
			      mStartConf_R, 
			      mTargetConf_R, 
			      mPath_R, 
			      true,  
			      true, 
			      5000 );

    bool la = mPPa->planPath( mRobotId, 
			      mLA_Links, 
			      mStartConf_L, 
			      mTargetConf_L, 
			      mPath_L, 
			      true,  
			      true, 
			      5000 );    
    if( ra == true && la == true ) {
      printf( " ** Found paths for both left (%d) and right(%d) arms \n", mPath_L.size(), mPath_R.size() );
    } else {
      printf( " ** Did not find a path for both arms ** \n" );
    }
  } break;

  } // end switch
return true;
}

