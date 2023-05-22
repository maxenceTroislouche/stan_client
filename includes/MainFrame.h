#pragma once
#include <wx/wx.h>

// Permet d'utiliser des chaines de caractères avec des accents dans les widgets
#define STR(s) wxString::FromUTF8(s)

typedef struct choiceWindowWidgets
{
    wxStaticText *mainTitle;
    wxButton *fingerprintChoiceButton;
    wxButton *codeChoiceButton;
    wxButton *quitButton;
    wxStaticText *messageText;
} choiceWindowWidgets_t;

typedef struct codeInputWidgets
{
    wxButton *button0;
    wxButton *button1;
    wxButton *button2;
    wxButton *button3;
    wxButton *button4;
    wxButton *button5;
    wxButton *button6;
    wxButton *button7;
    wxButton *button8;
    wxButton *button9;
    wxButton *buttonBackspace;
    wxButton *buttonClear;
} codeInputWidgets_t;

typedef struct codeWindowWidgets
{
    wxStaticText *mainTitle;
    wxStaticText *userIDIndicator;
    wxStaticText *passcodeIndicator;
    wxStaticText *userIDEntered;
    wxStaticText *passcodeEntered;
    wxButton *goBackButton;
    wxButton *connectButton;

    char enteredUserID[5];
    char enteredPasscode[5];

    codeInputWidgets_t userIDButtons;
    codeInputWidgets_t passcodeButtons;
} codeWindowWidgets_t;

typedef struct fingerprintWindowWidgets
{
    wxStaticText *mainTitle;
    wxStaticText *instructionText;
    wxButton *fingerPlacedButton;
    wxButton *goBackButton;
} fingerprintWindowWidgets_t;

typedef struct connectedWindowWidgets
{
    wxStaticText *mainTitle;
    wxStaticText *userid_indicator;
    wxStaticText *userlastname_indicator;
    wxStaticText *userfirstname_indicator;
    wxButton *disconnectButton;
} connectedWindowWidgets_t;

typedef struct userInfo
{
    int id;
    char lastname[200];
    char firstname[200];
    bool isadmin;
    char passcode[5];
    char fingerprintEigenvalue[200];
} userInfo_t;

typedef void * (*THREADFUNCPTR)(void *);

class MainFrame : public wxFrame
{
private:
    int fingerprint_module_fd;
    int id_stan;
    char adresseIPServeur[16];
    wxPanel *panel;
    choiceWindowWidgets_t choiceWindowWidgets;
    codeWindowWidgets_t codeWindowWidgets;
    fingerprintWindowWidgets_t fingerprintWindowWidgets;
    connectedWindowWidgets_t connectedWindowWidgets;
    userInfo_t userInfo;

    void addCharToCode(char car, char *code);
    void removeCharFromCode(char *code);
    void removeAllCharFromCode(char *code);
    void updateDisplayedCode(bool userID);
public:
    MainFrame();
    void getConfigData();
    void *compare_fingerprint();

    void handleCodeWindowButtonClicked(wxCommandEvent &evt);
    void handleFingerprintWindowButtonClicked(wxCommandEvent &evt);

    void handleFingerprintWindowGoBackButtonClicked(wxCommandEvent &evt);

    void handleCodeWindowGoBackButtonClicked(wxCommandEvent &evt);
    void handleCodeWindowConnectButtonClicked(wxCommandEvent &evt);

    void handleConnectedWindowDisconnectButtonClicked(wxCommandEvent &evt);

    void handleQuitButtonClicked(wxCommandEvent &evt);

    void displayChoiceWindow(wxString message);
    void destroyChoiceWindow();
    void displayCodeWindow();
    void destroyCodeWindow();
    void displayFingerprintWindow();
    void destroyFingerprintWindow();
    void displayConnectedWindow();
    void destroyConnectedWindow();

    void handleCodeUserIDButton0Clicked(wxCommandEvent &evt);
    void handleCodeUserIDButton1Clicked(wxCommandEvent &evt);
    void handleCodeUserIDButton2Clicked(wxCommandEvent &evt);
    void handleCodeUserIDButton3Clicked(wxCommandEvent &evt);
    void handleCodeUserIDButton4Clicked(wxCommandEvent &evt);
    void handleCodeUserIDButton5Clicked(wxCommandEvent &evt);
    void handleCodeUserIDButton6Clicked(wxCommandEvent &evt);
    void handleCodeUserIDButton7Clicked(wxCommandEvent &evt);
    void handleCodeUserIDButton8Clicked(wxCommandEvent &evt);
    void handleCodeUserIDButton9Clicked(wxCommandEvent &evt);
    void handleCodeUserIDButtonBackspaceClicked(wxCommandEvent &evt);
    void handleCodeUserIDButtonClearClicked(wxCommandEvent &evt);

    void handleCodePasscodeButton0Clicked(wxCommandEvent &evt);
    void handleCodePasscodeButton1Clicked(wxCommandEvent &evt);
    void handleCodePasscodeButton2Clicked(wxCommandEvent &evt);
    void handleCodePasscodeButton3Clicked(wxCommandEvent &evt);
    void handleCodePasscodeButton4Clicked(wxCommandEvent &evt);
    void handleCodePasscodeButton5Clicked(wxCommandEvent &evt);
    void handleCodePasscodeButton6Clicked(wxCommandEvent &evt);
    void handleCodePasscodeButton7Clicked(wxCommandEvent &evt);
    void handleCodePasscodeButton8Clicked(wxCommandEvent &evt);
    void handleCodePasscodeButton9Clicked(wxCommandEvent &evt);
    void handleCodePasscodeButtonBackspaceClicked(wxCommandEvent &evt);
    void handleCodePasscodeButtonClearClicked(wxCommandEvent &evt);

    void handleFingerPlaced(wxCommandEvent &evt);
};
