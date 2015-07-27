source_group(\\ FILES CMakeLists.txt)

set(FIRES_PUBLIC_HEADERS ${COMMON_INCLUDES}
Aggregate.h
Averager.h
Comparer.h
Definitions.h
Filter.h
error.h
Normalizer.h
Object.h
Objects.h
Feature.h
FeatureCaster.h
Engine.h
Task.h
Search.h
SearchConfig.h
Sort.h
)

set(FIRES_HEADERS )

set(FIRES_SOURCES ${COMMON_SOURCES}
Object.cpp
Objects.cpp
Engine.cpp
SearchConfig.cpp
Search.cpp
#Sort.cpp
)

common_library(fires)
set(FIRES_LINK_LIBRARIES "${FIRES_LINK_LIBRARIES}" PARENT_SCOPE)
