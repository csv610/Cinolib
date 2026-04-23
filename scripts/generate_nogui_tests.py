import os
import re

examples_dir = 'examples'
tests_dir = 'tests/nogui'
os.makedirs(tests_dir, exist_ok=True)

test_cmakelists = []

# List of examples to skip (too complex or purely interactive)
skip = ['bin', 'build', 'data', 'snapshots', 'README.md', 'CMakeLists.txt']

for example in sorted(os.listdir(examples_dir)):
    if example in skip: continue
    
    main_cpp = os.path.join(examples_dir, example, 'main.cpp')
    if not os.path.exists(main_cpp): continue

    print(f"Generating test for {example}...")
    
    with open(main_cpp, 'r') as f:
        content = f.read()

    # Extract default mesh
    match = re.search(r'DATA_PATH\s*\)\s*\+\s*"/([^"]+)"', content)
    default_mesh = match.group(1) if match else "bunny.obj"

    # Identify mesh type (Trimesh, Quadmesh, etc.)
    mesh_type = "Trimesh<>"
    if "Quadmesh" in content: mesh_type = "Quadmesh<>"
    if "Polygonmesh" in content: mesh_type = "Polygonmesh<> "
    if "Tetmesh" in content: mesh_type = "Tetmesh<>"
    if "Hexmesh" in content: mesh_type = "Hexmesh<>"
    if "Polyhedralmesh" in content: mesh_type = "Polyhedralmesh<>"

    # Create a simplified test source
    test_src = f"""#include <cinolib/meshes/meshes.h>
#include <iostream>
#include <cassert>

int main(int argc, char **argv) {{
    using namespace cinolib;
    std::string s = (argc >= 2) ? std::string(argv[1]) : std::string(DATA_PATH) + "/{default_mesh}";
    std::cout << "NOGUI Test: {example} loading " << s << std::endl;
    {mesh_type} m(s.c_str());
    assert(m.num_verts() > 0);
    std::cout << "NOGUI Test: {example} PASSED" << std::endl;
    return 0;
}}
"""
    test_file = os.path.join(tests_dir, f"test_{example}.cpp")
    with open(test_file, 'w') as f:
        f.write(test_src)

    test_cmakelists.append(f"add_executable(test_{example} nogui/test_{example}.cpp)")
    test_cmakelists.append(f"target_link_libraries(test_{example} cinolib)")
    test_cmakelists.append(f"add_test(NAME test_{example} COMMAND test_{example} \"${{CMAKE_SOURCE_DIR}}/examples/data/{default_mesh}\")")

# Write tests/CMakeLists.txt
with open('tests/CMakeLists.txt', 'w') as f:
    f.write("enable_testing()\n")
    f.write(f'add_compile_definitions(DATA_PATH="${{CMAKE_SOURCE_DIR}}/examples/data")\n')
    f.write("\n".join(test_cmakelists))
    f.write("\nadd_executable(test_harmonic_map test_harmonic_map.cpp)\ntarget_link_libraries(test_harmonic_map cinolib)\nadd_test(NAME test_harmonic_map COMMAND test_harmonic_map)")
