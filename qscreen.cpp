﻿#include "stdafx.h"
#include <QtGui>
#include <QMenu>
#include "qscreen.h"
#include "mainwindow.h"
#include "Emulator.h"
#include "emubase/Emubase.h"


//////////////////////////////////////////////////////////////////////
// Colors

/*
yrgb  R   G   B  0xRRGGBB
0000 000 000 000 0x000000
0001 000 000 128 0x000080
0010 000 128 000 0x008000
0011 000 128 128 0x008080
0100 128 000 000 0x800000
0101 128 000 128 0x800080
0110 128 128 000 0x808000
0111 128 128 128 0x808080
1000 000 000 000 0x000000
1001 000 000 255 0x0000FF
1010 000 255 000 0x00FF00
1011 000 255 255 0x00FFFF
1100 255 000 000 0xFF0000
1101 255 000 255 0xFF00FF
1110 255 255 000 0xFFFF00
1111 255 255 255 0xFFFFFF
*/

// Table for color conversion yrgb (4 bits) -> DWORD (32 bits)
const quint32 ScreenView_StandardRGBColors[16 * 8] =
{
    0xFF000000, 0xFF000080, 0xFF008000, 0xFF008080, 0xFF800000, 0xFF800080, 0xFF808000, 0xFF808080,
    0xFF000000, 0xFF0000FF, 0xFF00FF00, 0xFF00FFFF, 0xFFFF0000, 0xFFFF00FF, 0xFFFFFF00, 0xFFFFFFFF,
    0xFF000000, 0xFF000060, 0xFF008000, 0xFF008060, 0xFF800000, 0xFF800060, 0xFF808000, 0xFF808060,
    0xFF000000, 0xFF0000DF, 0xFF00FF00, 0xFF00FFDF, 0xFFFF0000, 0xFFFF00DF, 0xFFFFFF00, 0xFFFFFFDF,
    0xFF000000, 0xFF000080, 0xFF006000, 0xFF006080, 0xFF800000, 0xFF800080, 0xFF806000, 0xFF806080,
    0xFF000000, 0xFF0000FF, 0xFF00DF00, 0xFF00DFFF, 0xFFFF0000, 0xFFFF00FF, 0xFFFFDF00, 0xFFFFDFFF,
    0xFF000000, 0xFF000060, 0xFF006000, 0xFF006060, 0xFF800000, 0xFF800060, 0xFF806000, 0xFF806060,
    0xFF000000, 0xFF0000DF, 0xFF00DF00, 0xFF00DFDF, 0xFFFF0000, 0xFFFF00DF, 0xFFFFDF00, 0xFFFFDFDF,
    0xFF000000, 0xFF000080, 0xFF008000, 0xFF008080, 0xFF600000, 0xFF600080, 0xFF608000, 0xFF608080,
    0xFF000000, 0xFF0000FF, 0xFF00FF00, 0xFF00FFFF, 0xFFDF0000, 0xFFDF00FF, 0xFFDFFF00, 0xFFDFFFFF,
    0xFF000000, 0xFF000060, 0xFF008000, 0xFF008060, 0xFF600000, 0xFF600060, 0xFF608000, 0xFF608060,
    0xFF000000, 0xFF0000DF, 0xFF00FF00, 0xFF00FFDF, 0xFFDF0000, 0xFFDF00DF, 0xFFDFFF00, 0xFFDFFFDF,
    0xFF000000, 0xFF000080, 0xFF006000, 0xFF006080, 0xFF600000, 0xFF600080, 0xFF606000, 0xFF606080,
    0xFF000000, 0xFF0000FF, 0xFF00DF00, 0xFF00DFFF, 0xFFDF0000, 0xFFDF00FF, 0xFFDFDF00, 0xFFDFDFFF,
    0xFF000000, 0xFF000060, 0xFF006000, 0xFF006060, 0xFF600000, 0xFF600060, 0xFF606000, 0xFF606060,
    0xFF000000, 0xFF0000DF, 0xFF00DF00, 0xFF00DFDF, 0xFFDF0000, 0xFFDF00DF, 0xFFDFDF00, 0xFFDFDFDF,
};
const quint32 ScreenView_StandardGRBColors[16 * 8] =
{
    0xFF000000, 0xFF000080, 0xFF800000, 0xFF800080, 0xFF008000, 0xFf008080, 0xFF808000, 0xFF808080,
    0xFF000000, 0xFF0000FF, 0xFFFF0000, 0xFFFF00FF, 0xFF00FF00, 0xFF00FFFF, 0xFFFFFF00, 0xFFFFFFFF,
    0xFF000000, 0xFF000060, 0xFF800000, 0xFF800060, 0xFF008000, 0xFF008060, 0xFF808000, 0xFF808060,
    0xFF000000, 0xFF0000DF, 0xFFFF0000, 0xFFFF00DF, 0xFF00FF00, 0xFF00FFDF, 0xFFFFFF00, 0xFFFFFFDF,
    0xFF000000, 0xFF000080, 0xFF600000, 0xFF600080, 0xFF008000, 0xFF008080, 0xFF608000, 0xFF608080,
    0xFF000000, 0xFF0000FF, 0xFFDF0000, 0xFFDF00FF, 0xFF00FF00, 0xFF00FFFF, 0xFFDFFF00, 0xFFDFFFFF,
    0xFF000000, 0xFF000060, 0xFF600000, 0xFF600060, 0xFF008000, 0xFF008060, 0xFF608000, 0xFF608060,
    0xFF000000, 0xFF0000DF, 0xFFDF0000, 0xFFDF00DF, 0xFF00FF00, 0xFF00FFDF, 0xFFDFFF00, 0xFFDFFFDF,
    0xFF000000, 0xFF000080, 0xFF800000, 0xFF800080, 0xFF006000, 0xFF006080, 0xFF806000, 0xFF806080,
    0xFF000000, 0xFF0000FF, 0xFFFF0000, 0xFFFF00FF, 0xFF00DF00, 0xFF00DFFF, 0xFFFFDF00, 0xFFFFDFFF,
    0xFF000000, 0xFF000060, 0xFF800000, 0xFF800060, 0xFF006000, 0xFF006060, 0xFF806000, 0xFF806060,
    0xFF000000, 0xFF0000DF, 0xFFFF0000, 0xFFFF00DF, 0xFF00DF00, 0xFF00DFDF, 0xFFFFDF00, 0xFFFFDFDF,
    0xFF000000, 0xFF000080, 0xFF600000, 0xFF600080, 0xFF006000, 0xFF006080, 0xFF606000, 0xFF606080,
    0xFF000000, 0xFF0000FF, 0xFFDF0000, 0xFFDF00FF, 0xFF00DF00, 0xFF00DFFF, 0xFFDFDF00, 0xFFDFDFFF,
    0xFF000000, 0xFF000060, 0xFF600000, 0xFF600060, 0xFF006000, 0xFF006060, 0xFF606000, 0xFF606060,
    0xFF000000, 0xFF0000DF, 0xFFDF0000, 0xFFDF00DF, 0xFF00DF00, 0xFF00DFDF, 0xFFDFDF00, 0xFFDFDFDF,
};
// Table for color conversion, gray (black and white) display
const quint32 ScreenView_GrayColors[16 * 8] =
{
    0xFF000000, 0xFF242424, 0xFF484848, 0xFF6C6C6C, 0xFF909090, 0xFFB4B4B4, 0xFFD8D8D8, 0xFFFFFFFF,
    0xFF000000, 0xFF242424, 0xFF484848, 0xFF6C6C6C, 0xFF909090, 0xFFB4B4B4, 0xFFD8D8D8, 0xFFFFFFFF,
    0xFF000000, 0xFF242424, 0xFF484848, 0xFF6C6C6C, 0xFF909090, 0xFFB4B4B4, 0xFFD8D8D8, 0xFFFFFFFF,
    0xFF000000, 0xFF242424, 0xFF484848, 0xFF6C6C6C, 0xFF909090, 0xFFB4B4B4, 0xFFD8D8D8, 0xFFFFFFFF,
    0xFF000000, 0xFF242424, 0xFF484848, 0xFF6C6C6C, 0xFF909090, 0xFFB4B4B4, 0xFFD8D8D8, 0xFFFFFFFF,
    0xFF000000, 0xFF242424, 0xFF484848, 0xFF6C6C6C, 0xFF909090, 0xFFB4B4B4, 0xFFD8D8D8, 0xFFFFFFFF,
    0xFF000000, 0xFF242424, 0xFF484848, 0xFF6C6C6C, 0xFF909090, 0xFFB4B4B4, 0xFFD8D8D8, 0xFFFFFFFF,
    0xFF000000, 0xFF242424, 0xFF484848, 0xFF6C6C6C, 0xFF909090, 0xFFB4B4B4, 0xFFD8D8D8, 0xFFFFFFFF,
    0xFF000000, 0xFF242424, 0xFF484848, 0xFF6C6C6C, 0xFF909090, 0xFFB4B4B4, 0xFFD8D8D8, 0xFFFFFFFF,
    0xFF000000, 0xFF242424, 0xFF484848, 0xFF6C6C6C, 0xFF909090, 0xFFB4B4B4, 0xFFD8D8D8, 0xFFFFFFFF,
    0xFF000000, 0xFF242424, 0xFF484848, 0xFF6C6C6C, 0xFF909090, 0xFFB4B4B4, 0xFFD8D8D8, 0xFFFFFFFF,
    0xFF000000, 0xFF242424, 0xFF484848, 0xFF6C6C6C, 0xFF909090, 0xFFB4B4B4, 0xFFD8D8D8, 0xFFFFFFFF,
    0xFF000000, 0xFF242424, 0xFF484848, 0xFF6C6C6C, 0xFF909090, 0xFFB4B4B4, 0xFFD8D8D8, 0xFFFFFFFF,
    0xFF000000, 0xFF242424, 0xFF484848, 0xFF6C6C6C, 0xFF909090, 0xFFB4B4B4, 0xFFD8D8D8, 0xFFFFFFFF,
    0xFF000000, 0xFF242424, 0xFF484848, 0xFF6C6C6C, 0xFF909090, 0xFFB4B4B4, 0xFFD8D8D8, 0xFFFFFFFF,
    0xFF000000, 0xFF242424, 0xFF484848, 0xFF6C6C6C, 0xFF909090, 0xFFB4B4B4, 0xFFD8D8D8, 0xFFFFFFFF,
};


