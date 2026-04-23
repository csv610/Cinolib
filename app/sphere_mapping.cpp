#include <cinolib/meshes/meshes.h>
#include <cinolib/mean_curv_flow.h>
#include <cinolib/string_utilities.h>
#include <iostream>

int main(int argc, char **argv)
{
    using namespace cinolib;

    if(argc<2)
    {
        std::cout << "\nUsage: sphere_mapping <input> [iterations] [timestep]\n\n"
                  << "Map mesh to sphere using Mean Curvature Flow.\n"
                  << "Input: surface mesh (OBJ, OFF)\n"
                  << "Iterations: number of iterations (default: 10)\n"
                  << "Timestep: time step (default: 0.005)\n"
                  << "\nOutput: OBJ with mapped coordinates\n"
                  << std::endl;
        return -1;
    }

    std::string input(argv[1]);
    uint iterations = (argc>=3) ? atoi(argv[2]) : 10;
    double timestep = (argc>=4) ? atof(argv[3]) : 0.005;

    Trimesh<> m(input.c_str());

    std::cout << "Running MCF (" << iterations << " iters, dt=" << timestep << ")..." << std::endl;
    MCF(m, iterations, timestep);

    std::string output = get_file_name(input, false) + "_sphere.obj";
    m.save(output.c_str());

    std::cout << "Saved to " << output << std::endl;

    return 0;
}