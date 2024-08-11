# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/ItSchool/Folder_cu_programe/Proiect_de_curs/The_Beginning_of_the_End/source/build/_deps/sfml-src"
  "D:/ItSchool/Folder_cu_programe/Proiect_de_curs/The_Beginning_of_the_End/source/build/_deps/sfml-build"
  "D:/ItSchool/Folder_cu_programe/Proiect_de_curs/The_Beginning_of_the_End/source/build/_deps/sfml-subbuild/sfml-populate-prefix"
  "D:/ItSchool/Folder_cu_programe/Proiect_de_curs/The_Beginning_of_the_End/source/build/_deps/sfml-subbuild/sfml-populate-prefix/tmp"
  "D:/ItSchool/Folder_cu_programe/Proiect_de_curs/The_Beginning_of_the_End/source/build/_deps/sfml-subbuild/sfml-populate-prefix/src/sfml-populate-stamp"
  "D:/ItSchool/Folder_cu_programe/Proiect_de_curs/The_Beginning_of_the_End/source/build/_deps/sfml-subbuild/sfml-populate-prefix/src"
  "D:/ItSchool/Folder_cu_programe/Proiect_de_curs/The_Beginning_of_the_End/source/build/_deps/sfml-subbuild/sfml-populate-prefix/src/sfml-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/ItSchool/Folder_cu_programe/Proiect_de_curs/The_Beginning_of_the_End/source/build/_deps/sfml-subbuild/sfml-populate-prefix/src/sfml-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/ItSchool/Folder_cu_programe/Proiect_de_curs/The_Beginning_of_the_End/source/build/_deps/sfml-subbuild/sfml-populate-prefix/src/sfml-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
