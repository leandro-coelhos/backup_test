\
#include "backup.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <cassert>

namespace fs = std::filesystem;

std::vector<EntradaBackup> lerArquivoBackup(const std::string& nome_arquivo) {
     assert(!nome_arquivo.empty());

     std::ifstream arquivo(nome_arquivo);
     std::vector<EntradaBackup> entradas;
     std::string linha;

     if (!arquivo.is_open()) {
          std::cerr << "Erro ao abrir arquivo de parâmetros: " << nome_arquivo << std::endl;
          return entradas;
     }

     while (std::getline(arquivo, linha)) {
          // Trim leading spaces
          auto start = linha.find_first_not_of(" \t\r\n");
          if (start == std::string::npos) continue;
          linha = linha.substr(start);

          if (linha.empty() || linha[0] == '#') continue;

          std::istringstream iss(linha);
          EntradaBackup entrada;
          iss >> entrada.origem >> entrada.destino;

          // ignore malformed lines (must have origin and destination)
          if (!entrada.origem.empty() && !entrada.destino.empty()) {
          entradas.push_back(entrada);
          }
     }

     return entradas;
}

bool backupArquivo(const std::string& origem, const std::string& destino) {
     assert(!origem.empty());
     assert(!destino.empty());

     fs::path src(origem);
     fs::path dst = fs::path(destino) / src.filename();

     if (!fs::exists(src)) {
          std::cerr << "Arquivo inexistente: " << origem << std::endl;
          return false;
     }

     try {
          fs::create_directories(dst.parent_path());
          fs::copy_file(src, dst, fs::copy_options::overwrite_existing);
     } catch (const fs::filesystem_error& e) {
          std::cerr << "Erro ao copiar arquivo: " << e.what() << std::endl;
          return false;
     }

     return fs::exists(dst);
}
