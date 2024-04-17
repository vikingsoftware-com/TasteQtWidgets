set(LIB_NAME QGitlabAPI)

add_library(${LIB_NAME} STATIC)

target_sources(${LIB_NAME} PRIVATE
  QGitlabAPI_global.h
  issue.cpp
  issue.h
  issuerequestoptions.cpp
  issuerequestoptions.h
  label.cpp
  label.h
  labelsrequestoptions.h
  labelsrequestoptions.cpp
  qgitlabclient.cpp
  qgitlabclient.h
  requestoptions.h
  urlcomposer.cpp
  urlcomposer.h
)

target_include_directories(${LIB_NAME} PUBLIC .)
target_link_libraries(${LIB_NAME} Qt6::Network Qt6::Core Qt6::Gui)
target_compile_definitions(${LIB_NAME} PUBLIC QGITLABAPI_LIBRARY QT_DEBUG_OUTPUT)
