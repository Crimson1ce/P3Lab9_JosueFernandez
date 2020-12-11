/* 
 * File:   csv.h
 * Author: Josue_Fernandez
 */

#ifndef CSV_H
#define CSV_H

#include <string>
using std::string;

#include <vector>
using std::vector;

class csv {
public:
    /* Crear un objeto csv. */
    csv();
    
    /* Crea un objeto csv y carga la información del 
     * archivo con nombre file_name, se asume que el 
     * archivo viene sin encabezados. */
    csv(string file_name);
    
    /* Crea un objeto csv y carga la información del 
     * archivo con nombre file_name; si headers es 
     * true, se toma la primera línea del archivo como 
     * los encabezados. */
    csv(string file_name, bool headers);
    
    /* Constructor de copia para csv */
    csv(const csv& orig);
    
    /* Destructor */
    virtual ~csv();
    
    /* Carga los datos, headers indica si hay encabezados o no. */
    void load_file(bool headers);
    
    /* Imprime los datos en forma de tabla con sus encabezados (si los hay). */
    void print_data();
    
    /* Getter de file_name */
    string get_file_name();
    
    /* Setter de file_name */
    void set_file_name(string file_name);
    
    /* Getter de headers */
    vector<string> get_headers();
    
    /* Getter de data */
    vector<vector<string>> get_data();
    
    /* Getter de data_count */
    int get_data_count();
    
    /* Getter de has_headers */
    bool get_has_headers();
    
private:
    /* Nombre del archivo físico que contiene los datos. */
    string file_name;
    
    /* Si tiene encabezados */
    bool has_headers;
    
    /* Encabezados de los datos del archivo. */
    vector<string> headers;
    
    /* Datos del archivo. */
    vector<vector<string>> data;
    
    /* Numero de registros en el archivo, 
     * debe actualizarlo cuando sea necesario. */
    int data_count;
};

#endif /* CSV_H */

