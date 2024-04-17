set(LIB_NAME tracecommon)

add_library(${LIB_NAME} STATIC
)

target_sources(${LIB_NAME} PRIVATE
    credentialwidget.h credentialwidget.cpp credentialwidget.ui
    issuesmanager.h issuesmanager.cpp
    issuesmanagerprivate.h issuesmanagerprivate.cpp
    issuetextproxymodel.h issuetextproxymodel.cpp
    tagfilterproxymodel.h tagfilterproxymodel.cpp
    tracecommonresources.qrc
    tracecommonlibrary.h tracecommonlibrary.cpp
    tracecommonmodelbase.h tracecommonmodelbase.cpp
    widgetbar.h widgetbar.cpp widgetbar.ui
)

target_include_directories(${LIB_NAME} PUBLIC .)
target_link_libraries(${LIB_NAME}
    PUBLIC Qt6::Core Qt6::Widgets
    PRIVATE QGitlabAPI)
