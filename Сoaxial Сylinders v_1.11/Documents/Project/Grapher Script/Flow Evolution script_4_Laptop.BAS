Sub Main

'Declares Objects
Dim GrapherApp, Plot, Graph_1, Graph_2, LinePlot, LinePlot2 As Object

'Create an instance of Grapher named "GrapherApp"
Set GrapherApp = CreateObject("Grapher.Application")

'Make Grapher visible
GrapherApp.Visible = False

Dim i As Integer
i = 1

'Create a new plot document named "Plot"
Set Plot = GrapherApp.Documents.Add(grfPlotDoc)

'Assigns the Documents collection to the variable named "Docs"
Set Docs = GrapherApp.Documents

'Create a new graph with a single line plot
Set Graph = Plot.Shapes.AddLinePlotGraph("C:\Program Visual Studio\Coaxial Ñylinders\Ñoaxial Ñylinders v_0.5\Ñoaxial Ñylinders v_0.5\Documents\BLN\BLN_R1.bln")
'Set Graph = Plot.Shapes.AddLinePlotGraph("D:\Project Visual Studio\Ñoaxial Ñylinders v_0.5\Ñoaxial Ñylinders v_0.5\Documents\BLN\BLN_field_R1.bln")

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

While i <= 5000

'Add a second line plot to graph and name it "LinePlot2"
Set Obst = Plot.Shapes.AddLinePlotGraph("C:\Program Visual Studio\Coaxial Ñylinders\Ñoaxial Ñylinders v_1.11\Ñoaxial Ñylinders v_1.11\Documents\Blank\Blank Flow Evolution\Blank_R0"+Str(i)+".BLN")

'Open the worksheet
Set Wks = Docs.Open("C:\Program Visual Studio\Coaxial Ñylinders\Ñoaxial Ñylinders v_1.11\Ñoaxial Ñylinders v_1.11\Documents\Figure\Re=10.000000\El = 11069\Flow Evolution\Marker Array\Flow Evolution"+Str(i)+".DAT")
'Set Wks = Docs.Open("C:\Users\Äìèòðèé\Desktop\ÒÃÓ\_Íàó÷êà\Êóðñîâûå ðàáîòû\7 êóðñ\Ìåæñåçîíüå\2023\Ðèñóíêè\Data\Ïåðåìåííàÿ ñêîðîñòü\Êîíôèãóðàöèÿ ¹1\Re=40.000000\El = 3531\Flow Evolution\Marker Array 4\Flow Evolution"+Str(i)+".DAT")

'Read the contents of a cell for text
Text1 = Wks.Cells("A1")
Text2 = Wks.Cells("B1")

Graph.title.text = Text1 + "; " + Text2

'Adjust properties of the X axis
Set XAxis1 = Obst.Axes.Item(1)
XAxis1.Visible = False
XAxis1.AutoMin = False
XAxis1.Min = -1
XAxis1.AutoMax = False
XAxis1.Max = 1

'Define object pointer
Set ObstClipping = Obst.Plots.Item(1)
'Select object
ObstClipping.Select
'Set Clipping.Continuous
ObstClipping.Clipping.Continuous = 0

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
Obst_1.line.width = 0.01
Obst_1.Fill.SetPattern("Solid")
Obst_1.Fill.foreColor = grfColorBlack30
Obst_1.Fill.ForeOpacity = 100

Set Evo_Black = Graph.AddLinePlot("C:\Program Visual Studio\Coaxial Ñylinders\Ñoaxial Ñylinders v_1.11\Ñoaxial Ñylinders v_1.11\Documents\Figure\Re=10.000000\El = 11069\Flow Evolution\Marker Array\Flow Evolution"+Str(i)+".DAT")

Evo_Black.line.foreColor  = grfColorBlue
Evo_Black.line.style = "Invisible"
Evo_Black.symbolFreq = 1
Evo_Black.symbol.Index = 12
Evo_Black.symbol.size = 0.004
Evo_Black.symbol.line.foreColor = grfColorBlack

Plot.Export2("C:\Program Visual Studio\Coaxial Ñylinders\Ñoaxial Ñylinders v_1.11\Ñoaxial Ñylinders v_1.11\Documents\Figure\Re=10.000000\El = 11069\Flow Evolution\Marker Array\GIF\"+Str(i)+".jpg",False,"ColorDepth=24;ColorReductionMethod=5;ExportImageFormatBGR24=1;HDPI=1000;Height=3477;KeepAspect=1;KeepPixelSize=0;Quality=100;Update_ColorDepth=24;Update_ColorReductionMethod=5;Update_Height=3477;Update_Width=3492;VDPI=1000;Width=3492",True,"jpg")

Evo_Black.Delete
Obst.Delete
Wks.Close

	i = i + 1

Wend

End Sub
