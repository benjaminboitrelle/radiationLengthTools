#################################################
# CMake file for building radiation length tools
# @author Benjamin Boitrelle
# Copyright (c) DESY
CMAKE_MINIMUM_REQUIRED( VERSION 2.8 FATAL_ERROR )
#################################################

# project name
PROJECT(main CXX)

# Setup the build environment
LIST ( APPEND CMAKE_CXX_FLAGS "-fPIC -O2 -std=c++14 -Wall -g" )
LIST ( APPEND CMAKE_LD_FLAGS "-fPIC -O2" )

# Additional packages to be searched for by cmake
LIST( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake )

SET(INSTALL_PREFIX "${PROJECT_SOURCE_DIR}" CACHE PATH "Prefix prepended to install directories")
SET(CMAKE_INSTALL_PREFIX "${INSTALL_PREFIX}" CACHE INTERNAL "Prefix prepended to install directories" FORCE)

#SET(LIB_SOURCE_FILES
#  "telescope/propagate.cc"
#  "telescope/assembly.cc"
#  )
SET(main.cpp)

# Depends on ROOT for plotting:
FIND_PACKAGE(ROOT REQUIRED)
#FIND_PACKAGE(Boost 1.58 REQUIRED)
#INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

# Include root package properties
INCLUDE_DIRECTORIES( ${ROOT_INCLUDE_DIRS} )
LINK_LIBRARIES( ${ROOT_LIBRARIES} ${ROOT_ROOFIT_LIBRARY} )
ADD_DEFINITIONS ( ${ROOT_DEFINITIONS} )

FILE(
  GLOB_RECURSE SOURCE_FILES
  source/*
)


#FIND_PACKAGE ( PythonInterp ${REQUIRED_PYTHON_VERSION} REQUIRED)
#FIND_PACKAGE ( PythonLibs ${PYTHON_VERSION_STRING} EXACT)
#INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_DIRS})

#INCLUDE_DIRECTORIES(SYSTEM telescope utils ${ROOT_INCLUDE_DIR} ${GBL_INCLUDE_DIR})

# Build the telescope sim library
#ADD_LIBRARY(${PROJECT_NAME} SHARED ${LIB_SOURCE_FILES})

# Add subfolder with all telescope devices:
#ADD_SUBDIRECTORY(devices)

SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR} )

#install(TARGETS myExe mySharedLib myStaticLib
#        RUNTIME DESTINATION bin
#        LIBRARY DESTINATION lib
#        ARCHIVE DESTINATION lib/static)
#install(TARGETS mySharedLib DESTINATION /some/full/path)

ADD_EXECUTABLE(main main.cpp ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${ROOT_LIBRARY})

