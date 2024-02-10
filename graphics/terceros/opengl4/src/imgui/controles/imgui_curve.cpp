#include "imgui_curve.h"




namespace ImGui{
   // [src] http://iquilezles.org/www/articles/minispline/minispline.htm
   // key format (for dim == 1) is (t0,x0,t1,x1 ...)
   // key format (for dim == 2) is (t0,x0,y0,t1,x1,y1 ...)
   // key format (for dim == 3) is (t0,x0,y0,z0,t1,x1,y1,z1 ...)
   void spline(const float* key, int num, int dim, float t, float* v){
      static signed char coefs[16] = {
          -1, 2,-1, 0,
           3,-5, 0, 2,
          -3, 4, 1, 0,
           1,-1, 0, 0 };

      const int size = dim + 1;

      // find key
      int k = 0; while (key[k * size] < t) k++;

      // interpolant
      const float h = (t - key[(k - 1) * size]) / (key[k * size] - key[(k - 1) * size]);

      // init result
      for (int i = 0; i < dim; i++) v[i] = 0.0f;

      // add basis functions
      for (int i = 0; i < 4; i++)
      {
         int kn = k + i - 2; if (kn < 0) kn = 0; else if (kn > (num - 1)) kn = num - 1;

         const signed char* co = coefs + 4 * i;

         const float b = 0.5f * (((co[0] * h + co[1]) * h + co[2]) * h + co[3]);

         for (int j = 0; j < dim; j++) v[j] += b * key[kn * size + j + 1];
      }
   }
   float CurveValueSmooth(float p, int maxpoints, const ImVec2* points){
      if (maxpoints < 2 || points == 0)
         return 0;
      if (p < 0) return points[0].y;

      float* input = new float[maxpoints * 2];
      float output[4];

      for (int i = 0; i < maxpoints; ++i) {
         input[i * 2 + 0] = points[i].x;
         input[i * 2 + 1] = points[i].y;
      }

      spline(input, maxpoints, 1, p, output);

      delete[] input;
      return output[0];
   }
   float CurveValue(float p, int maxpoints, const ImVec2* points){
      if (maxpoints < 2 || points == 0)
         return 0;
      if (p < 0) return points[0].y;

      int left = 0;
      while (left < maxpoints && points[left].x < p && points[left].x != -1) left++;
      if (left) left--;

      if (left == maxpoints - 1)
         return points[maxpoints - 1].y;

      float d = (p - points[left].x) / (points[left + 1].x - points[left].x);

      return points[left].y + (points[left + 1].y - points[left].y) * d;
   }

