/* 
 * File:   csv.cpp
 * Author: Josue_Fernandez
 */

#include "csv.h"

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <sstream>
using std::istringstream;

#include <string>
using std::string;

#include <ios>
using std::ios;

#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

csv::csv()
: data_count(0), file_name(""), has_headers(false) {
}

csv::csv(string file_name)
: file_name(file_name), has_headers(false), data_count(0) {
    load_file(false);
}

csv::csv(string file_name, bool headers)
: file_name(file_name), has_headers(headers), data_count(0) {
    load_file(headers);
}

csv::csv(const csv& orig) {
}

csv::~csv() {
    headers.clear();
    for (int i = 0; i < data_count; i++) {
        ((vector<string>) data[i]).clear();
    }
    data.clear();
    widths.clear();
}

void csv::load_file(bool headers) {
    //Creamos el objeto para leer del archivo
    ifstream input_file;
    input_file.open(file_name);

    //Si el archivo está abierto...
    if (input_file.is_open()) {
        //Liberamos los datos actuales
        for (int i = 0; i < data_count; i++) {
            ((vector<string>) data[i]).clear();
        }
        data.clear();

        widths.clear();

        this->has_headers = headers;


        this->headers.clear();

        //Si tiene encabezados...
        if (headers == true) {

            //Leemos la primera linea del archivo
            string line;
            input_file >> line;

            //Creamos un stringstream para separar los tokens
            istringstream isstream(line);

            //Variable para almacenar los tokens
            string token;

            //Cargamos cada encabezado
            while (getline(isstream, token, ',')) {
                this->headers.push_back(token);
                widths.push_back(token.length());
            }
        }


        //String para las lineas
        string line;

        //Como leemos el archivo, iniciamos data_count en 0
        this->data_count = 0;

        //Leemos cada linea del archivo
        while (input_file >> line) {

            vector<string> registro;

            //Creamos un stringstream para separar los tokens
            istringstream isstream(line);

            //Variable para almacenar los tokens
            string token;

            //Cargamos cada valor al vector registro
            while (getline(isstream, token, ',')) {
                registro.push_back(token);
            }

            if (widths.size() == 0) {
                for (int i = 0; i < registro.size(); i++) {
                    widths.push_back(((string) registro[i]).length());
                }
            } else {
                for (int i = 0; i < widths.size(); i++) {
                    if (((string) registro[i]).length() > widths[i]) {
                        widths.erase(widths.begin() + i);
                        widths.insert(widths.begin() + i, ((string) registro[i]).length());
                    }
                }
            }


            //Añadimos el nuevo registro a la tabla
            data.push_back(registro);

            //Incrementamos el numero de registros por cada linea
            this->data_count++;
        }

    } else {
        cout << "No se encontró el archivo CSV\n";
    }
}

void csv::print_data() {
    if (has_headers) {
        for (int i = 0; i < headers.size(); i++) {
            cout << setw(widths[i] + 5) << headers[i];
        }
        cout << endl << endl;
    }

    for (int i = 0; i < data_count; i++) {
        for (int j = 0; j < ((vector<string>)data.at(0)).size(); j++) {
            cout << setw(widths[j] + 5) << data[i][j];
        }
        cout << endl;
    }
}

string csv::get_file_name() {
    return this->file_name;
}

void csv::set_file_name(string file_name) {
    this->file_name = file_name;
}

vector<string> csv::get_headers() {
    return this->headers;
}

vector<vector<string> > csv::get_data() {
    return this->data;
}

int csv::get_data_count() {
    return this->data_count;
}

bool csv::get_has_headers() {
    return this->has_headers;
}

