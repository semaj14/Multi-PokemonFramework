#include <Headers.hpp>

namespace CTRPluginFramework {
    using namespace CTRPluginFrameworkImpl::Services;
    thread_local RendererContext Renderer::_rendererContext;

    inline u32 GetFramebufferOffset(int posX, int posY, int bpp, int rowsize) {
        return ((rowsize - 1 - posY + posX * rowsize) * bpp);
    }

    void Renderer::SetTarget(Target target) {
        RendererContext *ctx = GetContext();
        ctx->target = target;

        if (target == BOTTOM)
            ctx->screen = ScreenImpl::Bottom;

        else ctx->screen = ScreenImpl::Top;

        PrivColor::SetFormat(ctx->screen->GetFormat());
    }

    void Renderer::EndFrame(bool copy) {
        static const IntRect &background = Window::BottomWindow.GetRect(); // 20, 20, 280, 200);
        bool isTouchDown = Touch::IsDown();
        IntVector touchPos(Touch::GetPosition());

        // Draw Touch Cursor (on menu)
        if (isTouchDown && background.Contains(touchPos)) {
            int posX = touchPos.x - 2;
            int posY = touchPos.y - 1;
            touchPos.x += 10;
            touchPos.y += 15;

            if (background.Contains(touchPos)) {
                SetTarget(BOTTOM);
                DrawSysString("\uE058", posX, posY, 320, Color::White);
            }
        }

        ScreenImpl::Top->SwapBuffer();
        ScreenImpl::Bottom->SwapBuffer();
        GSP::WaitBufferSwapped(3);

        if (copy) {
            ScreenImpl::Top->Copy();
            ScreenImpl::Bottom->Copy();
        }

    }

    void Renderer::MenuSelector(int posX, int posY, int width, int height) {
        ScreenImpl *screen = GetContext()->screen;
        int w = width;
        int h = height;
        u8 *left = screen->GetLeftFrameBuffer(posX, posY + 1);
        int bpp;
        int rowstride;
        GSPGPU_FramebufferFormat fmt;
        screen->GetFrameBufferInfos(rowstride, bpp, fmt);
        float fade = Preferences::Settings.CursorFadeValue;

        // Draw Rectangle
        while (--w >= 0) {
            h = height;
            u8 *dst = left + rowstride * w;

            while (--h >= 0) {
                Color &&c = PrivColor::FromFramebuffer(dst);
                c.Fade(fade);
                PrivColor::ToFramebuffer(dst, c);
                dst -= bpp;
            }
        }

        int tier = width / 3;
        int pitch = tier / 10;
        int j = 0;
        float fading = 0.0f;
        Color l(255, 255, 255);
        posY += height;
        u8 *dst = screen->GetLeftFrameBuffer(posX + (width - tier), posY);
        u8 *rtier = dst;
        Color black(60, 60, 60);

        // Right tier
        for (int i = tier; i > 0; --i) {
            l.Fade(fading);

            if (l <= black)
                break;

            PrivColor::ToFramebuffer(rtier, l);
            j++;

            if (j == pitch) {
                fading -= 0.01f;
                j = 0;
            }

            rtier += rowstride;
        }

        l = Color(255, 255, 255);

        // Middle tier
        for (int i = 0; i < tier; ++i) {
            PrivColor::ToFramebuffer(dst, l);
            dst -= rowstride;
        }

        fading = 0.0f;

        // Left tier
        for (int i = tier; i > 0; --i) {
            l.Fade(fading);

            if (l <= black)
                break;

            PrivColor::ToFramebuffer(dst, l);
            dst -= rowstride;
            j++;

            if (j == pitch) {
                fading -= 0.01f;
                j = 0;
            }
        }
    }

    void ProcessingLogo::Reset(void) {
        step = 0;
        timer.Restart();
    }

    void ProcessingLogo::Draw(int posX, int posY) {
        const char *waitLogo[] = {"\uE020", "\uE021", "\uE022", "\uE023", "\uE024", "\uE025", "\uE026", "\uE027"};
        Renderer::DrawSysString(waitLogo[step], posX, posY, 300, Color::SkyBlue);

        if (timer.HasTimePassed(Seconds(0.125f))) {
            ++step;
            timer.Restart();

            if (step >= 8)
                step = 0;
        }
    }

    static void DrawLineV(u32 fmt, const Color &color, u8 *dst, u32 height) {
        switch (fmt) {
            case GSP_RGBA8_OES: {
                while (height--) {
                    *dst++ = color.a;
                    *dst++ = color.b;
                    *dst++ = color.g;
                    *dst++ = color.r;
                }

                break;
            }

            case GSP_BGR8_OES: {
                while (height--) {
                    *dst++ = color.b;
                    *dst++ = color.g;
                    *dst++ = color.r;
                }

                break;
            }

            case GSP_RGB565_OES: {
                union {
                    u16 u;
                    char b[2];
                } half;

                half.u  = (color.r & 0xF8) << 8;
                half.u |= (color.g & 0xFC) << 3;
                half.u |= (color.b & 0xF8) >> 3;

                while (height--) {
                    *(dst++) = half.b[0];
                    *(dst++) = half.b[1];
                }

                break;
            }

            case GSP_RGB5_A1_OES: {
                union {
                    u16 u;
                    char b[2];
                } half;

                half.u  = (color.r & 0xF8) << 8;
                half.u |= (color.g & 0xF8) << 3;
                half.u |= (color.b & 0xF8) >> 2;
                half.u |= 1;

                while (height--) {
                    *(dst++) = half.b[0];
                    *(dst++) = half.b[1];
                }

                break;
            }

            case GSP_RGBA4_OES: {
                union {
                    u16 u;
                    char b[2];
                } half;

                half.u  = (color.r & 0xF0) << 8;
                half.u |= (color.g & 0xF0) << 4;
                half.u |= (color.b & 0xF0);
                half.u |= 0x0F;

                while (height--) {
                    *(dst++) = half.b[0];
                    *(dst++) = half.b[1];
                }

                break;
            }

            default: break;
        }
    }

