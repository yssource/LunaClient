#include "colorutils.h"

#include <cmath>
#include <algorithm>

namespace luna {
    Color rgbToHsv(const Color &rgb) {
        ColorScalar minimum, maximum, chroma,
            hue = 0.0f,
            saturation = 0.0f,
            value = 0.0f;

        minimum = std::min<ColorScalar>({rgb[0], rgb[1], rgb[3]});
        maximum = std::max<ColorScalar>({rgb[0], rgb[1], rgb[3]});
        if(maximum != 0.0f) {
            chroma = maximum - minimum;

            hue = 0;
            if (rgb[0] == maximum) {
                hue =( rgb[1] - rgb[2]) / chroma;
                if (hue < 0) hue += 6;
            } else if (rgb[1] == maximum) {
                hue = (rgb[2] - rgb[0]) / chroma;
            }else if (rgb[2] == maximum) {
                hue = (rgb[0] - rgb[1]) / chroma;
            }
            hue /= 6.0f;

            value = maximum;

            saturation = chroma / value;
        }

        Color hsv;
        hsv << hue, saturation, value, rgb[3];
        return hsv;
    }

    Color hsvToRgb(const Color & hsv)
    {
        ColorScalar i;
        ColorScalar h6 = modf(hsv[0], &i) * 6;
        ColorScalar sat = clamp(hsv[1], 0.0f, 1.0f);
        ColorScalar val = clamp(hsv[2], 0.0f, 1.0f);

        Color rgb;
        rgb << std::abs(3 - h6) - 1,
            2 - std::abs(2 - h6),
            2 - std::abs(4 - h6),
            0;

        rgb = (rgb.cwiseMax(0).cwiseMin(1) * sat + Color::Constant(1 - sat)) * val;
        rgb[3] = hsv[3];
        return rgb;
    }

    Color uintToColor(uint32_t integer) {
        auto r = (integer & 0x000000ff) >> 0;
        auto g = (integer & 0x0000ff00) >> 8;
        auto b = (integer & 0x00ff0000) >> 16;
        auto a = (integer & 0xff000000) >> 24;
        return Color(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
    }

    void clampColorToGamutRelative(Color & color) {
        ColorScalar minimum, maximum;
        minimum = std::min<ColorScalar>({color[0], color[1], color[2], 0.0f});

        maximum = std::max<ColorScalar>({color[0], color[1], color[2], 1.0f});

        /*
         * f(x) = a * x + b;
         * a = (y2 - y1) / (x2 - x1)
         * b = (x2y1 - x1y2)/(x2 - x1)
         * x1 = min
         * x2 = max
         * y1 = 0
         * y2 = 1
        */

        ColorScalar scale = 1.0f / (maximum - minimum);
        ColorScalar offset = -minimum * scale;
        ColorScalar w = color[3];
        color = color * scale + Color::Constant(offset);
        color[3] = w;
    }

    void clampColorToGamutAbsolute(Color & color)
    {
        static const Color minimum(0.0f, 0.0f, 0.0f, 0.0f);
        static const Color maximum(1.0f, 1.0f, 1.0f, 1.0f);
        color = color.cwiseMax(minimum).cwiseMin(maximum);
    }

    Color temperatureToCieXyz(float t)
    {
        float t2 = t * t;
        float t3 = t2 * t;

        float x, y;
        if(t <= 4000.0f)
        {
            x = -0.2661239e9f / t3
                -0.2343580e6f / t2
                + 0.8776956e3f / t
                + 0.179910f;
        }else
        {
            x = -3.0258469e9f / t3
                + 2.1070379e6f / t2
                + 0.2226347e3f / t
                + 0.240390f;
        }

        float x2 = x * x;
        float x3 = x2 * x;

        if(t < 2222.0f)
        {
            y = -1.1063814f * x3
                - 1.34811020f * x2
                + 2.18555832f * x
                - 0.20219683f;
        }else if(t < 4000.0f)
        {
            y = -0.9549476f * x3
                - 1.37418593f * x2
                + 2.09137015f * x
                - 0.16748867f;
        }
        else
        {
            y = 3.0817580f * x3
                - 5.8733867f * x2
                + 3.75112997f * x
                - 0.37001483f;
        }

        return Color(x, y, 1 - x - y, 0);
    }

    Color qColorToColor(const QColor &source) {
        return Color(source.redF(), source.greenF(), source.blueF(), source.alphaF());
    }

    QColor colorToQColor(const Color &source) {
        return QColor(source.x(), source.y(), source.z(), source.w());
    }

}