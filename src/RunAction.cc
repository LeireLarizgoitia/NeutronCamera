#include "RunAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"

namespace NCamera
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
{
  // set printing event number per each event
  //G4RunManager::GetRunManager()->SetPrintProgress(10000);

  // Create analysis manager
  // The choice of the output format is done via the specified
  // file extension.
  auto analysisManager = G4AnalysisManager::Instance();

  // Create directories
  //analysisManager->SetHistoDirectoryName("histograms");
  //analysisManager->SetNtupleDirectoryName("ntuple");
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetNtupleMerging(true);
  // Note: merging ntuples is available only with Root output

  // Creating ntuple
  //G4cout << "Creating data from the step in Ntuple" << G4endl;

  analysisManager->CreateNtuple("Plane1", "Hits Info");
  analysisManager->CreateNtupleIColumn("Event");
  analysisManager->CreateNtupleIColumn("Track");
  analysisManager->CreateNtupleIColumn("Parent");
  analysisManager->CreateNtupleSColumn("ParticleName");
  analysisManager->CreateNtupleDColumn("Energy");
  analysisManager->CreateNtupleDColumn("FinalTime");
  analysisManager->CreateNtupleDColumn("ProperTime");
  analysisManager->CreateNtupleSColumn("InitVolume");
  analysisManager->CreateNtupleSColumn("FinalVolume");
  analysisManager->CreateNtupleSColumn("CreatorProcess");
  analysisManager->CreateNtupleDColumn("xi");
  analysisManager->CreateNtupleDColumn("yi");
  analysisManager->CreateNtupleDColumn("zi");
  analysisManager->CreateNtupleDColumn("ti");
  analysisManager->CreateNtupleDColumn("xf");
  analysisManager->CreateNtupleDColumn("yf");
  analysisManager->CreateNtupleDColumn("zf");
  analysisManager->FinishNtuple();


  analysisManager->CreateNtuple("Plane2", "Hits Info");
  analysisManager->CreateNtupleIColumn("Event");
  analysisManager->CreateNtupleIColumn("Track");
  analysisManager->CreateNtupleIColumn("Parent");
  analysisManager->CreateNtupleSColumn("ParticleName");
  analysisManager->CreateNtupleDColumn("Energy");
  analysisManager->CreateNtupleDColumn("FinalTime");
  analysisManager->CreateNtupleDColumn("ProperTime");
  analysisManager->CreateNtupleSColumn("InitVolume");
  analysisManager->CreateNtupleSColumn("FinalVolume");
  analysisManager->CreateNtupleSColumn("CreatorProcess");
  analysisManager->CreateNtupleDColumn("xi");
  analysisManager->CreateNtupleDColumn("yi");
  analysisManager->CreateNtupleDColumn("zi");
  analysisManager->CreateNtupleDColumn("ti");
  analysisManager->CreateNtupleDColumn("xf");
  analysisManager->CreateNtupleDColumn("yf");
  analysisManager->CreateNtupleDColumn("zf");

  analysisManager->FinishNtuple();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run*)
{
  //inform the runManager to save random number seed
  //G4RunManager::GetRunManager()->SetRandomNumberStore(true);

  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->OpenFile();
  analysisManager->SetNtupleMerging(true);

  // Open an output file
  G4String fileName = "NCamera_d40_l20_E1_[88.1678,285.317,28.6475]1e9NOCOUT.root";
  analysisManager->OpenFile(fileName);

  //G4cout << "Using " << analysisManager->GetType() << G4endl;
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* )
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
