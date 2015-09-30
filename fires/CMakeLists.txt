source_group(\\ FILES CMakeLists.txt)

set(FIRES_PUBLIC_HEADERS
Aggregator.h
Averager.h
Comparer.h
Definitions.h
Filter.h
error.h
Normalizer.h
Object.h
Objects.h
Property.h
PropertyCaster.h
Engine.h
Task.h
Search.h
SearchConfig.h
Sort.h
)

set(FIRES_HEADERS )

set(FIRES_SOURCES
Object.cpp
Objects.cpp
Engine.cpp
SearchConfig.cpp
Search.cpp
)

if(VMMLIB_FOUND)
  list(APPEND FIRES_LINK_LIBRARIES PUBLIC vmmlib)
endif()

common_library(fires)

