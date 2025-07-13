include("C:/Users/Amalya/Documents/server/build/Desktop_Qt_6_9_1_MSVC2022_64bit-Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/server-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE C:/Users/Amalya/Documents/server/build/Desktop_Qt_6_9_1_MSVC2022_64bit-Debug/server.exe
    GENERATE_QT_CONF
)
