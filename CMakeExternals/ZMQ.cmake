#
# ZMQ
#
SET(ZMQ_DEPENDS)
ctkMacroShouldAddExternalProject(ZMQ_LIBRARIES add_project)
IF(${add_project})

  # Sanity checks
  IF(DEFINED ZMQ_DIR AND NOT EXISTS ${ZMQ_DIR})
    MESSAGE(FATAL_ERROR "ZMQ_DIR variable is defined but corresponds to non-existing directory")
  ENDIF()

  SET(ZMQ_enabling_variable ZMQ_LIBRARIES)
  
  SET(proj ZMQ)
  SET(proj_DEPENDENCIES)
  
  SET(ZMQ_DEPENDS ${proj})
  
  IF(NOT DEFINED ZMQ_DIR)
  #   MESSAGE(STATUS "Adding project:${proj}")
    ExternalProject_Add(${proj}
      SOURCE_DIR ${CMAKE_BINARY_DIR}/${proj}
      BINARY_DIR ${proj}-build
      PREFIX ${proj}${ep_suffix}
      GIT_REPOSITORY ${git_protocol}://github.com/PatrickCheng/zeromq2.git
      GIT_TAG "origin/master"
      INSTALL_COMMAND ""
      CMAKE_GENERATOR ${gen}
      CMAKE_ARGS
        ${ep_common_args}
        -DBUILD_TESTING:BOOL=OFF
        -DBUILD_SHARED_LIBS:BOOL=ON 
        -DZMQ_BUILD_DEVICES:BOOL=ON
        -DZMQ_BUILD_PERFORMANCE_TESTS:BOOL=ON
       DEPENDS
        ${proj_DEPENDENCIES}
      )
    SET(ZMQ_DIR ${CMAKE_BINARY_DIR}/${proj}-build)

  ELSE()
    ctkMacroEmptyExternalProject(${proj} "${proj_DEPENDENCIES}")
  ENDIF()
  
  LIST(APPEND CTK_SUPERBUILD_EP_ARGS -DZMQ_DIR:PATH=${ZMQ_DIR})

  SET(${ZMQ_enabling_variable}_INCLUDE_DIRS ZMQ_LIBRARY_DIRS)
  SET(${ZMQ_enabling_variable}_INCLUDE_DIRS ZMQ_INCLUDE_DIRS)
  SET(${ZMQ_enabling_variable}_FIND_PACKAGE_CMD ZMQ)
ENDIF()
