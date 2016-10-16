#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <vector>
#include <gmParametricsModule>
#include <parametrics/visualizers/gmpsurftexvisualizer.h>

#include <QImage>
#include <QOpenGLTexture>
#include <QImageReader>
#include <QDirIterator>

class TextureLoader
{
public:
    GMlib::PSurfTexVisualizer<float, 3>* loadTexture(QString fileName) const;
};

#endif // TEXTURELOADER_H
