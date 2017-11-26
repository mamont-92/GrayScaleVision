#ifndef ADDWEIGHTED_H
#define ADDWEIGHTED_H

#include "Core/FilterCreator.h"

class AddWeighted : public AbstractFilter
{
public:
    AddWeighted();
};

static FilterRegistrator filter_reg_AddWeighted("add weighted", [] () -> AbstractFilter * {
                                                  return new  AddWeighted();
                                              });

#endif // ADDWEIGHTED_H
