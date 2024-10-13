#include "barb.h"

Barb::Barb() {
    animation_loose.set_atlas(&atlas_barb_loose);
    animation_break.set_atlas(&atlas_barb_break);
    animation_loose.set_loop(true);
    animation_break.set_loop(false);

}