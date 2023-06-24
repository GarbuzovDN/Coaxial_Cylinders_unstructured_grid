Sub Main

'Declares Objects
Dim GrapherApp, Plot, Graph_1, Graph_2, LinePlot, LinePlot2 As Object

'Create an instance of Grapher named "GrapherApp"
Set GrapherApp = CreateObject("Grapher.Application")

'Make Grapher visible
GrapherApp.Visible = False

Dim i As Integer
i = 0

Dim k As Integer
k = 0

While i <= 1140

'Create a new plot document named "Plot"
Set Plot = GrapherApp.Documents.Add(grfPlotDoc)

'Assigns the Documents collection to the variable named "Docs"
Set Docs = GrapherApp.Documents

'Create a new graph with a single line plot
Set Graph = Plot.Shapes.AddLinePlotGraph("C:\Program Visual Studio\Coaxial Ñylinders\Ñoaxial Ñylinders v_0.5\Ñoaxial Ñylinders v_0.5\Documents\BLN\BLN_R1.bln")
'Set Graph = Plot.Shapes.AddLinePlotGraph("D:\Project Visual Studio\Ñoaxial Ñylinders v_0.5\Ñoaxial Ñylinders v_0.5\Documents\BLN\BLN_field_R1.bln")

'Open the worksheet
Set Wks = Docs.Open("C:\Program Visual Studio\Coaxial Ñylinders\Ñoaxial Ñylinders v_1.11\Ñoaxial Ñylinders v_1.11\Documents\Figure\Re=90.000000\El = 1891\Flow Evolution\Fixed Profile\Flow Evolution"+Str(i)+".DAT")

'Read the contents of a cell for text
Text1 = Wks.Cells("A1")
Text2 = Wks.Cells("B1")

Graph.title.text = Text1 + "; " + Text2

'Adjust properties of the X axis
Set XAxis1 = Graph.Axes.Item(1)
XAxis1.Visible = False
XAxis1.AutoMin = False
XAxis1.Min = -1
XAxis1.AutoMax = False
XAxis1.Max = 1

'Adjust properties of the X axis
Set YAxis1 = Graph.Axes.Item(2)
YAxis1.Visible = False
YAxis1.AutoMin = False
YAxis1.Min = -1
YAxis1.AutoMax = False
YAxis1.Max = 1

'Set the line plot to the variable named "LinePlot"
Set R1 = Graph.Plots.Item(1)
R1.line.foreColor  = grfColorBlack
R1.line.width = 0.03

'Add a second line plot to graph and name it "LinePlot2"
Set Obst = Plot.Shapes.AddLinePlotGraph("C:\Program Visual Studio\Coaxial Ñylinders\Ñoaxial Ñylinders v_1.11\Ñoaxial Ñylinders v_1.11\Documents\Blank\Blank_R0.BLN")

'Adjust properties of the X axis
Set XAxis1 = Obst.Axes.Item(1)
XAxis1.Visible = False
XAxis1.AutoMin = False
XAxis1.Min = -1
XAxis1.AutoMax = False
XAxis1.Max = 1

'Adjust properties of the X axis
Set YAxis1 = Obst.Axes.Item(2)
YAxis1.Visible = False
YAxis1.AutoMin = False
YAxis1.Min = -1
YAxis1.AutoMax = False
YAxis1.Max = 1

'Set the line plot to the variable named "LinePlot"
Set Obst_1 = Obst.Plots.Item(1)
Obst_1.line.foreColor  = grfColorBlack
Obst_1.line.width = 0.03
Obst_1.Fill.SetPattern("Solid")
Obst_1.Fill.foreColor = grfColorBlack30
Obst_1.Fill.ForeOpacity = 100

'Obst.Rotation = - i * (k * 0.0499)

Dim st1 As String
Set Evo = Graph.AddLinePlot("C:\Program Visual Studio\Coaxial Ñylinders\Ñoaxial Ñylinders v_1.11\Ñoaxial Ñylinders v_1.11\Documents\Figure\Re=90.000000\El = 1891\Flow Evolution\Fixed Profile\Flow Evolution"+Str(i)+".DAT")
Evo.line.foreColor  = grfColorBlue
Evo.line.width = 0.03

Plot.Export("C:\Program Visual Studio\Coaxial Ñylinders\Ñoaxial Ñylinders v_1.11\Ñoaxial Ñylinders v_1.11\Documents\Figure\Re=90.000000\El = 1891\Flow Evolution\Fixed Profile\GIF\"+Str(i)+".jpg")

	i = i + 5
	k = k + 1

Wend


End Sub
