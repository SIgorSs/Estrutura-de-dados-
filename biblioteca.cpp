#include <iostream>
#include <cstdio>
#include <cstring>
#include <limits>

using namespace std;

struct emprestimos {
    char dt_emp[10], dt_dev[10], usuario[255];
};

struct livros {
    int codigo, paginas;
    char area[30], titulo[255], autores[255], editora[50];
    struct emprestimos emp;
};

int main() {
    int opc_princ, cod;
    char opc;
    FILE *arquivo, *arquivoAux;
    struct livros livro;

    do {
        cout << "\n###### SISTEMA LEGAL DE BIBLIOTECA ######" << endl;
        cout << "1 - Cadastro" << endl;
        cout << "2 - Alteração" << endl;
        cout << "3 - Exclusão" << endl;
        cout << "4 - Empréstimo" << endl;
        cout << "5 - Devolução" << endl;
        cout << "6 - Consulta de Livro" << endl;
        cout << "7 - Listar Todos os Livros" << endl;
        cout << "8 - Listar Livros Emprestados" << endl;
        cout << "9 - Sair" << endl << endl;
        cout << "Digite a opção desejada: ";
        cin >> opc_princ;

        if (opc_princ == 1) {  
            cout << "Deseja cadastrar um livro (S ou N)? ";
            cin >> opc;
            while (opc == 'S') {
                cout << "Código: ";
                cin >> livro.codigo;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Área: ";
                cin.get(livro.area, 30);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Título: ";
                cin.get(livro.titulo, 255);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Autor(es): ";
                cin.get(livro.autores, 255);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Editora: ";
                cin.get(livro.editora, 50);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Nº de páginas: ";
                cin >> livro.paginas;

                if ((arquivo = fopen("dados.dat", "ab")) != NULL) {
                    fwrite(&livro, sizeof(struct livros), 1, arquivo);
                    cout << "Livro cadastrado com sucesso!" << endl;
                    fclose(arquivo);
                } else {
                    cout << "Erro ao abrir o arquivo para gravação!" << endl;
                }

                cout << "Deseja cadastrar outro livro (S ou N)? ";
                cin >> opc;
            }
        }

        else if (opc_princ == 2) {  
            cout << "Digite o código do livro que deseja alterar: ";
            cin >> cod;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if ((arquivo = fopen("dados.dat", "rb+")) != NULL) {
                bool encontrado = false;
                while (fread(&livro, sizeof(struct livros), 1, arquivo)) {
                    if (cod == livro.codigo) {
                        cout << "Área: ";
                        cin.get(livro.area, 30);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        cout << "Título: ";
                        cin.get(livro.titulo, 255);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        cout << "Autor(es): ";
                        cin.get(livro.autores, 255);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        cout << "Editora: ";
                        cin.get(livro.editora, 50);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        cout << "Nº de páginas: ";
                        cin >> livro.paginas;

                        fseek(arquivo, -sizeof(struct livros), SEEK_CUR);
                        fwrite(&livro, sizeof(struct livros), 1, arquivo);
                        cout << "Livro alterado com sucesso!" << endl;
                        encontrado = true;
                        break;
                    }
                }
                fclose(arquivo);

                if (!encontrado) {
                    cout << "Livro com código " << cod << " não encontrado!" << endl;
                }
            } else {
                cout << "Erro ao abrir o banco de dados!" << endl;
            }
        }

        else if (opc_princ == 3) {  
            cout << "Digite o código do livro que deseja excluir: ";
            cin >> cod;

            if ((arquivo = fopen("dados.dat", "rb")) != NULL) {
                if ((arquivoAux = fopen("dados.aux", "wb")) != NULL) {
                    bool encontrado = false;
                    while (fread(&livro, sizeof(struct livros), 1, arquivo)) {
                        if (cod != livro.codigo) {
                            fwrite(&livro, sizeof(struct livros), 1, arquivoAux);
                        } else {
                            encontrado = true;
                        }
                    }
                    fclose(arquivo);
                    fclose(arquivoAux);

                    if (encontrado) {
                        remove("dados.dat");
                        rename("dados.aux", "dados.dat");
                        cout << "Livro excluído com sucesso!" << endl;
                    } else {
                        cout << "Livro com código " << cod << " não encontrado!" << endl;
                        remove("dados.aux");
                    }
                } else {
                    cout << "Erro ao abrir o arquivo auxiliar!" << endl;
                    fclose(arquivo);
                }
            } else {
                cout << "Erro ao abrir o arquivo para exclusão!" << endl;
            }
        }

        else if (opc_princ == 4) {  
            cout << "Digite o código do livro que deseja emprestar: ";
            cin >> cod;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if ((arquivo = fopen("dados.dat", "rb+")) != NULL) {
                bool encontrado = false;
                while (fread(&livro, sizeof(struct livros), 1, arquivo)) {
                    if (cod == livro.codigo) {
                        cout << "Data de empréstimo: ";
                        cin.get(livro.emp.dt_emp, 10);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        cout << "Data de devolução: ";
                        cin.get(livro.emp.dt_dev, 10);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        cout << "Usuário: ";
                        cin.get(livro.emp.usuario, 255);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        fseek(arquivo, -sizeof(struct livros), SEEK_CUR);
                        fwrite(&livro, sizeof(struct livros), 1, arquivo);
                        cout << "Empréstimo registrado com sucesso!" << endl;
                        encontrado = true;
                        break;
                    }
                }
                fclose(arquivo);

                if (!encontrado) {
                    cout << "Livro com código " << cod << " não encontrado!" << endl;
                }
            } else {
                cout << "Erro ao abrir o banco de dados!" << endl;
            }
        }

        else if (opc_princ == 5) {  
            cout << "Digite o código do livro que deseja devolver: ";
            cin >> cod;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if ((arquivo = fopen("dados.dat", "rb+")) != NULL) {
                bool encontrado = false;
                while (fread(&livro, sizeof(struct livros), 1, arquivo)) {
                    if (cod == livro.codigo) {
                        memset(&livro.emp, 0, sizeof(livro.emp));

                        fseek(arquivo, -sizeof(struct livros), SEEK_CUR);
                        fwrite(&livro, sizeof(struct livros), 1, arquivo);
                        cout << "Devolução registrada com sucesso!" << endl;
                        encontrado = true;
                        break;
                    }
                }
                fclose(arquivo);

                if (!encontrado) {
                    cout << "Livro com código " << cod << " não encontrado!" << endl;
                }
            } else {
                cout << "Erro ao abrir o banco de dados!" << endl;
            }
        }        else if (opc_princ == 6) {  
            cout << "Digite o código do livro que deseja consultar: ";
            cin >> cod;

            if ((arquivo = fopen("dados.dat", "rb")) != NULL) {
                bool encontrado = false;
                while (fread(&livro, sizeof(struct livros), 1, arquivo)) {
                    if (cod == livro.codigo) {
                        cout << "Código: " << livro.codigo << endl;
                        cout << "Área: " << livro.area << endl;
                        cout << "Título: " << livro.titulo << endl;
                        cout << "Autor(es): " << livro.autores << endl;
                        cout << "Editora: " << livro.editora << endl;
                        cout << "Nº de páginas: " << livro.paginas << endl;
                        if (strlen(livro.emp.usuario) > 0) {
                            cout << "Emprestado para: " << livro.emp.usuario << endl;
                            cout << "Data de empréstimo: " << livro.emp.dt_emp << endl;
                            cout << "Data de devolução: " << livro.emp.dt_dev << endl;
                        } else {
                            cout << "Livro disponível." << endl;
                        }
                        encontrado = true;
                        break;
                    }
                }
                fclose(arquivo);

                if (!encontrado) {
                    cout << "Livro com código " << cod << " não encontrado!" << endl;
                }
            } else {
                cout << "Erro ao abrir o banco de dados!" << endl;
            }
        }

        else if (opc_princ == 7) {  
            if ((arquivo = fopen("dados.dat", "rb")) != NULL) {
                cout << "\nLista de todos os livros:\n" << endl;
                while (fread(&livro, sizeof(struct livros), 1, arquivo)) {
                    cout << "Código: " << livro.codigo << endl;
                    cout << "Área: " << livro.area << endl;
                    cout << "Título: " << livro.titulo << endl;
                    cout << "Autor(es): " << livro.autores << endl;
                    cout << "Editora: " << livro.editora << endl;
                    cout << "Nº de páginas: " << livro.paginas << endl;
                    if (strlen(livro.emp.usuario) > 0) {
                        cout << "Emprestado para: " << livro.emp.usuario << endl;
                        cout << "Data de empréstimo: " << livro.emp.dt_emp << endl;
                        cout << "Data de devolução: " << livro.emp.dt_dev << endl;
                    } else {
                        cout << "Livro disponível." << endl;
                    }
                    cout << "-----------------------" << endl;
                }
                fclose(arquivo);
            } else {
                cout << "Erro ao abrir o banco de dados!" << endl;
            }
        }

        else if (opc_princ == 8) {  
            if ((arquivo = fopen("dados.dat", "rb")) != NULL) {
                cout << "\nLista de livros emprestados:\n" << endl;
                bool encontrado = false;
                while (fread(&livro, sizeof(struct livros), 1, arquivo)) {
                    if (strlen(livro.emp.usuario) > 0) {  
                        cout << "Código: " << livro.codigo << endl;
                        cout << "Área: " << livro.area << endl;
                        cout << "Título: " << livro.titulo << endl;
                        cout << "Autor(es): " << livro.autores << endl;
                        cout << "Editora: " << livro.editora << endl;
                        cout << "Nº de páginas: " << livro.paginas << endl;
                        cout << "Emprestado para: " << livro.emp.usuario << endl;
                        cout << "Data de empréstimo: " << livro.emp.dt_emp << endl;
                        cout << "Data de devolução: " << livro.emp.dt_dev << endl;
                        cout << "-----------------------" << endl;
                        encontrado = true;
                    }
                }
                fclose(arquivo);

                if (!encontrado) {
                    cout << "Nenhum livro emprestado encontrado." << endl;
                }
            } else {
                cout << "Erro ao abrir o banco de dados!" << endl;
            }
        }

        else if (opc_princ != 9) {
            cout << "Informe uma opção válida!" << endl;
        }

    } while (opc_princ != 9);

    cout << "Obrigado por usar nossa solução!" << endl;

    return 0;
}
    
