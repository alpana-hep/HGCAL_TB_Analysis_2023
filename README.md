# HGCAL_TB_Analysis_2023

##Reco data analysis framework
### setup the mahcinery-
```
git clone -b AnalysisScripts https://github.com/alpana-hep/HGCAL_TB_Analysis_2023.git .
make
```
Scripts-
```
AnalyzeHGCOctTB.cc - source file, loop over events and fill hitograms
AnalyzeHGCOctTB.h - main class, functions where histograms are defined, read input root file
HGCNtupleVariables.cc - Pedestal map
HGCNtupleVariables.h - variables that needs to be read from input tree are in here.
```

Commands to run the script-
```
./analyzeHGCOctTB <file_list> <outputfilename> <type of run> <relay number> <energy for the particle, in case of pedestal '0'>

```

Example to run the script-
```
./analyzeHGCOctTB file_list/run_-1691505681_pedestal.txt out_reReco_Aug16 Pedestal 1691505681 0
```
shell script that loop over multiple file-
```
submit.sh
```


## Fitting the pedestal distirbutions and extarcting pedestal and noise


Script- loop over the output from analyzer script and created pedestal plots along with fit in png/pdf formats, save pedestal and noise values to the output txt file which can be later on converted to hexagonal plots
```
noiseFitter.C
```
Command to run over this-
```
root -b
.L noiseFitter.C
for_all("input_hist_file","path to save output plots","output_txt file")
```
An example-

```
root -b
.L noiseFitter.C
for_all("out_reReco_Aug16_Pedestal_1691505681.root","plots","run_pedestal_1691505681.txt")
```



## Making Hexagonal plots

Description of the scripts-

    Build a c++ shared library which contains a function to convert HGCAL (u, v) to (x, y)
    Import c++ class using PyRoot gInterpreter and gSystem
    Load geometry data
    Plot hexagons using TGraph
    Produce a geometry root file with a collection of graphs
    Make a hexagonal histogram using TH2Poly in a ROOT macro

Main scripts-
Changes related to plot description should be done in 'th2poly.C'

Commands to run the machinery
```
git clone -b v0_alps https://github.com/alpana-hep/hexagonal_histograms.git .
cd hexagonal_histograms
make && ./exe.py
```

Example to run over particular relay-
Change the relay number and other arguments upto your choice in exe.py file
```
https://github.com/alpana-hep/hexagonal_histograms/blob/v0_alps/exe.py#L292
```
Arguments to run 'th2poly.C'
```
exe("root -l -b -q th2poly.C'(\"./data/hexagons.root\","<runfile>","<calib files>","module png text","pdf name","range", bool drawLine=false, TString layer_="-1", TString runNumber="-1", "int ped_method=-1")'
```
Example to run 'th2poly.c'
```
exe("root -l -b -q th2poly.C'(\"./data/hexagons.root\", \"./run_1691487584_pedestal.txt\",\"./Calib_Files_Aug2023/level0_calib_params_run1691487584.txt\", \"Module_0_run_1691487584_noiserPerarea\", \"Module_0_run_1691487584_noiserPerarea.pdf\", 26, \"false\",\"0\",\"1691487584\",7)'")
```
