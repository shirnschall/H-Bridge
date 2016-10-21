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


/***************************************************************************
**
**This file was heavily edited by Sebastian Hirnschall to suite this project!
**
**
**
****************************************************************************/



#include <autocompleter.h>
#include <QtWidgets>

#include <ctype.h>
#include <algorithm>
#include "codeeditor.h"
#include "highlighter.h"
#include "mainwindow.h"
#include <stdlib.h>

#include <vector>

//Debugging
#include <iostream>

//settings:
bool    autoCompleteEnabled=true,
        autoIndent      =   true,
        syntaxHighl     =   true,
        closeBrackets   =   true,
        closeBraces     =   true,
        closeQuotes     =   true,
        closeSQuotes    =   true,
        autoSave        =   false,
        autoBackup      =   false,
        showUnsaved     =   true,
        quoteSelection  =   true,
        bracketSelection=   true,
        braceSelection  =   true;

int     autoMinLength   =   1,
        tabSpace        =   4;






std::vector<std::string>* wordlist;

CodeEditor::CodeEditor(QWidget *parent, QMainWindow *mainwindow, std::string text,std::vector<std::string>* completerWords) : QPlainTextEdit(parent)
{
    wordlist=completerWords;

    lineNumberArea = new LineNumberArea(this);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
    connect(this, SIGNAL(textChanged()), this, SLOT(parseText()));

    if(showUnsaved)
    {
        connect(this,SIGNAL(textChanged()),mainwindow,SLOT(CodeEditorTextChanged()));
    }

    //set stylesheet
    //setStyleSheet("CodeEditor{background-color:rgb(28,28,28);color:white;border:none;font:11pt Consolas;}");


    updateLineNumberAreaWidth(0);
    highlightCurrentLine();

    //set default code:
    setPlainText(text.c_str());

    highlighter = new Highlighter(document());

    completer = new AutoCompleter(this);
    completer->setVisible(false);
    completer->raise();
    completer->setFocusPolicy(Qt::ClickFocus);
    completer->setMaximumWidth(200);
    completer->setMaximumHeight(110);
}


int CodeEditor::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 25 + fontMetrics().width(QLatin1Char('9')) * digits;

    return space;
}



void CodeEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}



void CodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}



void CodeEditor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}



void CodeEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(50,50,50);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}


void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), QColor(28,28,28));

    //draw horizontal line
    //QLineF line(lineNumberArea->width()-5, 0, lineNumberArea->width()-5, lineNumberArea->height());
    //painter.setPen(QColor(Qt::darkGray));
    //painter.drawLine(line);


    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QFont font;
            font.setPointSize(11);

            QString number = QString::number(blockNumber + 1);
            painter.setFont(font);
            //painter.setPen(QColor(43, 145, 175));
            painter.setPen(QColor(Qt::darkGray));
            //painter.setPen(QColor(0, 136, 192));
            painter.drawText(0, top, lineNumberArea->width()-15, fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}


