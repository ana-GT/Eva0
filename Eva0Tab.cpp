/*
 * Copyright (c) 2010, Georgia Tech Research Corporation
 * 
 * Humanoid Robotics Lab      Georgia Institute of Technology
 * Director: Mike Stilman     http://www.golems.org
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *     * Redistributions of source code must retain the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials
 *       provided with the distribution.
 *     * Neither the name of the Georgia Tech Research Corporation nor
 *       the names of its contributors may be used to endorse or
 *       promote products derived from this software without specific
 *       prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY GEORGIA TECH RESEARCH CORPORATION ''AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL GEORGIA
 * TECH RESEARCH CORPORATION BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include "Eva0Tab.h"

#include <wx/wx.h>
#include <GUI/Viewer.h>
#include <GUI/GUI.h>
#include <GUI/RSTSlider.h>
#include <GUI/RSTFrame.h>

using namespace std; 

// Control IDs
enum Eva0TabEvents {
  button_SetStartConf_R = 50,
  button_ShowStartConf_R,
  button_SetTargetConf_R,
  button_ShowTargetConf_R,
  
  button_SetStartConf_L,
  button_ShowStartConf_L,
  button_SetTargetConf_L,
  button_ShowTargetConf_L,
  button_Plan,
  button_Execute
};

// Handlers for UI changes
BEGIN_EVENT_TABLE(Eva0Tab, wxPanel)
EVT_COMMAND( wxID_ANY, wxEVT_COMMAND_BUTTON_CLICKED, Eva0Tab::OnButton )
EVT_COMMAND( wxID_ANY, wxEVT_COMMAND_RADIOBOX_SELECTED, Eva0Tab::OnRadio )
END_EVENT_TABLE ()

// Class constructor for the tab: Each tab will be a subclass of RSTTab
IMPLEMENT_DYNAMIC_CLASS(Eva0Tab, RSTTab)

// Sizer for ConfigTab
wxBoxSizer* Eva0TabSizer;


const int Eva0Tab::sNumHandLinks = 9;
const int Eva0Tab::sNumArmLinks = 7;
const char* Eva0Tab::sLH_Ids[sNumHandLinks] = {"LH_F00", "LH_F01", "LH_F02", "LH_F10", "LH_F11", "LH_F12", "LH_F20", "LH_F21", "LH_F22"};
const char* Eva0Tab::sRH_Ids[sNumHandLinks] = {"RH_F00", "RH_F01", "RH_F02", "RH_F10", "RH_F11", "RH_F12", "RH_F20", "RH_F21", "RH_F22"};
const char* Eva0Tab::sLA_Ids[sNumArmLinks] = {"LJ1", "LJ2", "LJ3", "LJ4", "LJ5", "LJ6", "LJ7"};
const char* Eva0Tab::sRA_Ids[sNumArmLinks] = {"RJ1", "RJ2", "RJ3", "RJ4", "RJ5", "RJ6", "RJ7"};
const char* Eva0Tab::sBase_Id = "BASE1";

/**
 * @function Eva0Tab
 * @brief Constructor
 */
