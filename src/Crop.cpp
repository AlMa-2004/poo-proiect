#include "../headers/Crop.h"

Crop::Crop():
    cropGrowthTime(1),
    timeStampPlanted(0),
    cropGrowthStatus(false),
    cropWateredStatus(false)
{
}

Crop::Crop(std::string name, const int growth_time = 0, long long time_stamp_planted = 0,
           const bool growth_status = false, const bool watered_status = false)
    : cropName(std::move(name)),
      cropGrowthTime(growth_time),
      timeStampPlanted(time_stamp_planted),
      cropGrowthStatus(growth_status),
      cropWateredStatus(watered_status)

{
}

Crop& Crop::operator=(const Crop& other)
{
    cropName = other.cropName;
    cropGrowthTime = other.cropGrowthTime;
    cropGrowthStatus = other.cropGrowthStatus;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Crop& obj)
{
    os << "cropName: " << obj.cropName
        << " timeStampPlanted: " << obj.timeStampPlanted
        << " cropGrowthTime: " << obj.cropGrowthTime
        << " cropWateredStatus: " << obj.cropWateredStatus
        << " growthStatus: " << obj.cropGrowthStatus
        << "\n";
    return os;
}

void Crop::Grow(long long seconds)
{
    if (cropGrowthStatus == false && cropWateredStatus && (seconds - timeStampPlanted) >= cropGrowthTime)
    {
        cropGrowthStatus = true;
        std::cout << "The crop " << cropName << " has grown!\n";
    }
    else std::cout << "The crop " << cropName << " is still growing!\n";
}

[[nodiscard]] std::string Crop::getName() const { return cropName; }
[[nodiscard]] bool Crop::getGrowthStatus() const { return cropGrowthStatus; }
void Crop::setWateredStatus(bool t) { cropWateredStatus = t; }
[[nodiscard]] bool Crop::getWateredStatus() const { return cropWateredStatus; }
