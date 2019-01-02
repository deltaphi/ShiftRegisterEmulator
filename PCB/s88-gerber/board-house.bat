copy ArduinoS88-F.Cu.gtl      ArduinoS88.GTL
copy ArduinoS88-B.Cu.gbl      ArduinoS88.GBL
copy ArduinoS88-F.Mask.gts    ArduinoS88.GTS
copy ArduinoS88-B.Mask.gbs    ArduinoS88.GBS
copy ArduinoS88-F.SilkS.gto   ArduinoS88.GTO
copy ArduinoS88-B.SilkS.gbo   ArduinoS88.GBO
copy ArduinoS88-PTH.drl       ArduinoS88-PTH.TXT
copy ArduinoS88-NPTH.drl      ArduinoS88-NPTH.TXT
copy ArduinoS88-Edge.Cuts.gm1 ArduinoS88.GML
copy ArduinoS88-Margin.gbr    ArduinoS88.GBR

del ArduinoS88.zip

"c:\Program Files\7-Zip\7z.exe" a -- ArduinoS88.zip ArduinoS88.GTL ArduinoS88.GBL ArduinoS88.GTS ArduinoS88.GBS ArduinoS88.GTO ArduinoS88.GBO ArduinoS88-PTH.TXT ArduinoS88-NPTH.TXT ArduinoS88.GML ArduinoS88.GBR
