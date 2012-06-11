/**
 * @file Eva0TabApp.cpp
 */


#include "RSTApp.h"
#include "Eva0Tab.h"

/* To include Planning Tab, ensure that Tab/PlanningTab is present in SRC_WX for
 * librst/CMakeLists.txt. Then uncomment the two lines below */

// #include <Tabs/PlanningTab.h>

extern wxNotebook* tabView;

class Eva0TabApp : public RSTApp {
	virtual void AddTabs() {
		tabView->AddPage(new Eva0Tab(tabView), wxT("Eva0Tab"));
		// tabView->AddPage(new PlanningTab(tabView), wxT("PlanningTab"));
	}
};

IMPLEMENT_APP(Eva0TabApp)

