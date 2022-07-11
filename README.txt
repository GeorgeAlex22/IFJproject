---- Description of fields in "tracks_tree" ROOT TTree for Ar+Sc collision data: ----


1. Names/ types of fields:
---------------------------------------------------------------------------------

   // event vars
   UInt_t  run_number, event_id;
   UInt_t  cBin;
   UInt_t  nTracksFit, nTracksAll;
   Float_t VertexZ;
   Float_t energySpectatorModules, energyAllPSDModules;
   
   // track vars
   Float_t bx, by;
   Float_t NPratio;
   UInt_t  clustersVTPC1, clustersVTPC2, 
           clustersGTPC,  clustersdEdx, 
           clustersPotentialAll;
   UInt_t  clustersAll;
   Float_t px, py, pz;
   Float_t dEdx;
   Float_t probElectron, probPion, probKaon, probProton, probDeuteron;

2. Short descriptions of fields:
---------------------------------------------------------------------------------


*** Event variables ***

* run_number, event_id: Serial numbers of the run to which the event belongs, and the serial number of of the event within the specific run. Together, as a "tuple", they uniquely identify a specific event

* cBin: # of centrality bin to which the event belongs (0 -> 5). These are defined based on pre-selected thresholds of the energy deposited on the Projectile Spectator Detector (PSD). Anything below lowest threshold is "0"; anything above highest threshold is "5". In between, centrality is clustered in 5% intervals:

  "1" -> 0-5%
  "2" -> 5-10%
  "3" -> 10-15%
  "4" -> 15-20%
  
  Events with centrality > 20% are not considered "safe" for the purposes of this analysis (i.e. their centrality cannot be determined accurately enough)

* nTracksFit, nTracksAll: # of tracks fitted to the Main Vertex, and total # of reconstructed tracks. Used in quality cuts (we require a certain minimum number, or percentage, of fitted tracks for accepting a Main Vertex.

* VertexZ: Vertex z-position, in cm. The z-direction corresponds to the beam direction. A cut is to be applied on the VertexZ distribution: seen as a gaussian, we want to remove the "tails" and keep the central region.

* energySpectatorModules, energyAllPSDModules: energy [in GeV] deposited to selected / all PSD modules. Used to determine centrality, and for various quality event cuts.

*** Track variables ***

* bx, by: Impact parameter (x/y components, in cm) of reconstructed track with respect to Main Vertex fitted position.

* NPratio: ratio of # of points (clusters) on the track to the # of potential points on the track. It is used for track quality cut (typically, we demand NPratio > 0)

* clustersVTPC1, clustersVTPC2, clustersGTPC,  clustersdEdx, 
  clustersPotentialAll,         clustersAll: numbers of clusters of the reconstructed track in each Vertex TPC, in the Gap TPC, and in total; number of potential clusters; number of dE/dx clusters. These numbers are used in track quality cuts.
  
* px, py, pz: x/y/z components of reconstructed track momentum (at the Main Vertex), in GeV/c (LAB frame of reference).

* dEdx: energy deposition dE/dx of reconstructed track in the TPCs, in arbitrary units. It is used for purposes of particle identification.

* probElectron, probPion, probKaon, probProton, probDeuteron: estimated probabilities for the current track of being an electron/pion/kaon/proton/deuteron. Probabilities are estimated via the Karlsruhe Fitter (KIT) software, fitting a sum of asymmetric Gaussians to the histogram of dE/dx for selected slices of total momentum, p_tot, and transverse momentum, pT. Given a track's dEdx and {p_tot, pT}, and the collection of fits (dE/dx spectra decompositions), we can obtain the estimated probabilities.
