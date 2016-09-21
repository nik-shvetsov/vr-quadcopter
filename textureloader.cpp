#include "textureloader.h"

GMlib::PSurfTexVisualizer<float, 3>* TextureLoader::loadTexture(QString fileName) const {

    GMlib::PSurfTexVisualizer<float, 3>* visualizer = new GMlib::PSurfTexVisualizer<float, 3>;

    QImage img = QImage(fileName);

    if(!QFile::exists(fileName))
        std::cerr << "File " << fileName.toStdString() << " does not exist!" << std::endl;

    if(img.isNull()) {
        std::cerr << "Image file is not supported!" << std::endl;
    }

    img = img.convertToFormat(QImage::Format_RGB888);

    GMlib::GL::Texture texture;

    texture.create(GL_TEXTURE_2D);
    texture.texImage2D(0, GL_RGB, img.width(), img.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, img.bits());
    texture.texParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    texture.texParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    texture.texParameterf(GL_TEXTURE_WRAP_S, GL_REPEAT);
    texture.texParameterf(GL_TEXTURE_WRAP_T, GL_REPEAT);

    visualizer->setTexture(texture);

    return visualizer;
}
