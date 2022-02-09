//*****************************************************************//
//    Albany 2.0:  Copyright 2012 Sandia Corporation               //
//    This Software is released under the BSD license detailed     //
//    in the file "license.txt" in the top-level Albany directory  //
//*****************************************************************//

#ifndef ALBANY_MESH_SPECS_HPP
#define ALBANY_MESH_SPECS_HPP

#include "Shards_CellTopology.hpp"

#include <vector>
#include <string>

// The MeshSpecsStruct holds information (loaded mostly from STK::metaData),
// which is needed to create an Albany::Problem.
// The idea is that in order to build the problem's evaluators, we do not
// need to have a mesh. All we need are general topological information about the mesh.
// This includes worksetSize, CellTopologyData, etc.

namespace Albany {

struct MeshSpecsStruct
{
  // This constructor initializes all the possible informations in a mesh specs object.
  MeshSpecsStruct(
      const shards::CellTopology&       cell_topo_,
      const std::vector<std::string>&   nsNames_,
      const std::vector<std::string>&   ssNames_,
      const int                         worksetSize_,
      const bool                        interleavedOrdering_);

  // Note: non-const members can change during mesh adaptation
  const shards::CellTopology  cell_topo;
  std::vector<std::string>    nsNames; // Node Sets Names
  std::vector<std::string>    ssNames; // Side Sets Names
  int                         worksetSize;
  const bool                  interleavedOrdering;
};

} // namespace Albany

#endif // ALBANY_MESH_SPECS_HPP
