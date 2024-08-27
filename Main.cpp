// Incluimos las librerías necesarias
#include <wx/wx.h>
#include "C:\Users\engle\OneDrive\DS Itec\2do Año\Codes\TP_Final_P1\schätze\Biblioteca\Builder\noname.h" // Archivo de encabezado generado por wxFormBuilder
#include <thread>
#include "Builder/noname.h"
using namespace std;

// Definimos una nueva clase que hereda de wxApp para nuestra aplicación
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

// Punto de entrada de la aplicación
wxIMPLEMENT_APP(MyApp);
