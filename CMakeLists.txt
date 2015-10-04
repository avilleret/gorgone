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

ofxaddon(ofxCv)
if ( OF_PLATFORM STREQUAL armv7 )
    ofxaddon(ofxCvPiCam)
endif()

set(SOURCES
    src/main.cpp
    src/gorgone.cpp
    src/gorgoneEyeDetection.cpp
    src/crossVideoGrabber.cpp
)

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

if ( OF_PLATFORM STREQUAL armv7 )
    target_link_libraries(
        ${APP}
        mmal_core
        mmal_util
        mmal_vc_client
    )
endif()

cotire(${APP})
