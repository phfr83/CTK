PROJECT(CTKPluginFramework)

#
# See CTK/CMake/ctkMacroBuildLib.cmake for details
#

SET(KIT_export_directive "CTK_PLUGINFW_EXPORT")

  
# Source files
SET(KIT_SRCS
  ctkCaseInsensitiveString.cpp
  ctkDictionary.cpp
  ctkLDAPExpr.cpp
  ctkLDAPExpr_p.h
  ctkLDAPSearchFilter.cpp
  ctkPlugin.cpp
  ctkPluginAbstractTracked_p.h
  ctkPluginAbstractTracked.tpp
  ctkPluginActivator.h
  ctkPluginArchive.cpp
  ctkPluginArchive_p.h
  ctkPluginConstants.cpp
  ctkPluginContext.cpp
  ctkPluginContext_p.h
  ctkPluginDatabase.cpp
  ctkPluginDatabase_p.h
  ctkPluginDatabaseException.cpp
  ctkPluginEvent.cpp
  ctkPluginException.cpp
  ctkPluginFramework.cpp
  ctkPluginFramework_global.h
  ctkPluginFrameworkFactory.cpp
  ctkPluginFrameworkContext.cpp
  ctkPluginFrameworkContext_p.h
  ctkPluginFrameworkEvent.cpp
  ctkPluginFrameworkLauncher.cpp
  ctkPluginFrameworkListeners.cpp
  ctkPluginFrameworkListeners_p.h
  ctkPluginFrameworkPrivate.cpp
  ctkPluginFrameworkPrivate_p.h
  ctkPluginFrameworkUtil.cpp
  ctkPluginFrameworkUtil_p.h
  ctkPluginLocalization.cpp
  ctkPluginManifest.cpp
  ctkPluginManifest_p.h
  ctkPluginPrivate.cpp
  ctkPluginPrivate_p.h
  ctkPlugins.cpp
  ctkPlugins_p.h
  ctkPluginStorage.cpp
  ctkPluginStorage_p.h
  ctkPluginTracker.h
  ctkPluginTracker.tpp
  ctkPluginTrackerPrivate.h
  ctkPluginTrackerPrivate.tpp
  ctkRequirePlugin.cpp
  ctkRequirePlugin_p.h
  ctkRuntimeException.cpp
  ctkServiceEvent.cpp
  ctkServiceException.cpp
  ctkServiceFactory.h
  ctkServiceReference.cpp
  ctkServiceReferencePrivate.cpp
  ctkServiceRegistration.cpp
  ctkServiceRegistrationPrivate.cpp
  ctkServices.cpp
  ctkServices_p.h
  ctkServiceSlotEntry.cpp
  ctkServiceSlotEntry_p.h
  ctkServiceTracker.h
  ctkServiceTracker.tpp
  ctkServiceTrackerCustomizer.h
  ctkServiceTrackerPrivate.h
  ctkServiceTrackerPrivate.tpp
  ctkTrackedPlugin_p.h
  ctkTrackedPlugin.tpp
  ctkTrackedPluginListener_p.h
  ctkTrackedService_p.h
  ctkTrackedService.tpp
  ctkTrackedServiceListener_p.h
  ctkVersion.cpp
  ctkVersionRange.cpp
  ctkVersionRange_p.h

  # Services
  service/cm/ctkConfiguration.cpp
  service/cm/ctkConfigurationAdmin.cpp
  service/cm/ctkConfigurationEvent.cpp
  service/cm/ctkConfigurationException.cpp
  service/cm/ctkConfigurationListener.h
  service/cm/ctkConfigurationPlugin.cpp
  service/cm/ctkManagedService.h
  service/cm/ctkManagedServiceFactory.h

  service/event/ctkEvent.cpp
  service/event/ctkEventAdmin.h
  service/event/ctkEventConstants.cpp
  service/event/ctkEventHandler.h

  service/log/ctkLogEntry.h
  service/log/ctkLogListener.h
  service/log/ctkLogReaderService.h
  service/log/ctkLogService.cpp
  service/log/ctkLogStream.cpp

  service/metatype/ctkAttributeDefinition.cpp
  service/metatype/ctkMetaTypeInformation.h
  service/metatype/ctkMetaTypeProvider.cpp
  service/metatype/ctkMetaTypeService.cpp
  service/metatype/ctkObjectClassDefinition.h
  )

# Headers that should run through moc
SET(KIT_MOC_SRCS
  ctkPluginFrameworkListeners_p.h
  ctkTrackedPluginListener_p.h
  ctkTrackedServiceListener_p.h
)

# UI files
SET(KIT_UI_FORMS
)

# Resources
SET(KIT_resources
)

# Create a MANIFEST.MF resource for the PluginFramework library,
# pretending that is is a plugin (the system plugin)
ctkFunctionGeneratePluginManifest(KIT_SRCS
  SYMBOLIC_NAME "system.plugin"
  VERSION "0.9.9"
  )

# Target libraries - See CMake/ctkFunctionGetTargetLibraries.cmake
# The following macro will read the target libraries from the file 'target_libraries.cmake'
ctkFunctionGetTargetLibraries(KIT_target_libraries)

ctkMacroBuildLib(
  NAME ${PROJECT_NAME}
  EXPORT_DIRECTIVE ${KIT_export_directive}
  INCLUDE_DIRECTORIES ${CTK_SUPERBUILD_BINARY_DIR}
  SRCS ${KIT_SRCS}
  MOC_SRCS ${KIT_MOC_SRCS}
  UI_FORMS ${KIT_UI_FORMS}
  TARGET_LIBRARIES ${KIT_target_libraries}
  RESOURCES ${KIT_resources}
  LIBRARY_TYPE ${CTK_LIBRARY_MODE}
  )

# Testing
IF(BUILD_TESTING)
  ADD_SUBDIRECTORY(Testing)
ENDIF(BUILD_TESTING)
