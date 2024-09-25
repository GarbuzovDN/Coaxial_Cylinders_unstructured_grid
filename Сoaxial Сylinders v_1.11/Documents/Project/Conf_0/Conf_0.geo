// Gmsh project created on Sun Sep 22 17:04:20 2024
SetFactory("OpenCASCADE");
//+
Point(1) = {0, 0, 0, 1.0};
//+
Point(2) = {0, 1, 0, 1.0};
//+
Point(3) = {0, -1, 0, 1.0};
//+
Point(4) = {0, 0.2, 0, 1.0};
//+
Point(5) = {0, -0.2, 0, 1.0};
//+
Circle(1) = {4, 1, 5};
//+
Circle(2) = {5, 1, 4};
//+
Circle(3) = {2, 1, 3};
//+
Circle(4) = {3, 1, 2};
//+
Curve Loop(1) = {4, 3};
//+
Curve Loop(2) = {2, 1};
//+
Curve Loop(3) = {4, 3};
//+
Curve Loop(4) = {2, 1};
//+
Plane Surface(1) = {3, 4};