//////////////////////////////////////////////////////////////////////

#define AVERAGERGB(a, b)  ( (((a) & 0xfefefeffUL) + ((b) & 0xfefefeffUL)) >> 1 )

// Upscale screen from height 288 to 432
static void UpscaleScreen(void* pImageBits)
{
    quint32* pbits = static_cast<quint32*>(pImageBits);
    quint8* pbits8 = static_cast<quint8*>(pImageBits);
    int ukncline = 287;
    for (int line = 431; line > 0; line--)
    {
        quint32* pdest = pbits + line * UKNC_SCREEN_WIDTH;
        if (line % 3 == 1)
        {
            quint8* psrc1 = pbits8 + ukncline * UKNC_SCREEN_WIDTH * 4;
            quint8* psrc2 = pbits8 + (ukncline + 1) * UKNC_SCREEN_WIDTH * 4;
            quint8* pdst1 = reinterpret_cast<quint8*>(pdest);
            for (int i = 0; i < UKNC_SCREEN_WIDTH * 4; i++)
            {
                if (i % 4 == 3)
                    *pdst1 = 0;
                else
                    *pdst1 = (quint8)((((quint16) * psrc1) + ((quint16) * psrc2)) / 2);
                psrc1++;  psrc2++;  pdst1++;
            }
        }
        else
        {
            quint32* psrc = pbits + ukncline * UKNC_SCREEN_WIDTH;
            memcpy(pdest, psrc, UKNC_SCREEN_WIDTH * 4);
            ukncline--;
        }
    }
}

