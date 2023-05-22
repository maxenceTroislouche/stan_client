#include <App.h>
#include <MainFrame.h>
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool App::OnInit() {
    MainFrame* mainFrame = new MainFrame();
    mainFrame->SetClientSize(1920, 1080);
    mainFrame->Center();
    mainFrame->Show();
    return true;
}