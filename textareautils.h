#ifndef APPNOVELIST_TEXTAREAUTILS_H
#define APPNOVELIST_TEXTAREAUTILS_H

#include <QObject>
#include <QQmlEngine>
#include <QQuickTextDocument>
#include <QTextCursor>

class TextAreaUtils : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit TextAreaUtils(QObject *parent = nullptr);

    Q_INVOKABLE void insertHtmlAt(QQuickTextDocument *quickDoc,
                                  int position,
                                  const QString &html,
                                  const QColor &color = Qt::black) const
    {
        if (!quickDoc || !quickDoc->textDocument())
            return;

        QTextDocument *doc = quickDoc->textDocument();
        QTextCursor c(doc);
        position = qBound(0, position, doc->characterCount() - 1);

        QTextBlockFormat format;
        format.setBottomMargin(32);
        format.setForeground(color);

        QTextCharFormat charFormat;
        charFormat.setForeground(color);

        const auto style
            = QStringLiteral("<style>p{color:%1}</style>").arg(color.name(QColor::HexArgb));

        c.beginEditBlock();
        c.setPosition(position);
        c.insertBlock(format, charFormat);
        c.insertHtml(style + html);
        c.endEditBlock();
    }

    Q_INVOKABLE void replaceSelectionWithHtml(QQuickTextDocument *quickDoc,
                                              int selStart,
                                              int selEnd,
                                              const QString &html) const
    {
        if (!quickDoc || !quickDoc->textDocument())
            return;

        QTextDocument *doc = quickDoc->textDocument();
        QTextCursor c(doc);
        selStart = qMax(0, selStart);
        selEnd = qMin(selEnd, doc->characterCount() - 1);
        if (selEnd < selStart)
            std::swap(selStart, selEnd);

        c.setPosition(selStart);
        c.setPosition(selEnd, QTextCursor::KeepAnchor);
        c.insertHtml(html);
    }
};

#endif // APPNOVELIST_TEXTAREAUTILS_H
