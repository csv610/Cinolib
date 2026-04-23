#include <cinolib/meshes/meshes.h>
#include <cinolib/gl/glcanvas.h>
#include <cinolib/triangle_wrap.h>
#include <cinolib/dual_mesh.h>

int main(int argc, char **argv)
{
    using namespace cinolib;

    if(argc==2 && std::string(argv[1])=="-h")
    {
        std::cout << "\nPolygon Mesh Generation" << std::endl;
        std::cout << "=======================" << std::endl;
        std::cout << "Usage: polygon_mesh_generation [polygon_mesh_file]" << std::endl;
        std::cout << "\nGenerates triangle and polygon (Voronoi) meshes from a polygon mesh." << std::endl;
        std::cout << "If no mesh file is provided, defaults to: " << DATA_PATH << "/E.obj" << std::endl;
        std::cout << "\nDisplays three meshes: input, triangulated, and dual (Voronoi) polygon mesh." << std::endl;
        std::cout << "Controls: rotate (left click), pan (middle click), zoom (scroll)." << std::endl;
        return 0;
    }

    std::string s = (argc==2) ? std::string(argv[1]) : std::string(DATA_PATH) + "/E.obj";
    DrawablePolygonmesh<> m(s.c_str());

    // make trimesh
    double area_thresh = 0.01 * m.bbox().diag(); // force triangles to be smaller than 5% of bbox diag
    char opt[100];
    sprintf(opt, "Qqa%f", area_thresh);
    DrawableTrimesh<> m_tri;
    triangle_wrap(m.vector_verts(), m.vector_edges(), {}, 0, opt, m_tri);
    m_tri.translate(vec3d(m.bbox().delta_x()*1.5,0,0));
    m_tri.updateGL();

    // make polygon (voronoi) mesh
    DrawablePolygonmesh<> m_poly;
    dual_mesh(m_tri, m_poly, true);
    m_poly.translate(vec3d(m.bbox().delta_x()*1.5,0,0));
    m_poly.updateGL();

    GLcanvas gui;
    gui.push(&m);
    gui.push(&m_tri);
    gui.push(&m_poly);

    return gui.launch();
}
