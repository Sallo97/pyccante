# This files contains the generic class ImageWindow.
# ImageWindow is a QLabel that contains the image to show.
# Inside the class there are the methods to set and get the image.
# This is a generic class, the one used by the GUI are MainWindow for the
# read image and CustomWindow for showing the preview image.

from PySide6.QtWidgets import QLabel
from PySide6 import QtGui
from PySide6.QtGui import QImage
import pyccante as pyc
from utils import str_path as sp
from PySide6.QtCore import Qt
import numpy as np


class ImageWindow(QLabel):
    def __init__(self, win_width, win_height,
                 info_frame=None):
        super(ImageWindow, self).__init__()

        # Set the passed parameters
        self.path = sp.get_plc_path()
        self.width = win_width
        self.height = win_height
        self.info_frame = info_frame

        # Set the image informations
        self.ext = None
        self.gamma = 0
        self.exp = 0
        self.ext = None

        # Load the base images and set base values
        self.default_ldr = pyc.LDR_type.LT_NONE
        self.default_hdr_ldr = pyc.LDR_type.LT_NOR
        self.ldr_type = self.default_ldr

        # Set the image and the pixmap
        self.img = pyc.Image(self.path, self.ldr_type)
        self.set_ext(self.img.nameFile.split(".")[-1])
        self.pixmap = QtGui.QPixmap(self.get_qimg())
        self.setAlignment(Qt.AlignCenter)

    def set_img(self, new_img):
        # Set a new image to the windows
        # new_img = the new image to set
        # hdr = if the image is hdr or not
        if new_img is not None:
            self.img = new_img

    def get_img(self):
        # Returns the image used in the windows
        return self.img

    def apply_simple_tmo(self):
        # Creates a tmo image from the current hdr image
        # Writes the tmo image in the data folder
        # Returns nothing
        tmo_img = pyc.FilterSimpleTMO.execute(self.img, self.gamma, self.exp)
        return tmo_img

    def set_ldr(self, ldr_type):
        # Set the current ldr type
        # used when reading or writing the
        # image currently used.
        # It returns nothing.
        self.ldr_type = ldr_type

    def update_sliders(self, gamma=None, exp=None):
        # Update the exp and gamma values
        # when the apposite sliders are moved.
        # Set the new values and update the image
        # gamma = the new gamma value
        # exp = the new exp value.
        # It returns nothing.

        if gamma is not None:
            self.gamma = gamma
        if exp is not None:
            self.exp = exp

    def get_qimg(self):
        # Returns the QImage of the image
        # used in the windows.
        # The QImage will be used by update_pixmap for
        # showing the image to both imgwindows of the GUI.

        # the raw data of the image must be interpreted as
        # a numpy uint8 array
        data = pyc.getData(self.img).astype(np.uint8)
        q_img = None

        # check the image extension
        if self.ext in ["hdr", "exr"]:
            new_img = self.apply_simple_tmo()
            new_img.clamp(0, 255)
            data = pyc.getData(new_img).astype(np.uint8)
            q_img = QImage(data, new_img.width, new_img.height,
                           new_img.width * new_img.channels, QtGui.QImage.Format.Format_RGB888)
            q_img = q_img.convertToFormat(QtGui.QImage.Format.Format_RGB32)
        elif self.ext in ["jpg", "bmp"]:
            q_img = QImage(data, self.img.width, self.img.height,
                           self.img.width * self.img.channels, QtGui.QImage.Format.Format_RGB888)
            q_img = q_img.convertToFormat(QtGui.QImage.Format.Format_RGB32)
        elif self.ext == "png":
            # PNG images could be RGB888 or ARGB32
            # we try which one give a full QImage
            q_img = QImage(data, self.img.width, self.img.height,
                   self.img.width * self.img.channels, QtGui.QImage.Format.Format_ARGB32).rgbSwapped()
            q_img = q_img.convertToFormat(QtGui.QImage.Format.Format_RGB32)
            if q_img.isNull():
                # If the qimage is null, this is probably a png with a format of RGB888
                img_format = QtGui.QImage.Format_RGB888
                q_img = QImage(data, self.img.width, self.img.height,
                               self.img.width * self.img.channels, QtGui.QImage.Format.Format_RGB888)
        return q_img

    def set_ext(self, ext=None):
        # This function is called when reading a new image
        # We must save the extension of the image because
        # it would be lost if we apply a tmo or other filters to the image
        # and we needed to determine the format of the QImage
        if ext is not None:
            self.ext = ext