   int Curve(const char* label, const ImVec2& size, const int maxpoints, ImVec2* points){
      int modified = 0;
      int i;
      if (maxpoints < 2 || points == 0)
         return 0;

      if (points[0].x < 0)
      {
         points[0].x = 0;
         points[0].y = 0;
         points[1].x = 1;
         points[1].y = 1;
         points[2].x = -1;
      }

      ImGuiWindow* window = GetCurrentWindow();
      ImGuiContext& g = *GImGui;
      const ImGuiStyle& style = g.Style;
      const ImGuiID id = window->GetID(label);
      if (window->SkipItems)
         return 0;

      ImRect bb(window->DC.CursorPos, window->DC.CursorPos + size);
      ItemSize(bb);
      if (!ItemAdd(bb, NULL))
         return 0;

      const bool hovered = IsItemHovered();

      int max = 0;
      while (max < maxpoints && points[max].x >= 0) max++;

      int kill = 0;
      do
      {
         if (kill)
         {
            modified = 1;
            for (i = kill + 1; i < max; i++)
            {
               points[i - 1] = points[i];
            }
            max--;
            points[max].x = -1;
            kill = 0;
         }

         for (i = 1; i < max - 1; i++)
         {
            if (abs(points[i].x - points[i - 1].x) < 1 / 128.0)
            {
               kill = i;
            }
         }
      } while (kill);


      RenderFrame(bb.Min, bb.Max, GetColorU32(ImGuiCol_FrameBg, 1), true, style.FrameRounding);

      float ht = bb.Max.y - bb.Min.y;
      float wd = bb.Max.x - bb.Min.x;

      if (hovered)
      {
         SetHoveredID(id);
         if (g.IO.MouseDown[0])
         {
            modified = 1;
            ImVec2 pos = (g.IO.MousePos - bb.Min) / (bb.Max - bb.Min);
            pos.y = 1 - pos.y;

            int left = 0;
            while (left < max && points[left].x < pos.x) left++;
            if (left) left--;

            ImVec2 p = points[left] - pos;
            float p1d = sqrt(p.x * p.x + p.y * p.y);
            p = points[left + 1] - pos;
            float p2d = sqrt(p.x * p.x + p.y * p.y);
            int sel = -1;
            if (p1d < (1 / 16.0)) sel = left;
            if (p2d < (1 / 16.0)) sel = left + 1;

            if (sel != -1)
            {
               points[sel] = pos;
            } else
            {
               if (max < maxpoints)
               {
                  max++;
                  for (i = max; i > left; i--)
                  {
                     points[i] = points[i - 1];
                  }
                  points[left + 1] = pos;
               }
               if (max < maxpoints)
                  points[max].x = -1;
            }

            // snap first/last to min/max
            if (points[0].x < points[max - 1].x) {
               points[0].x = 0;
               points[max - 1].x = 1;
            } else {
               points[0].x = 1;
               points[max - 1].x = 0;
            }
         }
      }

      // bg grid
      window->DrawList->AddLine(
         ImVec2(bb.Min.x, bb.Min.y + ht / 2),
         ImVec2(bb.Max.x, bb.Min.y + ht / 2),
         GetColorU32(ImGuiCol_TextDisabled), 3);

      window->DrawList->AddLine(
         ImVec2(bb.Min.x, bb.Min.y + ht / 4),
         ImVec2(bb.Max.x, bb.Min.y + ht / 4),
         GetColorU32(ImGuiCol_TextDisabled));

      window->DrawList->AddLine(
         ImVec2(bb.Min.x, bb.Min.y + ht / 4 * 3),
         ImVec2(bb.Max.x, bb.Min.y + ht / 4 * 3),
         GetColorU32(ImGuiCol_TextDisabled));

      for (i = 0; i < 9; i++)
      {
         window->DrawList->AddLine(
            ImVec2(bb.Min.x + (wd / 10) * (i + 1), bb.Min.y),
            ImVec2(bb.Min.x + (wd / 10) * (i + 1), bb.Max.y),
            GetColorU32(ImGuiCol_TextDisabled));
      }

      // smooth curve
      enum { smoothness = 256 }; // the higher the smoother
      for (i = 0; i <= (smoothness - 1); ++i) {
         float px = (i + 0) / float(smoothness);
         float qx = (i + 1) / float(smoothness);
         float py = 1 - CurveValueSmooth(px, maxpoints, points);
         float qy = 1 - CurveValueSmooth(qx, maxpoints, points);
         ImVec2 p(px * (bb.Max.x - bb.Min.x) + bb.Min.x, py * (bb.Max.y - bb.Min.y) + bb.Min.y);
         ImVec2 q(qx * (bb.Max.x - bb.Min.x) + bb.Min.x, qy * (bb.Max.y - bb.Min.y) + bb.Min.y);
         window->DrawList->AddLine(p, q, GetColorU32(ImGuiCol_PlotLines));
      }

      // lines
      for (i = 1; i < max; i++)
      {
         ImVec2 a = points[i - 1];
         ImVec2 b = points[i];
         a.y = 1 - a.y;
         b.y = 1 - b.y;
         a = a * (bb.Max - bb.Min) + bb.Min;
         b = b * (bb.Max - bb.Min) + bb.Min;
         window->DrawList->AddLine(a, b, GetColorU32(ImGuiCol_PlotLinesHovered));
      }

      if (hovered)
      {
         // control points
         for (i = 0; i < max; i++)
         {
            ImVec2 p = points[i];
            p.y = 1 - p.y;
            p = p * (bb.Max - bb.Min) + bb.Min;
            ImVec2 a = p - ImVec2(2, 2);
            ImVec2 b = p + ImVec2(2, 2);
            window->DrawList->AddRect(a, b, GetColorU32(ImGuiCol_PlotLinesHovered));
         }
      }

      // buttons; @todo: mirror, smooth, tessellate
      if (ImGui::Button("Flip")) {
         for (i = 0; i < max; ++i) {
            points[i].y = 1 - points[i].y;
         }
      }
      ImGui::SameLine();

      // curve selector
      const char* items[] = {
          "Custom",

          "Linear",
          "Quad in",
          "Quad out",
          "Quad in  out",
          "Cubic in",
          "Cubic out",
          "Cubic in  out",
          "Quart in",
          "Quart out",
          "Quart in  out",
          "Quint in",
          "Quint out",
          "Quint in  out",
          "Sine in",
          "Sine out",
          "Sine in  out",
          "Expo in",
          "Expo out",
          "Expo in  out",
          "Circ in",
          "Circ out",
          "Circ in  out",
          "Elastic in",
          "Elastic out",
          "Elastic in  out",
          "Back in",
          "Back out",
          "Back in  out",
          "Bounce in",
          "Bounce out",
          "Bounce in out",

          "Sine square",
          "Exponential",

          "Schubring1",
          "Schubring2",
          "Schubring3",

          "SinPi2",
          "Swing"
      };
      static int item = 0;
      if (modified) {
         item = 0;
      }
      if (ImGui::Combo("Ease type", &item, items, IM_ARRAYSIZE(items))) {
         max = maxpoints;
         if (item > 0) {
            for (i = 0; i < max; ++i) {
               points[i].x = i / float(max - 1);
               points[i].y = float(tween::ease(item - 1, points[i].x));
            }
         }
      }

      char buf[128];
      const char* str = label;

      if (hovered) {
         ImVec2 pos = (g.IO.MousePos - bb.Min) / (bb.Max - bb.Min);
         pos.y = 1 - pos.y;

         sprintf(buf, "%s (%f,%f)", label, pos.x, pos.y);
         str = buf;
      }

      RenderTextClipped(ImVec2(bb.Min.x, bb.Min.y + style.FramePadding.y), bb.Max, str, NULL, NULL);//, ImGuiAlign_Center

      return modified;
   }

};
