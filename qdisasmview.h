﻿#ifndef QDISASMVIEW_H
#define QDISASMVIEW_H

#include <QVector>
#include <QTextStream>
#include <QWidget>

class QPainter;
class CProcessor;
class CMemoryController;


enum DisasmSubtitleType
{
    SUBTYPE_NONE = 0,
    SUBTYPE_COMMENT = 1,
    SUBTYPE_BLOCKCOMMENT = 2,
    SUBTYPE_DATA = 4
};

struct DisasmSubtitleItem
{
    quint16 address;
    DisasmSubtitleType type;
    QString comment;
};

class QDisasmView : public QWidget
{
    Q_OBJECT
public:
    QDisasmView();

    void setCurrentProc(bool okProc);
    void updateData();
    void updateWindowText();

public slots:
    void switchCpuPpu();
    void showHideSubtitles();

protected:
    void paintEvent(QPaintEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
    void focusInEvent(QFocusEvent *);
    void focusOutEvent(QFocusEvent *);

    void parseSubtitles(QTextStream& stream);
    void addSubtitle(quint16 addr, DisasmSubtitleType type, const QString& comment);

private:
    bool m_okDisasmProcessor;  // TRUE - CPU, FALSE - PPU
    quint16 m_wDisasmBaseAddr;
    quint16 m_wDisasmNextBaseAddr;
    QVector<DisasmSubtitleItem> m_SubtitleItems;

    int drawDisassemble(QPainter& painter, CProcessor* pProc, quint16 base, quint16 previous);
    const DisasmSubtitleItem * findSubtitle(quint16 address, quint16 typemask);

    bool checkForJump(const quint16* memory, int* pDelta);
    bool getJumpConditionHint(const quint16* memory, const CProcessor * pProc, const CMemoryController * pMemCtl, QString &buffer);
    void drawJump(QPainter& painter, int yFrom, int delta, int x, int cyLine, QColor color);
    void registerHint(const CProcessor *pProc, const CMemoryController *pMemCtl,
            QString &hint1, QString& hint2,
            int regnum, int regmod, bool byteword, quint16 indexval);
    void registerHintPC(const CProcessor *pProc, const CMemoryController *pMemCtl,
            QString &hint1, QString& hint2,
            int regmod, bool byteword, quint16 curaddr, quint16 value);
    void instructionHint(const quint16 *memory, const CProcessor *pProc, const CMemoryController *pMemCtl,
            QString& buffer, QString& buffer2,
            int srcreg, int srcmod, int dstreg, int dstmod);
    int getInstructionHint(const quint16* memory, const CProcessor * pProc, const CMemoryController * pMemCtl,
            QString &buffer, QString &buffer2);
    void drawBreakpoint(QPainter& painter, int x, int y, int cyLine);
};

#endif // QDISASMVIEW_H
