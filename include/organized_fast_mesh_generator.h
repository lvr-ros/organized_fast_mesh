/*
 *  Software License Agreement (BSD License)
 *
 *  Robot Operating System code by the University of Osnabrück
 *  Copyright (c) 2015, University of Osnabrück
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   1. Redistributions of source code must retain the above 
 *      copyright notice, this list of conditions and the following
 *      disclaimer.
 *
 *   2. Redistributions in binary form must reproduce the above 
 *      copyright notice, this list of conditions and the following
 *      disclaimer in the documentation and/or other materials provided
 *      with the distribution.
 *
 *   3. Neither the name of the copyright holder nor the names of its
 *      contributors may be used to endorse or promote products derived
 *      from this software without specific prior written permission.
 *
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 *  TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
 *  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *
 *  organized_point_cloud_generation.h
 *
 *  author: Sebastian Pütz <spuetz@uni-osnabrueck.de>
 */


#ifndef ORGANIZED_FAST_MESH_GENERATOR_H_
#define ORGANIZED_FAST_MESH_GENERATOR_H_
#include <lvr/reconstruction/MeshGenerator.hpp>
#include <lvr/geometry/BaseMesh.hpp>
#include <lvr/geometry/ColorVertex.hpp>
#include <lvr/geometry/Normal.hpp>
#include <lvr/geometry/HalfEdgeVertex.hpp>
#include <lvr/geometry/Tesselator.hpp>

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>



/**
 * \brief Generates an organized fast mesh out of an organized point cloud
 */
class OrganizedFastMeshGenerator : public lvr::MeshGenerator<lvr::ColorVertex<float, int>, lvr::Normal<float> >{

  public:
    /**
     * \brief Constrcutor
     * \param organized_scan The organized pcl point cloud 
     */
    OrganizedFastMeshGenerator(pcl::PointCloud<pcl::PointNormal>& organized_scan);
    
    /**
     * \brief generates the organized fast mesh
     * \param a reference to the mesh to fill with the data
     */
    virtual void getMesh(lvr::BaseMesh<lvr::ColorVertex<float, int>, lvr::Normal<float> >& mesh);
    
    /**
     * \brief sets the maximum edge length to filter big leaps in the 3D depth data
     */
    void setEdgeThreshold(float dist);
    
  	bool getContour(std::vector<int>& contour_indices);
  	
    void fillContour(std::vector<int>& contour_indices, lvr::BaseMesh<lvr::ColorVertex<float, int>, lvr::Normal<float> >& mesh, std::vector<int>& fillup_indices);

  private:

	void normalize(int& x, int& y);

    /**
     * \brief converts a pcl point into a lvr color vertex
     * \param in pcl point
     * \param out lvr point
     */
    void pclToLvrNormal(pcl::PointNormal& in, lvr::Normalf& out);

    /**
     * \brief converts a pcl point into a lvr color vertex
     * \param in pcl point
     * \param out lvr point
     */
    void pclToLvrVertex(pcl::PointNormal& in, lvr::ColorVertex<float, int>& out);
    
    void pclToLvrVertex(pcl::PointNormal& in, lvr::Vertexf& out);
    
    void lvrToPclVertex(lvr::Vertexf& vertex, lvr::Normalf& normal, pcl::PointNormal& out);

    
    /**
     * \brief calculates the corresponding index for x and y
     * \param x x-coord
     * \param y y-coord
     * \return index for x and y
     */
    uint32_t toIndex(int x, int y);
    
    
    /**
     * \brief checks if the given vertex exists
     * \param vertex The vertex to check for existence
     * \return true if all coords are not nan
     */
    bool pointExists(lvr::Vertexf& vertex);
    
    bool pointExists(pcl::PointNormal& point);


    /**
     * \brief checks if the given vertex exists
     * \param vertex The vertex to check for existence
     * \return true if all coords are not nan
     */
    bool pointExists(lvr::ColorVertex<float, int>& vertex);

    /**
     * \brief checks if the given normal exists
     * \param normal The normal to check for existence
     * \return true if all coords are not nan
     */
    bool normalExists(lvr::Normalf& normal);

    /**
     * \brief tests if the face has long edges
     */
    bool hasLongEdge(int a, int b, int c, float sqr_edge_threshold);
    
    void showField(std::map<int, int>& index_map, int x, int y);
	  
    bool findContour(std::map<int, int>& index_map, std::vector<int>& contour_indices, int start_x, int start_y, int end_x, int end_y);
    
	bool isValid(int x, int y);

	bool inBounds(int x, int y);

    //! \holds the organized point cloud
    pcl::PointCloud<pcl::PointNormal> organized_scan;
    
    pcl::PointCloud<pcl::PointNormal>::Ptr mesh_points;
    //! \holds the vertices in the same order as in the mesh
    std::vector<lvr::ColorVertex<float, int> >vertices;
    //! \threshold value for the longe edge test
    float sqr_edge_threshold;
    //! \map old indices to new indices, invalid indices are -1
    std::map<int, int> index_map;
    
    size_t index_map_index;

    

};

#endif /* organized_fast_mesh_generator.h */
