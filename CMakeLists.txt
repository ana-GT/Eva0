cmake_minimum_required (VERSION 2.6)
project (Eva0Tab)

include_directories( /home/humanoids/Software/rst /home/humanoids/Software/rst/librst )

set ( CMAKE_CXX_FLAGS "-L /home/humanoids/Software/rst/librst" )

set ( SRC_TAB_SIMULATION Eva0Tab Eva0TabApp )

set (wxWidgets_USE_LIBS base core gl)
find_package (wxWidgets)
if (wxWidgets_FOUND) 
  include (${wxWidgets_USE_FILE})
  add_executable (Eva0Tab  ${SRC_TAB_SIMULATION})
  target_link_libraries (Eva0Tab rst ${wxWidgets_LIBRARIES})
else (wxWidgets_FOUND)
  message ("wxWidgets not found!")
endif (wxWidgets_FOUND)

