# Cinolib: Professional Port & Automated Testing Suite

This repository provides a modernized port and enhanced distribution of **Cinolib**, the award-winning C++ library for polygonal and polyhedral mesh processing originally developed by Marco Livesu.

## Project Overview

Cinolib is a comprehensive header-only library designed for researchers and engineers in geometry processing. It offers a unique, unified data structure capable of representing any surface or volumetric element (triangles, quads, polygons, tetrahedra, hexahedra, and general polyhedra) within a single abstract framework.

**Original Author:** [Marco Livesu](https://github.com/mlivesu)  
**Original Repository:** [mlivesu/cinolib](https://github.com/mlivesu/cinolib)

---

## Port Enhancements & Contributions

This distribution, implemented by **Gemini CLI**, introduces several critical infrastructure improvements designed for professional development environments and Continuous Integration (CI) workflows:

### 1. Unified Root Build Architecture
The project has been restructured with a single top-level `CMakeLists.txt`. This allows for a streamlined "single-command" build of the entire library, including all 48 original examples and the newly introduced test suite.

### 2. Automated Headless Testing Framework (NoGUI)
To support server-side validation and CI pipelines, a specialized headless testing framework has been added:
*   **Automatic Test Generation**: Includes `scripts/generate_nogui_tests.py`, which dynamically parses example logic to create display-less verification tests.
*   **Verification Suite**: 49 new tests verify the core algorithmic integrity of the library (mesh I/O, connectivity, mapping, and volumetric generation) without requiring a graphical display or GPU.
*   **CTest Integration**: Full support for the CMake test driver for rapid regression testing.

### 3. Modernized dependency Management
The build system has been optimized to handle external dependencies (Tetgen, Triangle, Eigen, etc.) more robustly, ensuring compatibility across different operating systems and compiler versions.

---

## Getting Started

### Prerequisites
*   CMake (>= 3.10)
*   C++ Compiler (C++20 compliant)
*   Optional: Boost, VTK, CGAL (for extended functionality)

### Installation and Build
```bash
git clone https://github.com/csv610/Cinolib.git
cd Cinolib
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
```

### Running the Test Suite
Verification is handled via `ctest`. This will execute all headless tests to ensure the library is operating correctly in your environment.
```bash
cd build
ctest --output-on-failure
```

---

## Original Credits and Awards
Cinolib received the **[Symposium on Geometry Processing Software Award](http://awards.geometryprocessing.org)** in 2024.

If you utilize this library in an academic context, please cite the original work:

```bibtex
@article{cinolib,
  title   = {cinolib: a generic programming header only C++ library for processing polygonal and polyhedral meshes},
  author  = {Livesu, Marco},
  journal = {Transactions on Computational Science XXXIV},
  series  = {Lecture Notes in Computer Science},
  year    = {2019},
  doi     = {10.1007/978-3-662-59958-7_4}
}
```

## License
This project follows the licensing terms of the original Cinolib library. Please refer to the `LICENSE` file for full details.
