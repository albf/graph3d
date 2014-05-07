Graphic 3D - Alexandre Brisighello and Tristan Sahel

To Compile the program:
    qmake-qt4 cg3D.pro
    make

To execute the program:
    ./cg3D

The project contains, at the root:
    - this README.txt file;
    - the Makefile, used for compilation, which runs on the school’s machines
    - the cg3d.pro file, used for compilation
    - the renderable and viewer {.h, .cpp} files, which provide objects and methods for the implementation of the project
    - the source code files.

The source code files include the following classes:
    - bubble: class that defines the air bubbles coming out of the diver’s lungs and up to the surface of the ocean
    - cam: class that defines the camera, i.e. the point of view from which the user is watching the scene
    - crab: class that defines the crabs walking on the sand at the bottom of the ocean, as the diver swims through
    - diver: class that defines the human being who observes the scene and who gets attacked…
    - fishA: class that defines a first type of fish which the diver encounters
    - fishB: class that defines a second type of fish which the diver encounters
    - light: class that defines the lightning of the scene. It provides the impression of the fog
    - main.cpp: main application, in which all objects are instantiated and the scene is built
    - pacMan: class that defines the dangerous encounter the diver is about to have
    - seaFloor: class that defines the sand-textured floor at the bottom of the sea.