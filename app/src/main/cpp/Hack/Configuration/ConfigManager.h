//
// Created by ircxx on 7/8/2023.
//

#ifndef IMGUIANDROID_CONFIGMANAGER_H
#define IMGUIANDROID_CONFIGMANAGER_H
#include <iostream>
#include "ConfigurationStruct.h"

class ConfigManager{
private:
    std::string mConfigFilePath;
public:
    GlobalConfiguration G_Config;

    ConfigManager(std::string);
    void WriteConfiguration();
    void ReadConfiguration();


};


#endif //IMGUIANDROID_CONFIGMANAGER_H
