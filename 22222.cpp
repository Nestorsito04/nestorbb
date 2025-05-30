#include <iostream>  // Para operaciones de entrada/salida (cout, cin, endl)
#include <fstream>   // Para manejar archivos (lectura y escritura)
#include <string>    // Para trabajar con cadenas de texto (string)
#include <algorithm> // Para usar la función std::transform (cambiar a minúsculas)
#include <cctype>    // Para usar la función std::tolower (convertir caracteres a minúsculas)
#include <windows.h> // Específica para Windows: control de la consola (colores, UTF-8)

// Usamos el namespace std completo para simplificar el código
using namespace std;
// Definición de colores para la consola usando una enumeración para claridad
enum ConsoleTextColors {
    DEFAULT_CONSOLE_COLOR = 7,  // Color de texto predeterminado de la consola
    MATCH_HIGHLIGHT_COLOR = 12  // Código para el color rojo brillante
};

// Función para establecer el color del texto en la consola de Windows
void setConsoleOutputColor(int desiredColorCode) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), desiredColorCode);
}
// Función auxiliar para convertir una cadena completa a minúsculas (útil para búsquedas sin distinción de mayúsculas/minúsculas)
string convertToLowerCase(const string& originalText) {
    string lowercasedText = originalText; // Creamos una copia modificable de la cadena original
    
    // Aplicamos la función std::tolower a cada carácter de la cadena
    transform(lowercasedText.begin(), lowercasedText.end(), lowercasedText.begin(),
                   [](unsigned char c){ return tolower(c); });
    return lowercasedText; // Devolvemos la cadena convertida
}

// Función principal para procesar una línea, buscar coincidencias, resaltarlas y contarlas
void processLineAndHighlight(string& lineContent, const string& userSearchTerm, int& totalFoundOccurrences) {
    string lowerLine = convertToLowerCase(lineContent);          // La línea actual en minúsculas
    string lowerSearchTerm = convertToLowerCase(userSearchTerm); // El término de búsqueda en minúsculas
    size_t currentMatchPos = lowerLine.find(lowerSearchTerm);    // Buscamos la primera aparición del término
    size_t lineSpecificMatches = 0;                              // Contador para esta línea en particular
    
// Iteramos mientras se encuentren coincidencias en la línea
    while (currentMatchPos != string::npos) { // string::npos indica que no se encontró el término
        // Imprimimos la porción de la línea que precede a la coincidencia
        cout << lineContent.substr(0, currentMatchPos);

        // Cambiamos el color a rojo, imprimimos la coincidencia y luego restauramos el color predeterminado
        setConsoleOutputColor(MATCH_HIGHLIGHT_COLOR); // Establecemos el color rojo
        cout << lineContent.substr(currentMatchPos, userSearchTerm.length()); // Imprimimos la parte que coincide
        setConsoleOutputColor(DEFAULT_CONSOLE_COLOR); // Reestablecemos el color por defecto
        
 // Actualizamos la línea (y su versión en minúsculas) para continuar la búsqueda después de la coincidencia actual
        lineContent = lineContent.substr(currentMatchPos + userSearchTerm.length());
        lowerLine = lowerLine.substr(currentMatchPos + userSearchTerm.length());
        currentMatchPos = lowerLine.find(lowerSearchTerm); // Buscamos la siguiente ocurrencia
        lineSpecificMatches++; // Incrementamos el contador de coincidencias para esta línea
    }
    cout << lineContent << endl; // Imprimimos el resto de la línea (si queda algo sin resaltar)
    totalFoundOccurrences += lineSpecificMatches; // Agregamos las coincidencias de esta línea al total global
}

int main() {
    // Configuramos la consola para asegurar la correcta visualización y entrada de caracteres UTF-8
    SetConsoleOutputCP(65001); // Para la salida (lo que el programa imprime)
    SetConsoleCP(65001);      // Para la entrada (lo que el usuario teclea)

    string targetFileName = "archivoness.txt"; // Nombre del archivo de texto que vamos a leer
    string searchTermInput;              // Variable para guardar lo que el usuario quiere buscar
    char repeatSearchOption;             // Guarda la opción del usuario para buscar de nuevo

    // Este bucle principal permite al usuario realizar múltiples búsquedas consecutivas
    do {
        // Abrimos el archivo en cada iteración del bucle, ya que no estamos cargando todo en memoria con un vector
        ifstream inputFileStream(targetFileName);

        // Verificamos si el archivo se abrió correctamente
        if (!inputFileStream.is_open()) {
            cerr << "Error: No se pudo abrir el archivo '" << targetFileName << "'." << endl;
            return 1; // Salimos del programa con un código de error
        }
