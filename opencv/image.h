﻿#ifndef IMAGE_H
#define IMAGE_H

#include <QQuickPaintedItem>
#include <QVariant>
#include <QPainter>
#include <opencv2/opencv.hpp>
#include <mutex>

Q_DECLARE_METATYPE(cv::Mat)


namespace Littai
{


class Image : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QVariant image READ image WRITE setImage NOTIFY imageChanged)
    Q_PROPERTY(int imageWidth READ imageWidth NOTIFY imageWidthChanged)
    Q_PROPERTY(int imageHeight READ imageHeight NOTIFY imageHeightChanged)
    Q_PROPERTY(QString filePath READ filePath WRITE setFilePath NOTIFY filePathChanged)

public:
    explicit Image(QQuickItem *parent = 0);

    QVariant image() const;
    void setImage(const QVariant& image);

    QString filePath() const;
    void setFilePath(const QString& path);
    Q_INVOKABLE void saveToFile(const QString& path) const;

    int imageWidth() const;
    int imageHeight() const;

    void paint(QPainter *painter) override;

protected:
    void setImage(const cv::Mat& mat, bool isUpdate = true);
    cv::Mat clone() const;

    mutable std::mutex imageMutex_;
    QString filePath_;
    cv::Mat image_;

signals:
    void imageChanged() const;
    void imageWidthChanged() const;
    void imageHeightChanged() const;
    void filePathChanged() const;
    void error(const QString& message) const;
};


}

#endif // IMAGE_H
