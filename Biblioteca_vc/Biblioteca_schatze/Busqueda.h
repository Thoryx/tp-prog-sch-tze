#ifndef BUSQUEDA_H  // Inclusi�n segura del archivo de cabecera
#define BUSQUEDA_H

#include <wx/wx.h>
#include <vector>
#include <string>
#include "Books.h"

// Clase que maneja la ventana de b�squeda de libros
class Busqueda : public wxFrame {
public:
    // Constructor de la clase Busqueda
    // title: T�tulo de la ventana
    // isAdmin: Indica si el usuario es administrador
    // activeUser: Nombre del usuario activo
    Busqueda(const wxString& title, bool isAdmin, const wxString& activeUser);

private:
    // *** Atributos ***

    // Vector que contiene los libros cargados desde el archivo
    std::vector<Book> books;

    // Indicador para verificar si el usuario es administrador
    bool userIsAdmin;

    // Almacena el nombre del usuario activo
    wxString ActiveUser;

    // *** Controles de la interfaz gr�fica ***

    wxTextCtrl* searchCtrl;     // Control de texto para introducir el t�rmino de b�squeda
    wxChoice* filterChoice;     // Control de selecci�n para escoger el filtro (t�tulo, autor, g�nero, a�o)
    wxListBox* resultList;      // Lista donde se mostrar�n los resultados de la b�squeda
    wxButton* searchButton;     // Bot�n para iniciar la b�squeda
    wxButton* addfav;           // Bot�n para agregar libros a favoritos
    wxButton* verfav;           // Bot�n para ver la lista de favoritos
    wxButton* exitButton;       // Bot�n para salir y volver al men� principal
    wxStaticText* statusText;   // Texto para mostrar mensajes de estado o errores

    // *** M�todos ***

    // M�todo para manejar el evento de b�squeda de libros
    void OnSearch(wxCommandEvent& event);

    // M�todo para manejar el evento de cierre de la ventana (volver al men� principal)
    void OnExit(wxCommandEvent& event);

    // Funci�n auxiliar para cargar libros desde un archivo binario
    std::vector<Book> LoadBooks();

    // Mostrar los libros cargados en la lista de resultados
    void DisplayBooks(const std::vector<Book>& booksToDisplay);

    // M�todo para agregar un libro seleccionado a la lista de favoritos
    void OnAddToFavorites(wxCommandEvent& event);

    // Guardar la lista de libros favoritos en un archivo binario
    void SaveFavorites(const std::vector<Book>& favorites, const wxString& username);

    // Cargar la lista de favoritos desde el archivo binario
    std::vector<Book> LoadFavorites(const wxString& username);

    // M�todo para manejar el evento de visualizaci�n de favoritos
    void verFavs(wxCommandEvent& event);

    // Declaraci�n de la tabla de eventos de la clase (para vincular los eventos a m�todos)
    wxDECLARE_EVENT_TABLE();
};

#endif // BUSQUEDA_H
