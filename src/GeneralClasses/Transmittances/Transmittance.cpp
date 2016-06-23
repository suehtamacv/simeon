#include "GeneralClasses/Transmittances/Transmittance.h"

using namespace TF;

Transmittance::Transmittance(Gain scale) : scale(scale)
{

}

Gain &Transmittance::get_Gain()
{
    return scale;
}