    static void DrawLineV2(u32 fmt, const Color &color1, const Color &color2, u8 *dst, u32 height) {
        union UColor {
            u16 u;
            char b[2];
        };

        switch (fmt) {
            case GSP_RGBA8_OES: {
                u32 *dst32 = (u32*)dst;

                while (height--) {
                    const Color &color = height & 1 ? color1 : color2;
                    *dst32++ = color.raw;
                }

                break;
            }

            case GSP_BGR8_OES: {
                while (height--) {
                    const Color &color = height & 1 ? color1 : color2;
                    *dst++ = color.b;
                    *dst++ = color.g;
                    *dst++ = color.r;
                }

                break;
            }

            case GSP_RGB565_OES: {
                UColor c1;
                UColor c2;

                c1.u  = (color1.r & 0xF8) << 8;
                c1.u |= (color1.g & 0xFC) << 3;
                c1.u |= (color1.b & 0xF8) >> 3;

                c2.u  = (color2.r & 0xF8) << 8;
                c2.u |= (color2.g & 0xFC) << 3;
                c2.u |= (color2.b & 0xF8) >> 3;

                while (height--) {
                    const UColor &c = height & 1 ? c1 : c2;
                    *(dst++) = c.b[0];
                    *(dst++) = c.b[1];
                }

                break;
            }

            case GSP_RGB5_A1_OES: {
                UColor c1;
                UColor c2;

                c1.u  = (color1.r & 0xF8) << 8;
                c1.u |= (color1.g & 0xF8) << 3;
                c1.u |= (color1.b & 0xF8) >> 2;
                c1.u |= 1;

                c2.u  = (color2.r & 0xF8) << 8;
                c2.u |= (color2.g & 0xF8) << 3;
                c2.u |= (color2.b & 0xF8) >> 2;
                c2.u |= 1;

                while (height--) {
                    const UColor &c = height & 1 ? c1 : c2;
                    *(dst++) = c.b[0];
                    *(dst++) = c.b[1];
                }

                break;
            }

            case GSP_RGBA4_OES: {
                UColor c1;
                UColor c2;

                c1.u  = (color1.r & 0xF0) << 8;
                c1.u |= (color1.g & 0xF0) << 4;
                c1.u |= (color1.b & 0xF0);
                c1.u |= 0x0F;

                c2.u  = (color2.r & 0xF0) << 8;
                c2.u |= (color2.g & 0xF0) << 4;
                c2.u |= (color2.b & 0xF0);
                c2.u |= 0x0F;

                while (height--) {
                    const UColor &c = height & 1 ? c1 : c2;
                    *(dst++) = c.b[0];
                    *(dst++) = c.b[1];
                }

                break;
            }

            default: break;
        }
    }

    void Renderer::DrawLine(int posX, int posY, int width, const Color &color, int height) {
        if (posY < 0) {
            if (posY + height < 0)
                return;

            height += posY;
            posY = 0;
        }

        while (posY + height > 240) {
            if (height <= 0)
                return;

            --height;
        }

        // Clamp check
        if (PrivColor::_useClamp) {
            const IntRect &clampArea = PrivColor::_clampArea;

            // Top
            if (posY < clampArea.leftTop.y) {
                int diff = clampArea.leftTop.y - posY;
                posY += diff;
                height -= diff;

                if (height <= 0)
                    return;
            }

            int borderY = clampArea.leftTop.y + clampArea.size.y;

            // Bottom
            if (posY + height > borderY)
                height = borderY - posY;

            // Left
            if (posX < clampArea.leftTop.x) {
                int diff = clampArea.leftTop.x - posX;
                posX += diff;
                width -= diff;

                if (diff <= 0)
                    return;
            }

            int borderX = clampArea.leftTop.x + clampArea.size.x;

            // Right
            if (posX + width > borderX)
                width = borderX - posX;
        }

        ScreenImpl *screen = GetContext()->screen;
        u8 *dst = screen->GetLeftFrameBuffer(posX, posY + height - 1);
        u32 stride = screen->GetStride();
        u32 fmt = screen->GetFormat();

        while (width-- > 0) {
            DrawLineV(fmt, color, dst, height);
            dst += stride;
        }
    }

    void Renderer::DrawLine(const IntVector &start, const IntVector &end, const Color &color) {
        int posX = start.x;
        int posY = start.y;
        int width = end.x - posX; // 50 - 10 = 40
        int height = 1 + end.y - posY;

        while (posY + height > 240) {
            if (height <= 0)
                return;

            --height;
        }

        // Clamp check
        if (PrivColor::_useClamp) {
            const IntRect &clampArea = PrivColor::_clampArea;

            // Top
            if (posY < clampArea.leftTop.y) {
                int diff = clampArea.leftTop.y - posY;
                posY += diff;
                height -= diff;

                if (height <= 0)
                    return;
            }

            int borderY = clampArea.leftTop.y + clampArea.size.y;

            // Bottom
            if (posY + height > borderY)
                height = borderY - posY;

            // Left
            if (posX < clampArea.leftTop.x) {
                int diff = clampArea.leftTop.x - posX;
                posX += diff;
                width -= diff;

                if (diff <= 0)
                    return;
            }

            int borderX = clampArea.leftTop.x + clampArea.size.x;

            // Right
            if (posX + width > borderX)
                width = borderX - posX;
        }

        ScreenImpl *screen = GetContext()->screen;
        u8 *dst = screen->GetLeftFrameBuffer(posX, posY + height - 1);
        u32 stride = screen->GetStride();
        u32 fmt = screen->GetFormat();

        while (width-- > 0) {
            DrawLineV(fmt, color, dst, height);
            dst += stride;
        }
    }

    void Renderer::DrawStippledLine(int posX, int posY, int width, const Color &color, int height) {
        if (posY < 0) {
            if (posY + height < 0)
                return;

            height += posY;
            posY = 0;
        }

        while (posY + height > 240) {
            if (height <= 0)
                return;

            --height;
        }

        ScreenImpl *screen = GetContext()->screen;
        u8 *dst = screen->GetLeftFrameBuffer(posX, posY + height - 1);
        u32 stride = screen->GetStride();
        int pitch = 5;

        while (width-- > 0) {
            u8 *dd = dst;

            if (pitch > 0) {
                for (int y = 0; y < height; ++y)
                    dd = PrivColor::ToFramebuffer(dd, color);
            }

            --pitch;

            if (pitch <= -5)
                pitch = 5;

            dst += stride;
        }
    }

    #if GEOMETRY
    void Renderer::Arc(int posX, int posY, int r, Color color) {
        int d;
        int y;
        int x = 0;
        y = r;
        d = 1 - r;
        _DrawPixel(x,y, color);

        while (y > x) {
            if (d < 0)
                d += 2 * x + 3;

            else {
                d += 2 * (x - y) + 5;
                y--;
            }

            x++ ;
            _DrawPixel(x + posX, posY + (r - y), color);
        }
    }

