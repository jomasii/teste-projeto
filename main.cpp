#include<iostream>
#include<iomanip>
#include<cmath>
#include <string>

using namespace std;

class Transaction {
protected:
    double montante;
    string descricao;

public:
    Transaction(double amt, const string &des){
        montante = amt;
        descricao = des;
    }

    virtual void display() {
        cout << setw(15) << montante << setw(20) << descricao << endl;
    }
};

class Entrada : public Transaction {
public:
    Entrada(double amt, const string& des) : Transaction(amt, des) {}

    void display() {
        cout << setw(15) << "Entrada" << setw(20);
        Transaction::display();
    }
};

class Despesas : public Transaction {
public:
    Despesas(double amt, const string &des) : Transaction(amt, des) {}

    void display() {
        cout << setw(15) << "Despesas" << setw(20);
        Transaction::display();
    }
};

class investimento  {
protected:
    double montante;
    int duracao;

public:
    investimento (double amt, int dur) {
        montante = amt;
        duracao = dur;
    }

    virtual void display() {
        cout << setw(15) << montante << setw(15) << duracao;
    }

    virtual double andamentoMontante() {
        return montante;
    }
};

class Poupanca : public investimento  {
private:
    double mensal;

public:
    Poupanca(double amt, int dur, double monAmt) : investimento (amt, dur) {
        mensal = monAmt;
    }

    void display() {
        cout << setw(15) << "Poupanca";
        investimento ::display();
        cout << setw(20)<<mensal << endl;
    }

    double andamentoMontante() {
        double final = montante * pow(1 + (0.096/12), duracao*12);
        return final + (mensal * 12 * duracao);
    }
};

class CC : public investimento  {
public:
    CC(double amt, int dur) : investimento (amt, dur) {}

    void display() {
        cout << setw(15) << "CC";
        investimento ::display();
        cout << endl;
    }

    double andamentoMontante() {
        return montante * pow((1 + 0.071), duracao);
    }
};

class Gerenciador {
public:
    Transaction* transactions[100];
    investimento * investimentos[50];
    int tcount;
    int icount;

    Gerenciador() {
        tcount = 0;
        icount = 0;
    }

    void addTransaction(Transaction* t) {
        transactions[tcount++] = t;
    }

    void addinvestimento (investimento * i) {
        investimentos[icount++] = i;
    }

    void displayRecord(double Balanco) {
        cout << "-----------------------------------\n";
        cout << "|        Finanças Pessoais        |\n";
        cout << "-----------------------------------\n";

        cout << "\n||--Balanco--: " << Balanco << "||" << endl;

        cout << "\n--Guardado--: \n";
        cout << setw(15) << "Tipo"<<setw(15)<<"Montante" << setw(20) << "Descricao" << endl;
        for (int i = 0; i < tcount; i++) {
            transactions[i]->display();
        }

        cout << "\n--Investimentos--\n";
        cout << setw(15) << "Tipo" << setw(15) << "Montante" << setw(15) << "Duração"<<setw(30)<<"Montante mensal investido"<<endl;
        for (int i = 0; i < icount; i++) {
            investimentos[i]->display();
        }
    }
};

class User {
public:
    Gerenciador manager;
    double Balanco;

    User(double initialBalanco) {
        Balanco = initialBalanco;
    }

    void operations() {
        int choice = -1;
        while (choice != 0) {
            cout << "\n--OPÇÕES--\n";
            cout << "1. ENTRADAS\n";
            cout << "2. DESPESAS\n";
            cout << "3. INVESTIMENTOS\n";
            cout << "4. Informações Financeiras\n";
            cout << "5. Informações de Investimento\n";
            cout << "0. Sair\n";
            cout << "Escolha : ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    double amt;
                    string desc;
                    cout << "Digite montante : ";
                    cin >> amt;
                    cout << "Digite a descricao : ";
                    cin.ignore();
                    getline(cin, desc);
                    manager.addTransaction(new Entrada(amt, desc));
                    Balanco += amt;
                    break;
                }

                case 2: {
                    double amt;
                    string desc;
                    cout << "Digite montante: ";
                    cin >> amt;
                    if (Balanco - amt < 1000) {
                        cout << "Erro: Balanco não pode ser menor que 1000." << endl;
                        continue;
                    }
                    cin.ignore();
                    cout << "Digite a descricao: ";
                    getline(cin, desc);
                    manager.addTransaction(new Despesas(amt, desc));
                    Balanco -= amt;
                    break;
                }

                case 3: {
                    makeinvestimento ();
                    break;
                }

                case 4: {
                    manager.displayRecord(Balanco);
                    break;
                }

                case 5: {
                    cout << "--Total montante--||\n";
                    for (int i = 0; i < manager.icount; i++) {
                        investimento * inv = manager.investimentos[i];
                        cout << "\ninvestimento  " << i + 1 << " : " << inv->andamentoMontante() << " R$" << endl;
                        cout<<setw(15)<<"Tipo"<<setw(15)<<"Montante"<<setw(20)<<"Duração"<<setw(30)<<"Montante mensal investido"<<endl;
                        inv->display();
                    }
                    break;
                }

                case 0:
                    break;

                default:
                    cout << "\nSem opção disponivel :(";
                    break;
            }
        }
    }

    void makeinvestimento () {
        int sub = -1;
        while (sub != 0) {
            cout << "\nQual dais:\n";
            cout << "1. Poupanca\n";
            cout << "2. CC\n";
            cout << "0. Voltar\n";
            cout << "Digite sua escolha : ";
            cin >> sub;

            switch (sub) {
                case 1: {
                    double amt, mensal;
                    int dur;
                    cout << "Digite montante : ";
                    cin >> amt;
                    if (Balanco - amt < 1000) {
                        cout << "Erro : Min Balanco=1000";
                        return;
                    }
                    cout << "Digite a duração em anos : ";
                    cin >> dur;
                    cout << "Digite o investimento mensal : ";
                    cin >> mensal;
                    manager.addinvestimento (new Poupanca(amt, dur, mensal));
                    Balanco -= amt;
                    break;
                }

                case 2: {
                    double amt;
                    int dur;
                    cout << "Digite montante : ";
                    cin >> amt;
                    if (Balanco - amt < 1000) {
                        cout << "Erro: Min Balanco=1000";
                        return;
                    }
                    cout << "Digite a duração em anso : ";
                    cin >> dur;
                    manager.addinvestimento (new CC(amt, dur));
                    Balanco -= amt;
                    break;
                }

                case 0:
                    break;

                default:
                    cout << "Escolha invalida.";
                    break;
            }
        }
    }
};

int main() {
    cout << "---Bem vindo(a) ao Sistema de Gerenciamento Financeiro!!---\n";
    User user(2000);
    user.operations();

    return 0;
}