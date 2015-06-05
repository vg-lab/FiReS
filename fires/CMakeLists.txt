source_group(\\ FILES CMakeLists.txt)

set(FIRES_PUBLIC_HEADERS ${COMMON_INCLUDES}
Comparer.h
# Definitions.h
# FeaturePtr.h
# FeaturePtrToScalar.h
# FeaturePtrToVector.h
# FeaturePtrToVectorOfPtrs.h
# FeatureScalar.h
Object.h
# Objects.h
QueryFeatures.h
Feature.h
# FeaturePtrToScalarComparer.h
# FeaturePtrToVectorComparer.h
# FeaturePtrToVectorOfPtrsComparer.h
# FeatureScalarComparer.h
# FeatureVectorComparer.h
# Engine.h
)

set(FIRES_HEADERS )

set(FIRES_SOURCES ${COMMON_SOURCES}
# Comparer.cpp
# Feature.cpp
Object.cpp
# Objects.cpp
QueryFeatures.cpp
# Engine.cpp
)

common_library(fires)
set(FIRES_LINK_LIBRARIES "${FIRES_LINK_LIBRARIES}" PARENT_SCOPE)
