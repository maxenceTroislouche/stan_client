#include <MainFrame.h>
#include <fingerprint.h>
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <stdio.h>
#include <string.h>

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(1024, 600))
{
    // Initialisation des ports GPIO
    fp_init();

    // Allumage du module
    fp_turn_on_module();

    // Démarrage de la communication série
    this->fingerprint_module_fd = fp_get_fd();

    // Module démarré :)

    printf("fd module : %d\n", this->fingerprint_module_fd);

    if (this->fingerprint_module_fd < 0)
    {
        printf("Erreur : la communication série n'a pas pu être lancée !\n");
        exit(1);
    }

    this->getConfigData();

    this->panel = new wxPanel(this);
    this->ShowFullScreen(true);
    this->displayChoiceWindow(STR(""));
}

void MainFrame::getConfigData()
{
    // Ouvre le fichier de config et extrait l'id du stan et l'adresse IP du serveur
    FILE *f = fopen("config.txt", "r");
    if (f == NULL)
    {
        printf("Le fichier de configuration n'a pas été trouvé !\n");
        exit(-1);
    }

    char id_stan_str[200];
    id_stan_str[0] = '\0';
    this->adresseIPServeur[0] = '\0';
    char c;
    int l;

    while ((c = fgetc(f)) != '\n')
    {
        l = strlen(id_stan_str);
        id_stan_str[l] = c;
        id_stan_str[l+1] = '\0';
    }

    this->id_stan = atoi(id_stan_str);    

    while((c = fgetc(f)))
    {
        if (feof(f))
            break;
        l = strlen(this->adresseIPServeur);
        this->adresseIPServeur[l] = c;
        this->adresseIPServeur[l+1] = '\0';
    }

    printf("id_stan : %d\n", this->id_stan);
    printf("ip serv : %s\n", this->adresseIPServeur);

    fclose(f);
}

void MainFrame::handleCodeWindowButtonClicked(wxCommandEvent &evt)
{
    this->destroyChoiceWindow();
    this->displayCodeWindow();
}

void MainFrame::handleFingerprintWindowButtonClicked(wxCommandEvent &evt)
{
    this->destroyChoiceWindow();
    this->displayFingerprintWindow();
}

void MainFrame::handleFingerprintWindowGoBackButtonClicked(wxCommandEvent &evt)
{
    this->destroyFingerprintWindow();
    this->displayChoiceWindow(STR(""));
}

void MainFrame::handleCodeWindowGoBackButtonClicked(wxCommandEvent &evt)
{
    this->destroyCodeWindow();
    this->displayChoiceWindow(STR(""));
}

void MainFrame::handleCodeWindowConnectButtonClicked(wxCommandEvent &evt)
{
    // TODO : Lancer la connexion par code 
}

void MainFrame::handleConnectedWindowDisconnectButtonClicked(wxCommandEvent &evt)
{
    // TODO : Gérer la déconnexion
    this->destroyConnectedWindow();
    this->displayChoiceWindow(STR("Déconnecté"));
}

void MainFrame::handleQuitButtonClicked(wxCommandEvent &evt)
{
    // Ferme la communication série
    fp_close_fd(this->fingerprint_module_fd);
    exit(0);
}

void MainFrame::addCharToCode(char car, char *code)
{
    if (code == NULL)
    {
        return;
    }

    int longueurCode = strlen(code);
    
    if (longueurCode == 4)
    {
        return; // Code au max
    }

    code[longueurCode] = car;
    code[longueurCode + 1] = '\0';
}

void MainFrame::removeCharFromCode(char *code)
{
    if (code == NULL)
    {
        return;
    }
    int longueurCode = strlen(code);
    if (longueurCode > 0)
    {
        code[longueurCode - 1] = '\0';
    }
}

void MainFrame::removeAllCharFromCode(char *code)
{
    if (code == NULL)
    {
        return;
    }

    code[0] = '\0';
}

void MainFrame::handleCodeUserIDButton0Clicked(wxCommandEvent &evt)
{
    addCharToCode('0', this->codeWindowWidgets.enteredUserID);
    updateDisplayedCode(true);
}

