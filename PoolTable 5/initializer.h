#ifndef INITIALIZER_H
#define INITIALIZER_H

#include <string>

#include "poolgame.h"


class Dialog;

/**
 * @brief The Initializer class is the director of the poolgame builder
 * it decides what factory to provide to the build based on the config file and also calls the builder's build methods
 */
class Initializer
{
public:
    Initializer(){}

    /**
     * @brief creates a Poolgame from a config file
     * @param configFilePath the path to the config file encoded in JSon
     * @return returns a pointer to a created PoolGame, if the PoolGame failed to be created for any reason nullptr is returned instead
     */
    PoolGame *createPoolgame(const std::string &configFilePath, Dialog *parent);

    int m_volum;
    QString m_path;
    int m_mode;
    bool stage3flag;
    std::vector<Ball *> get_Initballs();
    std::vector<Ball *> Init_balls;  /*Flag - user: define Init Ball Vector*/
};

#endif // INITIALIZER_H