Eva0Tab::Eva0Tab(wxWindow *parent, 
		 const wxWindowID id,
		 const wxPoint& pos, 
		 const wxSize& size, 
		 long style) : RSTTab(parent, id, pos, size, style) {

  Eva0TabSizer = new wxBoxSizer( wxHORIZONTAL );

  // ** RIGHT ARM CONFIGURATION **
  wxStaticBox* setConfBox_R = new wxStaticBox(this, -1, wxT("Right Arm"));
  wxStaticBoxSizer* setConfBoxSizer_R = new wxStaticBoxSizer(setConfBox_R, wxVERTICAL);

  // Put buttons in
  setConfBoxSizer_R->Add( new wxButton(this, button_SetStartConf_R, wxT("Set Start Conf")),
			  0, wxALL, 1 ); 
  setConfBoxSizer_R->Add( new wxButton(this, button_ShowStartConf_R, wxT("Show Start Conf")),
			0, wxALL, 1 ); 
  setConfBoxSizer_R->Add( new wxButton(this, button_SetTargetConf_R, wxT("Set Target Conf")),
			  0, wxALL, 1 ); 
  setConfBoxSizer_R->Add( new wxButton(this, button_ShowTargetConf_R, wxT("Show Target Conf")),
			  0, wxALL, 1 ); 
   
  // ** Add to Eva0TabSizer **
  Eva0TabSizer->Add( setConfBoxSizer_R, 1, wxEXPAND | wxALL, 4 );

  // ** LEFT ARM CONFIGURATION **
  wxStaticBox* setConfBox_L = new wxStaticBox(this, -1, wxT("Left Arm"));
  wxStaticBoxSizer* setConfBoxSizer_L = new wxStaticBoxSizer(setConfBox_L, wxVERTICAL);

  // Put buttons in
  setConfBoxSizer_L->Add( new wxButton(this, button_SetStartConf_L, wxT("Set Start Conf")),
			  0, wxALL, 1 ); 
  setConfBoxSizer_L->Add( new wxButton(this, button_ShowStartConf_L, wxT("Show Start Conf")),
			0, wxALL, 1 ); 
  setConfBoxSizer_L->Add( new wxButton(this, button_SetTargetConf_L, wxT("Set Target Conf")),
			  0, wxALL, 1 ); 
  setConfBoxSizer_L->Add( new wxButton(this, button_ShowTargetConf_L, wxT("Show Target Conf")),
			  0, wxALL, 1 ); 
   
  // ** Add to Eva0TabSizer **
  Eva0TabSizer->Add( setConfBoxSizer_L, 1, wxEXPAND | wxALL, 4 );


  // ** PLAN AND EXECUTE **
  wxStaticBox* planBox = new wxStaticBox(this, -1, wxT("Plan & Execute"));
  wxStaticBoxSizer* planBoxSizer = new wxStaticBoxSizer(planBox, wxVERTICAL);

  // ** Radio buttons **
  static const wxString ConfMode[] = {
    wxT("Both Arms"),
    wxT("Only left"),
    wxT("Only right")
  };
  
  planBoxSizer->Add( new wxRadioBox( this, wxID_ANY, wxT("Mode:"),
				     wxDefaultPosition, wxDefaultSize,
				     WXSIZEOF(ConfMode), ConfMode, 1,
				     wxRA_SPECIFY_ROWS),
		     1,
		     wxALIGN_NOT,
		     0 );  

  wxBoxSizer *planButtonSizer = new wxBoxSizer( wxHORIZONTAL );
  planButtonSizer->Add( new wxButton(this, button_Plan, wxT("Plan")),
			0, wxALL, 1 ); 
  planButtonSizer->Add( new wxButton(this, button_Execute, wxT("Execute")),
			0, wxALL, 1 ); 
  planBoxSizer->Add( planButtonSizer, 1, wxALIGN_NOT, 0 );
  
  Eva0TabSizer->Add( planBoxSizer, 2, wxEXPAND | wxALL, 4 );

  // ** SET SIZER TO TAB **
  SetSizer( Eva0TabSizer );  
}

/**
 * @function ~Eva0Tab
 */
Eva0Tab::~Eva0Tab() {
  if( mPPa != NULL ) {
    delete mPPa;
  }

}


/**
 * @function Initialize
 * @brief Get robot information
 */