void MainFrame::handleCodeUserIDButton1Clicked(wxCommandEvent &evt)
{
    addCharToCode('1', this->codeWindowWidgets.enteredUserID);
    updateDisplayedCode(true);
}
void MainFrame::handleCodeUserIDButton2Clicked(wxCommandEvent &evt)
{
    addCharToCode('2', this->codeWindowWidgets.enteredUserID);
    updateDisplayedCode(true);
}
void MainFrame::handleCodeUserIDButton3Clicked(wxCommandEvent &evt)
{
    addCharToCode('3', this->codeWindowWidgets.enteredUserID);
    updateDisplayedCode(true);
}
void MainFrame::handleCodeUserIDButton4Clicked(wxCommandEvent &evt)
{
    addCharToCode('4', this->codeWindowWidgets.enteredUserID);
    updateDisplayedCode(true);
}
void MainFrame::handleCodeUserIDButton5Clicked(wxCommandEvent &evt)
{
    addCharToCode('5', this->codeWindowWidgets.enteredUserID);
    updateDisplayedCode(true);
}

void MainFrame::handleCodeUserIDButton6Clicked(wxCommandEvent &evt)
{
    addCharToCode('6', this->codeWindowWidgets.enteredUserID);
    updateDisplayedCode(true);
}
void MainFrame::handleCodeUserIDButton7Clicked(wxCommandEvent &evt)
{
    addCharToCode('7', this->codeWindowWidgets.enteredUserID);
    updateDisplayedCode(true);
}
void MainFrame::handleCodeUserIDButton8Clicked(wxCommandEvent &evt)
{
    addCharToCode('8', this->codeWindowWidgets.enteredUserID);
    updateDisplayedCode(true);
}
void MainFrame::handleCodeUserIDButton9Clicked(wxCommandEvent &evt)
{
    addCharToCode('9', this->codeWindowWidgets.enteredUserID);
    updateDisplayedCode(true);
}
void MainFrame::handleCodeUserIDButtonBackspaceClicked(wxCommandEvent &evt)
{
    removeCharFromCode(this->codeWindowWidgets.enteredUserID);
    updateDisplayedCode(true);
}
void MainFrame::handleCodeUserIDButtonClearClicked(wxCommandEvent &evt)
{
    removeAllCharFromCode(this->codeWindowWidgets.enteredUserID);
    updateDisplayedCode(true);
}

void MainFrame::handleCodePasscodeButton0Clicked(wxCommandEvent &evt)
{
    addCharToCode('0', this->codeWindowWidgets.enteredPasscode);
    updateDisplayedCode(false);
}
void MainFrame::handleCodePasscodeButton1Clicked(wxCommandEvent &evt)
{
    addCharToCode('1', this->codeWindowWidgets.enteredPasscode);
    updateDisplayedCode(false);
}
void MainFrame::handleCodePasscodeButton2Clicked(wxCommandEvent &evt)
{
    addCharToCode('2', this->codeWindowWidgets.enteredPasscode);
    updateDisplayedCode(false);
}
void MainFrame::handleCodePasscodeButton3Clicked(wxCommandEvent &evt)
{
    addCharToCode('3', this->codeWindowWidgets.enteredPasscode);
    updateDisplayedCode(false);   
}
void MainFrame::handleCodePasscodeButton4Clicked(wxCommandEvent &evt)
{
    addCharToCode('4', this->codeWindowWidgets.enteredPasscode);
    updateDisplayedCode(false);
}
void MainFrame::handleCodePasscodeButton5Clicked(wxCommandEvent &evt)
{
    addCharToCode('5', this->codeWindowWidgets.enteredPasscode);
    updateDisplayedCode(false);
}
void MainFrame::handleCodePasscodeButton6Clicked(wxCommandEvent &evt)
{
    addCharToCode('6', this->codeWindowWidgets.enteredPasscode);
    updateDisplayedCode(false);
}
void MainFrame::handleCodePasscodeButton7Clicked(wxCommandEvent &evt)
{
    addCharToCode('7', this->codeWindowWidgets.enteredPasscode);
    updateDisplayedCode(false);
}
void MainFrame::handleCodePasscodeButton8Clicked(wxCommandEvent &evt)
{
    addCharToCode('8', this->codeWindowWidgets.enteredPasscode);
    updateDisplayedCode(false);
}
void MainFrame::handleCodePasscodeButton9Clicked(wxCommandEvent &evt)
{
    addCharToCode('9', this->codeWindowWidgets.enteredPasscode);
    updateDisplayedCode(false);
}
void MainFrame::handleCodePasscodeButtonBackspaceClicked(wxCommandEvent &evt)
{
    removeCharFromCode(this->codeWindowWidgets.enteredPasscode);
    updateDisplayedCode(false);
}
void MainFrame::handleCodePasscodeButtonClearClicked(wxCommandEvent &evt)
{
    removeAllCharFromCode(this->codeWindowWidgets.enteredPasscode);
    updateDisplayedCode(false);
}

