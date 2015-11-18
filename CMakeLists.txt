project(gorgone)
set(APP gorgone)

cmake_minimum_required(VERSION 2.8)

include(../of/openFrameworks.cmake)
add_subdirectory(NIST_VASIR)
find_package( OpenCV REQUIRED )

include_directories (
  ${CMAKE_CURRENT_LIST_DIR}/NIST_VASIR/Analysis
  ${CMAKE_CURRENT_LIST_DIR}/NIST_VASIR/MasekAlg
  ${CMAKE_CURRENT_LIST_DIR}/NIST_VASIR/VASIR
  ${CMAKE_CURRENT_LIST_DIR}/ofxCv/libs/ofxCv/include/
)

# Jamoma specific directory
INCLUDE_DIRECTORIES("/usr/local/jamoma/include/jamoma/")
LINK_DIRECTORIES("/usr/local/jamoma/lib/")

ofxaddon(ofxCv)
ofxaddon(ofxArgParser)
ofxaddon(ofxGui)
ofxaddon(ofxSvg)

set(SOURCES
    src/gorgone.cpp
    src/gorgoneEyeDetection.cpp
    src/crossVideoGrabber.cpp
    src/svgInterpolation.cpp
    src/ofxJamoma.cpp
    src/main.cpp
)

if ( OF_PLATFORM STREQUAL armv7 )
    ofxaddon(ofxCvPiCam)
    list(APPEND SOURCES src/gnublin.cpp)
endif()



add_executable(
    ${APP}
    MACOSX_BUNDLE
    ${SOURCES}
    ${OFXADDONS_SOURCES}
)

target_link_libraries(
    ${APP}
    ${OPENFRAMEWORKS_LIBRARIES}
    VASIR
    MasekAlg
    Analysis
    ${OpenCV_LIBS}
    ${ofxCvPiCam}
)

target_link_libraries(
  ${APP}
  JamomaModular
  JamomaFoundation
)

if ( OF_PLATFORM STREQUAL armv7 )
    target_link_libraries(
        ${APP}
        mmal_core
        mmal_util
        mmal_vc_client
    )
endif()

cotire(${APP})
