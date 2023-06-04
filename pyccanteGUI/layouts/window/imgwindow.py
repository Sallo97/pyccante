from PySide6.QtWidgets import QLabel
from PySide6 import QtGui
import pyccante as pyc
from utils import path
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

        # Load the base images and set base values
        self.default_ldr = pyc.LDR_type.LT_NONE
        self.default_hdr_ldr = pyc.LDR_type.LT_NOR
        self.ldr_type = self.default_ldr

        self.img = pyc.Image(self.path, self.ldr_type)
        self.pix_map = QtGui.QPixmap(self.path)
        self.setAlignment(Qt.AlignCenter)

    def set_img(self, new_img, hdr):
        # Set a new image to the window
        # new_img = the new image to set
        # hdr = if the image is hdr or not
        if new_img is not None:
            self.img = new_img



    def get_img(self):
        # Returns the image used in the window
        return self.img

    def check_img_ext(self, hdr):
        # Checks the image extension and returns the path to
        # read it
        # hdr = is an hdr image or not

        new_path = self.img.nameFile

        # Checking if the image is hdr or ldr
        if hdr:
            new_path = path.get_hdr_path()
            tmo_img = pyc.ReinhardTMO.executeGlobal1(self.img)
            tmo_img.Write(new_path, self.ldr_type)

        return new_path

    def set_ldr(self, ldr_type):
        self.ldr_type = ldr_type



