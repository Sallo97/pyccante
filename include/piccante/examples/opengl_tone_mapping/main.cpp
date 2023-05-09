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
    pic::DragoTMOGL *drago_tmo;
    pic::ReinhardTMOGL *reinhard_tmo;
    pic::DurandTMOGL *durand_tmo;
    pic::DisplayGL *display;
    pic::ImageGL img, *img_tmo;

    int method;

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

        img_tmo = NULL;

        //read an input image
        img.Read("../data/input/bottles.hdr");
        img.generateTextureGL();

        //create a screen aligned quad
        display = new pic::DisplayGL();

        //allocate Drago et al.'s TMO
        drago_tmo = new pic::DragoTMOGL();

        //allocate Reinhard et al.'s TMO
        reinhard_tmo = new pic::ReinhardTMOGL();

        //allocate Durand et al.'s TMO
        durand_tmo = new pic::DurandTMOGL();
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

        switch(method) {
        case 0: {
            //apply Reinhard et al.'s TMO (local version)
            reinhard_tmo->update(-1.0f, -1.0f, false);
            img_tmo = reinhard_tmo->execute(&img, img_tmo);
        } break;

        case 1: {
            //apply Reinhard et al.'s TMO (global version)
            reinhard_tmo->update(-1.0f, -1.0f, true);
            img_tmo = reinhard_tmo->execute(&img, img_tmo);
        } break;

        case 2: {
            //apply Drago et al.'s TMO
            img_tmo = drago_tmo->execute(&img, img_tmo);
        } break;

        case 3: {
            //apply Durand et al.'s TMO
            img_tmo = durand_tmo->execute(&img, img_tmo);
        } break;
        }

        display->Process(img_tmo);
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

        img_tmo = NULL;
        method = 0;
    }

    /**
     * @brief update
     */
    void update()
    {
        method = (method + 1) % 4;
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
                    "Please hit the space bar in order to switch to different tone mapping images.",
                    this);
        label->setFixedWidth(912);
        label->setFixedHeight(64);
        label->setAlignment(Qt::AlignHCenter);

        layout->addWidget(label);

        setLayout(layout);

        setWindowTitle(tr("Tone Mapping Example"));
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
