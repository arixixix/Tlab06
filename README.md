## Laboratory work VI

Данная лабораторная работа посвещена изучению средств пакетирования на примере **CPack**

## Homework

После того, как вы настроили взаимодействие с системой непрерывной интеграции,</br>
обеспечив автоматическую сборку и тестирование ваших изменений, стоит задуматься</br>
о создание пакетов для измениний, которые помечаются тэгами (см. вкладку [releases](https://github.com/tp-labs/lab06/releases)).</br>
Пакет должен содержать приложение _solver_ из [предыдущего задания](https://github.com/tp-labs/lab03#задание-1)
Таким образом, каждый новый релиз будет состоять из следующих компонентов:
- архивы с файлами исходного кода (`.tar.gz`, `.zip`)
- пакеты с бинарным файлом _solver_ (`.deb`, `.rpm`, `.msi`, `.dmg`)

#### solver_application/CMakeLists.txt

```sh
cmake_minimum_required(VERSION 3.16.3)
project(equation)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(equation equation.cpp)

target_include_directories(equation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../formatter_ex_lib)
target_include_directories(equation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../solver_lib)

target_link_libraries(equation formatter_ex)
target_link_libraries(equation solver)


include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_NAME "solver")
set(CPACK_PACKAGE_VENDOR "Arixixix")
set(CPACK_PACKAGE_VERSION_MAJOR 0)
set(CPACK_PACKAGE_VERSION_MINOR 0)
set(CPACK_PACKAGE_VERSION_PATCH 0)

option(GENERATOR "")

if(${GENERATOR} MATCHES BINARY)
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Arixixix")
install(TARGETS solver DESTINATION bin)
endif()

if(${GENERATOR} MATCHES ARCHIVE)
install(FILES equation.cpp 
                ${CMAKE_CURRENT_SOURCE_DIR}/../formatter_lib/formatter.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../formatter_ex_lib/formatter_ex.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../solver_lib/solver.cpp
		DESTINATION files)
install(TARGETS formatter_ex solver LIBRARY DESTINATION libraries)
endif()

include(CPack)

```


#### main.yml

```sh
name: Archive_Create

on:
  push:
      branches: 
      - master
      
jobs:

  Release:
    name: Create Release
    runs-on: ubuntu-latest
    outputs:
      upload_url: ${{ steps.create_release.outputs.upload_url }}
      
    steps:        
    - name: Release
      id: create_release
      uses: actions/create-release@v1
      env :
          GITHUB_TOKEN: ${{ secrets.GITHUB1_TOKEN }}
      with:
          tag_name: 0.0.0
          release_name: Release ${{ github.ref }}
          body: |
            Upload archive and binary files for uploading
          draft: false
          prerelease: false

  Archives:
    needs: Release
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v1
    - name: Archive
      run : |
        mkdir build && cd build
        cmake -DGENERATOR=ARCHIVE ..
        make
        cpack -G ZIP
        cpack -G TGZ
        
        
    - name: ZIP_TO_RELEASE 
      uses: actions/upload-release-asset@v1
      env :
          GITHUB_TOKEN: ${{ secrets.GITHUB1_TOKEN }}
      with: 
       upload_url: ${{ needs.Release.outputs.upload_url }}
       asset_path: ./build/solver-0.0.0-Linux.zip
       asset_name: Solver.zip
       asset_content_type: files/zip   
        
    - name: TGZ_TO_RELEASE
      uses: actions/upload-release-asset@v1
      env :
          GITHUB_TOKEN: ${{ secrets.GITHUB1_TOKEN }}
      with: 
       upload_url: ${{ needs.Release.outputs.upload_url }}
       asset_path: ./build/solver-0.0.0-Linux.tar.gz
       asset_name: Solver.tar.gz
       asset_content_type: files/tgz
       
  Binary_deb_rpm:
    needs: Release
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v1
    - name: inst rpm
      run : |
        sudo apt-get install rpm
        
    - name: Binary_File
      run : |
        mkdir build && cd build
        cmake -DGENERATOR=BINARY ..
        make
        cpack -G DEB
        cpack -G RPM
        
    - name: DEB_TO_REALESE
      uses: actions/upload-release-asset@v1
      env :
          GITHUB_TOKEN: ${{ secrets.GITHUB1_TOKEN }}
      with: 
       upload_url: ${{ needs.Release.outputs.upload_url }}
       asset_path: ./build/solver-0.0.0-Linux.deb
       asset_name: solver_app.deb
       asset_content_type: files/deb
       
       
    - name: RPM_TO_REALESE
      uses: actions/upload-release-asset@v1
      env :
          GITHUB_TOKEN: ${{ secrets.GITHUB1_TOKEN }}
      with: 
       upload_url: ${{ needs.Release.outputs.upload_url }}
       asset_path: ./build/solver-0.0.0-Linux.rpm
       asset_name: solver_app.rpm
       asset_content_type: files/rpm       
       
     
  Binary_msi:
    needs: Release
    runs-on: windows-latest
    
    steps:
    - uses: actions/checkout@v1
    - name: Binary_File
      run : |
        mkdir build && cd build
        cmake -DGENERATOR=BINARY ..
        cmake --build .
        cpack -C CPackConfig.cmake -G WIX
        
    - name: MSI_TO_REALESE
      uses: actions/upload-release-asset@v1
      env :
          GITHUB_TOKEN: ${{ secrets.GITHUB1_TOKEN }}
      with: 
       upload_url: ${{ needs.Release.outputs.upload_url }}
       asset_path: ./build/solver-0.0.0-win64.msi
       asset_name: solver_app.msi
       asset_content_type: files/msi

  Binary_dmg:    
    needs: Release
    runs-on: macos-latest
    
    steps:
      - uses: actions/checkout@v1
      - name: Build binary files
        run : |
          mkdir build && cd build
          cmake -DGENERATOR=BINARY ..
          make
          cpack -G DragNDrop
          
      - name: DMGTO_TO_REALESE
        uses: actions/upload-release-asset@v1
        env :
          GITHUB_TOKEN: ${{ secrets.GITHUB1_TOKEN }}
        with: 
          upload_url: ${{ needs.Release.outputs.upload_url }}
          asset_path: ./build/solver-0.0.0-Darwin.dmg
          asset_name: solver_app.dmg
          asset_content_type: files/dmg  
```





## Links

- [DMG](https://cmake.org/cmake/help/latest/module/CPackDMG.html)
- [DEB](https://cmake.org/cmake/help/latest/module/CPackDeb.html)
- [RPM](https://cmake.org/cmake/help/latest/module/CPackRPM.html)
- [NSIS](https://cmake.org/cmake/help/latest/module/CPackNSIS.html)

```
Copyright (c) 2015-2021 The ISC Authors
```
