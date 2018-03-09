cmake_minimum_required(VERSION 2.6)

project(Unpacker2 CXX)

if(NOT MSVC)
  add_definitions(-std=c++11 -Wall -Wunused-parameter)
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# add possible ROOT cmake module locations to module path
execute_process(COMMAND root-config --etcdir OUTPUT_VARIABLE ROOT_ETCDIR OUTPUT_STRIP_TRAILING_WHITESPACE)
list(APPEND CMAKE_MODULE_PATH ${ROOT_ETCDIR}/cmake)
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS}/etc/cmake)

# find ROOT
find_package(ROOT 5 REQUIRED)

if(ROOT_USE_FILE)
  include(${ROOT_USE_FILE})
endif()

include_directories(${ROOT_INCLUDE_DIRS})
add_definitions(${ROOT_DEFINITIONS})

find_package(Boost 1.50.0 REQUIRED)
#include_directories(${TINYXML_INCLUDE_DIRS})

file(GLOB HEADERS *.h)
file(GLOB SOURCES *.cc)

set(DICTIONARY_REQUIRED
  Event.h
  Hit.h
  EventIII.h
  TDCChannel.h
  TDCHit.h
  TDCHitExtended.h
  TDCHitIII.h
  )

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
foreach(header ${DICTIONARY_REQUIRED})
  ROOT_GENERATE_DICTIONARY(${header}_Dict ${header} OPTIONS -p)
  list(APPEND SOURCES ${header}_Dict.cxx)
endforeach()

add_library(Unpacker2 SHARED ${SOURCES} ${HEADERS})

target_link_libraries(Unpacker2
  ${Boost_LIBRARIES}
  ${ROOT_LIBRARIES}
  )

set_target_properties(Unpacker2 PROPERTIES LINKER_LANGUAGE CXX)
