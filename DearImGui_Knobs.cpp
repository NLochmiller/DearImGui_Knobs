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

#include "imgui.h"
#include <math.h>
#include "DearImGui_Knobs.hpp"

// Convert radians to degrees
double radToDeg(double a)
{
    return a * 180/M_PI;
}

// Finds the angle from src to dest
double findAngleDifference(ImVec2 src, ImVec2 dest)
{
    return atan2(dest.y - src.y, dest.x - src.x);
}

/*
 * Returns if the value has been changed
 */
bool ImGui::Knob(const char* label, double* value_p, const float ImGui::KnobStyle)
{
    bool has_value_changed = false;

    // Get io and styling
    ImGuiIO& io = ImGui::GetIO();
    ImGuiStyle& style = ImGui::GetStyle();
    float line_height = ImGui::GetTextLineHeight();

    // Get positioning data
    float outer_radius = circumference / 2;
    ImVec2 pos = ImGui::GetCursorScreenPos();
    ImVec2 center = ImVec2(pos.x + outer_radius, pos.y + outer_radius);


    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    // The area occupied by this knob
    ImVec2 area = ImVec2(circumference,
                         circumference + line_height + style.ItemInnerSpacing.y
                         );

    // Use an invisible button to detect user input
    ImGui::InvisibleButton(label, area);
    bool is_active = ImGui::IsItemActive();
    bool is_hovered = ImGui::IsItemHovered();
    // If the user has moved at all, while clicking on this
    if (is_active && (io.MouseDelta.x != 0.0f || io.MouseDelta.y != 0.0f))
    {
        // Calculate the angle from center to users cursor
        ImVec2 mouse_pos = io.MousePos;
        *value_p = findAngleDifference(center, mouse_pos);
        has_value_changed = true;
    }

    /* Draw knob */
    // Draw base, then line from center to edge, then an inner circle to cutoff
    // line
    int segments = 0;
    ImU32 circle_col = ImGui::GetColorU32(ImGuiCol_FrameBg);
    draw_list->AddCircleFilled(center, outer_radius, circle_col, segments);

    return has_value_changed;
}
