/**
 * @file src/configurationmanager.h
 * @brief MEGAcmd: configuration manager
 *
 * (c) 2013-2016 by Mega Limited, Auckland, New Zealand
 *
 * This file is part of the MEGAcmd.
 *
 * MEGAcmd is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * @copyright Simplified (2-clause) BSD License.
 *
 * You should have received a copy of the license along with this
 * program.
 */

#ifndef CONFIGURATIONMANAGER_H
#define CONFIGURATIONMANAGER_H

#include "megacmd.h"
#include <map>
#include <set>

#define CONFIGURATIONSTOREDBYVERSION -2
class ConfigurationManager
{
private:
    static std::string configFolder;

    static void loadConfigDir();


public:
    static std::map<std::string, sync_struct *> configuredSyncs;
    static std::map<std::string, backup_struct *> configuredBackups;

    static std::string session;

    static std::set<std::string> excludedNames;

    static void loadConfiguration(bool debug);
    static void clearConfigurationFile();
    static void loadsyncs();
    static void loadbackups();

    static void saveSyncs(std::map<std::string, sync_struct *> *syncsmap);
    static void saveBackups(std::map<std::string, backup_struct *> *backupsmap);

    static void addExcludedName(std::string excludedName);
    static void removeExcludedName(std::string excludedName);
    static void saveExcludedNames();
    /**
     * @brief loadExcludedNames
     * if called for the first time, it will add default excluded names if no sync has been loaded previously
     */
    static void loadExcludedNames();

    static void saveSession(const char*session);

    static void saveProperty(const char* property, const char* value);

    template<typename T>
    static void savePropertyValue(const char* property, T value)
    {
        std::ostringstream os;
        os << value;
        saveProperty(property,os.str().c_str());
    }

    static std::string getConfigurationSValue(std::string propertyName);
    template <typename T>
    static T getConfigurationValue(std::string propertyName, T defaultValue)
    {
        std::string propValue = getConfigurationSValue(propertyName);
        if (!propValue.size()) return defaultValue;

        T i;
        std::istringstream is(propValue);
        is >> i;
        return i;
    }

    static std::string getConfigFolder();

    static void unloadConfiguration();

};


#endif // CONFIGURATIONMANAGER_H
