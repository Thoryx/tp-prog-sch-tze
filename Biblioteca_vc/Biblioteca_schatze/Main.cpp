// Incluimos las librer�as necesarias
#include <wx/wx.h>
#include "Loguin_GUI.h" // Archivo de encabezado generado por wxFormBuilder
#include <thread>
using namespace std;

// Definimos una nueva clase que hereda de wxApp para nuestra aplicaci�n
class MyApp : public wxApp {
public:
	virtual bool OnInit() {
		//se crea puntero de tipo frame al loguin
		wxFrame *frame = new Login_GUI(nullptr);
		//se muestra el frame apuntado
		frame->Show(true);
		
		
		return true;
	}
};

// Punto de entrada de la aplicaci�n
wxIMPLEMENT_APP(MyApp);
