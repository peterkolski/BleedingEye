# ========================================================
# ===================== User Settings ====================
# ========================================================
# ------------------------- Names  -----------------------
set( APP_NAME   ofDirectory_Test )

# ------------------------ OF Path -----------------------
#set( OF_DIRECTORY_BY_USER /Users/sonneundasche/programming/of )

# --------------------- Source Files ---------------------
set( ${APP_NAME}_SOURCE_FILES
        src/main.cpp
        src/ofApp.cpp
        )

# ------------------------ Shared ------------------------
list( APPEND ${APP_NAME}_SOURCE_FILES
        ../../shared/util/DirectoryDetector.cpp
        )

include_directories( ../../shared )

# ------------------------ AddOns ------------
set( OFX_ADDONS_ACTIVE

        )

# =========================================================================
# ============================== OpenFrameworks ===========================
# =========================================================================
include( ${OF_DIRECTORY_BY_USER}/addons/ofxCMake/modules/main.cmake )
# =========================================================================
