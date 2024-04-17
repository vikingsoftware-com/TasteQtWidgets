set(LIB_NAME reviews)

add_library(${LIB_NAME} STATIC
    addnewreviewdialog.h addnewreviewdialog.cpp addnewreviewdialog.ui
    gitlab/gitlabreviews.h gitlab/gitlabreviews.cpp
    review.h review.cpp
    reviewsmanager.h reviewsmanager.cpp
    reviewsmodelbase.h reviewsmodelbase.cpp
    reviewswidget.h reviewswidget.cpp reviewswidget.ui
)

target_include_directories(${LIB_NAME} PUBLIC .)
target_link_libraries(${LIB_NAME}
    PUBLIC Qt6::Core Qt6::Widgets tracecommon
    PRIVATE QGitlabAPI)
