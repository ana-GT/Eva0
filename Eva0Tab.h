/*
 * Copyright (c) 20102, Georgia Tech Research Corporation
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

#ifndef EVA0_TAB
#define EVA0_TAB

#include <Tabs/RSTTab.h>
#include <Tools/World.h>
#include <Tools/Robot.h>
#include <Tools/Link.h>
#include <Tools/Object.h>
#include <Tools/Constants.h>

#include <Tools/PathPlanner.h>

#include <Eigen/Core>
#include <list>

/**
 * @class Eva0Tab
 * @brief Test Class to show off Golem
 */
class Eva0Tab : public RSTTab
{
public:

  enum eConfMode {
    BOTH_ARMS,
    LEFT_ARM,
    RIGHT_ARM
  };

  Eva0Tab(){};
  Eva0Tab(wxWindow * parent, wxWindowID id = -1,
	  const wxPoint & pos = wxDefaultPosition,
	  const wxSize & size = wxDefaultSize,
	  long style = wxTAB_TRAVERSAL);
  virtual ~Eva0Tab();
  
  bool Initialize();
  bool ArmPlanning();
  void OnRadio( wxCommandEvent &_evt );
  void OnButton( wxCommandEvent &_evt );
  void ExecutePath( );
  void HomogenizePath( std::list<Eigen::VectorXd> _inputPath,
		       std::list<Eigen::VectorXd> &_outputPath );
  
  void RSTStateChange();
  
  // ** Constant variables **
  static const int sNumHandLinks;
  static const int sNumArmLinks;
  static const char* sLH_Ids[];
  static const char* sRH_Ids[];
  static const char* sLA_Ids[];
  static const char* sRA_Ids[];
  static const char* sBase_Id;
 
  // ** Member variables **
  Eigen::VectorXd mStartConf_R;
  Eigen::VectorXd mTargetConf_R;

  Eigen::VectorXd mStartConf_L;
  Eigen::VectorXd mTargetConf_L;

  PathPlanner<RRT> *mPPa;
  double mStepSize;

  int mRobotId;
  int mEEId; 
  std::string mRobotName;
  std::vector<int> mLA_Links;
  std::vector<int> mLH_Links;
  std::vector<int> mRA_Links;
  std::vector<int> mRH_Links;
  int mBase_Link;
  eConfMode mConfMode;

  std::list<Eigen::VectorXd> mPath_R;
  std::list<Eigen::VectorXd> mPath_L;

  DECLARE_DYNAMIC_CLASS(Eva0Tab)
    DECLARE_EVENT_TABLE()
    };

#endif /** EVA0_TAB */