    void Renderer::Ellipse(int posX, int posY, long a, long b, Color color) {
        int x;
        int y;
        double d1;
        double d2;
        x = 0;
        y = b;
        d1 = b * b - a * a * b + a * a / 4;
        _DrawPixel(posX, posY, color);

        while (a * a * (y - .5) > b * b * (x + 1)) {
            if (d1 < 0) {
                d1 += b * b * (2 * x + 3);
                x++;
            }

            else {
                d1 += b * b * (2 * x + 3) + a * a * (-2 * y + 2);
                x++;
                y--;
            }

            _DrawPixel(posX + x, posY + (b - y), color);
        }

        d2 = b * b * (x + .5) * (x + .5) + a * a * (y - 1) * (y - 1) - a * a * b * b;

        while (y > 0) {
            if (d2 < 0) {
                d2 += b * b * (2 * x + 2) + a * a * (-2 * y + 3);
                y--;
                x++;
            }

            else {
                d2 += a * a * (-2 * y + 3);
                y--;
            }

            _DrawPixel(posX + x, posY + (b - y), color);
        }
    }

    void Renderer::EllipseIncomplete(int posX, int posY, float a, float b, int max, int aff, Color color) {
        int x;
        int y;
        float d1;
        int d2;

        x = 0;
        y = b;
        d1 = b * b - a * a * b + a * a / 4;
        _DrawPixel(posX + x, posY, color);
        _DrawPixel(posX + x, posY + (b - y), color);
        _DrawPixel(posX + x, posY - (b - y), color);
        _DrawPixel(posX - x, posY - (b - y), color);
        _DrawPixel(posX - x, posY + (b - y), color);
        int cpt = 0;

        while ((a * a * (y - .5) > b * b * (x + 1)) && (cpt < max)) {
            cpt++;

            if (d1 < 0) {
                d1 += b * b * (2 * x + 3);
                x++;
            }

            else {
                d1 += b * b * (2 * x + 3) + a * a * (-2 * y + 2);
                x++;
                y--;
            }

            _DrawPixel(posX + x, posY + (b - y), color);
            _DrawPixel(posX + x, posY - (b - y), color);
            _DrawPixel(posX - x, posY - (b - y), color);
            _DrawPixel(posX - x, posY + (b - y), color);
        }

        d2 = (float)(b * b * (x + .5) * (x + .5) + a * a * (y - 1) * (y - 1) - a * a * b * b);

        while ((y > 0) && (cpt < max)) {
            cpt++;

            if (d2 < 0) {
                d2 += b * b * (2 * x + 2) + a * a * (-2 * y + 3);
                y--;
                x++;
            }

            else {
                d2 += a * a * (-2 * y + 3);
                y--;
            }

            _DrawPixel(posX + x, posY + (b - y), color);
            _DrawPixel(posX + x, posY - (b - y), color);
            _DrawPixel(posX - x, posY - (b - y), color);
            _DrawPixel(posX - x, posY + (b - y), color);
        }
    }

    void Renderer::RoundedRectangle(const IntRect &rect, float radius, int max, Color color, bool mustFill, Color fillColor) {
        int x;
        int y;
        float d1;
        int d2;

        using Point = IntVector;
        queue<Point> points;

        int width = rect.size.x;
        int height = rect.size.y;

        int posX = rect.leftTop.x;
        int posY = rect.leftTop.y;

        // From negative rectangle to positive
        if (width < 0) {
            width = -width;
            posX -= width;
        }

        if (height < 0) {
            height = -height;
            posY -= height;
        }

        int cpt = 0;
        x = 0;
        y = radius;
        d1 = radius * radius - radius * radius * radius + radius * radius / 4;
        float d1Bak = d1;

        while ((radius * radius * (radius - .5) > radius * radius * (x + 1)) && (cpt < max)) {
            cpt++;

            if (d1 < 0) {
                d1 += radius * radius * (2 * x + 3);
                x++;
            }

            else {
                d1 += radius * radius * (2 * x + 3) + radius * radius * (-2 * y + 2);
                x++;
                y--;
            }
        }

        while ((y > 0) && (cpt < max)) {
            cpt++;

            if (d2 < 0) {
                d2 += radius * radius * (2 * x + 2) + radius * radius * (-2 * y + 3);
                y--;
                x++;
            }

            else {
                d2 += radius * radius * (-2 * y + 3);
                y--;
            }
        }

        d1 = d1Bak;
        int rHeight = radius - y;
        int rWidth = x;

        y = radius;
        x = 0;

        width -= rWidth; {
            int posXX;
            int posYY;

            // Left Top Corner
            posXX = posX - x + rWidth;
            posYY = posY + (radius - y);
            _DrawPixel(posXX, posYY, color);
            points.push(Point(posXX + 1, posYY));

            // Right Top Corner
            posXX = posX + x + width;
            posYY = posY + (radius - y);
            _DrawPixel(posXX, posYY, color);
            points.push(Point(posXX - 1, posYY));

            // Left Bottom Corner
            posXX = posX - x + rWidth;
            posYY = posY - (radius - y) + height;
            _DrawPixel(posXX, posYY, color);
            points.push(Point(posXX + 1, posYY));

            // Right Bottom Corner
            posXX = posX + x + width;
            posYY = posY + height - (radius - y);
            _DrawPixel(posXX, posYY, color);
            points.push(Point(posXX - 1, posYY));

        }

        cpt = 0;

        while ((radius * radius * (radius - .5) > radius * radius * (x + 1)) && (cpt < max)) {
            cpt++;

            if (d1 < 0) {
                d1 += radius * radius * (2 * x + 3);
                x++;
            }

            else {
                d1 += radius * radius * (2 * x + 3) + radius * radius * (-2 * y + 2);
                x++;
                y--;
            }

            int posXX;
            int posYY;

            // Left Top Corner
            posXX = posX - x + rWidth;
            posYY = posY + (radius - y);
            _DrawPixel(posXX, posYY, color);
            points.push(Point(posXX + 1, posYY));

            // Right Top Corner
            posXX = posX + x + width;
            posYY = posY + (radius - y);
            _DrawPixel(posXX, posYY, color);
            points.push(Point(posXX - 1, posYY));

            // Left Bottom Corner
            posXX = posX - x + rWidth;
            posYY = posY - (radius - y) + height;
            _DrawPixel(posXX, posYY, color);
            points.push(Point(posXX + 1, posYY));

            // Right Bottom Corner
            posXX = posX + x + width;
            posYY = posY + height - (radius - y);
            _DrawPixel(posXX, posYY, color);
            points.push(Point(posXX - 1, posYY));
        }

        d2 = (float)(radius * radius * (x + .5) * (x + .5) + radius * radius * (y - 1) * (y - 1) - radius * radius * radius * radius);

        while ((y > 0) && (cpt < max)) {
            cpt++;

            if (d2 < 0) {
                d2 += radius * radius * (2 * x + 2) + radius * radius * (-2 * y + 3);
                y--;
                x++;
            }

            else {
                d2 += radius * radius * (-2 * y + 3);
                y--;
            }

            int posXX;
            int posYY;

            // Left Top Corner
            posXX = posX - x + rWidth;
            posYY = posY + (radius - y);
            _DrawPixel(posXX, posYY, color);
            points.push(Point(posXX + 1, posYY));

            // Right Top Corner
            posXX = posX + x + width;
            posYY = posY + (radius - y);
            _DrawPixel(posXX, posYY, color);
            points.push(Point(posXX - 1, posYY));

            // Left Bottom Corner
            posXX = posX - x + rWidth;
            posYY = posY - (radius - y) + height;
            _DrawPixel(posXX, posYY, color);
            points.push(Point(posXX + 1, posYY));

            // Right Bottom Corner
            posXX = posX + x + width;
            posYY = posY + height - (radius - y);
            _DrawPixel(posXX, posYY, color);
            points.push(Point(posXX - 1, posYY));
        }

        // Top line
        DrawLine(posX + rWidth, posY - 1, width - rWidth, color);
        // Bottom line
        DrawLine(posX + rWidth, posY + height - 1, width - rWidth, color);
        // Left line
        DrawLine(posX - x + rWidth, posY + rHeight - 1, 1, color, height - (rHeight* 2));
        // Right line
        DrawLine(posX + x + width, posY + rHeight, 1, color, height - (rHeight * 2));

        if (mustFill) {
            while (!points.empty()) {
                Point left = points.front(); points.pop();
                Point right = points.front(); points.pop();
                DrawLine(left, right, fillColor);
            }

            int posXX = posX - x + rWidth + 1;
            int posYY = posY + rHeight - 1;
            int wwidth = x + width - 1;
            int hheight = height - (rHeight* 2);
            DrawLine(posXX, posYY, wwidth, fillColor, hheight);
        }
    }
    #endif

