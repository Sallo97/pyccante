/*

PICCANTE Examples
The hottest examples of Piccante:
http://vcg.isti.cnr.it/piccante

Copyright (C) 2014
Visual Computing Laboratory - ISTI CNR
http://vcg.isti.cnr.it
First author: Francesco Banterle

This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3.0 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    See the GNU Lesser General Public License
    ( http://www.gnu.org/licenses/lgpl-3.0.html ) for more details.
*/

/**
 * NOTE: if you do not want to use this OpenGL functions loader,
 * please change it with your favorite one. This is just
 * a suggestion for running examples.
*/

#include "../common_code/gl_include.hpp"

#include <QKeyEvent>
#include <QtCore/QCoreApplication>
#include <QtOpenGL/QGLWidget>
#include <QApplication>
#include <QVBoxLayout>
#include <QLabel>

#include "piccante.hpp"

class GLWidget : public QGLWidget
        #ifndef PIC_INCLUDE_GL
        , protected QOpenGLFunctions
        #endif
{
protected:
    pic::QuadGL *quad;
    pic::ExposureFusionGL *ef;
    pic::FilterGLSimpleTMO *tmo;
    pic::ImageGL img, *img_tmo;
    pic::ImageGLVec img_vec;
    pic::TechniqueGL technique;

    unsigned int    method;

    /**
     * @brief initializeGL sets variables up.
     */
    void initializeGL(){

    #ifndef PIC_INCLUDE_GL
        initializeOpenGLFunctions();
    #endif

    #ifdef PIC_INCLUDE_GL
        if(ogl_LoadFunctions() == ogl_LOAD_FAILED) {
            printf("OpenGL functions are not loaded!\n");
        }
    #endif

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f );

        //read an input image
        img.Read("../data/input/bottles.hdr");
        img.generateTextureGL(GL_TEXTURE_2D, GL_FLOAT, false);

        //create a screen aligned quad
        pic::QuadGL::getTechnique(technique,
                                pic::QuadGL::getVertexProgramV3(),
                                pic::QuadGL::getFragmentProgramForView());

        quad = new pic::QuadGL(true);

        //allocate an exposure fusion instance
        ef = new pic::ExposureFusionGL();

        //compute a stack of LDR images from an HDR image
        img_vec = pic::getAllExposuresImagesGL(&img, 2.2f);

        //allocate a new filter for simple tone mapping
        tmo = new pic::FilterGLSimpleTMO();
    }

    /**
     * @brief resizeGL
     * @param w
     * @param h
     */
    void resizeGL( int w, int h ){
        const qreal retinaScale = devicePixelRatio();
        glViewport(0, 0, w * retinaScale, h * retinaScale);
    }

    /**
     * @brief paintGL
     */
    void paintGL(){
        if(parentWidget() != NULL) {
            if(!parentWidget()->isVisible()) {
                return;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        if(method == 0) {
            //compute exposure fusion for the stack (img_vec)
            img_tmo = ef->ProcessStack(img_vec, img_tmo);
        } else {
            //simple tone mapping: gamma + exposure correction
            img_tmo = tmo->Process(SingleGL(&img), img_tmo);
        }

        //visualization
        quad->Render(technique, img_tmo->getTexture());
    }

public:

    /**
     * @brief GLWidget
     * @param format
     * @param parent
     */
    GLWidget( const QGLFormat& format, QWidget* parent = 0 ): QGLWidget(format, parent, 0)
    {
        setFixedWidth(912);
        setFixedHeight(684);

        ef = NULL;
        img_tmo = NULL;
        tmo = NULL;
        method = 0;
    }

    /**
     * @brief update
     */
    void update()
    {
        method = (method + 1) % 2;
    }
};

class Window : public QWidget
{
protected:
    GLWidget *window_gl;
    QVBoxLayout *layout;
    QLabel *label;

public:

    /**
     * @brief Window
     * @param format
     */
    Window(const QGLFormat &format)
    {
        resize(912, 684 + 64);

        window_gl = new GLWidget(format, this);

        layout = new QVBoxLayout();

        layout->addWidget(window_gl);

        label = new QLabel(
                    "Please hit the space bar in order to switch from fused image to the original one.",
                    this);
        label->setAlignment(Qt::AlignHCenter);
        label->setFixedWidth(912);
        label->setFixedHeight(64);

        layout->addWidget(label);

        setLayout(layout);

        setWindowTitle(tr("Exposure Fusion Example"));
    }

    ~Window()
    {
        delete window_gl;
        delete layout;
        delete label;
    }

    /**
     * @brief keyPressEvent
     * @param e
     */
    void keyPressEvent( QKeyEvent* e ){
        if(e->type() == QEvent::KeyPress) {
            if(e->key() == Qt::Key_Space) {
                window_gl->update();
                window_gl->updateGL();
            }
        }
    }
};

int main(int argc, char **argv)
{
    QApplication app( argc, argv );

    QGLFormat glFormat;
    glFormat.setVersion( 4, 0 );
    glFormat.setProfile( QGLFormat::CoreProfile );
    glFormat.setSampleBuffers( true );

    //create a window with OpenGL 4.0 Core profile
    Window w( glFormat );
    w.show();

    app.installEventFilter(&w);

    return app.exec();
}