void MainFrame::updateDisplayedCode(bool userID)
{
    if (userID)
    {
        this->codeWindowWidgets.userIDEntered->Destroy();
        this->codeWindowWidgets.userIDEntered = new wxStaticText(this->panel, wxID_ANY, STR(this->codeWindowWidgets.enteredUserID), wxPoint(110, 170), wxSize(200, 50), wxALIGN_CENTER);
    }
    else
    {
        this->codeWindowWidgets.passcodeEntered->Destroy();
        this->codeWindowWidgets.passcodeEntered = new wxStaticText(this->panel, wxID_ANY, STR(this->codeWindowWidgets.enteredPasscode), wxPoint(710, 170), wxSize(200, 50), wxALIGN_CENTER);
    }
}

void MainFrame::displayChoiceWindow(wxString message)
{
    this->choiceWindowWidgets.mainTitle = new wxStaticText(this->panel, wxID_ANY, STR("Connexion à Stan"), wxPoint(410, 20), wxSize(200, 50), wxALIGN_CENTER);
    this->choiceWindowWidgets.fingerprintChoiceButton = new wxButton(this->panel, wxID_ANY, STR("Connexion par empreinte digitale"), wxPoint(70, 290), wxSize(360, 120));
    this->choiceWindowWidgets.codeChoiceButton = new wxButton(this->panel, wxID_ANY, STR("Connexion par code"), wxPoint(590, 290), wxSize(360, 120));
    this->choiceWindowWidgets.quitButton = new wxButton(this->panel, wxID_ANY, STR("Quitter l'application"), wxPoint(70, 420), wxSize(880, 120));

    this->choiceWindowWidgets.messageText = new wxStaticText(this->panel, wxID_ANY, message, wxPoint(410, 200), wxSize(200, 50), wxALIGN_CENTER);

    this->choiceWindowWidgets.codeChoiceButton->Bind(wxEVT_BUTTON, &MainFrame::handleCodeWindowButtonClicked, this);
    this->choiceWindowWidgets.fingerprintChoiceButton->Bind(wxEVT_BUTTON, &MainFrame::handleFingerprintWindowButtonClicked, this);
    this->choiceWindowWidgets.quitButton->Bind(wxEVT_BUTTON, &MainFrame::handleQuitButtonClicked, this);
}

void MainFrame::destroyChoiceWindow()
{
    this->choiceWindowWidgets.mainTitle->Destroy();
    this->choiceWindowWidgets.fingerprintChoiceButton->Destroy();
    this->choiceWindowWidgets.codeChoiceButton->Destroy();
    this->choiceWindowWidgets.quitButton->Destroy();
    this->choiceWindowWidgets.messageText->Destroy();
}