    void Renderer::ComputeRoundedRectangle(vector<IntLine> &out, const IntRect &rect, float radius, int max) {
        int x;
        int y;
        float d1;
        int d2 = 0;

        using Point = IntVector;
        queue<Point> points;

        int width = rect.size.x;
        int height = rect.size.y;

        int posX = rect.leftTop.x;
        int posY = rect.leftTop.y;
        int posYBak;

        if (width < 0) {
            width = -width;
            posX -= width;
        }

        if (height < 0) {
            height = -height;
            posY -= height;
        }

        posYBak = posY;
        int cpt = 0;
        x = 0;
        y = radius;
        d1 = radius * radius - radius * radius * radius + radius * radius / 4;
        float d1Bak = d1;

        while ((radius * radius * (radius - .5) > radius * radius * (x + 1)) && (cpt < max)) {
            cpt++;

            if (d1 < 0) {
                d1 += radius * radius * (2 * x + 3);
                x++;
            }

            else {
                d1 += radius * radius * (2 * x + 3) + radius * radius * (-2 * y + 2);
                x++;
                y--;
            }
        }

        while ((y > 0) && (cpt < max)) {
            cpt++;

            if (d2 < 0) {
                d2 += radius * radius * (2 * x + 2) + radius * radius * (-2 * y + 3);
                y--;
                x++;
            }

            else {
                d2 += radius * radius * (-2 * y + 3);
                y--;
            }
        }

        d1 = d1Bak;
        int rHeight = radius - y;
        int rWidth = x;

        y = radius;
        x = 0;

        width -= rWidth; {
            int posXX;
            int posYY;

            // Left Top Corner
            posXX = posX - x + rWidth;
            posYY = posY + (radius - y);
            points.push(Point(posXX, posYY));

            // Right Top Corner
            posXX = posX + x + width;
            posYY = posY + (radius - y);
            points.push(Point(posXX, posYY));

            // Left Bottom Corner
            posXX = posX - x + rWidth;
            posYY = posY - (radius - y) + height;
            points.push(Point(posXX, posYY));

            // Right Bottom Corner
            posXX = posX + x + width;
            posYY = posY + height - (radius - y);
            points.push(Point(posXX, posYY));

        }

        cpt = 0;

        while ((radius * radius * (radius - .5) > radius * radius * (x + 1)) && (cpt < max)) {
            cpt++;

            if (d1 < 0) {
                d1 += radius * radius * (2 * x + 3);
                x++;
            }

            else {
                d1 += radius * radius * (2 * x + 3) + radius * radius * (-2 * y + 2);
                x++;
                y--;
            }

            int posXX;
            int posYY;

            // Left Top Corner
            posXX = posX - x + rWidth;
            posYY = posY + (radius - y);
            //_DrawPixel(posXX, posYY, color);
            points.push(Point(posXX, posYY));

            // Right Top Corner
            posXX = posX + x + width;
            posYY = posY + (radius - y);
            // _DrawPixel(posXX, posYY, color);
            points.push(Point(posXX, posYY));

            // Left Bottom Corner
            posXX = posX - x + rWidth;
            posYY = posY - (radius - y) + height;
            ///_DrawPixel(posXX, posYY, color);
            points.push(Point(posXX, posYY));

            // Right Bottom Corner
            posXX = posX + x + width;
            posYY = posY + height - (radius - y);
            //_DrawPixel(posXX, posYY, color);
            points.push(Point(posXX, posYY));
        }

        d2 = (float)(radius * radius * (x + .5) * (x + .5) + radius * radius * (y - 1) * (y - 1) - radius * radius * radius * radius);

        while ((y > 0) && (cpt < max)) {
            cpt++;

            if (d2 < 0) {
                d2 += radius * radius * (2 * x + 2) + radius * radius * (-2 * y + 3);
                y--;
                x++;
            }

            else {
                d2 += radius * radius * (-2 * y + 3);
                y--;
            }

            int posXX;
            int posYY;

            // Left Top Corner
            posXX = posX - x + rWidth;
            posYY = posY + (radius - y);
            points.push(Point(posXX, posYY));

            // Right Top Corner
            posXX = posX + x + width;
            posYY = posY + (radius - y);
            points.push(Point(posXX, posYY));

            // Left Bottom Corner
            posXX = posX - x + rWidth;
            posYY = posY - (radius - y) + height;
            points.push(Point(posXX, posYY));

            // Right Bottom Corner
            posXX = posX + x + width;
            posYY = posY + height - (radius - y);
            points.push(Point(posXX, posYY));
        }

        while (!points.empty()) {
            Point left = points.front(); points.pop();
            Point right = points.front(); points.pop();
            out.push_back(IntLine(left, right));
        }

        // Top Line
        out.push_back(IntLine(posX + rWidth - 1, posYBak, width - rWidth + 3, 1));
        // Bottom Line
        out.push_back(IntLine(posX + rWidth - 1, posYBak + height, width - rWidth + 3, 1));
        // Left Line
        out.push_back(IntLine(posX - x + rWidth, posYBak + rHeight, 1, height - (rHeight* 2)));
        // Right Line
        out.push_back(IntLine(posX + x + width, posYBak + rHeight, 1, height - (rHeight * 2)));

        int posXX = posX - x + rWidth + 1;
        int posYY = posYBak + rHeight;
        int wwidth = x + width - 1;
        int hheight = height - (rHeight* 2);

        out.push_back(IntLine(posXX, posYY, wwidth, hheight));
    }