// Upscale screen from height 288 to 576 with "interlaced" effect
static void UpscaleScreen2(void* pImageBits)
{
    quint32* pbits = static_cast<quint32*>(pImageBits);
    for (int ukncline = 287; ukncline >= 0; ukncline--)
    {
        quint32* psrc = pbits + ukncline * UKNC_SCREEN_WIDTH;
        quint32* pdest = pbits + (ukncline * 2) * UKNC_SCREEN_WIDTH;
        memcpy(pdest, psrc, UKNC_SCREEN_WIDTH * 4);

        pdest += UKNC_SCREEN_WIDTH;
        memset(pdest, 0, UKNC_SCREEN_WIDTH * 4);
    }
}

// Upscale screen from height 288 to 576
static void UpscaleScreen2d(void* pImageBits)
{
    quint32* pbits = static_cast<quint32*>(pImageBits);
    for (int ukncline = 287; ukncline >= 0; ukncline--)
    {
        quint32* psrc = pbits + ukncline * UKNC_SCREEN_WIDTH;
        quint32* pdest = pbits + (ukncline * 2) * UKNC_SCREEN_WIDTH;
        memcpy(pdest, psrc, UKNC_SCREEN_WIDTH * 4);

        pdest += UKNC_SCREEN_WIDTH;
        memcpy(pdest, psrc, UKNC_SCREEN_WIDTH * 4);
    }
}

