PROJECT(org_commontk_pluginfwtest)

SET(PLUGIN_export_directive "org_commontk_pluginfwtest_EXPORT")

SET(PLUGIN_SRCS
  ctkPluginFrameworkTestActivator.cpp
  ctkPluginFrameworkTestSuite.cpp
)

SET(PLUGIN_MOC_SRCS
  ctkPluginFrameworkTestActivator_p.h
  ctkPluginFrameworkTestSuite_p.h
)

SET(PLUGIN_UI_FORMS
  
)

SET(PLUGIN_resources
  
)

ctkMacroGetTargetLibraries(PLUGIN_target_libraries)

ctkMacroBuildPlugin(
  NAME ${PROJECT_NAME}
  EXPORT_DIRECTIVE ${PLUGIN_export_directive}
  SRCS ${PLUGIN_SRCS}
  MOC_SRCS ${PLUGIN_MOC_SRCS}
  UI_FORMS ${PLUGIN_UI_FORMS}
  RESOURCES ${PLUGIN_resources}
  TARGET_LIBRARIES ${PLUGIN_target_libraries}
  TEST_PLUGIN
)