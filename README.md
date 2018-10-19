# Formula Engine

## Requirements

* cmake > 3.10.0

* c++ compiler
    
    * Windows - Visual Studio 2015 or above

    * Linux - g++ 5.4 or above

* google test >= 1.8.0 

## Install

* Linux

    first clone the repository to the local:
    ```bash
    git clone git@github.com:wegamekinglc/formula_engine.git
    cd formula_engine
    ```

    create a build dir under the root:
    ```bash
    mkdir build
    cd build
    ```

    using cmake to configure and then make:
    ```bash
    cmake ..
    make
    make install
    ```

    then a lib file will be create in the `$root/lib` folder and a executable named `test_suite` will appear in `$root/bin`. Run the test suite:
    ```bash
    ../bin/test_suite
    ```