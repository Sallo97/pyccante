# This file contains the MenuBarWindow class, which implements the menu bar of the GUI.

import pyccante as pyc
from bars import file as fl
from algorithms import hdr_merger
from transformations import blend
from filters import (b2df, b2ds, conv2d, gaussian2d,
                     lum, rotation, warp2d)
from PySide6.QtWidgets import QMenuBar, QFileDialog


class MenuBarWindow(QMenuBar):
    def __init__(self, main_win, custom_win, main):
        super(MenuBarWindow, self).__init__()
        self.main = main
        self.main_win = main_win
        self.custom_win = custom_win
        self.ldr_type = pyc.LDR_type.LT_NONE
        self.construct_file_menu()
        self.construct_transform_menu()
        self.construct_filter_menu()
        self.construct_algo_menu()

    def construct_file_menu(self):
        # Construct the File sub-menu
        file_menu = self.addMenu("&File")
        file_menu.addAction("&Open...",
                            (lambda: self.do_action("File",
                                                    "open")),
                            "Ctrl+O")
        file_menu.addAction("&Save as...",
                            (lambda: self.do_action("File",
                                                    "save")),
                            "Ctrl+S")
        file_menu.addAction("&Revert to original size",
                            lambda: self.do_action("File",
                                                   "rescale"))

    def construct_transform_menu(self):
        # Construct the Transform sub-menu
        transform_menu = self.addMenu("&Transform")
        transform_menu.addAction("&Rotate 90° clockwise",
                                 (lambda: self.do_action("Transformation",
                                                         "r90cw")),
                                 "Ctrl+["
                                 )
        transform_menu.addAction("&Rotate 90° counterclockwise",
                                 (lambda: self.do_action("Transformation",
                                                         "r90ccw")),
                                 "Ctrl+]"
                                 )
        transform_menu.addAction("&Flip horizontally",
                                 (lambda: self.do_action("Transformation",
                                                         "fliph")),
                                 "Ctrl+H"
                                 )
        transform_menu.addAction("&Flip vertically",
                                 (lambda: self.do_action("Transformation",
                                                         "flipv")),

                                 "Ctrl+V"
                                 )
        transform_menu.addAction("&Blend",
                                 (lambda: self.do_action("Transformation",
                                                         "blend")),
                                 "Ctrl+B"
                                 )

    def construct_filter_menu(self):
        # Construct the Filters sub-menu
        filter_menu = self.addMenu("&Filters")
        filter_menu.addAction("&Bilateral2df",
                              (lambda: self.do_action("Filter",
                                                      "b2df")))
        filter_menu.addAction("&Bilateral2ds",
                              lambda: self.do_action("Filter",
                                                     "b2ds"))
        filter_menu.addAction("&Conv2D",
                              lambda: self.do_action("Filter",
                                                     "conv2d"))
        filter_menu.addAction("&Gaussian2D",
                              lambda: self.do_action("Filter",
                                                     "gauss2d"))
        filter_menu.addAction("&Rotation",
                              lambda: self.do_action("Filter",
                                                     "rot"))
        filter_menu.addAction("&Warp2D",
                              lambda: self.do_action("Filter",
                                                     "warp2d"))
        return filter_menu

    def construct_algo_menu(self):
        # Construct the Algorithms sub-menu
        algo_menu = self.addMenu("&Algorithms")
        algo_menu.addAction("&HDR Merger",
                            (lambda: self.do_action("Algorithm",
                                                    "hdr_merger")))
        return algo_menu

    def do_action(self, cat, action):
        # This function calls the right action and update the custom img to the new modified one.
        # cat = the category that contains the action (Filter,Algorithm, LDR, Transformation)
        # action = the action you want to apply (es. b2df, hdr_merger, r90cw, etc.)
        new_img = None
        if cat == "File":
            new_img = self.do_file(action)
        elif cat == "Filter":
            new_img = self.do_filter(action)
        elif cat == "Algorithm":
            new_img = self.do_algo(action)
        elif cat == "Transformation":
            new_img = self.do_transformation(action)
        # If the action was rescale, there's no need to re-write the image
        if action != "rescale" and new_img is not None:
            self.custom_win.set_img(new_img)
        if cat == "Algorithm" or action == "open":
            self.custom_win.original_size()

    def do_file(self, action):
        # Calls the requested file function
        # and returns the new image
        new_img = None
        if action == "open":
            new_img = self.open_dialog()
        elif action == "save":
            self.save_dialog()
        elif action == "rescale":
            self.custom_win.original_size()

        return new_img

    def do_algo(self, action):
        # Calls the requested algorithm function
        # and returns the new image
        action_obj = None
        if action == "hdr_merger":
            action_obj = hdr_merger.HDRMergerWindow()
            self.main.update_window_title("HDR Merger result")

        action_obj.exec()
        new_img = action_obj.img
        if new_img is not None:
            self.custom_win.set_ext("hdr")
            self.main_win.set_ext("hdr")
            self.custom_win.set_ldr(pyc.LDR_type.LT_NONE)
            self.main_win.set_ldr(pyc.LDR_type.LT_NONE)
            self.main_win.set_img(new_img)
        del action_obj
        return new_img

    def do_filter(self, action):
        # Calls the requested filter function
        # and returns the new image
        action_obj = None

        new_img = self.custom_win.get_img()

        if action == "b2df":
            action_obj = b2df.B2DFWindow(new_img)
        elif action == "b2ds":
            action_obj = b2ds.B2DSWindow(new_img)
        elif action == "conv2d":
            action_obj = conv2d.Conv2DWindow(new_img)
        elif action == "gauss2d":
            action_obj = gaussian2d.Gauss2DWindow(new_img)
        elif action == "lum":
            action_obj = lum.LumWindow(new_img)
        elif action == "rot":
            action_obj = rotation.RotationWindow(new_img)
        elif action == "warp2d":
            action_obj = warp2d.Warp2DWindow(new_img)

        action_obj.exec()

        new_img = action_obj.img

        del action_obj
        return new_img

    def do_transformation(self, action):
        # Calls the requested transformation function
        # and returns the new image
        new_img = self.custom_win.get_img()
        if action == "r90cw":
            new_img.rotate90CW()
            self.custom_win.invert_w_h()
        elif action == "r90ccw":
            new_img.rotate90CCW()
            self.custom_win.invert_w_h()
        elif action == "fliph":
            new_img.flipH()
        elif action == "flipv":
            new_img.flipV()
        elif action == "blend":
            blend_obj = blend.Blend(self.custom_win.img)
            blend_obj.exec()
            new_img = blend_obj.img
            del blend_obj

        return new_img

    def open_dialog(self):
        # Opens a window for the user to select
        # an image to read
        new_path = QFileDialog.getOpenFileName(
            self,
            "Open the image", "",
            "Image Files (*.ppm *.pgm *.tga *.png *.jpg *.bmp *.hdr *.exr)")[0]
        new_img = fl.read_img(new_path)
        if new_img is not None:
            self.main_win.info_frame.update_text(new_img)
            self.main.update_window_title(new_img.nameFile)
            self.custom_win.set_ext(new_img.nameFile.split(".")[-1])
            self.main_win.set_ext(new_img.nameFile.split(".")[-1])
            self.custom_win.set_ldr(pyc.LDR_type.LT_NONE)
            self.main_win.set_ldr(pyc.LDR_type.LT_NONE)
            self.main_win.set_img(new_img)
        return new_img

    def save_dialog(self):
        # Opens a window for the user to select
        # where to save the modified image
        path = QFileDialog.getSaveFileName(
            self,
            "Save the image",
            "new_img",
            ".ppm;; .pgm;; .tga;; .png;; .jpg;; .bmp;; .hdr;; .exr",)

        # If the image is HDR, it must be tone mapped according to the
        # exposure values specified by the user in the sliders
        if self.custom_win.ext == "hdr":
            tmo_img = self.custom_win.apply_simple_tmo()
            fl.save_img(tmo_img, path, self.custom_win.ldr_type)

        # If the image is SDR, just save it
        else:
            fl.save_img(self.custom_win.img, path, self.custom_win.ldr_type)
        return None
