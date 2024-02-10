// [src] https://github.com/ocornut/imgui/issues/123
// [src] https://github.com/ocornut/imgui/issues/55

// v1.22 - flip button; cosmetic fixes
// v1.21 - oops :)
// v1.20 - add iq's interpolation code
// v1.10 - easing and colors        
// v1.00 - jari komppa's original

#pragma once

#include "imgui.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"

#include <cmath>

/* To use, add this prototype somewhere..
namespace ImGui
{
    int Curve(const char *label, const ImVec2& size, int maxpoints, ImVec2 *points);
    float CurveValue(float p, int maxpoints, const ImVec2 *points);
    float CurveValueSmooth(float p, int maxpoints, const ImVec2 *points);
};
*/
/*
    Example of use:
    ImVec2 foo[10];
    ...
    foo[0].x = -1; // init data so editor knows to take it from here
    ...
    if (ImGui::Curve("Das editor", ImVec2(600, 200), 10, foo))
    {
        // curve changed
    }
    ...
    float value_you_care_about = ImGui::CurveValue(0.7f, 10, foo); // calculate value at position 0.7
*/

namespace tween {
   enum TYPE
   {
      LINEAR,

      QUADIN,          // t^2
      QUADOUT,
      QUADINOUT,
      CUBICIN,         // t^3
      CUBICOUT,
      CUBICINOUT,
      QUARTIN,         // t^4
      QUARTOUT,
      QUARTINOUT,
      QUINTIN,         // t^5
      QUINTOUT,
      QUINTINOUT,
      SINEIN,          // sin(t)
      SINEOUT,
      SINEINOUT,
      EXPOIN,          // 2^t
      EXPOOUT,
      EXPOINOUT,
      CIRCIN,          // sqrt(1-t^2)
      CIRCOUT,
      CIRCINOUT,
      ELASTICIN,       // exponentially decaying sine wave
      ELASTICOUT,
      ELASTICINOUT,
      BACKIN,          // overshooting cubic easing: (s+1)*t^3 - s*t^2
      BACKOUT,
      BACKINOUT,
      BOUNCEIN,        // exponentially decaying parabolic bounce
      BOUNCEOUT,
      BOUNCEINOUT,

      SINESQUARE,      // gapjumper's
      EXPONENTIAL,     // gapjumper's
      SCHUBRING1,      // terry schubring's formula 1
      SCHUBRING2,      // terry schubring's formula 2
      SCHUBRING3,      // terry schubring's formula 3

      SINPI2,          // tomas cepeda's
      SWING,           // tomas cepeda's & lquery's
   };

   // }

   // implementation

