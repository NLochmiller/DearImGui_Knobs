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

#ifndef DEARIMGUI_KNOBS_HPP_
#define DEARIMGUI_KNOBS_HPP_

#pragma once

#include <math.h>
#include "imgui.h"

namespace ImGui {

    // Forward decleration
    class KnobStyle;
    
    namespace Knobs {
        class Indicator {
        public:
            virtual void render(ImDrawList* draw_list, double angle,
                                ImVec2 center, KnobStyle style) = 0;
        };
        
        enum Type {
            // Minimalist, just the base circle
            BLANK, // Draw only the base circle
            // Draw the base and the indicator
            BASIC,
        };

        // Structs to simplify styling
        struct Circle {
            ImU32 color;
            float radius; // Circumference of this circle
            int segments;
        };

        struct Line {
            ImU32 color;
            float thickness;
        };
    }


    class KnobStyle {
    public:
        // KnobStyle();
        KnobStyle(Knobs::Indicator* indicator = NULL);
        
        enum Knobs::Type type;

        Knobs::Circle base;    // Foundation of the knob
        Knobs::Indicator* indicator; // Indicator of angle
        Knobs::Circle cover;   // A neccessary cover for the indicator
    };

    bool Knob(const char* label, double* value_p,
              ImGui::KnobStyle knobStyle = KnobStyle());


    // TODO: Move to a better location (New file?)
    // Inherit from knobs indicator
    // Has public variables internalPadding and externalPadding, which is how much
    // padding should be between the center and edge of the base circle respectively
    class LineIndicator: public ImGui::Knobs::Indicator {
    public:

        float internalPadding;
        float externalPadding;
        ImU32 color;
        float thickness;
    
        LineIndicator(float internalPadding, float externalPadding, ImU32 color,
                      float thickness) {
            this->internalPadding = internalPadding;
            this->externalPadding = externalPadding;
            this->color = color;
            this->thickness = thickness;
        }
    
        LineIndicator() {
            this->internalPadding = 0.0f;
            this->externalPadding = 0.0f;
            this->color = IM_COL32(255, 255, 255, 255);
            this->thickness = 2.0f;
        }

        // Render the indicator
        void render(ImDrawList* draw_list, double angle, ImVec2 center,
                    ImGui::KnobStyle knobStyle) {
            double radius = knobStyle.base.radius;
            float angle_cos = cosf(angle), angle_sin = sinf(angle);

            // Trig to get the points on the line such that the internal and
            // external padding are the points on the line drawn
            ImVec2 inner_point = ImVec2(center.x +
                                        (angle_cos * this->internalPadding),
                                        center.y +
                                        (angle_sin * this->internalPadding));
            ImVec2 edge_point = ImVec2(center.x + (angle_cos * radius),
                                       center.y + (angle_sin * radius));
            // Point on the outer padding
            ImVec2 outer_point = ImVec2(edge_point.x -
                                        (angle_cos * this->externalPadding),
                                        edge_point.y -
                                        (angle_sin * this->externalPadding));
            draw_list->AddLine(inner_point, outer_point, this->color,
                               this->thickness);
        }
    };

    // A simple circle as the indicator
    class IndicatorDot: public ImGui::Knobs::Indicator {
    public:
        float inner_padding;
        float outer_padding;
        ImU32 color;
        float radius;
        int segments;

        IndicatorDot(float inner_padding = 0.0f, float outer_padding = 0.0f,
                     float radius = 5.0f,
                     ImU32 color = IM_COL32(255, 255, 255, 255),
                     int segments = 0)
        {
            this->inner_padding = inner_padding;
            this->outer_padding = outer_padding;
            this->radius = radius;
            this->color = color;
            this->segments = 0;
        }

        void render(ImDrawList* draw_list, double angle, ImVec2 center,
                    ImGui::KnobStyle knobStyle) {

            double radius = knobStyle.base.radius;
            float angle_cos = cosf(angle), angle_sin = sinf(angle);


            // Trig to get the points on the line such that the internal and
            // external padding are the points on the line drawn
            ImVec2 inner_point = ImVec2(center.x +
                                        (angle_cos * this->inner_padding),
                                        center.y +
                                        (angle_sin * this->inner_padding));
            ImVec2 edge_point = ImVec2(center.x + (angle_cos * radius),
                                       center.y + (angle_sin * radius));
            // Point on the outer padding
            ImVec2 outer_point = ImVec2(edge_point.x -
                                        (angle_cos * this->outer_padding),
                                        edge_point.y -
                                        (angle_sin * this->outer_padding));

            ImVec2 mid_point = ImVec2(inner_point.x +
                                      (outer_point.x - inner_point.x) / 2,
                                      inner_point.y +
                                      (outer_point.y - inner_point.y) / 2);
            
            draw_list->AddCircleFilled(mid_point, this->radius, this->color,
                                       this->segments);
        }
    };
}

#endif // DEARIMGUI_KNOBS_HPP_
