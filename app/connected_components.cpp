#include <cinolib/meshes/meshes.h>
#include <cinolib/connected_components.h>
#include <cinolib/string_utilities.h>
#include <iostream>

int main(int argc, char **argv)
{
    using namespace cinolib;

    if(argc<2)
    {
        std::cout << "\nUsage: connected_components <input> [output_dir]\n\n"
                  << "Find and export connected components from a mesh.\n"
                  << "Input: mesh (OBJ, OFF)\n"
                  << "Output dir: directory for component files (default: components/)\n"
                  << "\nSaves each component as a separate OBJ file.\n"
                  << std::endl;
        return -1;
    }

    std::string input(argv[1]);
    std::string output_dir = (argc>=3) ? argv[2] : "components";

    Trimesh<> m(input.c_str());

    std::vector<std::unordered_set<uint>> ccs;
    uint n_ccs = connected_components(m, ccs);

    std::cout << "Found " << n_ccs << " connected components" << std::endl;

    system(("mkdir -p " + output_dir).c_str());

    std::string base = get_file_name(input, false);
    for(uint i=0; i<n_ccs; ++i)
    {
        std::vector<vec3d> comp_verts;
        std::vector<std::vector<uint>> comp_polys;
        std::unordered_map<uint, uint> vmap, rmap;

        uint new_vid = 0;
        for(uint pid=0; pid<m.num_polys(); ++pid)
        {
            bool in_cc = ccs[i].count(m.poly_vert_id(pid, 0));
            if(!in_cc) continue;

            std::vector<uint> p;
            for(uint j=0; j<m.verts_per_poly(pid); ++j)
            {
                uint vid = m.poly_vert_id(pid, j);
                if(vmap.find(vid) == vmap.end())
                {
                    vmap[vid] = new_vid;
                    rmap[new_vid] = vid;
                    comp_verts.push_back(m.vert(vid));
                    ++new_vid;
                }
                p.push_back(vmap[vid]);
            }
            comp_polys.push_back(p);
        }

        Trimesh<> comp(comp_verts, comp_polys);
        std::string outFile = output_dir + "/" + base + "_cc" + std::to_string(i) + ".obj";
        comp.save(outFile.c_str());
    }

    std::cout << "Exported to " << output_dir << "/" << std::endl;

    return 0;
}