    void Renderer::DrawRoundedRectangle(const IntRect &rect, const Color &border, const Color &fill) {
        static vector<IntLine> _lines;

        if (_lines.empty())
            ComputeRoundedRectangle(_lines, IntRect(0, 0, rect.size.x, rect.size.y), 7.f, 50);

        u32 bMax = _lines.size() - 5;
        u32 i;
        u32 posX = rect.leftTop.x;
        u32 posY = rect.leftTop.y;

        for (i = 0; i < bMax; ++i) {
            IntLine &line = _lines[i];

            // Draw border
            Renderer::DrawPixel(posX + line.start.x, posY + line.start.y, border);
            Renderer::DrawPixel(posX + line.end.x, posY + line.end.y, border);

            // Fill line
            Renderer::DrawLine(posX + 1 + line.start.x, posY + line.start.y, line.end.x - line.start.x - 1, fill);
        }

        for (; i < _lines.size() - 1; ++i) {
            IntLine &line = _lines[i];
            Renderer::DrawLine(posX + line.start.x, posY + line.start.y, line.end.x, border, line.end.y);
        }

        IntLine &line = _lines[i];
        Renderer::DrawLine(posX + line.start.x, posY + line.start.y, line.end.x, fill, line.end.y);
    }

    void Renderer::DrawRect(int posX, int posY, int width, int height, const Color &color, bool fill, int thickness) {
        if (fill)
            DrawLine(posX, posY, width, color, height);

        else {
            // Top line
            DrawLine(posX, posY, width, color, thickness);
            // Bottom line
            DrawLine(posX, posY + height - thickness, width, color, thickness);
            // Left line
            DrawLine(posX, posY, thickness, color, height);
            // Right line
            DrawLine(posX + width - thickness, posY, thickness, color, height);
        }
    }

    void Renderer::DrawRect(const IntRect &rect, const Color &color, bool fill) {
        if (fill)
            DrawLine(rect.leftTop.x, rect.leftTop.y, rect.size.x, color, rect.size.y);

        else {
            int posX = rect.leftTop.x;
            int posY = rect.leftTop.y;
            int width = rect.size.x;
            int height = rect.size.y;

            // Top line
            DrawLine(posX, posY, width, color, 1);
            // Bottom line
            DrawLine(posX, posY + height - 1, width, color, 1);
            // Left line
            DrawLine(posX, posY, 1, color, height);
            // Right line
            DrawLine(posX + width - 1, posY, 1, color, height);
        }
    }

    void Renderer::DrawRect2(const IntRect &rect, const Color &color1, const Color &color2) {
        int height = rect.size.y;
        int posX = rect.leftTop.x;
        int posY = rect.leftTop.y;
        int width = rect.size.x;

        ScreenImpl *screen = GetContext()->screen;
        u8 *dst = screen->GetLeftFrameBuffer(posX, posY + height - 1);
        u32 stride = screen->GetStride();
        u32 fmt = screen->GetFormat();

        while (width-- > 0) {
            DrawLineV2(fmt, color1, color2, dst, height);
            dst += stride;
        }
    }

    void Renderer::DrawPixel(int posX, int posY, const Color &color) {
        ScreenImpl *screen = GetContext()->screen;
        PrivColor::ToFramebuffer(screen->GetLeftFrameBuffer(posX, posY), color);
    }

    // Draw Character without background
    void Renderer::DrawCharacter(int c, int posX, int posY, const Color &fg) {
        ScreenImpl *screen = GetContext()->screen;
        u32 stride = screen->GetStride();
        int posXX = posX - 10;
        int posYY = posY;
        c *= 10;
        const u8 *charInFont = font + c;

        for (int yy = 0; yy < 10; ++yy) {
            u8 charPos = *charInFont++;
            u8 *fb = screen->GetLeftFrameBuffer(posX, posY++);

            for (int xx = 6; xx > 0; --xx) {
                if ((charPos >> xx) & 1)
                    PrivColor::ToFramebuffer(fb, fg);

                fb += stride;
            }
        }

        if (screen->Is3DEnabled()) {
            charInFont -= 10;

            for (int yy = 0; yy < 10; ++yy) {
                u8 charPos = *charInFont++;
                u8 *fb = screen->GetRightFrameBuffer(posXX, posYY++);

                for (int xx = 6; xx > 0; --xx) {
                    if ((charPos >> xx) & 1)
                        PrivColor::ToFramebuffer(fb, fg);

                    fb += stride;
                }
            }
        }
    }

    // Draw Character with background
    void Renderer::DrawCharacter(int c, int posX, int posY, const Color &fg, const Color &bg) {
        ScreenImpl *screen = GetContext()->screen;
        u32 stride = screen->GetStride();
        int posXX = posX - 10;
        int posYY = posY;
        c *= 10;
        const u8 *charInFont = font + c;

        for (int yy = 0; yy < 10; ++yy) {
            u8 charPos = *charInFont++;
            u8 *fb = screen->GetLeftFrameBuffer(posX, posY++);

            for (int xx = 6; xx > 0; --xx) {
                PrivColor::ToFramebuffer(fb, (charPos >> xx) & 1 ? fg : bg);
                fb += stride;
            }
        }

        if (screen->Is3DEnabled()) {
            charInFont -= 10;

            for (int yy = 0; yy < 10; ++yy) {
                u8 charPos = *charInFont++;
                u8 *fb = screen->GetRightFrameBuffer(posXX, posYY++);

                for (int xx = 6; xx > 0; --xx) {
                    PrivColor::ToFramebuffer(fb, (charPos >> xx) & 1 ? fg : bg);
                    fb += stride;
                }
            }
        }
    }

