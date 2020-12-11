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
    if(has_headers){
        for (int i = 0; i < headers.size(); i++) {
            cout << headers[i] << '\t';
        }
        cout << endl << endl << endl;
    }
    
    for (int i = 0; i < data_count; i++) {
        for (int j = 0; j < ((vector<string>)data.at(0)).size(); j++) {
            cout << data[i][j] << '\t';
        }
        cout << endl << endl;
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
