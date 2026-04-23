#include <cinolib/meshes/meshes.h>
#include <cinolib/ARAP_2D_map.h>
#include <cinolib/profiler.h>
#include <cinolib/gl/load_texture.h>
#include <cinolib/gl/glcanvas.h>
#include <cinolib/gl/surface_mesh_controls.h>

int main(int argc, char **argv)
{
    using namespace cinolib;

    if(argc==2 && std::string(argv[1])=="-h")
    {
        std::cout << "\nARAP UV Mapping" << std::endl;
        std::cout << "===============" << std::endl;
        std::cout << "Usage: ARAP_UVmap [mesh_file]" << std::endl;
        std::cout << "\nComputes ARAP (As-Rigid-As-Possible) UV parameterization." << std::endl;
        std::cout << "If no mesh file is provided, defaults to: " << DATA_PATH << "/maxFace.obj" << std::endl;
        std::cout << "\nDisplays both 3D object space and 2D UV parameterization." << std::endl;
        std::cout << "Controls: rotate (left click), pan (middle click), zoom (scroll)." << std::endl;
        return 0;
    }

    GLcanvas gui_xyz, gui_uvw;

    std::string s = (argc==2) ? std::string(argv[1]) : std::string(DATA_PATH) + "/maxFace.obj";
    DrawableTrimesh<> m_xyz(s.c_str());
    m_xyz.show_wireframe(true);
    m_xyz.show_wireframe_transparency(0.2f);
    m_xyz.show_texture2D(TEXTURE_2D_CHECKERBOARD, 0.005f);
    SurfaceMeshControls<DrawableTrimesh<>> menu_xyz(&m_xyz, &gui_xyz, "OBJ space");
    gui_xyz.push(&m_xyz);
    gui_xyz.push(&menu_xyz);

    // solve for the interior vertices via harmonic map
    Profiler profiler;
    profiler.push("ARAP");
    ARAP_2D_map_data data;
    ARAP_2D_mapping(m_xyz,data);
    profiler.pop();
    m_xyz.updateGL();

    // create a mesh of the uv parametric space (same connectivity, different embedding)
    DrawableTrimesh<> m_uvw = m_xyz;
    m_uvw.copy_uvw_to_xyz(UV_param);
    for(uint vid=0; vid<m_uvw.num_verts(); ++vid) m_uvw.vert(vid).z() = 0.0;
    m_uvw.normalize_bbox();
    m_uvw.update_normals();
    m_uvw.show_wireframe(true);
    m_uvw.show_wireframe_transparency(0.2f);
    m_uvw.show_texture2D(TEXTURE_2D_CHECKERBOARD, 0.005f);
    gui_uvw.push(&m_uvw);
    m_uvw.updateGL();
    SurfaceMeshControls<DrawableTrimesh<>> menu_uvw(&m_uvw, &gui_xyz, "UV space");
    gui_xyz.push(&menu_uvw);

    return gui_xyz.launch({&gui_uvw});
}
