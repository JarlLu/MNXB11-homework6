#include "MovingObject.h"
#include <TFile.h>
#include <TTree.h>
#include <TRandom.h>
void write() {
  
// Initialize your object e.g. as a pointer
    MovingObject *object = new MovingObject();

// Create your root file here
    TFile *file = new TFile("tree_file.root","RECREATE");
// Create your TTree here
    TTree *tree = new TTree("tree","moving object tree");
// And the associated branches underneath
    tree->Branch("object","MovingObject",&object);
// for example a branch with your personal object type
// Now we create our loop for filling the tree with some random data
gRandom->SetSeed(12345);
// For loop here

for (Int_t i{0}; i<10000; i++){
    Double_t vx = gRandom->Gaus(0.0, 0.30);
    Double_t vy = gRandom->Gaus(0.0, 0.30);
    Double_t vz = gRandom->Gaus(0.0, 0.30);
    object->SetVelocity(vx,vy,vz);
    tree->Fill();

} // define how many events you want
// Initialize your new object below
// Now fill tree
// Remember to delete it again otherwise you will have memory leak!
file->cd();
tree->Write();
file->Close();
delete object;

}
// save the tree/file  