bool Eva0Tab::Initialize() {

  mRobotId = 0;

  /** Arms */
  mLA_Links.resize( sNumArmLinks );
  mRA_Links.resize( sNumArmLinks );
  for( size_t i = 0; i < sNumArmLinks; ++i ) {
    mLA_Links[i] = world->robots[mRobotId]->findLink( sLA_Ids[i] ); 
    mRA_Links[i] = world->robots[mRobotId]->findLink( sRA_Ids[i] ); 
  }

  /** Hands */
  mLH_Links.resize( sNumHandLinks );
  mRH_Links.resize( sNumHandLinks );
  for( size_t i = 0; i < sNumHandLinks; ++i ) {
    mLH_Links[i] = world->robots[mRobotId]->findLink( sLH_Ids[i] ); 
    mRH_Links[i] = world->robots[mRobotId]->findLink( sRH_Ids[i] ); 
  }

  /** Base */
  mBase_Link = world->robots[mRobotId]->findLink( sBase_Id );


}

/**
 * @function OnRadio
 */
void Eva0Tab::OnRadio( wxCommandEvent &_evt ) {

  int num = _evt.GetSelection();
  
  if( num == 0 ) {
    mConfMode = BOTH_ARMS;
    std::cout << "** Planning for both arms" << std::endl; 
  }
  else if( num == 1 ) {
    mConfMode = LEFT_ARM;
    std::cout << "** Planning for left arm only " << std::endl;
  }
  else if( num == 2 ) {
    mConfMode = RIGHT_ARM;
    std::cout << "-- Planning for right arm only" << std::endl;
  }
}

/**
 * @function OnButton
 */
void Eva0Tab::OnButton( wxCommandEvent &_evt ) {

  int button_num = _evt.GetId(); 
  Initialize();
  
  switch (button_num) {
    
    
    /** Set Start Configuration  Right */
  case button_SetStartConf_R: {

    mStartConf_R.resize( sNumArmLinks );
    for( size_t i = 0; i < sNumArmLinks; ++i ) {
      mStartConf_R[i] = world->robots[mRobotId]->links[mRA_Links[i]]->jVal;
    }
    std::cout << "** Start RA : " << mStartConf_R.transpose() << std::endl;
  } break;

    /** Show Right Start Configuration */
  case button_ShowStartConf_R: {

    if( mStartConf_R.size() < 1 ) {
      std::cout << "** (!) Set a right start config first (!)" << std::endl;
      break;
    }
    world->robots[mRobotId]->setConf( mRA_Links, mStartConf_R );
    viewer->UpdateCamera();
  } break;

    /** Set Right Target Configuration */
  case button_SetTargetConf_R: {
    
    mTargetConf_R.resize( sNumArmLinks );
    for( size_t i = 0; i < sNumArmLinks; ++i ) {
      mTargetConf_R[i] = world->robots[mRobotId]->links[mRA_Links[i]]->jVal;
    }
    std::cout << "** Target RA : " << mTargetConf_R.transpose() << std::endl;
  } break;

    /** Show Right Target Configuration */
  case button_ShowTargetConf_R: {

    if( mTargetConf_R.size() < 1 ) {
      std::cout << "** (!) Set a right target config first (!)" << std::endl;
      break;
    }
    world->robots[mRobotId]->setConf( mRA_Links, mTargetConf_R );
    viewer->UpdateCamera();
  } break;
  
    /** Set Left Start Configuration */
  case button_SetStartConf_L: {

    mStartConf_L.resize( sNumArmLinks );
    for( size_t i = 0; i < sNumArmLinks; ++i ) {
      mStartConf_L[i] = world->robots[mRobotId]->links[mLA_Links[i]]->jVal;
    }
    std::cout << "** Start LA : " << mStartConf_L.transpose() << std::endl;    
  } break;

    /** Show Left Start Configuration */
  case button_ShowStartConf_L: {
    if( mStartConf_L.size() < 1 ) {
      std::cout << "** (!) Set a left start config first (!)" << std::endl;
      break;
    }
    world->robots[mRobotId]->setConf( mLA_Links, mStartConf_L );
    viewer->UpdateCamera();
  } break;

    /** Set Left Target Configuration */
  case button_SetTargetConf_L: {

    mTargetConf_L.resize( sNumArmLinks );
    for( size_t i = 0; i < sNumArmLinks; ++i ) {
      mTargetConf_L[i] = world->robots[mRobotId]->links[mLA_Links[i]]->jVal;
    }
    std::cout << "** Target LA : " << mTargetConf_L.transpose() << std::endl;
  } break;

    /** Show Left Target Configuration */
  case button_ShowTargetConf_L: {

    if( mTargetConf_L.size() < 1 ) {
      std::cout << "** (!) Set a left target config first (!)" << std::endl;
      break;
    }
    world->robots[mRobotId]->setConf( mLA_Links, mTargetConf_L );
    viewer->UpdateCamera();
  } break;

    /** Plan */
  case button_Plan: {    
    ArmPlanning();
  } break;

    /** Execute */
  case button_Execute: {

    ExecutePath();
  } break;
    
  } // end of button switch

}