   static inline
      double ease(int easetype, double t)
   {
      using namespace std;

      const double d = 1.f;
      const double pi = 3.1415926535897932384626433832795;
      const double pi2 = 3.1415926535897932384626433832795 / 2;

      double p = t / d;

      switch (easetype)
      {
         // Modeled after the line y = x
      default:
      case TYPE::LINEAR: {
         return p;
      }

                       // Modeled after the parabola y = x^2
      case TYPE::QUADIN: {
         return p * p;
      }

                       // Modeled after the parabola y = -x^2 + 2x
      case TYPE::QUADOUT: {
         return -(p * (p - 2));
      }

                        // Modeled after the piecewise quadratic
                        // y = (1/2)((2x)^2)             ; [0, 0.5)
                        // y = -(1/2)((2x-1)*(2x-3) - 1) ; [0.5, 1]
      case TYPE::QUADINOUT: {
         if (p < 0.5) {
            return 2 * p * p;
         } else {
            return (-2 * p * p) + (4 * p) - 1;
         }
      }

                          // Modeled after the cubic y = x^3
      case TYPE::CUBICIN: {
         return p * p * p;
      }

                        // Modeled after the cubic y = (x - 1)^3 + 1
      case TYPE::CUBICOUT: {
         double f = (p - 1);
         return f * f * f + 1;
      }

                         // Modeled after the piecewise cubic
                         // y = (1/2)((2x)^3)       ; [0, 0.5)
                         // y = (1/2)((2x-2)^3 + 2) ; [0.5, 1]
      case TYPE::CUBICINOUT: {
         if (p < 0.5) {
            return 4 * p * p * p;
         } else {
            double f = ((2 * p) - 2);
            return 0.5 * f * f * f + 1;
         }
      }

                           // Modeled after the quartic x^4
      case TYPE::QUARTIN: {
         return p * p * p * p;
      }

                        // Modeled after the quartic y = 1 - (x - 1)^4
      case TYPE::QUARTOUT: {
         double f = (p - 1);
         return f * f * f * (1 - p) + 1;
      }

                         // Modeled after the piecewise quartic
                         // y = (1/2)((2x)^4)        ; [0, 0.5)
                         // y = -(1/2)((2x-2)^4 - 2) ; [0.5, 1]
      case TYPE::QUARTINOUT: {
         if (p < 0.5) {
            return 8 * p * p * p * p;
         } else {
            double f = (p - 1);
            return -8 * f * f * f * f + 1;
         }
      }

                           // Modeled after the quintic y = x^5
      case TYPE::QUINTIN: {
         return p * p * p * p * p;
      }

                        // Modeled after the quintic y = (x - 1)^5 + 1
      case TYPE::QUINTOUT: {
         double f = (p - 1);
         return f * f * f * f * f + 1;
      }

                         // Modeled after the piecewise quintic
                         // y = (1/2)((2x)^5)       ; [0, 0.5)
                         // y = (1/2)((2x-2)^5 + 2) ; [0.5, 1]
      case TYPE::QUINTINOUT: {
         if (p < 0.5) {
            return 16 * p * p * p * p * p;
         } else {
            double f = ((2 * p) - 2);
            return  0.5 * f * f * f * f * f + 1;
         }
      }

                           // Modeled after quarter-cycle of sine wave
      case TYPE::SINEIN: {
         return sin((p - 1) * pi2) + 1;
      }

                       // Modeled after quarter-cycle of sine wave (different phase)
      case TYPE::SINEOUT: {
         return sin(p * pi2);
      }

                        // Modeled after half sine wave
      case TYPE::SINEINOUT: {
         return 0.5 * (1 - cos(p * pi));
      }

                          // Modeled after shifted quadrant IV of unit circle
      case TYPE::CIRCIN: {
         return 1 - sqrt(1 - (p * p));
      }

                       // Modeled after shifted quadrant II of unit circle
      case TYPE::CIRCOUT: {
         return sqrt((2 - p) * p);
      }

                        // Modeled after the piecewise circular function
                        // y = (1/2)(1 - sqrt(1 - 4x^2))           ; [0, 0.5)
                        // y = (1/2)(sqrt(-(2x - 3)*(2x - 1)) + 1) ; [0.5, 1]
      case TYPE::CIRCINOUT: {
         if (p < 0.5) {
            return 0.5 * (1 - sqrt(1 - 4 * (p * p)));
         } else {
            return 0.5 * (sqrt(-((2 * p) - 3) * ((2 * p) - 1)) + 1);
         }
      }

                          // Modeled after the exponential function y = 2^(10(x - 1))
      case TYPE::EXPOIN: {
         return (p == 0.0) ? p : pow(2, 10 * (p - 1));
      }

                       // Modeled after the exponential function y = -2^(-10x) + 1
      case TYPE::EXPOOUT: {
         return (p == 1.0) ? p : 1 - pow(2, -10 * p);
      }

                        // Modeled after the piecewise exponential
                        // y = (1/2)2^(10(2x - 1))         ; [0,0.5)
                        // y = -(1/2)*2^(-10(2x - 1))) + 1 ; [0.5,1]
      case TYPE::EXPOINOUT: {
         if (p == 0.0 || p == 1.0) return p;

         if (p < 0.5) {
            return 0.5 * pow(2, (20 * p) - 10);
         } else {
            return -0.5 * pow(2, (-20 * p) + 10) + 1;
         }
      }

                          // Modeled after the damped sine wave y = sin(13pi/2*x)*pow(2, 10 * (x - 1))
      case TYPE::ELASTICIN: {
         return sin(13 * pi2 * p) * pow(2, 10 * (p - 1));
      }

                          // Modeled after the damped sine wave y = sin(-13pi/2*(x + 1))*pow(2, -10x) + 1
      case TYPE::ELASTICOUT: {
         return sin(-13 * pi2 * (p + 1)) * pow(2, -10 * p) + 1;
      }

                           // Modeled after the piecewise exponentially-damped sine wave:
                           // y = (1/2)*sin(13pi/2*(2*x))*pow(2, 10 * ((2*x) - 1))      ; [0,0.5)
                           // y = (1/2)*(sin(-13pi/2*((2x-1)+1))*pow(2,-10(2*x-1)) + 2) ; [0.5, 1]
      case TYPE::ELASTICINOUT: {
         if (p < 0.5) {
            return 0.5 * sin(13 * pi2 * (2 * p)) * pow(2, 10 * ((2 * p) - 1));
         } else {
            return 0.5 * (sin(-13 * pi2 * ((2 * p - 1) + 1)) * pow(2, -10 * (2 * p - 1)) + 2);
         }
      }

                             // Modeled (originally) after the overshooting cubic y = x^3-x*sin(x*pi)
      case TYPE::BACKIN: { /*
          return p * p * p - p * sin(p * pi); */
         double s = 1.70158f;
         return p * p * ((s + 1) * p - s);
      }

                       // Modeled (originally) after overshooting cubic y = 1-((1-x)^3-(1-x)*sin((1-x)*pi))
      case TYPE::BACKOUT: { /*
          double f = (1 - p);
          return 1 - (f * f * f - f * sin(f * pi)); */
         double s = 1.70158f;
         return --p, 1.f * (p * p * ((s + 1) * p + s) + 1);
      }

                        // Modeled (originally) after the piecewise overshooting cubic function:
                        // y = (1/2)*((2x)^3-(2x)*sin(2*x*pi))           ; [0, 0.5)
                        // y = (1/2)*(1-((1-x)^3-(1-x)*sin((1-x)*pi))+1) ; [0.5, 1]
      case TYPE::BACKINOUT: { /*
          if(p < 0.5) {
              double f = 2 * p;
              return 0.5 * (f * f * f - f * sin(f * pi));
          }
          else {
              double f = (1 - (2*p - 1));
              return 0.5 * (1 - (f * f * f - f * sin(f * pi))) + 0.5;
          } */
         double s = 1.70158f * 1.525f;
         if (p < 0.5) {
            return p *= 2, 0.5 * p * p * (p * s + p - s);
         } else {
            return p = p * 2 - 2, 0.5 * (2 + p * p * (p * s + p + s));
         }
      }

#           define tween$bounceout(p) ( \
                (p) < 4/11.0 ? (121 * (p) * (p))/16.0 : \
                (p) < 8/11.0 ? (363/40.0 * (p) * (p)) - (99/10.0 * (p)) + 17/5.0 : \
                (p) < 9/10.0 ? (4356/361.0 * (p) * (p)) - (35442/1805.0 * (p)) + 16061/1805.0 \
                           : (54/5.0 * (p) * (p)) - (513/25.0 * (p)) + 268/25.0 )

      case TYPE::BOUNCEIN: {
         return 1 - tween$bounceout(1 - p);
      }

      case TYPE::BOUNCEOUT: {
         return tween$bounceout(p);
      }

      case TYPE::BOUNCEINOUT: {
         if (p < 0.5) {
            return 0.5 * (1 - tween$bounceout(1 - p * 2));
         } else {
            return 0.5 * tween$bounceout((p * 2 - 1)) + 0.5;
         }
      }

#           undef tween$bounceout

      case TYPE::SINESQUARE: {
         double A = sin((p)*pi2);
         return A * A;
      }

      case TYPE::EXPONENTIAL: {
         return 1 / (1 + exp(6 - 12 * (p)));
      }

      case TYPE::SCHUBRING1: {
         return 2 * (p + (0.5f - p) * abs(0.5f - p)) - 0.5f;
      }

      case TYPE::SCHUBRING2: {
         double p1pass = 2 * (p + (0.5f - p) * abs(0.5f - p)) - 0.5f;
         double p2pass = 2 * (p1pass + (0.5f - p1pass) * abs(0.5f - p1pass)) - 0.5f;
         double pAvg = (p1pass + p2pass) / 2;
         return pAvg;
      }

      case TYPE::SCHUBRING3: {
         double p1pass = 2 * (p + (0.5f - p) * abs(0.5f - p)) - 0.5f;
         double p2pass = 2 * (p1pass + (0.5f - p1pass) * abs(0.5f - p1pass)) - 0.5f;
         return p2pass;
      }

      case TYPE::SWING: {
         return ((-cos(pi * p) * 0.5) + 0.5);
      }

      case TYPE::SINPI2: {
         return sin(p * pi2);
      }
      }
   }
}
namespace ImGui {
	int Curve(const char* label, const ImVec2& size, const int maxpoints, ImVec2* points);
	float CurveValue(float p, int maxpoints, const ImVec2* points);
	float CurveValueSmooth(float p, int maxpoints, const ImVec2* points);
	void spline(const float* key, int num, int dim, float t, float* v);
}