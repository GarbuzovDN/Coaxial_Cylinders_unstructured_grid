cl__1 = 1;
Point(1) = {0, 0, 0, cl__1};
Point(2) = {0, -0.2, 0, cl__1};
Point(3) = {0, 0.2, 0, cl__1};
Point(4) = {0.05, 0.5, 0, cl__1};
Point(5) = {0.05, 0.7, 0, cl__1};
Point(6) = {-0.05, 0.7, 0, cl__1};
Point(7) = {-0.05, 0.5, 0, cl__1};
Point(8) = {-0.05, -0.5, 0, cl__1};
Point(9) = {-0.05, -0.7, 0, cl__1};
Point(10) = {0.05, -0.7, 0, cl__1};
Point(11) = {0.05, -0.5, 0, cl__1};
Point(12) = {0, 1, 0, cl__1};
Point(13) = {0, -1, 0, cl__1};
Circle(1) = {2, 1, 3};
Circle(2) = {3, 1, 2};
Line(3) = {4, 5};
Line(4) = {5, 6};
Line(5) = {6, 7};
Line(6) = {7, 4};
Line(7) = {8, 9};
Line(8) = {9, 10};
Line(9) = {10, 11};
Line(10) = {11, 8};
Circle(11) = {12, 1, 13};
Circle(12) = {13, 1, 12};
Curve Loop(1) = {4, 5, 6, 3, -2, -1, -9, -8, -7, -10, -12, -11};
Plane Surface(1) = {1};