/**
 * @function ExecutePath
 */
void Eva0Tab::ExecutePath() {

  std::vector<int> _links;
  std::list<Eigen::VectorXd> _path;

  switch( mConfMode ) {
    
  case LEFT_ARM: {
    _links = mLA_Links;
    _path = mPath_L;
  } break;
    
  case RIGHT_ARM: {
    _links = mRA_Links;
    _path = mPath_R;
  } break;

  case BOTH_ARMS: {

    int pm, pM, lm, lM;
    std::list<Eigen::VectorXd> pathm; 
    std::list<Eigen::VectorXd> pathM;

    if( mPath_L.size() < mPath_R.size() ) {
      pathm = mPath_L; pathM = mPath_R;
      pm = mPath_L.size(); pM = mPath_R.size();
      lm = mLA_Links.size(); lM = mRA_Links.size();

      _links = mLA_Links;
      _links.insert( _links.end(), mRA_Links.begin(), mRA_Links.end() );

    } else {
      pathm = mPath_R; pathM = mPath_L;
      pm = mPath_R.size(); pM = mPath_L.size();
      lm = mRA_Links.size(); lM = mLA_Links.size();

      _links = mRA_Links;
      _links.insert( _links.end(), mLA_Links.begin(), mLA_Links.end() );
    }

    std::list<Eigen::VectorXd>::iterator itm = pathm.begin();
    std::list<Eigen::VectorXd>::iterator itM = pathM.begin();

    for( size_t i = 0; i < pm; ++i ) {

      Eigen::VectorXd conf(lm + lM);

      for( size_t j = 0; j < lm; ++j ) {
	conf[j] = (*itm)(j);
      }  
      for( size_t j = 0; j < lM; ++j ) {
	conf[j+lm] = (*itM)(j);
      }

      _path.push_back( conf );
      itm++;
      itM++;
    }

    itm--; // it ended in end()

    for( size_t i = pm; i < pM; ++i ) {

      Eigen::VectorXd conf(lm + lM);

      for( size_t j = 0; j < lm; ++j ) {
	conf[j] = (*itm)(j);
      }  
      for( size_t j = 0; j < lM; ++j ) {
	conf[j+lm] = (*itM)(j);
      }

      _path.push_back( conf );
      itM++;
    }

  } break;

  } // end of mConfMode switch

  /** Execution **/
  if( _path.size() == 0 ) {
    std::cout << "** (!) Must create a valid plan first (!)" << std::endl;
    return;
  }

  int numsteps = _path.size();
  double increment = 5.0 / numsteps;

  std::cout << "-->(+) Updating Timeline -- Steps: " << numsteps << endl;
  
  frame->InitTimer( string("Plan"),increment );
  
  Eigen::VectorXd vals( _links.size() );
  
  for( std::list<Eigen::VectorXd>::iterator it = _path.begin(); it != _path.end(); it++ ) {
    world->robots[mRobotId]->setConf( _links,  *it );
    frame->AddWorld( world );
  }
  
}


/**
 * @function RSTStateChange
 */
void Eva0Tab::RSTStateChange() {
}
