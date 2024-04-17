set(LIB_NAME requirements)

remove_definitions(-DQT_NO_KEYWORDS)

add_library(${LIB_NAME} STATIC)

target_sources(${LIB_NAME} PRIVATE
  addnewrequirementdialog.cpp
  addnewrequirementdialog.h
  addnewrequirementdialog.ui
  checkedfilterproxymodel.cpp
  checkedfilterproxymodel.h
  gitlab/gitlabrequirements.cpp
  gitlab/gitlabrequirements.h
  requirement.cpp
  requirement.h
  requirementsmanager.cpp
  requirementsmanager.h
  requirementsmodelbase.cpp
  requirementsmodelbase.h
  requirementswidget.cpp
  requirementswidget.h
  requirementswidget.ui
)

target_include_directories(${LIB_NAME} PUBLIC .)
target_link_libraries(${LIB_NAME}
    PUBLIC Qt6::Core Qt6::Widgets tracecommon
    PRIVATE QGitlabAPI)
target_compile_definitions(${LIB_NAME} PUBLIC QGITLABAPI_LIBRARY QT_DEBUG_OUTPUT)
