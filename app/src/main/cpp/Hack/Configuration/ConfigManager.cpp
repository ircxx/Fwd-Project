//
// Created by ircxx on 7/8/2023.
//

#include "ConfigManager.h"
#include "Obfuscation/Obfuscate.h"


ConfigManager::ConfigManager(std::string GameCachePath) {
    mConfigFilePath = GameCachePath + "/Configuration.cfg";
}

void ConfigManager::WriteConfiguration() {
    FILE* SavedFile = nullptr;
    SavedFile = fopen(mConfigFilePath.c_str(), OBFUSCATE("wb"));
    if(SavedFile != nullptr)
    fwrite(&G_Config, sizeof(GlobalConfiguration), 1, SavedFile);
    fclose(SavedFile);
}

void ConfigManager::ReadConfiguration() {
    FILE* SavedFile = nullptr;
    SavedFile = fopen(mConfigFilePath.c_str(), OBFUSCATE("rb"));
    if(SavedFile != nullptr)
    fread(&G_Config, sizeof(GlobalConfiguration), 1, SavedFile);
}