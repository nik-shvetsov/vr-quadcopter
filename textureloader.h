#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <vector>
#include <gmParametricsModule>

#include <QImage>
#include <QOpenGLTexture>
#include <QImageReader>
#include <QDirIterator>

namespace GMlib {
    template <typename T, int n>
    class  PSurfTexVisualizer;
}

class TextureLoader {

public:
    GMlib::PSurfTexVisualizer<float, 3>* loadTexture(QString fileName) const;

};

#endif // TEXTURELOADER_H
