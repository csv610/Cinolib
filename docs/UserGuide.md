# Cinolib User Guide

## Overview

**Cinolib** is a modern, header-only C++ library for polygonal and polyhedral mesh processing. It provides a unified data structure capable of representing any surface or volumetric element (triangles, quads, polygons, tetrahedra, hexahedra, and general polyhedra) within a single abstract framework.

**Original Author:** Marco Livesu (CNR-IMATI, Italy)  
**Original Repository:** [github.com/mlivesu/cinolib](https://github.com/mlivesu/cinolib)  
**License:** MIT  
**Award:** [2024 SGP Software Award](http://awards.geometryprocessing.org)

This distribution adds a unified root build architecture, automated headless testing (49 CTest-based tests), and modernized dependency management.

---

## Building

### Prerequisites

- CMake >= 3.10
- C++20-compliant compiler
- OpenGL/GLFW/ImGui (for visualization)
- Optional: Boost, VTK, CGAL, Tetgen, Triangle

### Build

```bash
git clone https://github.com/csv610/Cinolib.git
cd Cinolib
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
```

### CMake Options

| Option | Default | Description |
|--------|---------|-------------|
| `CINOLIB_BUILD_EXAMPLES` | ON | Build 48 example applications |
| `CINOLIB_USES_OPENGL_GLFW_IMGUI` | ON | OpenGL visualization |
| `CINOLIB_USES_TETGEN` | ON | Tetrahedralization support |
| `CINOLIB_USES_TRIANGLE` | ON | Triangle mesh generation |
| `CINOLIB_USES_SHEWCHUK_PREDICATES` | ON | Exact geometric predicates |
| `CINOLIB_USES_INDIRECT_PREDICATES` | ON | Indirect predicates |
| `CINOLIB_USES_GRAPH_CUT` | OFF | Graph cut segmentation |
| `CINOLIB_USES_BOOST` | ON | Boost library |
| `CINOLIB_USES_VTK` | ON | VTK support |
| `CINOLIB_USES_SPECTRA` | ON | Spectra eigensolver |
| `CINOLIB_USES_CGAL_GMP_MPFR` | ON | CGAL/GMP/MPFR |

### Running Tests

```bash
cd build
ctest --output-on-failure
```

---

## Quick Start

### Loading and Viewing a Mesh

```cpp
#include <cinolib/meshes/meshes.h>
#include <cinolib/gl/glcanvas.h>
#include <cinolib/gl/surface_mesh_controls.h>

int main(int argc, char **argv)
{
    using namespace cinolib;

    std::string filename = (argc > 1) ? argv[1] : "path/to/mesh.obj";
    DrawableTrimesh<> m(filename.c_str());

    GLcanvas gui;
    SurfaceMeshControls<DrawableTrimesh<>> menu(&m, &gui);
    gui.push(&m);
    gui.push(&menu);
    return gui.launch();
}
```

### Command-Line Format Conversion

```bash
./bin/mesh_format_converter input.obj output.off
./bin/tetrahedralize input.off -pq1.2
./bin/normalize_and_center input.obj
```

---

## Mesh Data Structures

The library provides a unified class hierarchy under `include/cinolib/meshes/meshes.h`:

### Surface Meshes

| Class | Description |
|-------|-------------|
| `Trimesh<>` / `DrawableTrimesh<>` | Triangle meshes |
| `Quadmesh<>` / `DrawableQuadmesh<>` | Quadrilateral meshes |
| `Polygonmesh<>` / `DrawablePolygonmesh<>` | General polygonal meshes |

### Volume Meshes

| Class | Description |
|-------|-------------|
| `Tetmesh<>` / `DrawableTetmesh<>` | Tetrahedral meshes |
| `Hexmesh<>` / `DrawableHexmesh<>` | Hexahedral meshes |
| `Polyhedralmesh<>` / `DrawablePolyhedralmesh<>` | General polyhedral meshes |

The `Drawable*` variants add OpenGL visualization capabilities. All meshes share a common interface for vertices, edges, polygons, and polyhedra.

---

## File I/O

Supported formats (via `include/cinolib/io/read_write.h`):

| Format | Extensions | Type |
|--------|------------|------|
| OBJ | .obj | Surface |
| OFF | .off | Surface |
| STL | .stl | Surface |
| HEDRA | .hedra | Hybrid poly |
| MESH | .mesh | Tet/Poly |
| VTK/VTU | .vtk, .vtu | Volumetric |
| TET | .tet | Tetrahedra |
| NODE/ELE | .node, .ele | Tet mesh |

Reading and writing:

```cpp
#include <cinolib/io/read_write.h>

std::vector<vec3d> verts;
std::vector<std::vector<uint>> polys;

read_OBJ("mesh.obj", verts, polys);
write_OBJ("output.obj", serialized_xyz_from_vec3d(verts), polys);
```

---

## Core Algorithms

### Geodesic Distances (Heat Flow)

```cpp
#include <cinolib/geodesics.h>

GeodesicsCache cache;
compute_geodesics_amortized(mesh, cache, sources).copy_to_mesh(mesh);
```

### Isocontours / Isosurfaces

```cpp
#include <cinolib/drawable_isocontour.h>
#include <cinolib/drawable_isosurface.h>

DrawableIsocontour<> iso(mesh, 0.5f);
iso.tessellate(mesh);
```

### Tetrahedralization

```cpp
#include <cinolib/tetgen_wrap.h>

std::vector<vec3d> v_out;
std::vector<uint> p_out;
tetgen_wrap(input_verts, input_polys, {}, flags, v_out, p_out);
```

### Remeshing

```cpp
#include <cinolib/remesh_BotschKobbelt2004.h>

mesh.edge_mark_sharp_creases(angle_threshold);
remesh_Botsch_Kobbelt_2004(mesh, target_edge_length, true);
```

### Voxelization

```cpp
#include <cinolib/voxelize.h>
#include <cinolib/voxel_grid_to_hexmesh.h>

VoxelGrid grid;
voxelize(polygon_mesh, max_voxels_per_side, grid);
voxel_grid_to_hexmesh(grid, hexmesh, VOXEL_BOUNDARY | VOXEL_INSIDE);
```

### UV Mapping

```cpp
#include <cinolib/lscm.h>
#include <cinolib/ARAP.h>

std::vector<vec2d> uv;
LSCM_parameterization(mesh, boundary_vids, uv);

ARAP_arap(mesh, 2, uv); // 2D ARAP
ARAP_arap(mesh, 3, xyz); // 3D ARAP deformation
```

---

## Visualization

### GLcanvas

The `GLcanvas` class manages OpenGL rendering and user interaction:

```cpp
GLcanvas gui;
gui.push(&drawable_mesh);
gui.push(&menu);
return gui.launch(); // enters event loop
```

### Controls

- **Rotate:** Left click drag
- **Pan:** Middle click drag
- **Zoom:** Scroll wheel
- **Pick:** Cmd+Click (vertex picking mode, see `14_heat_geodesics`)

### Scalar Fields

```cpp
mesh.copy_to_mesh(scalar_field);
mesh.show_texture1D(TEXTURE_1D_HSV_W_ISOLINES);
```

### Textures

```cpp
mesh.show_texture2D(TEXTURE_2D_BITMAP, 1.0f, "texture.png");
```

### Visualization Options

```cpp
mesh.show_wireframe(true);
mesh.show_mesh_flat();
mesh.show_mesh_smooth();
mesh.poly_color_wrt_label();
```

---

## Examples (48 Applications)

All examples are built to `examples/bin/`:

| # | Name | Description |
|---|------|-------------|
| 01 | trimesh_viewer | Triangle mesh viewer |
| 02 | quadmesh_viewer | Quadrilateral mesh viewer |
| 03 | polygonmesh_viewer | General polygonal mesh viewer |
| 04 | tetmesh_viewer | Tetrahedral mesh viewer |
| 05 | hexmesh_viewer | Hexahedral mesh viewer |
| 06 | polyhedralmesh_viewer | General polyhedral mesh viewer |
| 07 | texture_loading | Textured OBJ loading |
| 08 | picking | Interactive vertex picking |
| 09 | polyharmonic_functions_srf | Harmonic functions (surface) |
| 10 | polyharmonic_functions_vol | Harmonic functions (volume) |
| 11 | sphere_mapping | MCF sphere mapping |
| 12 | polygon_mesh_generation | 2D mesh generation (Triangle) |
| 13 | polyhedral_mesh_generation | 3D mesh generation (Tetgen) |
| 14 | heat_geodesics | Heat flow geodesics |
| 15 | polygon_measures | Polygon measures |
| 16 | sphere_sampling | Fibonacci sphere sampling |
| 17 | iso_contours | ISO contour extraction |
| 18 | iso_surfaces | ISO surface extraction |
| 19 | harmonic_map | Discrete harmonic maps |
| 20 | coarse_quad_layouts | Quad mesh coarse layouts |
| 21 | coarse_hex_layouts | Hex mesh coarse layouts |
| 22 | remesher | Botsch-Kobbelt remeshing |
| 23 | sharp_creases | Sharp crease detection |
| 24 | sliced_CLI_loader | 3D printing CLI loader |
| 25 | surface_painter | 3D surface painter |
| 26 | export_surface | Export volumetric mesh skin |
| 27 | import_surface | Import surface to mesh |
| 28 | tetrahedralize | Tetgen tetrahedralization |
| 29 | ambient_occlusion | AO rendering |
| 30 | mesh_format_converter | Format conversion |
| 31 | LSCM | Least Squares Conformal Map |
| 32 | homotopy_basis | Homotopy basis |
| 33 | edge_collapse | Progressive edge collapse |
| 34 | Hermite_RBF | Hermite RBF interpolation |
| 35 | Poisson_sampling | Poisson disk sampling |
| 36 | canonical_polygonal_schema | Canonical schema |
| 37 | find_intersections | Mesh intersection detection |
| 38 | octree | Octree spatial structure |
| 39 | normalize_and_center | Mesh normalization |
| 40 | ARAP_UVmap | ARAP UV mapping |
| 41 | ARAP_deformation | Interactive ARAP deformation |
| 42 | connected_components | Connected component detection |
| 43 | hex2tet | Hex to tet conversion |
| 44 | voxelize_mesh | Mesh voxelization |
| 45 | voxelize_function | Function voxelization |
| 46 | eigenfunctions | Laplacian eigenfunctions |
| 47 | AFM | Advancing Front Mapping |
| 48 | SE | Stripe Embedding |

Example meshes are located in `examples/data/`.

---

## Module Reference

| Module | Path | Description |
|--------|------|-------------|
| Meshes | `include/cinolib/meshes/` | Unified mesh data structures |
| I/O | `include/cinolib/io/` | File format reading/writing |
| GL | `include/cinolib/gl/` | OpenGL canvas and controls |
| Algorithms | `include/cinolib/` | Geometric algorithms, fields |

---

## Citation

If you use Cinolib in academic work, cite:

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
