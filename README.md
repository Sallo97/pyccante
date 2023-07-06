# pyccante
pyccante is a Python library that interfaces to [Piccante](https://github.com/cnr-isti-vclab/piccante), an image processing library aimed for both High Dynamic Range (HDR) and standard imaging. Python bindings are generated using pybind11.

## pyccante GUI
the pyccante GUI is a Graphical User Interface for pyccante, offering a more accessible way to
edit image for users of every skill-level

## Compilation
Start by cloning the pyccante repository from GitHub using the following commands:
```
$ git clone https :// github . com / Sallo97 / pyccante . git
$ cd pyccante
```
### Set the build directory
Inside the pyccante directory, with CMake create the `build` folder, and inside it gen-
erates the necessary build files based on your system configuration. To do so, run the
following command:
```
$ cmake -S . -B build
```
### Build the project
CMake offers the possibility to build the project in parallel with the `--parallel` parame-
ter, making the compilation time shorter. The following command shows how to build the
project using four CPU cores:
```
$ cmake --build build --parallel 4
```
### Compiled library
If the compilation succeeds, the generated binary library can be found inside the `src`
directory in the `build` folder. The name of the file is `pyccante.cPython-310-`, fol-
lowed by a specification of the system where it was built and terminating with the `.so`
extension (e.g., compiling on Ubuntu generates the file pyccante.cPython-310-x86 64-
linux-gnu). 
Note that the name of the file must not be changed, Python uses it to infer
information about the library, and with a different name it will not import it.

### Known compilation warnings
When compiling pyccante, some compilers could show warnings related to the [tinyexr](https://github.com/syoyo/tinyexr)
header-only library. The support library is used in Piccante for handling the EXR image
file format. These warnings are typically related to deprecated features within tinyexr.
Since the library is beyond the scope of the thesis and the warning do not directly affect
any functionality of pyccante, it has been decided to ignore them.
Note that any other warning message beyond the tinyexr library is not expected and
should not be ignored.

## Using pyccante
Once pyccante has been successfully compiled, it is possible to use its functionality
within Python by following these steps:
Set the library path
To use pyccante it is important to ensure that the binary library file is accessible to
Python. By default, Python searches for modules in the current directory and within a
group of standard paths called PythonPATH. It’s possible to add the pyccante’s path to
PythonPATH, allowing the import of the library from anywhere in the system.
67
On Linux use the following command in terminal:
1 export PYTHONPATH = path / to / pyccante / library
Import the module in Python
Import the pyccante library in Python using the following command:
1 import pyccante
From this point onward it is possible to call pyccante functions or create instances of
its classes, for example:
1 img = pyccante . Image ( " test . png " )
2 img . rotate90CW ()
3 img . save ( " path / to / the / image . png " )
Code A.4: This example rotates animage by 90° clockwise and then saves the result.
A.4 Run the pyccante GUI
For running the pyccante GUI open a terminal or command prompt inside the “pyccan-
teGUI” folder in the main directory and type the following action:
1 python ./ main . py
Code A.5: Note that some systems the command to execute python scripts is python