void csv::truncate_column(int index) {
    // Validamos que haya al menos un registro, y
    // que index esté en el rango correcto
    if (data_count > 0 && index >= 0 && index < ((vector<string>)this->data.at(0)).size()) {
        int columnas = this->data.at(0).size();

        //Eliminamos el encabezado, si hay
        if (has_headers) {
            this->headers.erase(this->headers.begin() + index);
        }

        //Eliminamos el ancho para la columna
        this->widths.erase(this->widths.begin() + index);

        for (int i = 0; i < data_count; i++) {
            //Eliminamos el elemento indicado de cada fila e insertamos uno nuevo
            vector<string> row;
            for (int j = 0; j < columnas; j++) {
                if (j != index) {
                    row.push_back(((vector<string>)(((vector<vector < string>>)data).at(i))).at(j));
                }
            }
            data.erase(data.begin() + i);
            data.insert(data.begin() + i, row);
        }
    }
}

void csv::truncate_row(int index) {
    // Validamos que index esté en el rango correcto
    if (index >= 0 && index < data_count) {
        //Eliminamos la fila indicada
        this->data.erase(this->data.begin() + index);
        this->data_count--;
    }
}

void csv::write_file() {
    //Creamos el objeto para leer del archivo
    ofstream output_file;
    output_file.open(file_name, ios::out | ios::trunc);

    //Si el archivo está abierto...
    if (output_file.is_open()) {

        if (has_headers == true) {
            for (int i = 0; i < headers.size(); i++) {
                output_file << headers[i];
                if (i != headers.size() - 1) {
                    output_file << ',';
                }
            }
            output_file << '\n';

        }

        for (int i = 0; i < data_count; i++) {
            for (int j = 0; j < widths.size(); j++) {
                output_file << data[i][j];
                if (j != widths.size() - 1) {
                    output_file << ',';
                }
            }
            output_file << '\n';
        }
    }
}

vector<string> csv::get_row(int index) {
    return (vector<string>)data[index];
}

vector<string> csv::get_column(int index) {
    vector<string> column;
    for (int i = 0; i < data_count; i++) {
        column.push_back(((vector<string>)data[i]).at(index));
    }
    return column;
}

vector<string> csv::get_max(int column) {
    int position = 0;
    string max = ((vector<string>)data.at(0)).at(column);
    for (int i = 0; i < data_count - 1; i++) {
        if (max < ((vector<string>)data.at(i+1)).at(column)) {
            max = ((vector<string>)data.at(i+1)).at(column);
            position = i;
        }

    }
    return (vector<string>)data[position];
}

vector<string> csv::get_min(int column) {
    int position = 0;
    string min = ((vector<string>)data.at(0)).at(column);
    for (int i = 0; i < data_count - 1; i++) {
        if (min > ((vector<string>)data.at(i+1)).at(column)) {
            min = ((vector<string>)data.at(i+1)).at(column);
            position = i;
        }

    }
    return (vector<string>)data[position];
}

csv* csv::concat(csv* file, string filename) {

    if (((vector<string>)file->data[0]).size() != ((vector<string>)this->data[0]).size()) {
        return NULL;
    }
    bool new_header = false;
    if (this->has_headers && file->has_headers) {
        for (int i = 0; i < this->headers.size(); i++) {
            if (this->headers[i] != file->headers[i]) {
                return NULL;
            }
        }
    }
    vector<string> nHeaders;
    if (this->has_headers || file->has_headers) {
        new_header = true;
        if (this->has_headers) {
            nHeaders = this->headers;
        } else {
            nHeaders = file->headers;
        }
    }

    csv* new_file = new csv();
    new_file->file_name = filename;
    new_file->has_headers = new_header;
    if (new_header) {
        new_file->headers = nHeaders;
    }

    new_file->data_count = (this->data_count + file->data_count);

    for (int i = 0; i < this->data_count; i++) {
        new_file->data.push_back((vector<string>)this->data[i]);
    }

    for (int i = 0; i < file->data_count; i++) {
        new_file->data.push_back((vector<string>)file->data[i]);
    }

    for (int i = 0; i < widths.size(); i++) {
        new_file->widths.push_back((this->widths[i] > file->widths[i] ? this->widths[i] : file->widths[i]));
    }
    return new_file;
}

vector<vector<string>> csv::sort_data(int column, bool up) {
    
    
}
