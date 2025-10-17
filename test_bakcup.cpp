#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "backup.h"
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

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