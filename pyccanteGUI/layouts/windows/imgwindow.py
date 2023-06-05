# This files contains the generic class ImageWindow.
# ImageWindow is a QLabel that contains the image to show.
# Inside the class there are the methods to set and get the image.
# This is a generic class, the one used by the GUI are MainWindow for the
# read image and CustomWindow for showing the preview image.

from PySide6.QtWidgets import QLabel
from PySide6 import QtGui
import pyccante as pyc
import tempfile
from utils import path
from layouts import windows
from PySide6.QtCore import Qt


class ImageWindow(QLabel):
    def __init__(self, win_width, win_height,
                 info_frame=None):
        super(ImageWindow, self).__init__()

        # Set the passed parameters
        self.path = path.get_plc_path()
        self.width = win_width
        self.height = win_height
        self.info_frame = info_frame

        # Set the flag
        self.hdr_flag = False
        self.gamma = 0
        self.exp = 0

        # Load the base images and set base values
        self.default_ldr = pyc.LDR_type.LT_NONE
        self.default_hdr_ldr = pyc.LDR_type.LT_NOR
        self.ldr_type = self.default_ldr

        # Set the image and the pixmap
        self.img = pyc.Image(self.path, self.ldr_type)
        self.pix_map = QtGui.QPixmap(self.path)
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

    def check_img_ext(self):
        # Checks if the img is LDR or HDR
        # does the tmo conversion if needed
        # hdr = is a hdr image or not
        # returns the path of the image
        # that the pixmap will use

        new_path = self.img.nameFile

        # Checking if the image is hdr or ldr
        if self.hdr_flag:
            new_path = path.get_hdr_path()
            self.apply_simple_tmo(new_path)
        return new_path

    def apply_simple_tmo(self, new_path):
        # Creates a tmo image from the current hdr image
        # Writes the tmo image in the data folder
        # Returns nothing
        tmo_img = pyc.FilterSimpleTMO.execute(self.img, self.gamma, self.exp)
        tmo_img.Write(new_path, self.ldr_type)

    def set_ldr(self, ldr_type):
        # Set the current ldr type
        # used when reading or writing the
        # image currently used.
        # It returns nothing.
        self.ldr_type = ldr_type

    def set_hdr_flag(self, hdr_flag):
        # Set the hdr flag.
        # if it's true the image is hdr
        # if it's false the image is ldr
        # hdr_flag = the new hdr flag
        self.hdr_flag = hdr_flag

    def get_hdr_flag(self):
        # Returns the hdr flag
        return self.hdr_flag

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
        if self.hdr_flag:
            self.set_img(None)
        else:
            # If the image is LDR, launch a warning
            ww = windows.warningwin.WarningWindow("Cannot apply the slider value to an ldr image!")
            ww.exec()
