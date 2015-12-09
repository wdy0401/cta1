#ifndef OPTIONF_H
#define OPTIONF_H

#include "optionf_global.h"

#include <math.h>
#include <map>
#include <list>

class OPTIONFSHARED_EXPORT optionf
{

public:
    optionf();
    void set_vol(long second,double price);
    double get_vol();
    double get_vol_adjust(std::map <long,double> *);
    double get_vol_adjust();
    double get_vol(long);


private:
    double lastp;
    bool inited;
    std::list <double> vol_list;
    std::map <long,double> vol_map;
    std::map <long,std::map<long,double>*> vol_snap_map;//use open as bar value
};
//

#endif // OPTIONF_H
