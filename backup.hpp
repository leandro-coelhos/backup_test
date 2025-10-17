\
#ifndef BACKUP_H
#define BACKUP_H

#include <string>
#include <vector>

struct EntradaBackup {
     std::string origem;
     std::string destino;
};

/***************************************************************************
 * Função: lerArquivoBackup
 * Descrição:
 *     Lê o arquivo Backup.parm e retorna uma lista de entradas de backup.
 * Parâmetros:
 *     nome_arquivo - caminho do arquivo Backup.parm
 * Valor retornado:
 *     Vetor com pares origem/destino
 * Assertivas de entrada:
 *     nome_arquivo não deve ser vazio.
 ***************************************************************************/
std::vector<EntradaBackup> lerArquivoBackup(const std::string& nome_arquivo);

/***************************************************************************
 * Função: backupArquivo
 * Descrição:
 *     Copia um arquivo do caminho de origem para o caminho de destino.
 * Parâmetros:
 *     origem - caminho do arquivo de origem
 *     destino - diretório de destino
 * Valor retornado:
 *     true se o backup for bem-sucedido, false caso contrário.
 * Assertivas de entrada:
 *     origem e destino não devem ser vazios.
 * Assertivas de saída:
 *     Arquivo de destino deve existir após a cópia.
 ***************************************************************************/
bool backupArquivo(const std::string& origem, const std::string& destino);

#endif