cl__1 = 1;
Point(1) = {0, 0, 0, cl__1};
Point(2) = {0, -0.2, 0, cl__1};
Point(3) = {0.05, 0.1936, 0, cl__1};
Point(4) = {-0.05, 0.1936, 0, cl__1};
Point(5) = {0.05, 0.7, 0, cl__1};
Point(6) = {-0.05, 0.7, 0, cl__1};
Point(7) = {0, 0, 0, cl__1};
Point(8) = {0, 1, 0, cl__1};
Point(9) = {0, -1, 0, cl__1};
Circle(1) = {4, 1, 2};
Circle(2) = {2, 1, 3};
Line(3) = {3, 5};
Line(4) = {5, 6};
Line(5) = {6, 4};
Circle(6) = {8, 1, 9};
Circle(7) = {9, 1, 8};
Curve Loop(1) = {6, 7, -3, -2, -1, -5, -4};
Plane Surface(1) = {1};
//+
Transfinite Curve {5, 4, 5} = 8 Using Progression 1;
//+
Transfinite Curve {5, 3} = 15 Using Progression 1;
//+
Transfinite Curve {5, 3} = 30 Using Progression 1;
//+
Transfinite Curve {1, 2} = 30 Using Progression 1;
//+
Transfinite Curve {6, 7} = 30 Using Progression 1;
//+
Transfinite Curve {6, 7} = 60 Using Progression 1;
//+
Transfinite Curve {6, 7} = 50 Using Progression 1;
//+
Transfinite Curve {6, 7} = 55 Using Progression 1;
//+
Transfinite Curve {6, 7} = 52 Using Progression 1;
//+
Transfinite Curve {6, 7} = 53 Using Progression 1;
