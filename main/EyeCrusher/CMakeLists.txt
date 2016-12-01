# ========================================================
# ===================== User Settings ====================
# ========================================================
# ------------------------- Names  -----------------------
#project(        BleedingEye )
set( APP_NAME   EyeCrusher )

# ------------------------ OF Path -----------------------
#set( OF_DIRECTORY_BY_USER ../../../../ )

# --------------------- Source Files ---------------------
set( ${APP_NAME}_SOURCE_FILES
        src/main.cpp
        src/ofApp.cpp
        )

# ------------------------ Shared ------------------------
list( APPEND ${APP_NAME}_SOURCE_FILES
        ../../shared/NetworkNode.cpp
        ../../shared/NetworkVisual.cpp
        ../../shared/SensorOSC.cpp
        ../../shared/videoDirectory.cpp
        ../../shared/MidiValues.cpp
        ../../shared/MidiMapping.cpp
        ../../shared/LinesHorizontal.cpp
        ../../shared/FlowPoint.cpp
        ../../shared/Ribbon.cpp
        ../../shared/Flow.cpp
        ../../shared/Network.cpp
        ../../shared/Lines.cpp
        ../../shared/Video.cpp
        ../../shared/KeyDetector.cpp
        )

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
