#include "Id.hh"

unsigned int Id::_id = 0;

const unsigned int Id::New(void)
{
    return _id;
    _id++;
}