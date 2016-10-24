# ========================================================
# ===================== User Settings ====================
# ========================================================
# ------------------------- Names  -----------------------
#project(        BleedingEye )
set( APP_NAME   EyeCrusher_TEST )

# ------------------------ OF Path -----------------------
#set( OF_DIRECTORY_BY_USER /Users/sonneundasche/programming/of )

# --------------------- Source Files ---------------------
set( ${APP_NAME}_SOURCE_FILES
        src/main.cpp
        src/ofApp.cpp
        )

# ------------------------ Shared ------------------------
list( APPEND ${APP_NAME}_SOURCE_FILES
        ../../shared/NetworkNode.cpp
        ../../shared/NetworkVisual.cpp
        ../../shared/DancePerfOSC.cpp
        ../../shared/videoDirectory.cpp
        ../../shared/MidiValues.cpp
        ../../shared/LinesHorizontal.cpp
        ../../shared/FlowPoint.cpp
        )

#include_directories( ../../shared )

# ------------------------ AddOns ------------
set( OFX_ADDONS_ACTIVE
                ofxXmlSettings
                ofxOsc
                ofxGui

                ofxTwistedRibbon
                ofxOneEuroFilter
                ofxFlowTools
                ofxMidi
        )

# =========================================================================
# ============================== OpenFrameworks ===========================
# =========================================================================
include( ${OF_DIRECTORY_BY_USER}/addons/ofxCMake/modules/main.cmake )
# =========================================================================