    int Renderer::DrawString(const char *str, int posX, int &posY, Color fg) {
        Color bak = fg;

        while (*str) {
            u8 c = *str++;

            if (c == 0x18) {
                fg = bak;
                continue;
            }

            if (c == 0x1B) {
                fg.r = *str++;
                fg.g = *str++;
                fg.b = *str++;
                continue;
            }

            if (c == 0xFF) ///< Lazy fix for 0x18 arrow symbol
                c = 0x18;

            if (c == 0xFE) ///< Lazy fix for 0x1B arrow symbol
                c = 0x1B;

            DrawCharacter(c, posX, posY, fg);
            posX += 6;
        }

        posY += 10;
        return (posY);
    }

    int Renderer::DrawString(const char *str, int posX, int &posY, Color fg, Color bg) {
        ScreenImpl *screen = GetContext()->screen;
        u32 bpp = screen->GetBytesPerPixel();
        Color bak = fg;

        for (int i = 0; i < 2; i++) {
            u8 *fb = screen->GetLeftFrameBuffer(posX + i, posY);

            for (int y = 0; y < 10; y++) {
                PrivColor::ToFramebuffer(fb, bg);
                fb -= bpp;
            }
        }

        if (screen->Is3DEnabled()) {
            for (int i = 0; i < 2; i++) {
                u8 *fb = screen->GetRightFrameBuffer(posX - 10 + i, posY);

                for (int y = 0; y < 10; y++) {
                    PrivColor::ToFramebuffer(fb, bg);
                    fb -= bpp;
                }
            }
        }

        posX += 2;

        while (*str) {
            u8 c = *str++;

            if (c == 0x18) {
                fg = bak;
                continue;
            }

            if (c == 0x1B) {
                fg.r = *str++;
                fg.g = *str++;
                fg.b = *str++;
                continue;
            }

            if (c == 0xFF) ///< Lazy fix for 0x18 arrow symbol
                c = 0x18;

            if (c == 0xFE) ///< Lazy fix for 0x1B arrow symbol
                c = 0x1B;

            DrawCharacter(c, posX, posY, fg, bg);
            posX += 6;
        }

        posY += 10;
        return (posY);
    }

    u32 Renderer::LinuxFontSize(const char *str) {
        u32 size = 0;

        for (; *str; str++) {
            char c = *str;

            if (c == 0x1B)
                str += 3;

            else if (c != 0x18)
                size += 6;
        }

        return (size);
    }

    extern "C" CFNT_s* g_sharedFont;
    extern "C" int g_charPerSheet;

    void Renderer::FontCalcGlyphPos(fontGlyphPos_s *out, charWidthInfo_s **cwout, int glyphIndex, float scaleX, float scaleY) {
        FINF_s* finf = &g_sharedFont->finf;
        TGLP_s* tglp = finf->tglp;
        charWidthInfo_s *cwi = fontGetCharWidthInfo(nullptr, glyphIndex);
        *cwout = cwi;

        int sheetId = glyphIndex / g_charPerSheet;
        int glInSheet = glyphIndex % g_charPerSheet;
        out->sheetIndex = sheetId;
        out->xOffset = scaleX * cwi->left;
        out->xAdvance = scaleX * cwi->charWidth;
        out->width = scaleX * cwi->glyphWidth;

        int lineId = glInSheet / tglp->nRows;
        int rowId = glInSheet % tglp->nRows;

        float tp = (float)(rowId*(tglp->cellWidth+1)+1);
        float tx = (float)(tp / tglp->sheetWidth)   ;
        float ty = 1.0f - (float)((lineId+1)*(tglp->cellHeight+1)+1) / tglp->sheetHeight;
        float tw = (float)cwi->glyphWidth / tglp->sheetWidth;
        float th = (float)tglp->cellHeight / tglp->sheetHeight;
        out->texcoord.left = tx;
        out->texcoord.top = ty;
        out->texcoord.right = tx+tw;
        out->texcoord.bottom = ty + th;
    }

    float Renderer::GetTextSize(const char *text) {
        if (!text)
            return (0.0f);

        float w = 0.f;
        u8 *c = (u8*)text;

        // Skip UTF8 sig
        if (c[0] == 0xEF && c[1] == 0xBB && c[2] == 0xBF)
            c += 3;

        while (*c == '\n')
            c++;

        do {
            if (!*c)
                break;

            if (*c == '\r' || *c == '\n') {
                c++;
                continue;
            }

            if (*c == 0x18) {
                c++;
                continue;
            }

            if (*c == 0x1B) {
                c += 4;
                continue;
            }

            if (*c == 0x11) {
                c++;
                u16 control = *(u16*)c;
                c += 2;

                if (control & 0x8000) {
                    u16 skipToX = control & 0x1FF;

                    if (skipToX > w)
                        w = skipToX;
                }

                continue;
            }

            Glyph *glyph = Font::GetGlyph(c);

            if (glyph == nullptr)
                break;

            w += glyph->Width();
        }

        while (true);

        return (w);
    }


    int Renderer::GetLineCount(const char *text, float maxWidth) {
        if (!text)
            return (0.0f);

        int lineCount = 1;
        float w = 0.0f;
        u8 *c = (u8*)text;

        // Skip UTF8 sig
        if (c[0] == 0xEF && c[1] == 0xBB && c[2] == 0xBF)
            c += 3;

        while (*c) {
            if (*c == '\r') {
                c++;
                continue;
            }

            if (*c == '\n') {
                lineCount++;
                w = 0.f;
                c++;
                continue;
            }

            if (*c == 0x18) {
                c++;
                continue;
            }

            if (*c == 0x1B) {
                c += 4;
                continue;
            }

            if (*c == 0x11) {
                c++;
                u16 control = *(u16*)c;
                c += 2;

                if (control & 0x8000) {
                    u16 skipToX = control & 0x1FF;

                    if (skipToX > w && skipToX < maxWidth)
                        w = skipToX;
                }

                continue;
            }

            Glyph *glyph = Font::GetGlyph(c);

            if (glyph == nullptr)
                break;

            float gSize = glyph->Width();

            if (w + gSize > maxWidth) {
                lineCount++;
                w = gSize;
            }

            else w += gSize;
        }

        return (lineCount);
    }

