// Gmsh project created on Wed Aug 03 14:33:09 2022
SetFactory("OpenCASCADE");
//+
Circle(1) = {0, 0, 0, 1, 0, 2*Pi};
//+
Circle(2) = {0, 0, 0, 0.2, 0, 2*Pi};
//+
Curve Loop(1) = {1};
//+
Curve Loop(2) = {2};
//+
Plane Surface(1) = {1, 2};
//+
Physical Curve("wall_1", 3) = {1};
//+
Physical Curve("wall_2", 4) = {2};
//+
Physical Surface("comp", 5) = {1};
