#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "backup.h"
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

void criarArquivo(const std::string& caminho, const std::string& conteudo = "teste") {
     fs::create_directories(fs::path(caminho).parent_path());
     std::ofstream ofs(caminho);
     ofs << conteudo;
     ofs.close();
}

void limpar(const std::string& caminho) {
     if (fs::exists(caminho)) fs::remove_all(caminho);
}

TEST_CASE("Ler Backup.parm válido retorna entradas corretas") {
     std::ofstream parm("Backup.parm");
     parm << "./teste/original.txt ./backup/\n";
     parm.close();

     auto entradas = lerArquivoBackup("Backup.parm");
     REQUIRE(entradas.size() == 1);
     REQUIRE(entradas[0].origem == "./teste/original.txt");
     REQUIRE(entradas[0].destino == "./backup/");

     
     fs::remove("Backup.parm");
}

TEST_CASE("Ler Backup.parm inexistente retorna lista vazia") {
     if (fs::exists("nao_existe.parm")) fs::remove("nao_existe.parm");
     auto entradas = lerArquivoBackup("nao_existe.parm");
     REQUIRE(entradas.empty());
}

TEST_CASE("Ler Backup.parm mal formatado ignora linhas inválidas") {
     std::ofstream parm("Backup.parm");
     parm << "# linha válida\n";
     parm << "./origem.txt ./destino/\n";
     parm << "so_um_campo_sem_destino\n";
     parm.close();

     auto entradas = lerArquivoBackup("Backup.parm");
     REQUIRE(entradas.size() == 1); // só uma linha é válida

     fs::remove("Backup.parm");
}

TEST_CASE("Backup de arquivo existente deve criar cópia") {
     limpar("teste");
     limpar("backup");
     criarArquivo("teste/original.txt", "conteudo");

     bool ok = backupArquivo("teste/original.txt", "backup/");
     REQUIRE(ok);
     REQUIRE(fs::exists("backup/original.txt"));

     limpar("teste");
     limpar("backup");
}