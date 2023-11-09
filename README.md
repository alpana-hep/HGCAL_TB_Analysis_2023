# HGCAL_TB_Analysis_2023

##Reco data analysis framework

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