void MainFrame::displayCodeWindow()
{
    this->codeWindowWidgets.mainTitle = new wxStaticText(this->panel, wxID_ANY, STR("Connexion à Stan par code"), wxPoint(410, 20), wxSize(200, 50), wxALIGN_CENTER);

    this->codeWindowWidgets.userIDIndicator = new wxStaticText(this->panel, wxID_ANY, STR("Identifiant"), wxPoint(110, 120), wxSize(200, 50), wxALIGN_CENTER);
    this->codeWindowWidgets.userIDEntered = new wxStaticText(this->panel, wxID_ANY, STR(""), wxPoint(110, 170), wxSize(200, 50), wxALIGN_CENTER);
    this->codeWindowWidgets.userIDButtons.button1 = new wxButton(this->panel, wxID_ANY, STR("1"), wxPoint(120, 220), wxSize(50, 50));
    this->codeWindowWidgets.userIDButtons.button2 = new wxButton(this->panel, wxID_ANY, STR("2"), wxPoint(185, 220), wxSize(50, 50));
    this->codeWindowWidgets.userIDButtons.button3 = new wxButton(this->panel, wxID_ANY, STR("3"), wxPoint(250, 220), wxSize(50, 50));
    this->codeWindowWidgets.userIDButtons.button4 = new wxButton(this->panel, wxID_ANY, STR("4"), wxPoint(120, 280), wxSize(50, 50));
    this->codeWindowWidgets.userIDButtons.button5 = new wxButton(this->panel, wxID_ANY, STR("5"), wxPoint(185, 280), wxSize(50, 50));
    this->codeWindowWidgets.userIDButtons.button6 = new wxButton(this->panel, wxID_ANY, STR("6"), wxPoint(250, 280), wxSize(50, 50));
    this->codeWindowWidgets.userIDButtons.button7 = new wxButton(this->panel, wxID_ANY, STR("7"), wxPoint(120, 340), wxSize(50, 50));
    this->codeWindowWidgets.userIDButtons.button8 = new wxButton(this->panel, wxID_ANY, STR("8"), wxPoint(185, 340), wxSize(50, 50));
    this->codeWindowWidgets.userIDButtons.button9 = new wxButton(this->panel, wxID_ANY, STR("9"), wxPoint(250, 340), wxSize(50, 50));
    this->codeWindowWidgets.userIDButtons.buttonClear = new wxButton(this->panel, wxID_ANY, STR("C"), wxPoint(120, 400), wxSize(50, 50));
    this->codeWindowWidgets.userIDButtons.button0 = new wxButton(this->panel, wxID_ANY, STR("0"), wxPoint(185, 400), wxSize(50, 50));
    this->codeWindowWidgets.userIDButtons.buttonBackspace = new wxButton(this->panel, wxID_ANY, STR("<-"), wxPoint(250, 400), wxSize(50, 50));

    this->codeWindowWidgets.passcodeIndicator = new wxStaticText(this->panel, wxID_ANY, STR("Code"), wxPoint(710, 120), wxSize(200, 50), wxALIGN_CENTER);
    this->codeWindowWidgets.passcodeEntered = new wxStaticText(this->panel, wxID_ANY, STR(""), wxPoint(710, 170), wxSize(200, 50), wxALIGN_CENTER);
    this->codeWindowWidgets.passcodeButtons.button1 = new wxButton(this->panel, wxID_ANY, STR("1"), wxPoint(720, 220), wxSize(50, 50));
    this->codeWindowWidgets.passcodeButtons.button2 = new wxButton(this->panel, wxID_ANY, STR("2"), wxPoint(785, 220), wxSize(50, 50));
    this->codeWindowWidgets.passcodeButtons.button3 = new wxButton(this->panel, wxID_ANY, STR("3"), wxPoint(850, 220), wxSize(50, 50));
    this->codeWindowWidgets.passcodeButtons.button4 = new wxButton(this->panel, wxID_ANY, STR("4"), wxPoint(720, 280), wxSize(50, 50));
    this->codeWindowWidgets.passcodeButtons.button5 = new wxButton(this->panel, wxID_ANY, STR("5"), wxPoint(785, 280), wxSize(50, 50));
    this->codeWindowWidgets.passcodeButtons.button6 = new wxButton(this->panel, wxID_ANY, STR("6"), wxPoint(850, 280), wxSize(50, 50));
    this->codeWindowWidgets.passcodeButtons.button7 = new wxButton(this->panel, wxID_ANY, STR("7"), wxPoint(720, 340), wxSize(50, 50));
    this->codeWindowWidgets.passcodeButtons.button8 = new wxButton(this->panel, wxID_ANY, STR("8"), wxPoint(785, 340), wxSize(50, 50));
    this->codeWindowWidgets.passcodeButtons.button9 = new wxButton(this->panel, wxID_ANY, STR("9"), wxPoint(850, 340), wxSize(50, 50));
    this->codeWindowWidgets.passcodeButtons.buttonClear = new wxButton(this->panel, wxID_ANY, STR("C"), wxPoint(720, 400), wxSize(50, 50));
    this->codeWindowWidgets.passcodeButtons.button0 = new wxButton(this->panel, wxID_ANY, STR("0"), wxPoint(785, 400), wxSize(50, 50));
    this->codeWindowWidgets.passcodeButtons.buttonBackspace = new wxButton(this->panel, wxID_ANY, STR("<-"), wxPoint(850, 400), wxSize(50, 50));

    this->codeWindowWidgets.connectButton = new wxButton(this->panel, wxID_ANY, STR("Se connecter"), wxPoint(410, 450), wxSize(200, 50));
    this->codeWindowWidgets.connectButton->Bind(wxEVT_BUTTON, &MainFrame::handleCodeWindowConnectButtonClicked, this);
    this->codeWindowWidgets.goBackButton = new wxButton(this->panel, wxID_ANY, STR("Revenir à la page precedente"), wxPoint(410, 510), wxSize(200, 50));
    this->codeWindowWidgets.goBackButton->Bind(wxEVT_BUTTON, &MainFrame::handleCodeWindowGoBackButtonClicked, this);

    this->codeWindowWidgets.userIDButtons.button0->Bind(wxEVT_BUTTON, &MainFrame::handleCodeUserIDButton0Clicked, this);
    this->codeWindowWidgets.userIDButtons.button1->Bind(wxEVT_BUTTON, &MainFrame::handleCodeUserIDButton1Clicked, this);
    this->codeWindowWidgets.userIDButtons.button2->Bind(wxEVT_BUTTON, &MainFrame::handleCodeUserIDButton2Clicked, this);
    this->codeWindowWidgets.userIDButtons.button3->Bind(wxEVT_BUTTON, &MainFrame::handleCodeUserIDButton3Clicked, this);
    this->codeWindowWidgets.userIDButtons.button4->Bind(wxEVT_BUTTON, &MainFrame::handleCodeUserIDButton4Clicked, this);
    this->codeWindowWidgets.userIDButtons.button5->Bind(wxEVT_BUTTON, &MainFrame::handleCodeUserIDButton5Clicked, this);
    this->codeWindowWidgets.userIDButtons.button6->Bind(wxEVT_BUTTON, &MainFrame::handleCodeUserIDButton6Clicked, this);
    this->codeWindowWidgets.userIDButtons.button7->Bind(wxEVT_BUTTON, &MainFrame::handleCodeUserIDButton7Clicked, this);
    this->codeWindowWidgets.userIDButtons.button8->Bind(wxEVT_BUTTON, &MainFrame::handleCodeUserIDButton8Clicked, this);
    this->codeWindowWidgets.userIDButtons.button9->Bind(wxEVT_BUTTON, &MainFrame::handleCodeUserIDButton9Clicked, this);
    this->codeWindowWidgets.userIDButtons.buttonBackspace->Bind(wxEVT_BUTTON, &MainFrame::handleCodeUserIDButtonBackspaceClicked, this);
    this->codeWindowWidgets.userIDButtons.buttonClear->Bind(wxEVT_BUTTON, &MainFrame::handleCodeUserIDButtonClearClicked, this);

    this->codeWindowWidgets.passcodeButtons.button0->Bind(wxEVT_BUTTON, &MainFrame::handleCodePasscodeButton0Clicked, this);
    this->codeWindowWidgets.passcodeButtons.button1->Bind(wxEVT_BUTTON, &MainFrame::handleCodePasscodeButton1Clicked, this);
    this->codeWindowWidgets.passcodeButtons.button2->Bind(wxEVT_BUTTON, &MainFrame::handleCodePasscodeButton2Clicked, this);
    this->codeWindowWidgets.passcodeButtons.button3->Bind(wxEVT_BUTTON, &MainFrame::handleCodePasscodeButton3Clicked, this);
    this->codeWindowWidgets.passcodeButtons.button4->Bind(wxEVT_BUTTON, &MainFrame::handleCodePasscodeButton4Clicked, this);
    this->codeWindowWidgets.passcodeButtons.button5->Bind(wxEVT_BUTTON, &MainFrame::handleCodePasscodeButton5Clicked, this);
    this->codeWindowWidgets.passcodeButtons.button6->Bind(wxEVT_BUTTON, &MainFrame::handleCodePasscodeButton6Clicked, this);
    this->codeWindowWidgets.passcodeButtons.button7->Bind(wxEVT_BUTTON, &MainFrame::handleCodePasscodeButton7Clicked, this);
    this->codeWindowWidgets.passcodeButtons.button8->Bind(wxEVT_BUTTON, &MainFrame::handleCodePasscodeButton8Clicked, this);
    this->codeWindowWidgets.passcodeButtons.button9->Bind(wxEVT_BUTTON, &MainFrame::handleCodePasscodeButton9Clicked, this);
    this->codeWindowWidgets.passcodeButtons.buttonBackspace->Bind(wxEVT_BUTTON, &MainFrame::handleCodePasscodeButtonBackspaceClicked, this);
    this->codeWindowWidgets.passcodeButtons.buttonClear->Bind(wxEVT_BUTTON, &MainFrame::handleCodePasscodeButtonClearClicked, this);
}

