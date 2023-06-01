import sys
import os
import pyccante as pyc
import imgwindow as iw
from menubar import file as fl
from menubar import ldr
from algorithms import hdr_merger
from transformations import blend
from filters import (b2df, b2ds, conv2d, gaussian2d,
                     lum, mosaic, rotation, warp2d)
from PySide6.QtCore import Qt
from PySide6.QtWidgets import (QApplication, QVBoxLayout, QHBoxLayout,
                               QLabel, QMenuBar, QFileDialog,
                               QFrame, QMainWindow, QGridLayout,
                               QSizePolicy, QSpacerItem)
from PySide6.QtGui import QIcon, QResizeEvent, QWheelEvent


def remove_temp_images():
    if os.path.isfile("./data/_custom_temp.png"):
        os.remove("./data/_custom_temp.png")
    if os.path.isfile("./data/_hdr_temp.png"):
        os.remove("./data/_hdr_temp.png")


def construct_boxes(boxes, categories):
    for i, (key, values) in enumerate(categories.items()):
        boxes[i].addItem(f"Select the {key} you want to apply...")
        for value in values:
            boxes[i].addItem(value)


class MainWindow(QMainWindow):
    def __init__(self):
        super(MainWindow, self).__init__()

        # Image size values
        main_h = 200
        main_w = 200

        custom_h = 700
        custom_w = 700

        # Paths values
        self.plcholder_path = "./data/placeholder.png"
        self.img_path = "./data/placeholder.png"
        self.custom_path = "./data/_custom_temp.png"
        self.hdr_path = "./data/_hdr_temp.png"

        # Define flags
        self.custom_flag = False
        self.is_hdr = False

        # Define images and img parameters
        self.main_img = pyc.Image(self.plcholder_path, pyc.LDR_type.LT_NONE)
        self.custom_img = self.main_img.clone()
        self.ldr_type = pyc.LDR_type.LT_NONE

        # Configure Window bar parameters
        self.setWindowTitle("Pyccante GUI [no image loaded]")
        self.setWindowIcon(QIcon("./data/icon.png"))

        # Define images window
        self.main_win = iw.ImageWindow(self.plcholder_path, main_h, main_w,
                                       self.main_img.width, self.main_img.height,
                                       "main")
        self.custom_win = iw.ImageWindow(self.plcholder_path, custom_h, custom_w,
                                         self.custom_img.width, self.custom_img.height,
                                         "custom")

        # Construct menus
        menubar = QMenuBar(self)
        self.construct_file_menu(menubar)

        self.transform_objs = []
        self.construct_transform_menu(menubar)

        self.construct_ldr_menu(menubar)

        self.filter_objs = []
        self.construct_filter_menu(menubar)

        self.algo_objs = []
        self.construct_algo_menu(menubar)

        # Define main image parameters
        self.info_tile = QLabel("Image Info")
        self.info_tile.setAlignment(Qt.AlignCenter)
        self.height_label = QLabel()
        self.height_label.setFixedSize(200, 20)
        self.width_label = QLabel()
        self.width_label.setFixedSize(200, 20)
        self.size_label = QLabel()
        self.size_label.setFixedSize(100, 20)
        info_layout = QVBoxLayout()
        info_layout.addWidget(self.info_tile)
        info_layout.addWidget(self.width_label)
        info_layout.addWidget(self.height_label)
        info_layout.addWidget(self.size_label)

        # Define maximum values
        self.max_title = QLabel("RGB Maximum")
        self.max_title.setAlignment(Qt.AlignCenter)
        self.maxr_label = QLabel()
        self.maxr_label.setFixedSize(100, 20)
        self.maxg_label = QLabel()
        self.maxg_label.setFixedSize(100, 20)
        self.maxb_label = QLabel()
        self.maxb_label.setFixedSize(100, 20)
        max_layout = QVBoxLayout()
        max_layout.addWidget(self.max_title)
        max_layout.addWidget(self.maxr_label)
        max_layout.addWidget(self.maxb_label)
        max_layout.addWidget(self.maxg_label)

        # Define minimum values
        self.min_title = QLabel("RGB Minimum")
        self.min_title.setAlignment(Qt.AlignCenter)
        self.minr_label = QLabel()
        self.minr_label.setFixedSize(100, 20)
        self.ming_label = QLabel()
        self.ming_label.setFixedSize(100, 20)
        self.minb_label = QLabel()
        self.minb_label.setFixedSize(100, 20)
        min_layout = QVBoxLayout()
        min_layout.addWidget(self.min_title)
        min_layout.addWidget(self.minr_label)
        min_layout.addWidget(self.minb_label)
        min_layout.addWidget(self.ming_label)
        self.update_text()

        # Define History

        # Define layout sx
        self.sx_layout = QVBoxLayout()
        self.sx_layout.addWidget(self.main_win)
        h_sep1 = QFrame()
        h_sep1.setFrameShape(QFrame.Shape.HLine)
        h_sep1.setFrameShadow(QFrame.Shadow.Sunken)
        self.sx_layout.addWidget(h_sep1)
        self.sx_layout.addLayout(info_layout)
        self.sx_layout.setAlignment(Qt.AlignTop)
        h_sep2 = QFrame()
        h_sep2.setFrameShape(QFrame.Shape.HLine)
        h_sep2.setFrameShadow(QFrame.Shadow.Sunken)
        self.sx_layout.addWidget(h_sep2)
        self.sx_layout.addLayout(max_layout)
        h_sep3 = QFrame()
        h_sep3.setFrameShape(QFrame.Shape.HLine)
        h_sep3.setFrameShadow(QFrame.Shadow.Sunken)
        self.sx_layout.addWidget(h_sep3)
        self.sx_layout.addLayout(min_layout)

        # sx_layout + v line
        sx_v = QHBoxLayout()
        sx_v.addLayout(self.sx_layout)

        v_sep1 = QFrame()
        v_sep1.setFrameShape(QFrame.Shape.VLine)
        v_sep1.setFrameShadow(QFrame.Shadow.Sunken)
        v_sep1.setSizePolicy(QSizePolicy.Policy.Fixed, QSizePolicy.Policy.Expanding)
        sx_v.addWidget(v_sep1)

        # Define frame sx
        sx_frame = QFrame()
        sx_frame.setLayout(sx_v)
        sx_frame.setFixedWidth(300)

        # Construct main window
        self.main_layout = QHBoxLayout()
        self.main_layout.setMenuBar(menubar)
        self.main_layout.addWidget(sx_frame)
        self.main_layout.addWidget(self.custom_win)

        # Construct main widget
        main_widget = QLabel()
        main_widget.setMinimumSize(900, 700)
        main_widget.setLayout(self.main_layout)
        main_widget.setSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Fixed)

        # Set main window
        self.setCentralWidget(main_widget)

    def update_objs(self):
        for transform_obj in self.transform_objs:
            transform_obj.update_infos(self.custom_img, self.custom_path,
                                       self.custom_win, self.ldr_type)

        for filter_obj in self.filter_objs:
            filter_obj.update_infos(self.custom_img,  self.custom_path,
                                    self.custom_win, self.ldr_type)

    def update_text(self):
        self.width_label.setText(f"W : {self.main_img.width} px")
        self.height_label.setText(f"H : {self.main_img.height} px")
        self.size_label.setText(f"S : {self.main_img.size()} px")

        max_rgb = self.main_img.getMaxVal()
        self.maxr_label.setText(f"R : {max_rgb[0]}")
        self.maxg_label.setText(f"G : {max_rgb[1]}")
        self.maxb_label.setText(f"B : {max_rgb[2]}")

        min_rgb = self.main_img.getMinVal()
        self.minr_label.setText(f"R : {min_rgb[0]}")
        self.ming_label.setText(f"G : {min_rgb[1]}")
        self.minb_label.setText(f"B : {min_rgb[2]}")

    def open_dialog(self):
        self.ldr_type = pyc.LDR_type.LT_NONE
        img_path = QFileDialog.getOpenFileName(
            self,
            "Open the image", "",
            "Image Files (*.png *.jpg *.bmp *.hdr)"
        )
        read_path = img_path[0]
        print(f"read_path = {read_path}")
        if read_path.endswith(".hdr"):
            self.is_hdr = True
        else:
            self.is_hdr = False
        new_img = fl.read_img(read_path, self.main_win,
                              self.custom_win)
        self.check_img(new_img)

    def check_img(self, new_img):
        if new_img is not None:
            self.main_img = new_img
            self.custom_img = new_img.clone()
            self.update_objs()
            self.setWindowTitle(f"Pyccante GUI [{self.main_img.nameFile}]")
            self.custom_flag = False
            self.update_text()

    def save_dialog(self):
        path = QFileDialog.getSaveFileName(
            self,
            "Save the image",
            "new_img",
            ".png;; .bmp;; .jpg;; .hdr",
        )
        fl.save_img(self.custom_img, path, self.ldr_type)
        
    def close(self):
        app.exit()

    def construct_file_menu(self, menubar):
        file_menu = menubar.addMenu("&File")
        file_menu.addAction("&Open...",
                            (lambda: self.open_dialog()),
                            "Ctrl+O")
        file_menu.addAction("&Save as...",
                            (lambda: self.save_dialog()),
                            "Ctrl+S")
        file_menu.addAction("&Revert to original size",
                            lambda: self.custom_win.original_size())
        file_menu.addAction("&Quit",
                            lambda: self.close(),
                            "Ctrl+Q")

    def construct_transform_menu(self, menubar):
        blend_obj = blend.Blend(self.custom_img, self.custom_path,
                                self.custom_win, self.ldr_type)

        self.transform_objs = [blend_obj]
        transform_menu = menubar.addMenu("&Transform")
        transform_menu.addAction("&Rotate 90° clockwise",
                                 (lambda: self.do_transformation("r90cw")),
                                 "Ctrl+["
                                 )
        transform_menu.addAction("&Rotate 90° counter clockwise",
                                 (lambda: self.do_transformation("r90ccw")),
                                 "Ctrl+]"
                                 )
        transform_menu.addAction("&Flip horizontally",
                                 (lambda: self.do_transformation("fliph")),
                                 "Ctrl+H"
                                 )
        transform_menu.addAction("&Flip vertically",
                                 (lambda: self.do_transformation("flipv")),

                                 "Ctrl+V"
                                 )
        transform_menu.addAction("&Blend",
                                 (lambda: self.do_transformation("blend")),
                                 "Ctrl+B"
                                 )

    def construct_ldr_menu(self, menubar):
        ldr_menu = menubar.addMenu("&LDR type")
        ldr_menu.addAction("&None",
                           (lambda: self.do_ldr("none")),
                           "Ctrl+O"
                           ),
        ldr_menu.addAction("&Normal",
                           (lambda: self.do_ldr("normal")),
                           "Ctrl+N"
                           ),
        ldr_menu.addAction("&Normal + Gamma",
                           (lambda: self.do_ldr("gamma")),
                           "Ctrl+G"
                           )

    def construct_filter_menu(self, menubar):
        b2df_obj = b2df.B2DFWindow(self.custom_img, self.custom_path,
                                   self.custom_win, self.ldr_type)
        b2ds_obj = b2ds.B2DSWindow(self.custom_img, self.custom_path,
                                   self.custom_win, self.ldr_type)
        conv2d_obj = conv2d.Conv2DWindow(self.custom_img, self.custom_path,
                                         self.custom_win, self.ldr_type)
        gauss2d_obj = gaussian2d.Gauss2DWindow(self.custom_img, self.custom_path,
                                               self.custom_win, self.ldr_type)
        lum_obj = lum.LumWindow(self.custom_img, self.custom_path,
                                self.custom_win, self.ldr_type)
        mosaic_obj = mosaic.MosaicWindow(self.custom_img, self.custom_path,
                                         self.custom_win, self.ldr_type)
        rot_obj = rotation.RotationWindow(self.custom_img, self.custom_path,
                                          self.custom_win, self.ldr_type)
        warp2d_obj = warp2d.Warp2DWindow(self.custom_img, self.custom_path,
                                         self.custom_win, self.ldr_type)
        self.filter_objs = [b2df_obj, b2ds_obj, conv2d_obj, gauss2d_obj,
                            lum_obj, mosaic_obj, rot_obj, warp2d_obj]
        filter_menu = menubar.addMenu("&Filters")
        filter_menu.addAction("&Bilateral2df",
                              (lambda: self.apply_filter(0)))
        filter_menu.addAction("&Bilateral2ds",
                              lambda: self.apply_filter(1))
        filter_menu.addAction("&Conv2D",
                              lambda: self.apply_filter(2))

        filter_menu.addAction("&Gaussian2D",
                              lambda: self.apply_filter(3))
        filter_menu.addAction("&Luminance",
                              lambda: self.apply_filter(4))
        filter_menu.addAction("&Mosaic",
                              lambda: self.apply_filter(5))
        filter_menu.addAction("&Rotation",
                              lambda: self.apply_filter(6))
        filter_menu.addAction("&Warp2D",
                              lambda: self.apply_filter(7))
        return filter_menu

    def construct_algo_menu(self, menubar):
        hdrmerge_obj = hdr_merger.HDRMergeWindow(self.custom_img, self.hdr_path,
                                                 self.custom_win, self.ldr_type)
        self.algo_objs = [hdrmerge_obj]
        algo_menu = menubar.addMenu("&Algorithms")
        algo_menu.addAction("&HDR Merger",
                            (lambda: self.apply_algo(0)))
        return algo_menu

    def apply_algo(self, i):
        self.algo_objs[i].exec()
        new_img = self.algo_objs[i].img
        if new_img is not None and self.algo_objs[i].modified:
            self.check_img(new_img)
            self.main_win.update_pixmap(self.main_img.width, self.main_win.height, self.hdr_path)
            self.custom_img = new_img
            self.update_objs()
            self.update_text()
            self.custom_flag = True

    def apply_filter(self, i):
        self.filter_objs[i].exec()
        new_img = self.filter_objs[i].img
        print(new_img)
        if new_img is not None and self.filter_objs[i].modified:
            self.custom_win.update_pixmap(self.custom_img.width, self.custom_img.height, self.custom_path)
            self.custom_img = new_img
            self.update_objs()
            self.update_text()
            self.custom_flag = True

    def do_ldr(self, command):
        print("here")
        if command == "none":
            self.ldr_type = pyc.LDR_type.LT_NONE
            ldr.none_action(self.custom_img, self.custom_path,
                            self.custom_win)
        elif command == "normal":
            self.ldr_type = pyc.LDR_type.LT_NOR
            ldr.nor_action(self.custom_img, self.custom_path,
                           self.custom_win)
        elif command == "gamma":
            self.ldr_type = pyc.LDR_type.LT_NOR_GAMMA
            ldr.gam_action(self.custom_img, self.custom_path,
                           self.custom_win)
        self.update_objs()
        self.update_text()
        self.custom_flag = True

    def do_transformation(self, action):
        if action == "r90cw":
            self.custom_img.rotate90CW()
        elif action == "r90ccw":
            self.custom_img.rotate90CCW()
        elif action == "fliph":
            self.custom_img.flipH()
        elif action == "flipv":
            self.custom_img.flipV()
        elif action == "blend":
            self.transform_objs[0].exec()

        self.custom_img.Write(self.custom_path, self.ldr_type)
        self.custom_win.update_pixmap(self.custom_img.width, self.custom_img.height, self.custom_path)
        self.update_text()
        self.update_objs()
        self.custom_flag = True


if __name__ == '__main__':

    # Create a Qt Application
    app = QApplication(sys.argv)

    # Create and show the form
    main_window = MainWindow()
    main_window.show()

    # Run the main Qt loop
    app.exec()

    # Deleting all the temp images
    print("Closing...")
    remove_temp_images()

    # Closing the program
    sys.exit()
