

source_group(\\ FILES CMakeLists.txt)

set(FIRES_PUBLIC_HEADERS ${COMMON_INCLUDES}
Comparer.h
FeaturePtr.h
FeaturePtrToFloat.h
FeaturePtrToVector.h
FeaturePtrToVectorOfPtrs.h
Object.h
Feature.h
FeaturePtrToFloatComparer.h
FeaturePtrToVectorComparer.h
FeaturePtrToVectorOfPtrsComparer.h
FeatureVectorComparer.h
System.h
)

set(FIRES_HEADERS )

set(FIRES_SOURCES ${COMMON_SOURCES}
Comparer.cpp
FeaturePtrToFloatComparer.cpp
Object.cpp
System.cpp
)

common_library(fires)
set(FIRES_LINK_LIBRARIES "${FIRES_LINK_LIBRARIES}" PARENT_SCOPE)
