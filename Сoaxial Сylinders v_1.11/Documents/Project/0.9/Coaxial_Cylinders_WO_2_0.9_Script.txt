//+
Point(1) = {0, 0, 0, 1.0};
//+
Point(2) = {0.025, 0.0545436, 0, 1.0};
//+
Point(3) = {0.025, 0.9, 0, 1.0};
//+
Point(4) = {-0.025, 0.9, 0, 1.0};
//+
Point(5) = {-0.025, 0.0545436, 0, 1.0};
//+
Point(6) = {-0.025, -0.0545436, 0, 1.0};
//+
Point(7) = {-0.025, -0.9, 0, 1.0};
//+
Point(8) = {0.025, -0.9, 0, 1.0};
//+
Point(9) = {0.025, -0.0545436, 0, 1.0};
//+
Point(10) = {0, 1, 0, 1.0};
//+
Point(11) = {0, -1, 0, 1.0};
//+
Circle(4) = {5, 1, 6};
//+
Circle(8) = {9, 1, 2};
//+
Line(1) = {2, 3};
//+
Line(2) = {3, 4};
//+
Line(3) = {4, 5};
//+
Line(5) = {6, 7};
//+
Line(6) = {7, 8};
//+
Line(7) = {8, 9};
//+
Circle(11) = {10, 1, 11};
//+
Circle(12) = {11, 1, 10};
//+
Curve Loop(1) = {11, 12};
//+
Curve Loop(2) = {3, 4, 5, 1, 6, 7, 8, 2};
//+
Plane Surface(1) = {1, 2};
//+
Transfinite Curve {1, 3, 5, 7} = 50 Using Progression 1;
//+
Transfinite Curve {4, 8} = 10 Using Progression 1;
//+
Transfinite Curve {2, 6} = 5 Using Progression 1;
