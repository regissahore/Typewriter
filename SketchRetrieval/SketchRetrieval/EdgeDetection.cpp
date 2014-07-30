#include <string>
#include "SettingControl.h"
#include "SettingEdgeDetect.h"
#include "EdgeDetection.h"
using namespace std;

EdgeDetection::EdgeDetection()
{
}


EdgeDetection::~EdgeDetection()
{
}

void EdgeDetection::detect()
{
    SettingEdgeDetect& setting = SettingControl::getInstance().edgeDetect;
    string edgeFolder = setting.getFolderName();
}