// Upscale screen width 640->960, height 288->576 with "interlaced" effect
static void UpscaleScreen3(void* pImageBits)
{
    quint32* pbits = static_cast<quint32*>(pImageBits);
    for (int ukncline = 287; ukncline >= 0; ukncline--)
    {
        quint32* psrc = pbits + ukncline * UKNC_SCREEN_WIDTH;
        psrc += UKNC_SCREEN_WIDTH - 1;
        quint32* pdest = pbits + (ukncline * 2) * 960;
        pdest += 960 - 1;
        for (int i = 0; i < UKNC_SCREEN_WIDTH / 2; i++)
        {
            quint32 c1 = *psrc;  psrc--;
            quint32 c2 = *psrc;  psrc--;
            quint32 c12 =
                (((c1 & 0xff) + (c2 & 0xff)) >> 1) |
                ((((c1 & 0xff00) + (c2 & 0xff00)) >> 1) & 0xff00) |
                ((((c1 & 0xff0000) + (c2 & 0xff0000)) >> 1) & 0xff0000);
            *pdest = c1;  pdest--;
            *pdest = c12; pdest--;
            *pdest = c2;  pdest--;
        }

        pdest += 960;
        memset(pdest, 0, 960 * 4);
    }
}

// Upscale screen width 640->960, height 288->720
static void UpscaleScreen4(void* pImageBits)
{
    quint32* pbits = static_cast<quint32*>(pImageBits);
    for (int ukncline = 0; ukncline < 288; ukncline += 2)
    {
        quint32* psrc1 = pbits + (286 - ukncline) * UKNC_SCREEN_WIDTH;
        quint32* psrc2 = psrc1 + UKNC_SCREEN_WIDTH;
        quint32* pdest0 = pbits + (286 - ukncline) / 2 * 5 * 960;
        quint32* pdest1 = pdest0 + 960;
        quint32* pdest2 = pdest1 + 960;
        quint32* pdest3 = pdest2 + 960;
        quint32* pdest4 = pdest3 + 960;
        for (int i = 0; i < UKNC_SCREEN_WIDTH / 2; i++)
        {
            quint32 c1a = *(psrc1++);  quint32 c1b = *(psrc1++);
            quint32 c2a = *(psrc2++);  quint32 c2b = *(psrc2++);
            quint32 c1 = AVERAGERGB(c1a, c1b);
            quint32 c2 = AVERAGERGB(c2a, c2b);
            quint32 ca = AVERAGERGB(c1a, c2a);
            quint32 cb = AVERAGERGB(c1b, c2b);
            quint32 c  = AVERAGERGB(ca,  cb);
            (*pdest0++) = c1a;  (*pdest0++) = c1;  (*pdest0++) = c1b;
            (*pdest1++) = c1a;  (*pdest1++) = c1;  (*pdest1++) = c1b;
            (*pdest2++) = ca;   (*pdest2++) = c;   (*pdest2++) = cb;
            (*pdest3++) = c2a;  (*pdest3++) = c2;  (*pdest3++) = c2b;
            (*pdest4++) = c2a;  (*pdest4++) = c2;  (*pdest4++) = c2b;
        }
    }
}