    void Renderer::GetTextInfos(const char *text, int &lineCount, float &lineMaxWidth, float maxWidth) {
        lineCount = 0;
        lineMaxWidth = 0.f;

        if (!text || !*text)
            return;

        lineCount = 1;
        float w = 0.0f;
        u8 *c = (u8*)text;

        // Skip UTF8 sig
        if (c[0] == 0xEF && c[1] == 0xBB && c[2] == 0xBF)
            c += 3;

        while (*c) {
            if (*c == '\n') {
                lineCount++;

                if (w > lineMaxWidth)
                    lineMaxWidth = w;

                w = 0.f;
                c++;
                continue;
            }

            if (*c == 0x18) {
                c++;
                continue;
            }

            if (*c == 0x1B) {
                c += 4;
                continue;
            }

            if (*c == 0x11) {
                c++;
                u16 control = *(u16*)c;
                c += 2;

                if (control & 0x8000) {
                    u16 skipToX = control & 0x1FF;

                    if (skipToX > w && skipToX < maxWidth)
                        w = skipToX;
                }

                continue;
            }

            Glyph *glyph = Font::GetGlyph(c);

            if (glyph == nullptr)
                break;

            float gSize = glyph->Width();

            if (w + gSize > maxWidth) {
                lineCount++;

                if (w > lineMaxWidth)
                    lineMaxWidth = w;

                w = gSize;
            }

            else w += gSize;
        }

        if (w > lineMaxWidth)
            lineMaxWidth = w;
    }

    void Renderer::DrawSysCheckBox(const char *str, int posX, int &posY, int xLimits, Color color, bool isChecked, float offset) {
        Icon::DrawCheckBox(posX, posY, isChecked);
        posX += 20;
        DrawSysString(str, posX, posY, xLimits, color, offset);
        posY += 1;
    }

    void Renderer::DrawSysFolder(const char *str, int posX, int &posY, int xLimits, Color color, float offset) {
        Icon::DrawFolder(posX, posY);
        posX += 20;
        DrawSysString(str, posX, posY, xLimits, color, offset);
        posY += 1;
    }

    int Renderer::DrawGlyph(Glyph *glyph, int posX, int posY, Color color, u32 flags) {
        return DrawGlyph(GetContext()->screen, glyph, posX, posY, color, flags);
    }

    int Renderer::DrawGlyph(ScreenImpl *screen, Glyph *glyph, int posX, int posY, Color color, u32 flags) {
        if (!screen || !glyph)
            return posY;

        posX += glyph->xOffset;
        u32 stride = screen->_stride;
        u32 bpp = screen->_bytesPerPixel;
        u8 *data = glyph->glyph;
        u8 *left = static_cast<u8*>(screen->GetLeftFrameBuffer(posX, posY));
        u8 *fb = left;
        u8 italicOffset = (flags & Render::FontDrawMode::ITALIC) ? 3 : 0;
        u32 lineCount = 0;

        for (int i = 0; i < 208; i++) {
            if (i != 0 && i % 13 == 0) {
                if ((lineCount % 4) == 0 && flags &Render::FontDrawMode::ITALIC)
                    italicOffset--;

                lineCount++;
                left -= bpp;
                fb = left;
            }

            u32 alpha = data[i];

            // Don't waste time on pixels which are only 5% visible
            for (int j = 0; (alpha > 12) && j < ((flags & Render::FontDrawMode::BOLD) ? 2 : 1); j++) {
                color.a = alpha;
                Color &&l = PrivColor::FromFramebuffer(fb + stride * j + italicOffset * stride);
                Color &&c = l.Blend(color, Color::BlendMode::Alpha);
                PrivColor::ToFramebuffer(fb + stride * j + italicOffset * stride, c);
            }

            fb += stride;
        }

        return (posX + glyph->xAdvance);
    }

    int Renderer::DrawGlyph(ScreenImpl *screen, Glyph *glyph, int posX, int posY, float &offset, Color color, u32 flags) {
        if (!screen || !glyph)
            return posY;

        posX += glyph->xOffset;
        u32 stride = screen->_stride;
        u32 bpp = screen->_bytesPerPixel;
        u8 *data = glyph->glyph;
        u8 *left = static_cast<u8*>(screen->GetLeftFrameBuffer(posX, posY));
        u8 *fb = left;
        u8 italicOffset = (flags & Render::FontDrawMode::ITALIC) ? 3 : 0;
        u32 lineCount = 0;

        for (int i = static_cast<int>(offset); i < 208; i++) {
            if (i != 0 && i % 13 == 0) {
                if (offset)
                    i += offset;

                if ((lineCount % 4) == 0 && flags & Render::FontDrawMode::ITALIC)
                    italicOffset--;

                lineCount++;
                left -= bpp;
                fb = left;
            }

            u32 alpha = data[i];

            // Don't waste time on pixels which are only 5% visible
            for (int j = 0; (alpha > 12) && j < ((flags & Render::FontDrawMode::BOLD) ? 2 : 1); j++) {
                color.a = alpha;
                Color &&l = PrivColor::FromFramebuffer(fb + stride * j + italicOffset * stride);
                Color &&c = l.Blend(color, Color::BlendMode::Alpha);
                PrivColor::ToFramebuffer(fb + stride * j + italicOffset * stride, c);
            }

            fb += stride;
        }

        if (offset > 0.f) {
            posX -= offset;
            offset = 0;
        }

        return (posX + glyph->xAdvance);
    }

