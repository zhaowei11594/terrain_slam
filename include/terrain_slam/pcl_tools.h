// The MIT License (MIT)

// Copyright (c) 2016 Miquel Massot Campos

//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
//  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.

#ifndef PCL_TOOLS_H
#define PCL_TOOLS_H

#include <pcl/common/common.h>
#include <pcl/point_types.h>

typedef pcl::PointXYZ PointT;
typedef pcl::PointCloud<PointT> CloudT;

namespace pcl_tools {

/**
 * @brief      Convert an Eigen pointcloud to a PCL pointcloud
 *
 * @param[in]  points       Eigen pointcloud
 *
 * @return     PCL pointcloud pointer
 */
static CloudT::Ptr toPCL(const Eigen::Matrix4Xd &points) {
  CloudT::Ptr cloud(new CloudT);
  cloud->width = points.cols();
  cloud->height = 1;  // unorganized point cloud
  cloud->is_dense = false;
  // Loop through all points
  for (int i = 0; i < points.cols(); i++) {
    double x = points(0, i);
    double y = points(1, i);
    double z = points(2, i);
    cloud->points.push_back(PointT(x, y, z));
  }
  return cloud;
}

/**
 * @brief      Convert a PCL pointcloud to an eigen pointcloud
 *
 * @param[in]  cloud  PCL cloud
 *
 * @return     Eigen pointcloud
 */
static Eigen::Matrix4Xd fromPCL(const CloudT::Ptr& cloud) {
  Eigen::Matrix4Xd points(4, cloud->size());
  // Loop through all points
  for (int i = 0; i < points.cols(); i++) {
    points(0, i) = cloud->points[i].x;
    points(1, i) = cloud->points[i].y;
    points(2, i) = cloud->points[i].z;
  }
  return points;
}

}  // namespace

#endif // PCL_TOOLS_H