// Upscale screen width 640->1120 (x1.75), height 288->864 (x3) with "interlaced" effect
static void UpscaleScreen175(void* pImageBits)
{
    quint32* pbits = static_cast<quint32*>(pImageBits);
    for (int ukncline = 287; ukncline >= 0; ukncline--)
    {
        quint32* psrc = pbits + ukncline * UKNC_SCREEN_WIDTH;
        quint32* pdest1 = pbits + (ukncline * 3) * 1120;
        quint32* pdest2 = pdest1 + 1120;
        quint32* pdest3 = pdest2 + 1120;
        for (int i = 0; i < UKNC_SCREEN_WIDTH / 4; i++)
        {
            quint32 c1 = *(psrc++);
            quint32 c2 = *(psrc++);
            quint32 c3 = *(psrc++);
            quint32 c4 = *(psrc++);

            *(pdest1++) = *(pdest2++) = c1;
            *(pdest1++) = *(pdest2++) = AVERAGERGB(c1, c2);
            *(pdest1++) = *(pdest2++) = c2;
            *(pdest1++) = *(pdest2++) = AVERAGERGB(c2, c3);
            *(pdest1++) = *(pdest2++) = c3;
            *(pdest1++) = *(pdest2++) = AVERAGERGB(c3, c4);
            *(pdest1++) = *(pdest2++) = c4;
        }

        memset(pdest3, 0, 1120 * 4);
    }
}

// Upscale screen width 640->1280, height 288->864 with "interlaced" effect
static void UpscaleScreen5(void* pImageBits)
{
    quint32* pbits = static_cast<quint32*>(pImageBits);
    for (int ukncline = 287; ukncline >= 0; ukncline--)
    {
        quint32* psrc = pbits + ukncline * UKNC_SCREEN_WIDTH;
        quint32* pdest = pbits + (ukncline * 3) * 1280;
        psrc += UKNC_SCREEN_WIDTH - 1;
        pdest += 1280 - 1;
        quint32* pdest2 = pdest + 1280;
        quint32* pdest3 = pdest2 + 1280;
        for (int i = 0; i < UKNC_SCREEN_WIDTH; i++)
        {
            quint32 color = *psrc;  psrc--;
            *pdest = color;  pdest--;
            *pdest = color;  pdest--;
            *pdest2 = color;  pdest2--;
            *pdest2 = color;  pdest2--;
            *pdest3 = 0;  pdest3--;
            *pdest3 = 0;  pdest3--;
        }
    }
}


//////////////////////////////////////////////////////////////////////


QEmulatorScreen::QEmulatorScreen(QWidget *parent) :
    QWidget(parent), m_image(nullptr)
{
    setFocusPolicy(Qt::StrongFocus);

    m_image = nullptr;
    m_mode = RGBScreen;
    m_sizeMode = RegularScreen;

    createDisplay();
}

QEmulatorScreen::~QEmulatorScreen()
{
    delete m_image;
}

void QEmulatorScreen::setMode(ScreenViewMode mode)
{
    m_mode = mode;
}

void QEmulatorScreen::setSizeMode(ScreenSizeMode mode)
{
    if (m_sizeMode == mode) return;

    m_sizeMode = mode;

    createDisplay();
}

QImage QEmulatorScreen::getScreenshot()
{
    QImage image(*m_image);
    return image;
}

