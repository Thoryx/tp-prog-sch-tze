#ifndef BUSQUEDA_H  // Inclusión segura del archivo de cabecera
#define BUSQUEDA_H

#include <wx/wx.h>
#include <vector>
#include <string>
#include "Books.h"

// Clase que maneja la ventana de búsqueda de libros
class Busqueda : public wxFrame {
public:
    // Constructor de la clase Busqueda
    // title: Título de la ventana
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

    // *** Controles de la interfaz gráfica ***

    wxTextCtrl* searchCtrl;     // Control de texto para introducir el término de búsqueda
    wxChoice* filterChoice;     // Control de selección para escoger el filtro (título, autor, género, año)
    wxListBox* resultList;      // Lista donde se mostrarán los resultados de la búsqueda
    wxButton* searchButton;     // Botón para iniciar la búsqueda
    wxButton* addfav;           // Botón para agregar libros a favoritos
    wxButton* verfav;           // Botón para ver la lista de favoritos
    wxButton* exitButton;       // Botón para salir y volver al menú principal
    wxStaticText* statusText;   // Texto para mostrar mensajes de estado o errores

    // *** Métodos ***

    // Método para manejar el evento de búsqueda de libros
    void OnSearch(wxCommandEvent& event);

    // Método para manejar el evento de cierre de la ventana (volver al menú principal)
    void OnExit(wxCommandEvent& event);

    // Función auxiliar para cargar libros desde un archivo binario
    std::vector<Book> LoadBooks();

    // Mostrar los libros cargados en la lista de resultados
    void DisplayBooks(const std::vector<Book>& booksToDisplay);

    // Método para agregar un libro seleccionado a la lista de favoritos
    void OnAddToFavorites(wxCommandEvent& event);

    // Guardar la lista de libros favoritos en un archivo binario
    void SaveFavorites(const std::vector<Book>& favorites, const wxString& username);

    // Cargar la lista de favoritos desde el archivo binario
    std::vector<Book> LoadFavorites(const wxString& username);

    // Método para manejar el evento de visualización de favoritos
    void verFavs(wxCommandEvent& event);

    // Declaración de la tabla de eventos de la clase (para vincular los eventos a métodos)
    wxDECLARE_EVENT_TABLE();
};

#endif // BUSQUEDA_H
