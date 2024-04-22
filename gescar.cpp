#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <cstdlib>

using namespace std;
#define LOG_FILE "log_file.txt"

/* Veiculo
 * --
 * Marca
 * Modelo
 * 
 */ 

struct veiculo {
    // string marca;
    // string modelo;
    string matricula;
    // numero de chaci
    // data de revisao
    // data de inspeçao
    // bool ativo;
    // data do selo + preço
    // seguro + preço
    string data_inspecao;
};

list<veiculo> frota;

void inserir (veiculo novo);
void listar ();
//void retirar ();
//int atualizar ();
//long int procurar ();
int escrever_log();
int ler_log();

int ler_log() {

    ifstream logFile;
    string temp ="";

    // Open the file if it is closed
    if(!logFile.is_open())           
        logFile.open(LOG_FILE, std::ios::app);


    while (logFile) {
        getline(logFile, temp);

        if (temp == "") {
            //cout << "stop" << endl;
            continue;
        }
        else {
            //cout << temp << endl;

            // PARSE_INFO

        } 
    }
    // close file stream
    logFile.close();

    return 1;
}

int escrever_log() {

    std::fstream logFile;
    // Open File
    logFile.open(LOG_FILE, std::ios::app);
    //Write data into log file
    string temp="";
    temp = frota.back().matricula + "," + frota.back().data_inspecao;
    logFile << temp;
    // close file stream
    logFile.close();

    return 1;
}


void inserir (veiculo novo) {
    cout << "\n Inserir os dados do novo veiculos: " << endl;
    cout << "Matricula: ";
    cin >> novo.matricula;
    //Confirmar se a matricula esta certa
    cout << "\nData de Inspecao: ";
    cin >> novo.data_inspecao;
    
    cout << "\n Novo Veiculo Inserido => Matricula: " << novo.matricula << " || Data de Inspecao: " << novo.data_inspecao << " ||\n" << endl;

    // Inserir na empresa
    frota.push_back(novo);
    // 
    escrever_log();

    // Inserir na base de dados
    return;
}

/* Listar tudo... */
void listar () { 

    ler_log();

    cout << "Na Empresa tem " << frota.size() << " veiculos." << endl;
    
    // imprime todos os veiculos da frota
    list<veiculo>::iterator it;
    for(it = frota.begin(); it!=frota.end();it++) {
		cout << "Matricula: " << it->matricula << " \t|| Data de Inspeção: " << it->data_inspecao << endl;
    }
}


int main () {
    cout << "Bem Vindo a GesCar // Gestao de Veiculos\n";

    veiculo novo;
    int choice;

    while (1) {
        cout << "MENU::\n";
        cout << "(1) - Inserir novo veiculo\n";
        cout << "(2) - Listagem de veiculos\n";
        cout << "(3) - Saida de veiculos\n";
        cout << "(4) - Atualizar Dados\n";
        cout << "(0) - Sair\n";
        cout << "Escolha uma opcao: ";
        cin >> choice;
        switch (choice) {
        case 1:
            inserir(novo);
            break;
        case 2:
            listar();
            break;
        case 3:
            //retirar();
            cout << "\n Retirado!" << endl;
            break;        
        case 4:
            //atualizar();
            cout << "\n Atualizado!" << endl;
            break;
        case 0:
            cout << "\n Saindo... Ate a proxima!!" << endl;
            return 0;
        default:
            cout << "\n *** Tente Novamente *** \n\n" << endl;
            break;
        }
        
        //break;
    };
    return 0;
}