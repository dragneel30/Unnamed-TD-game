#ifndef WAVE_H
#define WAVE_H

#include "FileLoader.h"
#include "information.h"
#include <sstream>
class Wave : public FileLoader
{
    public:
        Wave() : timePerWave(5)
        {
            load("enemywave.txt");
            currWave = -1;
        }

        struct waveInfo
        {
            waveInfo(const std::string& e, int q) : enemy(e), quantity(q), spawnCount(0), timePerSpawn(1) {}
            std::string enemy;
            int quantity;
            int spawnCount;
            bool hasFinishedSpawning()
            {
                return spawnCount == quantity;
            }
            void spawn()
            {
                spawnCount++;
            }
            double timePerSpawn;
        };
        bool load(const std::string& filename)
        {
            fOpener.open(filename);
            if ( fOpener.is_open() )
            {
                std::string enemy;
                double quantity;
                while(fOpener >> enemy)
                {
                    fOpener >> quantity;
                    enemyWaves.emplace_back(enemy,quantity);
                }
            }
            fOpener.close();
        }
        const std::vector<waveInfo>& getEnemyWaves()
        {
            return enemyWaves;
        }

        const waveInfo& getNextWave()
        {
            currWave++;
            std::ostringstream s;
            s << currWave;
            info.setText("Wave: " + s.str());
            return enemyWaves[currWave];
        }


        void setInfoPosition(const sf::Vector2f& pos)
        {
            info.setPosition(pos);
        }

        int timePerWave;
        int currWave;
        Information info;

    private:
        std::vector<waveInfo> enemyWaves;
};

#endif // WAVE_H
