# This file contains the MosaicWindow class
# The MosaicWindow class has been removed from the GUI
# but the implementation is still here in case we want to add it again

import pyccante as pyc
import utils.str_warning as sw
from layouts.windows import warningwin as ww
from PySide6.QtWidgets import (QLabel, QPushButton, QHBoxLayout,
                               QVBoxLayout, QDialog)


class MosaicWindow(QDialog):
    def __init__(self, img, ldr_type):
        # MosaicWindow is a QDialog that
        # implements a window to apply
        # the Mosaic filter to an image.
        # img = image to apply the filter to.
        # ldr_type = ldr_type of the image.
        super(MosaicWindow, self).__init__()
        self.ldr_type = ldr_type
        self.img = img
        self.setWindowTitle("Mosaic...")

        # Define labels for parameters
        self.ask_label = QLabel("Apply the Filter?")

        # Define buttons
        self.OK_button = QPushButton("OK")
        self.Cancel_button = QPushButton("Cancel")
        self.OK_button.clicked.connect(self.execute)
        self.Cancel_button.clicked.connect(self.hide)

        # Put buttons into a layout
        self.buttons_layout = QHBoxLayout()
        self.buttons_layout.addWidget(self.OK_button)
        self.buttons_layout.addWidget(self.Cancel_button)

        # Construct windows
        self.main_layout = QVBoxLayout(self)
        self.main_layout.addWidget(self.ask_label)
        self.main_layout.addLayout(self.buttons_layout)

    def execute(self):
        # Execute the Mosaic filter
        # Modify the self.img with the filtered one.
        new_img = pyc.FilterMosaic.execute(self.img)
        self.set_img(new_img)

    def set_img(self, new_img):
        # Set the new_img as the current one.
        # new_img = new image to set.
        if new_img is not None:
            self.img = new_img
            self.hide()
        else:
            ww.WarningWindow(sw.invalid_image_str()).exec()
