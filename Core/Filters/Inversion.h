#ifndef Inversion_H
#define Inversion_H

#include "Core/FilterCreator.h"

//#define REGISTER_FILTER(filter) temp_##filter; static FilterRegistrator filter_reg_##filter(#filter, [] () -> AbstractFilter * {return new  filter() }); class filter


class Inversion : public AbstractFilter
{
public:
    Inversion();
};

static FilterRegistrator filter_reg_Inversion("inversion", [] () -> AbstractFilter * {
                                                  return new  Inversion();
                                              });

#endif // ADDWEIGHTED_H
