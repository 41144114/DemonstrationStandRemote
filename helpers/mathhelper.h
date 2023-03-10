#ifndef MATHHELPER_H
#define MATHHELPER_H

class MathHelper
{
public:
    MathHelper();
    static float convertTo180Angle(float angle);
    static double convertTo180Angle(double angle);
    static void correctToFrom0To360Angle(float& angle);
    static void correctToFrom0To360Angle(double& angle);

    static double fromRadToDeg(double angle);
    static double fromDegToRad(double angle);
};

#endif // MATHHELPER_H
