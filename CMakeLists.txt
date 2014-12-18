cmake_minimum_required(VERSION 2.8.4)
project(LCollection)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -pthread")

set(SOURCE_FILES
    LTest/src/OutputFormat/rapidxml-1.13/rapidxml.hpp
    LTest/src/OutputFormat/rapidxml-1.13/rapidxml_iterators.hpp
    LTest/src/OutputFormat/rapidxml-1.13/rapidxml_print.hpp
    LTest/src/OutputFormat/rapidxml-1.13/rapidxml_utils.hpp
    LTest/src/OutputFormat/Format.h
    LTest/src/OutputFormat/OutputFormat.h
    LTest/src/OutputFormat/OutputFormatBase.h
    LTest/src/OutputFormat/TextOutput.h
    LTest/src/OutputFormat/TextTable.h
    LTest/src/OutputFormat/XmlOutput.h
    LTest/src/AsyncTaskExecuter.h
    LTest/src/FunctionPattern.h
    LTest/src/LTest.cpp
    LTest/src/LTest.h
    LTest/src/LTestAssert.h
    LTest/src/LTestMisuseException.h
    LTest/src/ManagedFixture.h
    LTest/src/MuteStream.h
    LTest/src/ParameterTest.h
    LTest/src/TestResult.h
    LTest/src/toStringPatch.h
    tests/main.cpp
    tests/ListTest.h
    tests/OptionalTest.h
    src/List.h
    src/Optional.h)

add_executable(LCollection ${SOURCE_FILES})