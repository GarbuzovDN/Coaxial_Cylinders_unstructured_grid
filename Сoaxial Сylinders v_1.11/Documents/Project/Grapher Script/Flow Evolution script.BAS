Sub Main

'Declares Objects
Dim GrapherApp, Plot, Graph, LinePlot, SplineFit, LinePlot2 As Object

'Create an instance of Grapher named "GrapherApp"
Set GrapherApp = CreateObject("Grapher.Application")

'Make Grapher visible
GrapherApp.Visible = False

Dim i As Integer
i = 0

While i <= 900

'Create a new plot document named "Plot"
Set Plot = GrapherApp.Documents.Add(grfPlotDoc)

'Assigns the Documents collection to the variable named "Docs"
Set Docs = GrapherApp.Documents

'Open the worksheet
Set Wks = Docs.Open("D:\Project Visual Studio\Ñoaxial Ñylinders v_0.5\Ñoaxial Ñylinders v_0.5\Flow Evolution\Flow Evolution"+Str(i)+".DAT")

'Read the contents of a cell for text
Text1 = Wks.Cells("A1")
Text2 = Wks.Cells("B1")

'Create a new graph with a single line plot
Set Graph = Plot.Shapes.AddLinePlotGraph("D:\Project Visual Studio\Ñoaxial Ñylinders v_0.5\Ñoaxial Ñylinders v_0.5\Documents\BLN\BLN_field_R1.bln")
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
Set Obst = Graph.AddLinePlot("D:\Project Visual Studio\Ñoaxial Ñylinders v_0.5\Ñoaxial Ñylinders v_0.5\Documents\BLN\BLN_obstacle.bln")

'Set the line plot to the variable named "LinePlot"
Set Obst = Graph.Plots.Item(2)
Obst.line.foreColor  = grfColorBlack
Obst.line.width = 0.03
Obst.Fill.SetPattern("Solid")
Obst.Fill.foreColor = grfColorBlack30
Obst.Fill.ForeOpacity = 100

Dim st1 As String
Set Evo = Graph.AddLinePlot("D:\Project Visual Studio\Ñoaxial Ñylinders v_0.5\Ñoaxial Ñylinders v_0.5\Flow Evolution\Flow Evolution"+Str(i)+".DAT")
Evo.line.foreColor  = grfColorBlue
Evo.line.width = 0.03

Plot.Export("D:\Project Visual Studio\Ñoaxial Ñylinders v_0.5\Ñoaxial Ñylinders v_0.5\Documents\GIF\"+Str(i)+".jpg")

	i= i + 5
Wend


End Sub
