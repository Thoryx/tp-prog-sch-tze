#include <iostream>
#include <fstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

using namespace std;

struct User {
	char username[20];
	char password[8];
	bool role;  // true for admin, false for regular user
	
	User() : role(false) {}
};

bool AddUser(const std::string& filename, const std::string& newUsername, const std::string& newPassword, bool newRole) {
	std::vector<User> users;
	User newUser;
	
	// Copiar los datos del nuevo usuario en la estructura
	std::strncpy(newUser.username, newUsername.c_str(), sizeof(newUser.username) - 1);
	newUser.username[sizeof(newUser.username) - 1] = '\0';
	std::strncpy(newUser.password, newPassword.c_str(), sizeof(newUser.password) - 1);
	newUser.password[sizeof(newUser.password) - 1] = '\0';
	newUser.role = newRole;
	
	// Abrir el archivo en modo lectura para cargar los usuarios existentes
	std::ifstream infile(filename, std::ios::binary);
	if (infile) {
		User temp;
		while (infile.read(reinterpret_cast<char*>(&temp), sizeof(User))) {
			users.push_back(temp);
		}
		infile.close();
	}
	
	// Agregar el nuevo usuario a la lista
	users.push_back(newUser);
	
	// Abrir el archivo en modo escritura para guardar todos los usuarios
	std::ofstream outfile(filename, std::ios::binary | std::ios::trunc);
	if (!outfile) {
		std::cerr << "Error al abrir el archivo para escribir." << std::endl;
		return false;
	}
	
	for (const auto& user : users) {
		outfile.write(reinterpret_cast<const char*>(&user), sizeof(User));
	}
	
	outfile.close();
	return true;
}

// Función para mostrar los usuarios almacenados en el archivo
void ViewUsers(const std::string& filename) {
	std::ifstream infile(filename, std::ios::binary);
	if (!infile) {
		std::cerr << "Error al abrir el archivo para lectura." << std::endl;
		return;
	}
	
	User user;
	int index = 1;
	
	std::cout << "Usuarios almacenados en el archivo:\n";
	std::cout << "-----------------------------------\n";
	while (infile.read(reinterpret_cast<char*>(&user), sizeof(User))) {
		std::cout << "Usuario " << index++ << ":\n";
		std::cout << "  Username: " << user.username << '\n';
		std::cout << "  Password: " << user.password << '\n';
		std::cout << "  Role: " << (user.role ? "Admin" : "Regular user") << '\n';
		std::cout << "-----------------------------------\n";
	}
	
	infile.close();
}

int main() {
	std::string filename = "Credenciales.dat";
	std::string username = "adm";
	std::string password = "123";
	bool role = true;  // true para admin, false para usuario regular
	
	if (AddUser(filename, username, password, role)) {
		std::cout << "Usuario agregado con éxito." << std::endl;
	} else {
		std::cerr << "No se pudo agregar el usuario." << std::endl;
	}
	
	// Llamar a la función para ver los usuarios almacenados
	ViewUsers(filename);
	
	return 0;
}

