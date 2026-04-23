#include <cinolib/voxelize.h>
#include <cinolib/voxel_grid_to_hexmesh.h>
#include <cinolib/profiler.h>
#include <cinolib/gl/glcanvas.h>
#include <cinolib/gl/surface_mesh_controls.h>
#include <cinolib/gl/volume_mesh_controls.h>

using namespace cinolib;

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

int main(int argc, char *argv[])
{
    if(argc==2 && std::string(argv[1])=="-h")
    {
        std::cout << "\nVoxelize Mesh" << std::endl;
        std::cout << "=============" << std::endl;
        std::cout << "Usage: voxelize_mesh [polygon_mesh] [max_voxels_per_side] [voxel_type]" << std::endl;
        std::cout << "\nVoxelizes a polygon mesh into a hexahedral voxel grid." << std::endl;
        std::cout << "If no mesh file is provided, defaults to: " << DATA_PATH << "/lion_vase_poly.off" << std::endl;
        std::cout << "Optional max_voxels_per_side (default: 64)" << std::endl;
        std::cout << "Optional voxel_type: 1=boundary, 2=inside, 3=both (default: 3)" << std::endl;
        std::cout << "\nDisplays both original mesh and voxelized hexmesh." << std::endl;
        std::cout << "Controls: rotate (left click), pan (middle click), zoom (scroll)." << std::endl;
        return 0;
    }

    std::string s = (argc>=2) ? std::string(argv[1]) : std::string(DATA_PATH) + "/lion_vase_poly.off";
    DrawablePolygonmesh<> m(s.c_str());

    uint max_voxels_per_side = (argc>=3) ? atoi(argv[2]) : 64;
    int  voxel_type = (argc>=4) ? atoi(argv[3]) : VOXEL_BOUNDARY | VOXEL_INSIDE;

    VoxelGrid g;
    Profiler p;
    p.push("voxelize");
    voxelize(m, max_voxels_per_side, g);
    p.pop();
    std::cout << "grid dimensions : " << g.dim[0] << " x " << g.dim[1] << " x " << g.dim[2] << std::endl;

    DrawableHexmesh<> h;
    p.push("voxel grid to hexmesh");
    voxel_grid_to_hexmesh(g,h,voxel_type);
    p.pop();
    h.poly_color_wrt_label();
    h.updateGL();

    GLcanvas gui;
    gui.push(&m);
    gui.push(&h);
    gui.push(new SurfaceMeshControls<DrawablePolygonmesh<>>(&m,&gui));
    gui.push(new VolumeMeshControls<DrawableHexmesh<>>(&h,&gui,"voxel grid"));
    return gui.launch();
}
