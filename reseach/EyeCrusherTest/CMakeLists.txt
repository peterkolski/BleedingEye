#THIS FILE SHOULD BE PUT INTO THE OF PROJECT FOLDER

# ========================================================
# ===================== CMake Settings ===================
# ========================================================
cmake_minimum_required(VERSION 2.8.4)
cmake_policy(SET CMP0042 NEW)

# ========================================================
# ===================== User Settings ====================
# ========================================================
# ------------------------- Names  -----------------------
project(        BleedingEye )
set( APP_NAME   EyeCrusher_TEST )

# ------------------------ OF Path -----------------------
set( OF_DIRECTORY /Users/sonneundasche/programming/of )

# --------------------- Source Files ---------------------
set( ${APP_NAME}_SOURCE_FILES
        src/main.cpp
        src/ofApp.cpp
        ../../shared/NetworkNode.cpp
        ../../shared/NetworkVisual.cpp
        ../../shared/DancePerfOSC.cpp
        ../../shared/videoDirectory.cpp
        ../../shared/MidiValues.cpp
        ../../shared/LinesHorizontal.cpp
        ../../shared/FlowPoint.cpp
        )


# ------------------------ AddOns OF INTERNAL ------------
set( OFX_ADDONS_ACTIVE
        #        ofxXmlSettings
        #        ofxOsc
                ofxGui
)

# ------------------------ AddOns EXTERNAL ----------------
#include( ${OF_DIRECTORY}/addons/external/ofxFluid/ )

# ========================================================
# ===================== OpenFrameworks ===================
# ========================================================
include( ${OF_DIRECTORY}/CMake/modules/openFrameworksGlobal.cmake )
# ========================================================

