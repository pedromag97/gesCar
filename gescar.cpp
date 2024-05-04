#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <cstdlib>
#include <chrono>


using namespace std;
#define LOG_FILE "log_file.txt"
#define DEBUG 0

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
    int tipo_veiculo; // 1 - Familiar, 2 - Comercial
    // numero de chaci
    // data de revisao
    // data de inspeçao
    // bool ativo;
    // data do selo + preço
    // seguro + preço
    // int dono; // 1 - Pedro Mag., 2 - Fernando Mag., 3 - 
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

// HOJE
int dia;
int mes;
int ano;


void hoje() {
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, 80, "%m/%d/%Y ", timeinfo);
    string str(buffer);

    dia = timeinfo->tm_mday;
    mes = timeinfo->tm_mon+1;
    ano = timeinfo->tm_year+1900;

    if (DEBUG)
        cout << "HOJE ||| => " << dia << "|" << mes << "|" << ano << endl;
}

int ler_log() {

    ifstream logFile;
    string temp ="";
    veiculo novo;

    // Open the file if it is closed
    if(!logFile.is_open())           
        logFile.open(LOG_FILE, std::ios::app);


    while (logFile) {
        getline(logFile, temp);

        if (temp == "") {
            //cout << "stop" << endl;
            break;
        }
        else {
            if (DEBUG)
                cout << temp << endl;
            
            // PARSE_INFO
            novo.matricula = temp.substr(0, temp.find(","));
            novo.data_inspecao = temp.substr(temp.find(",")+1, temp.length());
            
            if (DEBUG)
                cout << "XYZ - " << novo.matricula << " || " << novo.data_inspecao << endl;
            
            frota.push_back(novo);

            temp = "";
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
    temp = frota.back().matricula + "," + frota.back().data_inspecao + "\n";
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

    escrever_log();

    // Inserir na base de dados
    return;
}

/* Listar tudo... */
void listar () { 

    if (frota.size() <= 0)
        ler_log();

    cout << "Na Empresa tem " << frota.size() << " veiculos." << endl;
    
    // imprime todos os veiculos da frota
    list<veiculo>::iterator it;
    for(it = frota.begin(); it!=frota.end();it++) {
		cout << "Matricula: " << it->matricula << " \t|| Data de Inspecao: " << it->data_inspecao << endl;
    }
}

void avaliar_datas() {

    int counter=0;

    cout << "************ AVALIACAO ************   " << endl;

    // imprime todos os veiculos da frota
    list<veiculo>::iterator it;
    for(it = frota.begin(); it!=frota.end();it++) {
		if (DEBUG)
            cout << "Matricula: " << it->matricula << " \t|| Data de Inspecao: " << it->data_inspecao << endl;
        
        // contador
        counter++;
        
        // Se a data de inspeçao menor que 30 dias, imprimir aviso

        // PARSE DATA
        int parse_1 = it->data_inspecao.find('-');
        
        auto dia_insp = stoi(it->data_inspecao.substr(0, parse_1));
        auto mes_insp = stoi(it->data_inspecao.substr(parse_1+1, parse_1+2));
        auto ano_insp = stoi(it->data_inspecao.substr(parse_1+4, it->data_inspecao.length()));

        
        if (DEBUG)
            cout << "* Inspecao *   " << it->matricula 
                << " - " << dia_insp 
                << "|" << mes_insp 
                << "|" << ano_insp
                << endl;

        // IF DATA DE INSPEÇÃO - HOJE() menor Q 30 dias
        if (ano_insp > ano) {
            //cout << "---OK--- " << it->matricula << endl;
        }
        else if (mes_insp > mes) {
            //cout << "---OK--- " << it->matricula << endl;
        }
        else {       //      MENSAGEM ALERTA
            cout << "******** ALERTA ******** " << it->matricula << endl;
		    cout << "Matricula: " << it->matricula << " \t|| Data de Inspecao: " << it->data_inspecao << endl;
        }
    }
    cout << "Foram revistos " << counter << " na frota de "  << frota.size() << " veiculos." << endl;
}


int main () {
    cout << "Bem Vindo a GesCar // Gestao de Veiculos\n";

    veiculo novo;
    int choice;

    hoje();
    ler_log();

    // Primeira avaliação
    avaliar_datas();

    // Menu Interativo
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