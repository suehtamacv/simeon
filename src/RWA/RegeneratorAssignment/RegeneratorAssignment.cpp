#include <RWA/RegeneratorAssignment/RegeneratorAssignment.h>
#include <cmath>

RegeneratorAssignment::RegeneratorAssignment(std::shared_ptr<Topology> T) :
    T(T) {

}

unsigned int RegeneratorAssignment::get_NumNeededRegenerators(Call C) {
    return ceil(C.Bitrate.get_Bitrate() / RegeneratorBitrate);
}