void CodeEditor::keyPressEvent(QKeyEvent *e)
{
    std::string textToAdd{""};

    switch (e->key()) {
        case Qt::Key_Tab:
        if(completer->isVisible())
        {

            QTextCursor c = textCursor();
            //get wodlength:
            std::string charsToSplit  = " \t\"\'\\/,;:.-<>+*%&=[]{}()~";
            bool found=false;
            int wordLength=0;

            for(int i=c.positionInBlock()-1;i>=0;--i)
            {
                for(int j=0;j<charsToSplit.length();++j)
                {
                    //std::cout<<charsToSplit[j]<<":"<<c.block().text().toStdString()[i]<<"\n\n";
                    if(charsToSplit[j]==c.block().text().toStdString()[i])
                    {
                        found=true;
                        break;
                    }
                }
                if(found)
                {
                    break;
                }
                //std::cout<<c.block().text().toStdString()[i]<<'\n';

                wordLength++;

            }


            for(int i=0;i<wordLength;++i)
            {
                c.deletePreviousChar();
            }
            insertPlainText(completer->currentItem()->text());
            //insertPlainText(completer->currentItem()->text().toStdString().substr(word.length(),completer->currentItem()->text().length()-word.length()).c_str());
            completer->setVisible(false);
        }
        else
        {
            if(textCursor().columnNumber()%tabSpace==0)
            {
                for(int i=0;i<tabSpace;++i)
                {
                    insertPlainText(" ");
                }
            }
            else
            {
                for(int i=0;i<textCursor().columnNumber()%tabSpace;++i)
                {
                    insertPlainText(" ");
                }
            }
        }
        break;
        case Qt::Key_Enter:
        case Qt::Key_Return:
        try
        {
        //if enter is pressed get the current line and parse it:
            QTextBlock currentLine = document()->findBlockByNumber(textCursor().blockNumber());
            //debuginfo:
            std::cout<< currentLine.text().toStdString().c_str()<<std::endl;
            //parse:
            std::string line{currentLine.text().toStdString()};
            bool tab{true};
            int i{0};

            //for each tab at the begining of the previous line add one to the new line
            do
            {
              if(line[i]=='\t'||line[i]=='{')
              {
                  textToAdd+="    ";
                  ++i;
              }
              else
              {
                  tab=false;
              }
            }while(i<line.length()&&tab);
        }
        catch(...)
        {

        }
        //send keypress
        QPlainTextEdit::keyPressEvent(e);
        //insert n tabs
        if(textToAdd!="")
        {
           insertPlainText(textToAdd.c_str());
        }
        break;
    case Qt::Key_BraceRight:
        if(toPlainText().at(textCursor().position()-1)=='\t')
        {
            textCursor().deletePreviousChar();
        }
        //send keypress
        QPlainTextEdit::keyPressEvent(e);
        //insert n tabs
        if(textToAdd!="")
        {
           insertPlainText(textToAdd.c_str());
        }
        break;
    case Qt::Key_Down:
        if(completer->isVisible())
        {
            if(completer->currentRow()!=completer->count()-1)
            {
                completer->setCurrentRow(completer->currentRow()+1);
            }
            else
            {
                completer->setCurrentRow(0);
            }
        }
        else
        {
           QPlainTextEdit::keyPressEvent(e);
        }
        break;
    case Qt::Key_Up:
        if(completer->isVisible())
        {
            if(completer->currentRow()!=0)
            {
                completer->setCurrentRow(completer->currentRow()-1);
            }
            else
            {
                completer->setCurrentRow(completer->count()-1);
            }
        }
        else
        {
           QPlainTextEdit::keyPressEvent(e);
        }
        break;
    case Qt::Key_Right:
        completer->setVisible(false);
        QPlainTextEdit::keyPressEvent(e);
        break;
    case Qt::Key_Left:
        completer->setVisible(false);
        QPlainTextEdit::keyPressEvent(e);
        break;
    default:
        QPlainTextEdit::keyPressEvent(e);
        autoComplete();
        break;
    }



}


int CodeEditor::autoComplete()
{
    std::vector<std::string> wordsToComplete{*wordlist};
    if(autoCompleteEnabled)
    {
        std::string charsToSplit  = " \t\"\'\\/,;:.-<>+*%&=[]{}()~";
        //autocomplete:
        QTextCursor c = textCursor();

        bool found=false;

        std::string word{""},
                    wordToLower{""};

        for(int i=c.positionInBlock()-1;i>=0;--i)
        {
            for(int j=0;j<charsToSplit.length();++j)
            {
                //std::cout<<charsToSplit[j]<<":"<<c.block().text().toStdString()[i]<<"\n\n";
                if(charsToSplit[j]==c.block().text().toStdString()[i])
                {
                    std::cout<<"found\n";
                    found=true;
                    break;
                }
            }
            if(found)
            {
                break;
            }
            //std::cout<<c.block().text().toStdString()[i]<<'\n';

            word+=c.block().text().toStdString()[i];

        }
        //std::cout<<"\n\n\""<<word.toStdString().c_str()<<"\"\n\n";

        std::reverse(word.begin(),word.end());

        std::cout<<"\n\n\""<<word.c_str()<<"\"\n\n";

        //std::cout <<word.c_str()<<'\n';

        //std::transform(word.toStdString().begin(),word.toStdString().end(),word.toStdString().begin(),::tolower);
        bool show(false);


        for(int i=0;i<word.length();++i)
        {
            wordToLower+=tolower(word[i]);
        }

        completer->clear();

        if(word.length()>=1)
        {
            for(int i=0;i<wordsToComplete.size();++i)
            {
                std::string currentWordToLower{""};
                for(int j=0;j<wordsToComplete[i].length();++j)
                {
                    currentWordToLower+=tolower(wordsToComplete[i][j]);
                }

                if(currentWordToLower.find(wordToLower)==0&&currentWordToLower!=wordToLower)
                {
                    completer->addItem(wordsToComplete[i].c_str());
                    show=true;
                }
            }
        }
        if(show)
        {

            if(!completer->isVisible())
            {
                completer->setVisible(true);
                completer->move((c.columnNumber()-(autoMinLength-1))*fontMetrics().width('9')+35,fontMetrics().height()*(c.blockNumber()-firstVisibleBlock().blockNumber()+1)+1);
                completer->setCurrentRow(0);
            }
            else
            {
                completer->setCurrentRow(0);
            }

        }
        else
        {
            completer->setVisible(false);
        }



        return word.length();
    }
    else
    {
        return 0;
    }
}

