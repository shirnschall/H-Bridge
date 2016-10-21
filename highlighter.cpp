/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "highlighter.h"

Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    QStringList keywordPatterns;
    keywordPatterns  << "\\bdouble\\b"
                     << "\\bdo\\b"
                     << "\\bend\\b"
                     << "\\btrue\\b"
                     << "\\bfalse\\b"
                     << "\\bauto\\b"
                     << "\\bbreak\\b"
                     << "\\bcase\\b"
                     << "\\bchar\\b"
                     << "\\bconst\\b"
                     << "\\bcontinue\\b"
                     << "\\bdefault\\b"
                     << "\\belse\\b"
                     << "\\benum\\b"
                     << "\\bextern\\b"
                     << "\\bfor\\b"
                     << "\\bfloat\\b"
                     << "\\bgoto\\b"
                     << "\\bif\\b"
                     << "\\bint\\b"
                     << "\\blong\\b"
                     << "\\bregister\\b"
                     << "\\breturn\\b"
                     << "\\bshort\\b"
                     << "\\bsigned\\b"
                     << "\\bsizeof\\b"
                     << "\\bstatic\\b"
                     << "\\bstruct\\b"
                     << "\\bswitch\\b"
                     << "\\btypedef\\b"
                     << "\\bunion\\b"
                     << "\\bunsigned\\b"
                     << "\\bvoid\\b"
                     << "\\bvolatile\\b"
                     << "\\bwhile\\b"
                     << "\\bstring\\b"
                     << "\\bend\\b"
                     << "\\bnext\\b"
                     << "\\beach\\b"
                     << "\\bgoto\\b";

    QStringList libraries;

    libraries     << "<assert.h>"
                  << "<ctype.h>"
                  << "<errno.h>"
                  << "<float.h>"
                  << "<limits.h>"
                  << "<locale.h>"
                  << "<math.h>"
                  << "<setjmp.h>"
                  << "<signal.h>"
                  << "<stdarg.h>"
                  << "<stddef.h>"
                  << "<stdio.h>"
                  << "<stdlib.h>"
                  << "<string.h>"
                  << "<time.h>"
                  << "<iso646.h>"
                  << "<wchar.h>"
                  << "<wctype.h>"
                  << "<complex.h>"
                  << "<fenv.h>"
                  << "<inttypes.h>"
                  << "<stdbool.h>"
                  << "<stdint.h>"
                  << "<tgmath.h>"
                  << "<stdalign.h>"
                  << "<stdatomic.h>"
                  << "<stdnoreturn.h>"
                  << "<threads.h>"
                  << "<uchar.h>";

    //LIBRARIES
    libraryFormat.setForeground(QColor(144,144,144));
    foreach (const QString &pattern, libraries) {
        rule.pattern = QRegExp(pattern);
        rule.format = libraryFormat;
        highlightingRules.append(rule);
    }

    //#INCLUDE
    includeFormat.setForeground(QColor(144,144,144));
    rule.pattern = QRegExp("#include\\b");
    rule.format = includeFormat;
    highlightingRules.append(rule);


    //QUOTATION
    quotationFormat.setForeground(QColor(214,157,133));
    rule.pattern = QRegExp("\"([^\"]*)\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    //singleQUOTATION
    squotationFormat.setForeground(QColor(214,157,133));
    rule.pattern = QRegExp("\'([^\']*)\'");
    rule.format = squotationFormat;
    highlightingRules.append(rule);

    //FUNCTIONS
    functionFormat.setFontItalic(true);
    functionFormat.setForeground(QColor(78,201,176));
    rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);

    //GENERAL
    keywordFormat.setForeground(QColor(86,156,214));
    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    //COMMENTS
    singleLineCommentFormat.setForeground(QColor(87,166,74));
    rule.pattern = QRegExp("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(QColor(87,166,74));


    commentStartExpression = QRegExp("/\\*");
    commentEndExpression = QRegExp("\\*/");
}

void Highlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }
    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = commentStartExpression.indexIn(text);

    while (startIndex >= 0) {
        int endIndex = commentEndExpression.indexIn(text, startIndex);
        int commentLength;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
     + commentEndExpression.matchedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
    }
}
