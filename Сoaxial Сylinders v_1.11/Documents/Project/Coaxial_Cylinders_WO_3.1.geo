cl__1 = 1;
Point(1) = {0, 0, 0, cl__1};
Point(2) = {0.05, -0.1936, 0, cl__1};
Point(3) = {0.1936, -0.05, 0, cl__1};
Point(4) = {0.7, -0.05, 0, cl__1};
Point(5) = {0.7, 0.05, 0, cl__1};
Point(6) = {0.1936, 0.05, 0, cl__1};
Point(7) = {0.05, 0.1936, 0, cl__1};
Point(8) = {0.05, 0.7, -0, cl__1};
Point(9) = {-0.05, 0.7, -0, cl__1};
Point(10) = {-0.05, 0.1936, -0, cl__1};
Point(11) = {-0.1936, 0.05, -0, cl__1};
Point(12) = {-0.7, 0.05, 0, cl__1};
Point(13) = {-0.7, -0.05, 0, cl__1};
Point(14) = {-0.1936, -0.05, 0, cl__1};
Point(15) = {-0.05, -0.1936, 0, cl__1};
Point(16) = {-0.05, -0.7, 0, cl__1};
Point(17) = {0.05, -0.7, 0, cl__1};
Point(18) = {0, -1, 0, cl__1};
Point(19) = {0, 1, 0, cl__1};
Circle(1) = {2, 1, 3};
Line(2) = {3, 4};
Line(3) = {4, 5};
Line(4) = {5, 6};
Circle(5) = {6, 1, 7};
Line(6) = {7, 8};
Line(7) = {8, 9};
Line(8) = {9, 10};
Circle(9) = {10, 1, 11};
Line(10) = {11, 12};
Line(11) = {12, 13};
Line(12) = {13, 14};
Circle(13) = {14, 1, 15};
Line(14) = {15, 16};
Line(15) = {16, 17};
Line(16) = {17, 2};
Circle(17) = {19, 1, 18};
Circle(18) = {18, 1, 19};
Curve Loop(1) = {18, 17, -5, -4, -3, -2, -1, -16, -15, -14, -13, -12, -11, -10, -9, -8, -7, -6};
Plane Surface(1) = {1};
//+
Transfinite Curve {7, 11, 3, 15} = 8 Using Progression 1;
//+
Transfinite Curve {8, 6, 10, 12, 14, 16, 2, 4} = 30 Using Progression 1;
//+
Transfinite Curve {9, 5, 13, 1} = 10 Using Progression 1;
//+
Transfinite Curve {9, 5, 13, 1} = 15 Using Progression 1;
//+
Transfinite Curve {17, 18} = 50 Using Progression 1;
//+
Transfinite Curve {17, 18} = 55 Using Progression 1;
//+
Transfinite Curve {17, 18} = 75 Using Progression 1;
//+
Transfinite Curve {17, 18} = 60 Using Progression 1;
//+
Transfinite Curve {8, 6, 10, 12, 14, 16, 2, 4} = 25 Using Progression 1;
//+
Transfinite Curve {9, 5, 13, 1} = 10 Using Progression 1;
//+
Transfinite Curve {7, 11, 3, 15} = 6 Using Progression 1;