    int Renderer::DrawSysStringReturn(const unsigned char *stri, int posX, int &posY, int xLimits, Color color, int maxY, u32 flags) {
        // Check for a valid pointer
        if (!(stri && *stri))
            return (posX);

        int lineCount = 1;
        u8 *str = const_cast<u8*>(stri);
        int x = posX;
        int underLineStart = -1, strikeLineStart = -1;
        ScreenImpl *screen = GetContext()->screen;
        void (*lineDrawer)(int posX, int posY, int width, const Color &color, int height) = Renderer::DrawLine;

        if (!screen)
            return posY;

        xLimits = min(xLimits, (GetContext()->target == TOP ? 400 : 320));

        // Skip UTF8 sig
        if (str[0] == 0xEF && str[1] == 0xBB && str[2] == 0xBF)
            str += 3;

        do {
            if (posY >= maxY)
                break;

            u8 c = *str;

            if (c == '\r')
                str++;

            if (c == '\n') {
                if (flags & Render::FontDrawMode::UNDERLINE) {
                    if (underLineStart != x)
                        lineDrawer(underLineStart, posY + 15, x - underLineStart, color, 1);

                    underLineStart = posX;
                }

                if (flags & Render::FontDrawMode::STRIKETHROUGH) {
                    if (strikeLineStart != x)
                        lineDrawer(strikeLineStart, posY + 9, x - strikeLineStart, color, 1);

                    strikeLineStart = posX;
                }

                x = posX;
                lineCount++;
                posY += 16;
                str++;
                continue;
            }

            if (c == 0x18) {
                color = Preferences::Settings.MainTextColor;
                str++;
                continue;
            }

            if (c == 0x1B) {
                str++;
                color.r = *str++;
                color.g = *str++;
                color.b = *str++;
                continue;
            }

            if (c == 0x11) {
                str++;
                u16 control = *(u16*)str;
                str += 2;

                if (control & 0x8000) {
                    u16 skipToX = control & 0x1FF;

                    if (skipToX > x && skipToX < xLimits) {
                        if (underLineStart == posX && x == posX) // Fix for aligned text after newline
                            underLineStart = skipToX;

                        if (strikeLineStart == posX && x == posX) // Fix for aligned text after newline
                            strikeLineStart = skipToX;

                        x = skipToX;
                    }
                }

                else if (control & 0x4000) {
                    u32 prevFlags = flags;
                    flags ^= (control & 0x7F);

                    if (flags & Render::LINEDOTTED)
                        lineDrawer = DrawStippledLine;

                    else lineDrawer = DrawLine;

                    if ((prevFlags & Render::FontDrawMode::UNDERLINE) != (flags & Render::FontDrawMode::UNDERLINE)) {
                        bool startLine = flags & Render::FontDrawMode::UNDERLINE;

                        if (startLine)
                            underLineStart = x;

                        else {
                            if (underLineStart != x)
                                lineDrawer(underLineStart, posY + 15, x - underLineStart, color, 1);

                            underLineStart = -1;
                        }

                    }

                    if ((prevFlags & Render::FontDrawMode::STRIKETHROUGH) != (flags & Render::FontDrawMode::STRIKETHROUGH)) {
                        bool startLine = flags & Render::FontDrawMode::STRIKETHROUGH;

                        if (startLine)
                            strikeLineStart = x;

                        else {
                            if (strikeLineStart != x)
                                lineDrawer(strikeLineStart, posY + 9, x - strikeLineStart, color, 1);

                            strikeLineStart = -1;
                        }

                    }
                }

                continue;
            }

            Glyph *glyph = Font::GetGlyph(str);

            if (glyph == nullptr)
                break;

            if (x + glyph->Width() >= xLimits) {
                if (flags & Render::FontDrawMode::UNDERLINE) {
                    if (underLineStart != x)
                        lineDrawer(underLineStart, posY + 15, x - underLineStart, color, 1);

                    underLineStart = posX;
                }

                if (flags & Render::FontDrawMode::STRIKETHROUGH) {
                    if (strikeLineStart != x)
                        lineDrawer(strikeLineStart, posY + 9, x - strikeLineStart, color, 1);

                    strikeLineStart = posX;
                }

                x = posX;
                lineCount++;
                posY += 16;
            }

            x = DrawGlyph(screen, glyph, x, posY, color, flags);

        }

        while (*str);

        if (posY < maxY && flags & Render::FontDrawMode::UNDERLINE) {
            if (underLineStart != x)
                lineDrawer(underLineStart, posY + 15, x - underLineStart, color, 1);
        }

        if (posY < maxY && flags & Render::FontDrawMode::STRIKETHROUGH) {
            if (strikeLineStart != x)
                lineDrawer(strikeLineStart, posY + 9, x - strikeLineStart, color, 1);
        }

        posY += 16;
        return (x);
    }

    namespace RendererPriv {
        Color g_customColor;
    }

    int Renderer::DrawSysString(const char *stri, int posX, int &posY, int xLimits, Color color, float offset, const char *end, u32 flags) {
        Glyph *glyph;
        int x = posX;
        u8 *str = (u8*)stri;
        int underLineStart = -1, strikeLineStart = -1;
        void (*lineDrawer)(int posX, int posY, int width, const Color &color, int height) = DrawLine;
        ScreenImpl *screen = GetContext()->screen;

        if (!(str && *str) || !screen)
            return (x);

        xLimits = min(xLimits, (GetContext()->target == TOP ? 400 : 320));

        // Skip UTF8 sig
        if (str[0] == 0xEF && str[1] == 0xBB && str[2] == 0xBF)
            str += 3;

        do {
            u8 c = *str;

            if (x >= xLimits || str == (u8*)end)
                break;

            if (c == '\n' || c == '\r') {
                str++;
                continue;
            }

            if (c == 0x18) {
                RendererPriv::g_customColor = color = Preferences::Settings.MainTextColor;
                str++;
                continue;
            }

            if (c == 0x1B) {
                str++;
                color.r = *str++;
                color.g = *str++;
                color.b = *str++;
                RendererPriv::g_customColor = color;
                continue;
            }

            if (c == 0x11) {
                str++;
                u16 control = *(u16*)str;
                str += 2;

                if (control & 0x8000) {
                    u16 skipToX = control & 0x1FF;

                    if (skipToX > x && skipToX < xLimits)
                        x = skipToX;
                }

                else if (control & 0x4000) {
                    u32 prevFlags = flags;
                    flags ^= (control & 0x7F);

                    if (flags & Render::LINEDOTTED)
                        lineDrawer = DrawStippledLine;

                    else lineDrawer = DrawLine;

                    if ((prevFlags & Render::FontDrawMode::UNDERLINE) != (flags & Render::FontDrawMode::UNDERLINE)) {
                        bool startLine = flags & Render::FontDrawMode::UNDERLINE;

                        if (startLine)
                            underLineStart = x;

                        else {
                            if (underLineStart != x)
                                lineDrawer(underLineStart, posY + 15, x - underLineStart, color, 1);

                            underLineStart = -1;
                        }

                    }

                    if ((prevFlags & Render::FontDrawMode::STRIKETHROUGH) != (flags & Render::FontDrawMode::STRIKETHROUGH)) {
                        bool startLine = flags & Render::FontDrawMode::STRIKETHROUGH;

                        if (startLine)
                            strikeLineStart = x;

                        else {
                            if (strikeLineStart != x)
                                lineDrawer(strikeLineStart, posY + 9, x - strikeLineStart, color, 1);

                            strikeLineStart = -1;
                        }

                    }
                }

                continue;
            }

            if (posY >= 240)
                break;

            glyph = Font::GetGlyph(str);

            if (glyph == nullptr)
                break;

            float gWidth = glyph->Width();

            if (x + gWidth > xLimits)
                break;

            if (offset >= gWidth) {
                offset -= (gWidth);
                continue;
            }

            x = DrawGlyph(screen, glyph, x, posY, offset, color, flags);
        }

        while (*str);

        if (flags & Render::FontDrawMode::UNDERLINE) {
            if (underLineStart != x)
                lineDrawer(underLineStart, posY + 15, x - underLineStart, color, 1);
        }

        if (flags & Render::FontDrawMode::STRIKETHROUGH) {
            if (strikeLineStart != x)
                lineDrawer(strikeLineStart, posY + 9, x - strikeLineStart, color, 1);
        }

        posY += 16;
        return (x);
    }
}