void QEmulatorScreen::createDisplay()
{
    if (m_image != nullptr)
    {
        delete m_image;
        m_image = nullptr;
    }

    int cxScreenWidth = UKNC_SCREEN_WIDTH;
    int cyScreenHeight = UKNC_SCREEN_HEIGHT;
    if (m_sizeMode == DoubleInterlacedScreen || m_sizeMode == DoubleScreen)
        cyScreenHeight = UKNC_SCREEN_HEIGHT * 2;
    else if (m_sizeMode == UpscaledScreen)
        cyScreenHeight = 432;
    else if (m_sizeMode == UpscaledScreen3)
    {
        cxScreenWidth = 960;
        cyScreenHeight = UKNC_SCREEN_HEIGHT * 2;
    }
    else if (m_sizeMode == UpscaledScreen4)
    {
        cxScreenWidth = 960;
        cyScreenHeight = 720;
    }
    else if (m_sizeMode == UpscaledScreen175)
    {
        cxScreenWidth = 1120;
        cyScreenHeight = UKNC_SCREEN_HEIGHT * 3;
    }
    else if (m_sizeMode == UpscaledScreen5)
    {
        cxScreenWidth = UKNC_SCREEN_WIDTH * 2;
        cyScreenHeight = UKNC_SCREEN_HEIGHT * 3;
    }

    m_image = new QImage(cxScreenWidth, cyScreenHeight, QImage::Format_RGB32);

    setMinimumSize(cxScreenWidth, cyScreenHeight);
    setMaximumSize(cxScreenWidth + 100, cyScreenHeight + 20);
}

void QEmulatorScreen::paintEvent(QPaintEvent * /*event*/)
{
    const quint32* colors;
    switch (m_mode)
    {
    case RGBScreen:
        colors = ScreenView_StandardRGBColors; break;
    case GrayScreen:
        colors = ScreenView_GrayColors; break;
    default:
        colors = ScreenView_StandardGRBColors; break;
    }

    Emulator_PrepareScreenRGB32(m_image->bits(), colors);
    if (m_sizeMode == DoubleInterlacedScreen)
        UpscaleScreen2(m_image->bits());
    else if (m_sizeMode == DoubleScreen)
        UpscaleScreen2d(m_image->bits());
    else if (m_sizeMode == UpscaledScreen)
        UpscaleScreen(m_image->bits());
    else if (m_sizeMode == UpscaledScreen3)
        UpscaleScreen3(m_image->bits());
    else if (m_sizeMode == UpscaledScreen4)
        UpscaleScreen4(m_image->bits());
    else if (m_sizeMode == UpscaledScreen175)
        UpscaleScreen175(m_image->bits());
    else if (m_sizeMode == UpscaledScreen5)
        UpscaleScreen5(m_image->bits());

    QPainter painter(this);
    painter.drawImage(0, 0, *m_image);
}

void QEmulatorScreen::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(tr("Screenshot"), Global_getMainWindow(), SLOT(saveScreenshot()));
    menu.addAction(tr("Screenshot to Clipboard"), Global_getMainWindow(), SLOT(screenshotToClipboard()));
    menu.addAction(tr("Screen Text to Clipboard"), Global_getMainWindow(), SLOT(screenTextToClipboard()));
    menu.exec(event->globalPos());
}

void QEmulatorScreen::keyPressEvent(QKeyEvent *event)
{
    if (! g_okEmulatorRunning) return;
    if (event->isAutoRepeat()) return;

    unsigned char ukncscan = TranslateQtKeyToUkncKey(event->key());
    if (ukncscan == 0) return;

    Emulator_KeyEvent(ukncscan, true);
    event->accept();
}

void QEmulatorScreen::keyReleaseEvent(QKeyEvent *event)
{
    unsigned char ukncscan = TranslateQtKeyToUkncKey(event->key());
    if (ukncscan == 0) return;

    Emulator_KeyEvent(ukncscan, false);
    event->accept();
}

