# IFJ PAN Particle Physics Summer Student Programme
## Project: Search for critical signatures of strongly interacting matter in heavy ion collisions in SHINE @CERN SPS
### Supervisor: dr Nikolaos Davis
### Students: Elena Papadimitriou, Georgios Alexandris

To be able to run this code you need the following indide the project directory:
- A directory named ```plots```
- A directory named ```EventTrees``` with ```ArSc150``` data split as one ```.root``` file per run
- ```ArSc150-acc-map.root```
- ```OutData_ArScCharged150T2_cb34noDeuterons.root```



To run the analysis, first you need to run ```make``` under all subfolders of ```Tools``` and ```BetheBloch```.

Now you can run:
```
make all
make runE
make runF
make mTTD_cut
make factorial_moment # Takes much time
make mixEvents
./factorial_moment.exe mix_config.inp mixEvents.root accepted.root # Takes a very long time
make plot   