void MainFrame::destroyCodeWindow()
{
    this->codeWindowWidgets.mainTitle->Destroy();

    this->codeWindowWidgets.userIDIndicator->Destroy();
    this->codeWindowWidgets.userIDEntered->Destroy();
    this->codeWindowWidgets.passcodeIndicator->Destroy();
    this->codeWindowWidgets.passcodeEntered->Destroy();

    this->codeWindowWidgets.userIDButtons.button1->Destroy();
    this->codeWindowWidgets.userIDButtons.button2->Destroy();
    this->codeWindowWidgets.userIDButtons.button3->Destroy();
    this->codeWindowWidgets.userIDButtons.button4->Destroy();
    this->codeWindowWidgets.userIDButtons.button5->Destroy();
    this->codeWindowWidgets.userIDButtons.button6->Destroy();
    this->codeWindowWidgets.userIDButtons.button7->Destroy();
    this->codeWindowWidgets.userIDButtons.button8->Destroy();
    this->codeWindowWidgets.userIDButtons.button9->Destroy();
    this->codeWindowWidgets.userIDButtons.buttonClear->Destroy();
    this->codeWindowWidgets.userIDButtons.button0->Destroy();
    this->codeWindowWidgets.userIDButtons.buttonBackspace->Destroy();

    this->codeWindowWidgets.passcodeButtons.button1->Destroy();
    this->codeWindowWidgets.passcodeButtons.button2->Destroy();
    this->codeWindowWidgets.passcodeButtons.button3->Destroy();
    this->codeWindowWidgets.passcodeButtons.button4->Destroy();
    this->codeWindowWidgets.passcodeButtons.button5->Destroy();
    this->codeWindowWidgets.passcodeButtons.button6->Destroy();
    this->codeWindowWidgets.passcodeButtons.button7->Destroy();
    this->codeWindowWidgets.passcodeButtons.button8->Destroy();
    this->codeWindowWidgets.passcodeButtons.button9->Destroy();
    this->codeWindowWidgets.passcodeButtons.buttonClear->Destroy();
    this->codeWindowWidgets.passcodeButtons.button0->Destroy();
    this->codeWindowWidgets.passcodeButtons.buttonBackspace->Destroy();

    this->codeWindowWidgets.connectButton->Destroy();
    this->codeWindowWidgets.goBackButton->Destroy();
}

