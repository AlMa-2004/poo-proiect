#ifndef CROP_H
#define CROP_H
#include <string>
#include <iostream>

class Crop
{
    std::string cropName;
    int cropGrowthTime;

    /*
    This attribute cannot possibly be 0, since t=0 is allocated for initialisation of assets, display of menu etc. Everytime a crop object is created (aka planted in the field), this attribute must take the current timestamp of the elapsed in-game time.
    */
    long long timeStampPlanted;
    bool cropGrowthStatus, cropWateredStatus;

public:
    Crop();
    explicit Crop(std::string name, int growth_time, long long time_stamp_planted,
                  bool growth_status, bool watered_status);
    Crop& operator=(const Crop& r);
    friend std::ostream& operator<<(std::ostream& os, const Crop& obj);
    void Grow(long long seconds);
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] bool getGrowthStatus() const;
    [[nodiscard]] bool getWateredStatus() const;
    void setWateredStatus(bool t);
    friend void Harvest();
};
#endif //CROP_H
