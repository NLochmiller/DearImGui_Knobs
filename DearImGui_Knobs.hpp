/*
  BSD 3-Clause License

  Copyright (c) 2024, Nathan Lochmiller

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

  3. Neither the name of the copyright holder nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once

#include "imgui.h"

namespace ImGui {
    bool Knob(const char* label, double* value_p, float circumference = 40.0);
    
    namespace Knobs {
        enum Type {
            // Minimalist, just the base circle
            BLANK, // Draw only the base circle
            // Draw the base and the indicator
            BASIC,
        };

        // Structs to simplify styling
        struct Circle {
            ImU32 color;
            float base_circum;
            int base_segments;
        };

        struct Line {
            ImU32 color;
            float thickness;
        };
        
    }


    struct KnobStyle {
        enum Knobs::Type type;

        Circle base;    // Foundation of the knob
        Line indicator; // Indicator that follows from center to knob direction
        Circle cover;   // A neccessary cover for the indicator
    };
}