void MainFrame::handleFingerPlaced(wxCommandEvent &evt)
{
    this->userInfo.id = fp_compare_fingerprint(this->fingerprint_module_fd);
    printf("User id: %d\n", this->userInfo.id);
    if (this->userInfo.id == -1 || this->userInfo.id == 0)
    {
        printf("Empreinte non valide !n");
        this->destroyFingerprintWindow();
        this->displayChoiceWindow(STR("Empreinte non valide"));
        return;
    }
    strcpy(this->userInfo.lastname, "test_lastname");
    strcpy(this->userInfo.firstname, "test_firstname");
    this->destroyFingerprintWindow();
    this->displayConnectedWindow();
}

void MainFrame::displayFingerprintWindow()
{
    this->fingerprintWindowWidgets.mainTitle = new wxStaticText(this->panel, wxID_ANY, STR("Connexion à Stan par empreinte"), wxPoint(410, 20), wxSize(200, 50), wxALIGN_CENTER);

    this->fingerprintWindowWidgets.instructionText = new wxStaticText(this->panel, wxID_ANY, STR("Placez votre doigt sur le capteur"), wxPoint(410, 200), wxSize(200, 50), wxALIGN_CENTER);
    this->fingerprintWindowWidgets.goBackButton = new wxButton(this->panel, wxID_ANY, STR("Revenir à la page precedente"), wxPoint(410, 400), wxSize(200, 50));
    this->fingerprintWindowWidgets.goBackButton->Bind(wxEVT_BUTTON, &MainFrame::handleFingerprintWindowGoBackButtonClicked, this);

    this->fingerprintWindowWidgets.fingerPlacedButton = new wxButton(this->panel, wxID_ANY, STR("Doigt placé"), wxPoint(410, 300), wxSize(200, 50));
    this->fingerprintWindowWidgets.fingerPlacedButton->Bind(wxEVT_BUTTON, &MainFrame::handleFingerPlaced, this);
}

