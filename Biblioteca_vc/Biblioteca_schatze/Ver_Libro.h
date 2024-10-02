#ifndef Ver_Libro_H
#define Ver_Libro_H

#include <wx/wx.h>
#include <vector>
#include "Books.h"

class Ver_Libro : public wxFrame {
public:
    // Constructor: Se inicializa con el título y el nombre del usuario activo
    Ver_Libro(const wxString& title, bool isAdmin, const wxString& activeUser , const int& selection);

    

private:
    // Componentes gráficos
    wxStaticText* Titulo;
    wxStaticText* Autor;
    wxStaticText* Genero;
    wxStaticText* anio;

    wxButton* backButton;

    // Atributo para determinar si el usuario es administrador
    bool userIsAdmin;
    //atributo para guardarme el usuario
    wxString ActiveUser;
    //atributo para pasar el nombre del libro a mostrar detalles
    int selection;

   void SetLabels();
    std::vector<Book> LoadBooks();
    void OnBackToMain(wxCommandEvent& evente);
    // Funciones auxiliares
  
   // Destructor: Libera los recursos utilizados
    

    wxDECLARE_EVENT_TABLE();
};









#endif