const unsigned char arrQtkey2UkncscanLat[256] =    // ËÀÒ
{
    /*       0     1     2     3     4     5     6     7     8     9     a     b     c     d     e     f  */
    /*0*/    0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000,
    /*1*/    0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000,
    /*2*/    0113, 0004, 0151, 0172, 0000, 0116, 0154, 0133, 0134, 0000, 0000, 0000, 0000, 0000, 0000, 0000,
    /*3*/    0176, 0030, 0031, 0032, 0013, 0034, 0035, 0016, 0017, 0177, 0000, 0000, 0000, 0000, 0000, 0000,
    /*4*/    0000, 0072, 0076, 0050, 0057, 0033, 0047, 0055, 0156, 0073, 0027, 0052, 0056, 0112, 0054, 0075,
    /*5*/    0053, 0067, 0074, 0111, 0114, 0051, 0137, 0071, 0115, 0070, 0157, 0000, 0000, 0000, 0000, 0000,
    /*6*/    0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000,
    /*7*/    0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000,
    /*8*/    0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000,
    /*9*/    0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000,
    /*a*/    0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000,
    /*b*/    0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000,
    /*c*/    0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000,
    /*d*/    0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000,
    /*e*/    0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000,
    /*f*/    0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000,
};
const unsigned char arrQtkey2UkncscanRus[256] =    // ÐÓÑ
{
    /*       0     1     2     3     4     5     6     7     8     9     a     b     c     d     e     f  */
    /*0*/    0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000,
    /*1*/    0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000,
    /*2*/    0113, 0004, 0151, 0172, 0000, 0116, 0154, 0133, 0134, 0000, 0000, 0000, 0000, 0171, 0152, 0000,
    /*3*/    0176, 0030, 0031, 0032, 0013, 0034, 0035, 0016, 0017, 0177, 0000, 0000, 0000, 0000, 0000, 0000,
    /*4*/    0000, 0047, 0073, 0111, 0071, 0051, 0072, 0053, 0074, 0036, 0075, 0056, 0057, 0115, 0114, 0037,
    /*5*/    0157, 0027, 0052, 0070, 0033, 0055, 0112, 0050, 0110, 0054, 0067, 0000, 0000, 0000, 0000, 0000,
    /*6*/    0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000,
    /*7*/    0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000,
    /*8*/    0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000,
    /*9*/    0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000,
    /*a*/    0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000,
    /*b*/    0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000,
    /*c*/    0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000,
    /*d*/    0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000,
    /*e*/    0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000,
    /*f*/    0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000,
};


unsigned char QEmulatorScreen::TranslateQtKeyToUkncKey(int qtkey)
{
    switch (qtkey)
    {
    case Qt::Key_Down:      return 0134;
    case Qt::Key_Up:        return 0154;
    case Qt::Key_Left:      return 0116;
    case Qt::Key_Right:     return 0133;
    case Qt::Key_Enter:     return 0166;
    case Qt::Key_Return:    return 0166;
    case Qt::Key_Tab:       return 0026;
    case Qt::Key_Shift:     return 0105;  // HP key
    case Qt::Key_Space:     return 0113;
    case Qt::Key_Backspace: return 0132;  // ZB (BACKSPACE) key
    case Qt::Key_Control:   return 0046;  // SU (UPR) key
    case Qt::Key_F1:        return 0010;  // K1 / K6
    case Qt::Key_F2:        return 0011;  // K1 / K6
    case Qt::Key_F3:        return 0012;  // K1 / K6
    case Qt::Key_F4:        return 0014;  // K1 / K6
    case Qt::Key_F5:        return 0015;  // K1 / K6
    case Qt::Key_F7:        return 0152;  // UST key
    case Qt::Key_F8:        return 0151;  // ISP key
    }

    if (qtkey >= 32 && qtkey <= 255)
    {
        unsigned short ukncRegister = g_pBoard->GetKeyboardRegister();
        const unsigned char * pTable = ((ukncRegister & KEYB_LAT) != 0) ? arrQtkey2UkncscanLat : arrQtkey2UkncscanRus;
        return pTable[qtkey];
    }

    return 0;
}

