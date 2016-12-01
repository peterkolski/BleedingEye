# ========================================================
# ===================== CMake Settings ===================
# ========================================================
cmake_minimum_required(VERSION 2.8.4)
cmake_policy(SET CMP0042 NEW)

project(  BleedingEye )

set( OF_DIRECTORY_BY_USER ../../../../ )


include_directories( shared )


#add_subdirectory( main/EyeCrusher )
#add_subdirectory( reseach/EyeCrusherTest )
add_subdirectory( reseach/ofDirectory )


# =========================================================================
# ============================== OpenFrameworks ===========================
# =========================================================================
#include( ${OF_DIRECTORY_BY_USER}/addons/ofxCMake/modules/main.cmake )
# =========================================================================
