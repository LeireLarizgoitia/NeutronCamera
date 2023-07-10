#include <iostream>

#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"

#include "Geometry.hh"
#include "Physics.hh"
#include "InitializeAction.hh"

#include "G4PhysListFactory.hh"
#include "G4ParticleHPManager.hh"

#undef G4MULTITHREADED

int main(int argc, char** argv)
{

    // Detect interactive mode (if no arguments) and define UI session
    G4UIExecutive* ui = nullptr;
    if ( argc == 1 ) { ui = new G4UIExecutive(argc, argv); }

    #ifdef G4MULTITHREADED
    G4MTRunManager * runManager = new G4MTRunManager;
    //G4cout << " Number of cores: " << G4Threading::G4GetNumberOfCores() << G4endl;
    // runManager->SetNumberOfThreads(G4Threading::G4GetNumberOfCores());
    #else
    G4RunManager * runManager = new G4RunManager;
    #endif

    runManager->SetUserInitialization(new NCamera::Construction());
    //runManager->SetUserInitialization(new NCamera::ConstructionCsI());
    runManager->SetUserInitialization(new NCamera::PhysicsList());
    //runManager->SetUserInitialization(G4PhysListFactory().GetReferencePhysList("QGSP_BIC_HP"));
    //PhysicsList* phys = new PhysicsList;
    //runManager->SetUserInitialization(phys);
    runManager->SetUserInitialization(new NCamera::InitializeAction());

  // Replaced HP environmental variables with C++ calls
    G4ParticleHPManager::GetInstance()->SetSkipMissingIsotopes( false );
    G4ParticleHPManager::GetInstance()->SetDoNotAdjustFinalState( true );
    G4ParticleHPManager::GetInstance()->SetUseOnlyPhotoEvaporation( true );
    G4ParticleHPManager::GetInstance()->SetNeglectDoppler( true ); //true
    G4ParticleHPManager::GetInstance()->SetProduceFissionFragments( false );
    G4ParticleHPManager::GetInstance()->SetUseWendtFissionModel( false );
    G4ParticleHPManager::GetInstance()->SetUseNRESP71Model( false ); //false



    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();

    G4UImanager *UImanager = G4UImanager::GetUIpointer();

    // Process macro or start UI session
    //
    G4String command;
    G4String fileName;
    if ( argc <=  2){
        //UImanager->ApplyCommand("/control/execute basic_setup.mac");

        if ( ! ui ) {
            // batch mode
            command = "/control/execute ";
            fileName = argv[1];
            UImanager->ApplyCommand(command+fileName);
         }
        else {
            // interactive mode
            UImanager->ApplyCommand("/control/execute init_vis.mac");
            ui->SessionStart();
            delete ui;
        }
    }
    else{
        command = "/control/execute ";
        fileName = argv[1];
        UImanager->ApplyCommand(command+fileName);

            // batch mode
        command = "/control/execute ";
        fileName = argv[2];
        UImanager->ApplyCommand(command+fileName);

    }

    delete visManager;
    delete runManager;
}