void MainFrame::destroyFingerprintWindow()
{
    this->fingerprintWindowWidgets.mainTitle->Destroy();
    this->fingerprintWindowWidgets.instructionText->Destroy();
    this->fingerprintWindowWidgets.goBackButton->Destroy();
    this->fingerprintWindowWidgets.fingerPlacedButton->Destroy();
}

void MainFrame::displayConnectedWindow()
{
    this->connectedWindowWidgets.mainTitle = new wxStaticText(this->panel, wxID_ANY, STR("Connecté à Stan"), wxPoint(410, 20), wxSize(200, 50), wxALIGN_CENTER);
    this->connectedWindowWidgets.userid_indicator = new wxStaticText(this->panel, wxID_ANY, wxString::Format(wxT("%i"),this->userInfo.id), wxPoint(410, 50), wxSize(200, 50), wxALIGN_CENTER);
    this->connectedWindowWidgets.userlastname_indicator = new wxStaticText(this->panel, wxID_ANY, STR(this->userInfo.lastname), wxPoint(410, 110), wxSize(200, 50), wxALIGN_CENTER);
    this->connectedWindowWidgets.userfirstname_indicator = new wxStaticText(this->panel, wxID_ANY, STR(this->userInfo.firstname), wxPoint(410, 170), wxSize(200, 50), wxALIGN_CENTER);
    this->connectedWindowWidgets.disconnectButton = new wxButton(this->panel, wxID_ANY, STR("Se déconnecter"), wxPoint(410, 400), wxSize(200, 50));
    this->connectedWindowWidgets.disconnectButton->Bind(wxEVT_BUTTON, &MainFrame::handleConnectedWindowDisconnectButtonClicked, this);
}

void MainFrame::destroyConnectedWindow()
{
    this->connectedWindowWidgets.mainTitle->Destroy();
    this->connectedWindowWidgets.userid_indicator->Destroy();
    this->connectedWindowWidgets.userlastname_indicator->Destroy();
    this->connectedWindowWidgets.userfirstname_indicator->Destroy();
    this->connectedWindowWidgets.disconnectButton->Destroy();
}
