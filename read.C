#include "MovingObject.h"
#include <TFile.h>
#include <TTree.h>
#include <TH2D.h>
#include <TCanvas.h>
#include <iostream>
void read() {
    TFile *file = TFile::Open("tree_file.root","READ"); //opening file
    if (!file || file->IsZombie()) {
        std::cout << "File could not be opened\n";
        return;} // check if file was found properly
    TTree *tree =dynamic_cast<TTree*>(file->Get("tree")); //getting the tree
    if (tree==nullptr) {
        std::cout << "tree not found\n";
        return;} // check if tree was found   
    MovingObject *object=nullptr; //initializing movingobject
    tree->SetBranchAddress("object",&object); //setting branch address of object
    Long64_t n =tree->GetEntries(); //getting number of entries in tree
    TH2D *h1 = new TH2D("h1", "velocity Components", 100, -1.5,1.5, 100,-1.5,1.5); //creating histogram
    for (Long64_t i=0; i < n; ++i) {
        tree->GetEntry(i);
        h1->Fill(object->Vx(),object->Vy());} //filling histogram
    TCanvas velocitycompcanvas("velocitycompcanvas", "velocity components plot", 800,500);
    h1->GetXaxis()->SetTitle("v_{x} (m/s)");
    h1->GetYaxis()->SetTitle("v_{y} (m/s)");
    h1->SetTitle("Plot of v_{x} vs v_{y}");
    h1->Draw("COLZ");
    velocitycompcanvas.SaveAs("velocity_components.png");
    TCanvas selectivecanvas("selectivecanvas", "selective speed plot", 800, 500);
    tree->Draw(
    "sqrt(fVx*fVx + fVy*fVy):fVz",
    "fVx*fVx + fVy*fVy + fVz*fVz > 0.25");
    auto h2 = tree->GetHistogram();
    h2->SetTitle("Horizontal speed vs vertical velocity");
    h2->GetXaxis()->SetTitle("v_{z} (m/s)");
    h2->GetYaxis()->SetTitle("v_{xy} (m/s)");
    selectivecanvas.SaveAs("selective_plot_of_horizontal_vs_vertical_speed.png");
}