static uint8_t RecognizeCharacter(const uint8_t* fontcur, const uint8_t* fontstd, const QImage& image, int startx, int starty)
{
    int16_t bestmatch = -32767;
    uint8_t bestchar = 0;
    for (uint8_t charidx = 0; charidx < 16 * 14; charidx++)
    {
        int16_t matchcur = 0;
        int16_t matchstd = 0;
        for (int16_t y = 0; y < 11; y++)
        {
            uint8_t fontcurdata = fontcur[charidx * 11 + y];
            uint8_t fontstddata = fontstd[charidx * 11 + y];
            for (int x = 0; x < 8; x++)
            {
                uint32_t color = image.pixel(startx + x, starty + y);
                int sum = (color & 0xff) + ((color >> 8) & 0xff) + ((color >> 16) & 0xff);
                uint8_t fontcurbit = (fontcurdata >> x) & 1;
                uint8_t fontstdbit = (fontstddata >> x) & 1;
                if (sum > 384)
                {
                    matchcur += fontcurbit;  matchstd += fontstdbit;
                }
                else
                {
                    matchcur -= fontcurbit;  matchstd -= fontstdbit;
                }
            }
        }
        if (matchcur > bestmatch)
        {
            bestmatch = matchcur;
            bestchar = charidx;
        }
        if (matchstd > bestmatch)
        {
            bestmatch = matchstd;
            bestchar = charidx;
        }
    }

    return 0x20 + bestchar;
}

// buffer size is 81 * 26 + 1 means 26 lines, 80 chars in every line plus CR plus trailing zero
bool QEmulatorScreen::getScreenText(uint8_t* buffer)
{
    // Get screenshot
    QImage image(UKNC_SCREEN_WIDTH, UKNC_SCREEN_HEIGHT, QImage::Format_RGB32);
    Emulator_PrepareScreenToText(image.bits(), ScreenView_GrayColors);

    // Prepare font, get current font data from PPU memory
    CMemoryController* pPpuMemCtl = g_pBoard->GetPPUMemoryController();
    uint8_t fontcur[11 * 16 * 14];
    uint16_t fontaddr = 014142 + 32 * 2;
    int addrtype = 0;
    for (uint8_t charidx = 0; charidx < 16 * 14; charidx++)
    {
        uint16_t charaddr = pPpuMemCtl->GetWordView(fontaddr + charidx * 2, false, false, &addrtype);
        for (int16_t y = 0; y < 11; y++)
        {
            uint16_t fontdata = pPpuMemCtl->GetWordView((charaddr + y) & ~1, false, false, &addrtype);
            if (((charaddr + y) & 1) == 1) fontdata >>= 8;
            fontcur[charidx * 11 + y] = (uint8_t)(fontdata & 0xff);
        }
    }
    // Prepare font, get standard font data from PPU memory
    uint8_t fontstd[11 * 16 * 14];
    uint16_t charstdaddr = 0120170;
    for (uint16_t idx = 0; idx < 16 * 14 * 11; idx++)
    {
        uint16_t fontdata = pPpuMemCtl->GetWordView(charstdaddr & ~1, false, false, &addrtype);
        if ((charstdaddr & 1) == 1) fontdata >>= 8;
        fontstd[idx] = (uint8_t)(fontdata & 0xff);
        charstdaddr++;
    }

    // Loop for lines
    int charidx = 0;
    int y = 0;
    while (y <= 288 - 11)
    {
        for (int x = 0; x < 640; x += 8)
        {
            uint8_t ch = RecognizeCharacter(fontcur, fontstd, image, x, y);
            buffer[charidx] = ch;
            charidx++;
        }
        buffer[charidx++] = 0x0d;

        y += 11;
        if (y == 11) y++;  // Extra line after upper indicator lines
        if (y == 276) y++;  // Extra line before lower indicator lines
    }

    return true;
}
